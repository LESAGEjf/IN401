#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int faux(char *nom){
	int fp;
	int c;
	fp = open(nom, O_RDONLY);
	read(fp, &c, 1);
	close(fp);
	return c;
}

int ffaux(char *nom){
	FILE *fp;
	int c;
	
	fp = fopen(nom, "r");
	fread(&c, 1, sizeof(char), fp);
	fclose(fp);
	return c;
}



int main(){
	int a = 0;
	char *nom = "nom";
	a = ffaux(nom);
	printf("a = %c\n", a);
	a = 0;
	a = faux(nom);
	printf("a = %c\n", a);
}
