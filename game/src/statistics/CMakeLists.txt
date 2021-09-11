file(GLOB sources "**/*.cpp")

add_library(statistics STATIC ${sources})
target_link_libraries(statistics PRIVATE sqlite3)

target_include_directories(statistics 
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_include_directories(statistics 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_property(TARGET statistics PROPERTY CXX_STANDARD 20)