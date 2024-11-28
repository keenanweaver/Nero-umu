/*  Nero Launcher: A very basic Bottles-like manager using UMU.
    Manager Runner progress dialog.

    Copyright (C) 2024  That One Seong

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "nerorunnerdialog.h"
#include "ui_nerorunnerdialog.h"

NeroRunnerDialog::NeroRunnerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NeroRunnerDialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint, true);
}

NeroRunnerDialog::~NeroRunnerDialog()
{
    delete ui;
}

void NeroRunnerDialog::SetupWindow(const bool &isStarting,
                                   const QString &name,
                                   QIcon *icon)
{
    if(isStarting) {
        ui->header->setText("Starting " + name);
        ui->statusText->setText("Setting up umu environment...");

        if(icon != nullptr) {
            if(icon->actualSize(QSize(64,64)).height() < 64)
                ui->icoLabel->setPixmap(icon->pixmap(icon->actualSize(QSize(64,64))).scaled(64,64,Qt::KeepAspectRatio,Qt::SmoothTransformation));
            else ui->icoLabel->setPixmap(icon->pixmap(64,64));
        } else ui->icoLabel->setPixmap(QIcon::fromTheme("application-x-executable").pixmap(64,64));
    } else {
        ui->header->setText("Stopping " + name);
        ui->statusText->setText("Stopping umu...");

        if(icon != nullptr) {
            if(icon->actualSize(QSize(64,64)).height() < 64)
                ui->icoLabel->setPixmap(icon->pixmap(icon->actualSize(QSize(64,64))).scaled(64,64,Qt::KeepAspectRatio,Qt::SmoothTransformation));
            else ui->icoLabel->setPixmap(icon->pixmap(64,64));
        } else ui->icoLabel->setPixmap(QIcon::fromTheme("media-playback-stop").pixmap(64,64));
    }
}

void NeroRunnerDialog::SetText(const QString &text)
{
    ui->statusText->setText(text);
}
