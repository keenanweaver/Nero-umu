cmake_minimum_required(VERSION 3.16)

project(Nero-Launcher VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES Nero-Launcher_en_US.ts)

set(PROJECT_SOURCES
        main.cpp
        neromanager.cpp
        neromanager.h
        neromanager.ui
        nerorunner.cpp
        nerorunner.h
        nerofs.cpp
        nerofs.h
        nerotricks.cpp
        nerotricks.h
        nerotricks.ui
        nerowizard.cpp
        nerowizard.h
        nerowizard.ui
        neroshortcut.cpp
        neroshortcut.h
        neroshortcut.ui
        neroico.cpp
        neroico.h
        neropreferences.h
        neropreferences.cpp
        neropreferences.ui
        neroprefixsettings.h
        neroprefixsettings.cpp
        neroprefixsettings.ui
        neroconstants.h
        neroconstants.cpp
        nerodrives.h
        nerodrives.cpp
        nerodrives.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(QuaZip-Qt6)
    qt_add_executable(nero-launcher
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    find_package(QuaZip-Qt5)
    add_executable(nero-launcher
        ${PROJECT_SOURCES}
        pics.qrc
        nerorunnerdialog.h nerorunnerdialog.cpp nerorunnerdialog.ui
    )
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(nero-launcher PRIVATE Qt${QT_VERSION_MAJOR}::Widgets QuaZip::QuaZip)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER xyz.ThatOneSeong.Nero)
endif()
set_target_properties(nero-launcher PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS nero-launcher
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(nero-launcher)
endif()
