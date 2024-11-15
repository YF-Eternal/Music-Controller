#include <QApplication>
#include "MusicController.h"

int main(int argc, char* argv[]) {
    // Create the Qt application instance
    QApplication app(argc, argv);

    // Create an instance of the MusicController and show it
    MusicController controller;
    controller.show();

    // Start the application event loop
    return app.exec();
}
