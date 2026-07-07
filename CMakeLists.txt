cmake_minimum_required(VERSION 3.16)

project(tinykv VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(tinykv_core 
    src/kv_store.cpp
)

target_compile_features(tinykv_core PUBLIC cxx_std_17)

target_include_directories(tinykv_core PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(tinykv
    src/main.cpp
)

target_link_libraries(tinykv PRIVATE
    tinykv_core
)

enable_testing()

add_executable(kv_store_test
    tests/kv_store_test.cpp
)

target_link_libraries(kv_store_test PRIVATE
    tinykv_core
)

add_test(NAME kv_store_test COMMAND kv_store_test)
