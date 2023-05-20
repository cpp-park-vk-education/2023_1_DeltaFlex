file(GLOB deltacore_test_src
    "src/*.cpp"
)

add_executable(deltacore_test ${deltacore_test_src})
# find_package(GTest REQUIRED)

# target_include_directories(deltacore_test PUBLIC ../include)
target_link_libraries(deltacore_test deltacore GTest::gtest_main)

add_test(deltacore_test deltacore_test)