#include "project.h"

/*
 *  GENERAL GLUT COMMANDS
 */

/*
 *  changeObjectSelected
 *  ------
 *  changes to the new object selected, the preview, and then current tower data
 */
void changeObjectSelected(int newObjectSelected)
{
  objectSelected = newObjectSelected;
  preview_tower.id = objectSelected;
  preview_tower.translation.x = -255;
  preview_tower.translation.y = -255;
  preview_tower.translation.z = -255;
  setCurrentTowerData(objectSelected);
}

/*
 *  setCurrentTowerData
 *  ------
 *  sets the current tower data for a new tower or selected tower
 */
void setCurrentTowerData(int type)
{
  currentTextureSelected = tower_data[type-1].texture;
  currentTowerName = tower_data[type-1].name;
  currentTowerRange = tower_data[type-1].range;
  currentTowerDamage = tower_data[type-1].damage;
  currentTowerFireRate = tower_data[type-1].fireRate;
  currentTowerCost = tower_data[type-1].cost;
  currentTowerDescription = tower_data[type-1].description;
}

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
      setCurrentTowerData(towers[i].type);
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
  int i;

  /* reset font styling */
  fontStyle = DEF_FONT_STYLE;

  /* reset projection */
  asp  = DEF_ASP;
  dim  = DEF_DIM;
  th   = DEF_TH;
  ph   = DEF_PH;
  fov  = DEF_FOV;
  ecX  = DEF_ECX;
  ecY  = DEF_ECY;
  ecZ  = DEF_ECZ;  

  /* reset toggle draw */
  axes = DEF_AXES;
  grid = DEF_GRID;
  vals = DEF_VALS;

  /* reset collision detection */
  showCollisionDetection = DEF_COLLISION;
  lastShot               = DEF_LAST_SHOT;

  /* reset animation */
  gameStarted    = DEF_GAME_STARTED;
  gamePaused     = DEF_GAME_PAUSED;
  gameSpeed      = DEF_GAME_SPEED;
  moveLightB     = DEF_MOVE_LIGHT;
  lightPh        = DEF_L_PH;
  moveTowerTopsB = DEF_MOVE_TOWER_TOPS;
  towerTh        = DEF_TOWER_TH;

  /* reset game data */
  lives      = DEF_LIVES;
  money      = DEF_MONEY;
  scrolls    = DEF_SCROLLS;
  waveNumber = DEF_WAVE;
  lastWave   = DEF_LAST_WAVE;

  /* reset object selection */
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
  preview_tower.id = 0;
  preview_tower.type = 0;
  preview_tower.translation.x = 0;
  preview_tower.translation.y = 0;
  preview_tower.translation.z = 0;
  preview_tower.texture = 0;
  preview_tower.name = "preview";


  /* preview_points are okay */
  preview           = DEF_PREVIEW;
  objectSelected    = DEF_OBJ_SEL;
  lastCurrentObject = DEF_LAST_CURRENT_OBJECT;
  renderMode        = DEF_RENDER;
  objectPicked      = DEF_OBJ_PICKED;
  currentRed   = DEF_CURRENT_RED;
  currentGreen = DEF_CURRENT_GREEN;
  currentBlue  = DEF_CURRENT_BLUE;

  /* reset minions */
  /* minions are reset by the waves */
  initWaves();

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
