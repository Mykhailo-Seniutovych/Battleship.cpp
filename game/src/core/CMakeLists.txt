file(GLOB sources "**/*.cpp")

add_library(core STATIC ${sources})

target_include_directories(core 
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
