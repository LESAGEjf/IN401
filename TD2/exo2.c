#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <utime.h>

#define nbr_process 20

int main(){
	int pid, return_value, i;

	for(i=0; i<nbr_process; i++){
		pid = fork();
		if(pid == -1){
			exit(0);
		}
		if(pid == 0){
			exit(getpid() % 10)
		}
	}

	for(i=0; i<nbr_process; i++){
		pid = wait(&return_value);
		printf("pid fils : %d\n", pid);
		printf("return value : %d\n", WEXITSTATUS(return_value));
	}
	exit(0);
}