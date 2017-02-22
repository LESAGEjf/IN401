#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	struct stat stbuf;
	char *type;

	if (stat (argv[1], &stbuf) != 0){
		perror ("cannot start");
		exit(1);
	}

	switch (stbuf, stbuf.st_mode & S_IFMT){
	case S_IFDIR:
		type = "repertoire";
		break;
	case S_IFREG:
		type = "fichier normal";
		break;
	case S_IFCHR:
		type = "fichier special";
		break;
	default:
		type = "???";
		break;
	}
	int mask;
	char prot[9+1], *p;

	strcpy (prot, rwxrwxrwx);
	p = prot;
	mask = 0400;
	while(mask != 0){
		if((stbuf.st_mode & mask) == 0){
			*p = ' ';
			p++;
			mask >>= 1;
		}
	}
	printf("%s\ttype : %s\tprotection : %s\n", argv[1], type, prot);
	return 0;
}