#include <iostream>
#include "AppWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto *appWindow = new AppWindow();
    appWindow->show();
    return app.exec();
}