
file(GLOB deltacore_src
    "src/*.cpp"
)


add_library(deltacore SHARED ${deltacore_src})
target_include_directories(deltacore PUBLIC include)
target_link_libraries(deltacore spdlog::spdlog)
