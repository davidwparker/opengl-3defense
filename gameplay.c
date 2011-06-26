#include "project.h"

/*
 *  BEGIN GAMEPLAY FUNCTIONALITY
 */

/*
 *  modifyLives
 *  ------
 *  changes life +/- depending on buying or dying
 */
void modifyLives(int die)
{
  if (die) {
    lives--;
  }
  else {
    /* buying lives */
    lives++;
  }
}


