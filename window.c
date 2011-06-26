#include "project.h"

/*
 *  BEGIN WINDOW SECTION GLUT COMMANDS
 */

/*
 *  windowDisplay
 *  ------
 *  GLUT call this to display the window
 */
void windowDisplay(void)
{
  /* gray for the sidebar spacer */
  glClearColor(0.8, 0.8, 0.8, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSwapBuffers();
}

/*
 *  windowKey
 *  ------
 *  GLUT calls this routine when a non-special key is pressed
 */
void windowKey(unsigned char key,int x,int y)
{
  /*  Exit on ESC */
  if (key == 27) exit(0);
  /*  reset to default screen */
  else if (key == 'r' || key == 'R') reset();
  /*  toggle axes */
  else if (key == 'x' || key == 'X') axes = 1-axes;
  /*  toggle draw defaults */
  else if (key == 'f' || key == 'F') drawDefaults = 1-drawDefaults;
  /*  toggle text values displayed at bottom */
  else if (key == 'v' || key == 'V') vals = 1-vals;
  /*  toggle grid */
  else if (key == 'g' || key == 'G') grid = 1-grid;
  /*  change field of view angle */
  else if (key == '-' && key>1) fov--;
  else if (key == '+' && key<179) fov++;
  /*  change dim */
  else if (key == 'i' && dim>1) dim -= 0.2;
  else if (key == 'I') dim += 0.2;
  /*  BEGIN ANIMATION FUNCTIANALITY */
  /*  Toggle light movement */
  else if (key == 'm') moveLightB = 1-moveLightB;
  /*  Toggle minion movement */
  else if (key == 'p') moveMinionsB = 1-moveMinionsB;
  /*  Toggle tower tops moving */
  else if (key == 'M') moveTowerTopsB = 1-moveTowerTopsB;
  /*  BEGIN LIGHTING FUNCTIONALITY */
  /*  Toggle lighting */
  else if (key == 'l' || key == 'L') light = 1-light;
  /*  Move light */
  else if (key == '<') lightPh -= 1;
  else if (key == '>') lightPh += 1;
  /*  Light elevation */
  else if (key == '[') lightY -= 0.1;
  else if (key == ']') lightY += 0.1;
  /*  Ambient level */
  else if (key == 'a' && ambient>0) ambient -= 5;
  else if (key == 'A' && ambient<100) ambient += 5;
  /*  Diffuse level */
  else if (key == 'd' && diffuse>0) diffuse -= 5;
  else if (key == 'D' && diffuse<100) diffuse += 5;
  /*  Specular level */
  else if (key == 's' && specular>0) specular -= 5;
  else if (key == 'S' && specular<100) specular += 5;
  /*  Emission level */
  else if (key == 'e' && emission>0) emission -= 5;
  else if (key == 'E' && emission<100) emission += 5;
  /*  Shininess level */
  else if (key == 'n' && shininess>-1) shininess -= 1;
  else if (key == 'N' && shininess<7) shininess += 1;
  /*  BEGIN OPTION SELECTION FUNCTIONALITY */
  /*  Select object */
  else if (key == '0') objectSelected = DEF_OBJ_SEL;
  else if (key == '1') objectSelected = OBJ_FIRE;
  else if (key == '2') objectSelected = OBJ_FIRE2;
  else if (key == '3') objectSelected = OBJ_ICE;
  else if (key == '4') objectSelected = OBJ_ICE2;
  else if (key == '5') objectSelected = OBJ_EARTH;
  else if (key == '6') objectSelected = OBJ_EARTH2;
  else if (key == '7') objectSelected = OBJ_POISON;
  else if (key == '8') objectSelected = OBJ_POISON2;
  /*  Toggle preview mode (slightly buggy) */
  else if (key == 'w' || key == 'W') {
    preview = 1-preview;
    /* Reset preview object if preview is turned off */
    if (preview == DEF_PREVIEW) preview_tower.id = DEF_OBJ_SEL;
  }
  /*  Backspace and delete key to remove currently picked object */
  else if (key == 8 || key == 127) {
    if (objectPicked != DEF_OBJ_PICKED) {
      towers[objectPicked].id = DEF_OBJ_PICKED;
      towers[objectPicked].type = DEF_OBJ_SEL;
      towers[objectPicked].translation.x = 0;
      towers[objectPicked].translation.z = 0;
      towers[objectPicked].texture = 0;
      towers[objectPicked].rgb.r = 0;
      towers[objectPicked].rgb.g = 0;
      towers[objectPicked].rgb.b = 0;
      objectPicked = DEF_OBJ_PICKED;
      if (debug) printf("Killed current object picked ID: %d\n", objectPicked);
    }
  }

  /*  Translate shininess power to value (-1 => 0) */
  shinyvec[0] = shininess<0 ? 0 : pow(2.0,shininess);

  /*  do it */
  redisplayAll();
}

/*
 *  windowSpecial
 *  ------
 *  GLUT calls this routine when an special key is pressed
 */
void windowSpecial(int key,int x,int y)
{
  int modifiers = glutGetModifiers();
  /*  If holding shift, then rotate/elevate */
  if (modifiers == GLUT_ACTIVE_SHIFT) {
    /*  Right/Left - rotate */
    if (key == GLUT_KEY_RIGHT) th += 5;
    else if (key == GLUT_KEY_LEFT) th -= 5;
    /*  Up/Down - elevation */
    else if (key == GLUT_KEY_UP) ph += 5;
    else if (key == GLUT_KEY_DOWN) ph -= 5;
  }
  /*  Otherwise, just shift the screen */
  else {
    /*  Shift */
    if (key == GLUT_KEY_RIGHT) ecZ -= .5;
    else if (key == GLUT_KEY_LEFT) ecZ += .5;
    else if (key == GLUT_KEY_UP) ecX -= .5;
    else if (key == GLUT_KEY_DOWN) ecX += .5;
  }
  
  /*  Keep angles at +/- 360 degrees */
  th %= 360;
  ph %= 360;

  /*  do it */
  redisplayAll();
}

/*
 *  windowReshape
 *  ------
 *  GLUT calls this routine when the window is resized
 */
void windowReshape(int width,int height)
{
  windowHeight = height;
  windowWidth = width;

  /* main window stuff */
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,width,height,0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* set subwindow positions */
  /* set screen position, reshape */
  glutSetWindow(screen);
  glutPositionWindow(0, 0);
  glutReshapeWindow(windowWidth-DEF_SIDEBAR_WIDTH-DEF_SPACER, windowHeight);

  /* set sidebar position, reshape */
  glutSetWindow(sidebar);
  glutPositionWindow(windowWidth-DEF_SIDEBAR_WIDTH,0);
  glutReshapeWindow(DEF_SIDEBAR_WIDTH,windowHeight);
}

/*
 *  windowVisible
 *  ------
 *  If the program is visible, then do idle function
 */
void windowVisible(int vis)
{
  glutIdleFunc(vis == GLUT_VISIBLE ? idle: NULL);
}

