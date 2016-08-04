//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "SMException.hpp"
#include "Timer.hpp"
#include <QMediaPlaylist>

Timer::Timer(QString filename, int period, QKeySequence keySequence, UINT virtualKey, UINT modifiers, unsigned int hotkeyId)
    : filename(filename)
    , period(period)
    , keySequence(keySequence)
    , virtualKey(virtualKey)
    , modifiers(modifiers)
    , hotkeyId(hotkeyId)
{
    // Create the player, the playlist and the media container
    this->mediaContent = new QMediaContent(filename);
    this->player = new QMediaPlayer(this);
    QMediaPlaylist* playlist = new QMediaPlaylist(this);

    // Give the media to the playlist, and the playlist to the player
    playlist->addMedia(*mediaContent);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    player->setMedia(playlist);

    // Create the timer
    this->timer = new QTimer(this);
    this->timer->setInterval(period * 1000);

    // Finally, register the hotkey (add the MOD_NOREPEAT flag)
    if (!RegisterHotKey(nullptr, hotkeyId, modifiers | 0x4000, virtualKey)) {
        delete this->mediaContent;
        delete this->timer;
        throw SMException(tr("failed to register the hotkey"));
    }

    connect(this->player, &QMediaPlayer::mediaStatusChanged, this, &Timer::mediaStatusChanged);
    connect(this->timer, &QTimer::timeout, this, &Timer::playSound);
}

Timer::~Timer()
{
    delete this->mediaContent;
    UnregisterHotKey(nullptr, this->hotkeyId);
}

void Timer::setNewData(int period, QKeySequence keySequence, UINT virtualKey, UINT modifiers, int hotkeyId)
{
    // First, try to register the new hotkey if needed
    if ((this->virtualKey != virtualKey) || (this->modifiers != modifiers)) {
        if (!RegisterHotKey(nullptr, hotkeyId, modifiers | 0x4000, virtualKey)) {
            throw SMException(tr("failed to register the hotkey"));
        }
        UnregisterHotKey(nullptr, this->hotkeyId);
        this->hotkeyId = hotkeyId;
    }

    bool active = this->timer->isActive();
    if (active) {
        this->timer->stop();
        this->player->stop();
    }

    timer->setInterval(period * 1000);
    this->period = period;
    this->keySequence = keySequence;
    this->virtualKey = virtualKey;
    this->modifiers = modifiers;

    if (active) {
        this->timer->start();
        playSound();
    }
}

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

void Timer::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::InvalidMedia) {
        //TODO: disable timer, update status in the ui
    }
}

bool Timer::togglePlayStop()
{
    bool ret;
    if (this->timer->isActive()) {
        this->timer->stop();
        this->player->stop();
        ret = false;
    }
    else {
        this->timer->start();
        playSound();
        ret = true;
    }
    return ret;
}

void Timer::playSound()
{
    this->player->stop();
    this->player->play();
}
