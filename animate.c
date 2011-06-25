#include "project.h"

/*
 *  BEGIN ANIMATION FUNCTIONS
 */

/*
 *  moveLight
 *  ------
 *  move the light into position
 */
void moveLight(double t)
{
  if (moveLightB)
    lightPh = fmod(45*t,360.0);
}

/*
 *  moveMinions
 *  ------
 *  moves every minion into its specific position
 */
void moveMinions(void)
{
  if (moveMinionsB) {
    int i,j;
    /* each minion moves its specific amount along the path */
    for (i=0;i<Length(minions);i++) {
      int speed = minions[i].speed;
      /* Length(fullPath) = 2200... error about sizeof with structs */
      for (j=0;j<(DEF_PATH_LEN*DEF_FULL_PATH_LEN);j += speed) {
	/* first time through */
	if (minions[i].translation.x > 25) {
	  minions[i].translation.x = fullPath[0].p.x;
	  minions[i].translation.z = fullPath[0].p.z;
	  minions[i].rotation.y = fullPath[0].dir;
	  break;
	}
	/* if we're at the previous position, increment by one */
	else if(minions[i].translation.x == fullPath[j-speed].p.x &&
		minions[i].translation.z == fullPath[j-speed].p.z) {
	  minions[i].translation.x = fullPath[j].p.x;
	  minions[i].translation.z = fullPath[j].p.z;
	  minions[i].rotation.y = fullPath[j].dir;
	  break;
	}
	/* TODO: remove this after calculating failure, restart back at the begininning */
	if (j == (DEF_PATH_LEN*DEF_FULL_PATH_LEN)) {
	  minions[i].translation.x = fullPath[0].p.x;
	  minions[i].translation.z = fullPath[0].p.z;
	  minions[i].rotation.y = fullPath[0].dir;
	}
      }
    }
  }
}

void moveTowerTops(double t) 
{
  if (moveTowerTopsB) 
    towerTh = fmod(90*t,360.0);
}
