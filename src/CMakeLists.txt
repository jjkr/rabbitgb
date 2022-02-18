add_library(rabbitgb cart.cpp)
set_property(TARGET rabbitgb PROPERTY CXX_STANDARD 20)

add_executable(rgb main.cpp)
set_property(TARGET rgb PROPERTY CXX_STANDARD 20)
target_link_libraries(rgb rabbitgb ${SDL2_LIBRARIES})