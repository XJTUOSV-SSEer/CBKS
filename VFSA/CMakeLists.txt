cmake_minimum_required(VERSION 3.0.0)
project(my_test VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories(./include/)
link_directories("/usr/lib/x86-64-linux-gnu" "/usr/local/lib")
add_executable(mytest ./src/main.cpp ./src/client.cpp ./src/load_data.cpp ./src/BigInteger.cpp ./src/Crypto_Primitives.cpp ./src/MurmurHash3.cpp
                ./src/MultisetAccumulator.cpp ./src/Twin_BloomFilter.cpp ./src/MerkleTree.cpp ./src/server.cpp
                ./src/experiment.cpp)

target_link_libraries(mytest libcrypto.so libpbc.so libgmp.so)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
