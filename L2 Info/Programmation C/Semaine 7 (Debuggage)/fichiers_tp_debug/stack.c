#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int * tab;
	int size;
} data;

void* mallocX( size_t size ){
	void * result = malloc( size );
	if(result == NULL){
		fprintf(stderr,"Not egnougth memory.\n");
		exit(EXIT_FAILURE);	
	}
	return result;
}

data* init_data( data* d ){
	for( int i=0; i< d->size; i++ ){
		d->tab[i] = 0;
	}
	return d;
}

data* create_data( int size ){
	data d;
	d.size = size;
	d.tab = (int*) mallocX( size * sizeof(int) );
	return init_data( &d );	
}

void free_data( data * d ){
	free( d->tab );
	free( d );
}

int main(){
	int size = 5;

	data* d = create_data(size);
	for( int i=0; i<size; i++ ){
		d->tab[i] = i;
	}
	for( int i=0; i<size; i++ ){
		printf( "%d \n", d->tab[i] );
	}
	free_data(d);
	
	return 0;
}