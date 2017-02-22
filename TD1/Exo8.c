#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>


#define MAXBUF 1024
#define MAXLINE 1024
#define D_FMODE 0666
#define D_DMODE 0777


int copie(int fs, int fd){
	char buf[MAXBUF];
	int n;

	while((n=read(fs,buf,MAXBUF))>0)
		if(write(fd,buf,n) != n)
			return -1;
		return n;
	}

int copier(char source[], char dest[]) {
	int fs,fd;
	int n ;
	fs=open(source,O_RDONLY);
	if(fs== -1)
		return -1;

	fd=open(dest,O_WONLY | O_CREAT | O_TRUNC, D_FMODE);
	if(fd==-1){
		close(fs);
		return -1;
	}
	n=copie(fs,fd);
	close(fs);
	close(fd);

	return n;
}

