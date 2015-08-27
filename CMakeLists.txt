cmake_minimum_required(VERSION 2.8.11)
project(FMetro)

# Find the QtWidgets library
find_package(Qt5 REQUIRED Widgets)
find_package(Qt5 REQUIRED Gui)

# Include that globally, so KDevelop can find the headers
include_directories(FMetro PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    )

# Create target
add_executable(FMetro
    BOTimer.cpp
    Controller.cpp
    CyclicTimer.cpp
    FException.cpp
    Game.cpp
    GameUi.cpp
    main.cpp
    MainWindow.cpp
    UiEditCyclicTimer.cpp
    UiEditGameName.cpp
    )

target_compile_options(FMetro PUBLIC
    -std=c++11
    -Wall
    -Wextra
    )

target_link_libraries(FMetro
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    )

set_target_properties(FMetro PROPERTIES
    AUTOMOC ON
    )

# Installation
install(TARGETS FMetro RUNTIME DESTINATION bin)
