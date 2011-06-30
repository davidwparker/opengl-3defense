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
 *  Draws the board as a 24x24 flat board
 *  TODO: the board and the pathBlock should be refactored
 */
void board(void)
{
  int i,j;
  glPushMatrix();

  if (renderMode == DEF_RENDER) {
    currentTexture = textures[TEX_GRASS];
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,currentTexture);
  }

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(2,1);
  glColor3f(1,1,1);
  glNormal3f(0,1,0);
  for (i=-DEF_D_FLOOR;i<DEF_D_FLOOR;i+=2){
    glBegin(GL_QUADS);
    for(j=-DEF_D_FLOOR;j<DEF_D_FLOOR;j+=2){
      glTexCoord2f(0,0); glVertex3f(i,DEF_Y_FLOOR,j);
      glTexCoord2f(1,0); glVertex3f(i,DEF_Y_FLOOR,j+2);
      glTexCoord2f(1,1); glVertex3f(i+2,DEF_Y_FLOOR,j+2);
      glTexCoord2f(0,1); glVertex3f(i+2,DEF_Y_FLOOR,j);
    }
    glEnd();
  }
  glDisable(GL_POLYGON_OFFSET_FILL);

  if  (renderMode == DEF_RENDER) {
    glDisable(GL_TEXTURE_2D);
    currentTexture = textures[TEX_DEFAULT];
  }
  glPopMatrix();
}

/*
 *  pathBlock
 *  ------
 *  Draws an individual block of the path
 */
void pathBlock(pathCube p)
{
  glPushMatrix();

  if (renderMode == DEF_RENDER) {
    currentTexture = textures[p.texture];
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,currentTexture);
  }
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1,1);
  glColor3f(1,1,1);
  glNormal3f(0,1,0);

  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(p.p.x-2, p.p.y, p.p.z-2);
  glTexCoord2f(1,0); glVertex3f(p.p.x-2, p.p.y, p.p.z+2);
  glTexCoord2f(1,1); glVertex3f(p.p.x+2, p.p.y, p.p.z+2);
  glTexCoord2f(0,1); glVertex3f(p.p.x+2, p.p.y, p.p.z-2);
  glEnd();

  glDisable(GL_POLYGON_OFFSET_FILL);

  if  (renderMode == DEF_RENDER) {
    glDisable(GL_TEXTURE_2D);
    currentTexture = textures[TEX_DEFAULT];
  }

  glPopMatrix();
}

/*
 *  path
 *  ------
 *  A path is just a bunch of pathBlocks
 */
void path(void)
{
  int i;
  glPushMatrix();
  /* Length(pathCubes) = 45... error about sizeof with structs */
  for (i=0; i < DEF_PATH_LEN; i++) {
    pathBlock(pathCubes[i]);
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
 *  A keep is just walls, towers, and crates
 */
void keep(double x,double y,double z,
	  double dx,double dy,double dz,
	  double th)
{
  tower t = {0, OBJ_ADV_SQUARE,1,{9,0,9},{1.5,2,1.5},{0,0,0},TEX_BRICK2,{1,1,1},
	     "Advanced Tower",-1,-1,-1,-1,-1,-1,"Description"};
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

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
  advancedSquareTower(t);
  t.translation.x = -9;
  advancedSquareTower(t);
  t.translation.z = -9;
  advancedSquareTower(t);
  t.translation.x = 9;
  advancedSquareTower(t);

  /* crates */
  glPushMatrix();
  glTranslated(0,0,-3);
  crates(-3,0,-2, 1,1,1, 0);
  crates(0,0,0, 1,1,1, 45);
  crates(2,0,-3, 1,1,1, 90);
  crates(-7,0,7, 1,1,1, 150);
  crate(5,0,10, 1,1,1, 0);
  glPopMatrix();

  currentTexture = textures[TEX_DEFAULT];
  glPopMatrix();
}

/*
 *  shot
 *  ------
 *  draws an individual shot
 */
void shotModel(shot s)
{
  glPushMatrix();
  glTranslated(s.p.x, s.p.y, s.p.z);
  currentTexture = textures[s.texture];
  sphere(0,0,0, 0.5,towerTh);
  currentTexture = textures[TEX_DEFAULT];
  glPopMatrix();
}

/*
 *  minionModel
 *  ------
 *  A minionModel is just an obj at a particular location
 */
void minionModel(minion m)
{
  /* draw the minion */
  glPushMatrix();
  glTranslated(m.translation.x,m.translation.y,m.translation.z);
  glRotated(m.rotation.y,0,1,0);
  glScaled(m.scale.x,m.scale.y,m.scale.z);
  glColor3f((double)m.rgb.r/100,(double)m.rgb.g/100,(double)m.rgb.b/100);
  glCallList(m.type);

  /* sphere for reference with collision detection 
     collision detection should probably be done via a box for the planes
     but I'm using a sphere for ease of use/time
  */
  if (showCollisionDetection) {
    glColor3f(1,1,0);
    glTranslated(-2,4,-0.5);
    glutSolidSphere(5,16,16);
  }
  glColor3fv(white);

  glPopMatrix();
}

