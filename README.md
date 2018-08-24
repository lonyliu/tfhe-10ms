# tfhe-10ms

Thanks to the sharing of TFHE source code, since our work mainly focused on optimizing and improving the BOOTSTRAPPING module in TFHE, some modifications were made in the code, mainly focusing on the files /src/lwe-bootstrapping-functions-fft.cpp /src/tgsw-fft-operations.cpp /src/lwe-bootstrapping-functions.cpp /src/tfhe_gate_bootstrapping.cpp.

We have made two improvements to accelerate the bootstrapping based on TFHE. On the one hand, as hundreds of serial homomorphic additions take most of the time of bootstrapping, we constructed the logical expression using truth table to reduce the number of serial homomorphic additions by two-thirds, and thus proposed an efficient FHE scheme with bootstrapping. On the other hand, we proposed a set of more efficient combination of parameters.
Thanks again for the source code and you can visit https://github.com/tfhe/tfhe for more informations.


TFHE is open-source software distributed under the terms of the Apache 2.0 license. 
The scheme is described in the paper "Faster fully homomorphic encryption: Bootstrapping in less than 0.1 seconds" presented at the IACR conference Asiacrypt 2016 by Ilaria Chillotti, Nicolas Gama, Mariya Georgieva, Malika Izabachène.


### Dependencies 


The library interface can be used in a regular C code. However, to compile the core of the library you will need a standard C++11 compiler.
Currently, the project has only been tested with the g++ compiler under Linux. In the future, we plan to extend the compatibility to other compilers, platforms and operating systems.

At least one FFT processor is needed to run the project:

* The default processor comes from Project Nayuki, who proposes two implementations of the fast Fourier transform - one in portable C, and the other using the AVX assembly instructions.
This component is licensed under the MIT license, and we added the code of the reverse FFT (both in C and in assembly). Original source: https://www.nayuki.io/page/fast-fourier-transform-in-x86-assembly
* we provide another processor, named the spqlios processor, which is written in AVX and FMA assembly in the style of the nayuki processor, and which is dedicated to the ring R[X]/(X^N+1) for N a power of 2.
* We also provide a connector for the FFTW3 library: http://www.fftw.org. With this library, the performance of the FFT is between 2 and 3 times faster than the default Nayuki implementation. However, you should keep in mind that the library FFTW is published under the GPL License. If you choose to use this library in a final product, this product may have to be released under GPL License as well (other commercial licenses are available on their web site)
* We plan to add other connectors in the future (for instance the Intel’s IPP Fourier Transform, which should be 1.5× faster than FFTW for 1D real data)


### Installation

To build the library with the default options, run ```make``` and ```make install``` from the top level directory of the TFHE project. This assumes that the standard tool cmake is already installed on the system, and an
up-to-date c++ compiler (i.e. g++ >=5.2) as well.
It will compile the library in optimized mode, and install it to ```/usr/local/lib``` folder.
Currently, only static libraries are generated. 

If you want to choose additional compile options (i.e. other installation folder, debug mode, tests, fftw), you need to run cmake manually and pass the desired options:


```
mkdir build
cd build
cmake ../src -DENABLE_TESTS=on -DENABLE_FFTW=on -DCMAKE_BUILD_TYPE=release
cmake ../src -DENABLE_TESTS=on -DENABLE_FFTW=on -DCMAKE_BUILD_TYPE=release
make
```


The available options are the following:

| Variable Name          | values           | 
|------------------------|-------|
| CMAKE_INSTALL_PREFIX   | */usr/local* installation folder (libs go in lib/ and headers in include/) | 
| CMAKE_BUILD_TYPE       | <ul><li>*optim* enables compiler's optimization flags, including native architecture specific optimizations</li><li>*debug* disables any optimization and include all debugging info (-g3 -O0)</li> | 
| ENABLE_TESTS           | *on/off* compiles the library's unit tests and sample applications in the test/ folder. This assumes that googletest>1.8 is installed on the system. (use ```ctest``` to run all tests) | 
| ENABLE_FFTW            | *on/off* compiles libtfhe-fftw.a, using FFTW3 (GPL licence) for fast FFT computations |
| ENABLE_NAYUKI_PORTABLE | *on/off* compiles libtfhe-nayuki-portable.a, using the fast C version of nayuki for FFT computations |
| ENABLE_NAYUKI_AVX      | *on/off* compiles libtfhe-nayuki-avx.a, using the avx assembly version of nayuki for FFT computations |
| ENABLE_SPQLIOS_AVX     | *on/off* compiles libtfhe-spqlios-avx.a, using tfhe's dedicated avx assembly version for FFT computations |
| ENABLE_SPQLIOS_FMA     | *on/off* compiles libtfhe-spqlios-fma.a, using tfhe's dedicated fma assembly version for FFT computations |

### References

[CGGI17]	Chillotti I, Gama N, Georgieva M, et al. Faster Packed Homomorphic Operations and Efficient Circuit Bootstrapping for TFHE[C]. International Conference on the Theory and Application of Cryptology and Information Security—ASIACRYPT 2017. Springer, Heidelberg, 2017:377-408.

[CGGI16]: I. Chillotti, N. Gama, M. Georgieva, and M. Izabachène. Faster fully homomorphic encryption: Bootstrapping in less than 0.1 seconds. In Asiacrypt 2016, pages 3-33.

[DM15]:   L. Ducas and D. Micciancio.  FHEW: Bootstrapping homomorphic encryption in less than a second.  In Eurocrypt 2015, pages 617-640.

[GSW13]:  C. Gentry, A. Sahai, and B. Waters. Homomorphic encryption from learning with errors:  Conceptually-simpler,  asymptotically-faster,  attribute-based. In Crypto 2013, pages 75-92











