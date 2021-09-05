file(GLOB sources "**/*.cpp")

add_executable(battleship++ main.cpp ${sources})
target_link_libraries(battleship++ PRIVATE core)

target_include_directories(battleship++ 
    PRIVATE 
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)