#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QString>
#if defined(__APPLE__) || defined(MACOSX)
  #include <GLUT/glut.h>
#else
  #include <gl/glut.h>
#endif


enum Shape {
    NOTDRAWING,
    OBJ,
    SIERPINSKI,
    TETRAHEDRON,
    CUBE,
    OCTAHEDRON,
    DODECAHEDRON,
    ICOSAHEDRON,
};



struct Translate {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} ;

struct Scale {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct Rotate {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

//1234567890

struct GLOOKAT{
    GLfloat eyex;
    GLfloat eyey;
    GLfloat eyez;
    GLfloat centerx;
    GLfloat centery;
    GLfloat centerz;
    GLfloat upx;
    GLfloat upy;
    GLfloat upz;
};

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void display(Translate *t, Rotate *r, Scale *s);
   // void display(Translate *t, Rotate *r, Scale *s, GLOOKAT *l);
    void divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m);
    void tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d);
    void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc);

    void animation_t();
    void animation_r();
    void animation_s();
    void resetAnimation();

    //1234567890
    void animation_lookcx();
    void animation_lookex();
    void animation_lookux();

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);
    virtual void keyPressEvent(QKeyEvent* event);

public slots:
    void loadObj();
    void renderingMethodChange(const QString &);
    void redraw();
    void drawTetra();

    void setTXValue(int tx);
    void setTYValue(int ty);
    void setTZValue(int tz);
    void setRXValue(int rx);
    void setRYValue(int ry);
    void setRZValue(int rz);
    void setSXValue(int sx);
    void setSYValue(int sy);
    void setSZValue(int sz);

    //1234567890
    void setCEXValue(int eyex);
    void setCEYValue(int eyey);
    void setCEZValue(int eyez);
    void setCCXValue(int centerx);
    void setCCYValue(int centery);
    void setCCZValue(int centerz);
    void setCUXValue(int upx);
    void setCUYValue(int upy);
    void setCUZValue(int upz);

    //1234567890


    void glutMethodChange(const QString &select);
    void animationMethodChange(const QString &select);
    void startAnimation();
};

#endif // GLWIDGET_H
