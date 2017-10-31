#ifndef TFHE_H
#define TFHE_H

///@file
///@brief This file declares almost everything

#include "tfhe_core.h"

#include "numeric_functions.h"

#include "polynomials_arithmetic.h"
#include "lagrangehalfc_arithmetic.h"

#include "lwe-functions.h"

#include "tlwe_functions.h"

#include "tgsw_functions.h"

#include "lwekeyswitch.h"

#include "lwebootstrappingkey.h"

#include "tfhe_gate_bootstrapping_functions.h"

#include "tfhe_io.h"

///////////////////////////////////////////////////
//  TFHE bootstrapping internal functions
//////////////////////////////////////////////////


/** sets the seed of the random number generator to the given values */
EXPORT void tfhe_random_generator_setSeed(uint32_t* values, int size);

EXPORT void tfhe_blindRotate(TLweSample* accum, const TGswSample* bk, const int* bara, const int n, const TGswParams* bk_params);
EXPORT void tfhe_blindRotateAndExtract(LweSample* result, const TorusPolynomial* v, const TGswSample* bk, const int barb, const int* bara, const int n, const TGswParams* bk_params);
EXPORT void tfhe_bootstrap_woKS(LweSample* result, const LweBootstrappingKey* bk, Torus32 mu, const LweSample* x);
EXPORT void tfhe_bootstrap(LweSample* result, const LweBootstrappingKey* bk, Torus32 mu, const LweSample* x);
EXPORT void tfhe_createLweBootstrappingKey(LweBootstrappingKey* bk,LweBootstrappingKey* bk2,LweBootstrappingKey* bk3,LweBootstrappingKey* bk4, const LweKey* key_in, const TGswKey* rgsw_key);

EXPORT void tfhe_blindRotate_FFT(TLweSampleFFT* accum, 
    const TGswSampleFFT* bkFFT, 
    const TGswSampleFFT* bkFFT2, 
    const TGswSampleFFT* bkFFT3, 
    const TGswSampleFFT* bkFFT4, 
    const int* bara, 
    const int n, 
    const TGswParams* bk_params);
EXPORT void tfhe_blindRotateAndExtract_FFT(LweSample* result, const TorusPolynomial* v, const TGswSampleFFT* bk,const TGswSampleFFT* bk2,const TGswSampleFFT* bk3,const TGswSampleFFT* bk4, const int barb, const int* bara, const int n, const TGswParams* bk_params);
EXPORT void tfhe_bootstrap_woKS_FFT(LweSample* result, const LweBootstrappingKeyFFT* bk,const LweBootstrappingKeyFFT* bk2,const LweBootstrappingKeyFFT* bk3,const LweBootstrappingKeyFFT* bk4, Torus32 mu, const LweSample* x);
EXPORT void tfhe_bootstrap_FFT(LweSample* result, const LweBootstrappingKeyFFT* bk,const LweBootstrappingKeyFFT* bk2,const LweBootstrappingKeyFFT* bk3,const LweBootstrappingKeyFFT* bk4, Torus32 mu, const LweSample* x);
EXPORT void*  PreProcess( void* args);
struct PreParams {
    TLweSampleFFT* accum; 
    const TGswSampleFFT* bkFFT; 
    const TGswSampleFFT* bkFFT2; 
    const TGswSampleFFT* bkFFT3; 
    const TGswSampleFFT* bkFFT4; 
    const int* bara; 
    int n; 
    const TGswParams* bk_params;
};
     extern LagrangeHalfCPolynomial* xaitt[2048];
#endif //TFHE_H
