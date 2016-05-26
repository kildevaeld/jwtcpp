# Sources
file(GLOB Executable_SOURCES *.cpp)
file(GLOB Executable_HEADERS *.hpp)



add_executable(jwt ${Executable_SOURCES} ${Executable_HEADERS})

# Link in the library
target_link_libraries(jwt jwtcpp)