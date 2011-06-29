#ifndef CS_PROJECT
#define CS_PROJECT

/* standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* OpenGL and friends */
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*  DEFINES  */
#include "defines.h"

/*  STRUCTS  */
#include "structs.h"

/*  PROTOTYPES  */
#include "prototypes.h"

/*  GLOBALS (externs required here)  */
/*  Generic  */
extern int debug;
extern char *windowName;
extern int windowHeight;
extern int windowWidth;
extern GLuint window, screen, sidebar;

/*  Font styling  */
extern GLvoid *fontStyle;

/*  Projection  */
extern double asp;
extern double dim;
extern int th;
extern int ph;
extern int fov;
extern double ecX;
extern double ecY;
extern double ecZ;

/*  Toggle draw displays  */
extern int axes;
extern int grid;
extern int showAttackRadius;
extern int vals;

/*  Shots/Collision detection  */
extern int showCollisionDetection;
extern int lastShot;
extern shot shots[200];

/*  Animation  */
extern int gameStarted;
extern int gamePaused;
extern int gameSpeed;
extern int moveLightB;
extern int lightPh;
extern int moveTowerTopsB;
extern int towerTh;

/*  Game Data  */
extern char *info;
extern int lives;
extern int money;
extern int scrolls;
extern int score;
extern int waveNumber;
extern int lastWave;

/*  User Interaction  */
extern int mouseX, mouseY, mouseZ;

/*  Object Selection  */
extern tower towers[DEF_CURRENT_OBJS_SIZE];
extern tower preview_tower;
extern point preview_points[DEF_CURRENT_OBJS_SIZE];
extern int preview;
extern int objectSelected;
extern int lastCurrentObject;
extern int renderMode;
extern int objectPicked;
extern int currentRed;
extern int currentGreen;
extern int currentBlue;
extern char *currentTowerName;
extern int currentTowerRange;
extern int currentTowerDamage;
extern int currentTowerFireRate;
extern int currentTowerCost;
extern char *currentTowerDescription;

/*  Minions  */
extern wave waves[DEF_LAST_WAVE];
extern minion minions[DEF_MINION_PER_WAVE_SIZE];
extern int minionObj;

/*  Light  */
extern int light;
extern int distance;
extern int ambient;
extern int diffuse;
extern int emission;
extern int specular;
extern int shininess;
extern float shinyvec[1];
extern float lightY;
extern float white[];

/*  Textures  */
extern unsigned int textures[17];
extern int currentTexture;
extern int currentTextureSelected;
extern int backgrounds[6];

/*  Shadows  */
extern float N[];
extern float E[];

/*  Preset data  */
extern GLfloat cube_v[][3];
extern pathCube pathCubes[];
extern pathCube fullPath[];
extern tower default_towers[6];
extern tower tower_data[16];

#endif
