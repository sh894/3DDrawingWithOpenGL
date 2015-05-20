#include <QtGui>
#include <QAction>
#include <QMenuBar>
#include <QKeySequence>
#include <QToolBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QSlider>
#include <QFrame>

#include "mainwindow.h"
#include "GLWidget.h"
#include "loadObj.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QLabel *part_1 = new QLabel();
    // load button
    loadButton = new QPushButton(tr("Load OBJ"));
    glWindow = new GLWidget;
    connect(loadButton, SIGNAL(clicked()), glWindow, SLOT(loadObj()));

    // render method
    QLabel *rener_method = new QLabel(QWidget::tr("Rendering:"));
    QComboBox *cbo_render = new QComboBox();
    cbo_render->addItem(QWidget::tr("Surface"));
    cbo_render->addItem(QWidget::tr("Points"));
    cbo_render->addItem(QWidget::tr("Wireframe"));

    QHBoxLayout *render_layout = new QHBoxLayout;
    QPushButton *redraw_button = new QPushButton(QWidget::tr("Reload"));
    render_layout->addWidget(rener_method);
    render_layout->addWidget(cbo_render);
    render_layout->addWidget(redraw_button);
    connect(cbo_render, SIGNAL(currentIndexChanged(const QString &)), glWindow, SLOT(renderingMethodChange(const QString &)));
    connect(redraw_button, SIGNAL(clicked()), glWindow, SLOT(redraw()));

    // status bar
    msgLabel = new QLabel;
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);
    statusBar()->addWidget(msgLabel);


    QVBoxLayout *leftLayout = new QVBoxLayout;
    GLWidget* glwidget = new GLWidget;
    leftLayout->addWidget(glwidget);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(part_1);
    rightLayout->addWidget(loadButton);
    rightLayout->addLayout(render_layout);

    // tetra
    QPushButton *tetra_button = new QPushButton(QWidget::tr("Draw 3D Sierpinski Gasket"));
    rightLayout->addWidget(tetra_button);
    connect(tetra_button, SIGNAL(clicked()), glWindow, SLOT(drawTetra()));

    // glut library
    QLabel *glut_method = new QLabel(QWidget::tr("Platonic Solids:"));
    QComboBox *cbo_glut = new QComboBox();
    cbo_glut->addItem(QWidget::tr("Tetrahedron"));
    cbo_glut->addItem(QWidget::tr("Cube"));
    cbo_glut->addItem(QWidget::tr("Octahedron"));
    cbo_glut->addItem(QWidget::tr("Dodecahedron"));
    cbo_glut->addItem(QWidget::tr("Icosahedron"));
    QHBoxLayout *glut_layout = new QHBoxLayout;
    glut_layout->addWidget(glut_method);
    glut_layout->addWidget(cbo_glut);
    connect(cbo_glut, SIGNAL(currentIndexChanged(const QString &)), glWindow, SLOT(glutMethodChange(const QString &)));
    rightLayout->addLayout(glut_layout);

    // sliders
    QLabel *part_2 = new QLabel();
    rightLayout->addWidget(part_2);
    QLabel *slider_t_label = new QLabel(QWidget::tr("Translate: "));
    QLabel *slider_tx_label = new QLabel(QWidget::tr("x: "));
    QLabel *slider_ty_label = new QLabel(QWidget::tr("y: "));
    QLabel *slider_tz_label = new QLabel(QWidget::tr("z: "));
    QSlider *t_x = new QSlider(Qt::Horizontal);
    t_x->setRange(-50,50);
    t_x->setValue(0);
    QSlider *t_y = new QSlider(Qt::Horizontal);
    t_y->setRange(-50,50);
    t_y->setValue(0);
    QSlider *t_z = new QSlider(Qt::Horizontal);
    t_z->setRange(-50,50);
    t_z->setValue(0);
    connect(t_x, SIGNAL(valueChanged(int)), glWindow, SLOT(setTXValue(int)));
    connect(t_y, SIGNAL(valueChanged(int)), glWindow, SLOT(setTYValue(int)));
    connect(t_z, SIGNAL(valueChanged(int)), glWindow, SLOT(setTZValue(int)));
    rightLayout->addWidget(slider_t_label);
    QHBoxLayout *slider_tx_layout = new QHBoxLayout;
    slider_tx_layout->addWidget(slider_tx_label);
    slider_tx_layout->addWidget(t_x);
    rightLayout->addLayout(slider_tx_layout);
    QHBoxLayout *slider_ty_layout = new QHBoxLayout;
    slider_ty_layout->addWidget(slider_ty_label);
    slider_ty_layout->addWidget(t_y);
    rightLayout->addLayout(slider_ty_layout);
    QHBoxLayout *slider_tz_layout = new QHBoxLayout;
    slider_tz_layout->addWidget(slider_tz_label);
    slider_tz_layout->addWidget(t_z);
    rightLayout->addLayout(slider_tz_layout);

    QLabel *slider_r_label = new QLabel(QWidget::tr("Rotate: "));
    QLabel *slider_rx_label = new QLabel(QWidget::tr("x: "));
    QLabel *slider_ry_label = new QLabel(QWidget::tr("y: "));
    QLabel *slider_rz_label = new QLabel(QWidget::tr("z: "));
    QSlider *r_x = new QSlider(Qt::Horizontal);
    r_x->setRange(-50,50);
    r_x->setValue(0);
    QSlider *r_y = new QSlider(Qt::Horizontal);
    r_y->setRange(-50,50);
    r_y->setValue(0);
    QSlider *r_z = new QSlider(Qt::Horizontal);
    r_z->setRange(-50,50);
    r_z->setValue(0);
    connect(r_x, SIGNAL(valueChanged(int)), glWindow, SLOT(setRXValue(int)));
    connect(r_y, SIGNAL(valueChanged(int)), glWindow, SLOT(setRYValue(int)));
    connect(r_z, SIGNAL(valueChanged(int)), glWindow, SLOT(setRZValue(int)));
    rightLayout->addWidget(slider_r_label);
    QHBoxLayout *slider_rx_layout = new QHBoxLayout;
    slider_rx_layout->addWidget(slider_rx_label);
    slider_rx_layout->addWidget(r_x);
    rightLayout->addLayout(slider_rx_layout);
    QHBoxLayout *slider_ry_layout = new QHBoxLayout;
    slider_ry_layout->addWidget(slider_ry_label);
    slider_ry_layout->addWidget(r_y);
    rightLayout->addLayout(slider_ry_layout);
    QHBoxLayout *slider_rz_layout = new QHBoxLayout;
    slider_rz_layout->addWidget(slider_rz_label);
    slider_rz_layout->addWidget(r_z);
    rightLayout->addLayout(slider_rz_layout);

    QLabel *slider_s_label = new QLabel(QWidget::tr("Scale: "));
    QLabel *slider_sx_label = new QLabel(QWidget::tr("x: "));
    QLabel *slider_sy_label = new QLabel(QWidget::tr("y: "));
    QLabel *slider_sz_label = new QLabel(QWidget::tr("z: "));
    QSlider *s_x = new QSlider(Qt::Horizontal);
    s_x->setRange(-50,50);
    s_x->setValue(0);
    QSlider *s_y = new QSlider(Qt::Horizontal);
    s_y->setRange(-50,50);
    s_y->setValue(0);
    QSlider *s_z = new QSlider(Qt::Horizontal);
    s_z->setRange(-50,50);
    s_z->setValue(0);
    connect(s_x, SIGNAL(valueChanged(int)), glWindow, SLOT(setSXValue(int)));
    connect(s_y, SIGNAL(valueChanged(int)), glWindow, SLOT(setSYValue(int)));
    connect(s_z, SIGNAL(valueChanged(int)), glWindow, SLOT(setSZValue(int)));
    rightLayout->addWidget(slider_s_label);
    QHBoxLayout *slider_sx_layout = new QHBoxLayout;
    slider_sx_layout->addWidget(slider_sx_label);
    slider_sx_layout->addWidget(s_x);
    rightLayout->addLayout(slider_sx_layout);
    QHBoxLayout *slider_sy_layout = new QHBoxLayout;
    slider_sy_layout->addWidget(slider_sy_label);
    slider_sy_layout->addWidget(s_y);
    rightLayout->addLayout(slider_sy_layout);
    QHBoxLayout *slider_sz_layout = new QHBoxLayout;
    slider_sz_layout->addWidget(slider_sz_label);
    slider_sz_layout->addWidget(s_z);
    rightLayout->addLayout(slider_sz_layout);

    // animation
    QLabel *part_3 = new QLabel();
    rightLayout->addWidget(part_3);
    QComboBox *cbo_animation = new QComboBox();
    cbo_animation->addItem(QWidget::tr("Translate Animation"));
    cbo_animation->addItem(QWidget::tr("Rotate Animation"));
    cbo_animation->addItem(QWidget::tr("Scale Animation"));
    QHBoxLayout *animate_layout = new QHBoxLayout;
    QPushButton *animate_button = new QPushButton(QWidget::tr("Start"));
    animate_layout->addWidget(cbo_animation);
    animate_layout->addWidget(animate_button);
    connect(cbo_animation, SIGNAL(currentIndexChanged(const QString &)), glWindow, SLOT(animationMethodChange(const QString &)));
    connect(animate_button, SIGNAL(clicked()), glWindow, SLOT(startAnimation()));
    rightLayout->addLayout(animate_layout);

    rightLayout->addStretch();
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0,5);
    mainLayout->setColumnStretch(1,1);
    mainLayout->addLayout(leftLayout,0,0);
    mainLayout->addLayout(rightLayout,0,1);

    QWidget *window = new QWidget();
    window->setLayout(mainLayout);

    setCentralWidget(window);
    setWindowTitle(tr("ComputerGraphics_Assigment4_Siman Huang"));
    resize(1000,1000);
}

void MainWindow::open()
{

}

MainWindow::~MainWindow()
{

}
