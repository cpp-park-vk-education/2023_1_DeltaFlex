set(ROOTPATH ../../../)

file(GLOB PROJ_SRCS ${ROOTPATH}/src)

add_executable(yusaho_nongui_testing ${PROJ_SRCS})

target_link_libraries(yusaho_nongui_testing GTest::gtest_main)

add_test(yusaho_nongui_testing yusaho_nongui_testing)
