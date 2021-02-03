#include "core/application.h"
#include "utils/log.h"

int main()
{
    Log::init();

    CC_LOG_INFO("Testing");

    Application* app = new Application();

    app->run();

    delete app;
}