// Folco's Metronome for SC2.
// Copyright (C) 2015  Martial Demolins AKA Folco

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef ABOUTUI_HPP
#define ABOUTUI_HPP

#include <QDialog>

namespace Ui
{
    class AboutUi;
}

// This class provides the about box

class AboutUi : public QDialog
{
    Q_OBJECT
  public:
    explicit AboutUi(QWidget* parent = 0);
    ~AboutUi();
    static void display();
    QSize sizeHint() const;

  private:
    Ui::AboutUi* ui;
};

#endif // ABOUTUI_HPP
