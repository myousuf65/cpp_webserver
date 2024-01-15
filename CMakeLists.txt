cmake_minimum_required(VERSION 3.26)
project(cpp_webserver)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_webserver main.cpp)

include_directories(/opt/homebrew/include)
find_package(OpenSSL REQUIRED)
target_link_libraries(cpp_webserver OpenSSL::SSL)

set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/boost)
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(cpp_webserver ${Boost_LIBRARIES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/crow/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nlohmann/json/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cppjwt/jwt-cpp/include)

