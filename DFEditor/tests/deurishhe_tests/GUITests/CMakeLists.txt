project(deurishhe_gui_testing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Test Widgets)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

enable_testing(true)

set(ROOTPATH ../../..)

set(DFEDITOR_HEADERS 
    ${ROOTPATH}/include/DFESceneInspectorTree.hpp
)

set(DFEDITOR_SRCS 
    ${ROOTPATH}/src/DFESceneInspectorTree.cpp
)

file(GLOB DFEDITOR_TESTS tests/*)

add_executable(deurishhe_gui_testing
    ${DFEDITOR_HEADERS} 
    ${DFEDITOR_SRCS} 
    ${DFEDITOR_TESTS} 
    main.cpp
)

target_include_directories(deurishhe_gui_testing PUBLIC tests ${ROOTPATH}/include)

target_link_libraries(deurishhe_gui_testing PUBLIC Qt::Widgets Qt::Test)

add_test(NAME deurishhe_gui_testing COMMAND deurishhe_gui_testing)
