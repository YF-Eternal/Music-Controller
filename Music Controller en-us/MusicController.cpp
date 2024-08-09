#include "MusicController.h"
#include "CustomDialog.h"
#include <QFileDialog>
#include <QDebug>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QRegularExpression>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QFontDatabase>

MusicController::MusicController(QWidget* parent)
    : QMainWindow(parent), playbackSpeed(1.0), volume(0), ui(new Ui::MainWindow), trayIcon(new QSystemTrayIcon(this)) {
    ui->setupUi(this);
    this->setWindowTitle("Music Controller");
    setWindowIcon(QIcon(":/icon.ico"));

    this->setFixedSize(this->size());
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    ui->speedSlider->setValue(100);
    ui->speedSpinBox->setValue(100);
    ui->volumeSlider->setValue(volume);
    ui->volumeSpinBox->setValue(volume);
    ui->speedLabel->setText("Speed: 1.0x");
    ui->statusbar->showMessage("🔘 Waiting for action... (Click \"Import\" to add or drag audio files directly)");

    ui->exportButton->setEnabled(false);
    ui->exportButton->setStyleSheet("QPushButton:disabled { background-color: lightgray; color: gray; border: 1px solid gray; }");

    setAcceptDrops(true);

    trayIcon->setIcon(QIcon(":/icon.ico"));
    trayIcon->setVisible(true);

    // Create tray menu
    QMenu* trayMenu = new QMenu(this);
    QAction* exitAction = new QAction("Exit", this);
    trayMenu->addAction(exitAction);

    // Set menu font to Microsoft YaHei
    QFont font = QFontDatabase::systemFont(QFontDatabase::GeneralFont);
    font.setFamily("Microsoft YaHei");  // Set to Microsoft YaHei
    trayMenu->setFont(font);

    // Connect exit action slot
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // Set tray menu to tray icon
    trayIcon->setContextMenu(trayMenu);

    connectSignals();
}

void MusicController::connectSignals() {
    connect(ui->openButton, &QPushButton::clicked, this, &MusicController::openFile);
    connect(ui->exportButton, &QPushButton::clicked, this, &MusicController::exportFile);

    connect(ui->speedSlider, &QSlider::valueChanged, this, [this](int value) { updateSpeed(value); });
    connect(ui->speedSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) { updateSpeed(value); });

    connect(ui->volumeSlider, &QSlider::valueChanged, this, [this](int value) { updateVolume(value); });
    connect(ui->volumeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) { updateVolume(value); });
}

// Open file dialog and load music file
void MusicController::openFile() {
    filePath = QFileDialog::getOpenFileName(this, "Select Music File", "", "Audio Files (*.mp3 *.wav *.flac *.aac *.ogg)");  // Get file path
    if (!filePath.isEmpty()) {
        QFileInfo fileInfo(filePath);  // Get file info
        QString extension = fileInfo.suffix().toLower();  // Get file extension
        if (extension == "mp3" || extension == "wav" || extension == "flac" || extension == "aac" || extension == "ogg") {
            ui->statusbar->showMessage("🟡 File Loaded: \"" + filePath + "\"");  // Update status bar
            ui->fileNameLabel->setText("Current File: \"" + fileInfo.fileName() + "\"");  // Update file name label
            ui->exportButton->setEnabled(true);  // Enable export button
        }
        else {
            ui->statusbar->showMessage("🔴 Unsupported File Type: \"" + filePath + "\"");  // Update status bar
            ui->exportButton->setEnabled(false);  // Disable export button
        }
    }
}

// Handle drag enter event, accept drag containing URLs
void MusicController::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();  // Accept drag operation
    }
    else {
        event->ignore();  // Ignore operation
    }
}

// Handle file drop event
void MusicController::dropEvent(QDropEvent* event) {
    const QMimeData* mimeData = event->mimeData();  // Get MIME data
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();  // Get URL list
        if (!urlList.isEmpty()) {
            QString filePath = urlList.first().toLocalFile();  // Get file path
            if (!filePath.isEmpty()) {
                QFileInfo fileInfo(filePath);  // Get file info
                QString extension = fileInfo.suffix().toLower();  // Get file extension
                if (extension == "mp3" || extension == "wav" || extension == "flac" || extension == "aac" || extension == "ogg") {
                    this->filePath = filePath;  // Save file path
                    ui->statusbar->showMessage("🟡 File Loaded: \"" + filePath + "\"");  // Update status bar
                    ui->fileNameLabel->setText("Current File: \"" + fileInfo.fileName() + "\"");  // Update file name label
                    ui->exportButton->setEnabled(true);  // Enable export button
                }
                else {
                    ui->statusbar->showMessage("🔴 Unsupported File Type: \"" + filePath + "\"");  // Update status bar
                    ui->exportButton->setEnabled(false);  // Disable export button
                }
            }
        }
    }
}

// Update playback speed
void MusicController::updateSpeed(int value) {
    double speed = value / 100.0;  // Calculate speed value
    playbackSpeed = speed;  // Save playback speed
    ui->speedLabel->setText(QString("Speed: %1x").arg(speed));  // Update speed label
    ui->speedSlider->blockSignals(true);  // Block signals
    ui->speedSlider->setValue(value);  // Set slider value
    ui->speedSpinBox->setValue(value);  // Set spin box value
    ui->speedSlider->blockSignals(false);  // Unblock signals
}

// Update volume
void MusicController::updateVolume(int value) {
    volume = value;  // Save volume value
    ui->volumeSlider->setValue(value);  // Set slider value
    ui->volumeSpinBox->setValue(value);  // Set spin box value
}

// Export file
void MusicController::exportFile() {
    QFileInfo fileInfo(filePath);  // Get file info
    QString baseName = fileInfo.completeBaseName();  // Get base file name
    QString defaultFileName = baseName + ".mp3";  // Default export file name

    QString exportPath = QFileDialog::getSaveFileName(this, "Select Export Location", defaultFileName, "MP3 Files (*.mp3)");  // Get export path

    if (!exportPath.isEmpty()) {
        ui->statusbar->showMessage("🟡 Exporting: \"" + exportPath + "\"");  // Update status bar

        QString command = buildFFmpegCommand(filePath, exportPath, playbackSpeed, volume);  // Build FFmpeg command

        QProcess* process = new QProcess(this);  // Create process
        process->setProcessChannelMode(QProcess::MergedChannels);  // Merge standard output and standard error
        process->start(command);  // Start process

        connect(process, &QProcess::readyReadStandardOutput, [this, process]() {
            QString output = process->readAllStandardOutput();  // Read standard output
            updateProgressFromOutput(output);  // Update progress
            });

        connect(process, &QProcess::readyReadStandardError, [this, process]() {
            });

        connect(process, &QProcess::finished, [this, exportPath]() {
            ui->progressBar->setValue(100);  // Set progress bar to 100%
            ui->statusbar->showMessage("🟢 Export Successful: \"" + exportPath + "\"");  // Update status bar

            CustomDialog* dialog = new CustomDialog(this);  // Create dialog
            dialog->setFilePath(exportPath);  // Set file path
            dialog->setMessage("Export Successful: " + exportPath);  // Set dialog message
            dialog->exec();  // Show dialog
            });
    }
}

// Update progress from FFmpeg output
void MusicController::updateProgressFromOutput(const QString& output) {
    QRegularExpression progressRegex("time=(\\d+):(\\d+):(\\d+\\.\\d+)");  // Regular expression to match time
    QRegularExpressionMatch match = progressRegex.match(output);  // Match output
    if (match.hasMatch()) {
        QString timeStr = match.captured(0);  // Get matched time string
        QStringList timeParts = timeStr.split(":");  // Split time string
        if (timeParts.size() == 3) {
            bool ok;
            double seconds = timeParts[0].toDouble(&ok) * 3600 +
                timeParts[1].toDouble(&ok) * 60 +
                timeParts[2].toDouble(&ok);  // Calculate total seconds
            if (ok) {
                double totalDuration = 180.0;  // Assume total duration (can be adjusted as needed)
                int progress = static_cast<int>((seconds / totalDuration) * 100);  // Calculate progress percentage
                ui->progressBar->setValue(progress);  // Update progress bar
            }
        }
    }
}

// Replace backslashes in path
QString replaceBackslashes(const QString& path) {
    QString result = path;
    for (int i = 0; i < result.length(); ++i) {
        if (result[i] == '\\') {
            result[i] = '/';  // Replace backslashes with forward slashes
        }
    }
    return result;
}

// Build FFmpeg command
QString MusicController::buildFFmpegCommand(const QString& inputFilePath, const QString& outputFilePath, double speed, int volume) {
    QString speedFilter = QString("atempo=%1").arg(speed);  // Set speed filter
    QString volumeFilter = QString("volume=%1dB").arg(volume);  // Set volume filter

    QString sanitizedInputFilePath = QDir::toNativeSeparators(inputFilePath);  // Replace slashes in path
    QString sanitizedOutputFilePath = QDir::toNativeSeparators(outputFilePath);  // Replace slashes in path
    return QString("ffmpeg -y -i \"%1\" -af \"%2, %3\" -progress pipe:1 \"%4\"")
        .arg(sanitizedInputFilePath)  // Input file path
        .arg(speedFilter)  // Speed filter
        .arg(volumeFilter)  // Volume filter
        .arg(sanitizedOutputFilePath);  // Output file path
}
