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
    renderMode = DEF_RENDER;
    /* game data */
    if (money >= tower_data[objectSelected-1].cost) {
      info = "cha-ching$ thanks buddy.";
      setCurrentTowerData(objectSelected);
    } else {
      info = "Not enough $$$.";
      objectSelected = DEF_OBJ_SEL;
      preview_tower.id = DEF_OBJ_SEL;
    }

    if (objectSelected != DEF_OBJ_SEL) {
      tower t = {objectSelected,objectSelected,1,
		 {p.x,p.y,p.z},{1,1,1},{0,0,0},currentTextureSelected,
		 {currentRed,currentGreen,currentBlue},
		 /* name,level,range,damage,fireRate,lastFired,cost,description */
		 currentTowerName,1,currentTowerRange,currentTowerDamage,
		 currentTowerFireRate,0,currentTowerCost,"Description"};
      towers[lastCurrentObject] = t;
      modifyMoney(0,currentTowerCost);

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
      preview_tower.id = objectSelected;
      preview_tower.type = objectSelected;
      preview_tower.inPlay = 1;
      preview_tower.translation.x = p.x;
      preview_tower.translation.y = p.y;
      preview_tower.translation.z = p.z;
      preview_tower.texture = tower_data[objectSelected-1].texture;
      preview_tower.name = tower_data[objectSelected-1].name;
      preview_tower.range = tower_data[objectSelected-1].range;
      preview_tower.damage = tower_data[objectSelected-1].damage;
      preview_tower.fireRate = tower_data[objectSelected-1].fireRate;
      preview_tower.cost = tower_data[objectSelected-1].cost;

      redisplayAll();
    }
  }
}

