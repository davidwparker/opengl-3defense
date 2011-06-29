/*
 * Project - 3Defense
 * David Parker
 * June 21-29, 2011
 */
#include "project.h"

/*
 *  main
 *  ------
 *  main function
 */
int main(int argc,char* argv[])
{
  glutInit(&argc,argv);
  /*  Request double buffered, true color window with Z buffering */
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);
  /*  Even if you want full size, you need to specify initial size or get GLUT warning */
  glutInitWindowSize(windowWidth,windowHeight);

  window = glutCreateWindow(windowName);
  /*  I like full screen mode */
  if (DEF_FULL_SCREEN)
    glutFullScreen();
  glutDisplayFunc(windowDisplay);
  glutReshapeFunc(windowReshape);
  glutSpecialFunc(windowSpecial);
  glutKeyboardFunc(windowKey);

  reset();
  initialize();

  redisplayAll();
  glutMainLoop();
  return 0;
}
