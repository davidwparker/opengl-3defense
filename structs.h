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
  /* game data */
  char* name;
  int level;
  int range;
  int damage;
  int fireRate;
  int cost;
  char* description;
} tower;

typedef struct minion {
  int id;
  int type;
  point translation;
  point scale;
  point rotation;
  int texture;
  rgb rgb;
  /* game data */
  char* name;
  int damage;
  int health;
  int money;
  int speed;
  int wave;
} minion;
