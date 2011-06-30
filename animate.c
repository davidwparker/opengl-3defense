#include "project.h"

/*
 *  BEGIN ANIMATION FUNCTIONS
 */

/*
 *  timer
 *  ------
 *  game animation logic turned on or off here
 */
void timer(int toggle)
{
  if (gameStarted) {
    if (gamePaused != DEF_GAME_PAUSED) {
      moveLight();
      moveTowerTops();
      moveShots();
      checkCollisions();
      moveMinions();
      checkCollisions();
      checkTowerRange();
    }
    glutTimerFunc(50,timer,0);
  }
  redisplayAll();
}

/*
 *  slowAnimate
 *  ------
 *  step through the animation process
 */
void slowAnimate()
{
  moveLight();
  moveTowerTops();
  moveShots();
  checkCollisions();
  moveMinions();
  checkCollisions();
  checkTowerRange();
}

/*
 *  moveLight
 *  ------
 *  move the light into position
 */
void moveLight(void)
{
  if (moveLightB)
    lightPh = (lightPh+2)%360;
}

/*
 *  moveMinion
 *  ------
 *  moves an individual minion i from wave k to fullPath j position
 */
void moveMinion(int k, int i, int j)
{
  waves[k].m[i].translation.x = fullPath[j].p.x;
  waves[k].m[i].translation.z = fullPath[j].p.z;
  waves[k].m[i].rotation.y = fullPath[j].dir;
}

/*
 *  moveMinions
 *  ------
 *  moves every minion into its specific position
 *  This is horribly inefficient code
 */
void moveMinions(void)
{
  int i,j,k;
  /* for each wave (that is in play) 
     this allows for multiple waves at once moving along.
     I'm currently not using this, so we're going to just check against the current waveNumber,
     with a poor man's for loop so I don't have to re-write code 
  */
  //  for (k=0;k<waveNumber;k++) {
  for(k=waveNumber-1;k==waveNumber-1;k++) {
    
    /* for each minion in the wave */
    for (i=0;i<Length(waves[k].m);i++) {
      int speed = waves[k].m[i].speed;
      int damage = waves[k].m[i].damage;
      
      /* Length(fullPath) = 2200... error about sizeof with structs */
      for (j=0;j<(DEF_PATH_LEN*DEF_FULL_PATH_LEN);j += speed) {
	/* if the minion is in play and in front of the keep, take damage and remove from play */
	if (waves[k].m[i].inPlay == 1 && 
	    waves[k].m[i].translation.x <= -15 &&
	    waves[k].m[i].translation.z == 11) {
	  /* minion hurts you for X damage and gets removed from play */
	  modifyLives(1, damage);
	  waves[k].m[i].inPlay = 0;
	  break;
	}

	/* first minion */
	if (i == 0) {
	  /* first time through */
	  if (waves[k].m[i].translation.x > 25) {
	    moveMinion(k,i,0);
	    break;
	  }
	  /* if we're at the previous position, increment by one */
	  else if(waves[k].m[i].translation.x == fullPath[j-speed].p.x &&
		  waves[k].m[i].translation.z == fullPath[j-speed].p.z) {
	    moveMinion(k,i,j);
	    break;
	  }
	}
	/* every other minion */
	else {
	  /* stagger the planes - this technique won't work with different speeds of planes */
	  /* first time through */
	  if (fabs(waves[k].m[i-1].translation.x - waves[k].m[i].translation.x) > 
	      ((waves[k].m[i].scale.x)*20) || 
	      fabs(waves[k].m[i-1].translation.z - waves[k].m[i].translation.z) > 0) {
	    if (waves[k].m[i].translation.x > 25){
	      moveMinion(k,i,0);
	      break;
	    }
	    /* if we're at the previous position, increment by one */
	    else if(waves[k].m[i].translation.x == fullPath[j-speed].p.x &&
		    waves[k].m[i].translation.z == fullPath[j-speed].p.z) {
	      moveMinion(k,i,j);
	      break;
	    }
	  } /* end if for plane staggering */
	} /* end else for every other minion (not the first) */
      } /* end for each point in the fullPath */
    } /* end for each minion in wave */
  } /* end for each wave */
}

/*
 *  moveShot
 *  ------
 *  move an individual shot closer to a specific minion
 *  This is kind of choppy in that it moves at 90 degree angles and then goes straight
 *  Up the X/Z axis in order to hit the target
 */
void moveShot(int i, int j, int k)
{
  /* determine the new direction vector for the shot to move towards based on minion */
  point target = waves[j].m[k].translation;
  point origin = shots[i].p;
  double xFactor=0.0, zFactor=0.0;
  if (target.x > origin.x)
    xFactor = 0.5;
  else if (target.x == origin.x)
    xFactor = 0.0;
  else if (target.x < origin.x)
    xFactor = -0.5;

  if (target.z > origin.z)
    zFactor = 0.5;
  else if (target.z == origin.z)
    zFactor = 0.0;
  else if (target.z < origin.z)
    zFactor = -0.5;

  shots[i].p.x += xFactor;
  shots[i].p.z += zFactor;
}

/*
 *  moveShots
 *  ------
 *  moves the shots towards the farthest along minion in wave
 */
void moveShots(void)
{
  int i,j;
  for (i=0;i<lastShot;i++){
    //    shot s = shots[i];
    for (j=0;j<Length(waves[waveNumber-1].m);j++) {
      if (waves[waveNumber-1].m[j].inPlay) {
	moveShot(i,waveNumber-1,j);
	break; /* only fire move shot towards the first minion */
      } /* end if minion in play */
    } /* end for each minion in the last wave */
  } /* end for until last shot */
}

/*
 *  moveTowerTops
 *  ------
 *  toggles moving the tower tops on or off
 */
void moveTowerTops(void) 
{
  if (moveTowerTopsB) 
    towerTh = (towerTh+2)%360;
}
