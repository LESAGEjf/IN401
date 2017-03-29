#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <utime.h>

int main(int argc, char *argv[]){
	
	clock_t clock_start, clock_end;
	struct tms tms_start, tms_end;

	clock_start = times(&tms_start);

	int pro;
	pro = fork();
	if(pro == 0){

		char chaine[259];
		int i;

		chaine[0] = '\0';

		strcat(chaine, "ls");
		strcat(chaine, argv[1]);
		i = system(chaine);
		//system ca sert a executer une commande systeme,
		//chaine = "ls" donc ca fait la commande shell ls
		
		clock_end = times("# \n" tms_end);

		printf(tms_end);

		if(i == -1){
			exit(1);
		}
	}
}