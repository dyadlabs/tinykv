cmake_minimum_required(VERSION 3.16)

project(tinykv VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(tinykv_core 
    src/kv_store.cpp
    src/command_parser.cpp
    src/command_executor.cpp
    src/renderer.cpp
)

target_compile_features(tinykv_core PUBLIC cxx_std_17)

target_include_directories(tinykv_core 
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(tinykv
    src/main.cpp
)

target_link_libraries(tinykv 
    PRIVATE
        tinykv_core
)

include(CTest)

if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    )

    FetchContent_MakeAvailable(googletest)

    add_executable(kv_store_test
        tests/kv_store_test.cpp
    )

    target_link_libraries(kv_store_test 
        PRIVATE
            tinykv_core
            GTest::gtest_main
    )
    
    add_executable(command_parser_test
        tests/command_parser_test.cpp
    )

    target_link_libraries(command_parser_test
        PRIVATE
            tinykv_core
            GTest::gtest_main
    )

    add_executable(command_executor_test
        tests/command_executor_test.cpp
    )

    target_link_libraries(command_executor_test
        PRIVATE
            tinykv_core
            GTest::gtest_main
    )

    add_executable(renderer_test
            tests/renderer_test.cpp
    )

    target_link_libraries(renderer_test
        PRIVATE
            tinykv_core
            GTest::gtest_main
    )

    include(GoogleTest)

    gtest_discover_tests(kv_store_test)
    gtest_discover_tests(command_parser_test)
    gtest_discover_tests(command_executor_test)
    gtest_discover_tests(renderer_test)
endif()

