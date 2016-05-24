#include "oglwidget.h"


#include <QOpenGLContext>
#include <QOpenGLFunctions>

OGLWidget::OGLWidget(QWidget *parent): QOpenGLWidget(parent)
{}

OGLWidget::~OGLWidget()
{}

void OGLWidget::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.:

    // Initialize OpenGL Backend
    initializeOpenGLFunctions();

    // Set global information
    // Setting clear color to red so that we know this actually did stuff.
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
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
    GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
                          -0.5f, -0.5f, 0.0f,
                           0.5f, -0.5f, 0.0f};
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
