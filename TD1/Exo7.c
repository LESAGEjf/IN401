#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 1024

struct FICHIER
{
	int flags;
	int fd;
	int reste;
	unsigned char buf[1024];
	unsigned char *p;
};
typedef struct FICHIER FICHIER;

#define F_R 1
#define F_W 2

FICHIER *my_open(char *file, char *mode){
	FICHIER *fp;
	int m;
	int f;
	int fd;

	switch (mode[0]){
		case 'r':
		m = O_RDONLY;
		f = F_R;
		break;
		case 'w':
		m = O_CREAT | O_TRUNC | O_WRONLY;
		f = F_W;
		break;
		default:
		return NULL;
	}
	fd = open (file, m, 0666);
	if (fd == 1) return NULL;

	fp = (FICHIER *) malloc (sizeof (*fp));
	if (fp == NULL) return NULL;

	fp->flags = f;
	fp->fd = fd;
	fp->reste = 0;
	fp->p = fp->buf;

	return fp;
}

int my_getc (FICHIER * fp) {
	if ((fp->flags & F_R) == 0) return EOF;

	if(fp->reste <= 0){
		fp->reste = read (fp->fd, fp->buf, MAX);
		fp->p = fp->buf;
	}

	return (fp->reste <= 0) ? EOF : (fp->reste--, *(fp->p++));
}

int my_putc (int c, FICHIER *fp){
	if((fp->flags & F_W) ==0) return EOF;

	if(fp->reste >= MAX){
		if(write (fp->fd, fp->buf, MAX) != MAX)
			return EOF;
		fp->p = fp->buf;
		fp->reste = 0;
	}

	*(fp->p++) = c;
	fp->reste++;
	return c;
}

int my_close (FICHIER *fp){
	if((fp->flags & F_W) != 0 && fp->reste > 0){
		if(write (fp->fd, fp->buf, fp->reste) != fp->reste)
			return EOF;
	}
	close (fp->fd);
	free (fp);
	return 0;
}

int main (int argc, char *argv[]){
	FICHIER *f1, *f2;
	int c;

	f1 = my_open (argv[1], "r");
	if (f1 == NULL){
		perror ("peux pas ouvrir le premier fichier");
		exit(1);
	}

	f2 = my_open(argv[2], "w");
	if (f2 == NULL){
		perror ("peux pas ouvrir le fichier");
		exit(1);
	}

	while ((c = my_getc (f1)) != EOF) my_putc (c, f2);

	my_close (f1);
	my_close (f2);
	return 0;
}