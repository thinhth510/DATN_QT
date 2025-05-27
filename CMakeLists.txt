cmake_minimum_required(VERSION 3.16)

project(VS_MockProject VERSION 0.1 LANGUAGES CXX)

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
    src/main.cpp

    # View sources
    src/view/mainwindow.cpp
    src/view/videoview.cpp
    src/view/audioview.cpp
    src/view/playlistview.cpp

    # Controller sources
    src/controller/mediacontroller.cpp
    src/controller/uartcontroller.cpp

    # Model sources
    src/model/mediafile.cpp
    src/model/playlist.cpp
    src/model/uartreceiver.cpp

    # View headers
    include/view/mainwindow.h
    include/view/videoview.h
    include/view/audioview.h
    include/view/playlistview.h

    # Controller headers
    include/controller/mediacontroller.h
    include/controller/uartcontroller.h

    # Model headers
    include/model/mediafile.h
    include/model/playlist.h
    include/model/uartreceiver.h

    # UI files
    src/view/mainwindow.ui
    src/view/videoview.ui
    src/view/audioview.ui
    src/view/playlistview.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VS_MockProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(VS_MockProject SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(VS_MockProject
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(VS_MockProject PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(VS_MockProject PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
    Qt${QT_VERSION_MAJOR}::SerialPort
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.VS_MockProject)
endif()

set_target_properties(VS_MockProject PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS VS_MockProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VS_MockProject)
endif()
