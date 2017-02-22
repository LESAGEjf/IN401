#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main () {
	int tmp, toto, titi;
	
	toto = open("toto", O_RDONLY);
	titi = open("titi", O_CREAT | O_WRONLY);
	
	while(read(toto,&tmp,1) !=0){
		write(titi,&tmp,1);
	}
	
	close(toto);
	close(titi);
	
	return 0;
}
