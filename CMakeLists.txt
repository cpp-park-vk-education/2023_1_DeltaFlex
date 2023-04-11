cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_SYSTEM_NAME Windows)
add_compile_options("-fPIC")
project(CringeEngine VERSION 0.1.0)


# FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
# INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
add_subdirectory(libs/spdlog)
add_subdirectory(libs/deltacore)

add_executable(app.exe ./main.cpp)

target_link_libraries(app.exe deltacore)
target_link_libraries(app.exe spdlog::spdlog)
target_link_libraries(app.exe SDL2)
target_link_libraries(app.exe SDL2_image)
target_link_libraries(app.exe SDL2_mixer)
# TARGET_LINK_LIBRARIES(app.exe LINK_PUBLIC ${Boost_LIBRARIES} )
