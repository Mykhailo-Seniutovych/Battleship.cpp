file(GLOB sources "**/*.cpp")

add_executable(battleship++ main.cpp ${sources})
target_link_libraries(battleship++ PRIVATE core)
target_link_libraries(battleship++ PRIVATE statistics)
target_link_libraries(battleship++ PRIVATE sqlite3)

target_include_directories(battleship++ 
    PRIVATE 
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_property(TARGET battleship++ PROPERTY CXX_STANDARD 20)