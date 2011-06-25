#include "project.h"

/*
 *  GENERAL GLUT COMMANDS
 */

/*
 *  findMousePosition
 *  ------
 *  Determines the OpenGL mouse position based on world coordinates 
 */
point findMousePosition(int x, int y)
{
  point point;
  GLfloat winX, winY, winZ;
  GLdouble posX, posY, posZ;
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];

  /* get the necessary values from OPEN_GL */
  glGetIntegerv(GL_VIEWPORT, viewport);
  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);

  winX = (float)x;
  winY = (float)viewport[3]-(float)y-1;
  /* sets winZ */
  glReadPixels(x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

  /* sets posX, posY, posZ */
  gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

  /* show debug info */
  if (debug) {
    printf("\nobject selected: %d\n", objectSelected);
    printf("x y: %d %d\n", x, y);
    printf("vp : %d %d\n", viewport[2], viewport[3]);
    printf("win: %f %f %f\n", winX, winY, winZ);
    printf("pos: %f %f %f\n", posX, posY, posZ);
  }

  point.x = posX;
  point.y = posY;
  point.z = posZ;

  return point;
}

/*
 *  findPreviewPosition
 *  ------
 *  Finds the position that is in the preview_points list, which are the 
 *  only valid places to place a tower
 */
point findPreviewPosition(int x, int y)
{
  point p = findMousePosition(x,y);
  point returnP;
  int finalX = (int)p.x;
  int finalZ = (int)p.z;
  int i,j,exists;
  /* default "bad" values */
  returnP.x = DEF_BAD_POINT;
  returnP.y = DEF_BAD_POINT;
  returnP.z = DEF_BAD_POINT;
  exists = 0;

  /* current objects size is the size of the valid points */
  for (i=0; i < DEF_CURRENT_OBJS_SIZE; i++) {
    /* check +/-2 from the exact point to speed up the grid checking */
    if (finalX >= (preview_points[i].x-2) && finalX <= (preview_points[i].x+2) &&
	finalZ >= (preview_points[i].z-2) && finalZ <= (preview_points[i].z+2)) {
      /* check current objects to make sure there isn't a tower there already */
      for(j=0; j < Length(towers);j++) {
	if (towers[j].translation.x == preview_points[i].x &&
	    towers[j].translation.z == preview_points[i].z) {
	  /* a tower already exists in this location, break */
	  exists = 1;
	  break;
	}
      }
      /* tower doesn't exist, place the preview point */
      if (!exists) {
	returnP.x = preview_points[i].x;
	returnP.y = 0;
	returnP.z = preview_points[i].z;
	return returnP;
      }
    }
  }
  return returnP;
}

/*
 *  idle
 *  ------
 *  If we have movement on, then the light spins and the tower tops spin
 */
void idle(void)
{
  static int lastTime = 0;
  int time = glutGet(GLUT_ELAPSED_TIME);
  double t = time/1000.0;
  if (lastTime == 0 || time >= lastTime + 30) {
    lastTime = time;
    moveLight(t);
    moveTowerTops(t);

    moveMinions();
    redisplayAll();
  }
}

/* 
 *  incrementRGB
 *  ------
 *  Increment red, then green, the blue to get unique composite RGBs 
 *  for our object selection 
 */
void incrementCurrentRGB(void)
{
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
}

/*  
 *  processPicks
 *  ------
 *  Determines the pixel color and compares that to our object colors to determine
 *  which was picked
 */
void processPicks(void)
{
  int i;
  GLint viewport[4];
  GLubyte pixel[3];
  glGetIntegerv(GL_VIEWPORT,viewport);
  glReadPixels(mouseX,viewport[3]-mouseY,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);
  if (debug) printf("R:%d  G:%d  B:%d\n",pixel[0],pixel[1],pixel[2]);
  for (i = 0; i < Length(towers); i++){
    GLint red,green,blue;
    red = towers[i].rgb.r;
    green = towers[i].rgb.g;
    blue = towers[i].rgb.b;
    /* Found the object we need, break out of loop */
    if (pixel[0] == red && pixel[1] == green && pixel[2] == blue) {
      objectPicked = i;
      break;
    }
    /* Object not found, set to default */
    else {
      objectPicked = DEF_OBJ_PICKED;
    }
  }
}

/*
 *  redisplayAll
 *  ------
 *  This is called whenever we need to draw the display
 */
void redisplayAll(void)
{
  glutSetWindow(screen);

  /* set screen position, reshape */
  screenReshape(windowWidth-DEF_SIDEBAR_WIDTH-DEF_SPACER, windowHeight);
  glutPostRedisplay();

  /* set sidebar position, reshape */
  glutSetWindow(sidebar);
  sidebarReshape(windowWidth, windowHeight);
  glutPostRedisplay();
}

/*  
 *  reset
 *  ------
 *  reset all values back to defaults 
 */
void reset()
{
  /* reset the current objects with 0's and default objects */
  int i;
  for (i=0;i<DEF_CURRENT_OBJS_SIZE;i++) {
    towers[i].id = 0;
    towers[i].type = 0;
    towers[i].translation.x = 0;
    towers[i].translation.y = 0;
    towers[i].translation.z = 0;
    towers[i].texture = 0;
    towers[i].rgb.r = 0;
    towers[i].rgb.g = 0;
    towers[i].rgb.b = 0;
  }
  /*
  if (drawDefaults)
    for (i=0;i<Length(default_objects);i++)
      towers[i] = default_objects[i];

  if (drawDefaults) lastCurrentObject = DEF_LAST_CURRENT_OBJECT+Length(default_objects);
  else lastCurrentObject = DEF_LAST_CURRENT_OBJECT;*/

  /* reset object selection */
  objectSelected    = DEF_OBJ_SEL;
  objectPicked      = DEF_OBJ_PICKED;
  preview           = DEF_PREVIEW;
  currentRed   = DEF_CURRENT_RED;
  currentGreen = DEF_CURRENT_GREEN;
  currentBlue  = DEF_CURRENT_BLUE;

  /* reset the rest */
  asp  = DEF_ASP;
  dim  = DEF_DIM;
  th   = DEF_TH;
  ph   = DEF_PH;
  fov  = DEF_FOV;
  ecX  = DEF_ECX;
  ecY  = DEF_ECY;
  ecZ  = DEF_ECZ;  

  axes = DEF_AXES;
  vals = DEF_VALS;
  fontStyle    = DEF_FONT_STYLE;

  /* reset animation */
  moveLightB     = DEF_MOVE_LIGHT;
  lightPh        = DEF_L_PH;
  moveMinionsB   = DEF_MOVE_MINIONS;
  moveTowerTopsB = DEF_MOVE_TOWER_TOPS;
  towerTh        = DEF_TOWER_TH;

  /* reset lighting */
  light     = DEF_LIGHT;
  distance  = DEF_DISTANCE;
  ambient   = DEF_AMBIENT;
  diffuse   = DEF_DIFFUSE;
  emission  = DEF_EMISSION;
  specular  = DEF_SPECULAR;
  shininess = DEF_SHININESS;
  lightY    = DEF_L_Y;

  /* reset textures */
  currentTexture = TEX_DEFAULT;
  currentTextureSelected = TEX_DEFAULT;
}
