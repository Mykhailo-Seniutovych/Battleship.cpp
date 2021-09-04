file(GLOB sources "**/*.cpp")

add_executable(battleship++ main.cpp ${sources})
target_link_libraries(battleship++ PRIVATE core)