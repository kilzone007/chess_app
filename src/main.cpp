#include "log.h"

#include "window/MainWindow.h"

int main()
{
    LINFO("Starting the app");

    MainWindow window;
    window.Start();

    return 0;
}