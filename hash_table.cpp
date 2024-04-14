// ============================================
// The HashTable class file
//
// Copyright 2022 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


/*
Student Name: Raj Patel
Date: 11/04/2022
=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
    e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
    e.g. "_HashTable", "_HashTableEntry"

    Recall that in C, we have to type "struct" together with the name of the struct
    in order to initialize a new variable. To avoid this, in hash_table.h
    we use typedef to provide new "nicknames" for "struct _HashTable" and
    "struct _HashTableEntry". As a result, we can create new struct variables
    by just using:
        - "HashTable myNewTable;"
    or
        - "HashTableEntry myNewHashTableEntry;"

    The preceding underscore "_" simply provides a distinction between the names
    of the actual struct definition and the "nicknames" that we use to initialize
    new structs.
    [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
    the first letter is lower-case.
    e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
        It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
    as a distinction between function local variables and struct members.
    e.g. "num_buckets" is a member of "HashTable".
*/


/****************************************************************************
 * Include the Public Interface
 *
 * By including the public interface at the top of the file, the compiler can
 * enforce that the function declarations in the the header are not in
 * conflict with the definitions in the file. This is not a guarantee of
 * correctness, but it is better than nothing!
 ***************************************************************************/
#include "hash_table.h"

/****************************************************************************
 * Include other private dependencies
 *
 * These other modules are used in the implementation of the hash table module,
 * but are not required by users of the hash table.
 ***************************************************************************/
#include <stdlib.h> // For malloc and free
#include <stdio.h>  // For printf

/****************************************************************************
 * Hidden Definitions
 *
 * These definitions are not available outside of this file. However, because
 * the are forward declared in hash_table.h, the type names are
 * available everywhere and user code can hold pointers to these structs.
 ***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable
{
    /** The array of pointers to the head of a singly linked list, whose nodes
        are HashTableEntry objects */
    HashTableEntry **buckets;

    /** The hash function pointer */
    HashFunction hash;

    /** The number of buckets in the hash table */
    unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry
{
    /** The key for the hash table entry */
    unsigned int key;

    /** The value associated with this hash table entry */
    void *value;

    /**
     * A pointer pointing to the next hash table entry
     * NULL means there is no next entry (i.e. this is the tail)
     */
    HashTableEntry *next;
};

/****************************************************************************
 * Private Functions
 *
 * These functions are not available outside of this file, since they are not
 * declared in hash_table.h.
 ***************************************************************************/
/**
 * createHashTableEntry
 *
 * Helper function that creates a hash table entry by allocating memory for it on
 * the heap. It initializes the entry with key and value, initialize pointer to
 * the next entry as NULL, and return the pointer to this hash table entry.
 *
 * @param key The key corresponds to the hash table entry
 * @param value The value stored in the hash table entry
 * @return The pointer to the hash table entry
 */
static HashTableEntry *createHashTableEntry(unsigned int key, void *value)
{
    HashTableEntry* NewHashTableEntry= (HashTableEntry*) malloc(sizeof(HashTableEntry)); // initialize the HashTableEntry
    NewHashTableEntry->key = key;   // set key
    NewHashTableEntry->value= value;  // set value
    NewHashTableEntry->next=NULL; // set next
    return NewHashTableEntry;  // return HashTableEntry
}

/**
 * findItem
 *
 * Helper function that checks whether there exists the hash table entry that
 * contains a specific key.
 *
 * @param hashTable The pointer to the hash table.
 * @param key The key corresponds to the hash table entry
 * @return The pointer to the hash table entry, or NULL if key does not exist
 */
static HashTableEntry *findItem(HashTable *hashTable, unsigned int key)
{
	HashTableEntry* result= NULL;  // initialize result
    int n = hashTable->hash(key);  // find which bucket
    HashTableEntry* findHashTableEntry= hashTable->buckets[n];  // get the HashTableEntry of this index
    while(findHashTableEntry != NULL && findHashTableEntry->key != key)
        // if it doesn't match
        findHashTableEntry = findHashTableEntry->next;  // go to next one
    result= findHashTableEntry; // get the result
    return result;
}

/****************************************************************************
 * Public Interface Functions
 *
 * These functions implement the public interface as specified in the header
 * file, and make use of the private functions and hidden definitions in the
 * above sections.
 ****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable *createHashTable(HashFunction hashFunction, unsigned int numBuckets)
{
    // The hash table has to contain at least one bucket. Exit gracefully if
    // this condition is not met.
    if (numBuckets == 0)
    {
        printf("Hash table has to contain at least 1 bucket...\n");
        exit(1);
    }

    // Allocate memory for the new HashTable struct on heap.
    HashTable *newTable = (HashTable *)malloc(sizeof(HashTable));

    // Initialize the components of the new HashTable struct.
    newTable->hash = hashFunction;
    newTable->num_buckets = numBuckets;
    newTable->buckets = (HashTableEntry **)malloc(numBuckets * sizeof(HashTableEntry *));

    // As the new buckets are empty, init each bucket as NULL.
    unsigned int i;
    for (i = 0; i < numBuckets; ++i)
    {
        newTable->buckets[i] = NULL;
    }

    // Return the new HashTable struct.
    return newTable;
}

void destroyHashTable(HashTable *hashTable)
{
    for(int i = 0; i < hashTable->num_buckets; i++){ //loop through all buckets
    HashTableEntry* currentBucket = hashTable->buckets[i]; //currentBucket initialized
	    while(currentBucket) { //if there's a value
	      HashTableEntry* temp = currentBucket; //store currentBucket in temp
	      currentBucket = currentBucket->next; //update currentBucket
	      free(temp->value);  //destroy temp's value
	      free(temp); //destroy temp
	    }
    }
    free(hashTable->buckets); //destroy all hash buckets
    free(hashTable); //destroy hash table itself
}

void *insertItem(HashTable *hashTable, unsigned int key, void *value)
{
    HashTableEntry* newHashTableEntry = createHashTableEntry(key,value); //create the HashtableEntry to insert
    HashTableEntry* findHashTableEntry = findItem(hashTable, key); // use findItem to see if the entry already exists
    if (findHashTableEntry==NULL) {
        // if the key does not exist
        HashTableEntry * current= hashTable-> buckets[hashTable->hash(key)]; //find the buckets place
        if (current== NULL) {
            // if the buckets is empty
            hashTable-> buckets[hashTable->hash(key)] = newHashTableEntry;
            return NULL;
        }

        while (current->next!= NULL) {
            current=current->next;
            // find the position to insert
        }
        current->next = newHashTableEntry; // insert the HashTableEntry
        return NULL;
    } else {
        // if the key exists
        void* old_value = findHashTableEntry-> value;  // get the entry's current value that is stored in the entry
        findHashTableEntry->value = value; // change the value to the new value
        free(newHashTableEntry); // free the new HashTableEntry created
        return old_value; // return the old value
    }

}

void *getItem(HashTable *hashTable, unsigned int key)
{
    HashTableEntry* findHashTableEntry = findItem(hashTable, key); //check if HashTableEntry exists
    if (findHashTableEntry == NULL) {
        return NULL;  // key does not exist
    } else {
        void* value= findHashTableEntry-> value; // if it exists, return it's value
        return value;
    }

}

void *removeItem(HashTable *hashTable, unsigned int key)
{
    int bucket = hashTable->hash(key);  // find the bucket
    HashTableEntry* findHashTableEntry = hashTable->buckets[bucket];  // get the first HashTableEntry of this bucket
    void* value = NULL; //initialize return value to NULL
    if (findHashTableEntry==NULL) {
        return NULL; // HashTableEntry does not exist
    }
    if (findHashTableEntry->key==key) {
         // The item is the first item
        HashTableEntry* temp=findHashTableEntry;   // temporarily story this HashTableEntry
        hashTable->buckets[bucket]=findHashTableEntry->next;  // change head pointer to point to the next entry
        value= temp->value;  // get the value of the entry that is to be removed
        free(temp);  // free the HashTableEntry that was removed
    } else {
        while(findHashTableEntry->next != NULL){
           //Check the next entry
            if (findHashTableEntry->next->key==key ){
                // key found
                HashTableEntry* temp=findHashTableEntry->next; //temporarily store current HashTableEntry
                findHashTableEntry->next=findHashTableEntry->next->next;  // splice out current entry
                value= temp->value; // get the value of the entry to be removed
                free(temp);  // free the HashtableEntry that was removed
                return value;
            }
            findHashTableEntry =findHashTableEntry->next;   // move to next entry
        }
    }
    return value;

}

void deleteItem(HashTable *hashTable, unsigned int key)
{
    int bucket = hashTable->hash(key);  // find the bucket
    HashTableEntry* findHashTableEntry = findItem(hashTable, key);
    if (findHashTableEntry != NULL) {
        findHashTableEntry = hashTable->buckets[bucket];

	    if (findHashTableEntry->key==key){
	        //if it is first item
	        HashTableEntry* temp=findHashTableEntry;   // temporarily hold HashTableEntry
	        hashTable->buckets[bucket]=findHashTableEntry->next;  // change head pointer to point to the next entry
	        free(temp->value); // free the value of the HashtableEntry
	        free(temp);   // free the HashTableEntry
	    } else {
	        while(findHashTableEntry->next != NULL){
	            // check the next item
	            if (findHashTableEntry->next->key==key){
	                HashTableEntry* temp=findHashTableEntry->next; // make the temp of the HashTableEntry
	                findHashTableEntry->next=findHashTableEntry->next->next;  // splice out current entry
	                free(temp->value); //free the value of the HashtableEntry
	                free(temp);   // free the HashtableEntry
	                break;
	            }
	            findHashTableEntry =findHashTableEntry->next;  // move to next entry
	        }
	    }
    }
}
