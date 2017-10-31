cmake_minimum_required(VERSION 3.0)

include_directories(${GTEST_INCLUDE_DIRS})

set(GOOGLETEST_SOURCES
    arithmetic_test.cpp
    lwe_test.cpp
    polynomial_test.cpp
    tlwe_test.cpp
    tgsw_test.cpp
    tlwe_fft_test.cpp
    tgsw_fft_test.cpp
    lwekeyswitch_test.cpp
    bootstrapping_test.cpp
    bootstrapping_test_fft.cpp
    io_test.cpp
    lagrangehalfc_test.cpp
    boots_gates_test.cpp
    )

set(CPP_ITESTS
    test-bootstrapping-fft
    test-decomp-tgsw
    test-lwe
    test-multiplication
    test-tlwe
    test-gate-bootstrapping
    test-addition-boot
    test-long-run
    )

set(C_ITESTS
    test-c-binding
    )

# We build a specific unit and integration test for each fft processor
foreach (FFT_PROCESSOR IN LISTS FFT_PROCESSORS) 

if (FFT_PROCESSOR STREQUAL "fftw")
set(RUNTIME_LIBS
    tfhe-fftw
    ${FFTW_LIBRARIES}
    )

else ()
set(RUNTIME_LIBS
    tfhe-${FFT_PROCESSOR}
    )

endif (FFT_PROCESSOR STREQUAL "fftw") 




    add_executable(test-bootstrapping-fft-${FFT_PROCESSOR} test-bootstrapping-fft.cpp ${TFHE_HEADERS})
    target_link_libraries(test-bootstrapping-fft-${FFT_PROCESSOR} ${RUNTIME_LIBS})


endforeach (FFT_PROCESSOR IN LISTS FFT_PROCESSORS) 
