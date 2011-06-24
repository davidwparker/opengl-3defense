typedef struct point {
  float x;
  float y;
  float z;
} point;

typedef struct rgb {
  int r;
  int g;
  int b;
} rgb;

typedef struct pathCube {
  point p;
  int texture;
  int rotation;
  int dir;
} pathCube;

typedef struct tower {
  int id;
  int type;
  point translation;
  point scale;
  point rotation;
  int texture;
  rgb rgb;
} tower;

typedef struct minion {
  int id;
  int type;
  point translation;
  point scale;
  point rotation;
  int texture;
  rgb rgb;
  int health;
  int money;
  int speed;
} minion;
