#include "project.h"

/*
 *  BEGIN SIDEBAR SECTION GLUT COMMANDS
 */

/* 
 *  sidebarRow
 *  ------
 *  Add a row of text with: x, y, text, with optional object selected highlight
 */
void sidebarRow(int x, int y, int obj, char* text)
{
  glColor3fv(white);
  if (objectSelected == obj) glColor3f(1,0,1);
  printAt(x,y,text);
  glColor3fv(white);
}

/*
 *  sidebarDisplay
 *  ------
 *  The display for the sidebar
 *  TODO: textures for tower selection
 *  TODO: don't let user select tower unless they have enough money
 */
void sidebarDisplay(void)
{
  int line = 1;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  sidebarRow(80, windowHeight-DEF_TEXT_Y_OFFSET*line, -1, "3Defense");
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, "WAVE: %d out of %d", waveNumber, lastWave);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, "SCORE: %d", score);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, "LIVES: %d", lives);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, "MONEY: %d", money);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, "SCROLLS: %d", scrolls);

  /* These display locations need to line up with mouse clicks */
  setFont("helvetica",12);
  sidebarRow(5, windowHeight-DEF_TEXT_Y_OFFSET*++line, -1, "Select a tower to build:");
  setFont("helvetica",18);
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, DEF_OBJ_SEL, "[0] none");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_BASIC, "basic");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_ADV, "advanced");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_CONE, "cone");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_ADV_CONE, "advanced cone");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_SQUARE, "square");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_ADV_SQUARE, "advanced square");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_FIRE, "[1] fire");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_FIRE2, "[2] advanced fire");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_ICE, "[3] ice");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_ICE2, "[4] advanced ice");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_EARTH, "[5] earth");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_EARTH2, "[6] advanced earth");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_POISON, "[7] poison");
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, OBJ_POISON2, "[8] advanced poison");

  ++line;
  setFont("helvetica",12);
  glColor3fv(white);
  printAt(5, windowHeight-DEF_TEXT_Y_OFFSET*++line, "INFO");
  printAt(5, windowHeight-DEF_TEXT_Y_OFFSET*++line, "%s",info);
  printAt(5, windowHeight-DEF_TEXT_Y_OFFSET*++line, "Object Picked: %d", objectPicked);
  setFont("helvetica",18);

  glFlush();
  glutSwapBuffers();
}

/*
 *  sidebarReshape
 *  ------
 *  Reshapes the sidebar when resized
 */
void sidebarReshape(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width, height, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0.3, 0.3, 0.3, 0.0);
}

/*
 *  sidebarMouse
 *  ------
 *  Left mouse button is pressed in the sidebar
 */
void sidebarMouse(int btn, int state, int x, int y)
{
  int lineUp   = 6;
  int lineDown = 7;
  /* only left mouse button */
  if (btn != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

  /* mouse position starts at upper left */
  if (x < 180 && x>= 5) {
    if (y >= DEF_TEXT_Y_OFFSET*++lineUp+5 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=DEF_OBJ_SEL;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_BASIC;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_ADV;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_CONE;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_ADV_CONE;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_SQUARE;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_ADV_SQUARE;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_FIRE;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_FIRE2;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_ICE;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_ICE2;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_EARTH;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_EARTH2;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_POISON;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) objectSelected=OBJ_POISON2;
  }
  /* 
   * TODO: fix bug where if user clicks here instead of using keyboard that the preview
   * functionality doesn't work 
   */
  redisplayAll();
}

