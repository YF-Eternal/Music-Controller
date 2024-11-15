#include "CustomDialog.h"
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <Windows.h>
#include <QDir>

// Constructor: Initializes the CustomDialog instance
CustomDialog::CustomDialog(QWidget* parent)
    : QDialog(parent), messageLabel(new QLabel(this)),
    openFolderButton(new QPushButton("Open Folder", this)),
    playButton(new QPushButton("Play", this)) {

    // Set the font to Microsoft YaHei
    QFont font("Microsoft YaHei");
    setFont(font);
    messageLabel->setFont(font);
    openFolderButton->setFont(font);
    playButton->setFont(font);

    // Create a vertical layout and add the widgets
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(messageLabel);
    layout->addWidget(openFolderButton);
    layout->addWidget(playButton);

    // Connect signals and slots
    connect(openFolderButton, &QPushButton::clicked, this, &CustomDialog::openFolder);
    connect(playButton, &QPushButton::clicked, this, &CustomDialog::play);

    setLayout(layout);
    setWindowTitle("Notification");

    // Set the minimum and maximum sizes of the dialog and fix the size to the current dialog size
    setMinimumSize(300, 150);  // Set minimum size to 300x150
    setMaximumSize(600, 300);  // Set maximum size to 600x300
    setFixedSize(size());  // Fix the size to the current dialog size

    // Play system notification sound
    playSystemSound();
}

// Set the message to be displayed in the dialog
void CustomDialog::setMessage(const QString& message) {
    messageLabel->setText(message);
}

// Set the file path
void CustomDialog::setFilePath(const QString& path) {
    filePath = path;
}

// Use Windows API to open the folder and select the file
void CustomDialog::openFolder() {
    QFileInfo fileInfo(filePath);  // Get file information
    if (fileInfo.exists()) {  // If the file exists
        // Get the folder path of the file
        QString folderPath = QDir::toNativeSeparators(fileInfo.absolutePath());
        QString fileName = fileInfo.fileName();

        // Construct the command to open the folder and select the file
        QString fullPath = folderPath + "\\" + fileName;

        // Use ShellExecute to open the folder and select the file
        // Convert to wide character string
        std::wstring widePath = fullPath.toStdWString();
        ShellExecute(NULL, L"open", L"explorer.exe", (L"/select,\"" + widePath + L"\"").c_str(), NULL, SW_SHOWNORMAL);
    }
}

// Play the file
void CustomDialog::play() {
    QString command = "explorer \"" + filePath + "\"";  // Use the default system player to play the file
    QProcess::startDetached(command);
}

// Play the system notification sound
void CustomDialog::playSystemSound() {
    // Play the default system notification sound
    MessageBeep(MB_OK);  // Use MessageBeep to play the default system sound
}

// Destructor: Qt will automatically manage the memory of QProcess, so there's no need to manually delete it
CustomDialog::~CustomDialog() {
    // No need to delete process, Qt will manage it automatically
}
