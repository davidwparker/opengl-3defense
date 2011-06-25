#include "project.h"

/*
 *  BEGIN SHAPE DEFINITION FUNCTIONS
 */

/*
 *  square
 *  ------
 *  Draw a square of type t, up to four sides
 *  This can be refactored to be much nicer
 */
void square(int s, int a, int b, int c, int d)
{
  glBegin(GL_POLYGON);

  /* front */
  if (s == 1) { glNormal3f(0,0,1); }
  /* back */
  else if (s == 2) { glNormal3f(0,0,-1); }
  /* right */
  else if (s == 3) { glNormal3f(1,0,0); }
  /* left */
  else if (s == 4) { glNormal3f(-1,0,0); }
  /* top */
  else if (s == 5) { glNormal3f(0,1,0); }
  /* bottom */
  else if (s == 6) { glNormal3f(0,-1,0); }
  glTexCoord2f(0,0); glVertex3fv(cube_v[a]);
  glTexCoord2f(1,0); glVertex3fv(cube_v[b]);
  glTexCoord2f(1,1); glVertex3fv(cube_v[c]);
  glTexCoord2f(0,1); glVertex3fv(cube_v[d]);

  glEnd();
}

/*
 *  cube
 *  ------
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void cube(double x,double y,double z,
	  double dx,double dy,double dz,
	  double th)
{
  float emissions[] = {0,0,0.01*emission,1};
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emissions);

  /* enable textures */
  if (renderMode == DEF_RENDER) {
    glEnable(GL_TEXTURE_2D);
    /* using the current texture */
    glBindTexture(GL_TEXTURE_2D,currentTexture);
  }
  glPushMatrix();
  /*  Transform cube */
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* front */
  square(1, 4,5,6,7);
  /* back */
  square(2, 3,0,1,2);
  /* right */
  square(3, 5,6,2,1);
  /* left */
  square(4, 7,4,0,3);
  /* top */
  square(5, 6,7,3,2);
  /* bottom */
  square(6, 0,4,5,1);

  glPopMatrix();

  /* disable textures */
  glDisable(GL_TEXTURE_2D);
}

/*
 *  vertex
 *  ------
 *  Draw vertex in polar coordinates with normal
 */
void vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   /*  For a sphere at the origin, the position
       and normal vectors are the same */
   glNormal3d(x,y,z);
   glTexCoord2d(th/360.0,ph/180.0+0.5);
   glVertex3d(x,y,z);
}

/*
 *  Draw a sphere
 *     at (x,y,z)
 *     radius (r)
 *     rotated rot around the y axis
 */
void sphere(double x,double y,double z,double r,double rot)
{
  int th,ph;
  float yellow[] = {1.0,1.0,0.0,1.0};
  float emissions[] = {0.0,0.0,0.01*emission,1.0};
  glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
  glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
  glMaterialfv(GL_FRONT,GL_EMISSION,emissions);

  if (renderMode == DEF_RENDER) {
    /* enable textures */
    glEnable(GL_TEXTURE_2D);
    /* using the current texture */
    glBindTexture(GL_TEXTURE_2D,currentTexture);
  }
  glPushMatrix();

  /*  Offset, scale and rotate */
  glTranslated(x,y,z);
  glScaled(r,r,r);
  glRotated(rot,0,1,0);

  /*  Bands of latitude */
  for (ph=-90;ph<90;ph+=DEF_D) {
    glBegin(GL_QUAD_STRIP);
    for (th=0;th<=360;th+=2*DEF_D) {
      vertex(th,ph);
      vertex(th,ph+DEF_D);
    }
    glEnd();
  }

  glPopMatrix();

  /* disable textures */
  glDisable(GL_TEXTURE_2D);
}

/*
 *  cone
 *  ------
 *  Draws a cone
 *     at (x,y,z)
 *     with radius r and height h
 *     with 360/deg sides
 */
void cone(double x,double y,double z,
	  double r,double h,int deg)
{
  int k;
  if (renderMode == DEF_RENDER) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,currentTexture);
  }
  glPushMatrix();

  /*  Transformation */
  glTranslated(x,y,z);
  glScaled(r,h,r);
  /* we're drawing this sideways
     because for some reason drawing upright doesn't work for normals */
  glRotated(-90,1,0,0);

  /* sides */
  glBegin(GL_TRIANGLES);
  for (k=0;k<=360;k+=deg){
    glNormal3f(0,0,1);
    /* center of cone is always center of texture */
    glTexCoord2f(0.5,0.5);
    glVertex3f(0,0,1);

    glNormal3f(Cos(k),Sin(k),r);
    /* need to cast to double or lose precision */
    glTexCoord2f((double)1/2*Cos(k)+0.5,(double)1/2*Sin(k)+0.5);
    glVertex3f(Cos(k),Sin(k),0);

    glNormal3f(Cos(k+deg),Sin(k+deg),r);
    /* need to cast to double or lose precision */
    glTexCoord2f((double)1/2*Cos(k+deg)+0.5,(double)1/2*Sin(k+deg)+0.5);
    glVertex3f(Cos(k+deg),Sin(k+deg),0);
  }
  glEnd();

  /* bottom circle */ 
  /* rotate back */
  glRotated(90,1,0,0);
  glBegin(GL_TRIANGLES);
  glNormal3f(0,-1,0);
  for (k=0;k<=360;k+=deg) {
    glTexCoord2f(0.5,0.5);
    glVertex3f(0,0,0);
    glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
    glVertex3f(Cos(k),0,Sin(k));
    glTexCoord2f(0.5*Cos(k+deg)+0.5,0.5*Sin(k+deg)+0.5);
    glVertex3f(Cos(k+deg),0,Sin(k+deg));
  }
  glEnd();

  glPopMatrix();

  /* disable textures */
  glDisable(GL_TEXTURE_2D);
}

/*
 *  cylinder
 *  ------
 *  Draw a cylinder
 *     at (x, y, z)
 *     with radius r and height h
 */
void cylinder(double x,double y,double z,
	      double r,double h)
{
  int i,k;
  if (renderMode == DEF_RENDER) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,currentTexture);
  }
  glPushMatrix();

  /*  Transformation */
  glTranslated(x,y,z);
  glScaled(r,h,r);

  /*  sides */
  glBegin(GL_QUAD_STRIP);
  for (k=0;k<=360;k+=DEF_D) {
    /* These textures aren't exactly what I want, but I think they look cool */
    glNormal3f(Cos(k),0,Sin(k));
    glTexCoord2f(-Cos(k),Sin(k));
    glVertex3f(Cos(k),+1,Sin(k));

    glTexCoord2f(Cos(k),Sin(k));
    glVertex3f(Cos(k),-1,Sin(k));
  }
  glEnd();

  /* top and bottom circles */
  /* reuse the currentTexture on top and bottom) */
  for (i=1;i>=-1;i-=2) {
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0,i,0);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0,i,0);
    for (k=0;k<=360;k+=DEF_D) {
      glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
      glVertex3f(i*Cos(k),i,Sin(k));
    }
    glEnd();
  }

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}
