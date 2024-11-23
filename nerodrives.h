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

#ifndef NERODRIVES_H
#define NERODRIVES_H

#include <QDialog>
#include <QDir>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>

namespace Ui {
class NeroVirtualDriveDialog;
}

class NeroVirtualDriveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NeroVirtualDriveDialog(QWidget *parent = nullptr);
    ~NeroVirtualDriveDialog();

private slots:
    void on_addDirBtn_clicked();

    void changeBtn_clicked();

    void deleteBtn_clicked();

    void winLabel_textEdited(const QString);

private:
    Ui::NeroVirtualDriveDialog *ui;

    void AddDir(const QString, const QString);

    QDir prefixDir;
    QDir externalDir;
    QFile fileWriter;

    QStringList currentLinks;

    QList<QLabel*> dirPath;
    QList<QLineEdit*> dirWinLabel;
    QList<QPushButton*> dirChange;
    QList<QPushButton*> dirDelete;
    QList<QHBoxLayout*> dirLine;
    QList<QVBoxLayout*> dirLabelsLayout;

    QFont lineEditFont;
    QFont mainLabelFont;
};

#endif // NERODRIVES_H
