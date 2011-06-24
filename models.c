#include "project.h"

/*
 *  BEGIN MODEL DEFINITION FUNCTIONS
 */

/*
 *  pyramid
 *  ------
 *  Draw a pyramid 
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 *  A pyramid is just a cone with 4 sides (360/90 degrees)
 */ 
void pyramid(double x, double y, double z,
		    double dx, double dy, double dz,
		    double th)
{
  glPushMatrix();
  /*  Transform cube */
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  cone(0,0,0, 1,1, 90);

  glPopMatrix();
}

/*
 *  star
 *  ------
 *  Draw a star
 *     at (x, y, z)
 *     dimensions dx, dy, dz
 *     rotated th around the y axis
 *  A star is just 6 pyramids
 */
void star(double x, double y, double z,
		 double dx, double dy, double dz,
		 double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /*top of diamond*/
  pyramid(0,0.5,0, 1,3,1, 0);

  /*back facing*/
  glPushMatrix();
  glRotatef(-90,1,0,0);
  pyramid(0,0.5,0, 1,3,1, 90);
  glPopMatrix();

  /*forward facing*/
  glPushMatrix();
  glRotatef(90,1,0,0);
  pyramid(0,0.5,0, 1,3,1, 0);
  glPopMatrix();

  /*right facing*/
  glPushMatrix();
  glRotatef(-90,0,0,1);
  pyramid(0,0.5,0, 1,3,1, 90);
  glPopMatrix();

  /*left facing*/
  glPushMatrix();
  glRotatef(90,0,0,1);
  pyramid(0,0.5,0, 1,3,1, -90);
  glPopMatrix();

  /*bottom of star*/
  glPushMatrix();
  glRotatef(180,1,0,0);
  pyramid(0,0.5,0, 1,3,1, 0);
  glPopMatrix();

  glPopMatrix();
}

/*
 *  spike
 *  ------
 *  Draw a spike
 *     at (x, y, z)
 *     radius r, height h, with 360/deg sides
 *     rotated ox around the x axis
 *     rotated oy around the y axis
 *     rotated oz around the z axis
 *  A spike is just a cone that is textured in spike
 */
void spike(double x, double y, double z,
		  double r,double h,int deg,
		  double ox,double oy,double oz)
{
  currentTexture = textures[TEX_SPIKE];
  glPushMatrix();
  glRotated(oz,0,0,1);
  glRotated(oy,0,1,0);
  glRotated(ox,1,0,0);

  cone(x,y,z, r,h,deg);
  glPopMatrix();
  currentTexture = textures[TEX_DEFAULT];
}

/*
 *  board
 *  ------
 *  Draws the board as a 8x8 cubes on the screen
 */
void board(void)
{
  int i,j;
  currentTexture = textures[TEX_GRASS];
  for (i=-24;i<24;i++){
    for(j=-24;j<24;j++){
      cube(i,-3,j, 1,0.2,1, 0);
    }
  }
  currentTexture = textures[TEX_DEFAULT];
}

void pathCube(pathC path)
{
  glPushMatrix();
  currentTexture = path.texture;
  cube(path.p.x,path.p.y,path.p.z, 2,0.2,2, path.rotation);
  glPopMatrix();
}

/*
 *  path
 *  ------
 *  A path is just a textured cubes which is slightly higher than the board
 */
void path(void)
{
  int ts1 = textures[TEX_STREET1];
  int ts3 = textures[TEX_STREET3];
  pathC path[] = {
    {{21,-2.9,-1},ts1,90},{{17,-2.9,-1},ts1,90},{{13,-2.9,-1},ts3,270},
    {{13,-2.9,-5},ts1,180},{{13,-2.9,-9},ts1,180},{{13,-2.9,-13},ts1,180},
    {{13,-2.9,-17},ts3,90},{{9,-2.9,-17},ts1,90},{{5,-2.9,-17},ts3,180},
    {{5,-2.9,-17},ts1,180},{{5,-2.9,-13},ts1,180},{{5,-2.9,-9},ts1,180},
    {{5,-2.9,-5},ts1,180},{{5,-2.9,-1},ts1,180},{{5,-2.9,3},ts1,180},
    {{5,-2.9,7},ts3,270},{{9,-2.9,7},ts1,270},{{13,-2.9,7},ts1,270},
    {{17,-2.9,7},ts3,90},{{17,-2.9,11},ts1,0},{{17,-2.9,15},ts3,0},
    {{13,-2.9,15},ts1,90},{{9,-2.9,15},ts1,90},{{5,-2.9,15},ts1,90},
    {{1,-2.9,15},ts1,90},{{-3,-2.9,15},ts3,270},{{-3,-2.9,11},ts1,180},
    {{-3,-2.9,7},ts1,180},{{-3,-2.9,3},ts1,180},{{-3,-2.9,-1},ts1,180},
    {{-3,-2.9,-5},ts1,180},{{-3,-2.9,-9},ts1,180},{{-3,-2.9,-13},ts1,180},
    {{-3,-2.9,-17},ts3,90},{{-7,-2.9,-17},ts1,90},{{-11,-2.9,-17},ts3,180},
    {{-11,-2.9,-13},ts1,180},{{-11,-2.9,-9},ts1,180},{{-11,-2.9,-5},ts1,180},
    {{-11,-2.9,-1},ts1,180},{{-11,-2.9,3},ts1,180},{{-11,-2.9,7},ts1,180},
    {{-11,-2.9,11},ts3,0},{{-15,-2.9,11},ts1,90},{{-19,-2.9,11},ts1,90},
  };
  int i;

  glPushMatrix();
  for (i=0; i < Length(path); i++) {
    pathCube(path[i]);
  }
  currentTexture = textures[TEX_DEFAULT];
  glPopMatrix();
}

/*
 *  crate
 *  ------
 *  A crate is just a textured cube
 */
void crate(double x,double y,double z,
	   double dx,double dy,double dz,
	   double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_CRATE];
  cube(0,-2,0, 1,1,1, 0);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  crates
 *  ------
 *  Draws 4 crates stacked on each other
 */
void crates(double x,double y,double z,
	   double dx,double dy,double dz,
	   double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  /* base crates */
  crate(0,0,0, 1,1,1, 0);
  crate(-2.2,0,1, 1,1,1, 0);
  glPushMatrix();
  glTranslated(0,0,2.5);
  crate(0,0,0, 1,1,1, 45);
  glPopMatrix();
  /* top crate */
  crate(-1,2,1, 1,1,1, 30);
  glPopMatrix();
}

/*
 *  evergreenTree1
 *  ------
 *  Draws a single evergreen tree as two cones and a cylinder
 */
void evergreenTree1(double x,double y,double z,
		    double dx,double dy,double dz,
		    double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* base */
  currentTexture = textures[TEX_WOOD];
  cylinder(0,-2,0, 0.3,1.0);
  currentTexture = textures[TEX_EVERGREEN];
  /* mid-section */
  cone(0,-2,0, 1.3,2,DEF_D);
  /* top */
  cone(0,-1,0, 1,2,DEF_D);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  evergreenTree2
 *  ------
 *  Draws a single evergreen tree three cones and a cylinder
 */
void evergreenTree2(double x,double y,double z,
		    double dx,double dy,double dz,
		    double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* base */
  currentTexture = textures[TEX_WOOD];
  cylinder(0,-2,0, 0.5,1.0);
  currentTexture = textures[TEX_EVERGREEN];
  /* mid-section 1 */
  cone(0,-2,0, 1.5,3,DEF_D);
  /* mid-section 2 */
  cone(0,-0.5,0, 1.4,3,DEF_D);
  /* top */
  cone(0,1,0, 1,2,DEF_D);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  evergreenForest
 *  ------
 *  Draws 4 evergreens together of different sizes
 */
void evergreenForest(double x,double y,double z,
		     double dx,double dy,double dz,
		     double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  /* draw the forest */
  evergreenTree1(0,0.3,-1, 1,1,1, 0);
  evergreenTree1(1.5,-1.3,-2, 0.5,0.5,0.5, 0);
  evergreenTree2(3,0,0, 1,1,1, 0);
  evergreenTree2(1,1.5,2, 1.5,1.5,1.5, 0);

  glPopMatrix();
}

/*
 *  evergreenForest1
 *  ------
 *  Draws 3 evergreens forests together of different sizes
 */
void evergreenForest1(double x,double y,double z,
		      double dx,double dy,double dz,
		      double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  /* draw the forest */
  evergreenForest(-5,0.3,-5, 1.2,1.2,1.2, 270);
  evergreenForest(0,0,-2, 1,1,1, 180);
  evergreenForest(2,-0.5,-5, 0.8,0.8,0.8, 0);

  glPopMatrix();
}

/*
 *  wall
 *  ------
 *  A wall is just a few textured cubes
 */
void wall(double x,double y,double z,
	  double dx,double dy,double dz,
	  double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_BRICK];
  /* wall */
  cube(0,-2,0, 0.2,1,1, 0);
  cube(0,0,0, 0.2,1,1, 0);
  cube(0,2,0, 0.2,1,1, 0);
  cube(0,4,0, 0.2,1,1, 0);

  glPushMatrix();
  glTranslated(0,0,-2);
  cube(0,-2,0, 0.2,1,1, 0);
  cube(0,0,0, 0.2,1,1, 0);
  cube(0,2,0, 0.2,1,1, 0);
  cube(0,4,0, 0.2,1,1, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0,0,2);
  cube(0,-2,0, 0.2,1,1, 0);
  cube(0,0,0, 0.2,1,1, 0);
  cube(0,2,0, 0.2,1,1, 0);
  cube(0,4,0, 0.2,1,1, 0);
  glPopMatrix();

  /* platform */
  glPushMatrix();
  glTranslated(1,4,0);
  glRotated(90,0,0,1);
  glRotated(90,1,0,0);
  cube(0,-2,0, 0.2,1,1, 0);
  cube(0,0,0, 0.2,1,1, 0);
  cube(0,2,0, 0.2,1,1, 0);
  glPopMatrix();

  /* top blocks */
  glPushMatrix();
  glTranslated(0,5,0);
  cube(0,0,1.3, 0.2,1,0.7, 0);
  cube(0,0,-1.3, 0.2,1,0.7, 0);
  glPopMatrix();
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  keep
 *  ------
 *  A keep is just walls, towers, some grass (like board), and crates
 */
void keep(double x,double y,double z,
	  double dx,double dy,double dz,
	  double th)
{
  int i,j;
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* some grass */
  currentTexture = textures[TEX_GRASS];
  for (i=-10;i<8;i++){
    for(j=-10;j<10;j++){
      cube(i,-3,j, 1,0.2,1, 0);
    }
  }
  currentTexture = textures[TEX_DEFAULT];

  /* back walls */
  wall(-9,0,5, 1,1,1, 0);
  wall(-9,0,-0.5, 1,1,1, 0);
  wall(-9,0,-6, 1,1,1, 0);

  /* left walls */
  glPushMatrix();
  glRotated(90,0,1,0);
  wall(-9,0,5, 1,1,1, 0);
  wall(-9,0,-0.5, 1,1,1, 0);
  wall(-9,0,-6, 1,1,1, 0);
  glPopMatrix();

  /* right walls */
  glPushMatrix();
  glRotated(270,0,1,0);
  wall(-9,0,5, 1,1,1, 0);
  wall(-9,0,-0.5, 1,1,1, 0);
  wall(-9,0,-6, 1,1,1, 0);
  glPopMatrix();

  /* front walls */
  glPushMatrix();
  glRotated(180,0,1,0);
  wall(-9,0,5, 1,1,1, 0);
  /* gap here */
  wall(-9,0,-6, 1,1,1, 0);
  glPopMatrix();

  /* towers */
  currentTexture = textures[TEX_BRICK2];
  advancedSquareTower(9,0,9,1.5,2,1.5,0);
  currentTexture = textures[TEX_BRICK2];
  advancedSquareTower(-9,0,9,1.5,2,1.5,0);
  currentTexture = textures[TEX_BRICK2];
  advancedSquareTower(-9,0,-9,1.5,2,1.5,0);
  currentTexture = textures[TEX_BRICK2];
  advancedSquareTower(9,0,-9,1.5,2,1.5,0);
  currentTexture = textures[TEX_DEFAULT];

  /* crates */
  glPushMatrix();
  glTranslated(0,0,-3);
  crates(-3,0,-2, 1,1,1, 0);
  crates(0,0,0, 1,1,1, 45);
  crates(2,0,-3, 1,1,1, 90);
  crates(-7,0,7, 1,1,1, 150);
  crate(5,0,10, 1,1,1, 0);
  glPopMatrix();

  glPopMatrix();
}

/*
 *  plane
 *  ------
 *  A plane is just an obj
 */
void plane(double x,double y,double z,
	   double dx,double dy,double dz,
	   double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  glCallList(minionObj);
  glPopMatrix();
}
