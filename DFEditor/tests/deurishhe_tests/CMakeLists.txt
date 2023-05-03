project(deurishhe_testing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Test Widgets)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

enable_testing(true)

set(ROOTPATH ../../)

set(DFEDITOR_HEADERS 
    ${ROOTPATH}/include/DFEAssetViewer.hpp
    ${ROOTPATH}/include/DFEExpandingWidget.hpp
    ${ROOTPATH}/include/DFEProjectExplorer.hpp
)

set(DFEDITOR_SRCS 
    ${ROOTPATH}/src/DFEAssetViewer.cpp
    ${ROOTPATH}/src/DFEExpandingWidget.cpp
    ${ROOTPATH}/src/DFEProjectExplorer.cpp
)

file(GLOB DFEDITOR_TESTS tests/*)

add_executable(deurishhe_testing 
    ${DFEDITOR_HEADERS} 
    ${DFEDITOR_SRCS} 
    ${DFEDITOR_TESTS} 
    main.cpp
)

target_include_directories(deurishhe_testing PUBLIC tests ../../include)

target_link_libraries(deurishhe_testing PUBLIC Qt::Widgets Qt::Test)

add_test(NAME testing COMMAND testing)
