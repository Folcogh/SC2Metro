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

#include "Global.hpp"
#include "TimerUi.hpp"
#include "ui_TimerUi.h"
#include "Constants.hpp"
#include <QButtonGroup>
#include <QRadioButton>
#include <QDataStream>
#include <QSpinBox>

// Used by the file opening
TimerUi::TimerUi()
    : ui(new Ui::TimerUi)
    , m_timer(new QTimer(this))
    , m_player(new QMediaPlayer(this))
    , m_playlist(new QMediaPlaylist(this))
    , m_broken(false)
    , m_triggers(-1)
{
    ui->setupUi(this);
}

TimerUi::TimerUi(QString fullfilename, int period, double multiplier)
    : ui(new Ui::TimerUi)
    , m_timer(new QTimer(this))
    , m_multiplier(multiplier)
    , m_media(new QMediaContent(fullfilename))
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
    ui->labelSound->setText(fullfilename);
    ui->labelBroken->setText(QString());
    ui->spinDelay->setMaximum(TIMER_MAX);
    updateVolumeLabel();
    updatePeriodLabel();

    // ID of the radio buttons
    ui->groupTerminate->setId(ui->radioTerminateTriggers, TERMINATE_ON_TRIGGER_COUNT);
    ui->groupTerminate->setId(ui->radioTerminateSeconds, TERMINATE_ON_TIME_ELAPSED);

    // Setup the timer
    m_timer->setInterval(period * 1000 / multiplier);
    m_timer->setTimerType(Qt::PreciseTimer);

    // Setup the playlist
    m_playlist->addMedia(*m_media);
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

    // Setup the player
    m_player->setPlaylist(m_playlist);
    m_player->setVolume(INITIAL_VOLUME);

    // Establish connections
    connect(m_timer, &QTimer::timeout, this, &TimerUi::playMedia);
    connect(ui->buttonStart, &QPushButton::clicked, this, &TimerUi::start);
    connect(ui->buttonStop, &QPushButton::clicked, this, &TimerUi::stop);
    connect(ui->radioTerminateTriggers, &QRadioButton::toggled, ui->spinTerminateTriggers, &QSpinBox::setEnabled);
    connect(ui->radioTerminateSeconds, &QRadioButton::toggled, ui->spinTerminateSeconds, &QSpinBox::setEnabled);
    connect(m_player, (void (QMediaPlayer::*)(QMediaPlayer::Error)) & QMediaPlayer::error, this, &TimerUi::error);
    connect(native_event_filter, &NativeEventFilter::hotkeyPressed, this, &TimerUi::hotkeyTriggered);
}

TimerUi::~TimerUi()
{
    // Ensure that the running objets are stopped before deleting them. It should be useless
    m_player->stop();
    m_timer->stop();
    delete m_media;
    delete ui;
}

void TimerUi::on_hsliderPeriod_valueChanged(int value)
{
    m_timer->setInterval(value * 1000 / m_multiplier);
    updatePeriodLabel();
}

void TimerUi::on_hsliderVolume_valueChanged(int value)
{
    m_player->setVolume(value);
    updateVolumeLabel();
}

void TimerUi::multiplierChanged(double multiplier)
{
    m_multiplier = multiplier;
    m_timer->setInterval(ui->hsliderPeriod->value() * 1000 / multiplier);
}

void TimerUi::updateVolumeLabel()
{
    ui->labelVolume->setText(QString("Volume (%1%):").arg(ui->hsliderVolume->value()));
}

void TimerUi::updatePeriodLabel()
{
    ui->labelPeriod->setText(QString("Period (%1 seconds):").arg(ui->hsliderPeriod->value()));
}

void TimerUi::hotkeyTriggered()
{
    if (ui->checkSynchronize->isChecked())
    {
        stop();
        start();
    }
}

void TimerUi::start()
{
    // Check if the timer is alive. This is necessary if the main window broadcasts a "Start all" event
    if (!m_broken)
    {
        // Temporize the timer
        QTimer::singleShot(ui->spinDelay->value() * 1000 / m_multiplier, this, &TimerUi::startAfterDelay);
        ui->buttonStart->setDisabled(true);
        ui->buttonStop->setEnabled(true);
    }
}

void TimerUi::startAfterDelay()
{
    m_timer->start();
    if (ui->checkPlayOnStart->isChecked())
    {
        m_player->play();
    }

    // Setup a termination if requested
    m_triggers = -1;
    if (ui->groupTerminate->checkedId() == TERMINATE_ON_TRIGGER_COUNT && (ui->spinTerminateTriggers->value() != 0))
    {
        m_triggers = ui->spinTerminateTriggers->value();
    }
    else if (ui->spinTerminateSeconds->value() != 0) // TERMINATE_ON_TIME_ELAPSED
    {
        m_triggers = ui->spinTerminateSeconds->value() / ui->hsliderPeriod->value();
    }
}

void TimerUi::stop()
{
    m_timer->stop();
    m_player->stop();
    ui->buttonStart->setEnabled(true);
    ui->buttonStop->setDisabled(true);
}

void TimerUi::onStartAllEvent()
{
    if (ui->checkStartTimer->isChecked())
    {
        start();
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
    --m_triggers;
    if (m_triggers == 0)
    {
        m_timer->stop();
        ui->buttonStart->setEnabled(true);
        ui->buttonStop->setDisabled(true);;
    }
}

// Trigerred by the player in case of error
void TimerUi::error(QMediaPlayer::Error)
{
    ui->buttonStop->setDisabled(true);
    ui->labelBroken->setText(QString("The media is broken : %1").arg(m_player->errorString()));
    m_timer->stop();
    m_broken = true;
}

// Serialization
QDataStream& TimerUi::fromStream(QDataStream& stream)
{
    QString sound;
    int delay, period, volume, checkedId, triggers, seconds;
    bool play, start, synchro;
    stream >> sound >> delay >> play >> start >> synchro >> period >> volume >> checkedId >> triggers >> seconds;

    // ID of the radio buttons
    ui->groupTerminate->setId(ui->radioTerminateTriggers, TERMINATE_ON_TRIGGER_COUNT);
    ui->groupTerminate->setId(ui->radioTerminateSeconds, TERMINATE_ON_TIME_ELAPSED);

    // Setup the timer
    m_timer->setTimerType(Qt::PreciseTimer);

    // Setup the media
    m_media = new QMediaContent(sound);

    // Setup the playlist
    m_playlist->addMedia(*m_media);
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

    // Setup the player
    m_player->setPlaylist(m_playlist);

    // Create these connections now to set correctly the periods/seconds spinboxes
    connect(ui->radioTerminateTriggers, &QRadioButton::toggled, ui->spinTerminateTriggers, &QSpinBox::setEnabled);
    connect(ui->radioTerminateSeconds, &QRadioButton::toggled, ui->spinTerminateSeconds, &QSpinBox::setEnabled);

    // Set basic settings
    ui->hsliderPeriod->setMaximum(TIMER_MAX);
    ui->spinDelay->setMaximum(TIMER_MAX);
    ui->labelSound->setText(sound);
    ui->spinDelay->setValue(delay);
    ui->checkPlayOnStart->setChecked(play);
    ui->checkStartTimer->setChecked(start);
    ui->checkSynchronize->setChecked(synchro);
    ui->hsliderPeriod->setValue(period);
    ui->hsliderVolume->setValue(volume);
    ui->groupTerminate->button(checkedId)->setChecked(true);
    ui->spinTerminateTriggers->setValue(triggers);
    ui->spinTerminateSeconds->setValue(seconds);
    ui->labelBroken->setText(QString());
    updateVolumeLabel();
    updatePeriodLabel();

    // Establish other connections
    connect(m_timer, &QTimer::timeout, this, &TimerUi::playMedia);
    connect(ui->buttonStart, &QPushButton::clicked, this, &TimerUi::start);
    connect(ui->buttonStop, &QPushButton::clicked, this, &TimerUi::stop);
    connect(m_player, (void (QMediaPlayer::*)(QMediaPlayer::Error)) & QMediaPlayer::error, this, &TimerUi::error);

    return stream;
}

QDataStream& TimerUi::toStream(QDataStream& stream) const
{
    return stream << ui->labelSound->text() << ui->spinDelay->value() << ui->checkPlayOnStart->isChecked() << ui->checkStartTimer->isChecked() << ui->checkSynchronize->isChecked()
                  << ui->hsliderPeriod->value() << ui->hsliderVolume->value() << ui->groupTerminate->checkedId() << ui->spinTerminateTriggers->value() << ui->spinTerminateSeconds->value();
}

QDataStream& operator<<(QDataStream& stream, const TimerUi* timerui)
{
    return timerui->toStream(stream);
}

QDataStream& operator>>(QDataStream& stream, TimerUi*& timerui)
{
    timerui = new TimerUi;
    return timerui->fromStream(stream);
}
