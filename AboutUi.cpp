#include "AboutUi.hpp"
#include "ui_AboutUi.h"

AboutUi::AboutUi(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::AboutUi)
{
    ui->setupUi(this);
    connect(ui->buttonClose, &QPushButton::clicked, this, &QDialog::close);
}

AboutUi::~AboutUi()
{
    delete ui;
}

void AboutUi::display()
{
    AboutUi about;
    about.exec();
}

QSize AboutUi::sizeHint() const
{
    return QSize(800, 900);
}
