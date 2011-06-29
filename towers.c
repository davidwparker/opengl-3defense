#include "project.h"

/*
 *  BEGIN TOWER DEFINITIONS
 */

/*
 *  basicTower
 *  ------
 *  A basic tower just consists of several cylinders and a diamond
 */
void basicTower(tower t)
{
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);
  currentTexture = textures[t.texture];

  /* base */
  cylinder(0,0,0, 1,3);
  /* mid-section */
  cylinder(0,3,0, 1.5,1);
  /* top */
  cylinder(0,4,0, 1.2,1);

  currentTexture = textures[TEX_DEFAULT];

  /* everything has a hard-coded range of 10 at the moment*/
  if (t.range > -1 && showAttackRadius) {
    circle(t.range);
  }
  glPopMatrix();
}

/*
 *  advancedTower
 *  ------
 *  An advanced tower is a basic tower plus spikes
 */
void advancedTower(tower t)
{
  tower t2 = {0,OBJ_BASIC,1,{0,0,0},{1,1,1},{0,0,0},t.texture,{1,1,1},
	      t.name,1,t.range,t.damage,t.fireRate,0,t.cost,"Description"};
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);
  basicTower(t2);

  /* 8x cones as spikes */
  spike(0,1.2,-3, 0.5,1,DEF_D, 90,0,0);
  spike(0,1.2,3,  0.5,1,DEF_D, -90,0,0);
  spike(3,1.2,0,  0.5,1,DEF_D, 0,0,90);
  spike(-3,1.2,0, 0.5,1,DEF_D, 0,0,-90);

  /* diagonal spikes */
  spike(0,1.2,-3, 0.5,1,DEF_D, 90,45,0);
  spike(0,1.2,3,  0.5,1,DEF_D, -90,45,0);
  spike(0,1.2,-3, 0.5,1,DEF_D, 90,-45,0);
  spike(0,1.2,3,  0.5,1,DEF_D, -90,-45,0);

  glPopMatrix();
}

/*
 *  coneTower
 *  ------
 *  A cone tower just consists of two cones and a cylinders
 */
void coneTower(tower t)
{
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);
  currentTexture = textures[t.texture];

  /* base */
  cone(0,-3,0, 1.4,4,DEF_D);
  /* mid-section */
  glPushMatrix();
  glRotated(180,1,0,0);
  cone(0,-3,0, 1.4,4,DEF_D);
  glPopMatrix();
  /* top */
  cylinder(0,4.0,0, 1.5,1.0);

  currentTexture = textures[TEX_DEFAULT];

  /* everything has a hard-coded range of 10 at the moment*/
  if (t.range > -1 && showAttackRadius) {
    circle(t.range);
  }
  glPopMatrix();
}

/*
 *  advancedConeTower
 *  ------
 *  An advanced cone tower just consists of a cone tower and spikes
 */
void advancedConeTower(tower t)
{
  tower t2 = {0,OBJ_CONE,1,{0,0,0},{1,1,1},{0,0,0},t.texture,{1,1,1},
	      t.name,1,t.range,t.damage,t.fireRate,0,t.cost,"Description"};
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);
  coneTower(t2);

  /* 8x cones as spikes */
  spike(0,1.2,-4, 0.5,1,DEF_D, 90,0,0);
  spike(0,1.2,4,  0.5,1,DEF_D, -90,0,0);
  spike(4,1.2,0,  0.5,1,DEF_D, 0,0,90);
  spike(-4,1.2,0, 0.5,1,DEF_D, 0,0,-90);

  /* diagonal spikes */
  spike(0,1.2,-4, 0.5,1,DEF_D, 90,45,0);
  spike(0,1.2,4,  0.5,1,DEF_D, -90,45,0);
  spike(0,1.2,-4, 0.5,1,DEF_D, 90,-45,0);
  spike(0,1.2,4,  0.5,1,DEF_D, -90,-45,0);

  glPopMatrix();
}

/*
 *  squareTower
 *  ------
 *  A square tower just consists of a cylinder, a cube, and a pyramid
 */
void squareTower(tower t)
{
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);
  currentTexture = textures[t.texture];

  /* base */
  cylinder(0,0,0, 1,3);
  /* mid-section */
  cube(0,3.5,0, 1.5,.5,1.5, 0);
  /* pyramid */
  pyramid(0,4,0, 0.75,0.75,0.75, 0);

  currentTexture = textures[TEX_DEFAULT];

  /**/
  if (t.range > -1 && showAttackRadius) {
    /* everything has a hard-coded range of 10 at the moment*/
    circle(t.range);
  }
  glPopMatrix();
}

/*
 *  advancedSquareTower
 *  ------
 *  An advanced square tower just consists of a square tower and spikes
 */
void advancedSquareTower(tower t)
{
  tower t2 = {0, OBJ_SQUARE,1,{0,0,0},{1,1,1},{0,0,0},t.texture,{1,1,1},
	      t.name,1,t.range,t.damage,t.fireRate,0,t.cost,"Description"};
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);
  /* base */
  squareTower(t2);

  /* 8x cones as spikes */
  spike(0,1.2,-3.5, 0.5,1,DEF_D, 90,0,0);
  spike(0,1.2,3.5,  0.5,1,DEF_D, -90,0,0);
  spike(3.5,1.2,0,  0.5,1,DEF_D, 0,0,90);
  spike(-3.5,1.2,0, 0.5,1,DEF_D, 0,0,-90);

  /* diagonal spikes */
  spike(0,1.6,-3.5, 0.5,1,DEF_D, 90,45,0);
  spike(0,1.6,3.5, 0.5,1,DEF_D, -90,45,0);
  spike(0,1.6,-3.5, 0.5,1,DEF_D, 90,-45,0);
  spike(0,1.6,3.5, 0.5,1,DEF_D, -90,-45,0);

  glPopMatrix();
}

/*
 *  fireTower
 *  ------
 *  A fire tower is a plain tower with a sphere above it
 */
void fireTower(tower t)
{
  tower t2 = {0, OBJ_FIRE,1,{0,0,0},{1,1,1},{0,0,0},TEX_FIRE,{1,1,1},
	      t.name,1,t.range,t.damage,t.fireRate,0,t.cost,"Description"};
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);

  basicTower(t2);
  currentTexture = textures[TEX_FIRE];
  sphere(0,6.2,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  fireTower2
 *  ------
 *  A fire tower is an advanced tower with a sphere above it
 */
void fireTower2(tower t)
{
  tower t2 = {0, OBJ_FIRE2,1,{0,0,0},{1,1,1},{0,0,0},TEX_FIRE,{1,1,1},
	      t.name,1,t.range,t.damage,t.fireRate,0,t.cost,"Description"};
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);

  advancedTower(t2);
  currentTexture = textures[TEX_FIRE];
  sphere(0,6.2,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  iceTower
 *  ------
 *  An ice tower is a plain tower with a star above it
 */
void iceTower(tower t)
{
  tower t2 = {0, OBJ_ICE,1,{0,0,0},{1,1,1},{0,0,0},TEX_ICE,{1,1,1},
	      t.name,1,t.range,t.damage,t.fireRate,0,t.cost,"Description"};
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);

  basicTower(t2);
  currentTexture = textures[TEX_ICE];
  star(0,6.2,0, 0.25,0.25,0.25, towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  iceTower2
 *  ------
 *  An ice tower is an advanced tower with a star above it
 */
void iceTower2(tower t)
{
  tower t2 = {0, OBJ_ICE2,1,{0,0,0},{1,1,1},{0,0,0},TEX_ICE,{1,1,1},
	      t.name,1,t.range,t.damage,t.fireRate,0,t.cost,"Description"};
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);

  advancedTower(t2);
  currentTexture = textures[TEX_ICE];
  star(0,6.2,0, 0.25,0.25,0.25, towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  earthTower
 *  ------
 *  An earth tower is a cone tower with a sphere above it
 */
void earthTower(tower t)
{
  tower t2 = {0, OBJ_EARTH,1,{0,0,0},{1,1,1},{0,0,0},TEX_EARTH,{1,1,1},
	      t.name,1,t.range,t.damage,t.fireRate,0,t.cost,"Description"};
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);

  coneTower(t2);
  currentTexture = textures[TEX_EARTH];
  sphere(0,6.2,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  earthTower2
 *  ------
 *  An earth tower 2 is an advanced cone tower with a sphere above it
 */
void earthTower2(tower t)
{
  tower t2 = {0, OBJ_EARTH,1,{0,0,0},{1,1,1},{0,0,0},TEX_EARTH,{1,1,1},
	      t.name,1,t.range,t.damage,t.fireRate,0,t.cost,"Description"};
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);

  advancedConeTower(t2);
  currentTexture = textures[TEX_EARTH];
  sphere(0,6.2,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  poisonTower
 *  ------
 *  An poison tower is a square tower with a sphere above it
 */
void poisonTower(tower t)
{
  tower t2 = {0, OBJ_POISON,1,{0,0,0},{1,1,1},{0,0,0},TEX_POISON,{1,1,1},
	      t.name,1,t.range,t.damage,t.fireRate,0,t.cost,"Description"};
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);

  squareTower(t2);
  currentTexture = textures[TEX_POISON];
  sphere(0,6,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  poisonTower2
 *  ------
 *  An poison tower 2 is an advanced square tower with a sphere above it
 */
void poisonTower2(tower t)
{
  tower t2 = {0, OBJ_POISON,1,{0,0,0},{1,1,1},{0,0,0},TEX_POISON,{1,1,1},
	      t.name,1,t.range,t.damage,t.fireRate,0,t.cost,"Description"};
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);

  advancedSquareTower(t2);
  currentTexture = textures[TEX_POISON];
  sphere(0,6,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}
