// https://www.youtube.com/watch?v=2Ti5yvumFTU

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct {
    char name[MAX_NAME];
    int age;
    // add ... other stuff later, maybe
} person;

person * hash_table[TABLE_SIZE];

// El rango de un int va de -2.147.483.648 a 2.147.483.647.
// El rango de un unsigned int va de 0 to 4.294.967.295
unsigned int hash(char *name){
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for(int i = 0; i < length; i++){
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

bool init_hash_table(){
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
    // table is empty
}

void print_table(){
    printf("Start\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if(hash_table[i] == NULL){
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
    printf("End\n");
}

bool hash_table_insert(person *person){
    if(person == NULL) return false;
    
    int index = hash(person->name);

    for (int i = 0; i < TABLE_SIZE; i++){
        int try = (i + index) % TABLE_SIZE;
        if(hash_table[try] == NULL){
            hash_table[try] = person;

            return true;
        }
    }
    
    return false;
}

// find a person in the table by their name
person *hash_table_lookup(char *name){
    int index = hash(name);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (index + i) % TABLE_SIZE;
        if(hash_table[try] != NULL &&
           strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0   
        ){
            return hash_table[try];
        }
    }

    return NULL;
}

person *hash_table_delete(char *name){
    int index = hash(name);

    if(hash_table[index] != NULL &&
       strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0
    ){
        person *tmp = hash_table[index];
        hash_table[index] = NULL;
        return tmp;
    } else {
        return NULL;
    }
}



int main(){
    init_hash_table();
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

    person *tmp = hash_table_lookup("Sofia");
    if(tmp == NULL){
        printf("Not found!\n");
    } else {
        printf("Found %s.\n", tmp->name);
    }

    hash_table_delete("Sofia");
    tmp = hash_table_lookup("Sofia");

    if(tmp == NULL){
        printf("Not found!\n");
    } else {
        printf("Found %s.\n", tmp->name);
    }

    print_table();
    // printf("Jacob => %u\n", hash("Jacob"));
    // printf("Stefano => %u\n", hash("Stefano"));
    // printf("Sara => %u\n", hash("Sara"));
    // printf("Santiago => %u\n", hash("Santiago"));
    // printf("Pepe => %u\n", hash("Pepe"));

    return 0;
}
