#include "project.h"

/*
 *  BEGIN SCREEN SECTION GLUT COMMANDS
 */

/*
 *  displayInit
 *  -------
 *  Initializes display
 */
void displayInit(void)
{
  /*  Set the font style */
  setFont("helvetica", 18);

  glClearColor(0.8,0.8,0.8,0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
}

/*
 *  displayEye
 *  ------
 *  Sets where the user is looking 
 */
void displayEye(void)
{
  /*  Perspective - set eye position */
  double Ex = -2*dim*Sin(th)*Cos(ph);
  double Ey = +2*dim        *Sin(ph);
  double Ez = +2*dim*Cos(th)*Cos(ph);
  gluLookAt(Ex+ecX,Ey,Ez+ecZ, ecX,ecY,ecZ , 0,Cos(ph),0);
}

/*
 *  screenDisplay
 *  ------
 *  Display the actual scene
 */
void screenDisplay(void)
{
  /*  Setup, place eye position */
  displayInit();
  displayEye();

  /*  Draw scene */
  drawScene();

  /*  Object selection */
  /*  First pass picking mode, then render mode */
  /*  TODO: objectSelected and then deleting */
  if (renderMode == DEF_SELECT) {
    processPicks();
    renderMode = DEF_RENDER;
  }
  else {
    /*  Flush and swap */
    glFlush();
    glutSwapBuffers();
  }
  
  errCheck("display sanity check");
}

/*
 *  screenProject
 *  ------
 *  Projection determination method
 */
void screenProject(double fov, double asp, double dim)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov,asp,dim/16,16*dim);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*
 *  screenReshape
 *  ------
 *  Resize for the display screen area
 */
void screenReshape(int width, int height)
{
  /* set the aspect ratio */
  asp = (height>0) ? (double)width/height : 1;
  windowHeight = height;

  /*  Set the viewport to the entire window */
  glViewport(0,0, width,height);
  screenProject(fov,asp,dim);
}

/*
 *  screenMouse
 *  ------
 *  If an object is selected, left-click the mouse in order to place it
 *  If an object is not selected, left-click mouse on tower to select it
 *  (this functionality actually happens in screenDisplay/drawObjects)
 */ 
void screenMouse(int btn, int state, int x, int y)
{
  point p;
  /* return unless left mouse click and object selected */
  if ((btn != GLUT_LEFT_BUTTON || state != GLUT_DOWN)) 
    return;
  
  p = findPreviewPosition(x,y);
  mouseX = x;
  mouseY = y;
  renderMode = DEF_SELECT;

  /* We're adding a new object */ 
  if (objectSelected != DEF_OBJ_SEL && p.x != DEF_BAD_POINT) {
    int modifiers = glutGetModifiers();
    char *towerName = "";
    int towerRange = 0;
    int towerDamage = 0;
    int towerFireRate = 0;
    int towerCost = 0;
    renderMode = DEF_RENDER;
    /* game data - TODO: this should be in globals or somewhere permanent 
       this needs to be refactored big time */
    if (objectSelected == OBJ_BASIC) {
      if (money >= 10) {
	currentTextureSelected = TEX_BRICK;
	towerName = "Basic";
	towerRange = 5;
	towerDamage = 3;
	towerFireRate = 4;
	towerCost = 10;
      } else {
	info = "Not enough $$$. Requires $10.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    else if (objectSelected == OBJ_ADV) {
      if (money >= 15) {
	currentTextureSelected = TEX_BRICK;
	towerName = "Advanced";
	towerRange = 7;
	towerDamage = 4;
	towerFireRate = 4;
	towerCost = 15;
      } else {
	info = "Not enough $$$. Requires $15.";
	objectSelected = DEF_OBJ_SEL;
      }
    } 
    else if (objectSelected == OBJ_CONE) {
      if (money >= 20) {
	currentTextureSelected = TEX_BRICK;
	towerName = "Cone";
	towerRange = 7;
	towerDamage = 6;
	towerFireRate = 4;
	towerCost = 20;
      } else {
	info = "Not enough $$$. Requires $20.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    else if (objectSelected == OBJ_ADV_CONE) {
      if (money >= 25) {
	currentTextureSelected = TEX_BRICK;
	towerName = "Advanced Cone";
	towerRange = 9;
	towerDamage = 6;
	towerFireRate = 4;
	towerCost = 25;
      } else {
	info = "Not enough $$$. Requires $25.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    else if (objectSelected == OBJ_SQUARE) {
      if (money >= 30) {
	currentTextureSelected = TEX_BRICK;
	towerName = "Square";
	towerRange = 9;
	towerDamage = 6;
	towerFireRate = 3;
	towerCost = 30;
      } else {
	info = "Not enough $$$. Requires $30.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    else if (objectSelected == OBJ_ADV_SQUARE) {
      if (money >= 35) {
	currentTextureSelected = TEX_BRICK;
	towerName = "Advanced Square";
	towerRange = 10;
	towerDamage = 6;
	towerFireRate = 3;
	towerCost = 35;
      } else {
	info = "Not enough $$$. Requires $35.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    else if (objectSelected == OBJ_FIRE) {
      if (money >= 40) {
	currentTextureSelected = TEX_FIRE;
	towerName = "Fire";
	towerRange = 12;
	towerDamage = 4;
	towerFireRate = 3;
	towerCost = 40;
      } else {
	info = "Not enough $$$. Requires $40.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    else if (objectSelected == OBJ_FIRE2) {
      if (money >= 45) {
	currentTextureSelected = TEX_FIRE;
	towerName = "Advanced Fire";
	towerRange = 12;
	towerDamage = 6;
	towerFireRate = 3;
	towerCost = 45;
      } else {
	info = "Not enough $$$. Requires $45.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    else if (objectSelected == OBJ_ICE) {
      if (money >= 50) {
	currentTextureSelected = TEX_ICE;
	towerName = "Ice";
	towerRange = 12;
	towerDamage = 5;
	towerFireRate = 4;
	towerCost = 50;
      } else {
	info = "Not enough $$$. Requires $50.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    else if (objectSelected == OBJ_ICE2) {
      if (money >= 55) {
	currentTextureSelected = TEX_ICE;
	towerName = "Advanced Ice";
	towerRange = 12;
	towerDamage = 7;
	towerFireRate = 4;
	towerCost = 55;
      } else {
	info = "Not enough $$$. Requires $55.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    else if (objectSelected == OBJ_EARTH) {
      if (money >= 60) {
	currentTextureSelected = TEX_EARTH;
	towerName = "Earth";
	towerRange = 10;
	towerDamage = 8;
	towerFireRate = 6;
	towerCost = 60;
      } else {
	info = "Not enough $$$. Requires $60.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    else if (objectSelected == OBJ_EARTH2) {
      if (money >= 65) {
	currentTextureSelected = TEX_EARTH;
	towerName = "Advanced Earth";
	towerRange = 12;
	towerDamage = 10;
	towerFireRate = 6;
	towerCost = 65;
      } else {
	info = "Not enough $$$. Requires $65.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    else if (objectSelected == OBJ_POISON) {
      if (money >= 70) {
	currentTextureSelected = TEX_POISON;
	towerName = "Poison";
	towerRange = 10;
	towerDamage = 6;
	towerFireRate = 3;
	towerCost = 70;
      } else {
	info = "Not enough $$$. Requires $70.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    else if (objectSelected == OBJ_POISON2) {
      if (money >= 75) {
	currentTextureSelected = TEX_POISON;
	towerName = "Advanced Poison";
	towerRange = 12;
	towerDamage = 8;
	towerFireRate = 3;
	towerCost = 75;
      } else {
	info = "Not enough $$$. Requires $75.";
	objectSelected = DEF_OBJ_SEL;
      }
    }
    tower t = {objectSelected,objectSelected,1,
	       {p.x,p.y,p.z},{1,1,1},{0,0,0},currentTextureSelected,
	       {currentRed,currentGreen,currentBlue},
	       /* name,level,range,damage,fireRate,lastFired,cost,description */
	      towerName,1,towerRange,towerDamage,towerFireRate,0,towerCost,"Description"};
    towers[lastCurrentObject] = t;
    modifyMoney(0,towerCost);

    /* increment the rgb for object selection */
    incrementCurrentRGB();

    /* increment last current object, we are limiting to 57 objects, so reset if at 57 */
    if (debug) printf("just added object id: %d\n",lastCurrentObject);
    lastCurrentObject++;
    if (lastCurrentObject == DEF_CURRENT_OBJS_SIZE) lastCurrentObject = 0;

    /* reset object selected back to default unless shift key is held 
       this should be a bitwise &, in case multiple modifiers are pressed */
    if (modifiers != GLUT_ACTIVE_SHIFT) {
      objectSelected = DEF_OBJ_SEL;
      preview_tower.id = DEF_OBJ_SEL;
    }
  }

  redisplayAll();
}

/*
 *  screenPmotion
 *  ------
 *  If preview mode is on, then display where the tower will be placed
 */ 
void screenPmotion(int x, int y)
{
  if (preview && objectSelected != DEF_OBJ_SEL) {
    point p = findPreviewPosition(x,y);
    if (p.x != DEF_BAD_POINT) {
      char *towerName = "";
      int towerRange = 0;
      int towerDamage = 0;
      int towerFireRate = 0;
      int towerCost = 0;
      preview_tower.id = objectSelected;
      preview_tower.type = objectSelected;
      preview_tower.inPlay = 1;
      preview_tower.translation.x = p.x;
      preview_tower.translation.y = p.y;
      preview_tower.translation.z = p.z;
      preview_tower.texture = currentTextureSelected;
      /* TODO: Refactor this */
      if (objectSelected == OBJ_BASIC) {
	currentTextureSelected = TEX_BRICK;
	towerName = "Basic";
	towerRange = 5;
	towerDamage = 3;
	towerFireRate = 4;
	towerCost = 10;
      } 
      else if (objectSelected == OBJ_ADV) {
	currentTextureSelected = TEX_BRICK;
	towerName = "Advanced";
	towerRange = 7;
	towerDamage = 4;
	towerFireRate = 4;
	towerCost = 15;
      } 
      else if (objectSelected == OBJ_CONE) {
	currentTextureSelected = TEX_BRICK;
	towerName = "Cone";
	towerRange = 7;
	towerDamage = 6;
	towerFireRate = 4;
	towerCost = 20;
      }
      else if (objectSelected == OBJ_ADV_CONE) {
	currentTextureSelected = TEX_BRICK;
	towerName = "Advanced Cone";
	towerRange = 9;
	towerDamage = 6;
	towerFireRate = 4;
	towerCost = 25;
      }
      else if (objectSelected == OBJ_SQUARE) {
	currentTextureSelected = TEX_BRICK;
	towerName = "Square";
	towerRange = 9;
	towerDamage = 6;
	towerFireRate = 3;
	towerCost = 30;
      }
      else if (objectSelected == OBJ_ADV_SQUARE) {
	currentTextureSelected = TEX_BRICK;
	towerName = "Advanced Square";
	towerRange = 10;
	towerDamage = 6;
	towerFireRate = 3;
	towerCost = 35;
      }
      else if (objectSelected == OBJ_FIRE) {
	currentTextureSelected = TEX_FIRE;
	towerName = "Fire";
	towerRange = 10;
	towerDamage = 4;
	towerFireRate = 3;
	towerCost = 40;
      }
      else if (objectSelected == OBJ_FIRE2) {
	currentTextureSelected = TEX_FIRE;
	towerName = "Advanced Fire";
	towerRange = 12;
	towerDamage = 6;
	towerFireRate = 3;
	towerCost = 45;
      }
      else if (objectSelected == OBJ_ICE) {
	currentTextureSelected = TEX_ICE;
	towerName = "Ice";
	towerRange = 10;
	towerDamage = 6;
	towerFireRate = 4;
	towerCost = 50;
      }
      else if (objectSelected == OBJ_ICE2) {
	currentTextureSelected = TEX_ICE;
	towerName = "Advanced Ice";
	towerRange = 12;
	towerDamage = 7;
	towerFireRate = 4;
	towerCost = 55;
      }
      else if (objectSelected == OBJ_EARTH) {
	currentTextureSelected = TEX_EARTH;
	towerName = "Earth";
	towerRange = 10;
	towerDamage = 8;
	towerFireRate = 6;
	towerCost = 60;
      }
      else if (objectSelected == OBJ_EARTH2) {
	currentTextureSelected = TEX_EARTH;
	towerName = "Advanced Earth";
	towerRange = 12;
	towerDamage = 10;
	towerFireRate = 6;
	towerCost = 65;
      }
      else if (objectSelected == OBJ_POISON) {
	currentTextureSelected = TEX_POISON;
	towerName = "Poison";
	towerRange = 10;
	towerDamage = 6;
	towerFireRate = 3;
	towerCost = 70;
      }
      else if (objectSelected == OBJ_POISON2) {
	currentTextureSelected = TEX_POISON;
	towerName = "Advanced Poison";
	towerRange = 12;
	towerDamage = 8;
	towerFireRate = 3;
	towerCost = 75;
      }
      preview_tower.name = towerName;
      preview_tower.range = towerRange;
      preview_tower.damage = towerDamage;
      preview_tower.fireRate = towerFireRate;
      preview_tower.cost = towerCost;
      redisplayAll();
    }
  }
}

