#include "core/application.h"
#include "utils/assert.h"
#include "utils/log.h"

int main()
{
    Log::init();

    CC_LOG_INFO("Testing");
    CC_ASSERT(false);

    Application* app = new Application();

    app->run();

    delete app;
}