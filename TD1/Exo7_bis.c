#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>


int main(){

	DIR* rep = NULL;
    rep = opendir("/home/user/Bureau/IN401/TD1"); /* Ouverture d'un dossier */

    if (rep == NULL){/* Si le dossier n'a pas pu être ouvert */
       printf("N'ouvre pas\n");
       exit(1); /* (mauvais chemin par exemple) */

    }
    struct dirent *dir;
    while((dir = readdir(rep)) != NULL){
    	if(dir->d_name[0] != '.')
    	printf("%s\n",dir->d_name);
}

    if (closedir(rep) == -1){ /* S'il y a eu un souci avec la fermeture */
        printf("ne ferme pas\n");
        exit(-1);
    }

    return 0;
}