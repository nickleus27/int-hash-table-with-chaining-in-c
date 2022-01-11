//
//  int_vector.h
//  int_growing_array_c
//
//  Created by Nicholas Anderson on 9/12/21.
//

#ifndef int_vector_h
#define int_vector_h
#define INCREMENT 1

#include <stdio.h>
#include <stdbool.h>

typedef struct Int_Vector int_vector;

int_vector* new_int_vector(size_t );

bool intv_push( int_vector *, int );

void intv_finalizeMemory(int_vector *);

void intv_free(int_vector *);

int intv_size(int_vector *);

int intv_get(int_vector *, int);

int intv_pop(int_vector *);

void intv_clear(int_vector *);

int erase(int_vector *, int);

#endif /* int_vector_h */
