#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

// This widget will handle the opengl visualisation.
// Amazingly, we do not seem to have to include gl for it to work.
// Qt magic.
class OGLWidget : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
public:
    OGLWidget(QWidget* parent = 0);
    ~OGLWidget();

protected:
    // These three needed for it to work.
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // OGLWIDGET_H
