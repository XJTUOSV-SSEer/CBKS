# CBKS

### File Structure

~~~
CBKS/
├── CBKS							// our scheme: CBKS
│   ├── CMakeLists.txt				// CMake file
│   ├── include
│   │   ├── BF_Enc.h
│   │   ├── BloomFilter.h
│   │   ├── client.h
│   │   ├── CPRF.h
│   │   ├── Crypto_Primitives.h
│   │   ├── CSC_BloomFilter.h
│   │   ├── data_type.h
│   │   ├── experiment.h
│   │   ├── load_data.h
│   │   ├── msg.h
│   │   ├── MurmurHash3.h
│   │   └── server.h
│   └── src
│       ├── BF_Enc.cpp				// the CSC-BF after encrypting using SHVE technique
│       ├── BloomFilter.cpp			// the Bloom Filter using Murmurhash3 technique
│       ├── client.cpp				// the client with abilities of IndexGen, TokenGen and Refresh
│       ├── CPRF.cpp				// Constrained Pseudorandom Function
│       ├── Crypto_Primitives.cpp	// Some Cryptography primitives, such as AES256, PRF, SHA512, et al.
│       ├── CSC_BloomFilter.cpp		// the CSC-BF using Murmurhash3 technique
│       ├── experiment.cpp			// code for several experiments
│       ├── load_data.cpp			// load multi-map from dataset files
│       ├── main.cpp				
│       ├── MurmurHash3.cpp			// the Murmurhash3
│       ├── server.cpp				// the server with abilities of Search and Refresh
│       └── test_func.cpp
├── dataset							// dataset for experiment		
│   ├── 100K.txt					// the multi-map consisting of 100K key-value pairs	which has 200 keys
│   ├── 10K.txt						// the multi-map consisting of 10K key-value pairs	which has 20 keys
│   ├── 150K.txt					// the multi-map consisting of 150K key-value pairs	which has 300 keys
│   ├── 200K.txt					// the multi-map consisting of 200K key-value pairs	which has 400 keys
│   └── 50K.txt						// the multi-map consisting of 50K key-value pairs	which has 100 keys
├── generate_data.cpp
├── PBKS							// Baseline1: PBKS
│   ├── CMakeLists.txt
│   ├── include
│   │   ├── BF_Enc.h				
│   │   ├── BloomFilter.h			
│   │   ├── client.h				
│   │   ├── Crypto_Primitives.h		
│   │   ├── CSC_BloomFilter.h		
│   │   ├── data_type.h
│   │   ├── experiment.h
│   │   ├── load_data.h
│   │   ├── msg.h
│   │   ├── MurmurHash3.h
│   │   └── server.h
│   └── src
│       ├── BF_Enc.cpp				// the CSC-BF after encrypting using SHVE technique
│       ├── BloomFilter.cpp			// the Bloom Filter using Murmurhash3 technique
│       ├── client.cpp				// the client with abilities of IndexGen and TokenGen
│       ├── Crypto_Primitives.cpp	// Some Cryptography primitives, such as AES256, PRF, SHA512, et al.
│       ├── CSC_BloomFilter.cpp		// the CSC-BF using Murmurhash3 technique
│       ├── experiment.cpp			// code for several experiments
│       ├── load_data.cpp			// load multi-map from dataset files
│       ├── main.cpp
│       ├── MurmurHash3.cpp			// the Murmurhash3
│       ├── server.cpp				// the server with abilities of Search
│       └── test_func.cpp
├── PBKS+							// Baseline2: PBKS+
│   ├── CMakeLists.txt
│   ├── include
│   │   ├── BF_Enc.h
│   │   ├── BloomFilter.h
│   │   ├── client.h
│   │   ├── Crypto_Primitives.h
│   │   ├── CSC_BloomFilter.h
│   │   ├── data_type.h
│   │   ├── experiment.h
│   │   ├── load_data.h
│   │   ├── msg.h
│   │   ├── MurmurHash3.h
│   │   └── server.h
│   └── src
│       ├── BF_Enc.cpp				// the CSC-BF after encrypting using SHVE technique
│       ├── BloomFilter.cpp			// the Bloom Filter using Murmurhash3 technique
│       ├── client.cpp				// the client with abilities of IndexGen and TokenGen
│       ├── Crypto_Primitives.cpp	// Some Cryptography primitives, such as AES256, PRF, SHA512, et al.
│       ├── CSC_BloomFilter.cpp		// the CSC-BF using Murmurhash3 technique
│       ├── experiment.cpp			// code for several experiments
│       ├── load_data.cpp			// load multi-map from dataset files
│       ├── main.cpp
│       ├── MurmurHash3.cpp			// the Murmurhash3
│       ├── server.cpp				// the server with abilities of Search
│       └── test_func.cpp
├── VFSA
│   ├── CMakeLists.txt				// CMake file
│   ├── dataset						// dataset for experiment
│   │   ├── 100K.txt				
│   │   ├── 10K.txt
│   │   ├── 150K.txt
│   │   ├── 15K.txt
│   │   ├── 1K.txt
│   │   ├── 200K.txt
│   │   ├── 20K.txt
│   │   ├── 50K.txt
│   │   └── 5K.txt
│   ├── include
│   │   ├── BigInteger.h
│   │   ├── client.h
│   │   ├── Crypto_Primitives.h
│   │   ├── data_type.h
│   │   ├── experiment.h
│   │   ├── load_data.h
│   │   ├── MerkleTree.h
│   │   ├── msg.h
│   │   ├── MultisetAccumulator.h
│   │   ├── MurmurHash3.h
│   │   ├── server.h
│   │   └── Twin_BloomFilter.h
│   └── src
│       ├── a.param
│       ├── BigInteger.cpp				// some methods using for big integer operation
│       ├── client.cpp					// the client with abilities of IndexGen, TokenGen and verify query 											results
│       ├── Crypto_Primitives.cpp		// Some Cryptography primitives, such as AES256, PRF, SHA512, et al.
│       ├── experiment.cpp				// code for several experiments
│       ├── load_data.cpp				// load multi-map from dataset files
│       ├── main.cpp					
│       ├── MerkleTree.cpp				// a Merkle tree class with corresponding methods, such as construct 											and generate merkle proof
│       ├── MultisetAccumulator.cpp		// a RSA MultisetAccumulator
│       ├── MurmurHash3.cpp				// the Murmurhash3
│       ├── server.cpp					// the server with abilities of Search
│       ├── test.cpp
│       └── Twin_BloomFilter.cpp		// a Twin Bloom filter
└── README.md							// Introduction
~~~



### Baseline

PBKS, PBKS+: Y. Liang, J. Ma, et al. “Privacy preserving bloom filter-based keyword search over large encrypted cloud data,” IEEE Trans. Computers, vol. 72, no. 11, pp. 3086–3098, 2023.



### Prepare Environment

Intel(R) Core(TM) i7-10700 [CPU@2.60GHz](mailto:CPU@2.60GHz) ，16GB RAM

Ubuntu 18.04 Server,

GCC 7.5.0, CMake 3.22.4, OpenSSL 1.1.1n



### Building Procedure

#### Build CBKS

~~~bash
cd CBKS
sudo mkdir build
cd build
sudo cmake ..
sudo cmake --build .
./mytest		# run the code
~~~

#### Build PBKS

~~~bash
cd PBKS
sudo mkdir build
cd build
sudo cmake ..
sudo cmake --build .
./mytest		# run the code
~~~

#### Build PBKS+

~~~bash
cd PBKS+
sudo mkdir build
cd build
sudo cmake ..
sudo cmake --build .
./mytest		# run the code
~~~

#### Build VFSA

~~~bash
cd VFSA
sudo mkdir build
cd build
sudo cmake ..
sudo cmake --build .
./mytest		# run the code
~~~



### Contact

yangxu@stu.xjtu.edu.cn

hgzhao@stu.xjtu.edu.cn

