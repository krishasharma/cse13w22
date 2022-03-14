#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include "node.h"
#include "salts.h"
#include "ht.h"
#include "speck.h"

// Please Note: Professor Long is cited throughout this assignment for providing the pseudocode in the assignment7 PDF document.
// Professor Long is also cited for the help he gave as Walter Sobchack (Elmer) on discord in the CSE13s - Winter2022 - Professor Long server.
// Throughout this assignment, I had high-level pseudocode collaboration with my sister Twisha Sharma (tvsharma)
// Eugene is cited throughout this assignment for this help with explaining how to properly begin and correctly implement this assignment
// during his section on 03_04_2022
// Ben is cited for his tutoring session on 03_08_2022
// during it he helped me understand that to access the salt array we should treat it as a pointer because we want to access the whole
// array, not a specific part of the array.
// Audrey is cited for her tutoring session on 03_09_2022
// during it she helped me understand how to properly delete the hash table as my destructor function was running errors.

struct HashTable {
    uint64_t salt[2]; // the salt to use for the hash function
    uint32_t size; // the number of slots in the hash table
    Node **slots;
};

struct HashTableIterator {
    HashTable *table;
    uint32_t slot;
};

HashTable *ht_create(uint32_t size) {
    // The constructor for a hash table.
    HashTable *ht = (HashTable *) calloc(1, sizeof(HashTable)); // allocate memory for the HashTable
    if (ht == NULL) { // if memory could not be allocated for the hash table
        return NULL;
    }
    Node **slots = (Node **) calloc(size, sizeof(Node *)); // allocate memory for the slots array
    ht->slots = slots;
    ht->size = size;
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;
    return ht;
}

void ht_delete(HashTable **ht) {
    // The destructor for a hash table.
    for (uint32_t index = 0; index < ht_size(*ht);
         index += 1) { // if there are any remaining nodes left in the hash table
        if ((*ht)->slots[index] != NULL) {
            node_delete(&(*ht)->slots[index]); // delete the nodes and free them
        }
    }
    free((*ht)->slots);
    (*ht)->slots = NULL;
    free(*ht); // free the hash table
    *ht = NULL; // sets pointer to the the freed hash table to NULL
}

uint32_t ht_size(HashTable *ht) {
    // Returns the hash table’s size, the number of slots it can index up to.
    return ht->size; // returns hash table size
}

Node *ht_lookup(HashTable *ht, char *word) {
    // Searches for an entry, a node, in the hash table that contains word.
    // If the node is found, the pointer to the node is returned.
    // Otherwise, a NULL pointer is returned.
    uint32_t count = 0;
    uint32_t index = hash(ht->salt, word)
                     % ht->size; // Credit: Hashing Lecture and Eugene's section on 03_04_22
    while (count < ht->size) { // parse through the whole hashtable
        Node **slots = &ht->slots[index];
        if (slots && strcmp(ht->slots[index]->word, word) == 0) {
            return ht->slots[index]; // return pointer to node
        }
        index = (index + 1) % ht->size;
        count += 1;
    }
    return NULL;
}

Node *ht_insert(HashTable *ht, char *word) {
    // Inserts the specified word into the hash table.
    // If the word already exists in the hash table, increment its count by 1.
    // Otherwise, insert a new node containing word with its count set to 1.
    uint32_t count = 0;
    uint32_t index = hash(ht->salt, word) % ht->size;
    if (count < ht->size) { // parse through the whole hashtable
        if (ht->slots[index] == NULL) { // if the current slot is empty
            ht->slots[index] = node_create(word); // create a node and place at the current slot
            ht->slots[index]->count = 1; // set the count of the word to 1
            return ht->slots[index]; // return pointer to node
        }
        if (strcmp(ht->slots[index]->word, word)
            == 0) { // if the word at the ht index is the same as the word you are trying to insert
            ht->slots[index]->count += 1; // increment the word occurance count
            return ht->slots[index]; // return pointer to node
        }
        index = (index + 1) % ht->size;
        count += 1;
    }
    return NULL;
}

void ht_print(HashTable *ht) {
    // A debug function to print out the contents of a hash table.
    uint32_t index = 0;
    for (index = 0; index < ht->size;
         index += 1) { // if the index value is greater than the size of the hash table
        if (ht->slots[index] != NULL) { // if the pointer to the node does not equal NULL
            printf("%s\n", ht->slots[index]->word); // print the word at the node
        }
    }
}

HashTableIterator *hti_create(HashTable *ht) {
    // Creates a new hash table iterator.
    // This iterator should iterate over the ht.
    HashTableIterator *hti = (HashTableIterator *) malloc(
        sizeof(HashTableIterator)); // allocate memory for the hash table iterator
    hti->table = ht;
    hti->slot = 0;
    return hti;
}

void hti_delete(HashTableIterator **hti) {
    // Deletes a hash table iterator.
    free(*hti); // free the hash table iterator
    *hti = NULL; // sets the pointer to the freed hash table iterator to NULL
}

Node *ht_iter(HashTableIterator *hti) {
    // Returns the pointer to the next valid entry in the hash table.
    while (
        hti->slot
        < hti->table
              ->size) { // while the slot field of the iterator is less than the size of the hash table iterator
        if (hti->table->slots[hti->slot]
            != NULL) { // if the entire hash table has not been iterated over
            hti->slot += 1; // increment the slot field of the iterator by one
            return hti->table
                ->slots[hti->slot
                        - 1]; // return the pointer to the next valid entry in the hash table
        }
        hti->slot += 1; // increment the slot field of the iterator by one
    }
    return NULL;
}
