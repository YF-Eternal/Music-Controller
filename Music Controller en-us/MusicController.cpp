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

    // Initialize control values
    ui->speedSlider->setValue(1000);
    ui->speedSpinBox->setValue(1000);
    ui->volumeSlider->setValue(volume);
    ui->volumeSpinBox->setValue(volume);
    ui->speedLabel->setText("Speed: 1.000x");
    ui->statusbar->showMessage("🔘 Waiting for operation...   (Click \"Import\" to add or drag an audio file)");

    ui->exportButton->setEnabled(false);  // Initially disable export button
    ui->exportButton->setStyleSheet("QPushButton:disabled { background-color: lightgray; color: gray; border: 1px solid gray; }");

    setAcceptDrops(true);  // Enable drag-and-drop functionality

    trayIcon->setIcon(QIcon(":/icon.ico"));
    trayIcon->setVisible(true);

    // Create tray menu
    QMenu* trayMenu = new QMenu(this);
    QAction* exitAction = new QAction("Exit", this);
    trayMenu->addAction(exitAction);

    // Set tray menu font to Arial
    QFont font = QFontDatabase::systemFont(QFontDatabase::GeneralFont);
    font.setFamily("Arial");  // Set to Arial
    trayMenu->setFont(font);

    // Connect exit action
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // Set the tray menu to the tray icon
    trayIcon->setContextMenu(trayMenu);

    connectSignals();
}

void MusicController::connectSignals() {
    // Connect button signals to slot functions
    connect(ui->openButton, &QPushButton::clicked, this, &MusicController::openFile);
    connect(ui->exportButton, &QPushButton::clicked, this, &MusicController::exportFile);

    // Connect playback speed and volume adjustment controls
    connect(ui->speedSlider, &QSlider::valueChanged, this, [this](int value) { updateSpeed(value); });
    connect(ui->speedSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) { updateSpeed(value); });

    connect(ui->volumeSlider, &QSlider::valueChanged, this, [this](int value) { updateVolume(value); });
    connect(ui->volumeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) { updateVolume(value); });
}

// Open file dialog and load music file
void MusicController::openFile() {
    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);  // Get desktop path
    filePath = QFileDialog::getOpenFileName(this, "Choose Music File", defaultPath, "Audio Files (*.mp3 *.wav *.flac *.aac *.ogg)");  // Use desktop as default path
    if (!filePath.isEmpty()) {
        QFileInfo fileInfo(filePath);  // Get file information
        QString extension = fileInfo.suffix().toLower();  // Get file extension
        if (extension == "mp3" || extension == "wav" || extension == "flac" || extension == "aac" || extension == "ogg") {
            ui->statusbar->showMessage("🟡 File Loaded: \"" + filePath + "\"");  // Update status bar
            ui->fileNameLabel->setText("Current File: \"" + fileInfo.fileName() + "\"");  // Update filename label
            ui->exportButton->setEnabled(true);  // Enable export button
        }
        else {
            ui->statusbar->showMessage("🔴 Unsupported file type: \"" + filePath + "\"");  // Update status bar
            ui->exportButton->setEnabled(false);  // Disable export button
        }
    }
}

// Handle drag enter event, accept URLs
void MusicController::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();  // Accept drag action
    }
    else {
        event->ignore();  // Ignore action
    }
}

// Handle file drop event
void MusicController::dropEvent(QDropEvent* event) {
    const QMimeData* mimeData = event->mimeData();  // Get MIME data
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();  // Get list of URLs
        if (!urlList.isEmpty()) {
            QString filePath = urlList.first().toLocalFile();  // Get file path
            if (!filePath.isEmpty()) {
                QFileInfo fileInfo(filePath);  // Get file information
                QString extension = fileInfo.suffix().toLower();  // Get file extension
                if (extension == "mp3" || extension == "wav" || extension == "flac" || extension == "aac" || extension == "ogg") {
                    this->filePath = filePath;  // Save file path
                    ui->statusbar->showMessage("🟡 File Loaded: \"" + filePath + "\"");  // Update status bar
                    ui->fileNameLabel->setText("Current File: \"" + fileInfo.fileName() + "\"");  // Update filename label
                    ui->exportButton->setEnabled(true);  // Enable export button
                }
                else {
                    ui->statusbar->showMessage("🔴 Import failed: Unsupported file type! \"" + filePath + "\"");  // Update status bar
                    ui->exportButton->setEnabled(false);  // Disable export button
                }
            }
        }
    }
}

// Update playback speed
void MusicController::updateSpeed(int value) {
    // Use a new formula to calculate speed, accurate to 3 decimal places
    double speed = 0.5 + (value - 500) * (9.5 / 9500);  // 500 -> 0.5x, 10000 -> 10.0x
    playbackSpeed = speed;  // Save playback speed

    // Update speed label, accurate to 3 decimal places
    ui->speedLabel->setText(QString("Speed: %1x").arg(speed, 0, 'f', 3));  // Display 3 decimal places

    // Update slider and spinBox values
    ui->speedSlider->blockSignals(true);  // Block signals
    ui->speedSlider->setValue(value);  // Set slider value
    ui->speedSpinBox->setValue(value);  // Set spinBox value
    ui->speedSlider->blockSignals(false);  // Unblock signals
}

// Update volume
void MusicController::updateVolume(int value) {
    volume = value;  // Save volume value
    ui->volumeSlider->setValue(value);  // Set slider value
    ui->volumeSpinBox->setValue(value);  // Set spinBox value
}

// Export file
void MusicController::exportFile() {
    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);  // Get desktop path
    QFileInfo fileInfo(filePath);  // Get file information
    QString baseName = fileInfo.completeBaseName();  // Get base filename
    QString defaultFileName = baseName + ".mp3";  // Default export filename

    // Check if file exists
    if (!QFile::exists(filePath)) {
        QFont font("Arial");  // Set font to Arial
        font.setPointSize(10);
        ui->statusbar->showMessage("🔴 Export failed: File not found! \"" + filePath + "\"");  // Update status bar

        // Show message box informing that the file is missing
        QMessageBox msgBox(this);
        msgBox.setFont(font);  // Set font for the warning box to Arial
        msgBox.setIcon(QMessageBox::Warning);  // Set icon to warning
        msgBox.setWindowTitle("File Not Found");  // Set dialog title
        msgBox.setText("File \"" + filePath + "\" has been lost or deleted and cannot be exported!");
        msgBox.exec();  // Show dialog

        return;  // Abort export
    }
    QString exportPath = QFileDialog::getSaveFileName(this, "Choose Export Location", defaultPath + "/" + defaultFileName, "MP3 Files (*.mp3)");  // Use desktop as default path

    if (!exportPath.isEmpty()) {
        // Check if file exists
        if (!QFile::exists(filePath)) {
            QFont font("Arial");  // Set font to Arial
            font.setPointSize(10);
            ui->statusbar->showMessage("🔴 Export failed: File not found! \"" + filePath + "\"");  // Update status bar

            // Show message box informing that the file is missing
            QMessageBox msgBox(this);
            msgBox.setFont(font);  // Set font for the warning box to Arial
            msgBox.setIcon(QMessageBox::Warning);  // Set icon to warning
            msgBox.setWindowTitle("File Not Found");  // Set dialog title
            msgBox.setText("File \"" + filePath + "\" has been lost or deleted and cannot be exported!");
            msgBox.exec();  // Show dialog

            return;  // Abort export
        }

        // If file exists, proceed with export
        ui->statusbar->showMessage("🟡 Exporting: \"" + exportPath + "\"");  // Update status bar

        QString command = buildFFmpegCommand(filePath, exportPath, playbackSpeed, volume);  // Build FFmpeg command

        QProcess* process = new QProcess(this);  // Create process
        process->setProcessChannelMode(QProcess::MergedChannels);  // Merge standard output and error
        process->start(command);  // Start process

        connect(process, &QProcess::readyReadStandardOutput, [this, process]() {
            QString output = process->readAllStandardOutput();  // Read standard output
            updateProgressFromOutput(output);  // Update progress
            });

        connect(process, &QProcess::finished, [this, exportPath]() {
            ui->progressBar->setValue(100);  // Set progress bar to 100%
            ui->statusbar->showMessage("🟢 Export Successful: \"" + exportPath + "\"");  // Update status bar

            CustomDialog* dialog = new CustomDialog(this);  // Create dialog
            dialog->setFilePath(exportPath);  // Set file path
            dialog->setMessage("Export successful: " + exportPath);  // Set dialog message
            dialog->exec();  // Show dialog
            });
    }
}

// Update progress from FFmpeg output
void MusicController::updateProgressFromOutput(const QString& output) {
    QRegularExpression progressRegex("time=(\\d+):(\\d+):(\\d+\\.\\d+)");  // Regex to match time
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
                double totalDuration = 180.0;  // Assume total duration (can be modified)
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
    QString speedFilter = QString("atempo=%1").arg(speed, 0, 'f', 3);  // Set speed filter
    QString volumeFilter = QString("volume=%1dB").arg(volume);  // Set volume filter

    QString sanitizedInputFilePath = QDir::toNativeSeparators(inputFilePath);  // Replace slashes in paths
    QString sanitizedOutputFilePath = QDir::toNativeSeparators(outputFilePath);  // Replace slashes in paths
    return QString("ffmpeg -y -i \"%1\" -af \"%2, %3\" -progress pipe:1 \"%4\"")
        .arg(sanitizedInputFilePath)  // Input file path
        .arg(speedFilter)  // Speed filter
        .arg(volumeFilter)  // Volume filter
        .arg(sanitizedOutputFilePath);  // Output file path
}
