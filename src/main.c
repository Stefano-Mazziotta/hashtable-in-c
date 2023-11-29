#include "hash_table.h"
// gcc -o main main.c hash_table.c
int main(){
      
    if (!init_hash_table()) {
        fprintf(stderr, "Failed to initialize hash table.\n");
        return 1;
    }

    print_table();

    person stefano = {.name = "Stefano", .age = 22};
    person alvaro = {.name = "Alvaro", .age = 33};
    person jose = {.name = "Jose", .age = 27};
    person sofia = {.name = "Sofia", .age = 21};

    hash_table_insert(&stefano);
    hash_table_insert(&alvaro);
    hash_table_insert(&jose);
    hash_table_insert(&sofia);

    print_table();

    person* sofiaFound = hash_table_lookup("Sofia");
    if (sofiaFound == NULL) {
        printf("Not found!\n");
    } 
    if(sofiaFound != NULL){ 
        printf("Found %s.\n", sofiaFound->name);
    }

    hash_table_delete("Sofia");
    
    sofiaFound = hash_table_lookup("Sofia");

    if (sofiaFound == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s.\n", sofiaFound->name);
    }

    print_table();

    free_hash_table();

    return 0;
}