//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef TIMER_HPP
#define TIMER_HPP

#include <QTimer>
#include <QObject>
#include <QString>
#include <windows.h>
#include <QMetaType>
#include <QKeySequence>
#include <QMediaPlayer>
#include <QMediaContent>

#define PERIOD_MIN 1
#define PERIOD_MAX 600

#define STATUS_UNDEFINED 0
#define STATUS_STOPPED 1
#define STATUS_PLAYING 2
#define STATUS_BROKEN 3

/*
 *  This class contains a timer, which can be started and stopped with a hotkey
 *
 */

class Timer : public QObject
{
    Q_OBJECT

  public:
    Timer(QString filename, int period, QKeySequence keySequence, UINT virtualKey, UINT modifiers, unsigned int hotkeyId);
    ~Timer();
    void setNewData(int period, QKeySequence keySequence, UINT virtualKey, UINT modifiers, int hotkeyId);

    QString getFilename() const { return filename; }
    int getPeriod() const { return period; }
    QKeySequence getKeySequence() const { return keySequence; }
    UINT getVirtualKey() const { return virtualKey; }
    UINT getModifiers() const { return modifiers; }
    unsigned int getHotkeyId() const { return hotkeyId; }
    bool isBroken() const { return broken; }

  private:
    Q_DISABLE_COPY(Timer)

    QString filename;
    int period;
    QKeySequence keySequence;
    UINT virtualKey;
    UINT modifiers;
    int hotkeyId;

    QTimer* timer;
    QMediaPlayer* player;
    QMediaContent* mediaContent;
    bool broken;

    void play();
    void stop();
    void playSound();
    void togglePlayStop(int hotkeyId);

    void setBroken();
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void error(QMediaPlayer::Error error);
};

Q_DECLARE_METATYPE(Timer*)

#endif // TIMER_HPP
