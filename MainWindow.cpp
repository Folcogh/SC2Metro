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

#include "windows.h"
#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QDir>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QComboBox>
#include <QTabWidget>
#include <QDataStream>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include "TimerUi.hpp"
#include "ReadmeUi.hpp"
#include "Constants.hpp"
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

    // Set max timer value
    ui->hsliderPeriod->setMaximum(TIMER_MAX);

    // Create the timer components
    TimerComponent* CreepComponent = new TimerComponent(this, "Creep", "qrc:/Sounds/creep.mp3", CREEP_PERIOD, false);
    TimerComponent* InjectComponent = new TimerComponent(this, "Inject", "qrc:/Sounds/inject.mp3", INJECT_PERIOD, false);
    TimerComponent* MinimapComponent = new TimerComponent(this, "Minimap", "qrc:/Sounds/minimap.mp3", MINIMAP_PERIOD, false);
    TimerComponent* WorkerComponent = new TimerComponent(this, "Worker", "qrc:/Sounds/worker.mp3", WORKER_PERIOD, false);
    TimerComponent* MuleComponent = new TimerComponent(this, "Mule", "qrc:/Sounds/mule.mp3", MULE_PERIOD, false);
    TimerComponent* ResourceComponent = new TimerComponent(this, "Resource", "qrc:/Sounds/resource.mp3", RESOURCE_PERIOD, false);
    TimerComponent* ScoutComponent = new TimerComponent(this, "Scout", "qrc:/Sounds/scout.mp3", SCOUT_PERIOD, false);
    TimerComponent* SupplyComponent = new TimerComponent(this, "Supply", "qrc:/Sounds/supply.mp3", SUPPLY_PERIOD, false);
    TimerComponent* CustomComponent = new TimerComponent(this, "<Custom...>", "", CUSTOM_PERIOD, true);

    // Add the name of the timer componennts to the sound list
    ui->comboSound->addItem(CreepComponent->name(), QVariant::fromValue(CreepComponent));
    ui->comboSound->addItem(InjectComponent->name(), QVariant::fromValue(InjectComponent));
    ui->comboSound->addItem(MinimapComponent->name(), QVariant::fromValue(MinimapComponent));
    ui->comboSound->addItem(WorkerComponent->name(), QVariant::fromValue(WorkerComponent));
    ui->comboSound->addItem(MuleComponent->name(), QVariant::fromValue(MuleComponent));
    ui->comboSound->addItem(ResourceComponent->name(), QVariant::fromValue(ResourceComponent));
    ui->comboSound->addItem(ScoutComponent->name(), QVariant::fromValue(ScoutComponent));
    ui->comboSound->addItem(SupplyComponent->name(), QVariant::fromValue(SupplyComponent));
    ui->comboSound->addItem(CustomComponent->name(), QVariant::fromValue(CustomComponent));

    // Establish the connections
    connect(ui->tabs, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(ui->buttonAboutQt, &QPushButton::clicked, qApp, &QApplication::aboutQt);
    connect(ui->buttonLicense, &QPushButton::clicked, &LicenseUi::display);
    connect(ui->buttonAbout, &QPushButton::clicked, &AboutUi::display);

    // Trigger the activation callback to update the data of the current sound
    on_comboSound_activated(0);

    // Register an hotkey
//    if (!RegisterHotKey(NULL, 1, MOD_ALT | 0x4000, 0x42))
    if (!RegisterHotKey((HWND)winId(), 1, MOD_ALT | 0x4000, 0x42))
    {
        QMessageBox::critical(this, "Hotkey error", "Can't register hotkey, it won't work");
    }
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
    connect(ui->buttonStartAllTimers, &QPushButton::clicked, tu, &TimerUi::onStartAllEvent);
    connect(ui->buttonStopAllTimers, &QPushButton::clicked, tu, &TimerUi::stop);

    // Enable Start all/Stop all buttons
    ui->buttonStartAllTimers->setEnabled(true);
    ui->buttonStopAllTimers->setEnabled(true);
    ui->buttonSaveTimers->setEnabled(true);
}

// Used to set up the ui when the initial index is set on the ctor,
// and to fallback to an existing one when a custom file selection is cancelled
void MainWindow::on_comboSound_activated(int index)
{
    TimerComponent* tc = ui->comboSound->itemData(index).value<TimerComponent*>();
    if (tc->custom())
    {
        // Custom timer -> query the sound file
        QString filename = QFileDialog::getOpenFileName(this, "Custom sound to play", QDir::homePath(), tr("Sounds (*.mp3 *.wav)"));
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

        // Allow/forbid to broadcast the Start all/Stop all event and Save
        if (ui->tabs->count() == 1)
        {
            ui->buttonStartAllTimers->setDisabled(true);
            ui->buttonStopAllTimers->setDisabled(true);
            ui->buttonSaveTimers->setDisabled(true);
        }
    }
}

void MainWindow::on_buttonSaveTimers_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Select the file where the timers will be saved", QDir::homePath(), QString("FMetro timers file (*.%1)").arg(TIMERS_FILE_EXTENSION));
    if (filename.isNull())
    {
        return;
    }

    // Add the extension if necessary
    if (QFileInfo(filename).suffix() != TIMERS_FILE_EXTENSION)
    {
        filename += TIMERS_FILE_EXTENSION;
    }

    // Open the file
    QFile file(filename);
    QDataStream stream(&file);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, "Save error", QString("Failed to open the file %1").arg(filename));
        return;
    }

    // Write signature and version
    stream << QString(TIMERS_FILE_SIGNATURE) << int(TIMERS_FILE_VERSION);

    // Write the number of timers
    stream << ui->tabs->count() - 1;

    // Writes the timers
    for (int i = 1; i < ui->tabs->count(); i++)
    {
        stream << ui->tabs->tabText(i);                       // Write title
        stream << static_cast<TimerUi*>(ui->tabs->widget(i)); // Write content
    }

    // Check success
    if (stream.status() != QDataStream::Ok)
    {
        QMessageBox::critical(this, "Save error", QString("Failed to write to the file %1").arg(filename));
    }
}

void MainWindow::on_buttonOpenTimers_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select the file to open", QDir::homePath(), QString("FMetro timers file (*.%1)").arg(TIMERS_FILE_EXTENSION));
    if (filename.isNull())
    {
        return;
    }

    // Open the file
    QFile file(filename);
    QDataStream stream(&file);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Open error", QString("Failed to open the file %1").arg(filename));
        return;
    }

    // Check signature
    QString signature;
    stream >> signature;
    if (signature != QString(TIMERS_FILE_SIGNATURE))
    {
        QMessageBox::critical(this, "Open error", QString("File corrupted: %1").arg(filename));
        return;
    }

    // Check version
    int version;
    stream >> version;
    if (version > TIMERS_FILE_VERSION)
    {
        QMessageBox::critical(this, "Open error", QString("This version of FMetro is to old to open %1. Please update.").arg(filename));
        return;
    }

    // Read the number of timers
    int timercount;
    stream >> timercount;

    // Put all the timers in a list
    QList<QString> titles;
    QList<TimerUi*> timers;
    for (int i = 0; i < timercount; i++)
    {
        // Read title
        QString title;
        stream >> title;
        titles.append(title);

        // Read timer data
        TimerUi* timerui;
        stream >> timerui;
        timers.append(timerui);
    }

    // Check if the stream is alive
    if (stream.status() != QDataStream::Ok)
    {
        QMessageBox::critical(this, "Open error", QString("Error reading the file %1").arg(filename));
        return;
    }

    // All is fine, remove the current timers and add the new ones
    ui->tabs->setUpdatesEnabled(false);

    for (int i = 1; i < ui->tabs->count(); i++)
    {
        closeTab(i);
    }

    for (int i = 0; i < titles.count(); i++)
    {
        ui->tabs->addTab(timers[i], titles[i]);
        ui->buttonSaveTimers->setEnabled(true);
    }

    ui->tabs->setUpdatesEnabled(true);

    // Emit the "Speed changed" event to update the timers
    int index = ui->comboSpeed->currentIndex();
    emit speedChanged(ui->comboSpeed->itemData(index).value<double>());
}
