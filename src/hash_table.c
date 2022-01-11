//
//  hash_table.c
//  hash_table_c
//
//  Created by Nicholas Anderson on 9/20/21.
//

#include "hash_table.h"
#include <stdlib.h>

struct HashTable{
    int_vector **ptr;
    size_t cap;
    size_t size;
};

struct Int_Vector
{
    size_t space_left;
    size_t size;
    int *ptr;
};

hashtable* new_hashtable(size_t init_size)
{
    hashtable* table = (hashtable*)malloc(sizeof(struct HashTable));
    table->ptr = (int_vector**)malloc(init_size * sizeof(int_vector));
    table->cap = init_size;
    table->size = 0;
    if(!table->ptr)
    {
        printf("Hashtable failed to malloc. Program Exit.");
        exit(EXIT_FAILURE);
    }
    
    for(size_t i = 0; i < table->cap; i++)
    {
        int_vector* v = new_int_vector(2);
        table->ptr[i] = v;
    }
    return table;
}

void free_hashtable(hashtable *table)
{
    for(size_t i = 0; i < table->cap; i++)
        intv_free(table->ptr[i]);
    free(table->ptr);
    free(table);
}

//not finished
void init_hashtable(hashtable table, size_t init_size)
{
    table.cap = init_size;
    table.size = 0;
}

size_t hash(hashtable *table, int key){
    const double c = 0.618033;
    double kc = key * c;
    return (size_t)((size_t)table->cap * (kc-(size_t)kc));
}

bool resize(hashtable * table){
    //increase hashtable capacity by 2x
    size_t maxLength = table->cap<<INCREMENT;
    int tempArr [table->cap];
    int tempIndx = 0;
    //pull out all values into a temp array
    for(size_t i = 0; i<table->cap; i++){
        for(int j=0; j<table->ptr[i]->size; j++)
            tempArr[tempIndx++] = intv_get(table->ptr[i], j);
        intv_free(table->ptr[i]);
    }
    
    //realloc new memomry size on heap
    int_vector** ptrtemp = (int_vector**)realloc(table->ptr, maxLength * sizeof(int_vector) );
    //table->ptr = (int_vector**)realloc(table->ptr, maxLength * sizeof(int_vector) );
    table->cap = maxLength; // <---set hashtable capacity to new increased size
    if(!ptrtemp)
    {
        printf("Hashtable failed to malloc. Program Exit.");
        return false;
    }
    
    table->ptr = ptrtemp;
    
    //re initialize vectors at each index of table
    for(size_t i = 0; i < table->cap; i++)
    {
        int_vector* v = new_int_vector(2);
        table->ptr[i] = v;
    }
    //re insert
    for(int i = 0; i<table->size; i++)
        intv_push(table->ptr[hash(table, tempArr[i])], tempArr[i]);
    return true;
}

bool insert_hashtable(hashtable *table, int key)
{
    /*
     check if size == cap-1
     copy ints into array[cap] and free vectors
     realloc hahtable * and initialize
     copy ints back into hashtable *
     */
    
    
    if(table->size == table->cap)
        if (!resize(table))
            return false;
     
    if (intv_push(table->ptr[hash(table, key)], key))
    {
        table->size++;
        return true;
    }
    return false;
}

int contains(hashtable *table, int key)
{
    int found = 0;
    int_vector * temp = table->ptr[hash(table, key)];
    for(int i = 0; i < temp->size && !found; i++)
        if(key == intv_get(temp, i))
            found = 1;
    return found;
}

void print_table(hashtable *table)
{
    for(size_t i = 0; i<table->cap; i++)
        for(int j=0; j<table->ptr[i]->size; j++)
            printf("%d ", intv_get(table->ptr[i], j));
    printf("\n");
}

int key_erase(hashtable * table, int key)
{
    int found = 0;
    int_vector * temp = table->ptr[hash(table, key)];
    for(int i = 0; i < temp->size && !found; i++)
        if(key == intv_get(temp, i))
        {
            found = key;
            erase(temp, i);
        }
    return found;
}