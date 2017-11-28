/********************************************************************\
* Laboratory Exercise COMP 7300/06
* Author: Christian Kauten
* Date  : November 30, 2017
* File  : exp3.c  for Lab3
\*******************************************************************/


/********************************************************************\
*                    Global system headers                           *
\********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <pthread.h>

/******************************************************************\
*                  Global data types                               *
\******************************************************************/
typedef double          Timestamp;
typedef double          Period;

// parameters for multithreading applications
struct threadParams {
    int i;
    int j;
    int dimension;
};

/**********************************************************************\
*                      Global definitions                              *
\**********************************************************************/
#define DIMENSION        40000
#define PRINTDIM         7 // Dimension of matrix to display
#define NUMBER_TESTS     7
#define BLOCK_SIZE       625
/*!
The threading exponent. 2^THREAD_EXP threads are used.
For tux machines THREAD_EXP = 4 (16 cores)
For laptops THREAD_EXP = 2 (4 cores)
*/
#define THREAD_EXP       4 // 2^THREAD_EXP threads are used
/*!
The number of threads determined by the threading exponent
*/
#define NTHREADS         1 << THREAD_EXP
/**********************************************************************\
*                      Global data                                     *
\**********************************************************************/
Timestamp StartTime;
double    Matrix[DIMENSION][DIMENSION];
Period    Max, Min, Avg;
unsigned int MaxIndex, MinIndex;
// a value used in the sequence calculation of columnwise matrix
int COLUMNWISE_TN = 2 * (DIMENSION - 4) + 9;
/**********************************************************************\
*                        Function prototypes                           *
\**********************************************************************/
Timestamp Now();
int rowwise_nodes(int i);
double rowwise_entry(int i, int j);
int columnwise_nodes(int j);
double columnwise_entry(int i, int j);
void initialize_rowwise();
void initialize_rowwise_recursive(int i, int j, int dimension, int blocksize);
void thread_initialize_rowwise();
void initialize_columnwise();
void initialize_columnwise_recursive(int i, int j, int dimension, int blocksize);
void thread_initialize_columnwise();
void displayUpperQuadrant(unsigned dimension);
void printMatrix(unsigned dimension);
void swap(double *a, double *b);
void transpose();
void recursive_transpose(int i, int j, int dimension, int blocksize);
void thread_transpose();
void initializeAndTranspose();

int main(){
  int choice;
  Timestamp tStart;
  Period testTime;
  unsigned int i, j, nbreTests;

  tStart = Now();

  nbreTests = NUMBER_TESTS;

  Min    = 10000.00;
  Max    = 0.00;
  Avg    = 0.00;

  // display a message and run the test
  printf("Be patient! Initializing and Transposing............\n\n");
  for (j = 1; j <= nbreTests; j++) {
    // Record the starting time before the test begins
    tStart = Now();
    // Initialize a matrix and perform the transpose
    initializeAndTranspose();
    // Calculate the total time as the difference of now and the start time
    testTime = Now() - tStart;
    // if the time is greater than the max time, record it
    if (testTime > Max) {
      Max = testTime;
      MaxIndex = j;
    }
    // if the time is less than the min time, record it
    if (testTime < Min) {
      Min = testTime;
      MinIndex = j;
    }
    // increment the sum of times for the avg
    Avg += testTime;
    // print a status update to the console about the test
    printf("%3d: Init and Transpose Max[%2d]=%7.3f Min[%2d]=%7.3f Avg=%7.3f\n", j, MaxIndex, Max, MinIndex, Min, Avg / j);
    // display the upper portion of the matrix to ensure correctness of the
    // algorithms
    printMatrix(PRINTDIM);
  }
}



/*********************************************************************\
 * Input    : None                                                    *
 * Output   : Returns the current system time                         *
\*********************************************************************/
Timestamp Now(){
  struct timeval tv_CurrentTime;
  gettimeofday(&tv_CurrentTime,NULL);
  return( (Timestamp) tv_CurrentTime.tv_sec + (Timestamp) tv_CurrentTime.tv_usec / 1000000.0-StartTime);
}

/*!
 * Return the number of nodes in a columnwise matrix.
 * @param  j the column index
 * @param  n the dimension of the matrix
 */
int columnwise_nodes(int j) {
  return (1.0 / 2.0) * (-(j*j) + COLUMNWISE_TN*j - 2.0);
}

/*!
 * Return the columnwise entry for an i,j pairing.
 * mathed out using the series of smaller matrices and WolframAlpha
 * @param  i the row index
 * @param  j the column index
 */
double columnwise_entry(int i, int j) {
  if (i < j) {
    return 1;
  }
  return columnwise_nodes(j + 1) - (DIMENSION - i - 1);
}

/*!
 * Initialize the matrix columnwise.
 */
void initialize_columnwise() {
  int i,j;
  double x = 0.0;
  for (j = 0; j < DIMENSION; j++)
    for (i = 0; i < DIMENSION; i++)
      *(*Matrix + i * DIMENSION + j) = columnwise_entry(i, j);
}

/*!
Initialize the matrix columnwise using a recursive solution.
*/
void initialize_columnwise_recursive(int i, int j, int dimension, int blocksize) {
  int dx,dy;
  if (dimension <= blocksize) {
    for (dx = 0; dx < dimension; dx++)
      for (dy = 0; dy < dimension; dy++)
        *(*Matrix + (i + dx) * DIMENSION + j + dy) = columnwise_entry(i + dx, j + dy);
  } else {
    // cut the matrix into four quadrants and recursively initialize
    int midpoint = dimension / 2;
    // recursively call this function with the 4 smaller quadrants
    // the upper left quadrant
    initialize_columnwise_recursive(i, j, midpoint, blocksize);
    // the upper right quadrant
    initialize_columnwise_recursive(i + midpoint, j, midpoint, blocksize);
    // the lower left quadrant
    initialize_columnwise_recursive(i, j + midpoint, midpoint, blocksize);
    // the lower right quadrant
    initialize_columnwise_recursive(i + midpoint, j + midpoint, midpoint, blocksize);
  }
}

/*!
A launcher for starting background threads to initialize columnwise.
*/
void *thread_initialize_columnwise_helper(void *data) {
  struct threadParams *params = data;
  initialize_columnwise_recursive(params->i, params->j, params->dimension, BLOCK_SIZE);
  return 0;
}

/*!
Initialize the matrix columnwise using threads.
*/
void thread_initialize_columnwise() {
  pthread_t threads[NTHREADS];
  int thread_args[NTHREADS];
  int rc, i, j, dimension;

  dimension = DIMENSION / THREAD_EXP;
  struct threadParams params[THREAD_EXP][THREAD_EXP];
  for (j = 0; j < THREAD_EXP; j++) {
    for (i = 0; i < THREAD_EXP; i++) {
      params[i][j].i = i * dimension;
      params[i][j].j = j * dimension;
      params[i][j].dimension = dimension;
      rc = pthread_create(&threads[i + THREAD_EXP * j], NULL, *thread_initialize_columnwise_helper, &params[i][j]);
    }
  }

  // wait for threads to finish
  for (i = 0; i < NTHREADS; i++) {
    rc = pthread_join(threads[i], NULL);
  }
}

/*!
Swap the double values in two memory locations.
Args:
  a: a pointer to the first memory location
  b: a pointer to the second memory location
Returns:
  void
*/
void swap(double *a, double *b) {
 double temp = *a;
 *a = *b;
 *b = temp;
}

/*!
Perform the transpose operator on Matrix.
Args:
  None
Returns:
  void
*/
void transpose() {
  int i,j;
  // the naive baseline solution that performs poorly because it is oblivious
  // of the cache and therefore generates many cache misses
  for (i = 0; i < DIMENSION; i++)
    for (j = i; j < DIMENSION; j++)
      swap(&Matrix[i][j], &Matrix[j][i]);
}

/*!
Transpose the matrix recursively. i.e. cut into squares for better locality
without losing generality by cache blocking directly.
*/
void recursive_transpose(int i, int j, int dimension, int blocksize) {
  int dx,dy;
  if (dimension <= blocksize) {
    if (i < j)
      for (dx = 0; dx < dimension; dx++)
        for (dy = dx + 1; dy < dimension; dy++)
          swap(&Matrix[i + dx][j + dy], &Matrix[j + dy][i + dx]);
    else
      for (dx = 0; dx < dimension; dx++)
        for (dy = dx; dy < dimension; dy++)
          swap(&Matrix[i + dx][j + dy], &Matrix[j + dy][i + dx]);
  } else {
    // cut the matrix into four quadrants and recursively transpose them
    // the midpoint is halfway into the matrix
    int midpoint = dimension / 2;
    // recursively call this function with the 4 smaller quadrants
    // the upper left quadrant
    recursive_transpose(i, j, midpoint, blocksize);
    // the upper right quadrant
    recursive_transpose(i + midpoint, j, midpoint, blocksize);
    // the lower left quadrant
    recursive_transpose(i, j + midpoint, midpoint, blocksize);
    // the lower right quadrant
    recursive_transpose(i + midpoint, j + midpoint, midpoint, blocksize);
  }
}

/*!
A launcher for starting background threads to tranpose the matrix.
*/
void *thread_transpose_helper(void *data) {
  struct threadParams *params = data;
  recursive_transpose(params->i, params->j, params->dimension, BLOCK_SIZE);
  return 0;
}

/*!
Transpose the matrix using threads.
*/
void thread_transpose() {
  pthread_t threads[NTHREADS];
  int thread_args[NTHREADS];
  int rc, i, j, dimension;

  dimension = DIMENSION / THREAD_EXP;
  struct threadParams params[THREAD_EXP][THREAD_EXP];
  for (i = 0; i < THREAD_EXP; i++) {
    for (j = 0; j < THREAD_EXP; j++) {
      params[i][j].i = i * dimension;
      params[i][j].j = j * dimension;
      params[i][j].dimension = dimension;
      rc = pthread_create(&threads[i + THREAD_EXP * j], NULL, *thread_transpose_helper, &params[i][j]);
    }
  }

  // wait for threads to finish
  for (i = 0; i < NTHREADS; i++) {
    rc = pthread_join(threads[i], NULL);
  }
}

/*!
Initialize and transpose an array the most optimal way possible.
*/
void initializeAndTranspose() {
  thread_initialize_columnwise();
  thread_transpose();
}

/*********************************************************************\
* Input    : dimension (first n lines/columns)                        *
* Output   : None                                                     *
* Function : Initialize a matrix columnwise                           *
\*********************************************************************/
void displayUpperQuadrant(unsigned dimension) {
  int i,j;

  printf("\n\n********************************************************\n");
  for (i = 0; i < dimension; i++){
    printf("[");
    for (j = 0; j < dimension; j++){
      printf("%8.1f ",Matrix[i][j]);
    }
    printf("]\n");
  }
  printf("***************************************************************\n\n");
}

/*********************************************************************\
* Input    : dimension (first n lines/columns)                        *
* Output   : None                                                     *
* Function : Initialize a matrix columnwise                           *
\*********************************************************************/
void printMatrix(unsigned dimension) {
  int i,j;

  printf("\n\n*Top Left****************************************************\n");
  for (i = 0; i < dimension; i++) {
    printf("[");
    for (j = 0; j < dimension; j++)
      printf("%12.1f ", Matrix[i][j]);
    printf("]\n");
  }
  printf("***************************************************************\n\n");

  printf("\n\n*Bottom Left*************************************************\n");
  for (i = DIMENSION - dimension; i < DIMENSION; i++) {
    printf("[");
    for (j = 0; j < dimension; j++)
      printf("%12.1f ", Matrix[i][j]);
    printf("]\n");
  }
  printf("***************************************************************\n\n");

  printf("\n\n*Top Right***************************************************\n");
  for (i = 0; i < dimension; i++) {
    printf("[");
    for (j = DIMENSION - dimension; j < DIMENSION; j++)
      printf("%12.1f ", Matrix[i][j]);
    printf("]\n");
  }
  printf("***************************************************************\n\n");

  printf("\n\n*Bottom Right************************************************\n");
  for (i = DIMENSION - dimension; i < DIMENSION; i++) {
    printf("[");
    for (j = DIMENSION - dimension; j < DIMENSION; j++)
      printf("%12.1f ", Matrix[i][j]);
    printf("]\n");
  }
  printf("***************************************************************\n\n");
}
