#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <utime.h>

#define MAXBUF 1024
#define MAXLINE 1024
#define D_FMODE 0666
#define D_DMODE 0777

int copie_repertoire(char* source, char* copie);
int copie_arbre(char* source, char* copie);

int copie(int fs, int fd){
	char buf[MAXBUF];
	int n;

	while((n=read(fs,buf,MAXBUF))>0){
		if(write(fd,buf,n) != n)
			return -1;
		return n;
	}
}

int copie_fichier(char source[], char dest[]) {
	int fs,fd;
	int n ;
	fs=open(source,O_RDONLY);
	if(fs== -1)
		return -1;

	fd=open(dest,O_WRONLY | O_CREAT | O_TRUNC, D_FMODE);
	if(fd==-1){
		close(fs);
		return -1;
	}
	n=copie(fs,fd);
	close(fs);
	close(fd);

	return n;
}

int copie_repertoire(char* source, char* copie){
	DIR* rep = opendir(source);
	mkdir(copie,0777);
	char *tempsource, *tempdest;

	tempsource = source + strlen(source); //source tout seul met au début de la case mémoire
	//avec le strlen(source) il se place a la fin
	*tempsource ++ = '/' ;
	tempdest = copie + strlen(copie);
	*tempdest ++ = '/';
	struct dirent *dir;
	while((dir = readdir(rep)) != NULL){
		strcpy(tempsource, dir->d_name);
		strcpy(tempdest, dir->d_name);
		copie_arbre(tempsource, tempdest);
	}
	closedir(rep);
	*(tempsource-1) = '\0';
	*(tempdest-1) = '\0'; // le \0 dire que c'est une fin de chaine de caractère


	
	return 0;
}

int copie_arbre(char* source, char* copie){
	int n;

	struct stat stbuf;
	if(stat(source, &stbuf) == -1){/*erreur*/}
		
	if(stbuf.st_mode & S_IFDIR != 0){
		copie_repertoire(source, copie);
	}
	else if(stbuf.st_mode & S_IFREG != 0){
		n = copie_fichier(source, copie);
	}
	else n = -1;

	chmod(copie, stbuf.st_mode & 07777);
	struct utimbuf tm;

	tm.actime = stbuf.st_atime;
	tm.modtime = stbuf.st_mtime;
	utime(copie, &tm);

	return n;
}

int main(int argc, char* argv[]){
	char source[MAXLINE], dest[MAXLINE];
	if(argc != 3){
		//error
	}
	strcpy(source, argv[1]);
	strcpy(dest, argv[2]);
	if(copie_arbre(source, dest )== -1){
		//error
		exit(1);
	}
	exit(0);
}