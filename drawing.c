#include "project.h"

/*
 *  BEGIN DISPLAY AND DRAW FUNCTIONS
 */

/*
 *  drawAxes
 *  ------
 *  Draws the axes if desired
 */
void drawAxes(void)
{
  /* axes length */
  const double len=2.0;

  /*  Draw axes - no lighting */
  if (axes) {
    glDisable(GL_LIGHTING);
    glColor3fv(white);
    glBegin(GL_LINES);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(len,0.0,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,len,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,0.0,len);
    glEnd();
    /*  Label axes */
    glRasterPos3d(len,0.0,0.0);
    print("X");
    glRasterPos3d(0.0,len,0.0);
    print("Y");
    glRasterPos3d(0.0,0.0,len);
    print("Z");
  }
}

/*
 *  drawParameters
 *  ------
 *  Draws the parameters if desired
 */
void drawParameters(void)
{
  if (vals) {
    glColor3fv(white);
    /*  Display parameters */
    printAt(5,5,"Angle=%d,%d  Dim=%.1f FOV=%d Light=%s",
	    th,ph,dim,fov,light?"On":"Off");
    if (light) {
      printAt(5,45,"Distance=%d Elevation=%.1f",distance,lightY);
      printAt(5,25,"Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",
	      ambient,diffuse,specular,emission,shinyvec[0]);
    }
  }
}

/*
 *  drawGrid
 *  ------
 *  Draws the grid if desired
 */
void drawGrid(void)
{
  /*  Draw grid - no lighting */
  if (grid) {
    int i,j;
    glDisable(GL_LIGHTING);
    glColor3fv(white);
    glBegin(GL_LINES);
    /* horizontal z */
    for (i=-19;i<20;i+=2){
      for (j=-19;j<20;j+=38){
	glVertex3d(i,-2.75,j);
      }
    }
    /* horizontal x */
    for (i=-19;i<20;i+=2){
      for (j=-19;j<20;j+=38){
	glVertex3d(j,-2.75,i);
      }
    }

    glEnd();
  }
}

/*
 *  drawBackground
 *  ------
 *  Draws the background skybox
 */
void drawBackground(double D)
{
  glColor3fv(white);
  glEnable(GL_TEXTURE_2D);

  /* Sides */
  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_RIGHT]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(-D,-D,-D);
  glTexCoord2f(1,0); glVertex3f(+D,-D,-D);
  glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
  glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_FRONT]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(+D,-D,-D);
  glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
  glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
  glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
  glEnd();
  
  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_LEFT]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(+D,-D,+D);
  glTexCoord2f(1,0); glVertex3f(-D,-D,+D);
  glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
  glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_BACK]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
  glTexCoord2f(1,0); glVertex3f(-D,-D,-D);
  glTexCoord2f(1,1); glVertex3f(-D,+D,-D);
  glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
  glEnd();

  /* Up */
  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_UP]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(-D,+D,-D);
  glTexCoord2f(1,0); glVertex3f(+D,+D,-D);
  glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
  glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
  glEnd();

  /* Down */
  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_DOWN]);
  glBegin(GL_QUADS);
  glTexCoord2f(1,1); glVertex3f(+D,-D,-D);
  glTexCoord2f(0,1); glVertex3f(-D,-D,-D);
  glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
  glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}

/*
 *  drawLight 
 *  ------
 *  Draws the light (rotating sphere) if desired
 */
void drawLight(void)
{
  /*  Light switch */
  if (light) {
    /*  Translate intensity to color vectors */
    float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
    float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
    float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
    /*  Light position */
    float Position[]  = {lightY,distance*Sin(lightPh),distance*Cos(lightPh),1.0};
    /*  Draw light position as sphere (still no lighting here) */
    glColor3fv(white);
    sphere(Position[0],Position[1],Position[2] , 0.1,0);
    /*  OpenGL should normalize normal vectors */
    glEnable(GL_NORMALIZE);
    /*  Enable lighting */
    glEnable(GL_LIGHTING);
    /*  glColor sets ambient and diffuse color materials */
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    /*  Enable light 0 */
    glEnable(GL_LIGHT0);
    /*  Set ambient, diffuse, specular components and position of light 0 */
    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);
  }
  else
    glDisable(GL_LIGHTING);
}

/*
 *  drawBoard
 *  ------
 *  draw the board
 */
void drawBoard(void)
{
  board();
}

/*
 *  drawPath
 *  ------
 *  fixed path for the game.
 */
void drawPath(void)
{
  //TODO: stub for the path drawing
}

/*
 *  drawForests
 *  ------
 *  Draws forestry
 */
void drawForests(void)
{
  /* backside forests */
  evergreenForest1(-20,0,15, 1,1,1, 90);
  /* gap here for keep */
  evergreenForest1(-20,0,-20, 1,1,1, 90);

  /* rightside forests */
  evergreenForest1(-15,0,-20, 1,1,1, 0);
  evergreenForest1(-5,0,-20, 1,1,1, 0);
  evergreenForest1(5,0,-20, 1,1,1, 0);
  evergreenForest1(15,0,-20, 1,1,1, 0);
  evergreenForest1(20,0,-20, 1,1,1, 0);

  /* frontside forests */
  evergreenForest1(20,0,-15, 1,1,1, -90);
  evergreenForest1(20,0,-10, 1,1,1, -90);
  /* gap here for minions */
  evergreenForest1(20,0,10, 1,1,1, -90);
  evergreenForest1(20,0,20, 1,1,1, -90);

  /* leftside forests */
  evergreenForest1(15,0,20, 1,1,1, 180);
  evergreenForest1(10,0,20, 1,1,1, 180);
  evergreenForest1(0,0,20, 1,1,1, 180);
  evergreenForest1(-10,0,20, 1,1,1, 180);
  evergreenForest1(-20,0,20, 1,1,1, 180);
}

/*
 *  drawKeep
 *  ------
 *  Draws the keep
 */
void drawKeep(void)
{
  keep(-30,0,0, 1,1,1, 0);
}

/*
 *  drawMinions
 *  ------
 *  draw the minions
 */
void drawMinions(void)
{
  //TODO: stub for minions
}

/*
 *  drawObjects
 *  ------
 *  draw the current objects (towers)
 */
void drawObjects(void)
{
  int i;

  /* preview object */
  if (preview_object[0] != DEF_OBJ_SEL) {
    GLfloat oType,oX,oY,oZ;
    oType = preview_object[0];
    oX = preview_object[1];
    oY = preview_object[2];
    oZ = preview_object[3];
    currentTexture = preview_object[4];

    if (oType == OBJ_BASIC) basicTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_ADV) advancedTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_CONE) coneTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_ADV_CONE) advancedConeTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_SQUARE) squareTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_ADV_SQUARE) advancedSquareTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_FIRE) fireTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_FIRE2) fireTower2(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_ICE) iceTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_ICE2) iceTower2(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_EARTH) earthTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_EARTH2) earthTower2(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_POISON) poisonTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_POISON2) poisonTower2(oX,oY,oZ, 1,1,1, 0);
    currentTexture = TEX_DEFAULT;
  }

  /* current objects */
  if (Length(current_objects) > 0) {
    for (i = 0; i < Length(current_objects); i++){
      GLfloat oType,oX,oY,oZ;
      GLint red,green,blue;
      oType = current_objects[i][0];
      oX = current_objects[i][1];
      oY = current_objects[i][2];
      oZ = current_objects[i][3];
      currentTexture = current_objects[i][4];
      red = current_objects[i][5];
      green = current_objects[i][6];
      blue = current_objects[i][7];

      /* draw the objects */
      if (renderMode == DEF_SELECT) {
	glDisable(GL_DITHER);
	glDisable(GL_LIGHTING);
	glColor3ub(red,green,blue);
      }
      if (oType == OBJ_BASIC) basicTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_ADV) advancedTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_CONE) coneTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_ADV_CONE) advancedConeTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_SQUARE) squareTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_ADV_SQUARE) advancedSquareTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_FIRE) fireTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_FIRE2) fireTower2(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_ICE) iceTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_ICE2) iceTower2(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_EARTH) earthTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_EARTH2) earthTower2(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_POISON) poisonTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_POISON2) poisonTower2(oX,oY,oZ, 1,1,1, 0);
      currentTexture = TEX_DEFAULT;

      if (renderMode == DEF_SELECT) {
	glEnable(GL_DITHER);
	glEnable(GL_LIGHTING);
      }
    }
  }
}

/*
 *  drawScene
 *  ------
 *  draws the entire scene
 */
void drawScene(void)
{
  drawAxes();
  drawParameters();
  drawGrid();
  drawBackground(3.5*dim);
  drawLight();
  /* anything with lighting should be drawn after the light */
  drawBoard();
  drawPath();
  drawForests();
  drawKeep();
  drawMinions();
  drawObjects();
}
