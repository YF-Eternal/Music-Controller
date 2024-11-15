#include "MusicController.h"
#include "CustomDialog.h"
#include <QFileDialog>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QRegularExpression>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QFontDatabase>
#include <QMessageBox>
#include <QFile>
#include <QFont>
#include <QStandardPaths>

MusicController::MusicController(QWidget* parent)
    : QMainWindow(parent), playbackSpeed(1.0), volume(0), ui(new Ui::MainWindow), trayIcon(new QSystemTrayIcon(this)) {
    ui->setupUi(this);
    this->setWindowTitle("Music Controller");
    setWindowIcon(QIcon(":/icon.ico"));

    this->setFixedSize(this->size());
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    // 初始化控件值
    ui->speedSlider->setValue(1000);
    ui->speedSpinBox->setValue(1000);
    ui->volumeSlider->setValue(volume);
    ui->volumeSpinBox->setValue(volume);
    ui->speedLabel->setText("倍速: 1.000x");
    ui->statusbar->showMessage("🔘 等待操作中...   (请点击\"导入\"按钮添加或直接拖入音频文件)");

    ui->exportButton->setEnabled(false);  // 初始时禁用导出按钮
    ui->exportButton->setStyleSheet("QPushButton:disabled { background-color: lightgray; color: gray; border: 1px solid gray; }");

    setAcceptDrops(true);  // 启用拖放功能

    trayIcon->setIcon(QIcon(":/icon.ico"));
    trayIcon->setVisible(true);

    // 创建托盘菜单
    QMenu* trayMenu = new QMenu(this);
    QAction* exitAction = new QAction("退出", this);
    trayMenu->addAction(exitAction);

    // 设置菜单字体为微软雅黑
    QFont font = QFontDatabase::systemFont(QFontDatabase::GeneralFont);
    font.setFamily("Microsoft YaHei");  // 设置为微软雅黑
    trayMenu->setFont(font);

    // 连接退出操作的槽
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // 将托盘菜单设置到托盘图标
    trayIcon->setContextMenu(trayMenu);

    connectSignals();
}

void MusicController::connectSignals() {
    // 连接按钮的信号和槽函数
    connect(ui->openButton, &QPushButton::clicked, this, &MusicController::openFile);
    connect(ui->exportButton, &QPushButton::clicked, this, &MusicController::exportFile);

    // 连接播放速度和音量调整控件
    connect(ui->speedSlider, &QSlider::valueChanged, this, [this](int value) { updateSpeed(value); });
    connect(ui->speedSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) { updateSpeed(value); });

    connect(ui->volumeSlider, &QSlider::valueChanged, this, [this](int value) { updateVolume(value); });
    connect(ui->volumeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) { updateVolume(value); });
}

// 打开文件对话框并加载音乐文件
void MusicController::openFile() {
    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);  // 获取桌面路径
    filePath = QFileDialog::getOpenFileName(this, "选择音乐文件", defaultPath, "音频文件 (*.mp3 *.wav *.flac *.aac *.ogg)");  // 使用桌面路径作为起始路径
    if (!filePath.isEmpty()) {
        QFileInfo fileInfo(filePath);  // 获取文件信息
        QString extension = fileInfo.suffix().toLower();  // 获取文件扩展名
        if (extension == "mp3" || extension == "wav" || extension == "flac" || extension == "aac" || extension == "ogg") {
            ui->statusbar->showMessage("🟡 已加载文件: \"" + filePath + "\"");  // 更新状态栏信息
            ui->fileNameLabel->setText("当前文件: \"" + fileInfo.fileName() + "\"");  // 更新文件名标签
            ui->exportButton->setEnabled(true);  // 启用导出按钮
        }
        else {
            ui->statusbar->showMessage("🔴 不支持的文件类型: \"" + filePath + "\"");  // 更新状态栏信息
            ui->exportButton->setEnabled(false);  // 禁用导出按钮
        }
    }
}

// 处理拖入事件，接受含有 URL 的拖动
void MusicController::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();  // 接受拖入操作
    }
    else {
        event->ignore();  // 忽略操作
    }
}

// 处理文件拖放事件
void MusicController::dropEvent(QDropEvent* event) {
    const QMimeData* mimeData = event->mimeData();  // 获取 MIME 数据
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();  // 获取 URL 列表
        if (!urlList.isEmpty()) {
            QString filePath = urlList.first().toLocalFile();  // 获取文件路径
            if (!filePath.isEmpty()) {
                QFileInfo fileInfo(filePath);  // 获取文件信息
                QString extension = fileInfo.suffix().toLower();  // 获取文件扩展名
                if (extension == "mp3" || extension == "wav" || extension == "flac" || extension == "aac" || extension == "ogg") {
                    this->filePath = filePath;  // 保存文件路径
                    ui->statusbar->showMessage("🟡 已加载文件: \"" + filePath + "\"");  // 更新状态栏信息
                    ui->fileNameLabel->setText("当前文件: \"" + fileInfo.fileName() + "\"");  // 更新文件名标签
                    ui->exportButton->setEnabled(true);  // 启用导出按钮
                }
                else {
                    ui->statusbar->showMessage("🔴 导入失败: 不支持的文件类型! \"" + filePath + "\"");  // 更新状态栏信息
                    ui->exportButton->setEnabled(false);  // 禁用导出按钮
                }
            }
        }
    }
}

// 更新播放速度
void MusicController::updateSpeed(int value) {
    // 使用新的公式计算倍速，精确到小数点后三位
    double speed = 0.5 + (value - 500) * (9.5 / 9500);  // 将 500 -> 0.5x, 10000 -> 10.0x
    playbackSpeed = speed;  // 保存播放速度

    // 更新倍速显示到 label，精确到小数点后三位
    ui->speedLabel->setText(QString("倍速: %1x").arg(speed, 0, 'f', 3));  // 显示三位小数

    // 更新 slider 和 spinBox 的值
    ui->speedSlider->blockSignals(true);  // 阻止信号
    ui->speedSlider->setValue(value);  // 设置 slider 值
    ui->speedSpinBox->setValue(value);  // 设置 spinBox 值
    ui->speedSlider->blockSignals(false);  // 恢复信号
}

// 更新音量
void MusicController::updateVolume(int value) {
    volume = value;  // 保存音量值
    ui->volumeSlider->setValue(value);  // 设置滑块值
    ui->volumeSpinBox->setValue(value);  // 设置文本框值
}

// 导出文件
void MusicController::exportFile() {
    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);  // 获取桌面路径
    QFileInfo fileInfo(filePath);  // 获取文件信息
    QString baseName = fileInfo.completeBaseName();  // 获取基础文件名
    QString defaultFileName = baseName + ".mp3";  // 默认导出文件名

    // 检查文件是否存在
    if (!QFile::exists(filePath)) {
        QFont font("Microsoft YaHei");  // 设置字体为微软雅黑
        font.setPointSize(10);
        ui->statusbar->showMessage("🔴 导出失败: 文件不存在! \"" + filePath + "\"");  // 更新状态栏信息

        // 弹出提示框，告知文件已经丢失
        QMessageBox msgBox(this);
        msgBox.setFont(font);  // 设置警告框的字体为微软雅黑
        msgBox.setIcon(QMessageBox::Warning);  // 设置图标为警告
        msgBox.setWindowTitle("文件不存在");  // 设置对话框标题
        msgBox.setText("文件 \"" + filePath + "\" 已经丢失或被删除，无法进行导出操作!");
        msgBox.exec();  // 显示对话框

        return;  // 终止导出操作
    }

    QString exportPath = QFileDialog::getSaveFileName(this, "选择导出位置", defaultPath + "/" + defaultFileName, "MP3文件 (*.mp3)");  // 使用桌面路径作为起始路径

    if (!exportPath.isEmpty()) {
        // 检查文件是否存在
        if (!QFile::exists(filePath)) {
            QFont font("Microsoft YaHei");  // 设置字体为微软雅黑
            font.setPointSize(10);
            ui->statusbar->showMessage("🔴 导出失败: 文件不存在! \"" + filePath + "\"");  // 更新状态栏信息

            // 弹出提示框，告知文件已经丢失
            QMessageBox msgBox(this);
            msgBox.setFont(font);  // 设置警告框的字体为微软雅黑
            msgBox.setIcon(QMessageBox::Warning);  // 设置图标为警告
            msgBox.setWindowTitle("文件不存在");  // 设置对话框标题
            msgBox.setText("文件 \"" + filePath + "\" 已经丢失或被删除，无法进行导出操作!");
            msgBox.exec();  // 显示对话框

            return;  // 终止导出操作
        }

        // 如果文件存在，继续导出
        ui->statusbar->showMessage("🟡 正在导出中: \"" + exportPath + "\"");  // 更新状态栏信息

        QString command = buildFFmpegCommand(filePath, exportPath, playbackSpeed, volume);  // 构建 FFmpeg 命令

        QProcess* process = new QProcess(this);  // 创建进程
        process->setProcessChannelMode(QProcess::MergedChannels);  // 合并标准输出和标准错误
        process->start(command);  // 启动进程

        connect(process, &QProcess::readyReadStandardOutput, [this, process]() {
            QString output = process->readAllStandardOutput();  // 读取标准输出
            updateProgressFromOutput(output);  // 更新进度
            });

        connect(process, &QProcess::readyReadStandardError, [this, process]() {
            // 错误处理 (如果有)
            });

        connect(process, &QProcess::finished, [this, exportPath]() {
            ui->progressBar->setValue(100);  // 设置进度条为100%
            ui->statusbar->showMessage("🟢 导出成功: \"" + exportPath + "\"");  // 更新状态栏信息

            CustomDialog* dialog = new CustomDialog(this);  // 创建对话框
            dialog->setFilePath(exportPath);  // 设置文件路径
            dialog->setMessage("导出成功: " + exportPath);  // 设置对话框消息
            dialog->exec();  // 显示对话框
            });
    }
}

// 从 FFmpeg 输出中更新进度
void MusicController::updateProgressFromOutput(const QString& output) {
    QRegularExpression progressRegex("time=(\\d+):(\\d+):(\\d+\\.\\d+)");  // 正则表达式匹配时间
    QRegularExpressionMatch match = progressRegex.match(output);  // 匹配输出
    if (match.hasMatch()) {
        QString timeStr = match.captured(0);  // 获取匹配的时间字符串
        QStringList timeParts = timeStr.split(":");  // 分割时间字符串
        if (timeParts.size() == 3) {
            bool ok;
            double seconds = timeParts[0].toDouble(&ok) * 3600 +
                timeParts[1].toDouble(&ok) * 60 +
                timeParts[2].toDouble(&ok);  // 计算总秒数
            if (ok) {
                double totalDuration = 180.0;  // 假设总时长(可以根据实际情况修改)
                int progress = static_cast<int>((seconds / totalDuration) * 100);  // 计算进度百分比
                ui->progressBar->setValue(progress);  // 更新进度条
            }
        }
    }
}

// 替换路径中的反斜杠
QString replaceBackslashes(const QString& path) {
    QString result = path;
    for (int i = 0; i < result.length(); ++i) {
        if (result[i] == '\\') {
            result[i] = '/';  // 将反斜杠替换为正斜杠
        }
    }
    return result;
}

// 构建 FFmpeg 命令
QString MusicController::buildFFmpegCommand(const QString& inputFilePath, const QString& outputFilePath, double speed, int volume) {
    QString speedFilter = QString("atempo=%1").arg(speed, 0, 'f', 3);  // 设置速度滤镜
    QString volumeFilter = QString("volume=%1dB").arg(volume);  // 设置音量滤镜

    QString sanitizedInputFilePath = QDir::toNativeSeparators(inputFilePath);  // 替换路径中的斜杠
    QString sanitizedOutputFilePath = QDir::toNativeSeparators(outputFilePath);  // 替换路径中的斜杠
    return QString("ffmpeg -y -i \"%1\" -af \"%2, %3\" -progress pipe:1 \"%4\"")
        .arg(sanitizedInputFilePath)  // 输入文件路径
        .arg(speedFilter)  // 速度滤镜
        .arg(volumeFilter)  // 音量滤镜
        .arg(sanitizedOutputFilePath);  // 输出文件路径
}
