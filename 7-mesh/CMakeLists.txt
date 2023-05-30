cmake_minimum_required(VERSION 3.5)

project(7-mesh VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        camera.h
        camera.cpp
        settings.h
        settings.cpp
        shaderwrapper.h
        shaderwrapper.cpp
        vectorselector.h
        vectorselector.cpp
        selectcolor.cpp
        selectcolor.h

        meshobjfile.h
        meshobjfile.cpp

        objstorage.h
        objstorage.cpp
        objentry.h
        objentry.cpp

        mtlentry.h
        mtlentry.cpp
        mtlstorage.h
        mtlstorage.cpp

        shaders/frag.fsh
        shaders/directional.vsh
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(7-mesh
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 7-mesh APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(7-mesh SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(7-mesh
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(7-mesh PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(7-mesh PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS 7-mesh
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(7-mesh)
endif()
