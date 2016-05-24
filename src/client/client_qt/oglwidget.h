#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QWidget>
#include <QVector3D>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "common.h"

// This widget will handle the opengl visualisation.
// Amazingly, we do not seem to have to include gl for it to work.
// Qt magic.
class OGLWidget : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
public:
    OGLWidget(QWidget* parent = 0);
    ~OGLWidget();

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setData(path_t path);

protected:
    // These three needed for it to work.
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    // Copies the positions from path to vertices in a format acceptable for opengl.
    void updateVertices();

    path_t path;
    vector<float> vertices;

    QVector3D rot;
    QPoint lastPos;
    // Radius of a sphere that shall be visible inside the view.
    coord_t fitRadius = 1;
};

#endif // OGLWIDGET_H
