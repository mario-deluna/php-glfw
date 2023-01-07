#ifndef LINMATH_H
#define LINMATH_H

/**
 * Linmath 
 * Copyright (C) 2013 Wolfgang 'datenwolf' Draxinger <code@datenwolf.net>
 * Released under WTFPL license
 * 
 * Modified by Mario Döring
 */

#include <math.h>

#define LINMATH_H_DEFINE_VEC(n) \
typedef float vec##n[n]; \
static inline void vec##n##_add(vec##n r, vec##n const a, vec##n const b) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = a[i] + b[i]; \
} \
static inline void vec##n##_sub(vec##n r, vec##n const a, vec##n const b) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = a[i] - b[i]; \
} \
static inline void vec##n##_mul(vec##n r, vec##n const a, vec##n const b) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = a[i] * b[i]; \
} \
static inline void vec##n##_div(vec##n r, vec##n const a, vec##n const b) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = a[i] / b[i]; \
} \
static inline void vec##n##_scale(vec##n r, vec##n const v, float const s) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = v[i] * s; \
} \
static inline void vec##n##_s_add(vec##n r, vec##n const v, float const s) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = v[i] + s; \
} \
static inline void vec##n##_s_sub(vec##n r, vec##n const v, float const s) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = v[i] - s; \
} \
static inline void vec##n##_s_mul(vec##n r, vec##n const v, float const s) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = v[i] * s; \
} \
static inline void vec##n##_s_div(vec##n r, vec##n const v, float const s) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = v[i] / s; \
} \
static inline float vec##n##_mul_inner(vec##n const a, vec##n const b) \
{ \
	float p = 0.; \
	int i; \
	for(i=0; i<n; ++i) \
		p += b[i]*a[i]; \
	return p; \
} \
static inline float vec##n##_len(vec##n const v) \
{ \
	return sqrtf(vec##n##_mul_inner(v,v)); \
} \
static inline void vec##n##_norm(vec##n r, vec##n const v) \
{ \
	float k = 1.0 / vec##n##_len(v); \
	vec##n##_scale(r, v, k); \
} \
static inline void vec##n##_min(vec##n r, vec##n a, vec##n b) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = a[i]<b[i] ? a[i] : b[i]; \
} \
static inline void vec##n##_max(vec##n r, vec##n a, vec##n b) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = a[i]>b[i] ? a[i] : b[i]; \
} \
static inline float vec##n##_distance_square(vec##n const a, vec##n const b) \
{ \
	float d = 0.; \
	int i; \
	for(i=0; i<n; ++i) \
		d += (a[i] - b[i]) * (a[i] - b[i]); \
	return d; \
} \
static inline void vec##n##_abs(vec##n r, vec##n a) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = fabs(a[i]); \
} \
static inline void vec##n##_mix(vec##n r, vec##n a, vec##n b, float t) \
{ \
    int i; \
    for(i=0; i<n; ++i) \
        r[i] = a[i] + (b[i] - a[i]) * t; \
} \
static inline void vec##n##_lerp(vec##n r, vec##n a, vec##n b, float t) \
{ \
    vec##n##_mix(r, a, b, t); \
} \
static inline void vec##n##_slerp(vec##n r, vec##n a, vec##n b, float t) \
{ \
    float omega, cosom, sinom, scale0, scale1; \
    cosom = vec##n##_mul_inner(a, b); \
    if ((1.0 + cosom) > 0.000001) { \
        if ((1.0 - cosom) > 0.000001) { \
            omega = acos(cosom); \
            sinom = sin(omega); \
            scale0 = sin((1.0 - t) * omega) / sinom; \
            scale1 = sin(t * omega) / sinom; \
        } else { \
            scale0 = 1.0 - t; \
            scale1 = t; \
        } \
        int i; \
        for(i=0; i<n; ++i) \
            r[i] = scale0 * a[i] + scale1 * b[i]; \
    } else { \
        r[0] = -a[1]; \
        r[1] = a[0]; \
        r[2] = 0.0; \
        scale0 = sin((1.0 - t) * M_PI * 0.5); \
        scale1 = sin(t * M_PI * 0.5); \
        int i; \
        for(i=0; i<n; ++i) \
            r[i] = scale0 * a[i] + scale1 * r[i]; \
    } \
} \


LINMATH_H_DEFINE_VEC(2)
LINMATH_H_DEFINE_VEC(3)
LINMATH_H_DEFINE_VEC(4)

static inline void vec3_mul_cross(vec3 r, vec3 const a, vec3 const b)
{
	r[0] = a[1]*b[2] - a[2]*b[1];
	r[1] = a[2]*b[0] - a[0]*b[2];
	r[2] = a[0]*b[1] - a[1]*b[0];
}

static inline void vec3_reflect(vec3 r, vec3 const v, vec3 const n)
{
	float p  = 2.f*vec3_mul_inner(v, n);
	int i;
	for(i=0;i<3;++i)
		r[i] = v[i] - p*n[i];
}

static inline void vec4_mul_cross(vec4 r, vec4 a, vec4 b)
{
	r[0] = a[1]*b[2] - a[2]*b[1];
	r[1] = a[2]*b[0] - a[0]*b[2];
	r[2] = a[0]*b[1] - a[1]*b[0];
	r[3] = 1.f;
}

static inline void vec4_reflect(vec4 r, vec4 v, vec4 n)
{
	float p  = 2.f*vec4_mul_inner(v, n);
	int i;
	for(i=0;i<4;++i)
		r[i] = v[i] - p*n[i];
}

typedef vec4 mat4x4[4];
static inline void mat4x4_identity(mat4x4 M)
{
	int i, j;
	for(i=0; i<4; ++i)
		for(j=0; j<4; ++j)
			M[i][j] = i==j ? 1.f : 0.f;
}
static inline void mat4x4_dup(mat4x4 M, mat4x4 N)
{
	int i, j;
	for(i=0; i<4; ++i)
		for(j=0; j<4; ++j)
			M[i][j] = N[i][j];
}
static inline void mat4x4_row(vec4 r, mat4x4 M, int i)
{
	int k;
	for(k=0; k<4; ++k)
		r[k] = M[k][i];
}
static inline void mat4x4_col(vec4 r, mat4x4 M, int i)
{
	int k;
	for(k=0; k<4; ++k)
		r[k] = M[i][k];
}
static inline void mat4x4_transpose(mat4x4 M, mat4x4 N)
{
	int i, j;
	for(j=0; j<4; ++j)
		for(i=0; i<4; ++i)
			M[i][j] = N[j][i];
}
static inline void mat4x4_add(mat4x4 M, mat4x4 a, mat4x4 b)
{
	int i;
	for(i=0; i<4; ++i)
		vec4_add(M[i], a[i], b[i]);
}
static inline void mat4x4_sub(mat4x4 M, mat4x4 a, mat4x4 b)
{
	int i;
	for(i=0; i<4; ++i)
		vec4_sub(M[i], a[i], b[i]);
}
static inline void mat4x4_scale(mat4x4 M, mat4x4 a, float k)
{
	int i;
	for(i=0; i<4; ++i)
		vec4_scale(M[i], a[i], k);
}
static inline void mat4x4_scale_aniso(mat4x4 M, mat4x4 a, float x, float y, float z)
{
	int i;
	vec4_scale(M[0], a[0], x);
	vec4_scale(M[1], a[1], y);
	vec4_scale(M[2], a[2], z);
	for(i = 0; i < 4; ++i) {
		M[3][i] = a[3][i];
	}
}
static inline void mat4x4_mul(mat4x4 M, mat4x4 a, mat4x4 b)
{
	mat4x4 temp;
	int k, r, c;
	for(c=0; c<4; ++c) for(r=0; r<4; ++r) {
		temp[c][r] = 0.f;
		for(k=0; k<4; ++k)
			temp[c][r] += a[k][r] * b[c][k];
	}
	mat4x4_dup(M, temp);
}
static inline void mat4x4_mul_vec4(vec4 r, mat4x4 M, vec4 v)
{
	int i, j;
	for(j=0; j<4; ++j) {
		r[j] = 0.f;
		for(i=0; i<4; ++i)
			r[j] += M[i][j] * v[i];
	}
}
static inline void mat4x4_mul_vec3(vec3 r, mat4x4 M, vec3 v)
{
    vec4 v4 = {v[0], v[1], v[2], 1.0f};
    vec4 r4;
    mat4x4_mul_vec4(r4, M, v4);
    r[0] = r4[0];
    r[1] = r4[1];
    r[2] = r4[2];
}
static inline void mat4x4_translate(mat4x4 T, float x, float y, float z)
{
	mat4x4_identity(T);
	T[3][0] = x;
	T[3][1] = y;
	T[3][2] = z;
}
static inline void mat4x4_translate_in_place(mat4x4 M, float x, float y, float z)
{
	vec4 t = {x, y, z, 0};
	vec4 r;
	int i;
	for (i = 0; i < 4; ++i) {
		mat4x4_row(r, M, i);
		M[3][i] += vec4_mul_inner(r, t);
	}
}
static inline void mat4x4_from_vec3_mul_outer(mat4x4 M, vec3 a, vec3 b)
{
	int i, j;
	for(i=0; i<4; ++i) for(j=0; j<4; ++j)
		M[i][j] = i<3 && j<3 ? a[i] * b[j] : 0.f;
}
static inline void mat4x4_rotate(mat4x4 R, mat4x4 M, float x, float y, float z, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	vec3 u = {x, y, z};

	if(vec3_len(u) > 1e-4) {
		vec3_norm(u, u);
		mat4x4 T;
		mat4x4_from_vec3_mul_outer(T, u, u);

		mat4x4 S = {
			{    0,  u[2], -u[1], 0},
			{-u[2],     0,  u[0], 0},
			{ u[1], -u[0],     0, 0},
			{    0,     0,     0, 0}
		};
		mat4x4_scale(S, S, s);

		mat4x4 C;
		mat4x4_identity(C);
		mat4x4_sub(C, C, T);

		mat4x4_scale(C, C, c);

		mat4x4_add(T, T, C);
		mat4x4_add(T, T, S);

		T[3][3] = 1.;		
		mat4x4_mul(R, M, T);
	} else {
		mat4x4_dup(R, M);
	}
}
static inline void mat4x4_rotate_X(mat4x4 Q, mat4x4 M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	mat4x4 R = {
		{1.f, 0.f, 0.f, 0.f},
		{0.f,   c,   s, 0.f},
		{0.f,  -s,   c, 0.f},
		{0.f, 0.f, 0.f, 1.f}
	};
	mat4x4_mul(Q, M, R);
}
static inline void mat4x4_rotate_Y(mat4x4 Q, mat4x4 M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	mat4x4 R = {
		{   c, 0.f,   s, 0.f},
		{ 0.f, 1.f, 0.f, 0.f},
		{  -s, 0.f,   c, 0.f},
		{ 0.f, 0.f, 0.f, 1.f}
	};
	mat4x4_mul(Q, M, R);
}
static inline void mat4x4_rotate_Z(mat4x4 Q, mat4x4 M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	mat4x4 R = {
		{   c,   s, 0.f, 0.f},
		{  -s,   c, 0.f, 0.f},
		{ 0.f, 0.f, 1.f, 0.f},
		{ 0.f, 0.f, 0.f, 1.f}
	};
	mat4x4_mul(Q, M, R);
}
static inline void mat4x4_invert(mat4x4 T, mat4x4 M)
{
	float s[6];
	float c[6];
	s[0] = M[0][0]*M[1][1] - M[1][0]*M[0][1];
	s[1] = M[0][0]*M[1][2] - M[1][0]*M[0][2];
	s[2] = M[0][0]*M[1][3] - M[1][0]*M[0][3];
	s[3] = M[0][1]*M[1][2] - M[1][1]*M[0][2];
	s[4] = M[0][1]*M[1][3] - M[1][1]*M[0][3];
	s[5] = M[0][2]*M[1][3] - M[1][2]*M[0][3];

	c[0] = M[2][0]*M[3][1] - M[3][0]*M[2][1];
	c[1] = M[2][0]*M[3][2] - M[3][0]*M[2][2];
	c[2] = M[2][0]*M[3][3] - M[3][0]*M[2][3];
	c[3] = M[2][1]*M[3][2] - M[3][1]*M[2][2];
	c[4] = M[2][1]*M[3][3] - M[3][1]*M[2][3];
	c[5] = M[2][2]*M[3][3] - M[3][2]*M[2][3];
	
	/* Assumes it is invertible */
	float idet = 1.0f/( s[0]*c[5]-s[1]*c[4]+s[2]*c[3]+s[3]*c[2]-s[4]*c[1]+s[5]*c[0] );
	
	T[0][0] = ( M[1][1] * c[5] - M[1][2] * c[4] + M[1][3] * c[3]) * idet;
	T[0][1] = (-M[0][1] * c[5] + M[0][2] * c[4] - M[0][3] * c[3]) * idet;
	T[0][2] = ( M[3][1] * s[5] - M[3][2] * s[4] + M[3][3] * s[3]) * idet;
	T[0][3] = (-M[2][1] * s[5] + M[2][2] * s[4] - M[2][3] * s[3]) * idet;

	T[1][0] = (-M[1][0] * c[5] + M[1][2] * c[2] - M[1][3] * c[1]) * idet;
	T[1][1] = ( M[0][0] * c[5] - M[0][2] * c[2] + M[0][3] * c[1]) * idet;
	T[1][2] = (-M[3][0] * s[5] + M[3][2] * s[2] - M[3][3] * s[1]) * idet;
	T[1][3] = ( M[2][0] * s[5] - M[2][2] * s[2] + M[2][3] * s[1]) * idet;

	T[2][0] = ( M[1][0] * c[4] - M[1][1] * c[2] + M[1][3] * c[0]) * idet;
	T[2][1] = (-M[0][0] * c[4] + M[0][1] * c[2] - M[0][3] * c[0]) * idet;
	T[2][2] = ( M[3][0] * s[4] - M[3][1] * s[2] + M[3][3] * s[0]) * idet;
	T[2][3] = (-M[2][0] * s[4] + M[2][1] * s[2] - M[2][3] * s[0]) * idet;

	T[3][0] = (-M[1][0] * c[3] + M[1][1] * c[1] - M[1][2] * c[0]) * idet;
	T[3][1] = ( M[0][0] * c[3] - M[0][1] * c[1] + M[0][2] * c[0]) * idet;
	T[3][2] = (-M[3][0] * s[3] + M[3][1] * s[1] - M[3][2] * s[0]) * idet;
	T[3][3] = ( M[2][0] * s[3] - M[2][1] * s[1] + M[2][2] * s[0]) * idet;
}
static inline void mat4x4_orthonormalize(mat4x4 R, mat4x4 M)
{
	mat4x4_dup(R, M);
	float s = 1.;
	vec3 h;

	vec3_norm(R[2], R[2]);
	
	s = vec3_mul_inner(R[1], R[2]);
	vec3_scale(h, R[2], s);
	vec3_sub(R[1], R[1], h);
	vec3_norm(R[2], R[2]);

	s = vec3_mul_inner(R[1], R[2]);
	vec3_scale(h, R[2], s);
	vec3_sub(R[1], R[1], h);
	vec3_norm(R[1], R[1]);

	s = vec3_mul_inner(R[0], R[1]);
	vec3_scale(h, R[1], s);
	vec3_sub(R[0], R[0], h);
	vec3_norm(R[0], R[0]);
}

static inline void mat4x4_frustum(mat4x4 M, float l, float r, float b, float t, float n, float f)
{
	M[0][0] = 2.f*n/(r-l);
	M[0][1] = M[0][2] = M[0][3] = 0.f;
	
	M[1][1] = 2.*n/(t-b);
	M[1][0] = M[1][2] = M[1][3] = 0.f;

	M[2][0] = (r+l)/(r-l);
	M[2][1] = (t+b)/(t-b);
	M[2][2] = -(f+n)/(f-n);
	M[2][3] = -1.f;
	
	M[3][2] = -2.f*(f*n)/(f-n);
	M[3][0] = M[3][1] = M[3][3] = 0.f;
}
static inline void mat4x4_ortho(mat4x4 M, float l, float r, float b, float t, float n, float f)
{
	M[0][0] = 2.f/(r-l);
	M[0][1] = M[0][2] = M[0][3] = 0.f;

	M[1][1] = 2.f/(t-b);
	M[1][0] = M[1][2] = M[1][3] = 0.f;

	M[2][2] = -2.f/(f-n);
	M[2][0] = M[2][1] = M[2][3] = 0.f;
	
	M[3][0] = -(r+l)/(r-l);
	M[3][1] = -(t+b)/(t-b);
	M[3][2] = -(f+n)/(f-n);
	M[3][3] = 1.f;
}
static inline void mat4x4_perspective(mat4x4 m, float y_fov, float aspect, float n, float f)
{
	/* NOTE: Degrees are an unhandy unit to work with.
	 * linmath.h uses radians for everything! */
	float const a = 1.f / tan(y_fov / 2.f);

	m[0][0] = a / aspect;
	m[0][1] = 0.f;
	m[0][2] = 0.f;
	m[0][3] = 0.f;

	m[1][0] = 0.f;
	m[1][1] = a;
	m[1][2] = 0.f;
	m[1][3] = 0.f;

	m[2][0] = 0.f;
	m[2][1] = 0.f;
	m[2][2] = -((f + n) / (f - n));
	m[2][3] = -1.f;

	m[3][0] = 0.f;
	m[3][1] = 0.f;
	m[3][2] = -((2.f * f * n) / (f - n));
	m[3][3] = 0.f;
}
static inline void mat4x4_look_at(mat4x4 m, vec3 eye, vec3 center, vec3 up)
{
	/* Adapted from Android's OpenGL Matrix.java.                        */
	/* See the OpenGL GLUT documentation for gluLookAt for a description */
	/* of the algorithm. We implement it in a straightforward way:       */

	/* TODO: The negation of of can be spared by swapping the order of
	 *       operands in the following cross products in the right way. */
	vec3 f;
	vec3_sub(f, center, eye);	
	vec3_norm(f, f);	
	
	vec3 s;
	vec3_mul_cross(s, f, up);
	vec3_norm(s, s);

	vec3 t;
	vec3_mul_cross(t, s, f);

	m[0][0] =  s[0];
	m[0][1] =  t[0];
	m[0][2] = -f[0];
	m[0][3] =   0.f;

	m[1][0] =  s[1];
	m[1][1] =  t[1];
	m[1][2] = -f[1];
	m[1][3] =   0.f;

	m[2][0] =  s[2];
	m[2][1] =  t[2];
	m[2][2] = -f[2];
	m[2][3] =   0.f;

	m[3][0] =  0.f;
	m[3][1] =  0.f;
	m[3][2] =  0.f;
	m[3][3] =  1.f;

	mat4x4_translate_in_place(m, -eye[0], -eye[1], -eye[2]);
}

static inline float mat4x4_det(mat4x4 M)
{
	float a = M[0][0]*M[1][1] - M[0][1]*M[1][0];
	float b = M[0][0]*M[1][2] - M[0][2]*M[1][0];
	float c = M[0][0]*M[1][3] - M[0][3]*M[1][0];
	float d = M[0][1]*M[1][2] - M[0][2]*M[1][1];
	float e = M[0][1]*M[1][3] - M[0][3]*M[1][1];
	float f = M[0][2]*M[1][3] - M[0][3]*M[1][2];
	float g = M[2][0]*M[3][1] - M[2][1]*M[3][0];
	float h = M[2][0]*M[3][2] - M[2][2]*M[3][0];
	float i = M[2][0]*M[3][3] - M[2][3]*M[3][0];
	float j = M[2][1]*M[3][2] - M[2][2]*M[3][1];
	float k = M[2][1]*M[3][3] - M[2][3]*M[3][1];
	float l = M[2][2]*M[3][3] - M[2][3]*M[3][2];
	
	return a*l - b*k + c*j + d*i - e*h + f*g;
}

typedef float quat[4];
static inline void quat_identity(quat q)
{
	q[1] = q[2] = q[3] = 0.f;
	q[0] = 1.f;
}
static inline void quat_add(quat r, quat a, quat b)
{
	int i;
	for(i=0; i<4; ++i)
		r[i] = a[i] + b[i];
}
static inline void quat_sub(quat r, quat a, quat b)
{
	int i;
	for(i=0; i<4; ++i)
		r[i] = a[i] - b[i];
}
static inline void quat_mul(quat r, quat p, quat q)
{
    r[0] = p[0]*q[0] - p[1]*q[1] - p[2]*q[2] - p[3]*q[3];
    r[1] = p[0]*q[1] + p[1]*q[0] + p[2]*q[3] - p[3]*q[2];
    r[2] = p[0]*q[2] + p[2]*q[0] + p[3]*q[1] - p[1]*q[3];
    r[3] = p[0]*q[3] + p[3]*q[0] + p[1]*q[2] - p[2]*q[1];
}
static inline void quat_mul_scalar(quat r, quat q, float s)
{
    int i;
    for(i=0; i<4; ++i)
        r[i] = q[i] * s;
}
static inline void quat_div_scalar(quat r, quat p, float s)
{
    int i;
    for(i=0; i<4; ++i)
        r[i] = p[i] / s;
}
static inline float quat_len(quat q)
{
    return sqrtf(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
}
static inline float quat_len2(quat q)
{
    return q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3];
}

static inline void quat_scale(quat r, quat v, float s)
{
	int i;
	for(i=0; i<4; ++i)
		r[i] = v[i] * s;
}
static inline float quat_inner_product(quat a, quat b)
{
	float p = 0.f;
	int i;
	for(i=0; i<4; ++i)
		p += b[i]*a[i];
	return p;
}
static inline void quat_conj(quat r, quat q)
{
    r[0] =  q[0];
    r[1] = -q[1];
    r[2] = -q[2];
    r[3] = -q[3];
}
static inline float quat_dot(quat a, quat b)
{
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3];
}
static inline void quat_slerp(quat r, quat a, quat b, float t)
{
    float cosTheta = quat_dot(a, b);
    if(cosTheta < 0.f)
    {
        cosTheta = -cosTheta;
        b[0] = -b[0];
        b[1] = -b[1];
        b[2] = -b[2];
        b[3] = -b[3];
    }
    if(cosTheta > 1.f - 1e-6f)
    {
        r[0] = a[0] + t * (b[0] - a[0]);
        r[1] = a[1] + t * (b[1] - a[1]);
        r[2] = a[2] + t * (b[2] - a[2]);
        r[3] = a[3] + t * (b[3] - a[3]);
    }
    else
    {
        float angle = acosf(cosTheta);
        float sinTheta = sinf(angle);
        float a0 = sinf((1.f - t) * angle) / sinTheta;
        float b0 = sinf(t * angle) / sinTheta;
        r[0] = a0 * a[0] + b0 * b[0];
        r[1] = a0 * a[1] + b0 * b[1];
        r[2] = a0 * a[2] + b0 * b[2];
        r[3] = a0 * a[3] + b0 * b[3];
    }
}
static inline void quat_inverse(quat r, quat q)
{
    float d = quat_inner_product(q, q); 
    r[0] =  q[0] / d;
    r[1] = -q[1] / d;
    r[2] = -q[2] / d;
    r[3] = -q[3] / d;
}
static inline void quat_rotate(quat r, float angle, vec3 axis) {
    float half_angle = angle * 0.5f;
    float s = sinf(half_angle);
    r[0] = cosf(half_angle);
    r[1] = axis[0] * s;
    r[2] = axis[1] * s;
    r[3] = axis[2] * s;
}
static inline void quat_rotate_by(quat r, quat q, float angle, vec3 axis) {
    quat p;
    quat_rotate(p, angle, axis);
    quat_mul(r, q, p);
}
static inline void quat_euler_angles(vec3 r, quat q)
{
    // roll (x-axis rotation)
    double sinr_cosp = 2 * (q[0] * q[1] + q[2] * q[3]);
    double cosr_cosp = 1 - 2 * (q[1] * q[1] + q[2] * q[2]);
    r[0] = atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = 2 * (q[0] * q[2] - q[3] * q[1]);
    if (fabs(sinp) >= 1)
        r[1] = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        r[1] = asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (q[0] * q[3] + q[1] * q[2]);
    double cosy_cosp = 1 - 2 * (q[2] * q[2] + q[3] * q[3]);
    r[2] = atan2(siny_cosp, cosy_cosp);
}
#define quat_norm vec4_norm
#define quat_mix vec4_mix
#define quat_lerp vec4_lerp
static inline void quat_mul_vec3(vec3 r, quat q, vec3 v)
{
    /**
     * Method by Fabian 'ryg' Giessen (of Farbrausch)
     * t = 2 * cross(q.xyz, v)
     * v' = v + q.w * t + cross(q.xyz, t)
     */
    // rotates a vector by a quaternion
    // r = quat * vec3
    vec3 t;
    vec3 q_xyz = {q[1], q[2], q[3]};
    vec3 u = {q[1], q[2], q[3]};
    vec3_mul_cross(t, q_xyz, v);
    vec3_scale(t, t, 2);
    vec3_mul_cross(u, q_xyz, t);
    vec3_scale(t, t, q[0]);
    vec3_add(r, v, t);
    vec3_add(r, r, u);
}
static inline void vec3_mul_quat(vec3 r, vec3 v, quat q)
{
    // we copy the behavior of the GLM library here
    // meaing that we do the inverse quaternion
    // r = vec3 * quat
    quat q_inv;
    quat_inverse(q_inv, q);
    quat_mul_vec3(r, q_inv, v);
}
static inline void mat4x4_from_quat(mat4x4 M, quat q)
{   
    // this is basically a direct port of the code from the GLM library
    float qxx = q[1] * q[1];
    float qyy = q[2] * q[2];
    float qzz = q[3] * q[3];
    float qxz = q[1] * q[3];
    float qxy = q[1] * q[2];
    float qyz = q[2] * q[3];
    float qwx = q[0] * q[1];
    float qwy = q[0] * q[2];
    float qwz = q[0] * q[3];

    M[0][0] = 1.f - 2.f * (qyy +  qzz);
    M[0][1] = 2.f * (qxy + qwz);
    M[0][2] = 2.f * (qxz - qwy);
    M[0][3] = 0.f;

    M[1][0] = 2.f * (qxy - qwz);
    M[1][1] = 1.f - 2.f * (qxx +  qzz);
    M[1][2] = 2.f * (qyz + qwx);

    M[2][0] = 2.f * (qxz + qwy);
    M[2][1] = 2.f * (qyz - qwx);
    M[2][2] = 1.f - 2.f * (qxx +  qyy);
    M[2][3] = 0.f;
}

static inline void mat4x4o_mul_quat(mat4x4 R, mat4x4 M, quat q)
{
/*  XXX: The way this is written only works for othogonal matrices. */
/* TODO: Take care of non-orthogonal case. */
	quat_mul_vec3(R[0], q, M[0]);
	quat_mul_vec3(R[1], q, M[1]);
	quat_mul_vec3(R[2], q, M[2]);

	R[3][0] = R[3][1] = R[3][2] = 0.f;
	R[3][3] = 1.f;
}
static inline void quat_from_mat4x4(quat q, mat4x4 M)
{
    //  this again is basically a direct port of the code from the GLM library
    float fourXSquaredMinus1 = M[0][0] - M[1][1] - M[2][2];
    float fourYSquaredMinus1 = M[1][1] - M[0][0] - M[2][2];
    float fourZSquaredMinus1 = M[2][2] - M[0][0] - M[1][1];
    float fourWSquaredMinus1 = M[0][0] + M[1][1] + M[2][2];

    int biggestIndex = 0;
    float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
    if(fourXSquaredMinus1 > fourBiggestSquaredMinus1)
    {
        fourBiggestSquaredMinus1 = fourXSquaredMinus1;
        biggestIndex = 1;
    }
    if(fourYSquaredMinus1 > fourBiggestSquaredMinus1)
    {
        fourBiggestSquaredMinus1 = fourYSquaredMinus1;
        biggestIndex = 2;
    }
    if(fourZSquaredMinus1 > fourBiggestSquaredMinus1)
    {
        fourBiggestSquaredMinus1 = fourZSquaredMinus1;
        biggestIndex = 3;
    }

    float biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.f) * 0.5f;
    float mult = 0.25f / biggestVal;

    switch(biggestIndex)
    {
    case 0:
        q[0] = biggestVal;
        q[1] = (M[1][2] - M[2][1]) * mult;
        q[2] = (M[2][0] - M[0][2]) * mult;
        q[3] = (M[0][1] - M[1][0]) * mult;
        break;
    case 1:
        q[0] = (M[1][2] - M[2][1]) * mult;
        q[1] = biggestVal;
        q[2] = (M[0][1] + M[1][0]) * mult;
        q[3] = (M[2][0] + M[0][2]) * mult;
        break;
    case 2:
        q[0] = (M[2][0] - M[0][2]) * mult;
        q[1] = (M[0][1] + M[1][0]) * mult;
        q[2] = biggestVal;
        q[3] = (M[1][2] + M[2][1]) * mult;
        break;
    case 3:
        q[0] = (M[0][1] - M[1][0]) * mult;
        q[1] = (M[2][0] + M[0][2]) * mult;
        q[2] = (M[1][2] + M[2][1]) * mult;
        q[3] = biggestVal;
        break;
    default: 
        q[0] = 1;
        q[1] = 0;
        q[2] = 0;
        q[3] = 0;
        break;
    }
}

#endif