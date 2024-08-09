#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class CustomDialog : public QDialog {
    Q_OBJECT

public:
    // Constructor: Initializes the CustomDialog instance
    explicit CustomDialog(QWidget* parent = nullptr);

    // Sets the message displayed in the dialog
    void setMessage(const QString& message);

    // Sets the file operation path
    void setFilePath(const QString& path);

private slots:
    // Slot function: Opens the folder containing the file
    void openFolder();

    // Slot function: Plays the file
    void play();

private:
    QLabel* messageLabel;         // Label to display the message
    QPushButton* openFolderButton; // Button to open the folder
    QPushButton* playButton;       // Button to play the file
    QString filePath;             // File path

    // Plays a system sound notification
    void playSystemSound();
};

#endif // CUSTOMDIALOG_H
