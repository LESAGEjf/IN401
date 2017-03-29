#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <utime.h>

int main(void){
	int pid;

	pid = fork();
	if(pid == -){
		printf("fork error\n");
		exit(-);
	} else if(pid == ){
		/* fils */
		printf("fils : pid fils = %d\n", getpid());
		printf("fils : pid pere = %d\n", getppid());
		exit(getpid() % 10);
	}else{
		/* pere */
		int status;
		printf("pere : pid pere = %d\n", getpid() );
		printf("pere : pid fils = %d\n", pid );
		wait(&status);
		printf("status : %d\n", status);
		if(WIFEXITED(status)){
			printf("exited status %d\n", WEXITSTATUS(status));
		} else if(WIFSIGNALED(status)){
			printf("killed by signal %d\n", WTERMSIG(status));
		} else if(WIFSTOPPED(status)){
			printf("stopped by signal %d\n", WSTOPSIG(status));
		} else if(WIFCONTINUED(status)){
			printf("continued\n");
		}
		/* printf("pere: code retour = %d\n", status >> 8); */
		exit(0);
	}
	/* on arrive jamais a ce point */
	return 0;
}