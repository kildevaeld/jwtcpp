CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(jwtcpp)


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


find_package(PkgConfig REQUIRED)
pkg_search_module(OPENSSL REQUIRED openssl)

include_directories(/usr/local/include)

if( OPENSSL_FOUND )
	message(state ${OPENSSL_INCLUDE_DIRS})
    include_directories(${OPENSSL_INCLUDE_DIRS})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
else()
    # Error; with REQUIRED, pkg_search_module() will throw an error by it's own
endif()

option(BuildTests "" OFF)
add_subdirectory(vendor/json)
add_subdirectory(example)


include_directories(vendor/json/src/)

set(LIBS ${LIBS} ${OPENSSL_LIBRARIES} )

FILE(GLOB_RECURSE SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp)
FILE(GLOB_RECURSE HEADERS  ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.h)


add_library(jwtcpp ${SOURCES} ${HEADERS})

target_link_libraries(jwtcpp LINK_PUBLIC ${LIBS})
