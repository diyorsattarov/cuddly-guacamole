cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME remote-admin-tool)

project(${PROJECT_NAME})

add_subdirectory(src)
include_directories(include)

set(SOURCES
    src/socket/socket.cpp
)

add_executable(tests
    ${SOURCES}  
    tests/socket/test_socket.cpp
)

find_package(GTest REQUIRED)

target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS})

target_link_libraries(tests PRIVATE ${GTEST_BOTH_LIBRARIES} pthread)

add_custom_target(run_tests COMMAND tests)

# Check the operating system and set platform-specific settings
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Linux-specific settings
    target_link_libraries(tests PRIVATE -lpthread)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    # Windows-specific settings
    target_link_libraries(tests PRIVATE ws2_32)
    add_definitions(-D_WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
