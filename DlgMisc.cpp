#include "DlgMisc.hpp"
#include <QFile>
#include <QPointer>
#include <QPlainTextEdit>
#include <QFileInfo>
#include <QDataStream>
#include <QHBoxLayout>
#include <QDialogButtonBox>

DlgMisc::DlgMisc(QWidget* parent)
    : QDialog(parent)
{
    // Remove the '?' button
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

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

    setMinimumSize(480, 600);
}

DlgMisc::~DlgMisc()
{
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

    // Create a buffer to read the file
    qint64 length = file.size();
    char* buffer = new char[length];

    // Create a stream to read the file
    QDataStream stream(&file);
    stream.readRawData(buffer, length);

    // Create the edit widget which contains the text
    QPlainTextEdit* textEdit = new QPlainTextEdit(buffer);
    textEdit->setReadOnly(true);

    //Create the title based on the file name
    QFileInfo info(filename);
    QString title = info.completeBaseName();

    // Add the tab to the QTabWidget and release the buffer
    tabWidget->addTab(textEdit, title);
    delete[] buffer;
}
