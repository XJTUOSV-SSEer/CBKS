cmake_minimum_required(VERSION 3.0.0)
project(mytest VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories(./include/)
link_directories("/usr/lib/x86-64-linux-gnu")
add_executable(mytest ./src/test_func.cpp ./src/BloomFilter.cpp ./src/MurmurHash3.cpp ./src/CSC_BloomFilter.cpp
                ./src/Crypto_Primitives.cpp)

target_link_libraries(mytest libcrypto.so)                



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
