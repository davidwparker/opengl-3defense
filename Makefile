#-std=c99 gets rid of warning: initializer element is not computable at load time
GCC_OPTIONS=-Wall -pedantic -std=c99
GL_OPTIONS=-framework OpenGL -framework GLUT 
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)

TARGETS=hw3.c

.c: 
	gcc $(TARGETS) $(OPTIONS) -o ./hw3