#include "project.h"

/*
 *  BEGIN INITIALIZATION FUNCTIONS
 */

/*
 *  initialize
 *  ------
 *  initializes everything
 *
 */
void initialize(void)
{
  sidebarInit();
  screenInit();
  initTextures();
  initBackground();
}

/*
 *  initTextures
 *  ------
 *  initializes all of our textures
 */
void initTextures(void)
{
  /*
    TEX_DEFAULT 0
    TEX_BRICK 1
    TEX_FIRE 2
    TEX_ICE 3
    TEX_EARTH 4
    TEX_POISON 5
    TEX_SPIKE 6
    TEX_GRASS 7
    TEX_WOOD 8
    TEX_EVERGREEN 9
    TEX_BRICK2 10
   */
  /* for some reason, order matters here (I don't know C well enough */
  textures[TEX_BRICK] = loadTexBMP("txBrick14.bmp");
  textures[TEX_FIRE] = loadTexBMP("txlava1.bmp");
  textures[TEX_ICE] = loadTexBMP("txIce7.bmp");
  textures[TEX_EARTH] = loadTexBMP("txRock5.bmp");
  textures[TEX_POISON] = loadTexBMP("txFloor38.bmp");
  textures[TEX_SPIKE] = loadTexBMP("txFloor4.bmp");
  textures[TEX_GRASS] = loadTexBMP("txGrass6.bmp");
  textures[TEX_WOOD] = loadTexBMP("txWood3.bmp");
  textures[TEX_EVERGREEN] = loadTexBMP("txGrass5.bmp");
  textures[TEX_BRICK2] = loadTexBMP("txBrick13.bmp");
  textures[TEX_CRATE] = loadTexBMP("txCrate.bmp");
}

/*
 *  initBackground
 *  ------
 *  initializes all of our textures for the skybox background
 */
void initBackground(void)
{
  /*
    BACK_FRONT 0
    BACK_RIGHT 1
    BACK_LEFT 2
    BACK_BACK 3
    BACK_UP 4
    BACK_DOWN 5
   */
  /* for some reason, order matters here (I don't know C well enough */
  backgrounds[BACK_FRONT] = loadTexBMP("txStormydays_front.bmp");
  backgrounds[BACK_RIGHT] = loadTexBMP("txStormydays_right.bmp");
  backgrounds[BACK_LEFT] = loadTexBMP("txStormydays_left.bmp");
  backgrounds[BACK_BACK] = loadTexBMP("txStormydays_back.bmp");
  backgrounds[BACK_UP] = loadTexBMP("txStormydays_up.bmp");
  backgrounds[BACK_DOWN] = loadTexBMP("txStormydays_down.bmp");
}


/*
 *  screenInit
 *  ------
 *  Setup for screen
 */
void screenInit(void)
{
  /*  Create our screen subwindow that will be used for the actual display */
  screen = glutCreateSubWindow(window, 0, 0, 
			       windowWidth-DEF_SIDEBAR_WIDTH-DEF_SPACER,
			       windowHeight-DEF_SPACER);
  glutDisplayFunc(screenDisplay);
  glutReshapeFunc(screenReshape);
  glutMouseFunc(screenMouse);
  glutPassiveMotionFunc(screenPmotion);

  glutKeyboardFunc(windowKey);
  glutSpecialFunc(windowSpecial);
}

/*
 *  sidebarInit
 *  ------
 *  Setup for sidebar
 */
void sidebarInit(void)
{
  /*  Create our sidebar that will be used for controls */
  sidebar = glutCreateSubWindow(window, windowWidth-DEF_SIDEBAR_WIDTH, 0, 
				DEF_SIDEBAR_WIDTH, windowHeight);
  glutDisplayFunc(sidebarDisplay);
  glutReshapeFunc(sidebarReshape);
  glutMouseFunc(sidebarMouse);

  glutKeyboardFunc(windowKey); 
  glutSpecialFunc(windowSpecial);
}

