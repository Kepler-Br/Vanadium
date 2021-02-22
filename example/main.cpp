#include "Vanadium.h"

int main(int argc, char** argv)
{
    using namespace Van;

    auto *app = new Application("Oh my~", 800, 600, nullptr);
    app->run();
    delete app;

    return 0;
}
