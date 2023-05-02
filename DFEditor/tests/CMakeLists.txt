project(testing LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Test Widgets)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

enable_testing(true)

add_executable(testing ../src/DFEAssetViewer.cpp test_DFEAssetViewer.cpp)

target_include_directories(testing PUBLIC ../include)
target_link_libraries(testing PUBLIC Qt::Widgets Qt::Test)

add_test(NAME testing COMMAND testing)
