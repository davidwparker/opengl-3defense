# Target to build
TARGET=project

# GL Libraries
# LINUX
#LIBS=-lglut -lGLU
# OSX
LIBS=-framework OpenGL -framework GLUT 

all: $(TARGET)

#  Generic compile rules
.c.o:
	gcc -c -O -Wall $<

#  Generic compile and link
%: %.c project.a
	gcc -Wall -O3 -o ./$@ $^ $(LIBS)

#  Delete unwanted files - Linux or OS/X
clean:;rm -f $(TARGET) *.o *.a

#  Create archive
project.a:globals.o print.o loadTexBMP.o loadObj.o shapes.o models.o towers.o general.o initialize.o drawing.o window.o screen.o sidebar.o
	ar -rcs project.a $^
