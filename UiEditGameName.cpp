#include "UiEditGameName.hpp"
#include "MainWindow.hpp"
#include <QPushButton>
#include <QFormLayout>
#include <QBoxLayout>
#include <QLabel>

/**
 * @brief Construct a dialog to request a new name
 */
UiEditGameName::UiEditGameName()
    : QDialog(MainWindow::get())
    , buttons(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel))
    , mainLayout(new QVBoxLayout)
    , nameEdit(new QLineEdit)
{
    // Input layout
    QFormLayout* nameLayout = new QFormLayout;

    // Draw ui
    nameLayout->addRow(tr("Game name:"), nameEdit);
    mainLayout->addLayout(nameLayout);
    mainLayout->addWidget(buttons);
    setLayout(mainLayout);

    // Dialog config
    adjustSize();
    setWindowTitle(tr("New game"));
    buttons->button(QDialogButtonBox::Ok)->setDisabled(true);

    // Connexions
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);             // Ok
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);             // Cancel
    connect(nameEdit, &QLineEdit::textChanged, this, &UiEditGameName::adjustButtonOk); // Disable the OK button if the name field is empty
}

/**
 * @brief Construct a dialog to edit an existing name
 * @param name Existing name
 */
UiEditGameName::UiEditGameName(QString name)
    : UiEditGameName()
{
    mainLayout->insertWidget(0, new QLabel(tr("Current name: %1").arg(name)));
    nameEdit->setText(name);
    adjustSize();
    setWindowTitle(tr("Edit game name"));
}

UiEditGameName::~UiEditGameName()
{
}

/**
 * @brief Prompt for a new game name
 * @return QString A string containing the name. The string is empty if the dialog was cancelled
 */
QString UiEditGameName::newGameName()
{
    UiEditGameName* ui = new UiEditGameName;
    QString retval = ui->commonEdit();
    delete ui;
    return retval;
}

/**
 * @brief Edit the current game name
 * @param name Current name
 * @return QString A string containing the new name. The string is empty if the dialog was cancelled
 */
QString UiEditGameName::editGameName(QString name)
{
    UiEditGameName* ui = new UiEditGameName(name);
    QString retval = ui->commonEdit();
    delete ui;
    return retval;
}

/**
 * @brief Common part of the static methods
 * @return QString A string containing the typed name. The string is empty if the dialog was cancelled
 */
QString UiEditGameName::commonEdit()
{
    QString retval;
    exec();
    if (result() == QDialog::Accepted) {
        retval = nameEdit->text();
    }
    return retval;
}

/**
 * @brief Disable the button OK if the input field is empty, else enable it
 * @param text content of the input field
 * @return void
 */
void UiEditGameName::adjustButtonOk(const QString& text)
{
    buttons->button(QDialogButtonBox::Ok)->setDisabled(text.isEmpty());
}
