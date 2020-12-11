/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Marta Higuera and Miguel Blas
 * Version: 2.0
 * Fecha: 21-09-2020
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "permutations.h"


/***************************************************/
/* Function: random_num Date: 21-09-2020           */
/* Authors: Marta Higuera and Miguel Blas          */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/* or ERR in case of error                         */                           
/***************************************************/

int random_num(int inf, int sup) {

  int rand_num=0;

  if(inf < 0 || sup < inf){
    return ERR;
  }

  rand_num = inf + (int)(rand() / (float) RAND_MAX * (sup-inf+1));

  return rand_num;

}


/*private function declaration*/
void swap (int *numb1, int *numb2);


/***************************************************/
/* Function: swap       Date: 21-09-2020           */
/* Authors: Marta Higuera and Miguel Blas          */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int *numb1: pointer to first number             */
/* int *numb2: pointer to second number            */
/***************************************************/

void swap (int *numb1, int *numb2){

  int aux;

  if(numb1 == NULL || numb2 == NULL){
    return;
  }

  aux = *numb1;
  *numb1 = *numb2;
  *numb2 = aux;

}


/***************************************************/
/* Function: generate_perm Date: 21-09-2020        */
/* Authors: Marta Higuera and Miguel Blas          */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int N: number of elements in the permutation    */
/* Output:                                         */
/* int *gen_perm: pointer to integer array         */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/

int* generate_perm(int N) {
  
  int i=0;
  int* gen_perm=NULL;

  if(N < 1){
    return NULL;
  }

  gen_perm = (int*)calloc((N),sizeof(gen_perm[0]));
  if(gen_perm == NULL){
    return NULL;
  }

  for (i=0; i<N; i++){
    gen_perm[i] = i+1;
  }

  for (i=0; i<N; i++){
    swap(&gen_perm[i], &gen_perm[random_num(i,N-1)]);
  }

  return gen_perm;

}


/***************************************************/
/* Function: generate_permutations Date: 28-09-2020*/
/* Authors: Marta Higuera and Miguel Blas          */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**gen:Array of pointers to integer that point*/
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/

int** generate_permutations(int n_perms, int N){

  int **gen = NULL;
  int i, j;

  if (n_perms < 1 || N < 1){
    return NULL;
  }

  gen = (int**)malloc(n_perms*sizeof(gen[0]));
  if (gen == NULL){
    return NULL;
  }

  for (i = 0; i<n_perms; i++){
  
    gen[i] = generate_perm(N);

    if(gen[i] == NULL){
      
      for(j=0; j<i; j++){
        free(gen[j]);
      }
      free(gen);
      return NULL;
      
    }
  
  }

  return gen;

}
