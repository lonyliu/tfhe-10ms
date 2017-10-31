#ifndef TFHE_GATE_BOOTSTRAPPING_STRUCTURES_H
#define TFHE_GATE_BOOTSTRAPPING_STRUCTURES_H

///@file
///@brief gate bootstrapping api structures definition

#include "tfhe_core.h"

struct TFheGateBootstrappingParameterSet {
    const int ks_t;
    const int ks_basebit;
    const LweParams* const in_out_params;
    const TGswParams* const tgsw_params;
#ifdef __cplusplus
    TFheGateBootstrappingParameterSet(const int ks_t, const int ks_basebit, const LweParams* const in_out_params, const TGswParams* const tgsw_params);
    TFheGateBootstrappingParameterSet(const TFheGateBootstrappingParameterSet&)=delete;
    void operator=(const TFheGateBootstrappingParameterSet&)=delete;
#endif
};

struct TFheGateBootstrappingCloudKeySet {
    const TFheGateBootstrappingParameterSet* const params;
	    const LweBootstrappingKey* const bk;
	    const LweBootstrappingKey* const bk2;
	    const LweBootstrappingKey* const bk3;
	    const LweBootstrappingKey* const bk4;
	    const LweBootstrappingKeyFFT* const bkFFT;
	    const LweBootstrappingKeyFFT* const bkFFT2;
	    const LweBootstrappingKeyFFT* const bkFFT3;
	    const LweBootstrappingKeyFFT* const bkFFT4;
#ifdef __cplusplus
    TFheGateBootstrappingCloudKeySet(
	    const TFheGateBootstrappingParameterSet* const params, 
	    const LweBootstrappingKey* const bk,
	    const LweBootstrappingKey* const bk2,
	    const LweBootstrappingKey* const bk3,
	    const LweBootstrappingKey* const bk4,
	    const LweBootstrappingKeyFFT* const bkFFT,
	    const LweBootstrappingKeyFFT* const bkFFT2,
	    const LweBootstrappingKeyFFT* const bkFFT3,
	    const LweBootstrappingKeyFFT* const bkFFT4);
    TFheGateBootstrappingCloudKeySet(const TFheGateBootstrappingCloudKeySet&)=delete;
    void operator=(const TFheGateBootstrappingCloudKeySet&)=delete;
#endif
};

//大的，里面包含CloudKeySet
struct TFheGateBootstrappingSecretKeySet {
    const TFheGateBootstrappingParameterSet* params;
    const LweKey* lwe_key;
    const TGswKey* tgsw_key;
    const TFheGateBootstrappingCloudKeySet cloud;
#ifdef __cplusplus
    TFheGateBootstrappingSecretKeySet(
	    const TFheGateBootstrappingParameterSet* const params, 
	    const LweBootstrappingKey* const bk,
	    const LweBootstrappingKey* const bk2,
	    const LweBootstrappingKey* const bk3,
	    const LweBootstrappingKey* const bk4,
	    const LweBootstrappingKeyFFT* const bkFFT,
	    const LweBootstrappingKeyFFT* const bkFFT2,
	    const LweBootstrappingKeyFFT* const bkFFT3,
	    const LweBootstrappingKeyFFT* const bkFFT4,
	    const LweKey* lwe_key,
	    const TGswKey* tgsw_key);
    TFheGateBootstrappingSecretKeySet(const TFheGateBootstrappingSecretKeySet&)=delete;
    void operator=(const TFheGateBootstrappingSecretKeySet&)=delete;
#endif
};

#endif //TFHE_GATE_BOOTSTRAPPING_STRUCTURES_H
