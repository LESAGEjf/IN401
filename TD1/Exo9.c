#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main(){
	chmod(dest, stbuf.stmode & 07777);
	struct utimbuf tm;

	tm.actime = stbuf.st_utime;
	tm.modtime = stbuf.stmtime;
	utime(dest, &tm);
}