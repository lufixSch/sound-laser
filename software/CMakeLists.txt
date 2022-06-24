cmake_minimum_required(VERSION 3.0.0)
project(sound_laser VERSION 0.1.0)

add_executable(${PROJECT_NAME} main.cpp)

find_package(ALSA REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC bcm2835 ALSA)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
