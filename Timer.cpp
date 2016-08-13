//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "SMException.hpp"
#include "MainWindow.hpp"
#include "Timer.hpp"
#include <QMediaPlaylist>

Timer::Timer(QString filename, int period, QKeySequence keySequence, UINT virtualKey, UINT modifiers, unsigned int hotkeyId)
    : filename(filename)
    , period(period)
    , keySequence(keySequence)
    , virtualKey(virtualKey)
    , modifiers(modifiers)
    , hotkeyId(hotkeyId)
    , broken(false)
{
    // Register the hotkey (add the MOD_NOREPEAT flag)
    if (!RegisterHotKey(nullptr, hotkeyId, modifiers | 0x4000, virtualKey)) {
        throw SMException(tr("failed to register the hotkey."));
    }

    // Create the player, the playlist and the media container
    this->mediaContent       = new QMediaContent(filename);
    this->player             = new QMediaPlayer(this);
    QMediaPlaylist* playlist = new QMediaPlaylist(this);

    // Give the media to the playlist, and the playlist to the player
    playlist->addMedia(*mediaContent);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    player->setMedia(playlist);

    // Create the timer
    this->timer = new QTimer(this);
    this->timer->setInterval(period * 1000);

    // Connections
    connect(this->player, &QMediaPlayer::mediaStatusChanged, this, &Timer::mediaStatusChanged);
    connect(this->player, static_cast<void (QMediaPlayer::*)(QMediaPlayer::Error)>(&QMediaPlayer::error), this, &Timer::error);
    connect(this->timer, &QTimer::timeout, this, &Timer::playSound);
}

Timer::~Timer()
{
    UnregisterHotKey(nullptr, this->hotkeyId);
    delete this->mediaContent;
}

// Method called when the timer has been edited
void Timer::setNewData(int period, QKeySequence keySequence, UINT virtualKey, UINT modifiers, unsigned int hotkeyId)
{
    // First, try to register the new hotkey if needed
    if ((this->virtualKey != virtualKey) || (this->modifiers != modifiers)) {
        if (!RegisterHotKey(nullptr, hotkeyId, modifiers | 0x4000, virtualKey)) {
            throw SMException(tr("failed to register the hotkey. No modification done."));
        }
        UnregisterHotKey(nullptr, this->hotkeyId);
        this->hotkeyId = hotkeyId;
    }

    bool active = this->timer->isActive();
    stop();

    timer->setInterval(period * 1000);
    this->period      = period;
    this->keySequence = keySequence;
    this->virtualKey  = virtualKey;
    this->modifiers   = modifiers;

    if (active) {
        play();
    }
}

// Getters
unsigned int Timer::getHotkeyId() const
{
    return this->hotkeyId;
}

QString Timer::getFilename() const
{
    return this->filename;
}

int Timer::getPeriod() const
{
    return this->period;
}

QKeySequence Timer::getKeySequence() const
{
    return this->keySequence;
}

UINT Timer::getVirtualKey() const
{
    return this->virtualKey;
}

UINT Timer::getModifiers() const
{
    return this->modifiers;
}

// Slots called when an event occurs to the player
void Timer::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::InvalidMedia) {
        setBroken();
    }
}

void Timer::error(QMediaPlayer::Error error)
{
    if (error != QMediaPlayer::NoError) {
        setBroken();
    }
}

bool Timer::isBroken() const
{
    return this->broken;
}

void Timer::setBroken()
{
    this->timer->stop();
    this->player->stop();
    this->broken = true;
    MainWindow::instance()->setTimerStatus(this, STATUS_BROKEN);
}

// Triggerred when the hotkey is pressed
void Timer::togglePlayStop()
{
    if (!this->broken) {
        if (this->timer->isActive()) {
            stop();
        }
        else {
            play();
        }
    }
}

// Start and stop the Timer
void Timer::play()
{
    MainWindow::instance()->setTimerStatus(this, STATUS_PLAYING);
    this->timer->start();
    playSound();
}

void Timer::stop()
{
    MainWindow::instance()->setTimerStatus(this, STATUS_STOPPED);
    this->timer->stop();
    this->player->stop();
}

// Play the sound, ensuring that it's stopped
void Timer::playSound()
{
    this->player->stop();
    this->player->play();
}
