#include <QApplication>
#include "MusicController.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MusicController controller;
    controller.show();

    return app.exec();
}
