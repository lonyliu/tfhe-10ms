#include <polynomials.h>
#include "lagrangehalfc_impl.h"

LagrangeHalfCPolynomial_IMPL::LagrangeHalfCPolynomial_IMPL(const int N) {
    assert(N==1024);
    coefsC = new cplx[N/2];
    proc = &fp1024_nayuki;
}

LagrangeHalfCPolynomial_IMPL::~LagrangeHalfCPolynomial_IMPL() {
    delete[] coefsC;
}

//initialize the key structure
//(equivalent of the C++ constructor)
EXPORT void init_LagrangeHalfCPolynomial(LagrangeHalfCPolynomial* obj, const int N) {
    new(obj) LagrangeHalfCPolynomial_IMPL(N);
}
EXPORT void init_LagrangeHalfCPolynomial_array(int nbelts, LagrangeHalfCPolynomial* obj, const int N) {
    for (int i=0; i<nbelts; i++) {
	new(obj+i) LagrangeHalfCPolynomial_IMPL(N);
    }
}

//destroys the LagrangeHalfCPolynomial structure
//(equivalent of the C++ destructor)
EXPORT void destroy_LagrangeHalfCPolynomial(LagrangeHalfCPolynomial* obj) {
    LagrangeHalfCPolynomial_IMPL* objbis = (LagrangeHalfCPolynomial_IMPL*) obj;
    objbis->~LagrangeHalfCPolynomial_IMPL();
}
EXPORT void destroy_LagrangeHalfCPolynomial_array(int nbelts, LagrangeHalfCPolynomial* obj) {
    LagrangeHalfCPolynomial_IMPL* objbis = (LagrangeHalfCPolynomial_IMPL*) obj;
    for (int i=0; i<nbelts; i++) {
	(objbis+i)->~LagrangeHalfCPolynomial_IMPL();
    }
}
 

//MISC OPERATIONS
/** sets to zero */
EXPORT void LagrangeHalfCPolynomialClear(
	LagrangeHalfCPolynomial* reps) {
    LagrangeHalfCPolynomial_IMPL* reps1 = (LagrangeHalfCPolynomial_IMPL*) reps;
    const int Ns2 = reps1->proc->Ns2;
    for (int i=0; i<Ns2; i++) 
	reps1->coefsC[i] = 0;
}

EXPORT void LagrangeHalfCPolynomialSetTorusConstant(LagrangeHalfCPolynomial* result, const Torus32 mu) {
    LagrangeHalfCPolynomial_IMPL* result1 = (LagrangeHalfCPolynomial_IMPL*) result;
    const int Ns2 = result1->proc->Ns2;
    cplx* b = result1->coefsC;
    const cplx muc = t32tod(mu);
    for (int j=0; j<Ns2; j++)
    	b[j]=muc;
}

EXPORT void LagrangeHalfCPolynomialAddTorusConstant(LagrangeHalfCPolynomial* result, const Torus32 mu) {
    LagrangeHalfCPolynomial_IMPL* result1 = (LagrangeHalfCPolynomial_IMPL*) result;
    const int Ns2 = result1->proc->Ns2;
    cplx* b = result1->coefsC;
    const cplx muc = t32tod(mu);
    for (int j=0; j<Ns2; j++)
    	b[j]+=muc;
}
EXPORT void LagrangeHalfCPolynomialAddTorusConstant2(LagrangeHalfCPolynomial* result, LagrangeHalfCPolynomial* result2) {


    LagrangeHalfCPolynomial_IMPL* result11 = (LagrangeHalfCPolynomial_IMPL*) result;
    LagrangeHalfCPolynomial_IMPL* result22 = (LagrangeHalfCPolynomial_IMPL*) result2;
    const int Ns2 = result11->proc->Ns2;
    cplx* b = result11->coefsC;
    cplx* b2 = result22->coefsC;

    for (int j=0; j<Ns2; j++) b[j]+=b2[j];
}
EXPORT void LagrangeHalfCPolynomialSetXai(LagrangeHalfCPolynomial* result, const int ai) {
    LagrangeHalfCPolynomial_IMPL* result1 = (LagrangeHalfCPolynomial_IMPL*) result;
    const int Ns2 = result1->proc->Ns2;
    const int _2N = result1->proc->_2N;
    const cplx* omegaxminus1 = result1->proc->omegaxminus1;
    for (int i=0; i<Ns2; i++)
	result1->coefsC[i]=omegaxminus1[((2*i+1)*ai)%_2N];
}

/** termwise multiplication in Lagrange space */
EXPORT void LagrangeHalfCPolynomialMul(
	LagrangeHalfCPolynomial* result, 
	const LagrangeHalfCPolynomial* a, 
	const LagrangeHalfCPolynomial* b) {
    LagrangeHalfCPolynomial_IMPL* result1 = (LagrangeHalfCPolynomial_IMPL*) result;
    const int Ns2 = result1->proc->Ns2;
    cplx* aa = ((LagrangeHalfCPolynomial_IMPL*) a)->coefsC;
    cplx* bb = ((LagrangeHalfCPolynomial_IMPL*) b)->coefsC;
    cplx* rr = result1->coefsC;
    for (int i=0; i<Ns2; i++) 
	rr[i] = aa[i]*bb[i];
}
EXPORT void LagrangeHalfCPolynomialMul8Add(
	LagrangeHalfCPolynomial* result, 
	const LagrangeHalfCPolynomial* a,
	const LagrangeHalfCPolynomial* a2,
	const LagrangeHalfCPolynomial* a3,
	const LagrangeHalfCPolynomial* a4,
	const LagrangeHalfCPolynomial* a5,
	const LagrangeHalfCPolynomial* a6,
	const LagrangeHalfCPolynomial* a7,
 
	const LagrangeHalfCPolynomial* b,
	const LagrangeHalfCPolynomial* b2,
	const LagrangeHalfCPolynomial* b3,
	const LagrangeHalfCPolynomial* b4,
	const LagrangeHalfCPolynomial* b5,
	const LagrangeHalfCPolynomial* b6,
	const LagrangeHalfCPolynomial* b7,
	const LagrangeHalfCPolynomial* b8
) {
    LagrangeHalfCPolynomial_IMPL* result1 = (LagrangeHalfCPolynomial_IMPL*) result;
    const int Ns2 = result1->proc->Ns2;
    cplx* aa = ((LagrangeHalfCPolynomial_IMPL*) a)->coefsC;
    cplx* bb = ((LagrangeHalfCPolynomial_IMPL*) b)->coefsC;
    cplx* rr = result1->coefsC;
    for (int i=0; i<Ns2; i++) 
	rr[i] = aa[i]*bb[i];
}
/** termwise multiplication and addTo in Lagrange space */
EXPORT void LagrangeHalfCPolynomialAddMul(
	LagrangeHalfCPolynomial* accum, 
	const LagrangeHalfCPolynomial* a, 
	const LagrangeHalfCPolynomial* b) 
{
    LagrangeHalfCPolynomial_IMPL* result1 = (LagrangeHalfCPolynomial_IMPL*) accum;
    const int Ns2 = result1->proc->Ns2;
    cplx* aa = ((LagrangeHalfCPolynomial_IMPL*) a)->coefsC;
    cplx* bb = ((LagrangeHalfCPolynomial_IMPL*) b)->coefsC;
    cplx* rr = result1->coefsC;
    for (int i=0; i<Ns2; i++) 
	rr[i] += aa[i]*bb[i];
}


/** termwise multiplication and addTo in Lagrange space */
EXPORT void LagrangeHalfCPolynomialSubMul(
	LagrangeHalfCPolynomial* accum, 
	const LagrangeHalfCPolynomial* a, 
	const LagrangeHalfCPolynomial* b) 
{
    LagrangeHalfCPolynomial_IMPL* result1 = (LagrangeHalfCPolynomial_IMPL*) accum;
    const int Ns2 = result1->proc->Ns2;
    cplx* aa = ((LagrangeHalfCPolynomial_IMPL*) a)->coefsC;
    cplx* bb = ((LagrangeHalfCPolynomial_IMPL*) b)->coefsC;
    cplx* rr = result1->coefsC;
    for (int i=0; i<Ns2; i++) 
	rr[i] -= aa[i]*bb[i];
}

EXPORT void LagrangeHalfCPolynomialAddTo(
	LagrangeHalfCPolynomial* accum, 
	const LagrangeHalfCPolynomial* a) {
    LagrangeHalfCPolynomial_IMPL* result1 = (LagrangeHalfCPolynomial_IMPL*) accum;
    const int Ns2 = result1->proc->Ns2;
    cplx* aa = ((LagrangeHalfCPolynomial_IMPL*) a)->coefsC;
    cplx* rr = result1->coefsC;
    for (int i=0; i<Ns2; i++) 
	rr[i] += aa[i];
}    

