file(GLOB sources "**/*.cpp")

add_library(core STATIC ${sources})

target_include_directories(core 
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_include_directories(core
    PRIVATE 
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_include_directories(core 
    PRIVATE 
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/libs/json/include>
)

set_property(TARGET core PROPERTY CXX_STANDARD 20)
