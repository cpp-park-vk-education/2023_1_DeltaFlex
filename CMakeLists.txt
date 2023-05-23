cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_SYSTEM_NAME Windows)
add_compile_options("-fPIC")
project(CringeEngine VERSION 0.1.0)

set(BUILD_TESTS OFF)
# add_compile_definitions(DEVELOPMENT)

option(BUILD_TESTS "build tests")
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
      GTest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG        release-1.11.0
      )
      FetchContent_MakeAvailable(GTest)
      enable_testing()
endif()


# FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
# INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
add_subdirectory(libs/spdlog)
add_subdirectory(libs/deltacore)
add_subdirectory(libs/scloader)
add_subdirectory(libs/comploaders)
add_subdirectory(game)

add_executable(app.exe ./main.cpp)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../mentis_bellum/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY mentis_bellum/)
set_target_properties(app.exe PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "../mentis_bellum/"
)

set_target_properties(deltacore PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY "../../../mentis_bellum/lib/"
)

set_target_properties(game PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY "../../mentis_bellum/lib/"
)

set_target_properties(scloader PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY "../../../mentis_bellum/lib/"
)

set_target_properties(comploaders PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY "../../../mentis_bellum/lib/"
)
# include(FetchContent)
target_link_libraries(app.exe game)
target_link_libraries(app.exe comploaders)
target_link_libraries(app.exe deltacore)
target_link_libraries(app.exe scloader)
target_link_libraries(app.exe spdlog::spdlog)
target_link_libraries(app.exe SDL2)
target_link_libraries(app.exe SDL2_image)
target_link_libraries(app.exe SDL2_mixer)
target_link_libraries(app.exe SDL2_gfx)
target_link_libraries(app.exe SDL2_ttf)
# TARGET_LINK_LIBRARIES(app.exe LINK_PUBLIC ${Boost_LIBRARIES} )
