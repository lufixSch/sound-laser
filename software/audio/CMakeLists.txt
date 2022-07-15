cmake_minimum_required(VERSION 3.0.0)
project(sound_laser VERSION 0.1.1)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_PATH ${PROJECT_SOURCE_DIR}/src)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/include/**/*.hpp ${PROJECT_SOURCE_DIR}/src/*.hpp)
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/**/*.cpp ${PROJECT_SOURCE_DIR}/src/*.cpp)

include(CMakePrintHelpers)
cmake_print_variables(HEADER_FILES)

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_PATH})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

find_package(Threads REQUIRED)

find_package(ALSA REQUIRED)
if (ALSA_FOUND)
  target_include_directories(${PROJECT_NAME} PUBLIC ${ALSA_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} PUBLIC ${ALSA_LIBRARIES})
endif(ALSA_FOUND)

target_link_libraries(${PROJECT_NAME} PUBLIC bcm2835 Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
