#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* mallocX( size_t size ){
	void * result = malloc( size );
	if(result == NULL){
		fprintf(stderr,"Not egnougth memory.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int binomial(int n, int m){

	int size = m+1;
	int* array = (int*) mallocX( size*sizeof(int) );

	for(int i=0; i<size; i++){
		array[i] = 0;
	}
	array[0] = 1;
	
	for( int tmp_n =1; tmp_n<n+1; tmp_n++ ){
		for( int k = m+1; k>0; k-- ){
			array[k] = array[k] + array[k-1];
		}
	}

	int result = array[m];
	free(array);
	return result;
}

int main( int argc, char* argv[] ){
	int n = 8;
	int m = 4;
	int result = binomial( n, m);
	printf("Binomial( %d, %d ) = %d \n", n, m, result );

	return 0;
}