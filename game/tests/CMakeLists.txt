file(GLOB physics_test_srcs
    "src/*.cpp"
)

add_executable(physics_test ${physics_test_srcs})

target_link_libraries(physics_test game GTest::gtest_main)

add_test(physics_test physics_test)
