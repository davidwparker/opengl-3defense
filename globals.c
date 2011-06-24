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
int vals=DEF_VALS;       /* toggle show values on/off */
int drawDefaults=DEF_DRAW_DEFAULTS; /* toggle drawing the defaults */

/*  ANIMATION  */
int topsRotate=DEF_TOPS_ROTATE;     /* toggles whether top of towers rotate */
int towerTh=DEF_TOWER_TH;           /* top of ice tower rotation */

/*  USER INTERACTION  */
/*  current X, Y, Z position of mouse */
int mouseX=0;
int mouseY=0;
int mouseZ=0;

/*  OBJECT SELECTION  */
minion minions[1];                      /* holds the minions */
tower towers[DEF_CURRENT_OBJS_SIZE];    /* holds towers - the most our board can hold is 53 */
tower preview_tower;                    /* ho lds the preview tower */
point preview_points[DEF_CURRENT_OBJS_SIZE];/* holds valid locations of preview locations */
int preview=DEF_PREVIEW;                       /* determine if preview is on */
int objectSelected=DEF_OBJ_SEL;                /* the object to be placed */
int lastCurrentObject=DEF_LAST_CURRENT_OBJECT; /* determine last object */
int renderMode=DEF_RENDER;                     /* the current mode we are in */
int objectPicked=DEF_OBJ_PICKED;               /* the object that we have picked */
/*  Current level of RGB for object selection */
int currentRed=DEF_CURRENT_RED;
int currentGreen=DEF_CURRENT_GREEN;
int currentBlue=DEF_CURRENT_BLUE;

/*  MINIONS */
int minionObj=DEF_MINION_OBJ; /* minion obj */

/*  LIGHTING */
int light=DEF_LIGHT;          /* toggle light */
int move=DEF_MOVE;            /* toggle move light */
int distance=DEF_DISTANCE;    /* light distance */
int ambient=DEF_AMBIENT;      /* ambient intensity % */
int diffuse=DEF_DIFFUSE;      /* diffuse intensity % */
int emission=DEF_EMISSION;    /* emission intensity % */
int specular=DEF_SPECULAR;    /* specular intensity % */
int shininess=DEF_SHININESS;  /* shininess (power of two) */
float shinyvec[1]={1};        /* shininess (value) */
int lightPh=DEF_L_PH;         /* light elevation */
float lightY=DEF_L_Y;         /* elevation of light */
float white[]={1,1,1,1};

/*  TEXTURES  */
unsigned int textures[17];              /* holds our textures */
int currentTexture=TEX_DEFAULT;         /* no texture assigned as default */
int currentTextureSelected=TEX_DEFAULT; /* no texture currently selected */
int backgrounds[6];                     /* holds the textures for the skybox background */

/*  cube vertices */
GLfloat cube_v[][3] = {
  {-1.0,-1.0,-1.0},{+1.0,-1.0,-1.0},{+1.0,+1.0,-1.0},
  {-1.0,+1.0,-1.0},{-1.0,-1.0,+1.0},{+1.0,-1.0,+1.0},
  {+1.0,+1.0,+1.0},{-1.0,+1.0,+1.0}
};

/* default objects */
GLfloat default_objects[4][8] = {
  {OBJ_FIRE2, -2,0,-2, TEX_DEFAULT, 255,0,0},
  {OBJ_ICE2,   2,0, 2, TEX_DEFAULT, 0,255,255},
  {OBJ_EARTH2, 2,0,-2, TEX_DEFAULT, 139,69,19},
  {OBJ_POISON2,-2,0,2, TEX_DEFAULT, 0,255,0}
};
