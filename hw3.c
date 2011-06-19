/*
 * Homework Assignment #3
 * David Parker
 * June 14-20, 2011
 *
 * Eventually, I would like everything marked with ^ to be in its own file
 *
 * Table of Contents
 * INCLUDES^
 * DEFINES^
 * -macros
 * -for window sizing
 * -for resets
 * -for lighting
 * -for textures
 * STRUCTS^
 * PROTOTYPES^
 * GLOBAL VARIABLES^
 * -for various state
 * -for object selection
 * -for lighting
 * -for textures
 * -for vertices
 * FUNCTIONS:
 * -reset
 * -printing convenience functions^
 * --setFont
 * --printv
 * --print
 * --printAt
 * --errCheck
 * --fatal
 * -loadtexbmp convenience functions^
 * --reverse
 * --loadTexBMP
 * -shape definition functions^
 * --basic shapes^
 * ---square (15)
 * ---cube (16)
 * ---vertex (17)
 * ---sphere (18)
 * ---cone (19)
 * ---cylinder (20)
 * --composite shapes & board pieces^
 * ---pyramid (21)
 * ---star (22)
 * ---spike (23)
 * ---board (24)
 * --tower definitions (object #)^
 * ---basicTower (9)
 * ---advancedTower (10)
 * ---coneTower (11)
 * ---advancedConeTower (12)
 * ---squareTower (13)
 * ---advancedSquareTower (14)
 * ---fireTower (1)
 * ---fireTower2 (2)
 * ---iceTower (3)
 * ---iceTower2 (4)
 * ---earthTower (5)
 * ---earthTower2 (6)
 * ---poisonTower (7)
 * ---poisonTower2 (8)
 * -general glut functions^
 * --redisplayAll
 * --idle
 * --findMousePosition
 * --processPicks
 * -display and draw functions^
 * --displayInit
 * --displayEye
 * --drawAxes
 * --drawParameters
 * --drawLight
 * --drawObjects
 * -main glut commands^
 * --mainDisplay
 * --mainKey
 * --mainSpecial
 * --mainReshape
 * --mainVisible
 * -screen area glut commands^
 * --screenDisplay
 * --screenProject
 * --screenReshape
 * --screenMouse
 * -sidebar area glut commands^
 * --sidebarRow
 * --sidebarRowT
 * --sidebarDisplay
 * --sidebarReshape
 * --sidebarMouse
 * -initialization functions^
 * --sidebarInit
 * --screenInit
 * --initTextures
 * -main
 */

/*  Include standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

/*  Include GLEW if you need access to advanced features */
#ifdef USEGLEW
#include <GL/glew.h>
#endif
/*  Include GLUT and GL */
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*  OpenGL with prototypes for glext */
#define GL_GLEXT_PROTOTYPES
/*  Poor approximation of Cosine and Sine in degrees */
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))
/*  Determine number of elements in an array */
#define Length(x) (sizeof (x) / sizeof *(x))

/*  Defaults for window sizing */
/*  Keeping this for defaults, although we're using full screen mode */
#define DEF_WINDOW_HEIGHT 700
#define DEF_WINDOW_WIDTH 1000
/*  Space between sidebar and screen display */
#define DEF_SPACER 10
/*  Sidebar's permanent width */
#define DEF_SIDEBAR_WIDTH 300
/*  Line height for text */
#define DEF_TEXT_Y_OFFSET 20

/*  Defaults (for reset) */
#define DEF_FONT_STYLE GLUT_BITMAP_HELVETICA_10
#define DEF_DRAW_DEFAULTS 1
#define DEF_MODE 1
#define DEF_ASP 1
#define DEF_DIM 12
#define DEF_TH -60
#define DEF_PH 30
#define DEF_FOV 50
#define DEF_D 5
#define DEF_AXES 0
#define DEF_VALS 1
#define DEF_TOPS_ROTATE 1
#define DEF_TOWER_TH 0
#define DEF_DEBUG 0

/*  Object definitions and selection */
#define OBJ_FIRE 1
#define OBJ_FIRE2 2
#define OBJ_ICE 3
#define OBJ_ICE2 4
#define OBJ_EARTH 5
#define OBJ_EARTH2 6
#define OBJ_POISON 7
#define OBJ_POISON2 8
#define OBJ_BASIC 9
#define OBJ_ADV 10
#define OBJ_CONE 11
#define OBJ_ADV_CONE 12
#define OBJ_SQUARE 13
#define OBJ_ADV_SQUARE 14
#define DEF_LAST_CURRENT_OBJECT 0
#define DEF_OBJ_SEL 0
#define DEF_OBJ_PICKED -1
#define DEF_PREVIEW 0
#define DEF_RENDER 1
#define DEF_SELECT 2
#define DEF_CURRENT_RED 5
#define DEF_CURRENT_GREEN 5
#define DEF_CURRENT_BLUE 5
#define DEF_CURRENT_OBJS_SIZE 30
#define DEF_CURRENT_OBJS_ATRS 8

/*  Lighting */
#define DEF_LIGHT 1
#define DEF_MOVE 1
#define DEF_DISTANCE 5
#define DEF_AMBIENT 20
#define DEF_DIFFUSE 100
#define DEF_EMISSION 0
#define DEF_SPECULAR 0
#define DEF_SHININESS 0
#define DEF_L_TH 90
#define DEF_L_Y -2

/*  Texture definitions */
#define TEX_DEFAULT 0
#define TEX_BRICK 1
#define TEX_FIRE 2
#define TEX_ICE 3
#define TEX_EARTH 4
#define TEX_POISON 5
#define TEX_SPIKE 6
#define TEX_GRASS 7

/*  Structs */
typedef struct vertices3f {
  GLfloat posX;
  GLfloat posY;
  GLfloat posZ;
} vertices3f;

/*  Prototypes */
/*  Convenience */
void reset(void);
void setFont(char* name, int size);
void printv(va_list args, const char* format);
void print(const char* format , ...);
void printAt(int x,int y, const char* format , ...);
void errCheck(char* where);
void fatal(const char* format, ...);
static void reverse(void* x,const int n);
unsigned int loadTexBMP(char* file);
/*  Shapes and models */
static void square(int s, int a, int b, int c, int d);
static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th);
static void vertex(double th, double ph);
static void sphere(double x,double y,double z,double r,double rot);
static void cone(double x,double y,double z, double r, double h,int deg);
static void cylinder(double x,double y,double z,
		     double r,double h);
static void pyramid(double x, double y, double z,
		    double dx, double dy, double dz,
		    double th);
static void star(double x, double y, double z,
		    double dx, double dy, double dz,
		    double th);
static void spike(double x, double y, double z,
		  double r,double h,int deg,
		  double ox,double oy,double oz);
static void board(void);
static void basicTower(double x,double y,double z,
		       double dx,double dy,double dz,
		       double th);
static void advancedTower(double x,double y,double z,
			  double dx,double dy,double dz,
			  double th);
static void coneTower(double x,double y,double z,
		      double dx,double dy,double dz,
		      double th);
static void advancedConeTower(double x,double y,double z,
			      double dx,double dy,double dz,
			      double th);
static void squareTower(double x,double y,double z,
			double dx,double dy,double dz,
			double th);
static void advancedSquareTower(double x,double y,double z,
				double dx,double dy,double dz,
				double th);
static void fireTower(double x,double y,double z,
		      double dx,double dy,double dz,
		      double th);
static void fireTower2(double x,double y,double z,
		       double dx,double dy,double dz,
		       double th);
static void iceTower(double x,double y,double z,
		     double dx,double dy,double dz,
		     double th);
static void iceTower2(double x,double y,double z,
		      double dx,double dy,double dz,
		      double th);
static void earthTower(double x,double y,double z,
		       double dx,double dy,double dz,
		       double th);
static void earthTower2(double x,double y,double z,
			double dx,double dy,double dz,
			double th);
static void poisonTower(double x,double y,double z,
			double dx,double dy,double dz,
			double th);
static void poisonTower2(double x,double y,double z,
			 double dx,double dy,double dz,
			 double th);
/*  Display and interaction */
void redisplayAll(void);
void idle(void);
vertices3f findMousePosition(int x, int y);
void processPicks(void);
void displayInit(void);
void displayEye(void);
void drawAxes(void);
void drawParameters(void);
void drawLight(void);
void drawObjects(void);
void mainDisplay(void);
void mainKey(unsigned char key,int x,int y);
void mainSpecial(int key,int x,int y);
void mainReshape(int width, int height);
void mainVisible(int vis);
void screenDisplay(void);
void screenProject(double fov, double asp, double dim);
void screenReshape(int width, int height);
void screenMouse(int btn, int state, int x, int y);
void sidebarRow(int x, int y, int obj, char* text);
void sidebarRow(int x, int y, int obj, char* text);
void sidebarDisplay(void);
void sidebarReshape(int width, int height);
void sidebarMouse(int btn, int state, int x, int y);
void sidebarInit(void);
void screenInit(void);
void initTextures(void);

/*  Globals */
char *windowName = "Assignment 3: David Parker"; /* Window name */
int windowHeight = DEF_WINDOW_HEIGHT;      /* default window height */
int windowWidth  = DEF_WINDOW_WIDTH;       /* default window width */
GLuint window, screen, sidebar;            /* window id's */
GLvoid *fontStyle = DEF_FONT_STYLE;        /* default font style */

int mouseX = 0, mouseY = 0, mouseZ = 0; /* current X, Y position of mouse */
int mode=DEF_MODE;       /* toggle projection mode */
double asp=DEF_ASP;      /* aspect ratio */
double dim=DEF_DIM;      /* dimension of orthogonal box */
int th=DEF_TH;           /* azimuth of view angle */
int ph=DEF_PH;           /* elevation of view angle */
int fov=DEF_FOV;         /* field of view for perspective */
int axes=DEF_AXES;       /* toggle axes on/off */
int vals=DEF_VALS;       /* toggle show values on/off */
int topsRotate=DEF_TOPS_ROTATE;     /* toggles whether top of towers rotate */
int towerTh=DEF_TOWER_TH;           /* top of ice tower rotation */
int drawDefaults=DEF_DRAW_DEFAULTS; /* toggle drawing the defaults */
int debug=DEF_DEBUG;                /* toggle debug */

/*  Object selection */
GLfloat current_objects[DEF_CURRENT_OBJS_SIZE][DEF_CURRENT_OBJS_ATRS]={{0}}; /* hold towers */
GLfloat preview_object[5]={0};                 /* holds the preview object */
int preview=DEF_PREVIEW;                       /* determine if preview is on */
int objectSelected=DEF_OBJ_SEL;                /* the object to be placed */
int lastCurrentObject=DEF_LAST_CURRENT_OBJECT; /* determine last object */
int renderMode=DEF_RENDER;                     /* the current mode we are in */
int objectPicked=DEF_OBJ_PICKED;               /* the object that we have picked */
/*  Current level of RGB for object selection */
int currentRed=DEF_CURRENT_RED;
int currentGreen=DEF_CURRENT_GREEN;
int currentBlue=DEF_CURRENT_BLUE;

/*  Globals for lighting */
int light=DEF_LIGHT;          /* toggle light */
int move=DEF_MOVE;            /* toggle move light */
int distance=DEF_DISTANCE;    /* light distance */
int ambient=DEF_AMBIENT;      /* ambient intensity % */
int diffuse=DEF_DIFFUSE;      /* diffuse intensity % */
int emission=DEF_EMISSION;    /* emission intensity % */
int specular=DEF_SPECULAR;    /* specular intensity % */
int shininess=DEF_SHININESS;  /* shininess (power of two) */
float shinyvec[1]={1};     /* shininess (value) */
int lightTh=DEF_L_TH;  /* light azimuth */
float lightY=DEF_L_Y;  /* elevation of light */
float white[]={1,1,1,1};

/*  Globals for textures */
unsigned int textures[8];       /* currently holding eight textures */
int currentTexture=TEX_DEFAULT; /* no texture assigned as default */
int currentTextureSelected=TEX_DEFAULT; /* no texture currently selected */

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

/*  
 *  reset
 *  ------
 *  reset all values back to defaults 
 */
void reset()
{
  /* reset the current objects with 0's and default objects */
  int i,j;
  for (i=0;i<DEF_CURRENT_OBJS_SIZE;i++)
    for (j=0;j<DEF_CURRENT_OBJS_ATRS;j++)
      current_objects[i][j] = 0;
  if (drawDefaults)
    for (i=0;i<Length(default_objects);i++)
      for(j=0;j<DEF_CURRENT_OBJS_ATRS;j++)
	current_objects[i][j] = default_objects[i][j];
  /* reset object selection */
  if (drawDefaults) lastCurrentObject = DEF_LAST_CURRENT_OBJECT+Length(default_objects);
  else lastCurrentObject = DEF_LAST_CURRENT_OBJECT;
  objectSelected    = DEF_OBJ_SEL;
  objectPicked      = DEF_OBJ_PICKED;
  preview           = DEF_PREVIEW;
  currentRed   = DEF_CURRENT_RED;
  currentGreen = DEF_CURRENT_GREEN;
  currentBlue  = DEF_CURRENT_BLUE;


  /* reset the rest */
  mode = DEF_MODE;
  asp  = DEF_ASP;
  dim  = DEF_DIM;
  th   = DEF_TH;
  ph   = DEF_PH;
  fov  = DEF_FOV;
  axes = DEF_AXES;
  vals = DEF_VALS;
  fontStyle    = DEF_FONT_STYLE;
  topsRotate   = DEF_TOPS_ROTATE;
  towerTh      = DEF_TOWER_TH;

  /* reset lighting */
  light     = DEF_LIGHT;
  move      = DEF_MOVE;
  distance  = DEF_DISTANCE;
  ambient   = DEF_AMBIENT;
  diffuse   = DEF_DIFFUSE;
  emission  = DEF_EMISSION;
  specular  = DEF_SPECULAR;
  shininess = DEF_SHININESS;
  lightTh   = DEF_L_TH;
  lightY    = DEF_L_Y;

  /* reset textures */
  currentTexture = TEX_DEFAULT;
  currentTextureSelected = TEX_DEFAULT;
}

/*
 *  BEGIN PRINTING CONVENIENCE METHODS
 */

/*
 *  Set the font to either "helvetica" or "times roman" of size x
 */
void setFont(char* name, int size)
{
  if(strcmp(name,"helvetica") == 0) {
    if (size == 10) fontStyle = GLUT_BITMAP_HELVETICA_10;
    else if (size == 12) fontStyle = GLUT_BITMAP_HELVETICA_12;
    else if (size == 18) fontStyle = GLUT_BITMAP_HELVETICA_18;
  } else if (strcmp(name, "times roman") == 0) {
    if (size == 24) fontStyle = GLUT_BITMAP_TIMES_ROMAN_24;
  }
}

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
/* Maximum length of text string */
#define LEN 8192
void printv(va_list args, const char* format)
{
  char    buf[LEN];
  char*   ch=buf;
  /*  Turn the parameters into a character string */
  vsnprintf(buf,LEN,format,args);
  /*  Display the characters one at a time at the current raster position */
  while (*ch)
    glutBitmapCharacter(fontStyle,*ch++);
}

/*
 *  Convenience method to print
 */
void print(const char* format , ...)
{
  va_list args;
  va_start(args,format);
  printv(args,format);
  va_end(args);
}

/*
 *  Convenience method to print at a specific X, Y coordinate
 */
void printAt(int x, int y, const char* format, ...)
{
  va_list args;
  glWindowPos2i(x, y);
  va_start(args,format);
  printv(args,format);
  va_end(args);
}

/*
 *  Convenience method to print out OpenGL errors to stderr
 */
void errCheck(char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

/*
 *  Convenience method to print to stderr and exit
 */
void fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

/*
 *  BEGIN LOADTEXBMP CONVENIENCE METHODS
 */

/*
 *  Reverse n bytes
 */
static void reverse(void* x,const int n)
{
   int k;
   char* ch = (char*)x;
   for (k=0;k<n/2;k++)
   {
      char tmp = ch[k];
      ch[k] = ch[n-1-k];
      ch[n-1-k] = tmp;
   }
}

/*
 *  Load texture from BMP file
 */
unsigned int loadTexBMP(char* file)
{
  unsigned int   texture;    /* Texture name */
  FILE*          f;          /* File pointer */
  unsigned short magic;      /* Image magic */
  unsigned int   dx,dy,size; /* Image dimensions */
  unsigned short nbp,bpp;    /* Planes and bits per pixel */
  unsigned char* image;      /* Image data */
  unsigned int   k;          /* Counter */

  /*  Open file */
  f = fopen(file,"rb");
  if (!f) fatal("Cannot open file %s\n",file);
  /*  Check image magic */
  if (fread(&magic,2,1,f)!=1) fatal("Cannot read magic from %s\n",file);
  if (magic!=0x4D42 && magic!=0x424D) fatal("Image magic not BMP in %s\n",file);
  /*  Seek to and read header */
  if (fseek(f,16,SEEK_CUR) || fread(&dx ,4,1,f)!=1 || fread(&dy ,4,1,f)!=1 ||
      fread(&nbp,2,1,f)!=1 || fread(&bpp,2,1,f)!=1 || fread(&k,4,1,f)!=1)
    fatal("Cannot read header from %s\n",file);
  /*  Reverse bytes on big endian hardware (detected by backwards magic) */
  if (magic==0x424D) {
    reverse(&dx,4);
    reverse(&dy,4);
    reverse(&nbp,2);
    reverse(&bpp,2);
    reverse(&k,4);
  }
  /*  Check image parameters */
  if (dx<1 || dx>65536) fatal("%s image width out of range: %d\n",file,dx);
  if (dy<1 || dy>65536) fatal("%s image height out of range: %d\n",file,dy);
  if (nbp!=1)  fatal("%s bit planes is not 1: %d\n",file,nbp);
  if (bpp!=24) fatal("%s bits per pixel is not 24: %d\n",file,bpp);
  if (k!=0)    fatal("%s compressed files not supported\n",file);
#ifndef GL_VERSION_2_0
  /*  OpenGL 2.0 lifts the restriction that texture size must be a power of two */
  for (k=1;k<dx;k*=2);
  if (k!=dx) fatal("%s image width not a power of two: %d\n",file,dx);
  for (k=1;k<dy;k*=2);
  if (k!=dy) fatal("%s image height not a power of two: %d\n",file,dy);
#endif

  /*  Allocate image memory */
  size = 3*dx*dy;
  image = (unsigned char*) malloc(size);
  if (!image) fatal("Cannot allocate %d bytes of memory for image %s\n",size,file);
  /*  Seek to and read image */
  if (fseek(f,20,SEEK_CUR) || fread(image,size,1,f)!=1) 
    fatal("Error reading data from image %s\n",file);
  fclose(f);
  /*  Reverse colors (BGR -> RGB) */
  for (k=0;k<size;k+=3) {
    unsigned char temp = image[k];
    image[k]   = image[k+2];
    image[k+2] = temp;
  }

  /*  Sanity check */
  errCheck("LoadTexBMP");
  /*  Generate 2D texture */
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  /*  Copy image */
  glTexImage2D(GL_TEXTURE_2D,0,3,dx,dy,0,GL_RGB,GL_UNSIGNED_BYTE,image);
  if (glGetError()) fatal("Error in glTexImage2D %s %dx%d\n",file,dx,dy);
  /*  Scale linearly when image size doesn't match */
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

  /*  Free image memory */
  free(image);
  /*  Return texture name */
  return texture;
}

/*
 *  BEGIN SHAPE DEFINITION FUNCTIONS
 */

/*
 *  square
 *  ------
 *  Draw a square of type t, up to four sides
 *  This can be refactored to be much nicer
 */
static void square(int s, int a, int b, int c, int d)
{
  glBegin(GL_POLYGON);

  /* front */
  if (s == 1) { glNormal3f(0,0,1); }
  /* back */
  else if (s == 2) { glNormal3f(0,0,-1); }
  /* right */
  else if (s == 3) { glNormal3f(1,0,0); }
  /* left */
  else if (s == 4) { glNormal3f(-1,0,0); }
  /* top */
  else if (s == 5) { glNormal3f(0,1,0); }
  /* bottom */
  else if (s == 6) { glNormal3f(0,-1,0); }
  glTexCoord2f(0,0); glVertex3fv(cube_v[a]);
  glTexCoord2f(1,0); glVertex3fv(cube_v[b]);
  glTexCoord2f(1,1); glVertex3fv(cube_v[c]);
  glTexCoord2f(0,1); glVertex3fv(cube_v[d]);

  glEnd();
}

/*
 *  cube
 *  ------
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
  float emissions[] = {0,0,0.01*emission,1};
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emissions);

  /* enable textures */
  if (renderMode == DEF_RENDER) {
    glEnable(GL_TEXTURE_2D);
    /* using the current texture */
    glBindTexture(GL_TEXTURE_2D,currentTexture);
  }
  glPushMatrix();
  /*  Transform cube */
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* front */
  square(1, 4,5,6,7);
  /* back */
  square(2, 0,1,2,3);
  /* right */
  square(3, 5,6,2,1);
  /* left */
  square(4, 4,7,3,0);
  /* top */
  square(5, 6,7,3,2);
  /* bottom */
  square(6, 0,4,5,1);

  glPopMatrix();

  /* disable textures */
  glDisable(GL_TEXTURE_2D);
}

/*
 *  vertex
 *  ------
 *  Draw vertex in polar coordinates with normal
 */
static void vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   /*  For a sphere at the origin, the position
       and normal vectors are the same */
   glNormal3d(x,y,z);
   glTexCoord2d(th/360.0,ph/180.0+0.5);
   glVertex3d(x,y,z);
}

/*
 *  Draw a sphere
 *     at (x,y,z)
 *     radius (r)
 *     rotated rot around the y axis
 */
static void sphere(double x,double y,double z,double r,double rot)
{
  int th,ph;
  float yellow[] = {1.0,1.0,0.0,1.0};
  float emissions[] = {0.0,0.0,0.01*emission,1.0};
  glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
  glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
  glMaterialfv(GL_FRONT,GL_EMISSION,emissions);

  if (renderMode == DEF_RENDER) {
    /* enable textures */
    glEnable(GL_TEXTURE_2D);
    /* using the current texture */
    glBindTexture(GL_TEXTURE_2D,currentTexture);
  }
  glPushMatrix();

  /*  Offset, scale and rotate */
  glTranslated(x,y,z);
  glScaled(r,r,r);
  glRotated(rot,0,1,0);

  /*  Bands of latitude */
  for (ph=-90;ph<90;ph+=DEF_D) {
    glBegin(GL_QUAD_STRIP);
    for (th=0;th<=360;th+=2*DEF_D) {
      vertex(th,ph);
      vertex(th,ph+DEF_D);
    }
    glEnd();
  }

  glPopMatrix();

  /* disable textures */
  glDisable(GL_TEXTURE_2D);
}

/*
 *  cone
 *  ------
 *  Draws a cone
 *     at (x,y,z)
 *     with radius r and height h
 *     with 360/deg sides
 */
static void cone(double x,double y,double z,
		 double r,double h,int deg)
{
  int k;
  if (renderMode == DEF_RENDER) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,currentTexture);
  }
  glPushMatrix();

  /*  Transformation */
  glTranslated(x,y,z);
  glScaled(r,h,r);
  /* we're drawing this sideways
     because for some reason drawing upright doesn't work for normals */
  glRotated(-90,1,0,0);

  /* sides */
  glBegin(GL_TRIANGLES);
  for (k=0;k<=360;k+=deg){
    glNormal3f(0,0,1);
    /* center of cone is always center of texture */
    glTexCoord2f(0.5,0.5);
    glVertex3f(0,0,1);

    glNormal3f(Cos(k),Sin(k),r);
    /* need to cast to double or lose precision */
    glTexCoord2f((double)1/2*Cos(k)+0.5,(double)1/2*Sin(k)+0.5);
    glVertex3f(Cos(k),Sin(k),0);

    glNormal3f(Cos(k+deg),Sin(k+deg),r);
    /* need to cast to double or lose precision */
    glTexCoord2f((double)1/2*Cos(k+deg)+0.5,(double)1/2*Sin(k+deg)+0.5);
    glVertex3f(Cos(k+deg),Sin(k+deg),0);
  }
  glEnd();

  /* bottom circle */ 
  /* rotate back */
  glRotated(90,1,0,0);
  glBegin(GL_TRIANGLES);
  glNormal3f(0,-1,0);
  for (k=0;k<=360;k+=deg) {
    glTexCoord2f(0.5,0.5);
    glVertex3f(0,0,0);
    glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
    glVertex3f(Cos(k),0,Sin(k));
    glTexCoord2f(0.5*Cos(k+deg)+0.5,0.5*Sin(k+deg)+0.5);
    glVertex3f(Cos(k+deg),0,Sin(k+deg));
  }
  glEnd();

  glPopMatrix();

  /* disable textures */
  glDisable(GL_TEXTURE_2D);
}

/*
 *  cylinder
 *  ------
 *  Draw a cylinder
 *     at (x, y, z)
 *     with radius r and height h
 */
static void cylinder(double x,double y,double z,
		     double r,double h)
{
  int i,k;
  if (renderMode == DEF_RENDER) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,currentTexture);
  }
  glPushMatrix();

  /*  Transformation */
  glTranslated(x,y,z);
  glScaled(r,h,r);

  /*  sides */
  glBegin(GL_QUAD_STRIP);
  for (k=0;k<=360;k+=DEF_D) {
    /* These textures aren't exactly what I want, but I think they look cool */
    glNormal3f(Cos(k),0,Sin(k));
    /*  glTexCoord2f(Cos(k),Sin(k));  // vertical stripes */
    /*  glTexCoord2f(0,0);            // horizontal stripes */
    glTexCoord2f(-Cos(k),Sin(k));
    glVertex3f(Cos(k),+1,Sin(k));

    /*  glTexCoord2f(Cos(k),Sin(k));  // vertical stripes */
    /*  glTexCoord2f(1,1);            // horizontal stripes */
    glTexCoord2f(Cos(k),Sin(k));
    glVertex3f(Cos(k),-1,Sin(k));
  }
  glEnd();

  /* top and bottom circles */
  /* reuse the currentTexture on top and bottom) */
  for (i=1;i>=-1;i-=2) {
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0,i,0);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0,i,0);
    for (k=0;k<=360;k+=DEF_D) {
      glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
      glVertex3f(i*Cos(k),i,Sin(k));
    }
    glEnd();
  }

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

/*
 *  pyramid
 *  ------
 *  Draw a pyramid 
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 *  A pyramid is just a cone with 4 sides (360/90 degrees)
 */ 
static void pyramid(double x, double y, double z,
		    double dx, double dy, double dz,
		    double th)
{
  glPushMatrix();
  /*  Transform cube */
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  cone(0,0,0, 1,1, 90);

  glPopMatrix();
}

/*
 *  star
 *  ------
 *  Draw a star
 *     at (x, y, z)
 *     dimensions dx, dy, dz
 *     rotated th around the y axis
 *  A star is just 6 pyramids
 */
static void star(double x, double y, double z,
		 double dx, double dy, double dz,
		 double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /*top of diamond*/
  pyramid(0,0.5,0, 1,3,1, 0);

  /*back facing*/
  glPushMatrix();
  glRotatef(-90,1,0,0);
  pyramid(0,0.5,0, 1,3,1, 90);
  glPopMatrix();

  /*forward facing*/
  glPushMatrix();
  glRotatef(90,1,0,0);
  pyramid(0,0.5,0, 1,3,1, 0);
  glPopMatrix();

  /*right facing*/
  glPushMatrix();
  glRotatef(-90,0,0,1);
  pyramid(0,0.5,0, 1,3,1, 90);
  glPopMatrix();

  /*left facing*/
  glPushMatrix();
  glRotatef(90,0,0,1);
  pyramid(0,0.5,0, 1,3,1, -90);
  glPopMatrix();

  /*bottom of star*/
  glPushMatrix();
  glRotatef(180,1,0,0);
  pyramid(0,0.5,0, 1,3,1, 0);
  glPopMatrix();

  glPopMatrix();
}

/*
 *  spike
 *  ------
 *  Draw a spike
 *     at (x, y, z)
 *     radius r, height h, with 360/deg sides
 *     rotated ox around the x axis
 *     rotated oy around the y axis
 *     rotated oz around the z axis
 *  A spike is just a cone that is textured in spike
 */
static void spike(double x, double y, double z,
		  double r,double h,int deg,
		  double ox,double oy,double oz)
{
  currentTexture = textures[TEX_SPIKE];
  glPushMatrix();
  glRotated(oz,0,0,1);
  glRotated(oy,0,1,0);
  glRotated(ox,1,0,0);

  cone(x,y,z, r,h,deg);
  glPopMatrix();
  currentTexture = textures[TEX_DEFAULT];
}

/*
 *  board
 *  ------
 *  Draws the board as a 8x8 cubes on the screen
 */
static void board(void)
{
  int i,j;
  currentTexture = textures[TEX_GRASS];
  for (i=-8;i<8;i++){
    for(j=-8;j<8;j++){
      cube(i,-3,j, 1,0.2,1, 0);
    }
  }
  currentTexture = textures[TEX_DEFAULT];
}

/*
 *  BEGIN TOWER DEFINITIONS
 */

/*
 *  basicTower
 *  ------
 *  A basic tower just consists of several cylinders and a diamond
 */
static void basicTower(double x,double y,double z,
		       double dx,double dy,double dz,
		       double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* base */
  cylinder(0,0,0, 1,3);
  /* mid-section */
  cylinder(0,3,0, 1.5,1);
  /* top */
  cylinder(0,4,0, 1.2,1);

  glPopMatrix();
}

/*
 *  advancedTower
 *  ------
 *  An advanced tower is a basic tower plus spikes
 */
static void advancedTower(double x,double y,double z,
			  double dx,double dy,double dz,
			  double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  basicTower(0,0,0,1,1,1,0);

  /* 8x cones as spikes */
  spike(0,1.3,-3, 0.5,1,DEF_D, 90,0,0);
  spike(0,1.3,3,  0.5,1,DEF_D, -90,0,0);
  spike(3,1.3,0,  0.5,1,DEF_D, 0,0,90);
  spike(-3,1.3,0, 0.5,1,DEF_D, 0,0,-90);

  /* diagonal spikes */
  spike(0,1.3,-3, 0.5,1,DEF_D, 90,45,0);
  spike(0,1.3,3,  0.5,1,DEF_D, -90,45,0);
  spike(0,1.3,-3, 0.5,1,DEF_D, 90,-45,0);
  spike(0,1.3,3,  0.5,1,DEF_D, -90,-45,0);

  glPopMatrix();
}

/*
 *  coneTower
 *  ------
 *  A cone tower just consists of two cones and a cylinders
 */
static void coneTower(double x,double y,double z,
		      double dx,double dy,double dz,
		      double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* base */
  cone(0,-3,0, 1.4,4,DEF_D);
  /* mid-section */
  glPushMatrix();
  glRotated(180,1,0,0);
  cone(0,-3,0, 1.4,4,DEF_D);
  glPopMatrix();
  /* top */
  cylinder(0,4.0,0, 1.5,1.0);

  glPopMatrix();
}

/*
 *  advancedConeTower
 *  ------
 *  An advanced cone tower just consists of a cone tower and spikes
 */
static void advancedConeTower(double x,double y,double z,
			      double dx,double dy,double dz,
			      double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  coneTower(0,0,0, 1,1,1, 0);

  /* 8x cones as spikes */
  spike(0,1.3,-4, 0.5,1,DEF_D, 90,0,0);
  spike(0,1.3,4,  0.5,1,DEF_D, -90,0,0);
  spike(4,1.3,0,  0.5,1,DEF_D, 0,0,90);
  spike(-4,1.3,0, 0.5,1,DEF_D, 0,0,-90);

  /* diagonal spikes */
  spike(0,1.3,-4, 0.5,1,DEF_D, 90,45,0);
  spike(0,1.3,4,  0.5,1,DEF_D, -90,45,0);
  spike(0,1.3,-4, 0.5,1,DEF_D, 90,-45,0);
  spike(0,1.3,4,  0.5,1,DEF_D, -90,-45,0);

  glPopMatrix();
}

/*
 *  squareTower
 *  ------
 *  A square tower just consists of a cylinder, a cube, and a pyramid
 */
static void squareTower(double x,double y,double z,
		      double dx,double dy,double dz,
		      double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* base */
  cylinder(0,0,0, 1,3);
  /* mid-section */
  cube(0,3.5,0, 1.5,.5,1.5, 0);
  /* pyramid */
  pyramid(0,4,0, 0.75,0.75,0.75, 0);

  glPopMatrix();
}

/*
 *  advancedSquareTower
 *  ------
 *  An advanced square tower just consists of a square tower and spikes
 */
static void advancedSquareTower(double x,double y,double z,
				double dx,double dy,double dz,
				double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  /* base */
  squareTower(0,0,0, 1,1,1, 0);

  /* 8x cones as spikes */
  spike(0,1.3,-3.5, 0.5,1,DEF_D, 90,0,0);
  spike(0,1.3,3.5,  0.5,1,DEF_D, -90,0,0);
  spike(3.5,1.3,0,  0.5,1,DEF_D, 0,0,90);
  spike(-3.5,1.3,0, 0.5,1,DEF_D, 0,0,-90);

  /* diagonal spikes */
  spike(0,1.6,-3.5, 0.5,1,DEF_D, 90,45,0);
  spike(0,1.6,3.5, 0.5,1,DEF_D, -90,45,0);
  spike(0,1.6,-3.5, 0.5,1,DEF_D, 90,-45,0);
  spike(0,1.6,3.5, 0.5,1,DEF_D, -90,-45,0);

  glPopMatrix();
}

/*
 *  fireTower
 *  ------
 *  A fire tower is a plain tower with a sphere above it
 */
static void fireTower(double x,double y,double z,
		      double dx,double dy,double dz,
		      double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_FIRE];
  basicTower(0,0,0, 1,1,1,0);
  currentTexture = textures[TEX_FIRE];
  sphere(0,6.2,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  fireTower2
 *  ------
 *  A fire tower is an advanced tower with a sphere above it
 */
static void fireTower2(double x,double y,double z,
		      double dx,double dy,double dz,
		      double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_FIRE];
  advancedTower(0,0,0, 1,1,1,0);
  currentTexture = textures[TEX_FIRE];
  sphere(0,6.2,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  iceTower
 *  ------
 *  An ice tower is a plain tower with a star above it
 */
static void iceTower(double x,double y,double z,
		     double dx,double dy,double dz,
		     double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_ICE];
  basicTower(0,0,0, 1,1,1,0);
  currentTexture = textures[TEX_ICE];
  star(0,6.2,0, 0.25,0.25,0.25, towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  iceTower2
 *  ------
 *  An ice tower is an advanced tower with a star above it
 */
static void iceTower2(double x,double y,double z,
		      double dx,double dy,double dz,
		      double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_ICE];
  advancedTower(0,0,0, 1,1,1,0);
  currentTexture = textures[TEX_ICE];
  star(0,6.2,0, 0.25,0.25,0.25, towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  earthTower
 *  ------
 *  An earth tower is a cone tower with a sphere above it
 */
static void earthTower(double x,double y,double z,
		       double dx,double dy,double dz,
		       double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_EARTH];
  coneTower(0,0,0, 1,1,1, 0);
  currentTexture = textures[TEX_EARTH];
  sphere(0,6.2,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  earthTower2
 *  ------
 *  An earth tower 2 is an advanced cone tower with a sphere above it
 */
static void earthTower2(double x,double y,double z,
			double dx,double dy,double dz,
			double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_EARTH];
  advancedConeTower(0,0,0, 1,1,1, 0);
  currentTexture = textures[TEX_EARTH];
  sphere(0,6.2,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  poisonTower
 *  ------
 *  An poison tower is a square tower with a sphere above it
 */
static void poisonTower(double x,double y,double z,
			double dx,double dy,double dz,
			double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_POISON];
  squareTower(0,0,0, 1,1,1, 0);
  currentTexture = textures[TEX_POISON];
  sphere(0,6,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  poisonTower2
 *  ------
 *  An poison tower 2 is an advanced square tower with a sphere above it
 */
static void poisonTower2(double x,double y,double z,
			 double dx,double dy,double dz,
			 double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_POISON];
  advancedSquareTower(0,0,0, 1,1,1, 0);
  currentTexture = textures[TEX_POISON];
  sphere(0,6,0, 1,towerTh);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 *  GENERAL GLUT COMMANDS
 */

/*
 *  redisplayAll
 *  ------
 *  This is called whenever we need to draw the display
 */
void redisplayAll(void)
{
  /* 
     At one point, for some reason related to textures, I was losing the window, 
     so I was re-getting it here. 
     *** a fix may be available here: http://graphics.tudelft.nl/~paul/glut.html
     It's currently working without issue.
     window = glutGetWindow();
   */
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
 *  idle
 *  ------
 *  If we have movement on, then the light spins and the tower tops spin
 */
void idle(void)
{
  static int lastTime = 0;
  int time = glutGet(GLUT_ELAPSED_TIME);
  double t = time/1000.0;
  if (lastTime == 0 || time >= lastTime + 20) {
    lastTime = time;
    if (move) lightTh = fmod(90*t,360.0);
    if (topsRotate) towerTh = fmod(90*t,360.0);
    if (move || topsRotate) redisplayAll();
  }
}

/*
 *  findMousePosition
 *  ------
 *  Determines the OpenGL mouse position based on world coordinates 
 */
vertices3f findMousePosition(int x, int y)
{
  vertices3f vertices;
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

  vertices.posX = posX;
  vertices.posY = posY;
  vertices.posZ = posZ;

  return vertices;
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
  for (i = 0; i < Length(current_objects); i++){
    GLint red,green,blue;
    red = current_objects[i][5];
    green = current_objects[i][6];
    blue = current_objects[i][7];
    /* Found the object we need, break out of loop */
    if (pixel[0] == red && pixel[1] == green && pixel[2] == blue) {
      objectPicked = i;
      break;
    }
    /* Object not found, set to default */
    else {
      objectPicked = DEF_OBJ_PICKED;
    }
  }
}

/*
 *  BEGIN DISPLAY AND DRAW FUNCTIONS
 */

/*
 *  displayInit
 *  -------
 *  Initializes display
 */
void displayInit(void)
{
  /*  Set the font style */
  setFont("helvetica", 18);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
}

/*
 *  displayEye
 *  ------
 *  Sets where the user is looking 
 */
void displayEye(void)
{
  /*  Perspective - set eye position */
  if (mode) {
    double Ex = -2*dim*Sin(th)*Cos(ph);
    double Ey = +2*dim        *Sin(ph);
    double Ez = +2*dim*Cos(th)*Cos(ph);
    gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
  }
  /*  Orthogonal - set world orientation */
  else  {
    glRotatef(ph,1,0,0);
    glRotatef(th,0,1,0);
  }
}

/*
 *  drawAxes
 *  ------
 *  Draws the axes if desired
 */
void drawAxes(void)
{
  /* axes length */
  const double len=2.0;

  /*  Draw axes - no lighting */
  if (axes) {
    glDisable(GL_LIGHTING);
    glColor3fv(white);
    glBegin(GL_LINES);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(len,0.0,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,len,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,0.0,len);
    glEnd();
    /*  Label axes */
    glRasterPos3d(len,0.0,0.0);
    print("X");
    glRasterPos3d(0.0,len,0.0);
    print("Y");
    glRasterPos3d(0.0,0.0,len);
    print("Z");
  }
}

/*
 *  drawParameters
 *  ------
 *  Draws the parameters if desired
 */
void drawParameters(void)
{
  if (vals) {
    glColor3fv(white);
    /*  Display parameters */
    printAt(5,5,"Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",
	    th,ph,dim,fov,mode?"Perpective":"Orthogonal",light?"On":"Off");
    if (light) {
      printAt(5,45,"Distance=%d Elevation=%.1f",distance,lightY);
      printAt(5,25,"Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",
	      ambient,diffuse,specular,emission,shinyvec[0]);
    }
  }
}

/*
 *  drawLight 
 *  ------
 *  Draws the light (rotating sphere) if desired
 */
void drawLight(void)
{
  /*  Light switch */
  if (light) {
    /*  Translate intensity to color vectors */
    float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
    float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
    float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
    /*  Light position */
    float Position[]  = {distance*Cos(lightTh),lightY,distance*Sin(lightTh),1.0};
    /*  Draw light position as sphere (still no lighting here) */
    glColor3fv(white);
    sphere(Position[0],Position[1],Position[2] , 0.1,0);
    /*  OpenGL should normalize normal vectors */
    glEnable(GL_NORMALIZE);
    /*  Enable lighting */
    glEnable(GL_LIGHTING);
    /*  glColor sets ambient and diffuse color materials */
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    /*  Enable light 0 */
    glEnable(GL_LIGHT0);
    /*  Set ambient, diffuse, specular components and position of light 0 */
    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);
  }
  else
    glDisable(GL_LIGHTING);
}

/*
 *  drawObjects
 *  ------
 *  draw the board, default objects, and current objects to screen
 */
void drawObjects(void)
{
  int i;
  board();

  /* preview object */
  if (preview_object[0] != DEF_OBJ_SEL) {
    GLfloat oType,oX,oY,oZ;
    oType = preview_object[0];
    oX = preview_object[1];
    oY = preview_object[2];
    oZ = preview_object[3];
    currentTexture = preview_object[4];

    if (oType == OBJ_BASIC) basicTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_ADV) advancedTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_CONE) coneTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_ADV_CONE) advancedConeTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_SQUARE) squareTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_ADV_SQUARE) advancedSquareTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_FIRE) fireTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_FIRE2) fireTower2(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_ICE) iceTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_ICE2) iceTower2(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_EARTH) earthTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_EARTH2) earthTower2(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_POISON) poisonTower(oX,oY,oZ, 1,1,1, 0);
    else if (oType == OBJ_POISON2) poisonTower2(oX,oY,oZ, 1,1,1, 0);
    currentTexture = TEX_DEFAULT;
  }

  /* current objects */
  if (Length(current_objects) > 0) {
    for (i = 0; i < Length(current_objects); i++){
      GLfloat oType,oX,oY,oZ;
      GLint red,green,blue;
      oType = current_objects[i][0];
      oX = current_objects[i][1];
      oY = current_objects[i][2];
      oZ = current_objects[i][3];
      currentTexture = current_objects[i][4];
      red = current_objects[i][5];
      green = current_objects[i][6];
      blue = current_objects[i][7];

      /* draw the objects */
      if (renderMode == DEF_SELECT) {
	glDisable(GL_DITHER);
	glDisable(GL_LIGHTING);
	glColor3ub(red,green,blue);
      }
      if (oType == OBJ_BASIC) basicTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_ADV) advancedTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_CONE) coneTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_ADV_CONE) advancedConeTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_SQUARE) squareTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_ADV_SQUARE) advancedSquareTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_FIRE) fireTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_FIRE2) fireTower2(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_ICE) iceTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_ICE2) iceTower2(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_EARTH) earthTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_EARTH2) earthTower2(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_POISON) poisonTower(oX,oY,oZ, 1,1,1, 0);
      else if (oType == OBJ_POISON2) poisonTower2(oX,oY,oZ, 1,1,1, 0);
      currentTexture = TEX_DEFAULT;

      if (renderMode == DEF_SELECT) {
	glEnable(GL_DITHER);
	glEnable(GL_LIGHTING);
      }
    }
  }
}

/*
 *  BEGIN MAIN SECTION GLUT COMMANDS
 */

/*
 *  mainDisplay
 *  ------
 *  GLUT call this to display the main screen
 */
void mainDisplay(void)
{
  /* gray for the sidebar spacer */
  glClearColor(0.8, 0.8, 0.8, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSwapBuffers();
}

/*
 *  mainKey
 *  ------
 *  GLUT calls this routine when a non-special key is pressed
 */
void mainKey(unsigned char key,int x,int y)
{
  /*  Exit on ESC */
  if (key == 27) exit(0);
  /*  reset to default screen */
  else if (key == 'r' || key == 'R') reset();
  /*  toggle axes */
  else if (key == 'x' || key == 'X') axes = 1-axes;
  /*  toggle draw defaults */
  else if (key == 'f' || key == 'F') drawDefaults = 1-drawDefaults;
  /*  toggle text values displayed at bottom */
  else if (key == 'v' || key == 'V') vals = 1-vals;
  /*  toggle perspective mode */
  else if (key == 'p' || key == 'P') mode = 1-mode;
  /*  change field of view angle */
  else if (key == '-' && key>1) fov--;
  else if (key == '+' && key<179) fov++;
  /*  change dim */
  else if (key == 'i' && dim>1) dim -= 0.2;
  else if (key == 'I') dim += 0.2;
  /*  Toggle tower tops moving */
  else if (key == 'M') topsRotate = 1-topsRotate;
  /*  BEGIN LIGHTING FUNCTIONALITY */
  /*  Toggle lighting */
  else if (key == 'l' || key == 'L') light = 1-light;
  /*  Toggle light movement */
  else if (key == 'm') move = 1-move;
  /*  Move light */
  else if (key == '<') lightTh -= 1;
  else if (key == '>') lightTh += 1;
  /*  Light elevation */
  else if (key == '[') lightY -= 0.1;
  else if (key == ']') lightY += 0.1;
  /*  Ambient level */
  else if (key == 'a' && ambient>0) ambient -= 5;
  else if (key == 'A' && ambient<100) ambient += 5;
  /*  Diffuse level */
  else if (key == 'd' && diffuse>0) diffuse -= 5;
  else if (key == 'D' && diffuse<100) diffuse += 5;
  /*  Specular level */
  else if (key == 's' && specular>0) specular -= 5;
  else if (key == 'S' && specular<100) specular += 5;
  /*  Emission level */
  else if (key == 'e' && emission>0) emission -= 5;
  else if (key == 'E' && emission<100) emission += 5;
  /*  Shininess level */
  else if (key == 'n' && shininess>-1) shininess -= 1;
  else if (key == 'N' && shininess<7) shininess += 1;
  /*  BEGIN OPTION SELECTION FUNCTIONALITY */
  /*  Select object */
  else if (key == '0') objectSelected = DEF_OBJ_SEL;
  else if (key == '1') objectSelected = OBJ_FIRE;
  else if (key == '2') objectSelected = OBJ_FIRE2;
  else if (key == '3') objectSelected = OBJ_ICE;
  else if (key == '4') objectSelected = OBJ_ICE2;
  else if (key == '5') objectSelected = OBJ_EARTH;
  else if (key == '6') objectSelected = OBJ_EARTH2;
  else if (key == '7') objectSelected = OBJ_POISON;
  else if (key == '8') objectSelected = OBJ_POISON2;
  else if (key == '9') {
    if (objectSelected < OBJ_BASIC || objectSelected == OBJ_ADV_SQUARE) objectSelected = OBJ_BASIC;
    else if (objectSelected >= OBJ_BASIC && objectSelected != OBJ_ADV_SQUARE) objectSelected++;
  }
  /*  Toggle through all the different textures */
  else if (key == 't') {
    if (currentTextureSelected > 4) currentTextureSelected = TEX_DEFAULT;
    else currentTextureSelected++;
  }
  /*  Toggle preview mode (slightly buggy) */
  else if (key == 'w' || key == 'W') {
    preview = 1-preview;
    /* Reset preview object if preview is turned off */
    if (preview == DEF_PREVIEW) preview_object[0] = DEF_OBJ_SEL;
  }
  /*  Backspace and delete key to remove currently picked object */
  else if (key == 8 || key == 127) {
    int j;
    if (objectPicked != DEF_OBJ_PICKED) {
      for (j=0;j<DEF_CURRENT_OBJS_ATRS;j++)
	current_objects[objectPicked][j] = 0;
      if (debug) printf("Killed current object picked ID: %d\n", objectPicked);
      objectPicked = DEF_OBJ_PICKED;
    }
  }

  /*  Translate shininess power to value (-1 => 0) */
  shinyvec[0] = shininess<0 ? 0 : pow(2.0,shininess);

  /*  do it */
  redisplayAll();
}

/*
 *  special
 *  ------
 *  GLUT calls this routine when an special key is pressed
 */
void mainSpecial(int key,int x,int y)
{
  /*  Right arrow key - increase angle by 5 degrees */
  if (key == GLUT_KEY_RIGHT) th += 5;
  /*  Left arrow key - decrease angle by 5 degrees */
  else if (key == GLUT_KEY_LEFT) th -= 5;
  /*  Up arrow key - increase elevation by 5 degrees */
  else if (key == GLUT_KEY_UP) ph += 5;
  /*  Down arrow key - decrease elevation by 5 degrees */
  else if (key == GLUT_KEY_DOWN) ph -= 5;
  /*  Function F3 - toggle distance */
  else if (key == GLUT_KEY_F3) distance = (distance==2) ? 5 : 2;
  /*  Hold shift */
  //else
  /*  Keep angles at +/- 360 degrees */
  th %= 360;
  ph %= 360;

  /*  do it */
  redisplayAll();
}

/*
 *  reshape
 *  ------
 *  GLUT calls this routine when the window is resized
 */
void mainReshape(int width,int height)
{
  windowHeight = height;
  windowWidth = width;

  /* main window stuff */
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,width,height,0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* set subwindow positions */
  /* set screen position, reshape */
  glutSetWindow(screen);
  glutPositionWindow(0, 0);
  glutReshapeWindow(windowWidth-DEF_SIDEBAR_WIDTH-DEF_SPACER, windowHeight);

  /* set sidebar position, reshape */
  glutSetWindow(sidebar);
  glutPositionWindow(windowWidth-DEF_SIDEBAR_WIDTH,0);
  glutReshapeWindow(DEF_SIDEBAR_WIDTH,windowHeight);
}

/*
 *  mainVisible
 *  ------
 *  If the program is visible, then do idle function
 */
void mainVisible(int vis)
{
  glutIdleFunc(vis == GLUT_VISIBLE ? idle: NULL);
}

/*
 *  BEGIN SCREEN SECTION GLUT COMMANDS
 */

/*
 *  screenDisplay
 *  ------
 *  Display the actual scene
 */
void screenDisplay(void)
{
  /*  Setup, place eye position */
  displayInit();
  displayEye();
  /*  Draw axes, parameters, light source */
  drawAxes();
  drawParameters();
  drawLight();

  /* Draw scene */
  drawObjects();
  /* object selection */
  /* first pass picking mode, then render mode */
  if (renderMode == DEF_SELECT) {
    processPicks();
    renderMode = DEF_RENDER;
  }
  else {
    /*  Flush and swap */
    glFlush();
    glutSwapBuffers();
  }
  
  errCheck("display sanity check");
}

/*
 *  screenProject
 *  ------
 *  Projection determination method
 */
void screenProject(double fov, double asp, double dim)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  /*  Perspective transformation */
  if (fov)
    gluPerspective(fov,asp,dim/16,16*dim);
  /*  Orthogonal transformation */
  else
    glOrtho(-asp*dim,asp*dim,-dim,+dim,-dim,+dim);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*
 *  screenReshape
 *  ------
 *  Resize for the display screen area
 */
void screenReshape(int width, int height)
{
  /* set the aspect ratio */
  asp = (height>0) ? (double)width/height : 1;
  windowHeight = height;

  /*  Set the viewport to the entire window */
  glViewport(0,0, width,height);
  screenProject(mode?fov:0,asp,dim);
}

/*
 *  screenMouse
 *  ------
 *  If an object is selected, left-click the mouse in order to place it
 *  If an object is not selected, left-click mouse on tower to select it
 *  (this functionality actually happens in screenDisplay/drawObjects)
 */ 
void screenMouse(int btn, int state, int x, int y)
{
  vertices3f v3f;

  /* return unless left mouse click and object selected */
  if ((btn != GLUT_LEFT_BUTTON || state != GLUT_DOWN)) 
    return;
  
  v3f = findMousePosition(x,y);
  mouseX = x;
  mouseY = y;
  renderMode = DEF_SELECT;

  /* We're adding a new object */
  if (objectSelected != 0) {
    renderMode = DEF_RENDER;

    /* add the object to current objects */
    current_objects[lastCurrentObject][0] = objectSelected;
    current_objects[lastCurrentObject][1] = (int) v3f.posX;
    current_objects[lastCurrentObject][2] = 0;
    current_objects[lastCurrentObject][3] = (int) v3f.posZ;
    current_objects[lastCurrentObject][4] = currentTextureSelected;
    /* red, green, blue */
    current_objects[lastCurrentObject][5] = currentRed;
    current_objects[lastCurrentObject][6] = currentGreen;
    current_objects[lastCurrentObject][7] = currentBlue;

    /* increment red, then green, the blue to get unique composite RGBs 
       for our object selection
     */
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
    if (debug) printf("just added object id: %d\n",lastCurrentObject);

    /* increment last current object, we are limiting to 30 objects, so reset if at 30 */
    lastCurrentObject++;
    if (lastCurrentObject == DEF_CURRENT_OBJS_SIZE) lastCurrentObject = 0;
    /* reset object selected back to default unless shift key is held */
    if (glutGetModifiers() != GLUT_ACTIVE_SHIFT) objectSelected = DEF_OBJ_SEL;
  }

  redisplayAll();
}

/*
 *  Display the mouse position
 *  TODO: show opacity-based object where drawing it
 */ 
void screenPmotion(int x, int y)
{
  if (preview && objectSelected != DEF_OBJ_SEL) {
    vertices3f v3f= findMousePosition(x,y);
    preview_object[0] = objectSelected;
    preview_object[1] = (int)v3f.posX;
    preview_object[2] = 0;
    preview_object[3] = (int)v3f.posZ;
    preview_object[4] = currentTextureSelected;

    redisplayAll();
  }
}

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

/*
 *  INITIALIZATION FUNCTIONS
 */

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
  glutKeyboardFunc(mainKey); 
  glutSpecialFunc(mainSpecial);
  glutMouseFunc(sidebarMouse);
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
  glutKeyboardFunc(mainKey);
  glutSpecialFunc(mainSpecial);
  glutMouseFunc(screenMouse);
  glutPassiveMotionFunc(screenPmotion);
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
   */
  /* for some reason, order matters here (I don't know C well enough */
  textures[TEX_BRICK] = loadTexBMP("txBrick14.bmp");
  textures[TEX_FIRE] = loadTexBMP("txlava1.bmp");
  textures[TEX_ICE] = loadTexBMP("txIce7.bmp");
  textures[TEX_EARTH] = loadTexBMP("txRock5.bmp");
  textures[TEX_POISON] = loadTexBMP("txFloor38.bmp");
  textures[TEX_SPIKE] = loadTexBMP("txFloor4.bmp");
  textures[TEX_GRASS] = loadTexBMP("txGrass5.bmp");
}

/*
 *  main
 *  ------
 *  main function
 */
int main(int argc,char* argv[])
{
  glutInit(&argc,argv);
  /*  Request double buffered, true color window with Z buffering */
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(windowWidth,windowHeight);

  window = glutCreateWindow(windowName);
  /*  glutFullScreen();  // I like full screen mode */
  glutDisplayFunc(mainDisplay);
  glutReshapeFunc(mainReshape);
  glutSpecialFunc(mainSpecial);
  glutKeyboardFunc(mainKey);
  glutVisibilityFunc(mainVisible);

  reset();
  sidebarInit();
  screenInit();

  initTextures();

  redisplayAll();
  glutMainLoop();
  return 0;
}
