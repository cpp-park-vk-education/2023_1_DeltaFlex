file(GLOB physics_test_srcs
    "src/test_Link.cpp",
    "src/test_PhysicsComponent.cpp",
    "src/test_PointMass.cpp",
    "src/test_StickmanCircle.cpp"
)

file(GLOB ai_test_srcs
    "src/test_ControlComponent.cpp",
    "src/test_Evolution.cpp",
    "src/test_Model.cpp"
)

add_executable(physics_test ${physics_test_srcs})
add_executable(ai_test ${ai_test_srcs})

target_link_libraries(physics_test game GTest::gtest_main)
target_link_libraries(ai_test game GTest::gtest_main)

add_test(physics_test physics_test)
add_test(ai_test ai_test)
