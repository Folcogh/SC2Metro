//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "MainWindow.hpp"
#include "SC2Metro.hpp"
#include "Log.hpp"
#include <QObject>
#include <QMessageBox>
#include <QApplication>

int main(int argc, char* argv[])
{
    int retval = -1;

    // Initialize the application
    QApplication application(argc, argv);
    application.setApplicationVersion(QString(VERSION));

    // Check that we have no more than one argumen in the command line
    if (argc > 2) {
        QMessageBox::critical(
            nullptr, QObject::tr("Invalid number of arguments"), QObject::tr("SC2Metro invocation must have zero or one argument"), QMessageBox::Ok);
        return retval;
    }

    // Create a log file
    Log::instance();

    // Create and show the ui
    MainWindow::instance()->show();

    if (argc == 2) {
        MainWindow::instance()->openFile(argv[1]);
    }
    retval = application.exec();

    // Cleanup
    delete MainWindow::instance();
    delete Log::instance();
    return retval;
}
