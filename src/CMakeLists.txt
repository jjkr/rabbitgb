add_executable(rabbitgb main.cpp)
set_property(TARGET rabbitgb PROPERTY CXX_STANDARD 20)
target_link_libraries(rabbitgb ${SDL2_LIBRARIES})