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

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
  vertices3f v3f;
  int realX, realZ;

  /* return unless left mouse click and object selected */
  if ((btn != GLUT_LEFT_BUTTON || state != GLUT_DOWN)) 
    return;
  
  v3f = findMousePosition(x,y);
  mouseX = x;
  mouseY = y;
  /* TODO: after fixing preview, this should be the spot where we calculate actual
     drawing location */
  realX = (int)v3f.posX;
  realZ = (int)v3f.posZ;
  renderMode = DEF_SELECT;

  /* We're adding a new object (within the bounds of the grid) */
  if (objectSelected != 0 && 
      (realX <= 18 && realX >= -18) &&
      (realZ <= 18 && realZ >= -18)) {
    int modifiers = glutGetModifiers();
    renderMode = DEF_RENDER;
    
    /* add the object to current objects */
    current_objects[lastCurrentObject][0] = objectSelected;
    current_objects[lastCurrentObject][1] = realX;
    current_objects[lastCurrentObject][2] = 0;
    current_objects[lastCurrentObject][3] = realZ;
    current_objects[lastCurrentObject][4] = currentTextureSelected;
    /* red, green, blue */
    current_objects[lastCurrentObject][5] = currentRed;
    current_objects[lastCurrentObject][6] = currentGreen;
    current_objects[lastCurrentObject][7] = currentBlue;

    /* increment red, then green, the blue to get unique composite RGBs 
       for our object selection
     */
    currentRed += 10;
    if (currentRed > 255) {
      currentRed = 5;
      currentGreen += 10;
      if (currentGreen > 255) {
	currentGreen = 5;
	currentBlue += 10;
	if (currentBlue > 255) {
	  currentBlue = 5;
	}
      }
    }
    if (debug) printf("just added object id: %d\n",lastCurrentObject);

    /* increment last current object, we are limiting to 30 objects, so reset if at 30 */
    lastCurrentObject++;
    if (lastCurrentObject == DEF_CURRENT_OBJS_SIZE) lastCurrentObject = 0;
    /* reset object selected back to default unless shift key is held 
       this should be a bitwise &, in case multiple modifiers are pressed */
    if (modifiers != GLUT_ACTIVE_SHIFT) {
      objectSelected = DEF_OBJ_SEL;
      /* TODO: check preview mode stuff */
      preview_object[0] = DEF_OBJ_SEL;
    }
  }

  redisplayAll();
}

/*
 *  Display the mouse position
 *  TODO: show opacity-based object where drawing it
 */ 
void screenPmotion(int x, int y)
{
  if (preview && objectSelected != DEF_OBJ_SEL) {
    vertices3f v3f= findMousePosition(x,y);
    /*
    int newX = (int) v3f.posX;
    int newZ = (int) v3f.posZ;
    double finalX = (double) newX + 0.5;
    double finalZ = (double) newZ + 0.5;*/
    /* TODO: fix drop location to round posX and posY to closest 0.5 */
    /*    printf("%f %f\n",v3f.posX,v3f.posZ);
    printf("%d %d\n",newX, newZ);
    printf("%f %f\n",finalX, finalZ);*/
    preview_object[0] = objectSelected;
    preview_object[1] = (int) v3f.posX; //finalX;
    preview_object[2] = 0;
    preview_object[3] = (int) v3f.posZ; //finalZ;
    preview_object[4] = currentTextureSelected;

    redisplayAll();
  }
}

