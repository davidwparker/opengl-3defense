#include "project.h"

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
