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

#include "TimerUi.hpp"
#include "ui_TimerUi.h"
#include "TimerMax.hpp"
#include <QButtonGroup>

TimerUi::TimerUi(QString fullfilename, int period, double multiplier)
    : ui(new Ui::TimerUi)
    , m_timer(new QTimer(this))
    , m_multiplier(multiplier)
    , m_media(fullfilename)
    , m_player(new QMediaPlayer(this))
    , m_playlist(new QMediaPlaylist(this))
    , m_broken(false)
    , m_triggers(-1)
{
    // Setup the ui
    ui->setupUi(this);
    ui->hsliderPeriod->setMaximum(TIMER_MAX);
    ui->hsliderPeriod->setValue(period);
    ui->hsliderVolume->setValue(INITIAL_VOLUME);
    ui->labelPercent->setText(QString("%1%").arg(INITIAL_VOLUME));
    ui->labelSound->setText(fullfilename);
    ui->labelBroken->setText(QString());
    ui->spinDelay->setMaximum(TIMER_MAX);

    // ID of the radio buttons
    ui->groupTerminate->setId(ui->radioTerminateTriggers, TERMINATE_ON_TRIGGER_COUNT);
    ui->groupTerminate->setId(ui->radioTerminateSeconds, TERMINATE_ON_TIME_ELAPSED);

    // Setup the timer
    m_timer->setInterval(period * 1000 / multiplier);
    m_timer->setTimerType(Qt::PreciseTimer);

    // Setup the playlist
    m_playlist->addMedia(m_media);
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

    // Setup the player
    m_player->setPlaylist(m_playlist);
    m_player->setVolume(INITIAL_VOLUME);

    // Establish connections
    connect(m_timer, &QTimer::timeout, this, &TimerUi::playMedia);
    connect(ui->buttonStart, &QPushButton::clicked, this, &TimerUi::start);
    connect(ui->buttonStop, &QPushButton::clicked, this, &TimerUi::stop);
    connect(m_player, (void (QMediaPlayer::*)(QMediaPlayer::Error)) & QMediaPlayer::error, this, &TimerUi::error);
}

TimerUi::~TimerUi()
{
    // Ensure that the running objets are stopped before deleting them. It should be useless
    m_player->stop();
    m_timer->stop();
    delete ui;
}

void TimerUi::on_hsliderPeriod_valueChanged(int value)
{
    m_timer->setInterval(value * 1000 / m_multiplier);

    ui->labelSeconds->setText(QString("%1 seconds").arg(value));
    if (ui->spinDelay->value() > value)
    {
        ui->spinDelay->setValue(value);
    }
}

void TimerUi::on_hsliderVolume_valueChanged(int value)
{
    m_player->setVolume(value);
    ui->labelPercent->setText(QString("%1%").arg(value));
}

void TimerUi::multiplierChanged(double multiplier)
{
    m_multiplier = multiplier;
    m_timer->setInterval(ui->hsliderPeriod->value() * 1000 / multiplier);
}

void TimerUi::start()
{
    // Check if the timer is alive. This is necessary if the main window broadcasts a "Start all" event
    if (!m_broken && ui->gboxTimer->isChecked())
    {
        // Temporize the timer
        QTimer::singleShot(ui->spinDelay->value() * 1000 / m_multiplier, this, &TimerUi::startAfterDelay);
        ui->buttonStart->setDisabled(true);
        ui->buttonStop->setEnabled(true);
    }
}

void TimerUi::stop()
{
    m_timer->stop();
    m_player->stop();
    ui->buttonStart->setEnabled(true);
    ui->buttonStop->setDisabled(true);
}

void TimerUi::startAfterDelay()
{
    m_player->play();
    m_timer->start();

    // Setup a termination if requested
    if (ui->groupTerminate->checkedId() == TERMINATE_ON_TRIGGER_COUNT)
    {
        if (ui->spinTerminateTriggers->value() == 0)
        {
            m_triggers = -1;
        }
        else
        {
            m_triggers = ui->spinTerminateTriggers->value();
        }
    }
    else // TERMINATE_ON_TIME_ELAPSED
    {
        if (ui->spinTerminateSeconds->value() == 0)
        {
            m_triggers = -1;
        }
        else
        {
            m_triggers = ui->spinTerminateSeconds->value() / ui->hsliderPeriod->value();
        }
    }
}

void TimerUi::playMedia()
{
    m_player->stop();
    m_player->play();

    if (m_triggers == -1)
    {
        return;
    }
    if (m_triggers == 0)
    {
        stop();
    }
    --m_triggers;
}

// Trigerred by the player in case of error
void TimerUi::error(QMediaPlayer::Error)
{
    ui->buttonStop->setDisabled(true);
    ui->labelBroken->setText(QString("The media is broken : %1").arg(m_player->errorString()));
    m_timer->stop();
    m_broken = true;
}

void TimerUi::on_spinDelay_valueChanged(int delay)
{
    int max = ui->hsliderPeriod->value();
    if (delay > max)
    {
        ui->spinDelay->setValue(max);
    }
}

void TimerUi::on_gboxTimer_toggled(bool checked)
{
    if (!checked)
    {
        m_timer->stop();
        m_player->stop();
    }
}
