#include "include/vanadium/Vanadium.h"
#include "states/CustomState.h"
#warning "Add xml shaders assets."
//#include <tinyxml2.h>

int main(int argc, char** argv)
{
//    tinyxml2::XMLDocument doc;
//    doc.LoadFile( "dream.xml" );

    using namespace Vanadium;

    auto *app = new Application("Oh my~", 800, 600);
    app->forcePushArgumentlessState<CustomState>("Custom state");
    app->run();
    delete app;
    return 0;
}
