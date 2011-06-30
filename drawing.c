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
  const double len=5.0;

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
    glEnable(GL_LIGHTING);
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
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2,1);
    glBegin(GL_LINES);
    /* horizontal z */
    for (i=-21;i<21;i+=2){
      for (j=-19;j<23;j+=40){
	glVertex3d(i,-2.8,j);
      }
    }
    /* horizontal x */
    for (i=-19;i<23;i+=2){
      for (j=-21;j<20;j+=40){
	glVertex3d(j,-2.8,i);
      }
    }
    glEnd();
    glDisable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_LIGHTING);
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
  path();
}

/*
 *  drawForests
 *  ------
 *  Draws forestry
 */
void drawForests(void)
{
  /* backside forests */
  evergreenForest1(-22,0,-10, 1,1,1, 90);
  /* gap here for keep */
  evergreenForest1(-22,0,-20, 1,1,1, 90);

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
  evergreenForest1(15,0,22, 1,1,1, 180);
  evergreenForest1(10,0,22, 1,1,1, 180);
  evergreenForest1(0,0,22, 1,1,1, 180);
  evergreenForest1(-10,0,22, 1,1,1, 180);
  evergreenForest1(-20,0,22, 1,1,1, 180);
}

/*
 *  drawKeep
 *  ------
 *  Draws the keep
 */
void drawKeep(void)
{
  keep(-32,0,10, 1,1,1, 0);
}

/*
 *  drawShots
 *  ------
 *  Draws the shots from the towers
 */
void drawShots(void)
{
  int i;
  for (i=0;i<Length(shots);i++) {
    if (shots[i].inPlay == 1) shotModel(shots[i]);
  }
}

/*
 *  drawMinions
 *  ------
 *  draw the minions that are in play
 *  TODO: add object selection for minions
 */
void drawMinions(void)
{
  int i,k;
  for (k=0;k<waveNumber;k++) {
    for (i=0;i<Length(waves[k].m);i++) {
      if (waves[k].m[i].inPlay == 1) minionModel(waves[k].m[i]);
    }
  }
}

/*
 *  drawObjects
 *  ------
 *  draw the current objects (towers)
 */
void drawObjects(void)
{
  int i;

  /* preview tower */
  if (preview_tower.id != DEF_OBJ_SEL) {
    tower t = {preview_tower.id,preview_tower.type,preview_tower.inPlay,
	       {preview_tower.translation.x,preview_tower.translation.y,preview_tower.translation.z},
	       {1,1,1},{0,0,0},preview_tower.texture,{1,1,1},
	       preview_tower.name,1,preview_tower.range,preview_tower.damage,
	       preview_tower.fireRate,0,preview_tower.cost};

    /* awesome opacity for the preview */
    showAttackRadius = 1;
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ONE_MINUS_DST_COLOR);
    if (t.type == OBJ_BASIC) basicTower(t);
    else if (t.type == OBJ_ADV) advancedTower(t);
    else if (t.type == OBJ_CONE) coneTower(t);
    else if (t.type == OBJ_ADV_CONE) advancedConeTower(t);
    else if (t.type == OBJ_SQUARE) squareTower(t);
    else if (t.type == OBJ_ADV_SQUARE) advancedSquareTower(t);
    else if (t.type == OBJ_FIRE) fireTower(t);
    else if (t.type == OBJ_FIRE2) fireTower2(t);
    else if (t.type == OBJ_ICE) iceTower(t);
    else if (t.type == OBJ_ICE2) iceTower2(t);
    else if (t.type == OBJ_EARTH) earthTower(t);
    else if (t.type == OBJ_EARTH2) earthTower2(t);
    else if (t.type == OBJ_POISON) poisonTower(t);
    else if (t.type == OBJ_POISON2) poisonTower2(t);
    glDisable(GL_BLEND);
    showAttackRadius = 0;
  }

  /* towers */
  for (i = 0; i < Length(towers); i++) {
    if (towers[i].inPlay) {
      tower t = {0,towers[i].type,towers[i].inPlay,
		 {towers[i].translation.x,towers[i].translation.y,towers[i].translation.z},
		 {1,1,1},{0,0,0},towers[i].texture,
		 {towers[i].rgb.r,towers[i].rgb.g,towers[i].rgb.b},
		 towers[i].name,towers[i].level,towers[i].range,towers[i].damage,
		 towers[i].fireRate,towers[i].lastFired,towers[i].cost,towers[i].description};

      /* draw the objects */
      if (renderMode == DEF_SELECT) {
	glDisable(GL_DITHER);
	glDisable(GL_LIGHTING);
	glColor3ub(towers[i].rgb.r,towers[i].rgb.g,towers[i].rgb.b);
      }
      if (t.type == OBJ_BASIC) basicTower(t);
      else if (t.type == OBJ_ADV) advancedTower(t);
      else if (t.type == OBJ_CONE) coneTower(t);
      else if (t.type == OBJ_ADV_CONE) advancedConeTower(t);
      else if (t.type == OBJ_SQUARE) squareTower(t);
      else if (t.type == OBJ_ADV_SQUARE) advancedSquareTower(t);
      else if (t.type == OBJ_FIRE) fireTower(t);
      else if (t.type == OBJ_FIRE2) fireTower2(t);
      else if (t.type == OBJ_ICE) iceTower(t);
      else if (t.type == OBJ_ICE2) iceTower2(t);
      else if (t.type == OBJ_EARTH) earthTower(t);
      else if (t.type == OBJ_EARTH2) earthTower2(t);
      else if (t.type == OBJ_POISON) poisonTower(t);
      else if (t.type == OBJ_POISON2) poisonTower2(t);
      
      if (renderMode == DEF_SELECT) {
	glEnable(GL_DITHER);
	glEnable(GL_LIGHTING);
      }
    }
  }
}

/*
 *  drawShadows
 *  ------
 *  draw shadows for minions and objects on the screen
 */
void drawShadows()
{
  /* position of the light */
  float Position[]  = {lightY,distance*Sin(lightPh),distance*Cos(lightPh),1.0};

  /* Save what is glEnabled */
  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_LIGHTING);
  /* Enable stencil operations */
  glEnable(GL_STENCIL_TEST);

  /*
   *  Step 1:  Set stencil buffer to 1 where there are shadows
   */
  /* Existing value of stencil buffer doesn't matter */
  glStencilFunc(GL_ALWAYS,1,0xFFFFFFFF);
  /*  Set the value to 1 (REF=1 in StencilFunc)  
      only if Z-buffer would allow write */
  glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
  /*  Make Z-buffer and color buffer read-only */
  glDepthMask(0);
  glColorMask(0,0,0,0);
  
  /*  Draw flattened scene */
  glPushMatrix();
  shadowProjection(Position,E,N);
  /* only draw objects that we want shadows for */
  drawForests();
  drawKeep();
  drawMinions();
  drawObjects();

  glPopMatrix();
  /*  Make Z-buffer and color buffer read-write */
  glDepthMask(1);
  glColorMask(1,1,1,1);
  
  /*
   *  Step 2:  Draw shadow masked by stencil buffer
   */
  /*  Set the stencil test draw where stencil buffer is > 0 */
  glStencilFunc(GL_LESS,0,0xFFFFFFFF);
  /*  Make the stencil buffer read-only */
  glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
  /*  Enable blending */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(0,0,0,0.5);
  /*  Draw the shadow over the entire floor */
  glBegin(GL_QUADS);
  glVertex3f(-DEF_D_FLOOR,DEF_Y_FLOOR,-DEF_D_FLOOR);
  glVertex3f(+DEF_D_FLOOR,DEF_Y_FLOOR,-DEF_D_FLOOR);
  glVertex3f(+DEF_D_FLOOR,DEF_Y_FLOOR,+DEF_D_FLOOR);
  glVertex3f(-DEF_D_FLOOR,DEF_Y_FLOOR,+DEF_D_FLOOR);
  glEnd();

  /* Undo glEnables */
  glPopAttrib();
}

/*
 *  drawScene
 *  ------
 *  draws the entire scene
 */
void drawScene(void)
{
  if (renderMode == DEF_RENDER) {
    drawAxes();
    drawGrid();
    drawParameters();
    drawBackground(3.5*dim);
    drawLight();
    /* anything with lighting should be drawn after the light */
    drawBoard();
    drawPath();
    drawForests();
    drawKeep();
    drawShots();
  }
  drawMinions();
  drawObjects();
  /* only draw shadows on rendering, not selection */
  if (renderMode == DEF_RENDER) drawShadows();
}
