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
 *  canUserBuyTower
 *  ------
 *  determines if user can buy the selected tower and sets the appropriate variables
 */
void canUserBuyTower(int newObjectSelected)
{
  if (money >= tower_data[objectSelected-1].cost) {
    info = "cha-ching$ thanks buddy.";
    setCurrentTowerData(objectSelected);
  } else {
    info = "Not enough $$$.";
    objectSelected = DEF_OBJ_SEL;
    preview_tower.id = DEF_OBJ_SEL;
  }
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
  waves[k].m[j].inPlay = 0;
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


