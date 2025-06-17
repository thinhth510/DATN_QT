cmake_minimum_required(VERSION 3.16)

project(MockProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "/home/d1fficult/Qt/6.9.0")
find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Multimedia
    MultimediaWidgets
    SerialPort
)

set(PROJECT_SOURCES
    main.cpp

    # View sources
    view/mainwindow.cpp
    view/videoview.cpp
    view/audioview.cpp
    view/playlistview.cpp
    view/virtualkeyboard.cpp

    # Controller sources
    controller/mediacontroller.cpp
    controller/uartcontroller.cpp

    # Model sources
    model/mediafile.cpp
    model/playlist.cpp
    model/uartreceiver.cpp
    model/usbscanner.cpp

    # View headers
    view/mainwindow.h
    view/videoview.h
    view/audioview.h
    view/playlistview.h
    view/virtualkeyboard.h

    # Controller headers
    controller/mediacontroller.h
    controller/uartcontroller.h

    # Model headers
    model/mediafile.h
    model/playlist.h
    model/uartreceiver.h
    model/usbscanner.h

    # UI files
    view/mainwindow.ui
    view/videoview.ui
    view/audioview.ui
    view/playlistview.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MockProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(MockProject SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(MockProject
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(MockProject PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(MockProject PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
    Qt${QT_VERSION_MAJOR}::SerialPort
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MockProject)
endif()

set_target_properties(MockProject PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MockProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MockProject)
endif()
