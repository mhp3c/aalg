/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Marta Higuera and Miguel Blas
 * Version: 1.0
 * Date: 23-11-2020
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max){
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max){
  
  int i;

  for(i = 0; i < n_keys; i++) {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}


PDICT init_dictionary (int size, char order){

  PDICT dictionary = NULL;

  if(size<1){
    return NULL;
  }

  dictionary = (PDICT)malloc((size+1)*sizeof(dictionary[0]));
  if (dictionary == NULL){
    return NULL;
  }

  dictionary->size = size;
  dictionary->order = order;
  dictionary->n_data = 0;

  dictionary->table = (int*)malloc((dictionary->size+1)*sizeof(dictionary->table[0]));
  if(dictionary->table == NULL){
    return NULL;
  }

  return dictionary;

}


void free_dictionary(PDICT pdict){
	
  free(pdict->table);
  free(pdict);

}


int insert_dictionary(PDICT pdict, int key){
	
  int A, j, count = 0;

  if (pdict == NULL){
    return ERR;
  }

  if(pdict->size == pdict->n_data){
    return 0;
  }

  if(pdict->order == NOT_SORTED){
    pdict->table[pdict->n_data] = key;
  }

  if(pdict->order == SORTED){ 

    pdict->table[pdict->n_data] = key; /*insert the element in the last position and then order*/

    A = pdict->table[pdict->n_data];
    j = pdict->n_data-1;

    while(j>=0 && ++count && pdict->table[j]>A){
      pdict->table[j+1] = pdict->table[j];
      j--;
    }

    pdict->table[j+1] = A;

  }

  pdict->n_data++;

  return count;

}


int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys){
	
  int i = 0;
  int count = 0;

  if(pdict == NULL || keys == NULL){
    return ERR;
  }

  for(i = 0; i<n_keys; i++){
    if((count = insert_dictionary(pdict, keys[i])) == ERR){
      return ERR;
    }
  }


  return count;

}


int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method){
	
  if(pdict == NULL || ppos == NULL || method == NULL){
    return ERR;
  }

  return method(pdict->table, 0, pdict->n_data-1, key, ppos);

}


/* Search functions of the Dictionary ADT */
int bin_search(int *table, int F, int L, int key, int *ppos){

  int m = 0, result, count = 0;

  assert(F<=L);
  if (table == NULL || ppos == NULL){
    return ERR;
  }

  while(F <= L){

    ++count;

    m = (F+L)/2;
    result = table[m] - key;

    if(result == 0){
      *ppos = m;
      return count;
    }

    if(result < 0){
      F = m+1;
    }
    else {
      L = m-1;
    }

  }

  *ppos = NOT_FOUND;

  return count;

}


int lin_search(int *table,int F,int L,int key, int *ppos){

  int i, count = 0;

  assert(F<=L);
  if(table == NULL || ppos == NULL){
    return ERR;
  }

  for(i = F; i <= L; i++){

    count++;
    if(table[i] == key){

      *ppos = i;
      return count;

    }
  }

  *ppos = NOT_FOUND;
  return count;
	
}


/***************************************************/
/* Function: swap2       Date: 21-09-2020           */
/* Authors: Marta Higuera and Miguel Blas          */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int *numb1: pointer to first number             */
/* int *numb2: pointer to second number            */
/***************************************************/
void swap2 (int *numb1, int *numb2){

  int aux;

  if(numb1 == NULL || numb2 == NULL){
    return;
  }

  aux = *numb1;
  *numb1 = *numb2;
  *numb2 = aux;

}


int lin_auto_search(int *table,int F,int L,int key, int *ppos){

  int i, count = 0;

  assert(F<L);
  if(table == NULL || ppos == NULL){
    return ERR;
  }

  for(i = F; i <= L; i++){

    count++;
    if(table[i] == key){

      *(int*)ppos = i;

      if(i>0){
        swap2(&table[i], &table[i-1]);
      }

      return count;
    }
  }

  *(int*)ppos = NOT_FOUND;
  
  return count;

}


