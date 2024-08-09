#include "CustomDialog.h"
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <Windows.h>

// Constructor: Initializes the CustomDialog instance
CustomDialog::CustomDialog(QWidget* parent)
    : QDialog(parent), messageLabel(new QLabel(this)),
    openFolderButton(new QPushButton("Open Folder", this)),
    playButton(new QPushButton("Play", this)) {

    // Set font to Microsoft YaHei
    QFont font("Microsoft YaHei");
    setFont(font);
    messageLabel->setFont(font);
    openFolderButton->setFont(font);
    playButton->setFont(font);

    // Create vertical layout and add widgets
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(messageLabel);
    layout->addWidget(openFolderButton);
    layout->addWidget(playButton);

    // Connect signals and slots
    connect(openFolderButton, &QPushButton::clicked, this, &CustomDialog::openFolder);
    connect(playButton, &QPushButton::clicked, this, &CustomDialog::play);

    setLayout(layout);
    setWindowTitle("Notification");

    // Set the minimum and maximum size of the dialog, and fix the size to the current dialog size
    setMinimumSize(300, 150);  // Set minimum size to 300x150
    setMaximumSize(600, 300);  // Set maximum size to 600x300
    setFixedSize(size());  // Fix size to the current dialog size

    // Play system notification sound
    playSystemSound();
}

// Set the message displayed in the dialog
void CustomDialog::setMessage(const QString& message) {
    messageLabel->setText(message);
}

// Set the file path
void CustomDialog::setFilePath(const QString& path) {
    filePath = path;
}

// Open the folder containing the file
void CustomDialog::openFolder() {
    QFileInfo fileInfo(filePath);
    QString folderPath = fileInfo.absolutePath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
}

// Play the file
void CustomDialog::play() {
    QString command = "explorer \"" + filePath + "\""; // Use the system's default player to play the file
    QProcess::startDetached(command);
}

// Play system notification sound
void CustomDialog::playSystemSound() {
    // Play the default system notification sound
    MessageBeep(MB_OK); // Use MessageBeep to play the default system sound
}
