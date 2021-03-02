#pragma once

#include <xmmintrin.h>

template<int i>
inline __m128 shuf(__m128 v)
{
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(i, i, i, i));
}

void mul_mat4(const float* const A, const float* const B, float* C) 
{
	__m128 m[4];
	m[0] = _mm_load_ps(&A[12]);
	m[1] = _mm_load_ps(&A[8]);
	m[2] = _mm_load_ps(&A[4]);
	m[3] = _mm_load_ps(&A[0]);
	
	__m128 n[4];
	
	n[0] = _mm_load_ps(&B[0]);
	n[1] = _mm_load_ps(&B[4]);
	n[2] = _mm_load_ps(&B[8]);
	n[3] = _mm_load_ps(&B[12]);
	
	__m128 r[4];
	 r[0] =
		_mm_add_ps(
		  _mm_add_ps(
			_mm_mul_ps(m[0], shuf<3>(n[0])),
			_mm_mul_ps(m[1], shuf<2>(n[0]))),
		  _mm_add_ps(
			_mm_mul_ps(m[2], shuf<1>(n[0])),
			_mm_mul_ps(m[3], shuf<0>(n[0]))));

	  r[1] =
		_mm_add_ps(
		  _mm_add_ps(
			_mm_mul_ps(m[0], shuf<3>(n[1])),
			_mm_mul_ps(m[1], shuf<2>(n[1]))),
		  _mm_add_ps(
			_mm_mul_ps(m[2], shuf<1>(n[1])),
			_mm_mul_ps(m[3], shuf<0>(n[1]))));

	  r[2] =
		_mm_add_ps(
		  _mm_add_ps(
			_mm_mul_ps(m[0], shuf<3>(n[2])),
			_mm_mul_ps(m[1], shuf<2>(n[2]))),
		  _mm_add_ps(
			_mm_mul_ps(m[2], shuf<1>(n[2])),
			_mm_mul_ps(m[3], shuf<0>(n[2]))));

	  r[3] =
		_mm_add_ps(
		  _mm_add_ps(
			_mm_mul_ps(m[0], shuf<3>(n[3])),
			_mm_mul_ps(m[1], shuf<2>(n[3]))),
		  _mm_add_ps(
			_mm_mul_ps(m[2], shuf<1>(n[3])),
			_mm_mul_ps(m[3], shuf<0>(n[3]))));
		 
	_mm_store_ps(&C[0],  r[0]);
	_mm_store_ps(&C[4],  r[1]);
	_mm_store_ps(&C[8],  r[2]);
	_mm_store_ps(&C[12], r[3]);
}

void mul_mat4_vec4(const float* mat, const float* vec, float* out)
{
	__m128 v[4];
	v[0] = _mm_load_ps(&vec[0]);
	v[1] = _mm_load_ps(&vec[0]);
	v[2] = _mm_load_ps(&vec[0]);
	v[3] = _mm_load_ps(&vec[0]);
	
	__m128 m[4];
	m[0] = _mm_load_ps(&mat[0]);
	m[1] = _mm_load_ps(&mat[4]);
	m[2] = _mm_load_ps(&mat[8]);
	m[3] = _mm_load_ps(&mat[12]);
	
	__m128 v[0] = shuf<0>(v[0]);
	__m128 v[1] = shuf<1>(v[1]);
	__m128 v[2] = shuf<2>(v[2]);
	__m128 v[3] = shuf<3>(v[3]);

	__m128 m[0] = _mm_mul_ps(m[0], v[0]);
	__m128 m[1] = _mm_mul_ps(m[1], v[1]);
	__m128 m[2] = _mm_mul_ps(m[2], v[2]);
	__m128 m[3] = _mm_mul_ps(m[3], v[3]);
	
	__m128 r = _mm_add_ps(_mm_add_ps(m[0], m[1]), _mm_add_ps(m[2], m[3]));
	_mm_store_ps(out,  r);
}

void add_mat4(const float* mat1, const float* mat2, float* out)
{
	__m128 m1[4];
	m1[0] = _mm_load_ps(&mat1[0]);
	m1[1] = _mm_load_ps(&mat1[4]);
	m1[2] = _mm_load_ps(&mat1[8]);
	m1[3] = _mm_load_ps(&mat1[12]);
	
	__m128 m2[4];
	m2[0] = _mm_load_ps(&mat2[0]);
	m2[1] = _mm_load_ps(&mat2[4]);
	m2[2] = _mm_load_ps(&mat2[8]);
	m2[3] = _mm_load_ps(&mat2[12]);
	
	__m128 r[4];
	r[0] = _mm_add_ps(m1[0], m2[0]);
	r[1] = _mm_add_ps(m1[1], m2[1]);
	r[2] = _mm_add_ps(m1[2], m2[2]);
	r[3] = _mm_add_ps(m1[3], m2[3]);
	
	_mm_store_ps(&out[0],  r[0]);
	_mm_store_ps(&out[4],  r[1]);
	_mm_store_ps(&out[8],  r[2]);
	_mm_store_ps(&out[12], r[3]);
}

void sub_mat4(const float* mat1, const float* mat2, float* out)
{
	__m128 m1[4];
	m1[0] = _mm_load_ps(&mat1[0]);
	m1[1] = _mm_load_ps(&mat1[4]);
	m1[2] = _mm_load_ps(&mat1[8]);
	m1[3] = _mm_load_ps(&mat1[12]);
	
	__m128 m2[4];
	m2[0] = _mm_load_ps(&mat2[0]);
	m2[1] = _mm_load_ps(&mat2[4]);
	m2[2] = _mm_load_ps(&mat2[8]);
	m2[3] = _mm_load_ps(&mat2[12]);
	
	__m128 r[4];
	r[0] = _mm_sub_ps(m1[0], m2[0]);
	r[1] = _mm_sub_ps(m1[1], m2[1]);
	r[2] = _mm_sub_ps(m1[2], m2[2]);
	r[3] = _mm_sub_ps(m1[3], m2[3]);
	
	_mm_store_ps(&out[0],  r[0]);
	_mm_store_ps(&out[4],  r[1]);
	_mm_store_ps(&out[8],  r[2]);
	_mm_store_ps(&out[12], r[3]);
}