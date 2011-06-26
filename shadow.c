#include "project.h"

/*
 *  BEGIN SHADOW FUNCTIONALITY
 */

/* 
 *  shadowProjection
 *  ------
 *  Multiply the current ModelView-Matrix with a shadow-projetion matrix.
 *
 *  L is the position of the light source
 *  E is a point within the plane on which the shadow is to be projected.  
 *  N is the normal vector of the plane.
 *
 *  Everything that is drawn after this call is "squashed" down to the plane.
 */
void shadowProjection(float L[4], float E[4], float N[4])
{
  float mat[16];
  float e = E[0]*N[0] + E[1]*N[1] + E[2]*N[2];
  float l = L[0]*N[0] + L[1]*N[1] + L[2]*N[2];
  float c = e - l;
  int i;
  if (debug) {
    for (i=0;i<4;i++)  printf("L[%d]=   %f\n",i,L[i]);
    for (i=0;i<4;i++)  printf("E[%d]=   %f\n",i,E[i]);
    for (i=0;i<4;i++)  printf("N[%d]=   %f\n",i,N[i]);
    printf("\n%f, %f, %f\n",e,l,c);
  }
  /*  Create the matrix */
  mat[0] = N[0]*L[0]+c; mat[4] = N[1]*L[0];   mat[8]  = N[2]*L[0];   mat[12] = -e*L[0];
  mat[1] = N[0]*L[1];   mat[5] = N[1]*L[1]+c; mat[9]  = N[2]*L[1];   mat[13] = -e*L[1];
  mat[2] = N[0]*L[2];   mat[6] = N[1]*L[2];   mat[10] = N[2]*L[2]+c; mat[14] = -e*L[2];
  mat[3] = N[0];        mat[7] = N[1];        mat[11] = N[2];        mat[15] = -l;
  if (debug) {
    for (i=0;i<16;i++)  printf("mat[%d]=   %f\n",i,mat[i]);
  }
  /*  Multiply modelview matrix */
  glMultMatrixf(mat);
}
