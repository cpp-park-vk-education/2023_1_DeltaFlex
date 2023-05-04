
file(GLOB game_src
    "src/*/*.cpp"
)


add_library(game SHARED ${game_src})
target_include_directories(game PUBLIC include)
target_include_directories(game PUBLIC include/physics)
target_include_directories(game PUBLIC include/ai)
target_link_libraries(game deltacore)