/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Marta Higuera and Miguel Blas
 * Version: 3.0
 * Fecha: 17-10-2020
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "times.h"
#include "sorting.h"
#include "permutations.h"


/***************************************************/
/* Function: average_sorting_time Date: 06-11-2020 */
/*                                                 */
/* Rutine that calculates the algorithm average run*/
/* time and the max, min and average times it      */
/* does the basic operation                        */
/*                                                 */
/* Input:                                          */
/* pfunc_ordena metodo: pointer to InsertSort      */
/*                      function                   */
/* int n_perms: number of permutations             */
/* int N: number of elements in each permutation   */
/* PTIME_AA ptime: pointer to TIME_AA structure    */
/* Output:                                         */
/* short: OK or ERR in case of error               */  
/***************************************************/

short average_sorting_time(pfunc_ordena metodo, int n_perms, int N, PTIME_AA ptime) {

  int **generate=NULL;
  int i, j;
  int ob=0;
  double count = 0;
  clock_t start, end;
  
  if(metodo == NULL || ptime == NULL || n_perms < 1 || N < 1){
    return ERR;
  }

  generate = generate_permutations(n_perms, N);

  if(generate == NULL){
    return ERR;
  }

  ptime->N = N;
  ptime->n_elems = n_perms;

  ptime->min_ob = INT_MAX;
  ptime->max_ob = 1;

  start = clock();
  
  if(start == (clock_t)-1){
    
    for(i=0; i<n_perms;i++){
      free(generate[i]);      
    }
    
    free(generate);
    
    return ERR;
  }

  for(i=0; i<n_perms; i++){
    
    if((ob = metodo(generate[i], 0, N-1)) == ERR){
    
      for(j=0; j<n_perms;j++){
        free(generate[j]);      
      }
      
      free(generate);
      
      return ERR;
    } 

    if(ptime->min_ob > ob){
      ptime->min_ob = ob;
    }    

    else if(ptime->max_ob < ob){
      ptime->max_ob = ob;
    }

    count = count + ob;

  }

  end = clock();
  if(end == (clock_t)-1){
    
    for(i=0; i<n_perms;i++){
      free(generate[i]);      
    }
    
    free(generate);
    
    return ERR;
  }

  ptime->average_ob = (double)count / (double)n_perms;

  ptime->time = (double)(end-start)*1000000 / (CLOCKS_PER_SEC*n_perms); /*we are changing the time to microseconds*/


  for(i=0; i<n_perms;i++){
      free(generate[i]);      
  }

  free(generate);

  return OK;

}


/***************************************************/
/* Function: generate_sorting_times Date:06-11-2020*/
/*                                                 */
/* Authors: Marta Higuera and Miguel Blas          */
/*                                                 */
/* Rutine which writes in the file the average     */
/* clock time, and the average, minimum and maximum*/
/* number of times that the OB is executed in      */
/* the sorting algorithm method                    */
/*                                                 */
/* Input:                                          */
/* pfunc_ordena metodo: pointer to InsertSort      */
/*                      function                   */
/* char* file: pointer to the file where the output*/
/*             will be printed                     */
/* int num_min: minimum number of times that the OB*/
/*              is executed in the execution of    */
/*              the shorting algorithm method      */
/* int num_max: maximum number of times that the OB*/
/*              is executed in the execution of    */
/*              the shorting algorithm method      */
/* int incr: number of times that the number is    */
/*           incremented in each permutation       */
/* int n_perms: number of permutations that are run*/
/* Output:                                         */
/* short: OK or ERR in case of error               */
/***************************************************/

short generate_sorting_times(pfunc_ordena method, char* file, int num_min, int num_max, int incr, int n_perms) {
  
  PTIME_AA ptime;
  int aux1, N, i;

  if(method == NULL || file == NULL || num_min < 0 || num_max < num_min || incr < 0 || n_perms < 1){
    return ERR;
  }

  aux1 = ((num_max-num_min)/incr)+1;
  if(aux1 < 1){
    return ERR;
  }

  ptime = (PTIME_AA)malloc(aux1*sizeof(ptime[0]));
  if(ptime == NULL){
    return ERR;
  }


  for(i = 0, N = num_min; N <= num_max; i++, N = N+incr){

    if((average_sorting_time(method, n_perms, N, &(ptime[i]))) == ERR){
      free(ptime);
      return ERR;
    }

  }

  if(save_time_table(file, (TIME_AA*)ptime, aux1) == ERR){
    free(ptime);
    return ERR;
  }

  free(ptime);

  return OK;

}


/***************************************************/
/* Function: save_time_table      Date: 16-10-2020 */
/*                                                 */
/* Rutine that saves in a file the data of the     */
/* array of structures TIME_AA                     */
/*                                                 */
/* Input:                                          */
/* char* file: pointer to the file where the output*/
/*             will be printed                     */
/* int n_times: number of array elements           */
/* PTIME_AA ptime: pointer to TIME_AA structure    */
/* Output:                                         */
/* short: OK or ERR in case of error               */  
/***************************************************/

short save_time_table(char* file, PTIME_AA ptime, int n_times) {

  FILE* table = NULL;
  int i;

  if (file == NULL || ptime == NULL || n_times < 0){
    return ERR;
  } 

  table = fopen(file, "w");
  if(!table){
    return ERR;
  }

  for(i = 0; i < n_times; i++){

    fprintf(table, "%d\t%.8f\t%.5f\t%d\t%d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);

  }
  
  if(fclose(table) == -1){
    return ERR;
  }

  return OK;

}


/***************************************************/
/* Function: generate_search_times  Date:05-12-2020*/
/*                                                 */
/* Authors: Marta Higuera and Miguel Blas          */
/*                                                 */
/* Rutine which writes in the file the average     */
/* clock time, and the average, minimum and maximum*/
/* number of times that the OB is executed in      */
/* the searching algorithm methods used            */
/*                                                 */
/* Input:                                          */
/* pfunc_search method: pointer to a search        */
/*                      function                   */
/* pfunc_key_generator: pointer to a function      */
/*                      to generate keys           */
/* int order: indicates of the dictionary is       */
/*            order (1) or unsorted (0)            */
/* char* file: pointer to the file where the output*/
/*             will be printed                     */
/* int num_min: minimum number of times that the OB*/
/*              is executed in the execution of    */
/*              the shorting algorithm method      */
/* int num_max: maximum number of times that the OB*/
/*              is executed in the execution of    */
/*              the shorting algorithm method      */
/* int incr: number of times that the number is    */
/*           incremented in each permutation       */
/* int n_times: number of times each key is        */
/*              searched                           */
/* Output:                                         */
/* short: OK or ERR in case of error               */
/***************************************************/

short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char* file, int num_min, int num_max, int incr, int n_times){
  
  PTIME_AA ptime;
  int aux1, N, i;

  if(method == NULL || file == NULL || num_min < 0 || num_max < num_min || incr < 0 || generator == NULL || n_times < 1 || (order < 0 && order > 1)){
    return ERR;
  }

  aux1 = ((num_max-num_min)/incr)+1;
  if(aux1 < 1){
    return ERR;
  }

  ptime = (PTIME_AA)malloc(aux1*sizeof(ptime[0]));
  if(ptime == NULL){
    return ERR;
  }


  for(i = 0, N = num_min; N <= num_max; i++, N = N+incr){

    if((average_search_time(method, generator, order, N, n_times, &(ptime[i]))) == ERR){
      free(ptime);
      return ERR;
    }

  }

  if(save_time_table(file, (TIME_AA*)ptime, aux1) == ERR){
    free(ptime);
    return ERR;
  }

  free(ptime);

  return OK;

}


/***************************************************/
/* Function: average_search_time Date: 05-12-2020  */
/*                                                 */
/* Rutine that calculates the algorithm average run*/
/* time and the max, min and average times it      */
/* does the basic operation                        */
/*                                                 */
/* Input:                                          */
/* pfunc_search method: pointer to a searching     */
/*                      function                   */
/* pfunc_key_generator: pointer to a function      */
/*                      to generate keys           */
/* int order: indicates of the dictionary is       */
/*            order (1) or unsorted (0)            */
/* int N: size of the dictionary                   */
/* int n_times: number of times each key is        */
/*              searched                           */
/* PTIME_AA ptime: pointer to TIME_AA structure    */
/* Output:                                         */
/* short: OK or ERR in case of error               */  
/***************************************************/

short average_search_time(pfunc_search method, pfunc_key_generator generator, int order, int N, int n_times, PTIME_AA ptime){

  int *generate=NULL;
  int i=0;
  int ob=0, ppos;
  int *keys = NULL;
  double count = 0;
  clock_t start, end;
  PDICT pdict = NULL;
  
  if(method == NULL || ptime == NULL || generator == NULL || n_times < 1 || N < 1 || (order < 0 && order > 1)){
    return ERR;
  }

  ptime->N = N;
  ptime->n_elems = N*n_times;

  ptime->min_ob = INT_MAX;
  ptime->max_ob = 1;

  ppos = NOT_FOUND;

  pdict = init_dictionary(N, order);
  if(pdict == NULL){
    return ERR;
  }

  generate = generate_perm(N);
  if(generate == NULL){
    free_dictionary(pdict);
    return ERR;
  }

  if((massive_insertion_dictionary(pdict, generate, N)) == ERR){
    free_dictionary(pdict);
    free(generate);
    return ERR;    
  }

  keys = (int*)malloc((N*n_times)*sizeof(keys[0]));
  if(keys == NULL){
    free_dictionary(pdict);
    free(generate);
    return ERR; 
  }

  generator(keys, N*n_times, N);

  start = clock();
  if(start == (clock_t)-1){
    free_dictionary(pdict);
    free(generate);
    free(keys);
    return ERR; 
  }

  for(i=0; i<N*n_times; i++){
    
    if((ob = search_dictionary(pdict, keys[i], &ppos, method)) == ERR){
      free_dictionary(pdict);
      free(generate);
      free(keys);
      return ERR; 
    } 

    if(ptime->min_ob > ob){
      ptime->min_ob = ob;
    }    

    else if(ptime->max_ob < ob){
      ptime->max_ob = ob;
    }

    count = count + ob;

  }

  end = clock();
  if(end == (clock_t)-1){
    free_dictionary(pdict);
    free(generate);
    free(keys);
    return ERR; 
  }

  ptime->average_ob = (double)count / (double)(N*n_times);

  ptime->time = (double)(end-start)*1000000 / (N*n_times) / CLOCKS_PER_SEC; /*we are changing the time to microseconds*/


  free_dictionary(pdict);
  free(generate);
  free(keys);
  
  return OK; 

}
