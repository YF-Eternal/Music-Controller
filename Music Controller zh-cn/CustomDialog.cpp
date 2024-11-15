#include "CustomDialog.h"
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <Windows.h>
#include <QDir>

// 构造函数：初始化 CustomDialog 实例
CustomDialog::CustomDialog(QWidget* parent)
    : QDialog(parent), messageLabel(new QLabel(this)),
    openFolderButton(new QPushButton("打开文件夹", this)),
    playButton(new QPushButton("播放", this)) {

    // 设置字体为微软雅黑
    QFont font("Microsoft YaHei");
    setFont(font);
    messageLabel->setFont(font);
    openFolderButton->setFont(font);
    playButton->setFont(font);

    // 创建垂直布局并添加控件
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(messageLabel);
    layout->addWidget(openFolderButton);
    layout->addWidget(playButton);

    // 连接信号和槽
    connect(openFolderButton, &QPushButton::clicked, this, &CustomDialog::openFolder);
    connect(playButton, &QPushButton::clicked, this, &CustomDialog::play);

    setLayout(layout);
    setWindowTitle("提示");

    // 设置对话框的最小和最大尺寸，并将尺寸固定为当前对话框的大小
    setMinimumSize(300, 150);  // 设置最小尺寸为 300x150
    setMaximumSize(600, 300);  // 设置最大尺寸为 600x300
    setFixedSize(size());  // 设置固定大小为当前对话框的大小

    // 播放系统提示音
    playSystemSound();
}

// 设置对话框中显示的消息
void CustomDialog::setMessage(const QString& message) {
    messageLabel->setText(message);
}

// 设置文件路径
void CustomDialog::setFilePath(const QString& path) {
    filePath = path;
}

// 使用 Windows API 打开文件夹并选中文件
void CustomDialog::openFolder() {
    QFileInfo fileInfo(filePath);  // 获取文件信息
    if (fileInfo.exists()) {  // 如果文件存在
        // 获取文件所在的文件夹路径
        QString folderPath = QDir::toNativeSeparators(fileInfo.absolutePath());
        QString fileName = fileInfo.fileName();

        // 构建命令，使用 explorer 打开文件所在文件夹并选中文件
        QString fullPath = folderPath + "\\" + fileName;

        // 使用 ShellExecute 打开文件夹并选中文件
        // 转换为宽字符字符串
        std::wstring widePath = fullPath.toStdWString();
        ShellExecute(NULL, L"open", L"explorer.exe", (L"/select,\"" + widePath + L"\"").c_str(), NULL, SW_SHOWNORMAL);
    }
}

// 播放文件
void CustomDialog::play() {
    QString command = "explorer \"" + filePath + "\"";  // 使用系统默认的播放器播放文件
    QProcess::startDetached(command);
}

// 播放系统提示音
void CustomDialog::playSystemSound() {
    // 播放系统默认通知声音
    MessageBeep(MB_OK);  // 使用 MessageBeep 播放默认系统声音
}

// 析构函数：Qt 会自动管理 QProcess 的内存，因此无需手动删除
CustomDialog::~CustomDialog() {
    // 不需要删除 process，Qt 会自动管理
}
