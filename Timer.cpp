//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
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
#include "Log.hpp"
#include <QMediaPlaylist>
#include <versionhelpers.h>

Timer::Timer(QString filename, int period, QKeySequence keySequence, UINT modifiers, UINT virtualKey, unsigned int hotkeyId)
    : filename(filename)
    , period(period)
    , keySequence(keySequence)
    , modifiers(modifiers)
    , virtualKey(virtualKey)
    , hotkeyId(hotkeyId)
    , broken(false)
{
    Log::instance()->write(tr("Trying to register hotkey:"));
    Log::instance()->write(tr("Hotkey ID: %1").arg(hotkeyId));
    Log::instance()->write(tr("Native Modifiers: %1").arg(modifiers));
    Log::instance()->write(tr("Virtual Key: %1").arg(virtualKey));
    Log::instance()->newLine();

    // Register the hotkey (add the MOD_NOREPEAT flag)
    if (!RegisterHotKey(nullptr, hotkeyId, modifiers | getNoRepeatFlag(), virtualKey)) {
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
    connect(MainWindow::instance()->getNativeEventFilter(), &NativeEventFilter::hotkeyReceived, this, &Timer::togglePlayStop);
}

Timer::~Timer()
{
    UnregisterHotKey(nullptr, this->hotkeyId);
    delete this->mediaContent;
}

// Method called when the timer has been edited
void Timer::setNewData(int period, QKeySequence keySequence, UINT modifiers, UINT virtualKey, int hotkeyId)
{
    // First, try to register the new hotkey if needed
    if ((this->virtualKey != virtualKey) || (this->modifiers != modifiers)) {
        Log::instance()->write(tr("Trying to modify a hotkey:"));
        Log::instance()->write(tr("Previous Hokey ID: %1. New Hotkey ID: %2").arg(this->hotkeyId).arg(hotkeyId));
        Log::instance()->write(tr("Previous Native Modifiers: %1. New Native Modifiers: %2").arg(this->modifiers).arg(modifiers));
        Log::instance()->write(tr("Previous Virtual Key: %1. New Virtual Key: %2").arg(this->virtualKey).arg(virtualKey));
        Log::instance()->newLine();

        if (!RegisterHotKey(nullptr, hotkeyId, modifiers | getNoRepeatFlag(), virtualKey)) {
            throw SMException(tr("failed to register the hotkey. No modification done."));
        }
        UnregisterHotKey(nullptr, this->hotkeyId);
        this->hotkeyId = hotkeyId;
    }

    // Stop the timer if it's currently active
    bool active = this->timer->isActive();
    stop();

    // Update timer's data
    timer->setInterval(period * 1000);
    this->period      = period;
    this->keySequence = keySequence;
    this->modifiers   = modifiers;
    this->virtualKey  = virtualKey;

    // Enable the timer if it was previously active
    if (active) {
        play();
    }
}

// Windows Vista doesn't support the NO_REPEAT_FLAG
UINT Timer::getNoRepeatFlag()
{
    UINT flag = 0x0000;
    if (IsWindows7OrGreater()) {
        flag = 0x4000;
    }
    return flag;
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

void Timer::setBroken()
{
    // Disconnect the timer from the hotkey handler and stop it
    disconnect(MainWindow::instance()->getNativeEventFilter(), &NativeEventFilter::hotkeyReceived, this, &Timer::togglePlayStop);
    this->broken = true;
    this->timer->stop();
    this->player->stop();
    MainWindow::instance()->setTimerStatus(this, STATUS_BROKEN);
}

// Triggerred when the hotkey is pressed
void Timer::togglePlayStop(int hotkeyId)
{
    if (this->hotkeyId == hotkeyId) {
        this->timer->isActive() ? stop() : play();
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
