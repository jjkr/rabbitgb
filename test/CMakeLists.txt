add_executable(tests
    cart_test.cpp
    cpu_test.cpp
)
target_link_libraries(tests rabbitgb GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
set_property(TARGET tests PROPERTY CXX_STANDARD 20)
gtest_discover_tests(tests)