#include "project.h"

/*
 *  BEGIN COLLISION DETECTION METHODS
 */

/*
 *  checkCollisions
 *  ------
 *  Check each minions as spheres against the tower's shots for collision
 *  This is a brute force O(2N) function and checks every shot against every minion,
 *  this could be fixed up a lot with binary space partitioning.
 *  Additionally, this isn't proper collision detection (at all). We're just checking the origin
 *  of each object against one another (with a slight offset), rather than checking the surface
 *  normals of each other using dot product, etc.
 */
void checkCollisions(void)
{
  int i,j;
  /* this should be to lastShot, but I need a sorting algorithm first */
  for (i=0;i<Length(shots);i++) {
    shot s = shots[i];
    if (s.inPlay) {
      for (j=0;j<Length(waves[waveNumber-1].m);j++) {
	if (waves[waveNumber-1].m[j].inPlay) {
	  point origin = s.p;
	  point target = waves[waveNumber-1].m[j].translation;
	  point tScale = waves[waveNumber-1].m[j].scale;
	  double distance = sqrt((origin.x-target.x)*(origin.x-target.x)+
				 (origin.z-target.z)*(origin.z-target.z));
	  if (distance < 5*tScale.x) {
	    /* if hit, take damage on minion, remove shot */
	    int health = calculateDamageToMinion(waveNumber-1,j,i);
	    removeShot(i);
	    if (health <= 0) removeMinion(waveNumber-1,j);
	    /* check to see if minion is dead, if dead, remove minion */
	    if (debug) {
		printf("\nshot  i     :%d\n",i);
		printf("shot  loc  x:%f\n",origin.x);
		printf("shot  loc  y:%f\n",origin.y);
		printf("shot  loc  z:%f\n",origin.z);
		printf("minion j    :%d\n",j);
		printf("minion loc x:%f\n",target.x);
		printf("minion loc y:%f\n",target.y);
		printf("minion loc z:%f\n",target.z);
		printf("minion scale:%f\n",tScale.x);
		printf("distance    :%f\n",distance);
	    }
	    /* only do this until first one is found */
	    break;
	  }
	}
      }
    }
  }
}

/*
 *  checkTowerRange
 *  ------
 *  Check each tower's range to see if it should start shooting at a minion
 *  TODO: check to see if game paused and be sure to pause the timers
 *  TODO: the distance formula isn't exactly right below. It only fires after they're in range.
 */
void checkTowerRange(void)
{
  int i,j;
  for (i=0;i<Length(towers);i++) {
    if (towers[i].inPlay) {
      /* check to see when the last time the tower shot was and fire if its later than fireRate */
      time_t fireShot;
      double timeDiff;
      fireShot = time(NULL);
      timeDiff = difftime(fireShot,towers[i].lastFired);
      if (towers[i].lastFired == 0 || timeDiff > towers[i].fireRate) {
	for (j=0;j<Length(waves[waveNumber-1].m);j++) {
	  if (waves[waveNumber-1].m[j].inPlay) {
	    point origin = towers[i].translation;
	    point target = waves[waveNumber-1].m[j].translation;
	    point tScale = waves[waveNumber-1].m[j].scale;
	    double distance = sqrt((origin.x-target.x)*(origin.x-target.x)+
				   (origin.z-target.z)*(origin.z-target.z)) - tScale.x;
	    /* check to see if we're within range */
	    if (distance < towers[i].range) {
	      shot s = {1,{origin.x,origin.y,origin.z},towers[i].texture,towers[i].damage};
	      time_t shotFired;
	      shots[lastShot] = s;
	      shotFired = time(NULL);
	      towers[i].lastFired = shotFired;
	      lastShot++;
      	      if (debug) {
		printf("\npew pew\n");
		printf("fireshot: %f\n",(double)fireShot);
		printf("timediff: %f\n",timeDiff);
		printf("checking tower range\n");
		printf("target in range- fire ze missiles!\n");
		printf("tower i     :%d\n",i);
		printf("tower loc  x:%f\n",origin.x);
		printf("tower loc  y:%f\n",origin.y);
		printf("tower loc  z:%f\n",origin.z);
		printf("tower range :%d\n",towers[i].range);
		printf("minion j    :%d\n",j);
		printf("minion loc x:%f\n",target.x);
		printf("minion loc y:%f\n",target.y);
		printf("minion loc z:%f\n",target.z);
		printf("minion scale:%f\n",tScale.x);
		printf("distance    :%f\n",distance);
	      }
	      /* only do this until first one is found */
	      break;
	    } /* end if range check */
	  } /* end if minion in play */
	} /* end for each minion in wave */
      } /* end last fired check*/
    } /* end if tower in play */
  } /* end for each tower */
}
