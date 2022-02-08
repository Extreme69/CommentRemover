set(SOURCES FSM.c)

set(HEADER_LIST "${CMAKE_SOURCE_DIR}/include/FSM.h")

set(LIBNAME "io_functions")

add_library(${LIBNAME} ${SOURCES} ${HEADER_LIST})

target_include_directories(${LIBNAME} PUBLIC ../include)
