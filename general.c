#include "project.h"

/*
 *  GENERAL GLUT COMMANDS
 */

/*
 *  findMousePosition
 *  ------
 *  Determines the OpenGL mouse position based on world coordinates 
 */
vertices3f findMousePosition(int x, int y)
{
  vertices3f vertices;
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

  vertices.posX = posX;
  vertices.posY = posY;
  vertices.posZ = posZ;

  return vertices;
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
  if (lastTime == 0 || time >= lastTime + 20) {
    lastTime = time;
    if (move) lightPh = fmod(45*t,360.0);
    if (topsRotate) towerTh = fmod(90*t,360.0);
    if (move || topsRotate) redisplayAll();
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
  for (i = 0; i < Length(current_objects); i++){
    GLint red,green,blue;
    red = current_objects[i][5];
    green = current_objects[i][6];
    blue = current_objects[i][7];
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
  /* 
     At one point, for some reason related to textures, I was losing the window, 
     so I was re-getting it here. 
     *** a fix may be available here: http://graphics.tudelft.nl/~paul/glut.html
     It's currently working without issue.
     window = glutGetWindow();
   */
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
  int i,j;
  for (i=0;i<DEF_CURRENT_OBJS_SIZE;i++)
    for (j=0;j<DEF_CURRENT_OBJS_ATRS;j++)
      current_objects[i][j] = 0;
  if (drawDefaults)
    for (i=0;i<Length(default_objects);i++)
      for(j=0;j<DEF_CURRENT_OBJS_ATRS;j++)
	current_objects[i][j] = default_objects[i][j];
  /* reset object selection */
  if (drawDefaults) lastCurrentObject = DEF_LAST_CURRENT_OBJECT+Length(default_objects);
  else lastCurrentObject = DEF_LAST_CURRENT_OBJECT;
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
  axes = DEF_AXES;
  vals = DEF_VALS;
  fontStyle    = DEF_FONT_STYLE;
  topsRotate   = DEF_TOPS_ROTATE;
  towerTh      = DEF_TOWER_TH;

  /* reset lighting */
  light     = DEF_LIGHT;
  move      = DEF_MOVE;
  distance  = DEF_DISTANCE;
  ambient   = DEF_AMBIENT;
  diffuse   = DEF_DIFFUSE;
  emission  = DEF_EMISSION;
  specular  = DEF_SPECULAR;
  shininess = DEF_SHININESS;
  lightPh   = DEF_L_PH;
  lightY    = DEF_L_Y;

  /* reset textures */
  currentTexture = TEX_DEFAULT;
  currentTextureSelected = TEX_DEFAULT;
}
