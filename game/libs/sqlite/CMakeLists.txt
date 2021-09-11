PROJECT(sqlite3)
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/src)
add_library(sqlite3 STATIC src/sqlite3.c include/sqlite3.h include/sqlite3ext.h)

target_include_directories(sqlite3 
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_definitions(-DSQLITE_ENABLE_RTREE)
add_definitions(-DSQLITE_ENABLE_FTS4)
add_definitions(-DSQLITE_ENABLE_FTS5)
add_definitions(-DSQLITE_ENABLE_JSON1)
add_definitions(-DSQLITE_ENABLE_RBU)
add_definitions(-DSQLITE_ENABLE_STAT4)

# Uncomment this for single-threaded variant (faster)
add_definitions(-DSQLITE_THREADSAFE=0)

if(WIN32)
  install(FILES sqlite3.exe DESTINATION bin)
else()
  include(FindThreads)
  target_link_libraries(sqlite3 m ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
endif()

install(FILES src/sqlite3.h src/sqlite3ext.h DESTINATION include)
install(TARGETS sqlite3 LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
