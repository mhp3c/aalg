/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Marta Higuera and Miguel Blas
 * Version: 3.0
 * Fecha: 26-10-2020
 *
 */


#include "sorting.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/*private function declaration*/
void swap1 (int *numb1, int *numb2);

int merge(int* table, int ip, int iu, int imiddle);

int split(int* table, int ip, int iu,int *pos);

int median(int *table, int ip, int iu,int *pos);


/***************************************************/
/* Function: InsertSort    Date: 05-10-2020        */
/*                                                 */
/* Rutine that sorts the elements of an array      */
/* in ascending order                              */
/*                                                 */
/* Input:                                          */
/* int* table: table to sort                       */
/* int ip: minor limit number                      */
/* int iu: upper limit number                      */
/* Output:                                         */
/* int count: number of KC (basic operation)       */
/* or ERR in case of error                         */  
/***************************************************/

int InsertSort(int* table, int ip, int iu){

  int i = 0, j = 0;
  int A, count=0;

  if (table == NULL || ip<0 || iu<ip){
    return ERR;
  }

  for (i = ip+1; i<=iu; i++){

    A = table[i];
    j = i-1;
    
    while(j >= ip && ++count && table[j]>A){

      table[j+1] = table[j];
      j--;
      
    }

    table[j+1] = A;

  }

  return count;

}


/***************************************************/
/* Function: InsertSortInv    Date: 05-10-2020     */
/*                                                 */
/* Rutine that sorts the elements of an array      */
/* in descending order                             */
/*                                                 */
/* Input:                                          */
/* int* table: table to sort                       */
/* int ip: minor limit number                      */
/* int iu: upper limit number                      */
/* Output:                                         */
/* int count: number of KC (basic operation)       */
/* or ERR in case of error                         */
/***************************************************/

int InsertSortInv(int* table, int ip, int iu){

  int i=0, j=0;
  int A, count=0;

  if (table == NULL || ip<0 || iu<ip){
    return ERR; 
  }

  for (i = ip+1; i<=iu; i++){

    A = table[i];
    j = i-1;
    
    while(j >= ip && ++count && table[j] < A){

      table[j+1] = table[j];
      j--;
    
    }

    table[j+1] = A;

  }
  
  return count;
  
}



/***************************************************/
/* Function: mergesort    Date: 04-11-2020         */
/*                                                 */
/* Rutine that divides the number of elements of   */
/* an array and calls merge to sort the elements   */
/* in descending order                             */
/*                                                 */
/* Input:                                          */
/* int* table: table to sort                       */
/* int ip: minor limit number                      */
/* int iu: upper limit number                      */
/* Output:                                         */
/* int count: number of BO (basic operation)       */
/* or ERR in case of error                         */
/***************************************************/

int mergesort(int* table, int ip, int iu){

  int m, count = 0, count1 = 0, count2 = 0;

  assert(ip >= 0);
  assert(ip <= iu);
  if (table == NULL){
    return ERR;
  }

  if (ip == iu){
    
    return 1;

  }

  m = (ip+iu)/2;

  count1 = mergesort(table, ip, m);
  if(count1 == ERR){
    return ERR;
  }

  count2 = mergesort(table, m+1, iu);
  if(count2 == ERR){
    return ERR;
  }

  count = merge(table, ip, iu, m);
  if(count == ERR){
    return ERR;
  }

  return count+count1+count2;

} 


/***************************************************/
/* Function: merge         Date: 04-11-2020        */
/*                                                 */
/* Rutine that sorts the elements of an array      */
/* in ascending order                              */
/*                                                 */
/* Input:                                          */
/* int* table: table to sort                       */
/* int ip: minor limit index                       */
/* int iu: upper limit index                       */
/* int imiddle: middle index of the table          */
/* Output:                                         */
/* int count: number of BO (basic operation)       */
/* or ERR in case of error                         */  
/***************************************************/

int merge(int* table, int ip, int iu, int imiddle){

  int i=0, j=0, k=0;
  int count = 0;
  int* aux = NULL;

  assert(iu >= ip); 
  assert(imiddle >= ip); 
  assert(imiddle <= iu);
  if (table == NULL){
    return ERR;
  }

  aux = (int*)calloc(iu+1,sizeof(aux[0]));
  if(aux == NULL){
    return ERR;
  }

  i = ip;
  j = (imiddle+1);
  k = ip;

  while (i <= imiddle  && j <= iu){

    count += count;

    if (table[i] < table[j]){

      aux[k] = table[i];
      i++;

    }

    else{

      aux[k] = table[j];
      j++;

    }
    k++;
  }

  if (i > imiddle){

    while(j <= iu){

      count += count;
      aux[k] = table[j];
      j++;    
      k++;
    
    }
  }

  else if (j > iu){

    while(i <= imiddle){

      count += count;
      aux[k] = table[i];
      i++;    
      k++;
    
    }
  }  

  for(i=ip; i<=iu; i++){
    
    table[i] = aux[i];

  }

  free(aux);
  
  return count;

}


/***************************************************/
/* Function: swap1       Date: 21-09-2020          */
/* Authors: Marta Higuera and Miguel Blas          */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int *numb1: pointer to first number             */
/* int *numb2: pointer to second number            */
/***************************************************/
void swap1 (int *numb1, int *numb2){

  int aux;

  if(numb1 == NULL || numb2 == NULL){
    return;
  }

  aux = *numb1;
  *numb1 = *numb2;
  *numb2 = aux;

}


/***************************************************/
/* Function: quicksort         Date: 09-11-2020    */
/*                                                 */
/* Function that calls an auxiliary one to divide  */
/* it an array and then recursively call itself    */
/* to sort the array                               */
/*                                                 */
/* Input:                                          */
/* int* table: table to sort                       */
/* int ip: minor limit index                       */
/* int iu: upper limit index                       */
/* Output:                                         */
/* int count: number of BO (basic operation)       */
/* or ERR in case of error                         */  
/***************************************************/

int quicksort(int* table, int ip, int iu){

  int m = table[ip];
  int ret = 0, count1 = 0, count2 = 0;

  assert(iu >= ip); 
  if(table == NULL){
    return ERR;
  }

  if (ip == iu){
    return 1;
  }

  else{
    
    ret += split(table, ip, iu, &m);
    if (ret == ERR){
      return ERR;
    }

    if(ip < (m-1)){
      count1 = quicksort(table, ip, m-1);
      if(count1 == ERR){
        return ERR;
      }
    }

    if((m+1) < iu){
      count2 = quicksort(table, m+1, iu);
      if(count2 == ERR){
        return ERR;
      }      
    }

  }

  return ret+count1+count2;

}


/***************************************************/
/* Function: split         Date: 09-11-2020        */
/*                                                 */
/* Rutine that sorts the elements of an array      */
/* in ascending order according to pivot passed as */
/* argument                                        */
/*                                                 */
/* Input:                                          */
/* int* table: table to sort                       */
/* int ip: minor limit index                       */
/* int iu: upper limit index                       */
/* int *pos: pointer of the position of the pivot  */
/* element in the table                            */
/* Output:                                         */
/* int count: number of BO (basic operation)       */
/* or ERR in case of error                         */  
/***************************************************/

int split(int* table, int ip, int iu, int *pos) {

  int aux=0, i=0, count=0, m=0;

  assert(iu >= ip); 
  if(table == NULL){
    return ERR;
  }
  
  if(pos == NULL){
    return ERR;
  }

  m = median(table, ip, iu, pos);
  if(m == ERR){
    return ERR;
  }

  aux = table[*pos];
  swap1(&table[ip], &table[*pos]);
  *pos = ip;

  for(i = ip+1; i <= iu; i++, ++count){

    if(table[i] < aux){
      
      (*pos)++;      
      swap1(&table[i], &table[*pos]);

    }

  }

  swap1(&table[ip], &table[*pos]);

  return count;

}


/***************************************************/
/* Function: median         Date: 04-11-2020       */
/*                                                 */
/* Rutine that sorts the elements of an array      */
/* in ascending order                              */
/*                                                 */
/* Input:                                          */
/* int* table: table to sort                       */
/* int ip: minor limit index                       */
/* int iu: upper limit index                       */
/* int *pos: pointer to the pivot element          */
/* Output:                                         */
/* int : retuerns a 0 if it was successful or ERR  */
/* in case of error                                */  
/***************************************************/

int median(int *table, int ip, int iu, int *pos){

  assert(iu >= ip); 
  if(table == NULL){
    return ERR;
  }

  if(pos == NULL){
    return ERR;
  }

  *pos = ip;

  return 0;

}


/***************************************************/
/* Function: quicksort_ntr   Date: 09-11-2020      */
/*                                                 */
/* Rutine that sorts the elements of an array      */
/* in ascending order without tail recursion       */
/*                                                 */
/* Input:                                          */
/* int* table: table to sort                       */
/* int ip: minor limit index                       */
/* int iu: upper limit index                       */
/* Output:                                         */
/* int count: number of BO (basic operation)       */
/* or ERR in case of error                         */  
/***************************************************/

int quicksort_ntr(int* table, int ip, int iu){

  int m = table[ip];
  int count = 0, count1=0;

  if (table == NULL){
    return ERR;
  } 

  while(ip < iu){

    count += split(table, ip, iu, &m);
    if (count == ERR){
      return ERR;
    }

    if(ip < (m-1)){
      count1 = quicksort_ntr(table, ip, m-1);
      if(count1 == ERR){
        return ERR;
      }
    }

    if((m+1) < iu){
      ip= m+1;
    }

    return count+count1;

  }

  return ERR;
  
}