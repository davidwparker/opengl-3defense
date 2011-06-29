#include "project.h"

/*  GENERIC GLOBALS  */
int debug=DEF_DEBUG;                             /* toggle debug */
char *windowName="PROJECT: 3Defense by David Parker"; /* Window name */
int windowHeight=DEF_WINDOW_HEIGHT;              /* default window height */
int windowWidth=DEF_WINDOW_WIDTH;                /* default window width */
GLuint window, screen, sidebar;                  /* window id's */

/*  FONT STYLING  */
GLvoid *fontStyle=DEF_FONT_STYLE;        /* default font style */

/*  PROJECTION  */
double asp=DEF_ASP;      /* aspect ratio */
double dim=DEF_DIM;      /* dimension of orthogonal box */
int th=DEF_TH;           /* azimuth of view angle */
int ph=DEF_PH;           /* elevation of view angle */
int fov=DEF_FOV;         /* field of view for perspective */
double ecX=DEF_ECX;      /* eye center position x */
double ecY=DEF_ECY;      /* eye center position y */
double ecZ=DEF_ECZ;      /* eye center position z */

/*  TOGGLE DRAW DISPLAYS  */
int axes=DEF_AXES;       /* toggle axes on/off */
int grid=DEF_GRID;       /* toggle grid on/off */
int showAttackRadius=DEF_SHOW_ATTACK;  /* toggle attack radius on/off */
int vals=DEF_VALS;       /* toggle show values on/off */

/*  COLLISION DETECTION  */
int showCollisionDetection=DEF_COLLISION; /* toggle showing spheres around planes on/off */
int lastShot=DEF_LAST_SHOT;
shot shots[200];                          /* holds the current shots - hardcoded to 200 max */

/*  ANIMATION  */
char *info=DEF_INFO;
int gameStarted=DEF_GAME_STARTED;       /* has the game been started? */
int gamePaused=DEF_GAME_PAUSED;         /* toggle game paused */
int gameSpeed=DEF_GAME_SPEED;           /* game speed for idle */
int moveLightB=DEF_MOVE_LIGHT;          /* toggle move light */
int lightPh=DEF_L_PH;                   /* light elevation */
int moveTowerTopsB=DEF_MOVE_TOWER_TOPS; /* toggles whether top of towers rotate */
int towerTh=DEF_TOWER_TH;               /* top of ice tower rotation */

/*  USER INTERACTION  */
/*  GAME DATA  */
int lives=DEF_LIVES;
int money=DEF_MONEY;
int scrolls=DEF_SCROLLS;
int score=DEF_SCORE;
int waveNumber=DEF_WAVE;
int lastWave=DEF_LAST_WAVE;

/*  current X, Y, Z position of mouse */
int mouseX=0;
int mouseY=0;
int mouseZ=0;

/*  OBJECT SELECTION  */
tower towers[DEF_CURRENT_OBJS_SIZE];    /* holds towers - the most our board can hold is 53 */
tower preview_tower;                    /* holds the preview tower */
point preview_points[DEF_CURRENT_OBJS_SIZE];   /* holds valid locations of preview locations */
int preview=DEF_PREVIEW;                       /* determine if preview is on */
int objectSelected=DEF_OBJ_SEL;                /* the object to be placed */
int lastCurrentObject=DEF_LAST_CURRENT_OBJECT; /* determine last object */
int renderMode=DEF_RENDER;                     /* the current mode we are in */
int objectPicked=DEF_OBJ_PICKED;               /* the object that we have picked */
/*  Current level of RGB for object selection */
int currentRed=DEF_CURRENT_RED;
int currentGreen=DEF_CURRENT_GREEN;
int currentBlue=DEF_CURRENT_BLUE;

/*  MINIONS  */
wave waves[DEF_LAST_WAVE];                   /* holds the waves of minions */
minion minions[DEF_MINION_PER_WAVE_SIZE];    /* holds the minions */
int minionObj=DEF_MINION_OBJ;                /* minion obj */

/*  LIGHTING  */
int light=DEF_LIGHT;          /* toggle light */
int distance=DEF_DISTANCE;    /* light distance */
int ambient=DEF_AMBIENT;      /* ambient intensity % */
int diffuse=DEF_DIFFUSE;      /* diffuse intensity % */
int emission=DEF_EMISSION;    /* emission intensity % */
int specular=DEF_SPECULAR;    /* specular intensity % */
int shininess=DEF_SHININESS;  /* shininess (power of two) */
float shinyvec[1]={1};        /* shininess (value) */
float lightY=DEF_L_Y;         /* elevation of light */
float white[]={1,1,1,1};

/*  TEXTURES  */
unsigned int textures[17];              /* holds our textures */
int currentTexture=TEX_DEFAULT;         /* no texture assigned as default */
int currentTextureSelected=TEX_DEFAULT; /* no texture currently selected */
int backgrounds[6];                     /* holds the textures for the skybox background */

/*  SHADOWS  */
float N[] = {0, -1, 0, 0};            /* normal vector for the plane */
float E[] = {0, DEF_Y_FLOOR, 0, 0};   /* Point of the plane */

/*  PRESET DATA  */
/*  cube vertices */
GLfloat cube_v[][3] = {
  {-1.0,-1.0,-1.0},{+1.0,-1.0,-1.0},{+1.0,+1.0,-1.0},
  {-1.0,+1.0,-1.0},{-1.0,-1.0,+1.0},{+1.0,-1.0,+1.0},
  {+1.0,+1.0,+1.0},{-1.0,+1.0,+1.0}
};

/*  path cube vertices, texture, rotation */
pathCube pathCubes[] = {
  {{25,-3,-1},  TEX_STREET1,90, DEF_NORTH},
  {{21,-3,-1},  TEX_STREET1,90, DEF_NORTH}, {{17,-3,-1},  TEX_STREET1,90, DEF_NORTH},
  {{13,-3,-1},  TEX_STREET6,270,DEF_EAST},  {{13,-3,-5},  TEX_STREET2,0,  DEF_EAST},
  {{13,-3,-9},  TEX_STREET2,0,  DEF_EAST},  {{13,-3,-13}, TEX_STREET2,0,  DEF_EAST},
  {{13,-3,-17}, TEX_STREET4,90, DEF_NORTH}, {{9,-3,-17},  TEX_STREET1,90, DEF_NORTH},
  {{5,-3,-17},  TEX_STREET3,180,DEF_WEST},  {{5,-3,-13},  TEX_STREET2,180,DEF_WEST},
  {{5,-3,-9},   TEX_STREET2,180,DEF_WEST},  {{5,-3,-5},   TEX_STREET2,180,DEF_WEST},
  {{5,-3,-1},   TEX_STREET2,180,DEF_WEST},  {{5,-3,3},    TEX_STREET2,180,DEF_WEST},
  {{5,-3,7},    TEX_STREET6,270,DEF_SOUTH}, {{9,-3,7},    TEX_STREET1,270,DEF_SOUTH},
  {{13,-3,7},   TEX_STREET1,270,DEF_SOUTH}, {{17,-3,7},   TEX_STREET4,90, DEF_WEST},
  {{17,-3,11},  TEX_STREET2,0,  DEF_WEST},  {{17,-3,15},  TEX_STREET5,0,  DEF_NORTH},
  {{13,-3,15},  TEX_STREET1,90, DEF_NORTH}, {{9,-3,15},   TEX_STREET1,90, DEF_NORTH},
  {{5,-3,15},   TEX_STREET1,90, DEF_NORTH}, {{1,-3,15},   TEX_STREET1,90, DEF_NORTH},
  {{-3,-3,15},  TEX_STREET6,270,DEF_EAST},  {{-3,-3,11},  TEX_STREET2,0,  DEF_EAST},
  {{-3,-3,7},   TEX_STREET2,0,  DEF_EAST},  {{-3,-3,3},   TEX_STREET2,0,  DEF_EAST},
  {{-3,-3,-1},  TEX_STREET2,0,  DEF_EAST},  {{-3,-3,-5},  TEX_STREET2,0,  DEF_EAST},
  {{-3,-3,-9},  TEX_STREET2,0,  DEF_EAST},  {{-3,-3,-13}, TEX_STREET2,0,  DEF_EAST},
  {{-3,-3,-17}, TEX_STREET4,90, DEF_NORTH}, {{-7,-3,-17}, TEX_STREET1,90, DEF_NORTH},
  {{-11,-3,-17},TEX_STREET3,180,DEF_WEST},  {{-11,-3,-13},TEX_STREET2,180,DEF_WEST},
  {{-11,-3,-9}, TEX_STREET2,180,DEF_WEST},  {{-11,-3,-5}, TEX_STREET2,180,DEF_WEST},
  {{-11,-3,-1}, TEX_STREET2,180,DEF_WEST},  {{-11,-3,3},  TEX_STREET2,180,DEF_WEST},
  {{-11,-3,7},  TEX_STREET2,180,DEF_WEST},  {{-11,-3,11}, TEX_STREET5,0,  DEF_NORTH},
  {{-15,-3,11}, TEX_STREET1,90, DEF_NORTH}, {{-19,-3,11}, TEX_STREET1,90, DEF_NORTH}
};

pathCube fullPath[2200];

/*  default towers  */
tower default_towers[6] = {
  {0,OBJ_BASIC,1,{17,0,-17},{1,1,1},{0,0,0},TEX_BRICK,{5,5,5},
   "Basic",1,         5, 3,4,0,10,"Description"},
  {0,OBJ_FIRE,1,{9,0,-13},{1,1,1},{0,0,0},TEX_FIRE,{10,5,5},
   "Fire",1,          12,4,3,0,40,"Description"},
  {0,OBJ_FIRE2,1,{9,0,-9},{1,1,1},{0,0,0},TEX_FIRE,{15,5,5},
   "Advanced Fire",1, 12,6,3,0,45,"Description"},
  {0,OBJ_ICE,1,{13,0,3},{1,1,1},{0,0,0},TEX_ICE,{20,5,5},
   "Ice",1,           12,5,4,0,50,"Description"},
  {0,OBJ_EARTH,1,{13,0,19},{1,1,1},{0,0,0},TEX_EARTH,{25,5,5},
   "Earth",1,         10,8,6,0,60,"Description"},
  {0,OBJ_POISON2,1,{17,0,-5},{1,1,1},{0,0,0},TEX_POISON,{30,5,5},
   "Advanced Poison",1,12,8,3,0,75,"Description"}
};
