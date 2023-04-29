
file(GLOB game_src
    "src/*.cpp"
)


add_library(game SHARED ${game_src})
target_include_directories(game PUBLIC include)
target_link_libraries(game deltacore)