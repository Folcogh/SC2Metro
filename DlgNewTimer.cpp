#include "DlgNewTimer.hpp"
#include "Timer.hpp"
#include <QVBoxLayout>
#include <QFormLayout>

DlgNewTimer::DlgNewTimer(QWidget* parent)
    : QDialog(parent)
{
    /*
     * Create the user interface
     *
     */

    // Build the form layout which contains input widgets
    this->builtinList = new QComboBox;
    this->period = new QSpinBox;
    this->editHotkey = new QKeySequenceEdit; // TODO: replace with custom input widget

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow(tr("Sound file:"), this->builtinList);
    formLayout->addRow(tr("Period:"), this->period);
    formLayout->addRow(tr("Hotkey"), this->editHotkey); // TODO: replace with custom input widget

    // The label displayed if an hotkey is invalid. It's red, an invisible by default
    this->labelInvalidHotkey = new QLabel(tr("Invalid hotkey"));

    this->paletteInvalidHotkey = new QPalette;
    paletteInvalidHotkey->setColor(QPalette::Text, Qt::red);
    this->labelInvalidHotkey->setPalette(*this->paletteInvalidHotkey);

    // OK/Cancel buttons
    this->buttons = new QDialogButtonBox(QDialogButtonBox::Ok |
                                         QDialogButtonBox::Cancel);

    // Input parameters
    this->period->setRange(PERIOD_MIN, PERIOD_MAX);
    this->period->setAlignment(Qt::AlignHCenter);

    // Finalize the ui setup by placing the elements and adjusting their size
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(this->labelInvalidHotkey);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(this->buttons);
    this->setLayout(mainLayout);
    this->adjustSize();

    // Connections
    connect(this->buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(this->period, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &DlgNewTimer::periodChanged);

    // Trigger the slots to update the ui according to its current content
    periodChanged(this->period->value());
}

DlgNewTimer::~DlgNewTimer()
{
    delete this->paletteInvalidHotkey;
}

QString DlgNewTimer::getSoundName() const
{
    return this->builtinList->currentText();
}

int DlgNewTimer::getPeriod() const
{
    return this->period->value();
}

QKeyEvent DlgNewTimer::getHotKey() const
{

}

void DlgNewTimer::periodChanged(int newPeriod)
{
    if (newPeriod == 1) {
        this->period->setSuffix(tr(" second"));
    }
    else {
        this->period->setSuffix(tr(" seconds"));
    }
}
