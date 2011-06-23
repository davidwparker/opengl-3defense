#include "project.h"

/*
 *  BEGIN TOWER DEFINITIONS
 */

/*
 *  basicTower
 *  ------
 *  A basic tower just consists of several cylinders and a diamond
 */
void basicTower(double x,double y,double z,
		double dx,double dy,double dz,
		double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* base */
  cylinder(0,0,0, 1,3);
  /* mid-section */
  cylinder(0,3,0, 1.5,1);
  /* top */
  cylinder(0,4,0, 1.2,1);

  glPopMatrix();
}

/*
 *  advancedTower
 *  ------
 *  An advanced tower is a basic tower plus spikes
 */
void advancedTower(double x,double y,double z,
		   double dx,double dy,double dz,
		   double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  basicTower(0,0,0,1,1,1,0);

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
void coneTower(double x,double y,double z,
	       double dx,double dy,double dz,
	       double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* base */
  cone(0,-3,0, 1.4,4,DEF_D);
  /* mid-section */
  glPushMatrix();
  glRotated(180,1,0,0);
  cone(0,-3,0, 1.4,4,DEF_D);
  glPopMatrix();
  /* top */
  cylinder(0,4.0,0, 1.5,1.0);

  glPopMatrix();
}

/*
 *  advancedConeTower
 *  ------
 *  An advanced cone tower just consists of a cone tower and spikes
 */
void advancedConeTower(double x,double y,double z,
		       double dx,double dy,double dz,
		       double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  coneTower(0,0,0, 1,1,1, 0);

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
void squareTower(double x,double y,double z,
		 double dx,double dy,double dz,
		 double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* base */
  cylinder(0,0,0, 1,3);
  /* mid-section */
  cube(0,3.5,0, 1.5,.5,1.5, 0);
  /* pyramid */
  pyramid(0,4,0, 0.75,0.75,0.75, 0);

  glPopMatrix();
}

/*
 *  advancedSquareTower
 *  ------
 *  An advanced square tower just consists of a square tower and spikes
 */
void advancedSquareTower(double x,double y,double z,
			 double dx,double dy,double dz,
			 double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* base */
  squareTower(0,0,0, 1,1,1, 0);

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
void fireTower(double x,double y,double z,
	       double dx,double dy,double dz,
	       double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_FIRE];
  basicTower(0,0,0, 1,1,1,0);
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
void fireTower2(double x,double y,double z,
		double dx,double dy,double dz,
		double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_FIRE];
  advancedTower(0,0,0, 1,1,1,0);
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
void iceTower(double x,double y,double z,
	      double dx,double dy,double dz,
	      double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_ICE];
  basicTower(0,0,0, 1,1,1,0);
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
void iceTower2(double x,double y,double z,
	       double dx,double dy,double dz,
	       double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_ICE];
  advancedTower(0,0,0, 1,1,1,0);
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
void earthTower(double x,double y,double z,
		double dx,double dy,double dz,
		double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_EARTH];
  coneTower(0,0,0, 1,1,1, 0);
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
void earthTower2(double x,double y,double z,
		 double dx,double dy,double dz,
		 double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_EARTH];
  advancedConeTower(0,0,0, 1,1,1, 0);
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
void poisonTower(double x,double y,double z,
		 double dx,double dy,double dz,
		 double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_POISON];
  squareTower(0,0,0, 1,1,1, 0);
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
void poisonTower2(double x,double y,double z,
		  double dx,double dy,double dz,
		  double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_POISON];
  advancedSquareTower(0,0,0, 1,1,1, 0);
  currentTexture = textures[TEX_POISON];
  sphere(0,6,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}
