# Minimum CMake version required
cmake_minimum_required(VERSION 3.21) # C17 (and C23) support was added in CMake 3.21

# Project name
project(SimpleWebServer C) # Specify C language

# Set the C standard to C17 (ISO C17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON) # Make it a strict requirement

# Allow GNU extensions
set(CMAKE_C_EXTENSIONS ON) # This is the key for 'gnu17'

# Add source files
file(GLOB_RECURSE SOURCES "src/*.c")

# Add the executable target
add_executable(simple_web_server ${SOURCES})

# Link against networking libraries (if needed)
# On Linux, basic socket functions are usually part of libc and don't require explicit linking.
# If you encounter undefined references for networking functions, you might need to add:
# target_link_libraries(my_web_server PUBLIC ${LIBS}) # e.g., -lws2_32 on Windows

# Optional: Add compiler flags (e.g., warnings)
target_compile_options(simple_web_server PUBLIC
    -Wall       # Enable all common warnings
    -Wextra     # Enable extra warnings
    -pedantic   # Warn about non-standard C (this will still warn on GNU extensions
                # even with C_EXTENSIONS ON, if you want to avoid those warnings,
                # you might omit -pedantic if you intentionally use extensions)
    # -Werror   # Treat warnings as errors (good for CI/CD, but can be strict during development)
)

# Optional: Set output directory for executables
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# This was provided by an AI I do not claim it.