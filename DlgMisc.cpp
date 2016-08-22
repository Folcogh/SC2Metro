#include "DlgMisc.hpp"
#include "ui_DlgMisc.h"
#include <QPointer>
#include <QPushButton>

DlgMisc::DlgMisc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgMisc)
{
    ui->setupUi(this);
    ui->tabs->setCurrentIndex(0);
    layout()->setAlignment(ui->buttonOk, Qt::AlignCenter);
    setMinimumSize(1024, 768);
    connect(ui->buttonOk, &QPushButton::clicked, this, &QDialog::accept);
}

DlgMisc::~DlgMisc()
{
    delete ui;
}

void DlgMisc::showDlgMisc(QWidget* parent)
{
    QPointer<DlgMisc> dlg = new DlgMisc(parent);
    dlg->exec();
    delete dlg;
}
