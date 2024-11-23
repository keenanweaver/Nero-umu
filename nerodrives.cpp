/*  Nero Launcher: A very basic Bottles-like manager using UMU.
    Prefix Virtual Drives Manager dialog.

    Copyright (C) 2024 That One Seong

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

#include "nerodrives.h"
#include "ui_nerodrives.h"
#include "nerofs.h"

#include <QDebug>

NeroVirtualDriveDialog::NeroVirtualDriveDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NeroVirtualDriveDialog)
{
    ui->setupUi(this);

    lineEditFont.setPointSize(8);
    mainLabelFont.setPointSize(10);

    prefixDir.setPath(QString("%1/%2/dosdevices").arg(NeroFS::GetPrefixesPath().path(), NeroFS::GetCurrentPrefix()));
    currentLinks = prefixDir.entryList(QDir::NoDotAndDotDot | QDir::Dirs, QDir::Name);
    //qDebug() << currentLinks;

    for(const QString &dir : currentLinks) {
        QFileInfo parser(QString("%1/%2").arg(prefixDir.path(), dir));
        if(parser.isDir())
            AddDir(parser.canonicalFilePath(), parser.fileName());
    }
}

NeroVirtualDriveDialog::~NeroVirtualDriveDialog()
{
    // TODO: commit labels upon object destruction

    delete ui;
}

void NeroVirtualDriveDialog::AddDir(const QString newPath, const QString letter)
{
    dirPath << new QLabel(QString("<b>%1/</b> <i>[%2]</i>").arg(letter.toUpper(), newPath));
    dirPath.last()->setFont(mainLabelFont);
    dirPath.last()->setProperty("letter", letter);

    QFile windowsLabel(QString("%1/.windows-label").arg(newPath));
    if(windowsLabel.exists()) {
        windowsLabel.open(QIODevice::ReadWrite);
        dirWinLabel << new QLineEdit(windowsLabel.readLine().trimmed());
    } else dirWinLabel << new QLineEdit();
    dirWinLabel.last()->setFont(lineEditFont);
    dirWinLabel.last()->setFrame(false);
    dirWinLabel.last()->setMaxLength(16);
    dirWinLabel.last()->setStyleSheet("background-color: transparent");
    dirWinLabel.last()->setProperty("slot", dirWinLabel.size()-1);
    connect(dirWinLabel.last(), SIGNAL(textEdited(QString)), this, SLOT(winLabel_textEdited(QString)));

    dirChange << new QPushButton(QIcon::fromTheme("document-open"), "");
    dirChange.last()->setIconSize(QSize(24,24));
    dirChange.last()->setProperty("slot", dirChange.size()-1);
    connect(dirChange.last(), SIGNAL(clicked()), this, SLOT(changeBtn_clicked()));

    dirDelete << new QPushButton(QIcon::fromTheme("edit-delete"),"");
    dirDelete.last()->setIconSize(QSize(24,24));
    dirDelete.last()->setFlat(true);
    dirDelete.last()->setProperty("slot", dirDelete.size()-1);
    connect(dirDelete.last(), SIGNAL(clicked()), this, SLOT(deleteBtn_clicked()));

    dirLabelsLayout << new QVBoxLayout;

    dirLabelsLayout.last()->addWidget(dirPath.last());
    dirLabelsLayout.last()->addWidget(dirWinLabel.last());
    dirLabelsLayout.last()->setStretch(0,1);

    dirLine << new QHBoxLayout;
    dirLine.last()->addWidget(dirChange.last());
    dirLine.last()->addLayout(dirLabelsLayout.last());
    dirLine.last()->addWidget(dirDelete.last());
    dirLine.last()->setStretch(1,1);

    ui->dirsList->addLayout(dirLine.last());
    if(letter == "c:") {
        dirPath.last()->setEnabled(false);
        dirWinLabel.last()->setEnabled(false);
        dirChange.last()->setEnabled(false);
        dirDelete.last()->setEnabled(false);
        dirLabelsLayout.last()->setEnabled(false);
        dirLine.last()->setEnabled(false);
    }
}

void NeroVirtualDriveDialog::on_addDirBtn_clicked()
{
    // TODO: symlinks aren't sym'ing. :<
    externalDir.setPath(QFileDialog::getExistingDirectory(this,
                                                          "Select a directory",
                                                          qEnvironmentVariable("HOME")));
    if(!externalDir.path().isEmpty()) {
        QFile newLink(externalDir.path());
        char letter = 'a';
        for(int i = 0; i < 26; i++) {
            if(!newLink.exists(QString("%1:").arg(letter+i))) {
                if(newLink.link(externalDir.canonicalPath(), QString("%1:").arg(letter+i))) {
                    letter += i;
                    break;
                }
            }
        }
        AddDir(externalDir.canonicalPath(), QString("%1:").arg(letter));
    }
}

void NeroVirtualDriveDialog::deleteBtn_clicked()
{
    int slot = sender()->property("slot").toInt();
    QDir dirToDel(prefixDir.path());
    if(dirToDel.remove(sender()->property("letter").toString())) {
        delete dirPath.at(slot);
        delete dirWinLabel.at(slot);
        delete dirChange.at(slot);
        delete dirDelete.at(slot);
        delete dirLabelsLayout.at(slot);
        delete dirLine.at(slot);
    }
}

void NeroVirtualDriveDialog::changeBtn_clicked()
{
    int slot = sender()->property("slot").toInt();
    externalDir.setPath(QFileDialog::getExistingDirectory(this,
                                                          "Select a directory",
                                                          qEnvironmentVariable("HOME")));
    if(!externalDir.path().isEmpty()) {
        QFile newLink(prefixDir.path());
        if(newLink.remove(dirPath.at(slot)->property("letter").toString())) {
            newLink.link(externalDir.canonicalPath(), dirPath.at(slot)->property("letter").toString());
            dirPath.at(slot)->setText(QString("<b>%1/</b> <i>[%2]</i>").arg(dirPath.at(slot)->property("letter").toString().toUpper(), externalDir.canonicalPath()));
        }
    }
}

void NeroVirtualDriveDialog::winLabel_textEdited(const QString arg1)
{
    int slot = sender()->property("slot").toInt();

    dirWinLabel.at(slot)->setText(arg1.toUpper().trimmed());
}
