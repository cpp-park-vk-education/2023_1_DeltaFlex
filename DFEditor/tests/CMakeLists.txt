project(testing LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Test Widgets)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

enable_testing(true)

file(GLOB DFEDITOR_HEADERS ../include/**)
file(GLOB DFEDITOR_SRCS ../src/**)
file(GLOB DFEDITOR_HEADERS_WRAPPERS include/**)
file(GLOB DFEDITOR_TESTS src/**)

add_executable(testing 
    ${DFEDITOR_HEADERS} 
    ${DFEDITOR_SRCS} 
    ${DFEDITOR_HEADERS_WRAPPERS}
    ${DFEDITOR_TESTS} 
)

target_include_directories(testing PUBLIC ../include PUBLIC include/)
target_link_libraries(testing PUBLIC Qt::Widgets Qt::Test)

add_test(NAME testing COMMAND testing)
