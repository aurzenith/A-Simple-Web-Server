cmake_minimum_required(VERSION 3.21) # C17 (and C23) support was added in CMake 3.21

project(SimpleWebServer C) 

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON) 


set(CMAKE_C_EXTENSIONS ON) 


file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(simple_web_server ${SOURCES})

# target_link_libraries(my_web_server PUBLIC ${LIBS}) 

target_compile_options(simple_web_server PUBLIC
    -Wall      
    -Wextra     
    -pedantic
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
