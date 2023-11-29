#include "hash_table.h"

person** hash_table;

size_t hash(char *name){
    size_t length = strnlen(name, MAX_NAME_LENGTH);
    size_t hash_value = 0;
    for(size_t i = 0; i < length; i++){
        hash_value = (hash_value + name[i]) * 31;
        hash_value = hash_value % TABLE_SIZE;
    }
    return hash_value;
}

bool init_hash_table(){
    
    hash_table = (person**)malloc(TABLE_SIZE * sizeof(person*));
    
    if(hash_table == NULL){
        return false; // Memory allocation failed
    }

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }

    return true;
}
// free dynamic memory (heap)
void free_hash_table() {
    if (hash_table == NULL) {
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        person* currentPerson = hash_table[i];
        while (currentPerson != NULL) {
            person* next = currentPerson->next;
            free(currentPerson);
            currentPerson = next;
        }
        hash_table[i] = NULL;
    }

    free(hash_table);
    hash_table = NULL;
}

void print_table(){
    printf("Start\n");
    
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if(hash_table[i] == NULL){
            printf("\t%i\t---\n", i);
        
        }
        
        if(hash_table[i] != NULL){
            
            printf("\t%i\t ", i);
            
            person *currentPerson = hash_table[i];
            while (currentPerson != NULL)
            {
                printf("%s - ", currentPerson->name);
                currentPerson = currentPerson->next;
            }

            printf("\n");
        }
    }
    printf("End\n");
}

bool hash_table_insert(person *inputPerson) {
    if (inputPerson == NULL) {
        return false;
    }

    // Allocate memory for the new person
    person* newPerson = (person*)malloc(sizeof(person));
    if (newPerson == NULL) {
        return false;
    }

    // Copy the input data to the new person
    strncpy(newPerson->name, inputPerson->name, MAX_NAME_LENGTH);
    newPerson->age = inputPerson->age;
    newPerson->next = NULL;

    int index = hash(newPerson->name);

    // Insert the new person at the beginning of the linked list
    newPerson->next = hash_table[index];
    hash_table[index] = newPerson;

    return true;
}

// find a person in the table by their name
person *hash_table_lookup(char *name){
    int index = hash(name);
    person *currentPerson = hash_table[index];

    while (currentPerson != NULL && strncmp(currentPerson->name, name, MAX_NAME_LENGTH) != 0)
    {
        currentPerson = currentPerson->next;
    }

    return currentPerson;
}

person *hash_table_delete(char *name){
    int index = hash(name);

    person *currentPerson = hash_table[index];
    person *previousPerson = NULL;
    while (currentPerson != NULL && strncmp(currentPerson->name, name, MAX_NAME_LENGTH) != 0)
    {
        previousPerson = currentPerson;
        currentPerson = currentPerson->next;
    }

    if(currentPerson == NULL) return NULL;

    if(previousPerson == NULL) {
        // deleting the head
        hash_table[index] = currentPerson->next;
    } else {
        previousPerson->next = currentPerson->next;
    }

    return currentPerson;
}