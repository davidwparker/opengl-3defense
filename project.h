#ifndef CS_PROJECT
#define CS_PROJECT

/* standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

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
extern int debug;
extern char *windowName;
extern int windowHeight;
extern int windowWidth;
extern GLuint window, screen, sidebar;
extern GLvoid *fontStyle;
extern double asp;
extern double dim;
extern int th;
extern int ph;
extern int fov;
extern double ecX;
extern double ecY;
extern double ecZ;
extern int axes;
extern int grid;
extern int vals;
extern int drawDefaults;
extern int topsRotate;
extern int towerTh;
extern int mouseX, mouseY, mouseZ;
extern minion minions[1];
extern tower towers[DEF_CURRENT_OBJS_SIZE];
extern tower preview_tower;
extern point preview_points[DEF_CURRENT_OBJS_SIZE];
extern int preview;
extern int objectSelected;
extern int lastCurrentObject;
extern int minionObj;
extern int renderMode;
extern int objectPicked;
extern int currentRed;
extern int currentGreen;
extern int currentBlue;
extern int light;
extern int move;
extern int distance;
extern int ambient;
extern int diffuse;
extern int emission;
extern int specular;
extern int shininess;
extern float shinyvec[1];
extern int lightPh;
extern float lightY;
extern float white[];
extern unsigned int textures[17];
extern int currentTexture;
extern int currentTextureSelected;
extern int backgrounds[6];
extern GLfloat cube_v[][3];
extern pathCube pathCubes[];
extern GLfloat default_objects[4][8];

#endif
