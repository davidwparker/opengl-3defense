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
  initObjs();
  initMinions();
  initWaves();
  initShots();
  initPath();
  initPreviewPoints();
  initDefaultTowers();
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
    TEX_CRATE 11
    TEX_STREET1 12
    TEX_STREET2 13
    TEX_STREET3 14
    TEX_STREET4 15
    TEX_STREET5 16
    TEX_STREET6 17
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
  textures[TEX_STREET1] = loadTexBMP("txStreet1.bmp");
  textures[TEX_STREET2] = loadTexBMP("txStreet2.bmp");
  textures[TEX_STREET3] = loadTexBMP("txStreet3.bmp");
  textures[TEX_STREET4] = loadTexBMP("txStreet4.bmp");
  textures[TEX_STREET5] = loadTexBMP("txStreet5.bmp");
  textures[TEX_STREET6] = loadTexBMP("txStreet6.bmp");
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
 *  initObjs
 *  ------
 *  initializes our obj's for use
 */
void initObjs(void)
{
  minionObj = loadOBJ("obj-f16.obj");
}

/*
 *  initMinions
 *  ------
 *  initializes our minions
 */
void initMinions(void)
{
  /* 
     minion: 
     typedef struct minion {
     int id;
     int type;
     point translation;

     point scale;
     point rotation;
     int texture;
     rgb rgb;
     
     char* name;
     int damage;
     int health;
     int money;
     int speed;
     int inPlay;
  */
  /* make a few default minions for the various waves */
  minion m0 = {0,minionObj,{26,0,-0.5},
	       {1,1,1},{0,270,0},0,{1,1,1},
	       "F16",1,5,5,1,1};
  int i;
  for (i=0;i<DEF_MINION_PER_WAVE_SIZE;i++) {
    minions[i] = m0;
  }
}

/*
 *  initWaves
 *  ------
 *  initializes the waves which will be used
 *  TODO: initialize minions with unique colors for object selection
 */
void initWaves()
{
  wave wave = {0,1};
  int i,k;
  /* fixed length of X minions per wave so we don't have to deal 
     with flexible array variables in structs */
  for (k=0;k<Length(waves);k++) {
    for (i=0;i<Length(minions);i++) {
      /* change stats for each wave */
      minions[i].scale.x = (k+1)*0.1;
      minions[i].scale.y = (k+1)*0.1;
      minions[i].scale.z = (k+1)*0.1;
      /* damage health money speed */
      minions[i].damage += k;
      minions[i].health += (2*k);
      minions[i].money  += (5*k);
      if (k < 3)
	minions[i].speed = 5-k;
      /* minimum speed of 2 */
      else 
	minions[i].speed = 2;

      /* default wave length is 10, for each of 0-4 waves decrement by 2 */
      if (i >= (DEF_MINION_PER_WAVE_SIZE-2*k)) {
	minions[i].inPlay = 0;
      }

      wave.m[i] = minions[i];
    }
    waves[k] = wave;
  }
}

/*
 *  initShots
 *  ------
 *  initializes the shot data
 */
void initShots()
{
  shot s = {0,{0,0,0},TEX_DEFAULT,0};
  int i;
  for (i=0;i<200;i++) {
    shots[i] = s;
  }
}

/*
 *  initPath
 *  ------
 *  initializes all the points that we'll be using for the path
 */
void initPath(void)
{
  int i,j;
  pathCube currentPath, nextPath, addedPath;
  /* 4/50 = 0.08 = # points between centerpoints/# desired points */
  double moveFactor = 0.08;
  fullPath[0] = pathCubes[0];

  /* Length(pathCubes) = 45... error about sizeof with structs */
  /* one less since we're checking next path */
  for (i=0;i<(DEF_PATH_LEN-1);i++) {
    addedPath = currentPath = pathCubes[i];
    nextPath = pathCubes[i+1];

    /* create 50 points between each pathCube for 2200 = (44x50) points total */
    for (j=0;j<DEF_FULL_PATH_LEN;j++) {
      /* add x */
      if (currentPath.p.x > nextPath.p.x) addedPath.p.x -= moveFactor;
      else if (currentPath.p.x < nextPath.p.x) addedPath.p.x += moveFactor;
      /* add z */
      if (currentPath.p.z > nextPath.p.z) addedPath.p.z -= moveFactor;
      else if (currentPath.p.z < nextPath.p.z) addedPath.p.z += moveFactor;
      fullPath[i*50+j] = addedPath;
    }
  }
}

/*
 *  initPreviewPoints
 *  ------
 *  initializes the preview points (line up with grid);
 */
void initPreviewPoints(void)
{
  point valid_points[DEF_CURRENT_OBJS_SIZE] = {
    /* ordered by row */
    {17,0,-17},{17,0,-13},{17,0,-9},{17,0,-5},{17,0,3},{17,0,19},
    {13,0,3},{13,0,11},{13,0,19},
    {9,0,-13},{9,0,-9},{9,0,-5},{9,0,-1},{9,0,3},{9,0,11},{9,0,19},
    {5,0,11},{5,0,19},
    {1,0,-17},{1,0,-13},{1,0,-9},{1,0,-5},{1,0,-1},{1,0,3},{1,0,7},{1,0,11},{1,0,19},
    {-3,0,19},
    {-7,0,-13},{-7,0,-9},{-7,0,-5},{-7,0,-1},{-7,0,3},{-7,0,7},{-7,0,11},{-7,0,15},{-7,0,19},
    {-11,0,15},{-11,0,19},
    {-15,0,-17},{-15,0,-13},{-15,0,-9},{-15,0,-5},{-15,0,-1},{-15,0,3},{-15,0,7},{-15,0,15},{-15,0,19},
    {-19,0,-17},{-19,0,-13},{-19,0,-9},{-19,0,-5},{-19,0,-1},{-19,0,3},{-19,0,7},{-19,0,15},{-19,0,19},
  };
  int i;
  for (i = 0; i < Length(valid_points); i++) {
    preview_points[i].x = valid_points[i].x;
    preview_points[i].y = valid_points[i].y;
    preview_points[i].z = valid_points[i].z;
  }
}

/*
 *  initDefaultTowers
 *  ------
 *  initialize the default towers into the towers array
 */
void initDefaultTowers(void)
{
  int i;
  for (i=0;i<Length(default_towers);i++) {
    printf("default tower %d \n",i);
    towers[i] = default_towers[i];
  }
  lastCurrentObject = 6;
  currentRed = 35;
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

