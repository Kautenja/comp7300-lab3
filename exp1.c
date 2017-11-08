/********************************************************************\
* Laboratory Exercise COMP 7300/06                                   *
* Author: Saad Biaz                                                  *
* Date  : October 25, 2017                                           *
* File  : myInitializeMatrix.c  for Lab3                             *
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
#define ROWWISE          0
#define COLUMNWISE       1

/**********************************************************************\
*                      Global data                              *
\**********************************************************************/
Timestamp StartTime;
double    Matrix[DIMENSION][DIMENSION];
Period    Max[2],Min[2],Avg[2];
unsigned int MaxIndex[2],MinIndex[2];
/**********************************************************************\
*                        Function prototypes                           *
\**********************************************************************/
Timestamp   Now();
void        InitializeMatrixRowwise();
void        InitializeMatrixColumnwise();
void        DisplayUpperQuandrant(unsigned dimension);


int main(){
  int choice;
  Timestamp StartInitialize;
  Period    testTime;
  unsigned int i,j,nbreTests;

  // Global Initialization
  StartTime       = Now();

  nbreTests       = NUMBER_TESTS;
  Max[ROWWISE]    = 0.00;
  Max[COLUMNWISE] = 0.00;

  Min[ROWWISE]    = 10000.00;
  Min[COLUMNWISE] = 10000.00;

  Avg[ROWWISE]    = 0.00;
  Avg[COLUMNWISE] = 0.00;

  // Matrix Initialization
  printf("Be patient! Initializing............\n\n");
  for (j = 1; j <= nbreTests; j++) {
    for (i = ROWWISE; i <= COLUMNWISE; i++) {
      StartInitialize = Now();
      if (i == ROWWISE) {
	        InitializeMatrixRowwise();
      }
      else {
	        InitializeMatrixColumnwise();
      }
      testTime = Now() - StartInitialize;
      if (testTime > Max[i]) {
	        Max[i] = testTime;
	        MaxIndex[i] = j;
      }
      if (testTime < Min[i]) {
          Min[i] = testTime;
	        MinIndex[i] = j;
      }
      Avg[i] += testTime;
    }
    printf("%3d: Rowwise    Max[%2d]=%7.3f Min[%2d]=%7.3f Avg=%7.3f\n",
	   j,MaxIndex[ROWWISE],Max[ROWWISE],MinIndex[ROWWISE],
	   Min[ROWWISE],Avg[ROWWISE]/j);
    printf("     Columnwise Max[%2d]=%7.3f Min[%2d]=%7.3f Avg=%7.3f\n\n",
           MaxIndex[COLUMNWISE],Max[COLUMNWISE],MinIndex[COLUMNWISE],
	   Min[COLUMNWISE],Avg[COLUMNWISE]/j);
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
void      InitializeMatrixRowwise() {
  int i,j;
  double x;
  x = 0.0;
  for (i = 0; i < DIMENSION; i++) {
    for (j = 0; j < DIMENSION; j++) {
      if (i >= j) {
	       // Matrix[i][j] = x;
         *(*Matrix + i * DIMENSION + j) = x;
	       x += 1.0;
      } else {
	       // Matrix[i][j] = 1.0;
         *(*Matrix + i * DIMENSION + j) = 1.0;
      }
    }
  }
}


/*********************************************************************\
* Input    : None                                                     *
* Output   : None                                                     *
* Function : Initialize a matrix columnwise                           *
\*********************************************************************/
void      InitializeMatrixColumnwise() {
  int i,j;
  double x;

  x = 0.0;
  for (j = 0; j < DIMENSION; j++) {
    for (i = 0; i < DIMENSION; i++) {
      if (i >= j) {
        // Matrix[i][j] = x;
        *(*Matrix + i * DIMENSION + j) = x;
	      x += 1.0;
      } else {
	      // Matrix[i][j] = 1.0;
        *(*Matrix + i * DIMENSION + j) = 1.0;
      }
    }
  }
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
