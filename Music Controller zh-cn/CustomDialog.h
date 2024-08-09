#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class CustomDialog : public QDialog {
    Q_OBJECT

public:
    // 构造函数：初始化 CustomDialog 实例
    explicit CustomDialog(QWidget* parent = nullptr);

    // 设置对话框中显示的消息
    void setMessage(const QString& message);

    // 设置文件操作的路径
    void setFilePath(const QString& path);

private slots:
    // 槽函数：打开包含文件的文件夹
    void openFolder();

    // 槽函数：播放文件
    void play();

private:
    QLabel* messageLabel;         // 显示消息的标签
    QPushButton* openFolderButton; // 打开文件夹的按钮
    QPushButton* playButton;       // 播放文件的按钮
    QString filePath;             // 文件路径

    // 播放系统声音通知
    void playSystemSound();
};

#endif // CUSTOMDIALOG_H