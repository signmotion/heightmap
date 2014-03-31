#include "../include/stdafx.h"
#include "../include/Scene.h"


namespace heightmap {


Scene::Scene( const std::string& source,  QWidget* parent ) :
    QGLWidget( parent ),
    hm( source )
{
    defaultScene();
}




Scene::~Scene() {
}




void
Scene::initializeGL() {

    qglClearColor( Qt::black );
    glEnable( GL_DEPTH_TEST );
    glShadeModel( GL_SMOOTH );
    glEnable( GL_CULL_FACE );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    glEnableClientState( GL_VERTEX_ARRAY );
    //glEnableClientState( GL_NORMAL_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
}




void
Scene::resizeGL( int nWidth, int nHeight ) {

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
 
    const GLfloat ratio =
       static_cast< GLfloat >( nHeight ) /
       static_cast< GLfloat >( nWidth );

    // лева€, права€, верхн€€, нижн€€, ближн€€, дальн€€
#if 1
    if (nWidth >= nHeight) {
        glOrtho( -1.0 / ratio, 1.0 / ratio, -1.0, 1.0, -10.0, 1.0 );
    } else {
        glOrtho( -1.0, 1.0, -1.0 * ratio, 1.0 * ratio, -10.0, 1.0 );
    }
#else
    glFrustum( -1.0, 1.0, -1.0, 1.0, 1.0, 10.0 );
#endif

    glViewport( 0, 0, nWidth, nHeight );
}




void
Scene::paintGL() { 

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glScalef( nSca, nSca, nSca );
    glTranslatef( 0.0f, zTra, 0.0f );
    glRotatef( xRot, 1.0f, 0.0f, 0.0f );
    glRotatef( yRot, 0.0f, 1.0f, 0.0f );
    glRotatef( zRot, 0.0f, 0.0f, 1.0f );
 
    //drawAxis();
    draw();
}




void
Scene::mousePressEvent( QMouseEvent* pe ) {
    mousePosition = pe->pos();                     
} 




void
Scene::mouseReleaseEvent( QMouseEvent* pe ) { 
} 




void
Scene::mouseMoveEvent( QMouseEvent* pe ) {
    xRot += 180/nSca*(GLfloat)(pe->y()-mousePosition.y())/height(); 
    zRot += 180/nSca*(GLfloat)(pe->x()-mousePosition.x())/width(); 
   
    mousePosition = pe->pos();
   
    updateGL();
}




void
Scene::wheelEvent( QWheelEvent* pe ) { 
    if (pe->delta() > 0) {
        scalePlus();
    } else if (pe->delta() < 0) {
        scaleMinus();
    }
    updateGL();       
}




void
Scene::keyPressEvent( QKeyEvent* pe ) {  

    switch ( pe->key() ) {         
        case Qt::Key_Plus:  
            scalePlus();
        break;
         
        case Qt::Key_Equal:  
            scalePlus(); 
        break;
         
        case Qt::Key_Minus: 
            scaleMinus();
        break;

        case Qt::Key_Up:  
            rotateUp();
        break;
         
        case Qt::Key_Down:  
            rotateDown();
        break;         
         
        case Qt::Key_Left:  
        rotateLeft();
        break;
         
        case Qt::Key_Right:  
            rotateRight();
        break;                           
         
        case Qt::Key_Z:
            translateDown();
        break;  
         
        case Qt::Key_X:
            translateUp();
        break; 
         
        case Qt::Key_Space:
            defaultScene();
        break;
      
        case Qt::Key_Escape:
            this->close();
        break;                                                           
    }
   
    updateGL();
}




void
Scene::scalePlus() {
    nSca = nSca*1.1;
}




void
Scene::scaleMinus() {
    nSca = nSca/1.1;
}




void
Scene::rotateUp() {
    xRot += 1.0;
}




void
Scene::rotateDown() {
    xRot -= 1.0;
}




void
Scene::rotateLeft() {
    zRot += 1.0;
}




void
Scene::rotateRight() {
    zRot -= 1.0;
}




void
Scene::translateDown() {
    zTra -= 0.05f;
}




void
Scene::translateUp() {
    zTra += 0.05f;
}




void
Scene::defaultScene() {
    xRot=-90;
    yRot=0;
    zRot=0;
    zTra=0;
    nSca=1;
}




void
Scene::drawAxis() {

    glLineWidth( 2.0f ); 
   
    glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
    glBegin( GL_LINES );
        glVertex3f( 1.0f,  0.0f,  0.0f);
        glVertex3f(-1.0f,  0.0f,  0.0f);
    glEnd();  
   
    QColor halfGreen( 0, 128, 0, 255 );
    qglColor( halfGreen );
    glBegin( GL_LINES );
        glVertex3f( 0.0f,  1.0f,  0.0f);
        glVertex3f( 0.0f, -1.0f,  0.0f);
        glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
        glVertex3f( 0.0f,  0.0f,  1.0f);
        glVertex3f( 0.0f,  0.0f, -1.0f);
    glEnd();
}




void Scene::draw() {

    DASSERT( hm.figure().vertex
        && " арта высот не инициализирована." );

    glLineWidth( 1.0f );

    /* @test
    {
        const auto image = hm.heightmap();
        const int a = image.width();
        const int b = image.height();
        const float box = 1.0f;
        const float color[ 3 ] = { 1.0f, 1.0f, 1.0f };
        glBegin( GL_TRIANGLE_STRIP );
        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < b; ++j) {
                const float x = (-1.0f + 2.0f * ((float)j / (float)a)) * box;
                const float y = (-1.0f + 2.0f * ((float)i / (float)b)) * box;
                const QRgb rgb = image.pixel( i, j );
                const float gray = static_cast< float >( qGray( rgb ) );
                const float height = (-box + 2.0f * (gray / 255.0f)) * 0.5f / 2.0f;
                glColor3fv( color );
                glVertex3f( x, y, height );
            }
        }
        glEnd(); 
    }
    */


    /* @test
    {
        const auto image = hm.heightmap();
        const auto fnh = [ &image ] ( int x, int y ) -> float {
            const QRgb rgb = image.pixel( x, y );
            const int gray = qGray( rgb );
            return static_cast< float >( gray ) / 255.0f;
        };

        size_t sideswitch = 0;
        glBegin( GL_TRIANGLE_STRIP );
        const int a = image.width();
        const float halfA = static_cast< float >( a ) / 2.0f;
        const int b = image.height();
        const float halfB = static_cast< float >( b ) / 2.0f;
        const float color = 1.0f;
        const float trisize = 1.0f;
        for (int x = 0; x < (a - 1); ++x) {
            if ( sideswitch ) {
                for (int y = (b - 2); y >= 0; --y) {
                    const float x1 = x * trisize - halfA;
                    const float x2 = (x * trisize + trisize) - halfA;
                    const float y1 = fnh( x, y ) - halfB;
                    const float y2 = fnh( x + 1, y ) - halfB;
                    const float z  = fnh( x, y );
                    glVertex3f( x1, y1, z );
                    glVertex3f( x2, y2, z );
                }
            } else {
                for (int y = 0; y < (b - 1); ++y) {
                    const float x1 = (x * trisize + trisize) - halfA;
                    const float x2 = x * trisize - halfA;
                    const float y1 = fnh( x + 1, y ) - halfB;
                    const float y2 = fnh( x, y ) - halfB;
                    const float z  = fnh( x, y );
                    glVertex3f( x1, y1, z );
                    glVertex3f( x2, y2, z );
                }
            }
            sideswitch++;
            if (sideswitch > 1) { sideswitch = 0; }
        }
        glEnd();
    }
    */

    //@todo http://mbsoftworks.sk/index.php?page=tutorials&series=1&tutorial=8


    // @test
    // @source http://nehe.gamedev.net/tutorial/beautiful_landscapes_by_means_of_height_mapping/16006
    {
        const auto image = hm.heightmap();
        const auto fnH = [ &image ] ( int x, int y ) -> float {
            const QRgb rgb = image.pixel( x, y );
            const int gray = qGray( rgb );
            return static_cast< float >( gray );
        };

        const int a = image.width();
        const float halfA = static_cast< float >( a ) / 2.0f;
        const int b = image.height();
        const float halfB = static_cast< float >( b ) / 2.0f;
        const auto tx = hm.texture();
        const auto fnCVN = [ a, b, halfA, halfB, &tx, this ] ( int x, int y, int z ) {
            const QRgb c = tx.pixel( x, y );
            const auto rgb = QColor( c );
            qglColor( rgb );
            const QVector3D  vc(
                static_cast< float >(x - halfA) / static_cast< float >( a ),
                static_cast< float >(y - halfB) / static_cast< float >( b ),
                static_cast< float >( z ) / 255.0f / 5.0f
            );
            glVertex3f( vc.x(), vc.y(), vc.z() );
        };

#if 0
        glBegin( GL_LINES );
#else
        glBegin( GL_QUADS );
#endif
        for (int x = 0; x < (a - 1); ++x) {
            for (int y = 0; y < (b - 1); ++y) {
                // bottom right
                int xx = x + 1;
                int yy = y;
                int zz = fnH( x + 1, y );
                fnCVN( xx, yy, zz );

                // top right
                xx = x + 1;
                yy = y + 1;
                zz = fnH( x + 1, y + 1 );
                fnCVN( xx, yy, zz );
 
                // top left
                xx = x;
                yy = y + 1;
                zz = fnH( x, y + 1 );
                fnCVN( xx, yy, zz );
 
                // bottom left
                xx = x;
                yy = y;
                zz = fnH( x, y );
                fnCVN( xx, yy, zz ); 
            }
        }
        glEnd();
    }


    /* - @todo optimize ќтрисовывать построенными заранее буферами.
    glVertexPointer( 3, GL_FLOAT, 0, hm.figure().vertex.get() );
    //glNormalPointer(    GL_FLOAT, 0, hm.figure().normal.get() );
    glColorPointer(  3, GL_FLOAT, 0, hm.figure().color.get() );
    const size_t n = hm.figure().countIndex;
    glDrawElements(
        GL_TRIANGLES,
        n,
        GL_UNSIGNED_INT,
        hm.figure().index.get()
    );
    */
}


} // heightmap
