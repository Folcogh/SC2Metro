#include "EditGameName.hpp"
#include "ui_EditGameName.h"
#include "MainWindow.hpp"
#include <QPointer>

EditGameName::EditGameName(QString name)
    : QDialog(MainWindow::get())
    , ui(new Ui::EditGameName)
{
    ui->setupUi(this);
    ui->editName->setText(name);
    adjustButtonOK();
    setWindowTitle(tr("Edit game name"));
    adjustSize();

    connect(ui->editName, &QLineEdit::textEdited, this, &EditGameName::adjustButtonOK);
    connect(ui->buttonOK, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &QDialog::reject);
}

EditGameName::~EditGameName()
{
    delete ui;
}

void EditGameName::adjustButtonOK()
{
    if (ui->editName->text().isEmpty()) {
        ui->buttonOK->setDisabled(true);
    }
    else {
        ui->buttonOK->setEnabled(true);
    }
}

QString EditGameName::editGameName(QString name)
{
    QPointer<EditGameName> egn = new EditGameName(name);
    if (egn->exec() == QDialog::Accepted) {
        name = egn->ui->editName->text();
    }
    delete egn;
    return name;
}
