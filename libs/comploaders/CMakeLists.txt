file(GLOB comploaders_src
    "src/*.cpp"
)

add_library(comploaders SHARED ${comploaders_src})
target_link_libraries(comploaders deltacore)
target_link_libraries(comploaders scloader)