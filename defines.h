/*  Poor man's approximation of Cosine and Sine in degrees  */
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))
/*  Determine number of elements in an array  */
#define Length(x) (sizeof (x) / sizeof *(x))

#define DEF_DEBUG 0
#define DEF_FULL_SCREEN 0

/*  Defaults for window sizing  */
/*  Keeping this for defaults, although we're using full screen mode  */
#define DEF_WINDOW_HEIGHT 700
#define DEF_WINDOW_WIDTH 1000
/*  Space between sidebar and screen display  */
#define DEF_SPACER 10
/*  Sidebar's permanent width  */
#define DEF_SIDEBAR_WIDTH 300
/*  Line height for text  */
#define DEF_TEXT_Y_OFFSET 20

/*  Font styling  */
#define DEF_FONT_STYLE GLUT_BITMAP_HELVETICA_10

/*  Projection  */
#define DEF_ASP 1
#define DEF_DIM 25
#define DEF_TH 250
#define DEF_PH 40
#define DEF_FOV 55
#define DEF_ECX 2
#define DEF_ECY 0
#define DEF_ECZ 4

/*  Draw defaults  */
#define DEF_DRAW_DEFAULTS 0
#define DEF_GRID 1
#define DEF_AXES 0
#define DEF_VALS 1
#define DEF_D 5

/*  Animation  */
#define DEF_MOVE_LIGHT 1
#define DEF_L_PH 90
#define DEF_MOVE_MINIONS 1
#define DEF_MOVE_TOWER_TOPS 0
#define DEF_TOWER_TH 0

/*  Game Data  */
#define DEF_LIVES 10
#define DEF_MONEY 500
#define DEF_SCROLLS 0
#define DEF_WAVE 0
#define DEF_LAST_WAVE 10

/*  Object definitions  */
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
#define OBJ_PYRAMID 15
#define OBJ_ADV_PYRAMID 16

/*  Object Selection  */
#define DEF_CURRENT_OBJS_SIZE 57
#define DEF_LAST_CURRENT_OBJECT 0
#define DEF_OBJ_SEL 0
#define DEF_OBJ_PICKED -1
#define DEF_BAD_POINT -255
#define DEF_PREVIEW 1
#define DEF_RENDER 1
#define DEF_SELECT 2
#define DEF_CURRENT_RED 5
#define DEF_CURRENT_GREEN 5
#define DEF_CURRENT_BLUE 5

/*  Minions  */
#define DEF_MINION_OBJ 0
#define DEF_NORTH 270
#define DEF_EAST 180
#define DEF_SOUTH 90
#define DEF_WEST 0
#define DEF_PATH_LEN 45
#define DEF_FULL_PATH_LEN 50

/*  Lighting  */
#define DEF_LIGHT 1
#define DEF_DISTANCE 40
#define DEF_AMBIENT 35
#define DEF_DIFFUSE 100
#define DEF_EMISSION 0
#define DEF_SPECULAR 0
#define DEF_SHININESS 0
#define DEF_L_Y 0

/*  Texture definitions  */
#define TEX_DEFAULT 0
#define TEX_BRICK 1
#define TEX_FIRE 2
#define TEX_ICE 3
#define TEX_EARTH 4
#define TEX_POISON 5
#define TEX_SPIKE 6
#define TEX_GRASS 7
#define TEX_WOOD 8
#define TEX_EVERGREEN 9
#define TEX_BRICK2 10
#define TEX_CRATE 11
#define TEX_STREET1 12
#define TEX_STREET2 13
#define TEX_STREET3 14
#define TEX_STREET4 15
#define TEX_STREET5 16
#define TEX_STREET6 17

/*  Background (skybox)  */
#define BACK_FRONT 0
#define BACK_RIGHT 1
#define BACK_LEFT 2
#define BACK_BACK 3
#define BACK_UP 4
#define BACK_DOWN 5

/*  Shadows  */
#define DEF_D_FLOOR 45
#define DEF_Y_FLOOR -3
