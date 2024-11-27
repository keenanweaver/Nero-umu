/*  Nero Launcher: A very basic Bottles-like manager using UMU.
    Icon extraction and creation.

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

#ifndef NEROICO_H
#define NEROICO_H

#include <QString>
#include <QDir>

class NeroIcoExtractor
{
public:
    static QString GetIcon(QString sourceFile);
    static void CheckIcoCache(QDir cache) { if(!cache.exists(".icoCache")) { cache.mkdir(".icoCache"); } }
};

#endif // NEROICO_H
