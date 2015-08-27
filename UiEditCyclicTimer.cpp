#include "UiEditCyclicTimer.hpp"
#include "MainWindow.hpp"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QBoxLayout>

UiEditCyclicTimer::UiEditCyclicTimer()
    :QDialog(MainWindow::get())
    , Collapsed(false)
{
    // Essential box
    ComboSound = new QComboBox;
    SliderPeriod = new QSlider(Qt::Horizontal);
    QGroupBox* EssentialBox = new QGroupBox(tr("Essentials"));
    QFormLayout* EssentialLayout = new QFormLayout(EssentialBox);
    EssentialLayout->addRow(tr("Sound:"), ComboSound);
    EssentialLayout->addRow(tr("Period:"), SliderPeriod);

    // Advanced box
    SliderStart = new QSlider(Qt::Horizontal);
    SliderTerminate = new QSlider(Qt::Horizontal);
    SliderVolume = new QSlider(Qt::Horizontal);
    EditKeySequence = new QKeySequenceEdit;
    AdvancedBox = new QGroupBox(tr("Advanced settings"));
    QFormLayout* AdvancedLayout = new QFormLayout(AdvancedBox);
    AdvancedLayout->addRow(tr("Start at:"), SliderStart);
    AdvancedLayout->addRow(tr("Terminate at:"), SliderTerminate);
    AdvancedLayout->addRow(tr("Volume:"), SliderVolume);
    AdvancedLayout->addRow(tr("Start/sync hotkey:"), EditKeySequence);

    // Buttons
    QPushButton* ButtonOk = new QPushButton(tr("OK"));
    QPushButton* ButtonCancel = new QPushButton(tr("Cancel"));
    ButtonMore = new QPushButton(tr(BUTTON_MORE_TEXT));
    QHBoxLayout* ButtonHLayout = new QHBoxLayout;
    ButtonHLayout->addWidget(ButtonOk);
    ButtonHLayout->addWidget(ButtonCancel);
    ButtonHLayout->addWidget(ButtonMore);

    // Settings
    AdvancedBox->setVisible(false);
    adjustSize();
    setWindowTitle("New cyclic timer");

    // Connexions
    connect(ButtonOk, &QPushButton::clicked, this, &QDialog::accept);
    connect(ButtonCancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(ButtonMore, &QPushButton::clicked, this, &UiEditCyclicTimer::buttonMoreClicked);
}

UiEditCyclicTimer::~UiEditCyclicTimer()
{
}

bool UiEditCyclicTimer::newCyclicTimer()
{
    UiEditCyclicTimer ct;
    return ct.exec() == QDialog::Accepted;
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
