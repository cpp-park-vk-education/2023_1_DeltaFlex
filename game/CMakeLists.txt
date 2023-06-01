
file(GLOB game_src
    "src/*/*.cpp"
    "src/*.cpp"
)

add_library(game SHARED ${game_src})
target_include_directories(game PUBLIC include)
target_include_directories(game PUBLIC include/physics)
target_include_directories(game PUBLIC include/ai)
target_include_directories(game PUBLIC include/menu)
target_include_directories(game PUBLIC include/game_ui)
target_link_libraries(game deltacore)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
