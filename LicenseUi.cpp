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

#include "LicenseUi.hpp"
#include "ui_LicenseUi.h"

LicenseUi::LicenseUi()
    : ui(new Ui::LicenseUi)
{
    ui->setupUi(this);
    setMinimumSize(600, 700);
    connect(ui->buttonClose, &QPushButton::clicked, this, &QDialog::close);
}

LicenseUi::~LicenseUi()
{
    delete ui;
}

void LicenseUi::display()
{
    LicenseUi license;
    license.exec();
}
