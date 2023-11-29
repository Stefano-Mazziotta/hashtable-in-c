#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 256
#define TABLE_SIZE 10

typedef struct Person {
    char name[MAX_NAME_LENGTH];
    int age;
    struct Person* next;
} person;

bool init_hash_table();
void free_hash_table();
void print_table();
bool hash_table_insert(person* p);
person* hash_table_lookup(char* name);
person* hash_table_delete(char* name);

#endif
