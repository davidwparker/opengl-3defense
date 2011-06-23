/*  Printing Convenience (print.c)  */
void setFont(char* name, int size);
void printv(va_list args, const char* format);
void print(const char* format , ...);
void printAt(int x,int y, const char* format , ...);
void errCheck(char* where);
void fatal(const char* format, ...);

/*  Texture loading (loadTexBMP.c)  */
unsigned int loadTexBMP(char* file);

/*  Shapes (shapes.c)  */
void square(int s, int a, int b, int c, int d);
void cube(double x,double y,double z,
	  double dx,double dy,double dz,
	  double th);
void vertex(double th, double ph);
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

/*  Towers (towers.c)  */
void basicTower(double x,double y,double z,
		double dx,double dy,double dz,
		double th);
void advancedTower(double x,double y,double z,
		   double dx,double dy,double dz,
		   double th);
void coneTower(double x,double y,double z,
	       double dx,double dy,double dz,
	       double th);
void advancedConeTower(double x,double y,double z,
		       double dx,double dy,double dz,
		       double th);
void squareTower(double x,double y,double z,
		 double dx,double dy,double dz,
		 double th);
void advancedSquareTower(double x,double y,double z,
			 double dx,double dy,double dz,
			 double th);
void fireTower(double x,double y,double z,
	       double dx,double dy,double dz,
	       double th);
void fireTower2(double x,double y,double z,
		double dx,double dy,double dz,
		double th);
void iceTower(double x,double y,double z,
	      double dx,double dy,double dz,
	      double th);
void iceTower2(double x,double y,double z,
	       double dx,double dy,double dz,
	       double th);
void earthTower(double x,double y,double z,
		double dx,double dy,double dz,
		double th);
void earthTower2(double x,double y,double z,
		 double dx,double dy,double dz,
		 double th);
void poisonTower(double x,double y,double z,
		 double dx,double dy,double dz,
		 double th);
void poisonTower2(double x,double y,double z,
		  double dx,double dy,double dz,
		  double th);

/*  General Convenience (general.c)- the catchall  */
vertices3f findMousePosition(int x, int y);
void idle(void);
void processPicks(void);
void redisplayAll(void);
void reset(void);

/*  Initialization  (initialize.c)  */
void initialize(void);
void initTextures(void);
void initBackground(void);
void screenInit(void);
void sidebarInit(void);

/*  Display and draw  (drawing.c)  */
void drawAxes(void);
void drawParameters(void);
void drawGrid(void);
void drawBackground(double d);
void drawLight(void);
void drawBoard(void);
void drawPath(void);
void drawForests(void);
void drawKeep(void);
void drawMinions(void);
void drawObjects(void);
void drawScene(void);

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
void sidebarRowT(int x, int y, int obj, char* text);
void sidebarDisplay(void);
void sidebarReshape(int width, int height);
void sidebarMouse(int btn, int state, int x, int y);

