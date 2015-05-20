#ifndef PLATONICSOLID
#define PLATONICSOLID

#include<GLUT/glut.h>
#include<math.h>
#define RADIUS 50.0f
#define SIZE 100.0f

#define TETRAHEDRON 2
#define CUBE 3
#define DODECAHEDRON 4
#define ICOSAHEDRON 5
#define OCTAHEDRON 6


GLint nSelected=CUBE;
/* initial triangle */
GLfloat v[4][3]={{0.0, 0.0, 1.0}, {0.0, 0.942809, -0.33333},{-0.816497, -0.471405, -0.333333}, {0.816497, -0.471405, -0.333333}};

GLfloat colors3[4][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},{0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}};
GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

//    GLfloat normals[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
//    {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
//    {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

GLfloat colors[][3] = {{0.0,0.0,0.0},{1.0,0.0,0.0},
{1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0},
{1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}};


static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLdouble viewer[]= {0.0, 0.0, 5.0}; /* initial viewer location */
static GLfloat Coord[] = {0.0,0.0,0.0};/*glTranslate(Coodr[3])*/
static GLint distance = 2;
static GLfloat Scale[] = {1.0, 1.0,1.0};/*glScale(Scale[3])*/
static GLint ratio = 1;

double g_dAngle= 0.0f;
double d_translate = 0.0f;
double s_scale = 0.0f;

void OnDisplay(void);
void OnReshape(int,int);
void OnMenu(int value);
void CreateMenu();
void SetupLights();
#endif // PLATONICSOLID

