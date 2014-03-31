#include "../include/stdafx.h"
#include "../include/Heightmap.h"


namespace heightmap {


Heightmap::Heightmap( const std::string&  source ) :
    source( source )
{
    DASSERT( !source.empty() );

    create();
}




Heightmap::~Heightmap() {
}




void
Heightmap::create() {

    const std::string hmSource = PATH_MEDIA + "/" + source + ".png";
    mHeightmap = QImage( hmSource.c_str() );
    ASSERT( !mHeightmap.isNull()
        && "‘айл карты высот не найден." );

    // # ”меньшаем изображение, чтобы получить м€гкий градиент.
    const size_t scaleX = 300;
    const size_t scaleY = 300;
    mHeightmap = mHeightmap.scaled(
        scaleX, scaleY,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
    );

    const std::string txSource = PATH_MEDIA + "/" + source + ".jpg";
    mTexture = QImage( txSource.c_str() );
    ASSERT( !mTexture.isNull()
        && "‘айл текстуры не найден." );

    mTexture = mTexture.scaled(
        scaleX, scaleY,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
    );

    ASSERT( (mHeightmap.size() == mTexture.size())
        && "»зображени€ должны быть одного размера." );


    /* - @test
    for (int y = 0; y < hmImage.height(); ++y) {
        for (int x = 0; x < hmImage.width(); ++x) {
            const QRgb rgb = hmImage.pixel( x, y );
            const int gray = qGray( rgb );
            CONSOLE << gray << " ";
        }
        CONSOLE << std::endl;
    }
    */

    const int a = mHeightmap.width();
    const int aHalf = a / 2;
    const int b = mHeightmap.height();
    const int bHalf = b / 2;


    // инициализируем буферы
    mFigure.countVertex = 3 * a * b;
    mFigure.vertex = createContent< GLfloat >( mFigure.countVertex );
    mFigure.countNormal = 3 * a * b;
    mFigure.normal = createContent< GLfloat >( mFigure.countNormal );
    mFigure.countColor = a * b;
    mFigure.color  = createContent< GLfloat >( mFigure.countColor );

    // сокращени€
    GLfloat*  vertex = mFigure.vertex.get();
    GLfloat*  normal = mFigure.normal.get();
    GLfloat*  color  = mFigure.color.get();


    // соберЄм вершины и нормали
    float hMin = std::numeric_limits< float >::max();
    float hMax = std::numeric_limits< float >::min();
    size_t t = 0;
    for (int j = 0; j < b; ++j) {
        for (int i = 0; i < a; ++i) {
            // высота лежит в диапазоне [0; 255]
            const QRgb rgb = mHeightmap.pixel( i, j );
            const int gray = qGray( rgb );
            const float height = static_cast< float >( gray );

            // центром делаем координату (0; 0; 0)
            QVector3D  vc(
                static_cast< float >( i - aHalf ),
                static_cast< float >( j - bHalf ),
                height
            );
            vertex[ t + 0 ] = vc.x();
            vertex[ t + 1 ] = vc.y();
            vertex[ t + 2 ] = vc.z();

            const auto nc = vc.normalized();
            normal[ t + 0 ] = nc.x();
            normal[ t + 1 ] = nc.y();
            normal[ t + 2 ] = nc.z();

            if (hMin > vc.z()) { hMin = vc.z(); }
            if (hMax < vc.z()) { hMax = vc.z(); }

            t += 3;
        }
    }


    // назначаем вершинам цвета
    for (int i = 0; i < (a * b); ++i) {
        color[ i ] = 1.0f;
    }


    // строим индексы
    std::vector< size_t >  ind;
    int jf = 0;
    for (int j = 0; j < (b - 1); ++j) {
        for (int i = 0; i < a; ++i) {
            if ((i - 1) >= 0) {
                ind.push_back( jf - 1 );
                ind.push_back( jf );
                ind.push_back( a + jf );
            }
            if ((i + 1) <= a) {
                ind.push_back( jf );
                ind.push_back( a + 1 + jf );
                ind.push_back( a + jf );                       
            }
            jf++;
        }
    }

    mFigure.countIndex = ind.size();
    mFigure.index = createContent< GLuint >( mFigure.countIndex );
    GLuint* index = mFigure.index.get();
    for (size_t i = 0; i < ind.size(); ++i) {
        index[ i ] = ind[ i ];
    }

}


} // heightmap
