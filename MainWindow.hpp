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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

// Game speed
#define GAME_SPEED_SLOWER 0
#define GAME_SPEED_SLOW 1
#define GAME_SPEED_NORMAL 2
#define GAME_SPEED_FAST 3
#define GAME_SPEED_FASTER 4

// Time multiplier according to the game speed
#define SPEED_SLOWER_MULTIPLIER 0.6
#define SPEED_SLOW_MULTIPLIER 0.8
#define SPEED_NORMAL_MULTIPLIER 1.0
#define SPEED_FAST_MULTIPLIER 1.2
#define SPEED_FASTER_MULTIPLIER 1.4

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private:
    Q_DISABLE_COPY(MainWindow)
    Ui::MainWindow* ui;

  private slots:
    void on_editName_textChanged(const QString& text);
    void on_comboSpeed_currentIndexChanged(int index);
    void on_hsliderPeriod_valueChanged(int value);
    void on_buttonCreate_clicked();
    void on_comboSound_activated(int index);
    void closeTab(int index);

    void on_buttonSaveTimers_clicked();

    void on_buttonOpenTimers_clicked();

    signals:
    void speedChanged(double);
};

#endif // MAINWINDOW_HPP
