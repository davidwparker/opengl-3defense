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
 *  sidebarRowT
 *  ------
 *  Add a row of text with: x, y, text, with optional texture selected highlight
 */
void sidebarRowT(int x, int y, int obj, char* text)
{
  glColor3fv(white);
  if (currentTextureSelected == obj) glColor3f(1,0,1);
  printAt(x,y,text);
  glColor3fv(white);
}

/*
 *  sidebarDisplay
 *  ------
 *  The display for the sidebar
 */
void sidebarDisplay(void)
{
  int line = 1;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  /* These display locations need to line up with mouse clicks */
  sidebarRow(100, windowHeight-DEF_TEXT_Y_OFFSET*line, -1, "EXTRA CONTROLS");
  setFont("helvetica",12);
  sidebarRow(5, windowHeight-DEF_TEXT_Y_OFFSET*++line, -1, "Select a tower to draw:");
  setFont("helvetica",18);
  sidebarRow(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, DEF_OBJ_SEL, "none");
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
  sidebarRowT(5, windowHeight-DEF_TEXT_Y_OFFSET*++line, -1, "Select a texture for non-element tower:");
  setFont("helvetica",18);
  sidebarRowT(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, TEX_DEFAULT, "none");
  sidebarRowT(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, TEX_BRICK, "brick");
  sidebarRowT(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, TEX_FIRE, "fire");
  sidebarRowT(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, TEX_ICE, "ice");
  sidebarRowT(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, TEX_EARTH, "earth");
  sidebarRowT(10, windowHeight-DEF_TEXT_Y_OFFSET*++line, TEX_POISON, "poison");

  ++line;
  setFont("helvetica",12);
  glColor3fv(white);
  printAt(5, windowHeight-DEF_TEXT_Y_OFFSET*++line, "For best (accurate) results, ");
  printAt(5, windowHeight-DEF_TEXT_Y_OFFSET*++line, "draw on the board");
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
  int lineUp   = 1;
  int lineDown = 2;
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
    ++lineUp; ++lineUp; ++lineDown; ++lineDown;
    if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) currentTextureSelected=TEX_DEFAULT;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) currentTextureSelected=TEX_BRICK;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) currentTextureSelected=TEX_FIRE;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) currentTextureSelected=TEX_ICE;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) currentTextureSelected=TEX_EARTH;
    else if (y >= DEF_TEXT_Y_OFFSET*++lineUp+9 && y < DEF_TEXT_Y_OFFSET*++lineDown+9) currentTextureSelected=TEX_POISON;
  }

  redisplayAll();
}
