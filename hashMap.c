#include <stdlib.h>
#include "assert.h"
#include "hashMap.h"

int stringHash1(char * str)
{
    int i;
    int r = 0;
    for (i = 0; str[i] != '\0'; i++)
        r += str[i];
    return r;
}

int stringHash2(char * str)
{
    int i;
    int r = 0;
    for (i = 0; str[i] != '\0'; i++)
        r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
    return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
    int index;
    
    if(ht == NULL)
        return;
    ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
    ht->tableSize = tableSize;
    ht->count = 0;
    for(index = 0; index < tableSize; index++)
        ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{
    /*write this*/
	int i;
	hashLink* bucket;
	hashLink* next;

	if (ht == NULL){
	return;
	}
	for(i=0; i<ht->tableSize; i++){
		bucket = ht->table[i];
		while(bucket!=NULL){
			next = bucket->next;
			free(bucket);
			bucket = next;
		}

	}
	free(ht->table);
	free(ht);

}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{ 
    /*write this*/

	hashLink* bucket;
	if (containsKey(ht,k) == 0){
		bucket = (hashLink*) malloc (sizeof(hashLink)); 
		assert(bucket);
		bucket->key = k;
		bucket->next= ht->table[v]; 
		ht->table[v] = bucket;
		ht->tableSize++;

	}else{

		bucket->value = v;
		ht->tableSize++;
	}
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{
    /*write this*/
	int i;
	hashLink* bucket;
	for(i=0; i<ht->tableSize;i++){
		for(bucket = ht->table[i]; bucket != NULL; bucket = bucket->next){
			return &(bucket->value);
		}
	}
}

int containsKey (struct hashMap * ht, KeyType k)
{
    /*write this*/
	hashLink* bucket;

	while (bucket != NULL){
		if (k==bucket->key)
			return 1;
			bucket = bucket->next;
	}
	return 0;
}

void removeKey (struct hashMap * ht, KeyType k)
{
    /*write this*/
	hashLink* bucket;
	hashLink* bucketPrev;
	int i;
	int hashVal = stringHash1(k);
	int hashIndex = (int) (labs(hashVal) % ht->tableSize);
	if (containsKey(ht,k)){

		bucket = ht->table[hashIndex];
		bucketPrev = ht->table[hashIndex];

		while(bucket != NULL){

			if (bucket->key = k){
				if(bucket == ht->table[hashIndex])
					ht->table[hashIndex]= bucket->next;
				else bucketPrev->next = bucket->next;
					free(bucket);
					ht->tableSize--;
					bucket = NULL;
				}else{
				bucketPrev->next = bucket->next;
		}
	}
	}
}

int size (struct hashMap *ht)
{
    /*write this*/
	if (ht != NULL){
		return ht->tableSize;
	}
}

int capacity(struct hashMap *ht)
{
	hashLink* bucket;
	int count=0;
	while (ht != NULL){
		while (bucket != NULL){
			count++;
			bucket = bucket->next;
		}
	}
	return count;
}

int emptyBuckets(struct hashMap *ht)
{
    /*write this*/
    	hashLink* bucket;
	int count=0;
	while (ht != NULL){
		while (bucket == NULL){
			count++;
			bucket = bucket->next;
		}
	}
	return count;
}

float tableLoad(struct hashMap *ht)
{
    /*write this*/
    return size(ht)/capacity(ht);
}
