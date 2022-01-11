main : main.o int_vector.o hash_table.o
	clang -o main main.o int_vector.o hash_table.o

main.o : main.c hash_table.h
	clang -g -c main.c

hash_table.o : hash_table.c hash_table.h int_vector.h 
	clang -g -c hash_table.c

int_vector.o : int_vector.c int_vector.h 
	clang -g -c int_vector.c 
 

clean :
	rm main main.o int_vector.o hash_table.o
