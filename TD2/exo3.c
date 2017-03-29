#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <utime.h>

void creation(int n, int m){
	int i, pid;

	for(i=0; i<n; i++){
		pid = fork();
	}
	if(pid == -1){
		printf("erreur");
	}
	if(pid == 0){
		if(m > 1){
			creation(n, m);
		}
	}
	if(pid > 0){
		for(i=0; i<n; i++){
			wait(&pid);
		}
	}
}