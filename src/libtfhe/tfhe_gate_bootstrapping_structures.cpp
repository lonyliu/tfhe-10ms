#include "tfhe_gate_bootstrapping_structures.h"
#include "lwekey.h"
#include "lweparams.h"
#include "lwesamples.h"
#include "tlwe.h"
#include "tgsw.h"

TFheGateBootstrappingParameterSet::TFheGateBootstrappingParameterSet(const int ks_t, const int ks_basebit, const LweParams* const in_out_params, const TGswParams* const tgsw_params):
    ks_t(ks_t),
    ks_basebit(ks_basebit),
    in_out_params(in_out_params),
    tgsw_params(tgsw_params)
{}

TFheGateBootstrappingCloudKeySet::TFheGateBootstrappingCloudKeySet(
        const TFheGateBootstrappingParameterSet* const params, 
        const LweBootstrappingKey* const bk,
	const LweBootstrappingKey* const bk2,
	const LweBootstrappingKey* const bk3,
	const LweBootstrappingKey* const bk4,
        const LweBootstrappingKeyFFT* const bkFFT,
        const LweBootstrappingKeyFFT* const bkFFT2,
        const LweBootstrappingKeyFFT* const bkFFT3,
        const LweBootstrappingKeyFFT* const bkFFT4):
    params(params),bk(bk),bk2(bk2),bk3(bk3),bk4(bk4),bkFFT(bkFFT),bkFFT2(bkFFT2),bkFFT3(bkFFT3),bkFFT4(bkFFT4)
{}

TFheGateBootstrappingSecretKeySet::TFheGateBootstrappingSecretKeySet(
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
        const TGswKey* tgsw_key):
    params(params),
    lwe_key(lwe_key),
    tgsw_key(tgsw_key),
    cloud(params,bk,bk2,bk3,bk4,bkFFT,bkFFT2,bkFFT3,bkFFT4) 
{}
