/*  Printing Convenience (print.c)  */
void setFont(char* name, int size);
void printv(va_list args, const char* format);
void print(const char* format , ...);
void printAt(int x,int y, const char* format , ...);
void errCheck(char* where);
void fatal(const char* format, ...);

/*  Texture loading (loadTexBMP.c)  */
unsigned int loadTexBMP(char* file);

/*  Object loading (loadObj.c)  */
int loadOBJ(char* file);

/*  Shapes (shapes.c)  */
void square(int s, int a, int b, int c, int d);
void cube(double x,double y,double z,
	  double dx,double dy,double dz,
	  double th);
void vertex(double th, double ph);
void circle(int r);
void sphere(double x,double y,double z,double r,double rot);
void cone(double x,double y,double z, double r, double h,int deg);
void cylinder(double x,double y,double z,
	      double r,double h);

/*  Models (models.c)  */
void pyramid(double x, double y, double z,
	     double dx, double dy, double dz,
	     double th);
void star(double x, double y, double z,
	  double dx, double dy, double dz,
	  double th);
void spike(double x, double y, double z,
	   double r,double h,int deg,
	   double ox,double oy,double oz);
void board(void);
void pathBlock(pathCube p);
void path(void);
void crate(double x, double y, double z,
	   double dx,double dy,double dz,
	   double th);
void crates(double x, double y, double z,
	    double dx,double dy,double dz,
	    double th);
void evergreenTree1(double x, double y, double z,
		    double dx,double dy,double dz,
		    double th);
void evergreenTree2(double x, double y, double z,
		    double dx,double dy,double dz,
		    double th);
void evergreenForest(double x, double y, double z,
		     double dx,double dy,double dz,
		     double th);
void evergreenForest1(double x, double y, double z,
		      double dx,double dy,double dz,
		      double th);
void wall(double x, double y, double z,
	  double dx,double dy,double dz,
	  double th);
void keep(double x, double y, double z,
	  double dx,double dy,double dz,
	  double th);
void shotModel(shot s);
void minionModel(minion m);

/*  Towers (towers.c)  */
void basicTower(tower t);
void advancedTower(tower t);
void coneTower(tower t);
void advancedConeTower(tower t);
void squareTower(tower t);
void advancedSquareTower(tower t);
void fireTower(tower t);
void fireTower2(tower t);
void iceTower(tower t);
void iceTower2(tower t);
void earthTower(tower t);
void earthTower2(tower t);
void poisonTower(tower t);
void poisonTower2(tower t);

/*  General Convenience (general.c)- the catchall  */
void changeObjectSelected(int newObjectSelected);
void setCurrentTowerData(int type);
point findMousePosition(int x, int y);
point findPreviewPosition(int x, int y);
void idle(void);
void incrementCurrentRGB(void);
void processPicks(void);
void redisplayAll(void);
void reset(void);

/*  Initialization (initialize.c)  */
void initialize(void);
void initTextures(void);
void initBackground(void);
void initObjs(void);
void initMinions(void);
void initShots(void);
void initWaves(void);
void initPath(void);
void initPreviewPoints(void);
void initDefaultTowers(void);
void screenInit(void);
void sidebarInit(void);

/*  Drawing (drawing.c)  */
void drawAxes(void);
void drawParameters(void);
void drawGrid(void);
void drawBackground(double d);
void drawLight(void);
void drawBoard(void);
void drawPath(void);
void drawForests(void);
void drawKeep(void);
void drawShots(void);
void drawMinions(void);
void drawObjects(void);
void drawScene(void);

/*  Animation (animate.c)  */
void timer(int toggle);
void slowAnimate(void);
void moveLight(void);
void moveMinion(int k, int i, int j);
void moveMinions(void);
void moveShots(void);
void moveTowerTops(void);

/*  Collisions (collision.c)  */
void checkCollisions(void);
void checkTowerRange(void);

/*  Shadows (shadow.c)  */
void shadowProjection(float L[4], float E[4], float N[4]);

/*  Main window (window.c)  */
void windowDisplay(void);
void windowKey(unsigned char key,int x,int y);
void windowSpecial(int key,int x,int y);
void windowReshape(int width, int height);
void windowVisible(int vis);

/*  Screen display (screen.c)  */
void displayInit(void);
void displayEye(void);
void screenDisplay(void);
void screenProject(double fov, double asp, double dim);
void screenReshape(int width, int height);
void screenMouse(int btn, int state, int x, int y);
void screenPmotion(int x, int y);

/*  Sidebar display (sidebar.c)  */
void sidebarRow(int x, int y, int obj, char* text);
void sidebarDisplay(void);
void sidebarReshape(int width, int height);
void sidebarMouse(int btn, int state, int x, int y);

/*  Gameplay (gameplay.c)  */
int calculateDamageToMinion(int k, int j, int i);
void modifyLives(int die, int damage);
void modifyMoney(int what, int amount);
void modifyScore(int k);
void removeMinion(int k, int j);
void removeShot(int i);
