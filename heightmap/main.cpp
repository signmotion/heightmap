#include "include/stdafx.h"
#include "include/configure.h"
#include "include/Scene.h"




int run( QApplication& app,  const std::string& source );




/**
* Визуализации карты высот.
*/
int
main( int argc, char** argv ) {

    using namespace heightmap;

    setlocale( LC_ALL, "Russian" );
    setlocale( LC_NUMERIC, "C" );


    QApplication  app( argc, argv );
   
   
    // @todo args
    const std::string source = "region1";


    int code = 0;
    try {
        code = run( app, source );
        
    } catch ( const Exception& ex ) {
        std::cerr << std::endl << ex.what() << std::endl;
        code = -1;

    } catch ( const std::exception& ex ) {
        std::cerr << std::endl << ex.what() << std::endl;
        code = -2;

    } catch ( const std::string& ex ) {
        std::cerr << std::endl << ex << std::endl;
        code = -100;

    } catch ( const char* const ex ) {
        std::cerr << std::endl << *ex << std::endl;
        code = -200;
        
    } catch ( ... ) {
        std::cerr << std::endl << "(!) Unknown exception." << std::endl;
        code = -300;
    }

    std::cout << "\n^\n";
    if (code != 0) { std::cin.ignore(); }

    return code;

}; // main()








inline int
run( QApplication& app,  const std::string& source ) {

    using namespace heightmap;

    Scene  scene( source );
    scene.setWindowTitle( "Heightmap" ); 
    scene.resize( 1000, 1000 );
    scene.show();

    return app.exec();
}
