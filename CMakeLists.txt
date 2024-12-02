cmake_minimum_required(VERSION 3.16)

project(Nero-UMU VERSION 0.9 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES translations/Nero-Launcher_en_US.ts)

set(PROJECT_SOURCES
        src/main.cpp
        src/neromanager.cpp
        src/neromanager.h
        src/neromanager.ui
        src/nerorunner.cpp
        src/nerorunner.h
        src/nerofs.cpp
        src/nerofs.h
        src/nerotricks.cpp
        src/nerotricks.h
        src/nerotricks.ui
        src/nerowizard.cpp
        src/nerowizard.h
        src/nerowizard.ui
        src/neroshortcut.cpp
        src/neroshortcut.h
        src/neroshortcut.ui
        src/neroico.cpp
        src/neroico.h
        src/neropreferences.h
        src/neropreferences.cpp
        src/neropreferences.ui
        src/neroprefixsettings.h
        src/neroprefixsettings.cpp
        src/neroprefixsettings.ui
        src/neroconstants.h
        src/neroconstants.cpp
        src/nerodrives.h
        src/nerodrives.cpp
        src/nerodrives.ui
        src/nerorunnerdialog.h
        src/nerorunnerdialog.cpp
        src/nerorunnerdialog.ui
        src/neroonetimedialog.h
        src/neroonetimedialog.cpp
        src/neroonetimedialog.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(QuaZip-Qt6)
    qt_add_executable(nero-umu
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    find_package(QuaZip-Qt5)
    add_executable(nero-umu
        ${PROJECT_SOURCES}
        img/pics.qrc
    )
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(nero-umu PRIVATE Qt${QT_VERSION_MAJOR}::Widgets QuaZip::QuaZip)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER xyz.ThatOneSeong.Nero)
endif()
set_target_properties(nero-umu PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
)

include(GNUInstallDirs)
install(TARGETS nero-umu
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(nero-umu)
endif()
