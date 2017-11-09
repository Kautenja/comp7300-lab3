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
#define DIMENSION    40000
#define PRINTDIM         7 // Dimension of matrix to display
#define NUMBER_TESTS     7

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
Timestamp   Now();
void InitializeMatrixRowwise();
void InitializeMatrixColumnwise();
void DisplayUpperQuandrant(unsigned dimension);
void swap(double *a, double *b);
void TransposeMatrix();
void InitializeAndTranspose();

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
    InitializeAndTranspose();
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
    DisplayUpperQuandrant(PRINTDIM);
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
void InitializeMatrixRowwise() {
  double x = 0.0;
  #pragma omp parallel for
  for (int i = 0; i < DIMENSION; i++)
    for (int j = 0; j < DIMENSION; j++)
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
void InitializeMatrixColumnwise() {
  double x = 0.0;
  #pragma omp parallel for
  for (int j = 0; j < DIMENSION; j++)
    for (int i = 0; i < DIMENSION; i++)
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
void TransposeMatrix() {
  // the naive baseline solution that performs poorly due to cache oblivious
  #pragma omp parallel for
  for (int i = 0; i < DIMENSION - 2; i++)
    for (int j = i + 1; j < DIMENSION - 1; j++)
      swap(&Matrix[i][j], &Matrix[j][i]);
}

/*!
Initialize and transpose an array the most optimal way possible.
*/
void InitializeAndTranspose() {
  InitializeMatrixRowwise();
  TransposeMatrix();
}

/*********************************************************************\
* Input    : dimension (first n lines/columns)                        *
* Output   : None                                                     *
* Function : Initialize a matrix columnwise                           *
\*********************************************************************/
void      DisplayUpperQuandrant(unsigned dimension){
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
