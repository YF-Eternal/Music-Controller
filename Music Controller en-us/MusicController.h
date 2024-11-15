#ifndef MUSICCONTROLLER_H
#define MUSICCONTROLLER_H

#include <QMainWindow>
#include <QString>
#include <QProcess>
#include <QRegularExpression>  // Use QRegularExpression instead of QRegExp
#include <QSystemTrayIcon>      // Add this include for system tray notifications
#include "ui_MusicController.h"

// MusicController class inherits from QMainWindow, used for music control interface and logic
class MusicController : public QMainWindow {
    Q_OBJECT

public:
    // Constructor: Initializes MusicController instance
    explicit MusicController(QWidget* parent = nullptr);

private slots:
    // Slot function: Open file
    void openFile();

    // Slot function: Update playback speed
    void updateSpeed(int value);

    // Slot function: Update volume
    void updateVolume(int value);

    // Slot function: Export file
    void exportFile();

protected:
    // Event handler: Handle drag enter event
    void dragEnterEvent(QDragEnterEvent* event) override;

    // Event handler: Handle drop event
    void dropEvent(QDropEvent* event) override;

private:
    // UI component pointer: Manages interface elements
    Ui::MainWindow* ui;

    // Current file path
    QString filePath;

    // Playback speed (multiplier)
    double playbackSpeed;

    // Volume (range 0 to 100)
    int volume;

    // System tray icon, used for notifications
    QSystemTrayIcon* trayIcon;

    // Connect signals and slots
    void connectSignals();

    // Build FFmpeg command line arguments
    QString buildFFmpegCommand(const QString& inputFilePath, const QString& outputFilePath, double speed, int volume);

    // Update progress from FFmpeg output
    void updateProgressFromOutput(const QString& output);
};

#endif // MUSICCONTROLLER_H
