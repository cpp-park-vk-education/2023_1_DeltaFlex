cmake_minimum_required(VERSION 3.5)
project(dfeditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ui/)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

file(GLOB DFEDITOR_SOURCES src/*.cpp)
file(GLOB DFEDITOR_HEADERS include/*.hpp)
file(GLOB DFEDITOR_UIS ui/*.ui)

add_executable(dfeditor ${DFEDITOR_SOURCES} ${DFEDITOR_UIS} ${DFEDITOR_HEADERS})

target_include_directories(dfeditor PUBLIC include)
target_link_libraries(dfeditor PRIVATE Qt5::Widgets)
