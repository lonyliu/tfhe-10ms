#ifndef LAGRANGEHALFC_ARITHMETIC_H
#define LAGRANGEHALFC_ARITHMETIC_H

///@file
///@brief This file contains the declaration of operations on LagrangeHalfC polynomials

#include "polynomials.h"

//initialize the LagrangeHalfCPolynomial structure
//(equivalent of the C++ constructor)
EXPORT void init_LagrangeHalfCPolynomial(LagrangeHalfCPolynomial* obj, const int N);

//destroys the LagrangeHalfCPolynomial structure
//(equivalent of the C++ destructor)
EXPORT void destroy_LagrangeHalfCPolynomial(LagrangeHalfCPolynomial* obj);


/**
 * FFT functions 
 */
EXPORT void IntPolynomial_ifft(LagrangeHalfCPolynomial* result, const IntPolynomial* p);
EXPORT void TorusPolynomial_ifft(LagrangeHalfCPolynomial* result, const TorusPolynomial* p);
EXPORT void TorusPolynomial_fft(TorusPolynomial* result, const LagrangeHalfCPolynomial* p);

//MISC OPERATIONS
/** sets to zero */
EXPORT void LagrangeHalfCPolynomialClear(LagrangeHalfCPolynomial* result);

/** sets to this torus32 constant */
EXPORT void LagrangeHalfCPolynomialSetTorusConstant(LagrangeHalfCPolynomial* result, const Torus32 mu);
EXPORT void LagrangeHalfCPolynomialAddTorusConstant(LagrangeHalfCPolynomial* result, const Torus32 cst);
EXPORT void LagrangeHalfCPolynomialAddTorusConstant2(LagrangeHalfCPolynomial* result, LagrangeHalfCPolynomial* result2);
// /* sets to X^ai-1 */
//This function is commented, because it is not used 
//in the current version. However, it may be included in future releases
EXPORT void LagrangeHalfCPolynomialSetXai(LagrangeHalfCPolynomial* result, const int ai);


/** multiplication via direct FFT */
EXPORT void torusPolynomialMultFFT(TorusPolynomial* result, const IntPolynomial* poly1, const TorusPolynomial* poly2);
EXPORT void torusPolynomialAddMulRFFT(TorusPolynomial* result, const IntPolynomial* poly1, const TorusPolynomial* poly2);
EXPORT void torusPolynomialSubMulRFFT(TorusPolynomial* result, const IntPolynomial* poly1, const TorusPolynomial* poly2);

/** termwise multiplication in Lagrange space */
EXPORT void LagrangeHalfCPolynomialMul(
	LagrangeHalfCPolynomial* result, 
	const LagrangeHalfCPolynomial* a, 
	const LagrangeHalfCPolynomial* b);
/** termwise multiplication in Lagrange space */
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
);
/** termwise multiplication and addTo in Lagrange space */
EXPORT void LagrangeHalfCPolynomialAddTo(
	LagrangeHalfCPolynomial* accum, 
	const LagrangeHalfCPolynomial* a);

EXPORT void LagrangeHalfCPolynomialAddMul(
	LagrangeHalfCPolynomial* accum, 
	const LagrangeHalfCPolynomial* a, 
	const LagrangeHalfCPolynomial* b);

EXPORT void LagrangeHalfCPolynomialSubMul(
	LagrangeHalfCPolynomial* accum, 
	const LagrangeHalfCPolynomial* a, 
	const LagrangeHalfCPolynomial* b);

#endif // LAGRANGEHALFC_ARITHMETIC_H
