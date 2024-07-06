cmake_minimum_required(VERSION 3.12)
project(CppProjectBuilder)

set(CMAKE_CXX_STANDARD 17)

# Gather all source files
file(GLOB SOURCES "source/*.cpp")
file(GLOB HEADERS "source/*.h")

# Create the executable
add_executable(CppProjectBuilder ${SOURCES} ${HEADERS})

# Link any additional libraries here
# target_link_libraries(CppProjectBuilder YourLibrary)
