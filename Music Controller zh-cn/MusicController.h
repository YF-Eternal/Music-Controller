#ifndef MUSICCONTROLLER_H
#define MUSICCONTROLLER_H

#include <QMainWindow>
#include <QString>
#include <QProcess>
#include <QRegularExpression>  // 使用 QRegularExpression 替代 QRegExp
#include <QSystemTrayIcon>      // 添加此包含以支持系统托盘通知
#include "ui_MusicController.h"

// MusicController 类继承自 QMainWindow，用于音乐控制界面和逻辑
class MusicController : public QMainWindow {
    Q_OBJECT

public:
    // 构造函数: 初始化 MusicController 实例
    explicit MusicController(QWidget* parent = nullptr);

private slots:
    // 槽函数: 打开文件
    void openFile();

    // 槽函数: 更新播放速度
    void updateSpeed(int value);

    // 槽函数: 更新音量
    void updateVolume(int value);

    // 槽函数: 导出文件
    void exportFile();

protected:
    // 事件处理函数: 处理拖放进入事件
    void dragEnterEvent(QDragEnterEvent* event) override;

    // 事件处理函数: 处理拖放事件
    void dropEvent(QDropEvent* event) override;

private:
    // UI 组件指针: 管理界面元素
    Ui::MainWindow* ui;

    // 当前文件路径
    QString filePath;

    // 播放速度(倍数)
    double playbackSpeed;

    // 音量(范围 0 到 100)
    int volume;

    // 系统托盘图标，用于通知
    QSystemTrayIcon* trayIcon;

    // 连接信号和槽
    void connectSignals();

    // 构建 FFmpeg 命令行参数
    QString buildFFmpegCommand(const QString& inputFilePath, const QString& outputFilePath, double speed, int volume);

    // 根据 FFmpeg 输出更新进度
    void updateProgressFromOutput(const QString& output);
};

#endif // MUSICCONTROLLER_H