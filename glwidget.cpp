#include "GLWidget.h"
#include "loadObj.h"

#include <math.h>

#include <QTimer>
#include <qgl.h>
#include <QMouseEvent>
#include <QVector>
#include <QString>
#include <QFileDialog>
#include <unistd.h>
#include <qdir.h>
#include<QKeyEvent>
#include<QtGui>
#include<QWidget>
#include<QPaintEvent>

Shape shape = NOTDRAWING;
loadObj *objLoader = new loadObj();
int myDrawType = 0; // default:point
int myAnimationType = 0;
int animationDirection = 1;
bool animationModel = false;
char* myObjFile;

Translate t = {0.0,-0.15,-1.0};
Rotate r = {-8.0,160.0,0.0};
Scale s = {0.8,0.75,1.0};

Translate t_animation = {0.0,-0.15,-1.0};
Rotate r_animation = {-8.0,160.0,0.0};
Scale s_animation = {0.8,0.75,1.0};

//1234567890
GLOOKAT look = {0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05};

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    // The following code allows for animated graphics by attempting to refresh the screen at 50fps.
    //	STEP 1: Create a timer
    QTimer *timer = new QTimer(this);
    //	STEP 2: Update the GL graphics every time the timer is fired off
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    //	STEP 3: Start the timer to go off every 20 milliseconds.
    timer->start(16);

    // Enables mouse tracking. This means that whenever the mouse is moved
    // and/or clicked on the widget, a mouse event is generated
    setMouseTracking(true);

    setFocusPolicy( Qt::StrongFocus );
    setFocus( Qt::PopupFocusReason );
    setEnabled( true );
}

void GLWidget::loadObj()
{
    animationModel = false;
    QString path = QFileDialog::getOpenFileName(this, tr("Open OBJ"), ".", tr("OBJ Files(*.obj)"));
    QByteArray tempPath = path.toLatin1();
    myObjFile = tempPath.data();
    objLoader->setDrawType(myDrawType);
    objLoader->Load(myObjFile);
    shape = OBJ;
}

void GLWidget::renderingMethodChange(const QString &select)
{
    animationModel = false;
    if (select == "Points") {
        myDrawType = 0;
    } else if (select == "Wireframe") {
        myDrawType = 1;
    } else if (select == "Surface") {
        myDrawType = 2;
    }
}

void GLWidget::glutMethodChange(const QString &select)
{
    animationModel = false;
    if (select == "Tetrahedron") {
        shape = TETRAHEDRON;
    } else if (select == "Tetrahedron") {
        shape = TETRAHEDRON;
    } else if (select == "Cube") {
        shape = CUBE;
    } else if (select == "Octahedron") {
        shape = OCTAHEDRON;
    } else if (select == "Dodecahedron") {
        shape = DODECAHEDRON;
    } else if (select == "Icosahedron") {
        shape = ICOSAHEDRON;
    }
}

void GLWidget::animationMethodChange(const QString &select)
{
    animationModel = false;
    if (select == "Translate along cube edge") {
        myAnimationType = 0;
    } else if (select == "Rotate around x, y and z") {
        myAnimationType = 1;
    } else if (select == "Scale around x, y and z") {
        myAnimationType = 2;
    }
}

void GLWidget::startAnimation()
{
    animationDirection = 1;
    animationModel = true;
    resetAnimation();
}

void GLWidget::redraw()
{
    animationModel = false;
    if (myObjFile == NULL) {
        QMessageBox::information(NULL, tr("Message"), tr("Please load a OBJ file first!"));
    } else {
        objLoader->setDrawType(myDrawType);
        shape = OBJ;
    }
}

void GLWidget::drawTetra()
{
    animationModel = false;
    shape = SIERPINSKI;
}

void GLWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (shape) {
    case NOTDRAWING:
        break;
    case OBJ:
        if (animationModel) {
            glLoadIdentity();
            glTranslatef(t_animation.x,t_animation.y,t_animation.z);
            glRotatef(r_animation.x, 1.0f, 0.0f, 0.0f);
            glRotatef(r_animation.y, 0.0f, 1.0f, 0.0f);
            glRotatef(r_animation.z, 0.0f, 0.0f, 1.0f);
            glScalef(s_animation.x,s_animation.y,s_animation.z);
            objLoader->drawmodel();
            if (myAnimationType == 0) {
                animation_t();
            } else if (myAnimationType == 1) {
                animation_r();
            } else if (myAnimationType == 2) {
                animation_s();
            }
        } else {
            glLoadIdentity();
            glTranslatef(t.x,t.y,t.z);
            glRotatef(r.x, 1.0f, 0.0f, 0.0f);
            glRotatef(r.y, 0.0f, 1.0f, 0.0f);
            glRotatef(r.z, 0.0f, 0.0f, 1.0f);
            glScalef(s.x,s.y,s.z);
            objLoader->drawmodel();
        }

        break;
    case SIERPINSKI:
        if (animationModel) {
            this->display(&t_animation, &r_animation, &s_animation);
            if (myAnimationType == 0) {
                animation_t();
            } else if (myAnimationType == 1) {
                animation_r();
            } else if (myAnimationType == 2) {
                animation_s();
            }
        } else {
            //1234567890
            this->display(&t, &r, &s);

           // gluLookAt(look.centerx,look.centery,look.centerz,look.eyex,look.eyey,look.eyez,look.upx,look.upy,look.upz);
        }
        break;
    case TETRAHEDRON:
        if (animationModel) {
            glLoadIdentity();
            glTranslatef(t_animation.x,t_animation.y,t_animation.z);
            glRotatef(r_animation.x, 1.0f, 0.0f, 0.0f);
            glRotatef(r_animation.y, 0.0f, 1.0f, 0.0f);
            glRotatef(r_animation.z, 0.0f, 0.0f, 1.0f);
            glScalef(s_animation.x,s_animation.y,s_animation.z);
            glutWireTetrahedron();
            glFlush();
            if (myAnimationType == 0) {
                animation_t();
            } else if (myAnimationType == 1) {
                animation_r();
            } else if (myAnimationType == 2) {
                animation_s();
            }
        } else {
            glLoadIdentity();
            glTranslatef(t.x,t.y,t.z);
            glRotatef(r.x, 1.0f, 0.0f, 0.0f);
            glRotatef(r.y, 0.0f, 1.0f, 0.0f);
            glRotatef(r.z, 0.0f, 0.0f, 1.0f);
            glScalef(s.x,s.y,s.z);
            glutWireTetrahedron();
            glFlush();
        }
        break;
    case CUBE:
        if (animationModel) {
            glLoadIdentity();
            glTranslatef(t_animation.x,t_animation.y,t_animation.z);
            glRotatef(r_animation.x, 1.0f, 0.0f, 0.0f);
            glRotatef(r_animation.y, 0.0f, 1.0f, 0.0f);
            glRotatef(r_animation.z, 0.0f, 0.0f, 1.0f);
            glScalef(s_animation.x,s_animation.y,s_animation.z);
            glutWireCube(0.5);
            glFlush();
            if (myAnimationType == 0) {
                animation_t();
            } else if (myAnimationType == 1) {
                animation_r();
            } else if (myAnimationType == 2) {
                animation_s();
            }
        } else {
            glLoadIdentity();
            glTranslatef(t.x,t.y,t.z);
            glRotatef(r.x, 1.0f, 0.0f, 0.0f);
            glRotatef(r.y, 0.0f, 1.0f, 0.0f);
            glRotatef(r.z, 0.0f, 0.0f, 1.0f);
            glScalef(s.x,s.y,s.z);
            glutWireCube(0.5);
            glFlush();
        }
        break;
    case OCTAHEDRON:
        if (animationModel) {
            glLoadIdentity();
            glTranslatef(t_animation.x,t_animation.y,t_animation.z);
            glRotatef(r_animation.x, 1.0f, 0.0f, 0.0f);
            glRotatef(r_animation.y, 0.0f, 1.0f, 0.0f);
            glRotatef(r_animation.z, 0.0f, 0.0f, 1.0f);
            glScalef(s_animation.x,s_animation.y,s_animation.z);
            glutWireOctahedron();
            glFlush();
            if (myAnimationType == 0) {
                animation_t();
            } else if (myAnimationType == 1) {
                animation_r();
            } else if (myAnimationType == 2) {
                animation_s();
            }
        } else {
            glLoadIdentity();
            glTranslatef(t.x,t.y,t.z);
            glRotatef(r.x, 1.0f, 0.0f, 0.0f);
            glRotatef(r.y, 0.0f, 1.0f, 0.0f);
            glRotatef(r.z, 0.0f, 0.0f, 1.0f);
            glScalef(s.x,s.y,s.z);
            glutWireOctahedron();
            glFlush();
        }
        break;
    case DODECAHEDRON:
        if (animationModel) {
            glLoadIdentity();
            glTranslatef(t_animation.x,t_animation.y,t_animation.z);
            glRotatef(r_animation.x, 1.0f, 0.0f, 0.0f);
            glRotatef(r_animation.y, 0.0f, 1.0f, 0.0f);
            glRotatef(r_animation.z, 0.0f, 0.0f, 1.0f);
            glScalef(s_animation.x,s_animation.y,s_animation.z);
            glutWireDodecahedron();
            glFlush();
            if (myAnimationType == 0) {
                animation_t();
            } else if (myAnimationType == 1) {
                animation_r();
            } else if (myAnimationType == 2) {
                animation_s();
            }
        } else {
            glLoadIdentity();
            glTranslatef(t.x,t.y,t.z);
            glRotatef(r.x, 1.0f, 0.0f, 0.0f);
            glRotatef(r.y, 0.0f, 1.0f, 0.0f);
            glRotatef(r.z, 0.0f, 0.0f, 1.0f);
            glScalef(s.x,s.y,s.z);
            glutWireDodecahedron();
            glFlush();
        }
        break;
    case ICOSAHEDRON:
        if (animationModel) {
            glLoadIdentity();
            glTranslatef(t_animation.x,t_animation.y,t_animation.z);
            glRotatef(r_animation.x, 1.0f, 0.0f, 0.0f);
            glRotatef(r_animation.y, 0.0f, 1.0f, 0.0f);
            glRotatef(r_animation.z, 0.0f, 0.0f, 1.0f);
            glScalef(s_animation.x,s_animation.y,s_animation.z);
            glutWireIcosahedron();
            glFlush();
            if (myAnimationType == 0) {
                animation_t();
            } else if (myAnimationType == 1) {
                animation_r();
            } else if (myAnimationType == 2) {
                animation_s();
            }
        } else {
            glLoadIdentity();
            glTranslatef(t.x,t.y,t.z);
            glRotatef(r.x, 1.0f, 0.0f, 0.0f);
            glRotatef(r.y, 0.0f, 1.0f, 0.0f);
            glRotatef(r.z, 0.0f, 0.0f, 1.0f);
            glScalef(s.x,s.y,s.z);
            glutWireIcosahedron();
            glFlush();
        }
        break;
    }
    glFlush();
}

void GLWidget::resizeGL(int width, int height)
{

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   // gluLookAt(look.centerx,look.centery,look.centerz,look.eyex,look.eyey,look.eyez,look.upx,look.upy,look.upz);

    gluPerspective(90,(width/height),0.1,600);

    glMatrixMode(GL_MODELVIEW);


    glLoadIdentity();
}

void GLWidget::setTXValue(int tx)
{
    t.x = tx / 100.0;
}

void GLWidget::setTYValue(int ty)
{
    t.y = ty / 100.0;
}

void GLWidget::setTZValue(int tz)
{
    t.z = tz / 100.0;
}


void GLWidget::setRXValue(int rx)
{
    r.x = rx / 1.0;
}

void GLWidget::setRYValue(int ry)
{
    r.y = ry / 1.0;
}

void GLWidget::setRZValue(int rz)
{
    r.z = rz / 1.0;
}


void GLWidget::setSXValue(int sx)
{
    s.x = sx / 100.0;
}

void GLWidget::setSYValue(int sy)
{
    s.y = sy / 100.0;
}

void GLWidget::setSZValue(int sz)
{
    s.z = sz / 100.0;
}

//1234567890
void GLWidget::setCEXValue(int eyex){
    look.eyex = eyex /10.0;
}

void GLWidget::setCEYValue(int eyey){
    look.eyey = eyey / 10.0;
}

void GLWidget::setCEZValue(int eyez){
    look.eyez = eyez / 10.0;
}

void GLWidget::setCCXValue(int centerx){
    look.centerx = centerx / 10.0;
}

void GLWidget::setCCYValue(int centery){
    look.centery = centery / 10.0;
}

void GLWidget::setCCZValue(int centerz){
    look.centerz = centerz / 10.0;
}

void GLWidget::setCUXValue(int upx){
    look.upx = upx / 10.0;
}

void GLWidget::setCUYValue(int upy){
    look.upy = upy /10.0;
}

void GLWidget::setCUZValue(int upz){
    look.upz = upz / 10.0;
}

void GLWidget::animation_t()
{
    animationModel = true;
    glLoadIdentity();
    glTranslatef(t_animation.x,t_animation.y,t_animation.z);
    glRotatef(r_animation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(r_animation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(r_animation.z, 0.0f, 0.0f, 1.0f);
    glScalef(s_animation.x,s_animation.y,s_animation.z);
    glFlush();
    switch (animationDirection) {
    case 1:
        if (t_animation.x > 0.2f) {
            animationDirection = 2;
        }
        t_animation.x += 0.005f;
        break;
    case 2:
        if (t_animation.y > 0.05f) {
            animationDirection = 3;
        }
        t_animation.y += 0.005f;
        break;
    case 3:
        if (t_animation.z > -0.8f) {
            animationDirection = 4;
        }
        t_animation.z += 0.005f;
        break;
    case 4:
        t_animation.x -= 0.005f;
        t_animation.y -= 0.005f;
        t_animation.z -= 0.005f;
        if (t_animation.x <= 0.0f) {
            animationDirection = 1;
        }
        break;
    }
}

void GLWidget::animation_r()
{
    animationModel = true;
    glLoadIdentity();
    glTranslatef(t_animation.x,t_animation.y,t_animation.z);
    glRotatef(r_animation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(r_animation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(r_animation.z, 0.0f, 0.0f, 1.0f);
    glScalef(s_animation.x,s_animation.y,s_animation.z);
    glFlush();
    r_animation.x += 1.0f;
    r_animation.y += 1.0f;
    r_animation.z += 1.0f;
}

void GLWidget::animation_s()
{
    animationModel = true;
    if (s_animation.x > 1.8f) {
        animationDirection = 2;
    } else if (s_animation.x < -0.5f) {
        animationDirection = 1;
    }
    if (animationDirection == 1) {
        s_animation.x += 0.01f;
        s_animation.y += 0.01f;
        s_animation.z += 0.01f;
    } else if (animationDirection == 2) {
        s_animation.x -= 0.01f;
        s_animation.y -= 0.01f;
        s_animation.z -= 0.01f;
    }
}

//1234567890
void GLWidget::animation_lookcx(){

}

void GLWidget::animation_lookex(){

}

void GLWidget::animation_lookux(){

}

void GLWidget::resetAnimation()
{
    t_animation.x = 0.0;
    t_animation.y = -0.15;
    t_animation.z = -1.0;
    r_animation.x = -8.0;
    r_animation.y = 160.0;
    r_animation.z = 0.0;
    s_animation.x = 0.8;
    s_animation.y = 0.75;
    s_animation.z = 1.0;
}


void GLWidget::keyPressEvent(QKeyEvent *e)
{
    //1234567890
    switch(e->key())
    {
    case Qt::Key_0:
        t.x += 0.05f;
        break;
    case Qt::Key_1:
        t.y += 0.05f;
        break;
    case Qt::Key_3:
        t.z += 0.05f;
        break;
    case Qt::Key_4:
        s.x += 0.05f;
        break;
    case Qt::Key_5:
        s.y += 0.05f;
        break;
    case Qt::Key_6:
        s.z += 0.05f;
        break;
    case Qt::Key_7:
        r.x += 0.05f;
        break;
    case Qt::Key_8:
        r.y += 0.05f;
        break;
    case Qt::Key_9:
        r.z += 0.05f;
        break;
    case Qt::Key_A:
        look.centerx += 0.05f;
        break;
    case Qt::Key_B:
        look.centery += 0.05f;
        break;
    case Qt::Key_C:
        look.centerz += 0.05f;
        break;
    case Qt::Key_D:
        look.eyex += 0.05f;
        break;
    case Qt::Key_E:
        look.eyey += 0.05f;
        break;
    case Qt::Key_F:
        look.eyez += 0.05f;
        break;
    case Qt::Key_G:
        look.upx += 0.05f;
        break;
    case Qt::Key_H:
        look.upy += 0.05f;
        break;
    case Qt::Key_I:
        look.upz += 0.05f;
        break;
    }
}

GLWidget::~GLWidget()
{

}

// from gasket.c

/* initial tetrahedron */

GLfloat v[4][3]={{0.0f, 0.0f, 1.0f}, {0.0f, 0.942809f, -0.33333f}, {-0.816497f, -0.471405f, -0.333333f}, {0.816497f, -0.471405f, -0.333333f}};
GLfloat colors[4][3] = {{0.97f, 0.26f, 0.21f}, {0.13f, 0.59f, 0.95f}, {0.30f, 0.69f, 0.31f}, {1.0f, 0.47f, 0.0f}};

int n = 3;

void GLWidget::triangle(GLfloat *va, GLfloat *vb, GLfloat *vc)
{
    glVertex3fv(va);
    glVertex3fv(vb);
    glVertex3fv(vc);
}

void GLWidget::tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
    glColor3fv(colors[0]);
    triangle(a, b, c);
    glColor3fv(colors[1]);
    triangle(a, c, d);
    glColor3fv(colors[2]);
    triangle(a, d, b);
    glColor3fv(colors[3]);
    triangle(b, d, c);
}

void GLWidget::divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m)
{

    GLfloat mid[6][3];
    int j;
    if(m>0)
    {
        /* compute six midpoints */

        for(j=0; j<3; j++) mid[0][j]=(a[j]+b[j])/2;
        for(j=0; j<3; j++) mid[1][j]=(a[j]+c[j])/2;
        for(j=0; j<3; j++) mid[2][j]=(a[j]+d[j])/2;
        for(j=0; j<3; j++) mid[3][j]=(b[j]+c[j])/2;
        for(j=0; j<3; j++) mid[4][j]=(c[j]+d[j])/2;
        for(j=0; j<3; j++) mid[5][j]=(b[j]+d[j])/2;

        /* create 4 tetrahedrons by subdivision */

        divide_tetra(a, mid[0], mid[1], mid[2], m-1);
        divide_tetra(mid[0], b, mid[3], mid[5], m-1);
        divide_tetra(mid[1], mid[3], c, mid[4], m-1);
        divide_tetra(mid[2], mid[4], d, mid[5], m-1);

    }
    else(tetra(a,b,c,d)); /* draw tetrahedron at end of recursion */
}


void GLWidget::display(Translate* t, Rotate* r, Scale* s)
{
    glLoadIdentity();

    glTranslatef(t->x,t->y,t->z);


    glRotatef(r->x, 1.0f, 0.0f, 0.0f);
    glRotatef(r->y, 0.0f, 1.0f, 0.0f);
    glRotatef(r->z, 0.0f, 0.0f, 1.0f);
    glScalef(s->x,s->y,s->z);
    glBegin(GL_TRIANGLES);
    divide_tetra(v[0], v[1], v[2], v[3], n);
    glEnd();
    glFlush();
}


//void GLWidget::display(Translate *t, Rotate *r, Scale *s, GLOOKAT *l)

//{
//    glLoadIdentity();
//    gluLookAt(l->centerx,l->centery,l->centerz,l->eyex,l->eyey,l->eyez,l->upx,l->upy,l->upz);
//    glTranslatef(t->x,t->y,t->z);
//    glRotatef(r->x, 1.0f, 0.0f, 0.0f);
//    glRotatef(r->y, 0.0f, 1.0f, 0.0f);
//    glRotatef(r->z, 0.0f, 0.0f, 1.0f);
//    glScalef(s->x,s->y,s->z);
//    glBegin(GL_TRIANGLES);
//    divide_tetra(v[0], v[1], v[2], v[3], n);
//    glEnd();
//    glFlush();


//}
