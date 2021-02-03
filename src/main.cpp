#include "core/application.h"
#include "utils/assert.h"
#include "utils/log.h"

int main()
{
    Log::init();

    Application* app = new Application();

    app->run();

    delete app;
}