add_library(rabbitgb
    cart.cpp
    cpu.cpp
    )
set_property(TARGET rabbitgb PROPERTY CXX_STANDARD 20)
target_compile_options(rabbitgb PRIVATE -fmodules-ts)

add_executable(rgb main.cpp)
set_property(TARGET rgb PROPERTY CXX_STANDARD 20)
target_compile_options(rgb PRIVATE -fmodules-ts)
target_link_libraries(rgb rabbitgb ${SDL2_LIBRARIES})

add_executable(tests
    cart_test.cpp
    cpu_test.cpp
)
target_link_libraries(tests rabbitgb GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
set_property(TARGET tests PROPERTY CXX_STANDARD 20)
target_compile_options(tests PRIVATE -fmodules-ts)
gtest_discover_tests(tests)