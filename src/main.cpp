#include "core/application.h"

int main()
{
    Application* app = new Application();

    app->run();

    delete app;
}