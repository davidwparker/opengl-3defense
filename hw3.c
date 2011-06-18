/*
 * Homework Assignment #3
 * David Parker
 * June 14-29, 2011
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
 * PROTOTYPES^
 * STRUCTS^
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
 * --leadTexBMP
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
 * ---basicTower (1)
 * ---advancedTower (2)
 * ---coneTower (3)
 * ---advancedConeTower (4)
 * ---squareTower (5)
 * ---advancedSquareTower (6)
 * ---fireTower (7)
 * ---fireTower2 (8)
 * ---iceTower (9)
 * ---iceTower2 (10)
 * ---earthTower (11)
 * ---earthTower2 (12)
 * ---poisonTower (13)
 * ---poisonTower2 (14)
 * -general glut functions^
 * --redisplayAll
 * --idle
 * --findMousePosition
 * -display and draw functions^
 * --displayInit
 * --displayEye
 * --drawAxes
 * --drawParameters
 * --drawLight
 * -main glut commands^
 * --mainDisplay
 * --mainKey
 * --mainSpecial
 * --mainVisible
 * --mainReshape
 * -screen area glut commands^
 * --screenDisplay
 * --screenProject
 * --screenReshape
 * -sidebar area glut commands^
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
#define DEF_DIM 30
#define DEF_TH -60
#define DEF_PH 30
#define DEF_FOV 15
#define DEF_D 5
#define DEF_AXES 0
#define DEF_VALS 1
#define DEF_TOPS_ROTATE 1
/////#define DEF_SPIKES_ROTATE 1
#define DEF_TOWER_TH 0
#define DEF_DEBUG 1

/*  Object selection */
#define DEF_OBJ_SEL 0

/*  Lighting */
#define DEF_LIGHT 1
#define DEF_MOVE 1
#define DEF_DISTANCE 5
#define DEF_AMBIENT 30
#define DEF_DIFFUSE 100
#define DEF_EMISSION 0
#define DEF_SPECULAR 0
#define DEF_SHININESS 0
#define DEF_L_TH 90
#define DEF_L_Y 0

/*  Texture definitions */
#define TEX_DEFAULT 0
#define TEX_BRICK 1
#define TEX_SPIKE 2
#define TEX_FIRE 3
#define TEX_ICE 4
#define TEX_ROCK 5
#define TEX_POISON 6
#define TEX_GRASS 7

/*  Prototypes */
void screenReshape(int width, int height);
void sidebarReshape(int width, int height);

/*  Structs */
typedef struct vertices3f {
  GLfloat posX;
  GLfloat posY;
  GLfloat posZ;
} vertices3f;

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
int objectSelected=DEF_OBJ_SEL;

/*  Globals for lighting */
int light=DEF_LIGHT;          /* toggle light */
int move=DEF_MOVE;            /* toggle move light */
int distance=DEF_DISTANCE;    /* light distance */
int ambient=DEF_AMBIENT;      /* ambient intensity % */
int diffuse=DEF_DIFFUSE;      /* diffuse intensity % */
int emission=DEF_EMISSION;    /* emission intensity % */
int specular=DEF_SPECULAR;    /* specular intensity % */
int shininess=DEF_SHININESS;  /* shininess (power of two) */
float shinyvec[1];     /* shininess (value) */
int lightTh=DEF_L_TH;  /* light azimuth */
float lightY=DEF_L_Y;  /* elevation of light */
float white[]={1,1,1,1};

/*  Globals for textures */
unsigned int textures[8];       /* currently holding eight textures */
int currentTexture=TEX_DEFAULT; /* no texture assigned as default */

/*  cube vertices */
GLfloat cube_v[][3] = {
  {-1.0,-1.0,-1.0},{+1.0,-1.0,-1.0},{+1.0,+1.0,-1.0},
  {-1.0,+1.0,-1.0},{-1.0,-1.0,+1.0},{+1.0,-1.0,+1.0},
  {+1.0,+1.0,+1.0},{-1.0,+1.0,+1.0}
};

/*  
 *  reset
 *  ------
 *  reset all values back to defaults 
 */
void reset()
{
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
  drawDefaults = DEF_DRAW_DEFAULTS;
  topsRotate   = DEF_TOPS_ROTATE;
  towerTh      = DEF_TOWER_TH;
  objectSelected = DEF_OBJ_SEL;

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
void square(int s, int a, int b, int c, int d)
{
  glBegin(GL_POLYGON);

  glColor3fv(white);
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
  glEnable(GL_TEXTURE_2D);
  /* using the current texture */
  glBindTexture(GL_TEXTURE_2D,currentTexture);

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

  /* enable textures */
  glEnable(GL_TEXTURE_2D);
  /* using the current texture */
  glBindTexture(GL_TEXTURE_2D,currentTexture);

  glPushMatrix();

  /*  Offset, scale and rotate */
  glTranslated(x,y,z);
  glScaled(r,r,r);
  glRotated(rot,0,1,0);

  /*  White ball */
  glColor3fv(white);

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
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();

  /*  Transformation */
  glTranslated(x,y,z);
  glScaled(r,h,r);
  /* we're drawing this sideways
     because for some reason drawing upright doesn't work for normals */
  glRotated(-90,1,0,0);

  /* sides */
  glBindTexture(GL_TEXTURE_2D,currentTexture);
  glColor3f(1,1,1);
  glBegin(GL_TRIANGLES);
  for (k=0;k<=360;k+=deg){
    /* the normals probably aren't 100% correct :( */
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
  glColor3f(1,1,1);
  glBegin(GL_TRIANGLES);
  glNormal3f(0,-1,0);
  /* TODO: add texture */
  for (k=0;k<=360;k+=deg) {
    glVertex3f(0,0,0);
    glVertex3f(Cos(k),0,Sin(k));
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
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();

  /*  Transformation */
  glTranslated(x,y,z);
  glScaled(r,h,r);

  /*  sides */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glBindTexture(GL_TEXTURE_2D,currentTexture);
  glColor3f(1,1,1);
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
  glColor3f(1,1,1);
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
 *  Draws the board as a cube on the screen
 */
static void board()
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

  currentTexture = textures[TEX_ROCK];
  coneTower(0,0,0, 1,1,1, 0);
  currentTexture = textures[TEX_ROCK];
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

  currentTexture = textures[TEX_ROCK];
  advancedConeTower(0,0,0, 1,1,1, 0);
  currentTexture = textures[TEX_ROCK];
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
  if (move) {
    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    lightTh = fmod(90*t,360.0);
    towerTh = fmod(90*t,360.0);
    redisplayAll();
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

  /*  Erase the window and the depth buffer */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /*  Enable Z-buffering in OpenGL */
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
    glColor3f(1,1,1);
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
    glColor3f(1,1,1);
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
    glColor3f(1,1,1);
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
 *  BEGIN MAIN SECTION GLUT COMMANDS
 */

/*
 *  mainDisplay
 *  ------
 *  GLUT call this to display the main screen
 */
void mainDisplay()
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
  /*  BEGIN LIGHTING FUNCTIONALITY */
  /*  Toggle lighting */
  else if (key == 'l' || key == 'L') light = 1-light;
  /*  Toggle light movement */
  else if (key == 'm' || key == 'M') move = 1-move;
  /*  Move light */
  else if (key == '<') lightTh += 1;
  else if (key == '>') lightTh -= 1;
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

  /*  Draw scene */
  board();

  //  basicTower(0,0,0, 1,1,1, 0);
  //  advancedTower(0,0,0, 1,1,1, 0);
  //  coneTower(4,0,0, 1,1,1, 0);
  //  advancedConeTower(4,0,0, 1,1,1, 0);
  //  squareTower(0,0,0, 1,1,1, 0);
  //  advancedSquareTower(0,0,0, 1,1,1, 0);


  //  fireTower(4,0,0, 1,1,1, 0);
    fireTower2(-2,0,-2, 1,1,1, 0);
  //  iceTower(0,0,0, 1,1,1, 0);
    iceTower2(2,0,2, 1,1,1, 0);
  //  earthTower(4,0,0, 1,1,1, 0);
    earthTower2(2,0,-2, 1,1,1, 0);
  //  poisonTower(0,0,0, 1,1,1, 0);
    poisonTower2(-2,0,2, 1,1,1, 0);

  errCheck("display sanity check");

  /*  Flush and swap */
  glFlush();
  glutSwapBuffers();
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
 *  BEGIN SIDEBAR SECTION GLUT COMMANDS
 */

/*
 *  sidebarDisplay
 *  ------
 *  The display for the sidebar
 */
void sidebarDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glColor3f(1,1,1);

  /* These display locations need to line up with mouse clicks */
  printAt(100, windowHeight-DEF_TEXT_Y_OFFSET, "EXTRA CONTROLS");
  printAt(5, windowHeight-DEF_TEXT_Y_OFFSET*2, "Select a tower to draw:");

  if (objectSelected == 1) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*3, "basic");

  glColor3f(1,1,1);
  if (objectSelected == 2) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*4, "advanced");

  glColor3f(1,1,1);
  if (objectSelected == 3) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*5, "cone");

  glColor3f(1,1,1);
  if (objectSelected == 4) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*6, "advanced cone");

  glColor3f(1,1,1);
  if (objectSelected == 5) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*7, "square");

  glColor3f(1,1,1);
  if (objectSelected == 6) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*8, "advanced square");

  glColor3f(1,1,1);
  if (objectSelected == 7) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*9, "fire");

  glColor3f(1,1,1);
  if (objectSelected == 8) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*10, "advanced fire");

  glColor3f(1,1,1);
  if (objectSelected == 9) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*11, "ice");

  glColor3f(1,1,1);
  if (objectSelected == 10) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*12, "advanced ice");

  glColor3f(1,1,1);
  if (objectSelected == 11) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*13, "earth");

  glColor3f(1,1,1);
  if (objectSelected == 12) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*14, "advanced earth");

  glColor3f(1,1,1);
  if (objectSelected == 13) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*15, "poison");

  glColor3f(1,1,1);
  if (objectSelected == 14) glColor3f(1,0,1);
  printAt(10, windowHeight-DEF_TEXT_Y_OFFSET*16, "advanced poison");

  glColor3f(1,1,1);
  printAt(5, windowHeight-DEF_TEXT_Y_OFFSET*21, "For best (accurate) results, ");
  printAt(5, windowHeight-DEF_TEXT_Y_OFFSET*22, "draw on the board");

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
  /* only left mouse button */
  if (btn != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

  objectSelected=0;
  /* mouse position starts at upper left */
  if (x < 180 && x>= 5) {
    if (y >= DEF_TEXT_Y_OFFSET*2+5 && y < DEF_TEXT_Y_OFFSET*3+9) objectSelected=1;
    else if (y >= DEF_TEXT_Y_OFFSET*3+9 && y < DEF_TEXT_Y_OFFSET*4+9) objectSelected=2;
    else if (y >= DEF_TEXT_Y_OFFSET*4+9 && y < DEF_TEXT_Y_OFFSET*5+9) objectSelected=3;
    else if (y >= DEF_TEXT_Y_OFFSET*5+9 && y < DEF_TEXT_Y_OFFSET*6+9) objectSelected=4;
    else if (y >= DEF_TEXT_Y_OFFSET*6+9 && y < DEF_TEXT_Y_OFFSET*7+9) objectSelected=5;
    else if (y >= DEF_TEXT_Y_OFFSET*7+9 && y < DEF_TEXT_Y_OFFSET*8+9) objectSelected=6;
    else if (y >= DEF_TEXT_Y_OFFSET*8+9 && y < DEF_TEXT_Y_OFFSET*9+9) objectSelected=7;
    else if (y >= DEF_TEXT_Y_OFFSET*9+9 && y < DEF_TEXT_Y_OFFSET*10+9) objectSelected=8;
    else if (y >= DEF_TEXT_Y_OFFSET*10+9 && y < DEF_TEXT_Y_OFFSET*11+9) objectSelected=9;
    else if (y >= DEF_TEXT_Y_OFFSET*11+9 && y < DEF_TEXT_Y_OFFSET*12+9) objectSelected=10;
    else if (y >= DEF_TEXT_Y_OFFSET*12+9 && y < DEF_TEXT_Y_OFFSET*13+9) objectSelected=11;
    else if (y >= DEF_TEXT_Y_OFFSET*13+9 && y < DEF_TEXT_Y_OFFSET*14+9) objectSelected=12;
    else if (y >= DEF_TEXT_Y_OFFSET*14+9 && y < DEF_TEXT_Y_OFFSET*15+9) objectSelected=13;
    else if (y >= DEF_TEXT_Y_OFFSET*15+9 && y < DEF_TEXT_Y_OFFSET*16+9) objectSelected=14;
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

  /*  glutCreateMenu(sidebarMenu);
  glutAddMenuEntry("Select a Tower", 0);
  glutAddMenuEntry("-------------",0);
  glutAddMenuEntry("[u] basic", 'u');
  glutAddMenuEntry("[h] advanced", 'h');
  glutAddMenuEntry("[p] cone", 'p');
  glutAddMenuEntry("[i] advanced cone", 'i');
  glutAddMenuEntry("[s] square", 's');
  glutAddMenuEntry("[t] advanced square", 't');
  glutAddMenuEntry("[w] fire", 'w');
  glutAddMenuEntry("[o] advanced fire", 'o');
  glutAddMenuEntry("[w] ice", 'w');
  glutAddMenuEntry("[o] advanced ice", 'o');
  glutAddMenuEntry("[w] earth", 'w');
  glutAddMenuEntry("[o] advanced earth", 'o');
  glutAddMenuEntry("[w] poison", 'w');
  glutAddMenuEntry("[o] advanced poison", 'o');
  glutAttachMenu(GLUT_RIGHT_BUTTON); */
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
  //  glutPassiveMotionFunc(screenPmotion);
  //  glutMouseFunc(screenMouse);
  /*
  glutCreateMenu(screenMenu);
  glutAddMenuEntry("[r] reset",'r');
  glutAddMenuEntry("[f] toggle defaults",'f');
  glutAddMenuEntry("[b] toggle board",'b');
  glutAttachMenu(GLUT_RIGHT_BUTTON);*/
}

/*
 *  initTextures
 *  ------
 *  initializes all of our textures
 */
void initTextures(void)
{
  textures[TEX_BRICK] = loadTexBMP("Brick14.bmp");
  textures[TEX_FIRE] = loadTexBMP("lava1.bmp");
  textures[TEX_SPIKE] = loadTexBMP("Floor4.bmp");
  textures[TEX_ICE] = loadTexBMP("Ice7.bmp");
  textures[TEX_ROCK] = loadTexBMP("Rock5.bmp");
  textures[TEX_POISON] = loadTexBMP("Floor38.bmp");
  textures[TEX_GRASS] = loadTexBMP("Grass5.bmp");
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

  sidebarInit();
  screenInit();

  initTextures();

  redisplayAll();
  glutMainLoop();
  return 0;
}
