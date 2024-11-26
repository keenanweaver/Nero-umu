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
    } else {
        ui->header->setText("Stopping " + name);
        ui->statusText->setText("Stopping umu...");
    }

    if(icon != nullptr) {
        if(icon->actualSize(QSize(64,64)).height() < 64)
            ui->icoLabel->setPixmap(icon->pixmap(icon->actualSize(QSize(64,64))).scaled(64,64,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        else ui->icoLabel->setPixmap(icon->pixmap(64,64));
    } else ui->icoLabel->setPixmap(QIcon::fromTheme("application-x-executable").pixmap(64,64));
}

void NeroRunnerDialog::SetText(const QString &text)
{
    ui->statusText->setText(text);
}
