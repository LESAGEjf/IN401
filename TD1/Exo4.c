#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MAXBUF 1024

int getchar2(void){
	unsigned char c;
	return read(0, &c, 1) ?c : EOF;
}

int buffergetchar(void){
	static unsigned char buf[MAXBUF];
	static int ncar;
	static char *p;

	if(ncar == 0){
		ncar = read (0, buf, MAXBUF);
		p = buf;
	}
	return (ncar-- >0) ? *p++ :EOF;
}

int main(){
	int res;
	 while(1){
	 	res = buffergetchar();
	 	if(res == EOF){
	 		printf("EOF\n");
	 		break;
	 	}
	 	printf("got: %c\n", res);
	 } 
	return 0;
}