#include "DlgMisc.hpp"
#include <QFile>
#include <QPointer>
#include <QFileInfo>
#include <QDataStream>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QDialogButtonBox>

DlgMisc::DlgMisc(QWidget* parent)
    : QDialog(parent)
{
    QTabWidget* tabWidget = new QTabWidget(this);
    QDialogButtonBox* button = new QDialogButtonBox(QDialogButtonBox::Ok, this);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(button);
    mainLayout->setAlignment(button, Qt::AlignCenter);

    createPageWithText(tabWidget, ":/About.txt");
    createPageWithText(tabWidget, ":/Howto.txt");
    createPageWithText(tabWidget, ":/License.txt");

    connect(button, &QDialogButtonBox::accepted, this, &QDialog::accept);

    // Dialog setup
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setMinimumSize(480, 600);
}

// static method which showes up the dialog
void DlgMisc::showDlgMisc(QWidget* parent)
{
    QPointer<DlgMisc> dlg = new DlgMisc(parent);
    dlg->exec();
    delete dlg;
}

void DlgMisc::createPageWithText(QTabWidget* tabWidget, QString filename)
{
    // Open the file
    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    // Create a buffer to read the file, ensure that is has a terminal 0
    // Debug: add one byte, to ensure that the allocation is really performed (used when the files were still empty)
    qint64 length = file.size();
    char* buffer = new char[length + 1];
    buffer[length] = 0;

    // Create a stream to read the file
    QDataStream stream(&file);
    stream.readRawData(buffer, length);

    // Create the edit widget which contains the text
    QPlainTextEdit* textEdit = new QPlainTextEdit(buffer, tabWidget);
    textEdit->setReadOnly(true);

    //Create the title based on the file name
    QFileInfo info(filename);
    QString title = info.completeBaseName();

    // Add the tab to the QTabWidget and release the buffer
    tabWidget->addTab(textEdit, title);
    delete[] buffer;
}
