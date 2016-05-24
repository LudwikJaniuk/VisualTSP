#include "oglwidget.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      path{Node{point_t{0, 0, 0}, 0},
           Node{point_t{0, 0.5, 0}, 1},
           Node{point_t{0.5, 0, 0}, 2}}
{
    updateVertices();
}

OGLWidget::~OGLWidget()
{}

void OGLWidget::updateVertices()
{
    vertices.clear();
    vertices.reserve(path.size()*3);
    for (auto& n : path) {
        vertices.push_back(n.pos.get<0>());
        vertices.push_back(n.pos.get<1>());
        vertices.push_back(n.pos.get<2>());
    }
}

void OGLWidget::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.

    // Initialize OpenGL Backend
    initializeOpenGLFunctions();

    // Set global information
    // Setting clear color to red so that we know this actually did stuff.
    //glClearColor(0.173f, 0.0f, 0.3f, 1.0f);
    glClearColor(0.369f, 0.153f, 0.314f, 1.0f);
    glEnable( GL_POINT_SMOOTH );
    glPointSize(5.0f);
}

void OGLWidget::resizeGL(int width, int height)
{
    // Update projection matrix to work with the new window dimensions.
    // The rules are that everything between (-1, -1, -1) and (1, 1, 1) must be in view.
    // The code in here technically makes everything between (-1, -1, 1) and (1, 1, 3) visible
    // (Because of math reasons), but we account for that by translating everything forward 
    // by 2 in paintGL.

    float side = qMin(width, height);
    float worldWidth = width/side;
    float worldHeight= height/side;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-worldWidth, +worldWidth, -worldHeight, +worldHeight, 1.0, 3.0);
    glMatrixMode(GL_MODELVIEW);
}

void OGLWidget::paintGL()
{
    // Draw the scene.
    // Right now we only draw a triangle. Visualization to come.

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glBlendColor(1, 1, 1, 1);
    glTranslatef(0, 0, -2); // Shift the world so origin is at (0,0,0) instead of (0,0,2).
    //glRotatef(rot.x() * 3.6f, rot.y() * 3.6f, rot.z() * 3.6f, 0.0);
    glRotatef(rot.x() * 3.6f, 0.0, 1.0, 0.0);
    glRotatef(rot.y() * 3.6f, 1.0, 0.0, 0.0);
    glRotatef(rot.z() * 3.6f, 0.0, 0.0, 1.0);
    cout << "REdrew" << endl;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_POINTS, 0, vertices.size()/3);
    glDrawArrays(GL_LINE_LOOP, 0, vertices.size()/3);
}

void OGLWidget::setXRotation(int angle)
{
    if (angle != rot.x()) {
        rot.setX(angle);
        update();
    }
    cout << "Angle changes to " << angle << endl;
}

void OGLWidget::setYRotation(int angle)
{
    if (angle != rot.y()) {
        rot.setY(angle);
        update();
    }
    cout << "Angle changes to " << angle << endl;
}

void OGLWidget::setZRotation(int angle)
{
    if (angle != rot.z()) {
        rot.setZ(angle);
        update();
    }
    cout << "Angle changes to " << angle << endl;
}
