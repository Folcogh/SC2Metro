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

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QDir>
#include <QFileInfo>
#include <QComboBox>
#include <QTabWidget>
#include <QPushButton>
#include <QFileDialog>
#include "AboutUi.hpp"
#include "TimerUi.hpp"
#include "LicenseUi.hpp"
#include "TimerComponent.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumWidth(350);

    // Create the list of speeds, which contains the multiplier as QVariant
    ui->comboSpeed->addItem("Slower", SPEED_SLOWER_MULTIPLIER);
    ui->comboSpeed->addItem("Slow", SPEED_SLOW_MULTIPLIER);
    ui->comboSpeed->addItem("Normal", SPEED_NORMAL_MULTIPLIER);
    ui->comboSpeed->addItem("Fast", SPEED_FAST_MULTIPLIER);
    ui->comboSpeed->addItem("Faster", SPEED_FASTER_MULTIPLIER);

    // Default game speed : standard 1v1
    ui->comboSpeed->setCurrentIndex(GAME_SPEED_FASTER);

    // Create the timer components
    TimerComponent* CreepComponent = new TimerComponent(this, "Creep", "qrc:/Sounds/creep.mp3", CREEP_PERIOD, false);
    TimerComponent* InjectComponent =
        new TimerComponent(this, "Inject", "qrc:/Sounds/inject.mp3", INJECT_PERIOD, false);
    TimerComponent* MinimapComponent =
        new TimerComponent(this, "Minimap", "qrc:/Sounds/minimap.mp3", MINIMAP_PERIOD, false);
    TimerComponent* WorkerComponent =
        new TimerComponent(this, "Worker", "qrc:/Sounds/worker.mp3", WORKER_PERIOD, false);
    TimerComponent* CustomComponent = new TimerComponent(this, "<Custom...>", "", CUSTOM_PERIOD, true);

    // Add the name of the timer componennts to the sound list
    ui->comboSound->addItem(CreepComponent->name(), QVariant::fromValue(CreepComponent));
    ui->comboSound->addItem(InjectComponent->name(), QVariant::fromValue(InjectComponent));
    ui->comboSound->addItem(MinimapComponent->name(), QVariant::fromValue(MinimapComponent));
    ui->comboSound->addItem(WorkerComponent->name(), QVariant::fromValue(WorkerComponent));
    ui->comboSound->addItem(CustomComponent->name(), QVariant::fromValue(CustomComponent));

    // Establish the connections
    connect(ui->tabs, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(ui->buttonAboutQt, &QPushButton::clicked, qApp, &QApplication::aboutQt);
    connect(ui->buttonLicense, &QPushButton::clicked, &LicenseUi::display);
    connect(ui->buttonAbout, &QPushButton::clicked, &AboutUi::display);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Enable the create button if the name is not null
void MainWindow::on_editName_textChanged(const QString& text)
{
    ui->buttonCreate->setDisabled(text.isEmpty());
}

// Signal emitted when the game speed is changed. The timers listen to this signal
void MainWindow::on_comboSpeed_currentIndexChanged(int index)
{
    emit speedChanged(ui->comboSpeed->itemData(index).value<double>());
}

// Modify the period
void MainWindow::on_hsliderPeriod_valueChanged(int value)
{
    ui->labelSeconds->setText(QString("%1 seconds").arg(value));
}

// Create a new timer
void MainWindow::on_buttonCreate_clicked()
{
    // Get user data of the sound and speed combos
    int soundindex = ui->comboSound->currentIndex();
    TimerComponent* tc = ui->comboSound->itemData(soundindex).value<TimerComponent*>();

    int speedindex = ui->comboSpeed->currentIndex();
    double multiplier = ui->comboSpeed->itemData(speedindex).value<double>();

    // Create the timer ui and add it to the app
    TimerUi* tu = new TimerUi(tc->fullfilename(), ui->hsliderPeriod->value(), multiplier);
    ui->tabs->addTab(tu, ui->editName->text());
    ui->tabs->setCurrentWidget(tu);

    // Connect the timer to the main ui
    connect(this, &MainWindow::speedChanged, tu, &TimerUi::multiplierChanged);
    connect(ui->buttonStartAllTimers, &QPushButton::clicked, tu, &TimerUi::start);
    connect(ui->buttonStopAllTimers, &QPushButton::clicked, tu, &TimerUi::stop);

    // Enable Start all/Stop all buttons
    ui->buttonStartAllTimers->setEnabled(true);
    ui->buttonStopAllTimers->setEnabled(true);
}

// Used to set up the ui when the initial index is set on the ctor,
// and to fallback to an existing one when a custom file selection is cancelled
void MainWindow::on_comboSound_currentIndexChanged(int index)
{
    TimerComponent* tc = ui->comboSound->itemData(index).value<TimerComponent*>();
    if (tc->custom())
    {
        // Custom timer -> query the sound file
        QString filename =
            QFileDialog::getOpenFileName(this, "Custom sound to play", QDir::homePath(), tr("Sounds (*.mp3 *.wav)"));
        if (filename.isEmpty())
        {
            ui->comboSound->setCurrentIndex(0);
            return;
        }
        tc->setFilename(filename);
    }
    ui->hsliderPeriod->setValue(tc->period());

    // Update the ui
    ui->labelSeconds->setText(QString("%1 seconds").arg(tc->period()));
    ui->labelSoundname->setText(QFileInfo(tc->fullfilename()).fileName());
}

// A tab requests to be closed
void MainWindow::closeTab(int index)
{
    // Don't close the start tab
    if (index != 0)
    {
        // Remove the current tab
        QWidget* widget = ui->tabs->widget(index);
        ui->tabs->removeTab(index);
        delete widget;

        // Allow/forbid to broadcast the Start all/Stop all event
        if (ui->tabs->count() == 1)
        {
            ui->buttonStartAllTimers->setDisabled(true);
            ui->buttonStopAllTimers->setDisabled(true);
        }
    }
}
