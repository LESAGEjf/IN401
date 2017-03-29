#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <uvsqgraphics.h>


void affiche(int N){
	POINT p;
	int i;
	for(i=0; i<N; i++){
		p = wait_clic();
		draw_fill_circle(p, 50, rouge);
	}
}

int main(){
	init_graphics(400, 400);

	int N; 
	while( (N != NULL) && (N<256) ){
		N = scanf()
	}

	affiche(N);
}