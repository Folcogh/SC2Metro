//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "DlgMisc.hpp"
#include <QFile>
#include <QPointer>
#include <QFileInfo>
#include <QDataStream>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QDialogButtonBox>

DlgMisc::DlgMisc(QWidget* parent)
    : SMDialog(parent)
{
    QTabWidget* tabWidget    = new QTabWidget(this);
    QDialogButtonBox* button = new QDialogButtonBox(QDialogButtonBox::Ok, this);
    QVBoxLayout* mainLayout  = new QVBoxLayout(this);

    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(button);
    mainLayout->setAlignment(button, Qt::AlignCenter);

    createPageWithText(tabWidget, ":/About.txt");
    createPageWithText(tabWidget, ":/Howto.txt");
    createPageWithText(tabWidget, ":/License.txt");

    connect(button, &QDialogButtonBox::accepted, this, &QDialog::accept);

    // Dialog setup
    setMinimumSize(480, 600);
    setWindowTitle(tr("Miscellaneous"));
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
    // Debug: add one byte, to ensure that the allocation is really performed (usefull when the files were still empty)
    qint64 length  = file.size();
    char* buffer   = new char[length + 1];
    buffer[length] = 0;

    // Create a stream to read the file
    QDataStream stream(&file);
    stream.readRawData(buffer, length);

    // Create the edit widget which contains the text
    QPlainTextEdit* textEdit = new QPlainTextEdit(buffer, tabWidget);
    textEdit->setReadOnly(true);

    // Create the title based on the file name
    QFileInfo info(filename);
    QString title = info.completeBaseName();

    // Add the tab to the QTabWidget and release the buffer
    tabWidget->addTab(textEdit, title);
    delete[] buffer;
}
