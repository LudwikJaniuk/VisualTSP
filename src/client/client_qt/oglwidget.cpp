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
    //QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    // Initialize OpenGL Backend
    initializeOpenGLFunctions();

    // Set global information
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void OGLWidget::resizeGL(int w, int h)
{
    // Update projection matrix and other size related settings:
    //m_projection.setToIdentity();
    //m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
    //...
}

void OGLWidget::paintGL()
{
    // Clear
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the scene:
    //QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBlendColor(1, 1, 1, 1);
    GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
                          -0.5f, -0.5f, 0.0f,
                           0.5f, -0.5f, 0.0f};
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //...

}
