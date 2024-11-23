/*  Nero Launcher: A very basic Bottles-like manager using UMU.
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

#include "neromanager.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Nero-Launcher_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    printf("Arguments count: %d\nArguments: \"%s\"\n", argc, *argv);
    if(argc > 1) {
        // TODO: if arguments are used, only invoke the launcher process;
        //       else, start the manager.
        printf("Additional arguments detected!\n");

        QStringList arguments;

        for(uint8_t i = 2; i <= argc; i++) {
            arguments.append(argv[i]);
        }

        if(arguments.indexOf("-v") != -1) {
            //mainApp.verbosity = true;
            printf("Enabling verbose output!\n");
            arguments.removeAt(arguments.indexOf("-v"));
        }

        // TODO: replace with executing launcher window using the arguments provided.
        a.exit();
        //return a.exec();
    } else {
        NeroManagerWindow w;
        w.show();
        return a.exec();
    }
}
