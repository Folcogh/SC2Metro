cmake_minimum_required(VERSION 2.6)
project(fmetro)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(FMetro_SRCS FMetro.cpp main.cpp)

qt4_automoc(${FMetro_SRCS})
add_executable(fmetro ${FMetro_SRCS})
target_link_libraries(fmetro ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS fmetro RUNTIME DESTINATION bin)
