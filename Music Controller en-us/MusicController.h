#ifndef MUSICCONTROLLER_H
#define MUSICCONTROLLER_H

#include <QMainWindow>
#include <QString>
#include <QProcess>
#include <QRegularExpression>  // Replaces QRegExp with QRegularExpression
#include <QSystemTrayIcon>      // Added to support system tray notifications
#include "ui_MusicController.h"

// The MusicController class inherits from QMainWindow for music control interface and logic
class MusicController : public QMainWindow {
    Q_OBJECT

public:
    // Constructor: Initializes the MusicController instance
    explicit MusicController(QWidget* parent = nullptr);

private slots:
    // Slot function: Opens a file
    void openFile();

    // Slot function: Updates playback speed
    void updateSpeed(int value);

    // Slot function: Updates volume
    void updateVolume(int value);

    // Slot function: Exports the file
    void exportFile();

protected:
    // Event handler: Handles drag-enter events
    void dragEnterEvent(QDragEnterEvent* event) override;

    // Event handler: Handles drop events
    void dropEvent(QDropEvent* event) override;

private:
    // UI component pointer: Manages UI elements
    Ui::MainWindow* ui;

    // Current file path
    QString filePath;

    // Playback speed (multiplier)
    double playbackSpeed;

    // Volume (range 0 to 100)
    int volume;

    // System tray icon for notifications
    QSystemTrayIcon* trayIcon;

    // Connect signals and slots
    void connectSignals();

    // Build FFmpeg command line arguments
    QString buildFFmpegCommand(const QString& inputFilePath, const QString& outputFilePath, double speed, int volume);

    // Update progress from FFmpeg output
    void updateProgressFromOutput(const QString& output);
};

#endif // MUSICCONTROLLER_H
