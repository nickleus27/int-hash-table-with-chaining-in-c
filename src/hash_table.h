//
//  hash_table.h
//  hash_table_c
//
//  Created by Nicholas Anderson on 9/20/21.
//

#ifndef hash_table_h
#define hash_table_h

#include <stdio.h>
#include "int_vector.h"

typedef struct HashTable hashtable;

//needs to be freed from heap
hashtable* new_hashtable(size_t);
//frees hashtable off of heap
void free_hashtable(hashtable *);
bool insert_hashtable(hashtable *, int);
//const int hash(hashtable *, int);
int contains(hashtable *, int);
void print_table(hashtable *);
int key_erase(hashtable *, int);
#endif /* hash_table_h */
