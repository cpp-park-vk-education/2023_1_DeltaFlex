
file(GLOB scloader_src
    "src/*.cpp"
)

add_library(scloader SHARED ${scloader_src})
target_include_directories(scloader PUBLIC include)
target_link_libraries(scloader deltacore)
target_link_libraries(scloader spdlog::spdlog)

# if(BUILD_TESTS)
#     add_subdirectory(tests)
# endif()