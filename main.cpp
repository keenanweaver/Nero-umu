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
#include "nerofs.h"
#include "neroonetimedialog.h"
#include "nerorunner.h"

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

    if(argc > 1) {
        // TODO: if arguments are used, only invoke the launcher process;
        //       else, start the manager.
        printf("Additional arguments detected!\n");

        QStringList arguments;

        for(uint8_t i = 1; i < argc; i++)
            arguments.append(argv[i]);

        if(argc < 3 && (arguments.last().endsWith(".exe") || arguments.last().endsWith(".msi") || arguments.last().endsWith(".bat"))) {
            printf("Requested to open file!\n");

            if(NeroFS::InitPaths()) {
                NeroOneTimeDialog oneTimeDiag;
                oneTimeDiag.exec();
                if(!oneTimeDiag.selected.isEmpty()) {
                    NeroFS::SetCurrentPrefix(oneTimeDiag.selected);
                    NeroRunner runner;
                    runner.StartOnetime(arguments.last(), {});
                } else printf("No prefix selected! Aborting...\n");
            } else {
                printf("Nero cannot run without a home directory set! Aborting...\n");
                a.exit(1);
            }
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
