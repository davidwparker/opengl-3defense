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

typedef struct pathC {
  point p;
  int texture;
  int rotation;
} pathC;

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
  point translation;
  point scale;
  point rotation;
  int texture;
  rgb rgb;
} minion;
