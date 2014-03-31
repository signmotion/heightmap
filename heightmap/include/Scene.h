#pragma once

#include <QGLWidget>
#include "Heightmap.h"


namespace heightmap {


class Scene : public QGLWidget { 
public: 
    Scene( const std::string& source,  QWidget* parent = nullptr );

    ~Scene();


protected:
    void initializeGL();         
    void resizeGL( int nWidth, int nHeight );
    void paintGL();
    void mousePressEvent( QMouseEvent* );
    void mouseMoveEvent( QMouseEvent* );
    void mouseReleaseEvent( QMouseEvent* );
    void wheelEvent( QWheelEvent* );
    void keyPressEvent( QKeyEvent* );


private: 
    void defaultScene();  
    void scalePlus();
    void scaleMinus();
    void rotateUp();
    void rotateDown();
    void rotateLeft();
    void rotateRight();
    void translateDown();
    void translateUp();     
      
    void drawAxis();

    void create();     
    void draw();
        

private:
    GLfloat  xRot;
    GLfloat  yRot; 
    GLfloat  zRot;
    GLfloat  zTra;
    GLfloat  nSca;
      
    QPoint   mousePosition;

    Heightmap  hm;
};


} // heightmap
