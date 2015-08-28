#include "UiEditCyclicTimer.hpp"
#include "MainWindow.hpp"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QChar>

UiEditCyclicTimer::UiEditCyclicTimer(CyclicTimerSpec* spec)
    :QDialog(MainWindow::get())
    , Collapsed(false)
{
    /***********************************************************
     *
     *          ESSENTIAL BOX
     *
     ***********************************************************/

    // Box
    QGroupBox* EssentialBox = new QGroupBox(tr("Essentials"));
    QFormLayout* EssentialLayout = new QFormLayout(EssentialBox);

    // Sounds combo
    ComboSound = new QComboBox;
    EssentialLayout->addRow(tr("Sound:"), ComboSound);

    // Period slider
    SliderPeriod = new QSlider(Qt::Horizontal);
    LabelPeriod = new QLabel;
    QHBoxLayout* PeriodLayout = new QHBoxLayout;
    PeriodLayout->addWidget(SliderPeriod);
    PeriodLayout->addWidget(LabelPeriod);
    EssentialLayout->addRow(tr("Period:"), PeriodLayout);

    /***********************************************************
     *
     *          ADVANCED BOX
     *
     ***********************************************************/

    // Box
    AdvancedBox = new QGroupBox(tr("Advanced settings"));
    QFormLayout* AdvancedLayout = new QFormLayout(AdvancedBox);

    // Start slider
    SliderStart = new QSlider(Qt::Horizontal);
    LabelStart = new QLabel;
    QHBoxLayout* StartLayout = new QHBoxLayout;
    StartLayout->addWidget(SliderStart);
    StartLayout->addWidget(LabelStart);
    AdvancedLayout->addRow(tr("Start at:"), StartLayout);

    // Terminate slider
    SliderTerminate = new QSlider(Qt::Horizontal);
    LabelTerminate = new QLabel;
    QHBoxLayout* TerminateLayout = new QHBoxLayout;
    TerminateLayout->addWidget(SliderTerminate);
    TerminateLayout->addWidget(LabelTerminate);
    AdvancedLayout->addRow(tr("Terminate at:"), TerminateLayout);

    // Volume slider
    SliderVolume = new QSlider(Qt::Horizontal);
    LabelVolume = new QLabel;
    QHBoxLayout* VolumeLayout = new QHBoxLayout;
    VolumeLayout->addWidget(SliderVolume);
    VolumeLayout->addWidget(LabelVolume);
    AdvancedLayout->addRow(tr("Volume:"), VolumeLayout);

    // Hotkey edit
    EditKeySequence = new QKeySequenceEdit;
    ButtonClear = new QPushButton(tr("Clear"));
    QHBoxLayout* HotkeyLayout = new QHBoxLayout;
    HotkeyLayout->addWidget(EditKeySequence);
    HotkeyLayout->addWidget(ButtonClear);
    AdvancedLayout->addRow(tr("Synchronization hotkey:"), HotkeyLayout);

    // Buttons
    QPushButton* ButtonOk = new QPushButton(tr("OK"));
    QPushButton* ButtonCancel = new QPushButton(tr("Cancel"));
    ButtonMore = new QPushButton(tr(BUTTON_MORE_TEXT));
    QHBoxLayout* ButtonHLayout = new QHBoxLayout;
    ButtonHLayout->addWidget(ButtonOk);
    ButtonHLayout->addWidget(ButtonCancel);
    ButtonHLayout->addWidget(ButtonMore);

    /***********************************************************
     *
     *          Dialog layout
     *
     ***********************************************************/

    QVBoxLayout* MainLayout =new QVBoxLayout(this);
    MainLayout->addWidget(EssentialBox);
    MainLayout->addWidget(AdvancedBox);
    MainLayout->addLayout(ButtonHLayout);

    /***********************************************************
     *
     *          Connexions
     *
     ***********************************************************/

    connect(ButtonOk, &QPushButton::clicked, this, &QDialog::accept);
    connect(ButtonCancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(ButtonMore, &QPushButton::clicked, this, &UiEditCyclicTimer::buttonMoreClicked);
    connect(ButtonClear, &QPushButton::clicked, EditKeySequence, &QKeySequenceEdit::clear);
    connect(SliderPeriod, &QSlider::valueChanged, this, &UiEditCyclicTimer::adjustPeriodLabel);
    connect(SliderStart, &QSlider::valueChanged, this, &UiEditCyclicTimer::adjustStartLabel);
    connect(SliderTerminate, &QSlider::valueChanged, this, &UiEditCyclicTimer::adjustTerminateLabel);
    connect(SliderVolume, &QSlider::valueChanged, this, &UiEditCyclicTimer::adjustVolumeLabel);
    connect(SliderStart, &QSlider::sliderReleased, this, &UiEditCyclicTimer::checkStart);
    connect(SliderTerminate, &QSlider::sliderReleased, this, &UiEditCyclicTimer::checkTerminate);

    /***********************************************************
     *
     *          Settings
     *
     ***********************************************************/

    // Period
    SliderPeriod->setMinimum(spec->periodMin());
    SliderPeriod->setMaximum(spec->periodMax());
    SliderPeriod->setValue(spec->defaultPeriod());
    SliderPeriod->setSingleStep(spec->periodStep());
    SliderPeriod->setPageStep(spec->periodPageStep());

    // Start
    SliderStart->setMinimum(spec->boundMin());
    SliderStart->setMaximum(spec->boundMax());
    SliderStart->setValue(spec->defaultStart());
    SliderStart->setSingleStep(spec->boundStep());
    SliderStart->setPageStep(spec->boundPageStep());

    // Terminate
    SliderTerminate->setMinimum(spec->boundMin());
    SliderTerminate->setMaximum(spec->boundMax());
    SliderTerminate->setValue(spec->defaultTerminate());
    SliderTerminate->setSingleStep(spec->boundStep());
    SliderTerminate->setPageStep(spec->boundPageStep());

    // Volume
    SliderVolume->setMinimum(spec->volumeMin());
    SliderVolume->setMaximum(spec->volumeMax());
    SliderVolume->setValue(spec->defaultVolume());
    SliderVolume->setSingleStep(spec->volumeStep());
    SliderVolume->setPageStep(spec->volumePageStep());

    // Dialog
    AdvancedBox->setVisible(false);
    adjustSize();
    setWindowTitle(tr("New cyclic timer"));

}

UiEditCyclicTimer::~UiEditCyclicTimer()
{
}

CyclicTimerData* UiEditCyclicTimer::newCyclicTimer(CyclicTimerSpec* spec)
{
    CyclicTimerData* data = nullptr;
    UiEditCyclicTimer ct(spec);
    if (ct.exec() == QDialog::Accepted) {
        data = new CyclicTimerData(ct.SliderPeriod->value(), ct.SliderStart->value(), ct.SliderTerminate->value(),
                                   ct.SliderVolume->value(), ct.ComboSound->currentText(), ct.EditKeySequence->keySequence());
    }
    return data;
}

CyclicTimerData* UiEditCyclicTimer::editCyclictimer(CyclicTimerSpec* spec)
{
    (void) spec;
    return nullptr;
}

void UiEditCyclicTimer::buttonMoreClicked()
{
    if (Collapsed) {
        ButtonMore->setText(tr(BUTTON_MORE_TEXT));
        AdvancedBox->setVisible(false);
    }
    else {
        ButtonMore->setText(tr("Less..."));
        AdvancedBox->setVisible(true);
    }
    adjustSize();
    Collapsed = !Collapsed;
}

void UiEditCyclicTimer::adjustPeriodLabel(int seconds)
{
    LabelPeriod->setText(QString("%1:%2").arg(seconds / 60, 2, 10, QChar('0')).arg(seconds % 60, 2, 10, QChar('0')));
}

void UiEditCyclicTimer::adjustStartLabel(int seconds)
{
    LabelStart->setText(QString("%1:%2").arg(seconds / 60, 2, 10, QChar('0')).arg(seconds % 60, 2, 10, QChar('0')));
}

void UiEditCyclicTimer::adjustTerminateLabel(int seconds)
{
    QString label = QString("%1:%2").arg(seconds / 60, 2, 10, QChar('0')).arg(seconds % 60, 2, 10, QChar('0'));
    if (seconds == 0) {
        label.append((" (never terminate)"));
    }
    LabelTerminate->setText(label);
}

void UiEditCyclicTimer::adjustVolumeLabel(int percent)
{
    LabelVolume->setText(QString("%1%").arg(percent));
}

void UiEditCyclicTimer::checkStart()
{
    if ((SliderStart->value() > SliderTerminate->value()) && (SliderTerminate->value() != 0)) {
        SliderStart->setValue(SliderTerminate->value());
    }
}

void UiEditCyclicTimer::checkTerminate()
{
    if ((SliderStart->value() > SliderTerminate->value()) && (SliderTerminate->value() != 0)) {
        SliderTerminate->setValue(SliderStart->value());
    }
}

