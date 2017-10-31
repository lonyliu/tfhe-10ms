/*
 * Bootstrapping FFT functions
 */


#ifndef TFHE_TEST_ENVIRONMENT
#include <iostream>
#include <cassert>
#include "tfhe.h"
//#include <pthread.h>
#include <sys/time.h>
using namespace std;
#define INCLUDE_ALL
#else
#undef EXPORT
#define EXPORT
#endif
/*

	TGswSampleFFT* wintempFFT0;
	TGswSampleFFT* wintempFFT1;
	TGswSampleFFT* wintempFFT2;

	int number0=-1;
	int number1=-1;
*/



#if defined INCLUDE_ALL || defined INCLUDE_TFHE_INIT_LWEBOOTSTRAPPINGKEY_FFT
#undef INCLUDE_TFHE_INIT_LWEBOOTSTRAPPINGKEY_FFT
//(equivalent of the C++ constructor)
EXPORT void init_LweBootstrappingKeyFFT(LweBootstrappingKeyFFT* obj, const LweBootstrappingKey* bk) {
    
    const LweParams* in_out_params = bk->in_out_params;
    const TGswParams* bk_params = bk->bk_params;
    const TLweParams* accum_params = bk_params->tlwe_params;
    const LweParams* extract_params = &accum_params->extracted_lweparams;
    const int n = in_out_params->n;
    const int t = bk->ks->t;
    const int basebit = bk->ks->basebit;
    const int base = bk->ks->base;
    const int N = extract_params->n;

    LweKeySwitchKey* ks = new_LweKeySwitchKey(N, t, basebit, in_out_params);
    // Copy the KeySwitching key
    for(int i=0; i<N; i++) {
        for(int j=0; j<t; j++){
            for(int p=0; p<base; p++) {
                lweCopy(&ks->ks[i][j][p], &bk->ks->ks[i][j][p], in_out_params);
            }
        }
    }

    // Bootstrapping Key FFT 
    TGswSampleFFT* bkFFT = new_TGswSampleFFT_array(n,bk_params);
    for (int i=0; i<n; ++i) {
        tGswToFFTConvert(&bkFFT[i], &bk->bk[i], bk_params);
    }

    new(obj) LweBootstrappingKeyFFT(in_out_params, bk_params, accum_params, extract_params, bkFFT, ks);
}
#endif



//destroys the LweBootstrappingKeyFFT structure
//(equivalent of the C++ destructor)
EXPORT void destroy_LweBootstrappingKeyFFT(LweBootstrappingKeyFFT* obj) {
    delete_LweKeySwitchKey((LweKeySwitchKey*) obj->ks);
    delete_TGswSampleFFT_array(obj->in_out_params->n,(TGswSampleFFT*) obj->bkFFT);

    obj->~LweBootstrappingKeyFFT();
}






#if defined INCLUDE_ALL || defined INCLUDE_TFHE_BLIND_ROTATE_FFT
#undef INCLUDE_TFHE_BLIND_ROTATE_FFT
/**
 * multiply the accumulator by X^sum(bara_i.s_i)
 * @param accum the TLWE sample to multiply
 * @param bk An array of n TGSW FFT samples where bk_i encodes s_i
 * @param bara An array of n coefficients between 0 and 2N-1
 * @param bk_params The parameters of bk
 */

/*
EXPORT void*  PreProcess( void* args)
{
	return 0;
}
*/


EXPORT void tfhe_blindRotate_FFT(TLweSampleFFT* accum, 
    const TGswSampleFFT* bkFFT, 
    const TGswSampleFFT* bkFFT2, 
    const TGswSampleFFT* bkFFT3, 
    const TGswSampleFFT* bkFFT4, 
    const int* bara, 
    const int n, 
    const TGswParams* bk_params) 
{
	TLweSample* temp = new_TLweSample(bk_params->tlwe_params);

    TGswSampleFFT* ACCTempFFT=new_TGswSampleFFT(bk_params);

    //xaitt=new_LagrangeHalfCPolynomial(bk_params->tlwe_params->N);

    const TLweParams* tlwe_params=bk_params->tlwe_params;
    const int k = tlwe_params->k;
    //const int l = params->l;
    const int kpl = bk_params->kpl;
    const int N = tlwe_params->N;

    for (int i=201; i<n; i=i+3) {
        const int ai=bara[i];
        const int ai2=bara[i+1];
        const int ai3=bara[i+2];

//	int inttemp=(ai+ai2+ai3)%2048;
//	int inttemp2=(ai+ai2)%2048;	
//	int inttemp3=(ai+ai3)%2048;	
//	int inttemp4=(ai2+ai3)%2048;	
    static LagrangeHalfCPolynomial* xai=xaitt[(ai+ai2+ai3)%2048];
    static LagrangeHalfCPolynomial* xai2=xaitt[(ai+ai2)%2048];
    static LagrangeHalfCPolynomial* xai3=xaitt[(ai+ai3)%2048];
    static LagrangeHalfCPolynomial* xai4=xaitt[(ai2+ai3)%2048];
    static LagrangeHalfCPolynomial* xai5=xaitt[ai];
    static LagrangeHalfCPolynomial* xai6=xaitt[ai2];
    static LagrangeHalfCPolynomial* xai7=xaitt[ai3];
    static LagrangeHalfCPolynomial* xai8=xaitt[0];



    for (int p=0; p<kpl; p++) {
        const LagrangeHalfCPolynomial* in_s  = (bkFFT+i)->all_samples[p].a;
        const LagrangeHalfCPolynomial* in_s2 = (bkFFT+i+1)->all_samples[p].a;
        const LagrangeHalfCPolynomial* in_s3 = (bkFFT2+i)->all_samples[p].a;
        const LagrangeHalfCPolynomial* in_s4 = (bkFFT2+i+1)->all_samples[p].a;
        const LagrangeHalfCPolynomial* in_s5 = (bkFFT3+i)->all_samples[p].a;
        const LagrangeHalfCPolynomial* in_s6 = (bkFFT3+i+1)->all_samples[p].a;
        const LagrangeHalfCPolynomial* in_s7 = (bkFFT4+i)->all_samples[p].a;
        const LagrangeHalfCPolynomial* in_s8 = (bkFFT4+i+1)->all_samples[p].a;

        LagrangeHalfCPolynomial* out_s = ACCTempFFT->all_samples[p].a;

        for (int j=0; j<=k; j++)
	{

		
		LagrangeHalfCPolynomialAddMul(&out_s[j], xai, &in_s[j]);

		LagrangeHalfCPolynomialAddMul(&out_s[j], xai2, &in_s2[j]);

		LagrangeHalfCPolynomialAddMul(&out_s[j], xai3, &in_s3[j]);

		LagrangeHalfCPolynomialAddMul(&out_s[j], xai4, &in_s4[j]);
	
		LagrangeHalfCPolynomialAddMul(&out_s[j], xai5, &in_s5[j]);

		LagrangeHalfCPolynomialAddMul(&out_s[j], xai6, &in_s6[j]);

		LagrangeHalfCPolynomialAddMul(&out_s[j], xai7, &in_s7[j]);

		LagrangeHalfCPolynomialAddMul(&out_s[j], xai8, &in_s8[j]);


	}
    }

//cout << "here2..." << endl;
//    clock_t begin = clock();
    tGswFFTExternMulToTLwe(accum, ACCTempFFT, bk_params);
//    clock_t end = clock();
// cout << "%2018 time ... " << (end-begin) << endl;
	
    }

    
    delete_TLweSample(temp);
}
#endif 

EXPORT void tGswFFTExternMulToTLwe2(TLweSample *accum, const TGswSampleFFT *gsw, const TGswParams *params) {
    const TLweParams *tlwe_params = params->tlwe_params;
    const int k = tlwe_params->k;
    const int l = params->l;
    const int kpl = params->kpl;
    const int N = tlwe_params->N;
    //TODO attention, improve these new/delete...
    IntPolynomial *deca = new_IntPolynomial_array(kpl, N); //decomposed accumulator
    LagrangeHalfCPolynomial *decaFFT = new_LagrangeHalfCPolynomial_array(kpl, N); //fft version
    TLweSampleFFT *tmpa = new_TLweSampleFFT(tlwe_params);

    for (int i = 0; i <= k; i++)
        tGswTorus32PolynomialDecompH(deca + i * l, accum->a + i, params);
    for (int p = 0; p < kpl; p++)
        IntPolynomial_ifft(decaFFT + p, deca + p);

    tLweFFTClear(tmpa, tlwe_params);
    for (int p = 0; p < kpl; p++) {
        tLweFFTAddMulRTo(tmpa, decaFFT + p, gsw->all_samples + p, tlwe_params);
    }
    tLweFromFFTConvert(accum, tmpa, tlwe_params);

    delete_TLweSampleFFT(tmpa);
    delete_LagrangeHalfCPolynomial_array(kpl, decaFFT);
    delete_IntPolynomial_array(kpl, deca);
}

void tfhe_MuxRotate_FFT(TLweSample *result, const TLweSample *accum, const TGswSampleFFT *bki, const int barai,
                        const TGswParams *bk_params) {
    // ACC = BKi*[(X^barai-1)*ACC]+ACC
    // temp = (X^barai-1)*ACC
    tLweMulByXaiMinusOne(result, barai, accum, bk_params->tlwe_params);
    // temp *= BKi
    tGswFFTExternMulToTLwe2(result, bki, bk_params);
    // ACC += temp
    tLweAddTo(result, accum, bk_params->tlwe_params);
}

EXPORT void tfhe_blindRotate_FFT2(TLweSample *accum,
                                 const TGswSampleFFT *bkFFT,
                                 const int *bara,
                                 const int n,
                                 const TGswParams *bk_params) {

    //TGswSampleFFT* temp = new_TGswSampleFFT(bk_params);
    TLweSample *temp = new_TLweSample(bk_params->tlwe_params);
    TLweSample *temp2 = temp;
    TLweSample *temp3 = accum;

    for (int i = 0; i < 201; i++) {
        const int barai = bara[i];
        if (barai == 0) continue; //indeed, this is an easy case!

        tfhe_MuxRotate_FFT(temp2, temp3, bkFFT + i, barai, bk_params);
        swap(temp2, temp3);
    }
    if (temp3 != accum) {
        tLweCopy(accum, temp3, bk_params->tlwe_params);
    }

    delete_TLweSample(temp);
    //delete_TGswSampleFFT(temp);
}





#if defined INCLUDE_ALL || defined INCLUDE_TFHE_BLIND_ROTATE_AND_EXTRACT_FFT
#undef INCLUDE_TFHE_BLIND_ROTATE_AND_EXTRACT_FFT
/**
 * result = LWE(v_p) where p=barb-sum(bara_i.s_i) mod 2N
 * @param result the output LWE sample
 * @param v a 2N-elt anticyclic function (represented by a TorusPolynomial)
 * @param bk An array of n TGSW FFT samples where bk_i encodes s_i
 * @param barb A coefficients between 0 and 2N-1
 * @param bara An array of n coefficients between 0 and 2N-1
 * @param bk_params The parameters of bk
 */
EXPORT void tfhe_blindRotateAndExtract_FFT(LweSample* result, 
    const TorusPolynomial* v, 
    const TGswSampleFFT* bk,
    const TGswSampleFFT* bk2,
    const TGswSampleFFT* bk3,
    const TGswSampleFFT* bk4, 
    const int barb,
    const int* bara,
    const int n,
    const TGswParams* bk_params) {

    const TLweParams* accum_params = bk_params->tlwe_params;
    const LweParams* extract_params = &accum_params->extracted_lweparams;
    const int N = accum_params->N;
    const int _2N = 2*N;

    // Test polynomial 
    TorusPolynomial* testvectbis = new_TorusPolynomial(N);
    // Accumulator
    TLweSample* acc = new_TLweSample(accum_params);
    TLweSampleFFT* accFFT=new_TLweSampleFFT(accum_params);

    // testvector = X^{2N-barb}*v
    if (barb!=0) torusPolynomialMulByXai(testvectbis, _2N-barb, v);
    else torusPolynomialCopy(testvectbis, v);
    tLweNoiselessTrivial(acc, testvectbis, accum_params);

    // Blind rotation
    tfhe_blindRotate_FFT2(acc, bk, bara, n, bk_params);
//cout << "tfhe_blindRotate_FFT2..." << endl;
//要做一个函数,见CGGI17中tfhe_blindRotate_FFT函数
    tLweToFFTConvert(accFFT,acc,accum_params);

    tfhe_blindRotate_FFT(accFFT, bk,bk2,bk3,bk4, bara, n, bk_params);
    tLweFromFFTConvert(acc,accFFT,accum_params);
    // Extraction
    tLweExtractLweSample(result, acc, extract_params, accum_params);

    delete_TLweSample(acc);
    delete_TorusPolynomial(testvectbis);
}
#endif 





#if defined INCLUDE_ALL || defined INCLUDE_TFHE_BOOTSTRAP_WO_KS_FFT
#undef INCLUDE_TFHE_BOOTSTRAP_WO_KS_FFT
/**
 * result = LWE(mu) iff phase(x)>0, LWE(-mu) iff phase(x)<0
 * @param result The resulting LweSample
 * @param bk The bootstrapping + keyswitch key
 * @param mu The output message (if phase(x)>0)
 * @param x The input sample
 */
EXPORT void tfhe_bootstrap_woKS_FFT(LweSample* result, 
    const LweBootstrappingKeyFFT* bk,
    const LweBootstrappingKeyFFT* bk2,
    const LweBootstrappingKeyFFT* bk3,
    const LweBootstrappingKeyFFT* bk4, 
    Torus32 mu, 
    const LweSample* x){

    const TGswParams* bk_params = bk->bk_params;
    const TLweParams* accum_params = bk->accum_params;
    const LweParams* in_params = bk->in_out_params;
    const int N=accum_params->N;
    const int Nx2= 2*N;
    const int n = in_params->n;

    TorusPolynomial* testvect = new_TorusPolynomial(N);
    int* bara = new int[N];
    

    // Modulus switching
    int barb = modSwitchFromTorus32(x->b,Nx2);
    for (int i=0; i<n; i++) {
        bara[i]=modSwitchFromTorus32(x->a[i],Nx2);
    }

    // the initial testvec = [mu,mu,mu,...,mu]
    for (int i=0;i<N;i++) testvect->coefsT[i]=mu;

    // Bootstrapping rotation and extraction
    tfhe_blindRotateAndExtract_FFT(result, testvect, bk->bkFFT,bk2->bkFFT,bk3->bkFFT,bk4->bkFFT, barb, bara, n, bk_params);

    
    delete[] bara;
    delete_TorusPolynomial(testvect);
}
#endif





   

#if defined INCLUDE_ALL || defined INCLUDE_TFHE_BOOTSTRAP_FFT
#undef INCLUDE_TFHE_BOOTSTRAP_FFT
/**
 * result = LWE(mu) iff phase(x)>0, LWE(-mu) iff phase(x)<0
 * @param result The resulting LweSample
 * @param bk The bootstrapping + keyswitch key
 * @param mu The output message (if phase(x)>0)
 * @param x The input sample
 */
EXPORT void tfhe_bootstrap_FFT(LweSample* result, 
    const LweBootstrappingKeyFFT* bk, 
    const LweBootstrappingKeyFFT* bk2, 
    const LweBootstrappingKeyFFT* bk3, 
    const LweBootstrappingKeyFFT* bk4, 
    Torus32 mu, 
    const LweSample* x){

    LweSample* u = new_LweSample(&bk->accum_params->extracted_lweparams);

    tfhe_bootstrap_woKS_FFT(u, bk,bk2,bk3,bk4, mu, x);
    // Key switching
    lweKeySwitch(result, bk->ks, u);

    delete_LweSample(u);
}
#endif
















//allocate memory space for a LweBootstrappingKeyFFT

EXPORT LweBootstrappingKeyFFT* alloc_LweBootstrappingKeyFFT() {
    return (LweBootstrappingKeyFFT*) malloc(sizeof(LweBootstrappingKeyFFT));
}
EXPORT LweBootstrappingKeyFFT* alloc_LweBootstrappingKeyFFT_array(int nbelts) {
    return (LweBootstrappingKeyFFT*) malloc(nbelts*sizeof(LweBootstrappingKeyFFT));
}

//free memory space for a LweKey
EXPORT void free_LweBootstrappingKeyFFT(LweBootstrappingKeyFFT* ptr) {
    free(ptr);
}
EXPORT void free_LweBootstrappingKeyFFT_array(int nbelts, LweBootstrappingKeyFFT* ptr) {
    free(ptr);
}

//initialize the key structure

EXPORT void init_LweBootstrappingKeyFFT_array(int nbelts, LweBootstrappingKeyFFT* obj, const LweBootstrappingKey* bk) {
    for (int i=0; i<nbelts; i++) {
    init_LweBootstrappingKeyFFT(obj+i,bk);
    }
}


EXPORT void destroy_LweBootstrappingKeyFFT_array(int nbelts, LweBootstrappingKeyFFT* obj) {
    for (int i=0; i<nbelts; i++) {
        destroy_LweBootstrappingKeyFFT(obj+i);
    }
}
 
//allocates and initialize the LweBootstrappingKeyFFT structure
//(equivalent of the C++ new)
EXPORT LweBootstrappingKeyFFT* new_LweBootstrappingKeyFFT(const LweBootstrappingKey* bk) {
    LweBootstrappingKeyFFT* obj = alloc_LweBootstrappingKeyFFT();
    init_LweBootstrappingKeyFFT(obj,bk);
    return obj;
}
EXPORT LweBootstrappingKeyFFT* new_LweBootstrappingKeyFFT_array(int nbelts, const LweBootstrappingKey* bk) {
    LweBootstrappingKeyFFT* obj = alloc_LweBootstrappingKeyFFT_array(nbelts);
    init_LweBootstrappingKeyFFT_array(nbelts,obj,bk);
    return obj;
}

//destroys and frees the LweBootstrappingKeyFFT structure
//(equivalent of the C++ delete)
EXPORT void delete_LweBootstrappingKeyFFT(LweBootstrappingKeyFFT* obj) {
    destroy_LweBootstrappingKeyFFT(obj);
    free_LweBootstrappingKeyFFT(obj);
}
EXPORT void delete_LweBootstrappingKeyFFT_array(int nbelts, LweBootstrappingKeyFFT* obj) {
    destroy_LweBootstrappingKeyFFT_array(nbelts,obj);
    free_LweBootstrappingKeyFFT_array(nbelts,obj);
}






