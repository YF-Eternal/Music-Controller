#include <QApplication>
#include "MusicController.h"

int main(int argc, char* argv[]) {
    // 创建 Qt 应用程序实例
    QApplication app(argc, argv);

    // 创建 MusicController 控制器实例，并显示
    MusicController controller;
    controller.show();

    // 启动应用程序事件循环
    return app.exec();
}
