#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QProcess>  // Include QProcess for command execution

class CustomDialog : public QDialog {
    Q_OBJECT

public:
    explicit CustomDialog(QWidget* parent = nullptr);
    void setMessage(const QString& message);  // Set the message to display
    void setFilePath(const QString& path);  // Set the file path
    ~CustomDialog();  // Destructor declaration

private slots:
    void openFolder();  // Open folder and select file
    void play();  // Play the file

private:
    QLabel* messageLabel;  // Label to display the message
    QPushButton* openFolderButton;  // Button to open the folder
    QPushButton* playButton;  // Play button
    QString filePath;  // File path

    QProcess* process;  // QProcess to execute commands
    void playSystemSound();  // Play the system notification sound
};

#endif // CUSTOMDIALOG_H
