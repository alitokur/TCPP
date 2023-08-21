cmake_minimum_required(VERSION 3.10)
project(TCPP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(tcp_client main.cpp tcp_client.cpp)

# Include directories
target_include_directories(tcp_client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Optional: Install target (example)
install(TARGETS tcp_client DESTINATION bin)
