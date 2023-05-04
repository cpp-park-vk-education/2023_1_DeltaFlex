
file(GLOB deltacore_src
    "src/*.cpp"
)

add_library(deltacore SHARED ${deltacore_src})
target_include_directories(deltacore PUBLIC include)
target_link_libraries(deltacore spdlog::spdlog)
target_link_libraries(deltacore SDL2)
target_link_libraries(deltacore SDL2_image)
target_link_libraries(deltacore SDL2_mixer)
target_link_libraries(deltacore SDL2_gfx)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()