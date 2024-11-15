#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QProcess>  // 引入 QProcess

class CustomDialog : public QDialog {
    Q_OBJECT

public:
    explicit CustomDialog(QWidget* parent = nullptr);
    void setMessage(const QString& message);  // 设置消息
    void setFilePath(const QString& path);  // 设置文件路径
    ~CustomDialog();  // 析构函数声明

private slots:
    void openFolder();  // 打开文件夹并选中文件
    void play();  // 播放文件

private:
    QLabel* messageLabel;  // 显示消息的标签
    QPushButton* openFolderButton;  // 打开文件夹按钮
    QPushButton* playButton;  // 播放按钮
    QString filePath;  // 文件路径

    QProcess* process;  // 用于执行命令的 QProcess
    void playSystemSound();  // 播放系统提示音
};

#endif // CUSTOMDIALOG_H
