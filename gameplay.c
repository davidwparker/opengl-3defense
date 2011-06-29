#include "project.h"

/*
 *  BEGIN GAMEPLAY FUNCTIONALITY
 */

/*
 *  calculateDamage
 *  ------
 *  calculates the damage done to a specific minion and returns its current health
 */
int calculateDamageToMinion(int k, int j, int i)
{
  waves[k].m[j].health -= shots[i].damage;
  return waves[k].m[j].health;
}

/*
 *  modifyLives
 *  ------
 *  changes life +/- depending on buying or dying
 */
void modifyLives(int die, int damage)
{
  if (die) {
    lives -= damage;
  }
  else {
    /* buying lives */
    lives++;
  }
}

/*
 *  modifyMoney
 *  ------
 *  changes money based on buying/killing/selling
 */
void modifyMoney(int what, int amount)
{
  /* buying */
  if (what == 0) {
    money -= amount;
  }
  /* killing */
  else if (what == 1) {
    money += amount;
  }
  /* selling - to be implemented */
  else if (what == 2) {
    money += amount;
  }
}

/*
 *  modifyScore
 *  ------
 *  changes score. This should probably be a static thing, but we're doing it based on wave number
 */
void modifyScore(int k)
{
  score += waveNumber*5;
}


/*
 *  removeMinion
 *  ------
 *  "removes" the minion
 */
void removeMinion(int k, int j)
{
  minion m = {0,minionObj,{-255,-255,-255},
	       {1,1,1},{0,270,0},0,{1,1,1},
	       "F16",1,5,5,1,0};
  waves[k].m[j] = m;
  modifyScore(k+1);
  modifyMoney(1,waves[k].m[j].money);
}

/*
 *  removeShot
 *  ------
 *  "removes" the shot
 */
void removeShot(int i)
{
  shot s = {0,{-255,-255,-255},TEX_DEFAULT,0};
  shots[i] = s;
}


