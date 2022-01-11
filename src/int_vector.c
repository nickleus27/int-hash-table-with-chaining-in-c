//
//  int_vector.c
//  int_growing_array_c
//
//  Created by Nicholas Anderson on 9/12/21.
//

#include "int_vector.h"
#include <stdlib.h>

//initialize vector with initial size argument
struct Int_Vector
{
    size_t space_left;
    size_t size;
    int *ptr;
};

int_vector* new_int_vector(size_t init_size )
{
    int_vector* vector = (int_vector*)malloc(sizeof(struct Int_Vector));
    vector->ptr = malloc(init_size * sizeof(int *));//initialize array to size set to argument
    if(!vector->ptr){
        printf("Failed malloc\n");
        exit(EXIT_FAILURE);
    }
    vector->size = 0;//array is empty
    vector->space_left = init_size;//space left is initial size (16)
    return vector;
}

bool intv_push( int_vector *vector, int data ){

    if( vector->space_left == 0 ){//if array is full
        int *ptrTemp = NULL;
        size_t maxLength = 0;
        maxLength = vector->size<<INCREMENT;//1;//double the size of array (maxLength x 2)
        ptrTemp = realloc(vector->ptr, maxLength * sizeof(int *) );//have vptrTemp = realloc incase not succesful
        if( ptrTemp == NULL )
        {//exit it realloc failed
            printf( "Failed realloc");
            return false;
        }
        vector->space_left = maxLength - vector->size;//space left after growing
        vector->ptr = ptrTemp;//have vector point to realloc array
    }

    vector->ptr[vector->size++] = data;//now that we have space push data to next available spot
    vector->space_left--;
    return true;
}

//This will make the memory efficient.
void intv_finalizeMemory(int_vector *vector)
{
    vector->ptr = realloc(vector->ptr, vector->size * sizeof(int *));
}

//free memory back to heap
void intv_free(int_vector *vector)
{
    free(vector->ptr);
    free(vector);
}

//return amount of elements in array
int intv_size(int_vector *vector)
{
    return (int)vector->size;
}

/* return integer value at index*/
int intv_get(int_vector *vector, int index )
{
    if(index >= vector->size)
    {
        printf("Error: index %d out of bounds ", index);
        intv_free(vector);
        exit(EXIT_FAILURE);
    }
    else
    {
        //int * tempptr = &vector->ptr[0];
        return vector->ptr[index];
    }
}
 
int intv_pop(int_vector *vector)
{
    if(vector->size == 0)
        return 0;
    int pop = vector->ptr[--vector->size];
    vector->ptr[vector->size] = 0; // clear data from array
    vector->space_left++;
    return pop;
}


void intv_clear(int_vector *vector)
{
    while(vector->size != 0)
    {
        vector->ptr[--vector->size] = 0;
        vector->space_left++;
    }
}

int erase(int_vector *vector, int index)
{
    int value=0;
    if (index<0 || index>=(int)vector->size)
        return value;
    value = vector->ptr[index];
    while (index < vector->size-1)
    {
        vector->ptr[index] = vector->ptr[index+1];
        index++;
    }
    vector->ptr[--vector->size]=0;
    vector->space_left++;
    return value;
}