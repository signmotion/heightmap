#pragma once

#include "configure.h"
#include "structure.h"


namespace heightmap {


class Heightmap {
public:
    /**
    * ������������� ����� ����� � ���� ������� OpenGL.
    */
    typedef struct {
        size_t countVertex;
        std::unique_ptr< GLfloat >  vertex;
        size_t countNormal;
        std::unique_ptr< GLfloat >  normal;
        size_t countColor;
        std::unique_ptr< GLfloat >  color;
        size_t countIndex;
        std::unique_ptr< GLuint >   index;
    } figure_t;



public:
    const std::string  source;


public:
    /**
    * # �������� ����������� ��� ����������.
    * # ���������� � ������ ��� ����� ����� - PNG.
    * # ���������� � ������ ��� �������� - JPG.
    */
    Heightmap( const std::string&  source );


    virtual ~Heightmap();


    inline QImage heightmap() const { return mHeightmap; }


    inline QImage texture() const { return mTexture; }


    inline figure_t const& figure() const { return mFigure; }

    
protected:
    /**
    * ������ ����� ����� � ���� ������� OpenGL.
    */
    void create();


    /**
    * ����������� ����� ��� ��������� � ����.
    * �������������� ��������� T ������.
    */
    template< class T >
    static inline std::unique_ptr< T >  createContent( size_t N ) {
        std::unique_ptr< T >  content( new T[ N ] );
        std::memset( content.get(),  T(),  sizeof( T ) * N );
        return std::move( content );
    }


private:
    QImage    mHeightmap;
    QImage    mTexture;
    figure_t  mFigure;
};


} // heightmap
