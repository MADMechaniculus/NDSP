cmake_minimum_required(VERSION 3.5)

project(wavelet_experiments VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_subdirectory(${PROJECT_SOURCE_DIR}/QCustomPlot)

set(PROJECT_SOURCES
        main.cpp
        waveletmainwindow.cpp
        waveletmainwindow.h
        waveletmainwindow.ui

        visualuzerwindow.h
        visualuzerwindow.cpp
        visualuzerwindow.ui

        waveformopeningdialog.h
        waveformopeningdialog.cpp
        waveformopeningdialog.ui

        resources.qrc

        dsp.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(wavelet_experiments
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET wavelet_experiments APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(wavelet_experiments SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(wavelet_experiments
            ${PROJECT_SOURCES}
        )
    endif()
endif()

add_dependencies(wavelet_experiments QCustomPlot)

target_link_libraries(wavelet_experiments PRIVATE Qt${QT_VERSION_MAJOR}::Widgets QCustomPlot)

set_target_properties(wavelet_experiments PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(wavelet_experiments)
endif()
