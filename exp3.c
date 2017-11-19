/********************************************************************\
* Laboratory Exercise COMP 7300/06
* Author: Christian Kauten
* Date  : November 30, 2017
* File  : exp2.c  for Lab3
\*******************************************************************/


/********************************************************************\
*                    Global system headers                           *
\********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>

/******************************************************************\
*                  Global data types                               *
\******************************************************************/
typedef double          Timestamp;
typedef double          Period;

/**********************************************************************\
*                      Global definitions                              *
\**********************************************************************/
#define DIMENSION        14
#define PRINTDIM         14//7 // Dimension of matrix to display
#define NUMBER_TESTS     1//7

/**********************************************************************\
*                      Global data                              *
\**********************************************************************/
Timestamp StartTime;
double    Matrix[DIMENSION][DIMENSION];
Period    Max, Min, Avg;
unsigned int MaxIndex, MinIndex;
/**********************************************************************\
*                        Function prototypes                           *
\**********************************************************************/
Timestamp Now();
void initialize_rowwise();
void initialize_columnwise();
void displayUpperQuadrant(unsigned dimension);
void swap(double *a, double *b);
void swap_matrices(int i_a, int j_a, int i_b, int j_b, int dimension);
void transpose();
void initializeAndTranspose();
void recursive_transpose(int i, int j, int dimension);

int main(){
  int choice;
  Timestamp tStart;
  Period testTime;
  unsigned int i, j, nbreTests;

  //
  // MARK: Global Initialization
  //

  tStart = Now();

  nbreTests = NUMBER_TESTS;

  Min    = 10000.00;
  Max    = 0.00;
  Avg    = 0.00;

  //
  // MARK: Test Suite
  //

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
    // displayUpperQuadrant(PRINTDIM);
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


/*********************************************************************\
* Input    : None                                                     *
* Output   : None                                                     *
* Function : Initialize a matrix rowwise                              *
\*********************************************************************/
void initialize_rowwise() {
  int i,j;
  double x = 0.0;
  #pragma omp parallel for
  for (i = 0; i < DIMENSION; i++)
    for (j = 0; j < DIMENSION; j++)
      if (i >= j)
         *(*Matrix + i * DIMENSION + j) = x++;
      else
         *(*Matrix + i * DIMENSION + j) = 1.0;
}


/*********************************************************************\
* Input    : None                                                     *
* Output   : None                                                     *
* Function : Initialize a matrix columnwise                           *
\*********************************************************************/
void initialize_columnwise() {
  int i,j;
  double x = 0.0;
  #pragma omp parallel for
  for (j = 0; j < DIMENSION; j++)
    for (i = 0; i < DIMENSION; i++)
      if (i >= j)
        *(*Matrix + i * DIMENSION + j) = x++;
      else
        *(*Matrix + i * DIMENSION + j) = 1.0;
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
  #pragma omp parallel for
  for (i = 0; i < DIMENSION; i++)
    for (j = i; j < DIMENSION; j++)
      swap(&Matrix[i][j], &Matrix[j][i]);
}

/*!
Swap the values in two square submatrices.
Args:
  i_a: the i value of the first matrix
  j_a: the j value of the first matrix
  i_b: the i value of the second matrix
  j_b: the j value of the second matrix
  dimension: the size of the matrix
*/
void swap_matrices(int i_a, int j_a, int i_b, int j_b, int dimension) {
  int i, j;
  // iterate over the dimension and swap the values by i,j pairs
  #pragma omp parallel for
  for (i = 0; i < dimension; i++)
    for(j = 0; j < dimension; j++)
      swap(&Matrix[i_a + i][j_a + j], &Matrix[i_b + i][j_b + j]);
}

/*!
Perform a cache oblivious transpose that utilizes the stack to prevent
excessive cache mits generated by a naive iterative solution.
Args:
  i: the current i dimension in the matrix (row)
  j: the current j dimension in the matric (row)
  dimension: the current dimension of the matric (assumes SQUARE)
Returns:
  void
*/
void recursive_transpose(int i, int j, int dimension) {
  int dx,dy;
  printf("%i ", i);
  printf("%i ", j);
  printf("%i ", dimension);
  printf("\n");
  if (dimension % 2 == 1) {
    // #pragma omp parallel for
    // for (dx = i; dx < i + dimension; dx++)
    //   for (dy = j + dx; dy < j + dimension; dy++)
    //     swap(&Matrix[i + dx][j + dy], &Matrix[j + dy][i + dx]);
    for (dx = 0; dx < dimension; dx++)
      for (dy = dx; dy < dimension; dy++)
        if (i == j)
          swap(&Matrix[i + dx][j + dy], &Matrix[j + dy][i + dx]);
        else
          swap(&Matrix[i + dx][j + dy], &Matrix[dimension - j + dy][dimension - i + dx]);
  } else {
    // cut the matrix into four quadrants and recursively transpose them
    // the midpoint is halfway into the matrix
    int midpoint = dimension / 2;
    // recursively call this function with the 4 smaller quadrants
    // the upper left quadrant
    recursive_transpose(i, j, midpoint);
    // the upper right quadrant
    recursive_transpose(i + midpoint, j, midpoint);
    // the lower left quadrant
    recursive_transpose(i, j + midpoint, midpoint);
    // the lower right quadrant
    recursive_transpose(i + midpoint, j + midpoint, midpoint);
    // swap upper right with the bottom left
    swap_matrices(i + midpoint, j, i, j + midpoint, midpoint);
  }
}

/*!
Initialize and transpose an array the most optimal way possible.
*/
void initializeAndTranspose() {

  initialize_rowwise();
  transpose();
  displayUpperQuadrant(DIMENSION);

  initialize_rowwise();
  recursive_transpose(0, 0, DIMENSION);
  displayUpperQuadrant(DIMENSION);

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
