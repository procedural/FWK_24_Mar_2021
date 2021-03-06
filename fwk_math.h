// math framework
// - rlyeh, public domain
//
// Credits: @ands+@krig+@vurtun (PD), @datenwolf (WTFPL2), @evanw+@barerose (CC0), @sgorsten (Unlicense).

#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <float.h>
#include <stdint.h>
#include <stdbool.h>

#define C_EPSILON  (1e-6)
#define C_PI       (3.141592654f) // (3.14159265358979323846f)
#define TO_RAD     (C_PI/180.f)
#define TO_DEG     (180.f/C_PI)

#if defined(_MSC_VER) && !defined(__cplusplus)
#define m_inline __inline
#else
#define m_inline inline
#endif

#if defined(_MSC_VER) && (_MSC_VER <= 1700)
#define m_finite _finite
#else
#define m_finite isfinite
#endif

#ifdef __cplusplus
#define M_CAST(type, ...)  ( type { __VA_ARGS__ } )
#else
#define M_CAST(type, ...)  ((type){ __VA_ARGS__ } )
#endif

// ----------------------------------------------------------------------------

static m_inline float ease_linear(float t) { return t; }

static m_inline float ease_out_sine(float t) { return sinf(t*(C_PI*0.5f)); }
static m_inline float ease_out_quad(float t) { return -(t*(t-2)); }
static m_inline float ease_out_cubic(float t) { float f=t-1; return f*f*f+1; }
static m_inline float ease_out_quart(float t) { float f=t-1; return f*f*f*(1-t)+1; }
static m_inline float ease_out_quint(float t) { float f=(t-1); return f*f*f*f*f+1; }
static m_inline float ease_out_expo(float t) { return (t >= 1) ? t : 1-powf(2,-10*t); }
static m_inline float ease_out_circ(float t) { return sqrtf((2-t)*t); }
static m_inline float ease_out_back(float t) { float f=1-t; return 1-(f*f*f-f*sinf(f*C_PI)); }
static m_inline float ease_out_elastic(float t) { return sinf(-13*(C_PI*0.5f)*(t+1))*powf(2,-10*t)+1; }
static m_inline float ease_out_bounce(float t) { return (t < 4.f/11) ? (121.f*t*t)/16 : (t < 8.f/11) ? (363.f/40*t*t)-(99.f/10*t)+17.f/5 : (t < 9.f/10) ? (4356.f/361*t*t)-(35442.f/1805*t)+16061.f/1805 : (54.f/5*t*t)-(513.f/25*t)+268.f/25; }

static m_inline float ease_in_sine(float t) { return 1+sinf((t-1)*(C_PI*0.5f)); }
static m_inline float ease_in_quad(float t) { return t*t; }
static m_inline float ease_in_cubic(float t) { return t*t*t; }
static m_inline float ease_in_quart(float t) { return t*t*t*t; }
static m_inline float ease_in_quint(float t) { return t*t*t*t*t; }
static m_inline float ease_in_expo(float t) { return (t <= 0) ? t : powf(2,10*(t-1)); }
static m_inline float ease_in_circ(float t) { return 1-sqrtf(1-(t*t)); }
static m_inline float ease_in_back(float t) { return t*t*t-t*sinf(t*C_PI); }
static m_inline float ease_in_elastic(float t) { return sinf(13*(C_PI*0.5f)*t)*powf(2,10*(t-1)); }
static m_inline float ease_in_bounce(float t) { return 1-ease_out_bounce(1-t); }

static m_inline float ease_inout_sine(float t) { return 0.5f*(1-cosf(t*C_PI)); }
static m_inline float ease_inout_quad(float t) { return (t < 0.5f) ? 2*t*t : (-2*t*t)+(4*t)-1; }
static m_inline float ease_inout_cubic(float t) { float f; return (t < 0.5f) ? 4*t*t*t : (f=(2*t)-2,0.5f*f*f*f+1); }
static m_inline float ease_inout_quart(float t) { float f; return (t < 0.5f) ? 8*t*t*t*t : (f=(t-1),-8*f*f*f*f+1); }
static m_inline float ease_inout_quint(float t) { float f; return (t < 0.5f) ? 16*t*t*t*t*t : (f=((2*t)-2),0.5f*f*f*f*f*f+1); }
static m_inline float ease_inout_expo(float t) { return (t <= 0 || t >= 1) ? t : t < 0.5f ? 0.5f*powf(2,(20*t)-10) : -0.5f*powf(2,(-20*t)+10)+1; }
static m_inline float ease_inout_circ(float t) { return t < 0.5f ? 0.5f*(1-sqrtf(1-4*(t*t))) : 0.5f*(sqrtf(-((2*t)-3)*((2*t)-1))+1); }
static m_inline float ease_inout_back(float t) { float f; return t < 0.5f ? (f=2*t,0.5f*(f*f*f-f*sinf(f*C_PI))) : (f=(1-(2*t-1)),0.5f*(1-(f*f*f-f*sinf(f*C_PI)))+0.5f); }
static m_inline float ease_inout_elastic(float t) { return t < 0.5f ? 0.5f*sinf(13*(C_PI*0.5f)*(2*t))*powf(2,10*((2*t)-1)) : 0.5f*(sinf(-13*(C_PI*0.5f)*((2*t-1)+1))*powf(2,-10*(2*t-1))+2); }
static m_inline float ease_inout_bounce(float t) { return t < 0.5f ? 0.5f*ease_in_bounce(t*2) : 0.5f*ease_out_bounce(t*2-1)+0.5f; }

static m_inline float ease_perlin_inout(float t) { float t3=t*t*t,t4=t3*t,t5=t4*t; return 6*t5-15*t4+10*t3; }

static m_inline float ease_ping_pong(float t, float(*fn1)(float), float(*fn2)(float)) { return t < 0.5 ? fn1(t*2) : 1-fn2((t-0.5)*2); }
static m_inline float ease_pong_ping(float t, float(*fn1)(float), float(*fn2)(float)) { return 1 - ease_ping_pong(t,fn1,fn2); }

// ----------------------------------------------------------------------------

#define ptr(type)         0[&(type).x]
#define vec2(x, y      )  M_CAST(vec2, (float)(x), (float)(y)                        )
#define vec3(x, y, z   )  M_CAST(vec3, (float)(x), (float)(y), (float)(z),           )
#define vec4(x, y, z, w)  M_CAST(vec4, (float)(x), (float)(y), (float)(z), (float)(w))
#define quat(x, y, z, w)  M_CAST(quat, (float)(x), (float)(y), (float)(z), (float)(w))
#define axis(x, y, z)     M_CAST(axis, (float)(x), (float)(y), (float)(z))
#define mat33(...)        M_CAST(mat33, __VA_ARGS__ )
#define mat34(...)        M_CAST(mat34, __VA_ARGS__ )
#define mat44(...)        M_CAST(mat44, __VA_ARGS__ )
#define coord_system(...) M_CAST(coord_system, __VA_ARGS__)

typedef union vec2 { struct { float x,y; }; struct { float r,g; }; struct { float w,h; }; float v[1]; } vec2;
typedef union vec3 { struct { float x,y,z; }; struct { float r,g,b; }; struct { float w,h,d; }; vec2 xy; vec2 rg; vec2 wh; float v[1]; } vec3;
typedef union vec4 { struct { float x,y,z,w; }; struct { float r,g,b,a; }; vec2 xy; vec3 xyz; vec2 rg; vec3 rgb; vec2 wh; vec3 whd; float v[1]; } vec4;
typedef union quat { struct { float x,y,z,w; }; vec3 xyz; vec4 xyzw; float v[1]; } quat;
typedef float mat33[9];
typedef float mat34[12];
typedef float mat44[16];

// A value type representing an abstract direction vector in 3D space, independent of any coordinate system.
// A concrete 3D coordinate system with defined x, y, and z axes.
typedef enum { axis_front, axis_back, axis_left, axis_right, axis_up, axis_down } coord_axis;
typedef union coord_system { struct { coord_axis x,y,z; }; } coord_system;

// ----------------------------------------------------------------------------

static m_inline float deg      (float radians)      { return radians / C_PI * 180.0f; }
static m_inline float rad      (float degrees)      { return degrees * C_PI / 180.0f; }

static m_inline int   mini     (int    a, int    b) { return a < b ? a : b; }
static m_inline int   maxi     (int    a, int    b) { return a > b ? a : b; }
static m_inline int   absi     (int    a          ) { return a < 0 ? -a : a; }
static m_inline float minf     (float  a, float  b) { return a < b ? a : b; }
static m_inline float maxf     (float  a, float  b) { return a > b ? a : b; }
static m_inline float absf     (float  a          ) { return a < 0.0f ? -a : a; }
static m_inline float pmodf    (float  a, float  b) { return (a < 0.0f ? 1.0f : 0.0f) + (float)fmod(a, b); } // positive mod
static m_inline float signf    (float  a)           { return (a < 0) ? -1.f : 1.f; }
static m_inline float clampf(float v,float a,float b){return maxf(minf(b,v),a); }
static m_inline float mixf(float a,float b,float t) { return a*(1-t)+b*t; }

// ----------------------------------------------------------------------------

static m_inline vec2  ptr2     (const float *a    ) { return vec2(a[0],a[1]); }
//
static m_inline vec2  neg2     (vec2   a          ) { return vec2(-a.x, -a.y); }
static m_inline vec2  add2     (vec2   a, vec2   b) { return vec2(a.x + b.x, a.y + b.y); }
static m_inline vec2  sub2     (vec2   a, vec2   b) { return vec2(a.x - b.x, a.y - b.y); }
static m_inline vec2  mul2     (vec2   a, vec2   b) { return vec2(a.x * b.x, a.y * b.y); }
static m_inline vec2  inc2     (vec2   a, float  b) { return vec2(a.x + b, a.y + b); }
static m_inline vec2  dec2     (vec2   a, float  b) { return vec2(a.x - b, a.y - b); }
static m_inline vec2  scale2   (vec2   a, float  b) { return vec2(a.x * b, a.y * b); }
static m_inline vec2  div2     (vec2   a, float  b) { return scale2(a, b ? 1/b : 0.f); }
static m_inline vec2  pmod2    (vec2   a, float  b) { return vec2(pmodf(a.x, b), pmodf(a.y, b)); }
static m_inline vec2  min2     (vec2   a, vec2   b) { return vec2(minf(a.x, b.x), minf(a.y, b.y)); }
static m_inline vec2  max2     (vec2   a, vec2   b) { return vec2(maxf(a.x, b.x), maxf(a.y, b.y)); }
static m_inline vec2  abs2     (vec2   a          ) { return vec2(absf(a.x), absf(a.y)); }
static m_inline vec2  floor2   (vec2   a          ) { return vec2(floorf(a.x), floorf(a.y)); }
static m_inline vec2  ceil2    (vec2   a          ) { return vec2(ceilf (a.x), ceilf (a.y)); }
static m_inline float dot2     (vec2   a, vec2   b) { return a.x * b.x + a.y * b.y; }
static m_inline vec2  refl2    (vec2   a, vec2   b) { return sub2(a, scale2(b, 2*dot2(a,b))); }
static m_inline float cross2   (vec2   a, vec2   b) { return a.x * b.y - a.y * b.x; } // pseudo cross product
static m_inline float len2sq   (vec2   a          ) { return a.x * a.x + a.y * a.y; }
static m_inline float len2     (vec2   a          ) { return sqrtf(len2sq(a)); }
static m_inline vec2  norm2    (vec2   a          ) { return /*dot(2) == 0 ? a :*/ div2(a, len2(a)); }
static m_inline int   finite2  (vec2   a          ) { return m_finite(a.x) && m_finite(a.y); }
static m_inline vec2  mix2  (vec2 a,vec2 b,float t) { return add2(scale2((a),1-(t)), scale2((b), t)); }
// ----------------------------------------------------------------------------

static m_inline vec3  ptr3     (const float *a    ) { return vec3(a[0],a[1],a[2]); }
static m_inline vec3  vec23    (vec2   a, float z ) { return vec3(a.x,a.y,z); }
//
static m_inline vec3  neg3     (vec3   a          ) { return vec3(-a.x, -a.y, -a.z); }
static m_inline vec3  add3     (vec3   a, vec3   b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
static m_inline vec3  sub3     (vec3   a, vec3   b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
static m_inline vec3  mul3     (vec3   a, vec3   b) { return vec3(a.x * b.x, a.y * b.y, a.z * b.z); }
static m_inline vec3  inc3     (vec3   a, float  b) { return vec3(a.x + b, a.y + b, a.z + b); }
static m_inline vec3  dec3     (vec3   a, float  b) { return vec3(a.x - b, a.y - b, a.z - b); }
static m_inline vec3  scale3   (vec3   a, float  b) { return vec3(a.x * b, a.y * b, a.z * b); }
static m_inline vec3  div3     (vec3   a, float  b) { return scale3(a, b ? 1/b : 0.f); }
static m_inline vec3  pmod3    (vec3   a, float  b) { return vec3(pmodf(a.x, b), pmodf(a.y, b), pmodf(a.z, b)); }
static m_inline vec3  min3     (vec3   a, vec3   b) { return vec3(minf(a.x, b.x), minf(a.y, b.y), minf(a.z, b.z)); }
static m_inline vec3  max3     (vec3   a, vec3   b) { return vec3(maxf(a.x, b.x), maxf(a.y, b.y), maxf(a.z, b.z)); }
static m_inline vec3  abs3     (vec3   a          ) { return vec3(absf(a.x), absf(a.y), absf(a.z)); }
static m_inline vec3  floor3   (vec3   a          ) { return vec3(floorf(a.x), floorf(a.y), floorf(a.z)); }
static m_inline vec3  ceil3    (vec3   a          ) { return vec3(ceilf (a.x), ceilf (a.y), ceilf (a.z)); }
static m_inline vec3  cross3   (vec3   a, vec3   b) { return vec3(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y); }
static m_inline float dot3     (vec3   a, vec3   b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
static m_inline vec3  refl3    (vec3   a, vec3   b) { return sub3(a, scale3(b, 2*dot3(a, b))); }
static m_inline float len3sq   (vec3   a          ) { return dot3(a,a); }
static m_inline float len3     (vec3   a          ) { return sqrtf(len3sq(a)); }
static m_inline vec3  norm3    (vec3   a          ) { return /*dot3(a) == 0 ? a :*/ div3(a, len3(a)); }
static m_inline vec3  norm3sq  (vec3   a          ) { return /*dot3(a) == 0 ? a :*/ div3(a, len3sq(a)); }
static m_inline int   finite3  (vec3   a          ) { return finite2(vec2(a.x,a.y)) && m_finite(a.z); }
static m_inline vec3  mix3  (vec3 a,vec3 b,float t) { return add3(scale3((a),1-(t)), scale3((b), t)); }
//static m_inline vec3 tricross3 (vec3 a, vec3 b, vec3 c) { return cross3(a,cross3(b,c)); } // useful?
static m_inline void  ortho3   (vec3 *left, vec3 *up, vec3 v) {
#if 0
    if ((v.z * v.z) > (0.7f * 0.7f)) {
        float sqrlen  = v.y*v.y + v.z*v.z;
        float invlen  = 1.f / sqrtf(sqrlen);
        *up = vec3(0, v.z*invlen, -v.y*invlen);
        *left = vec3(sqrlen*invlen, -v.x*up->z, v.x*up->y);
    } else {
        float sqrlen = v.x*v.x + v.y*v.y;
        float invlen = 1.f / sqrtf(sqrlen);
        *left = vec3(-v.y*invlen, v.x*invlen, 0);
        *up = vec3(-v.z*left->y, v.z*left->x, sqrlen*invlen);
    }
#else
    *left = (v.z*v.z) < (v.x*v.x) ? vec3(v.y,-v.x,0) : vec3(0,-v.z,v.y);
    *up = cross3(*left, v);
#endif
}

// ----------------------------------------------------------------------------

static m_inline vec4  ptr4     (const float *a    ) { return vec4(a[0],a[1],a[2],a[3]); }
static m_inline vec4  vec34    (vec3   a, float w ) { return vec4(a.x,a.y,a.z,w); }
//
static m_inline vec4  neg4     (vec4   a          ) { return vec4(-a.x, -a.y, -a.z, -a.w); }
static m_inline vec4  add4     (vec4   a, vec4   b) { return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
static m_inline vec4  sub4     (vec4   a, vec4   b) { return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
static m_inline vec4  mul4     (vec4   a, vec4   b) { return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
static m_inline vec4  inc4     (vec4   a, float  b) { return vec4(a.x + b, a.y + b, a.z + b, a.w + b); }
static m_inline vec4  dec4     (vec4   a, float  b) { return vec4(a.x - b, a.y - b, a.z - b, a.w - b); }
static m_inline vec4  scale4   (vec4   a, float  b) { return vec4(a.x * b, a.y * b, a.z * b, a.w * b); }
static m_inline vec4  div4     (vec4   a, float  b) { return scale4(a, b ? 1/b : 0.f); }
static m_inline vec4  pmod4    (vec4   a, float  b) { return vec4(pmodf(a.x, b), pmodf(a.y, b), pmodf(a.z, b), pmodf(a.w, b)); }
static m_inline vec4  min4     (vec4   a, vec4   b) { return vec4(minf(a.x, b.x), minf(a.y, b.y), minf(a.z, b.z), minf(a.w, b.w)); }
static m_inline vec4  max4     (vec4   a, vec4   b) { return vec4(maxf(a.x, b.x), maxf(a.y, b.y), maxf(a.z, b.z), maxf(a.w, b.w)); }
static m_inline vec4  abs4     (vec4   a          ) { return vec4(absf(a.x), absf(a.y), absf(a.z), absf(a.w)); }
static m_inline vec4  floor4   (vec4   a          ) { return vec4(floorf(a.x), floorf(a.y), floorf(a.z), floorf(a.w)); }
static m_inline vec4  ceil4    (vec4   a          ) { return vec4(ceilf (a.x), ceilf (a.y), ceilf (a.z), ceilf (a.w)); }
static m_inline float dot4     (vec4   a, vec4   b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
static m_inline vec4  refl4    (vec4   a, vec4   b) { return sub4(a, scale4(b, 2*dot4(a, b))); }
static m_inline float len4sq   (vec4   a          ) { return dot4(a,a); }
static m_inline float len4     (vec4   a          ) { return sqrtf(len4sq(a)); }
static m_inline vec4  norm4    (vec4   a          ) { return /*dot4(a) == 0 ? a :*/ div4(a, len4(a)); }
static m_inline vec4  norm4sq  (vec4   a          ) { return /*dot4(a) == 0 ? a :*/ div4(a, len4sq(a)); }
static m_inline int   finite4  (vec4   a          ) { return finite3(vec3(a.x,a.y,a.z)) && m_finite(a.w); }
static m_inline vec4  mix4  (vec4 a,vec4 b,float t) { return add4(scale4((a),1-(t)), scale4((b), t)); }
// static m_inline vec4 cross4(vec4 v0, vec4 v1) { return vec34(cross3(v0.xyz, v1.xyz), (v0.w + v1.w) * 0.5f); } // may fail

// ----------------------------------------------------------------------------

static m_inline quat  idq      (                  ) { return quat(0,0,0,1); }
static m_inline quat  ptrq     (const float *a    ) { return quat(a[0],a[1],a[2],a[3]); }
static m_inline quat  vec3q    (vec3   a, float w ) { return quat(a.x,a.y,a.z,w); }
static m_inline quat  vec4q    (vec4   a          ) { return quat(a.x,a.y,a.z,a.w); }
//
static m_inline quat  negq     (quat   a          ) { return quat(-a.x,-a.y,-a.z,-a.w); }
static m_inline quat  conjq    (quat   a          ) { return quat(-a.x,-a.y,-a.z,a.w); }
static m_inline quat  addq     (quat   a, quat   b) { return quat(a.x+b.x,a.y+b.y,a.z+b.z,a.w+b.w); }
static m_inline quat  subq     (quat   a, quat   b) { return quat(a.x-b.x,a.y-b.y,a.z-b.z,a.w-b.w); }
static m_inline quat  mulq     (quat   p, quat   q) { vec3 w = scale3(p.xyz, q.w), r = add3(add3(cross3(p.xyz, q.xyz), w), scale3(q.xyz, p.w)); return quat(r.x,r.y,r.z,p.w*q.w - dot3(p.xyz, q.xyz)); }
static m_inline quat  scaleq   (quat   a, float  s) { return quat(a.x*s,a.y*s,a.z*s,a.w*s); }
static m_inline quat  normq    (quat   a          ) { vec4 v = norm4(a.xyzw); return quat(v.x,v.y,v.z,v.w); }
static m_inline float dotq     (quat   a, quat   b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; }
static m_inline quat  mixq(quat a, quat b, float t) { return normq(dotq(a,b) < 0 ? addq(negq(a),scaleq(addq(b,a),t)) : addq(a,scaleq(subq(b,a),t))); }
/* static m_inline quat lerpq(quat a, quat b, float s) {
    return norm(quat((1-s)*a.x + s*b.x, (1-s)*a.y + s*b.y, (1-s)*a.z + s*b.z, (1-s)*a.w + s*b.w));
}*/
static m_inline quat slerpq(quat a, quat b, float s) { //ok ?
    float t = acosf(dotq(a,b)), st = sinf(t), wa = sinf((1-s)*t)/st, wb = sinf(s*t)/st;
    return normq(quat(wa*a.x + wb*b.x, wa*a.y + wb*b.y, wa*a.z + wb*b.z, wa*a.w + wb*b.w));
}

static m_inline quat  rotationq(float deg,float x,float y,float z){ deg=rad(deg)*0.5f; return vec3q(scale3(vec3(x,y,z),sinf(deg)),cosf(deg)); }
static m_inline quat  mat44q   (mat44 M) {
    float r=0.f;
    int perm[] = { 0, 1, 2, 0, 1 }, *p = perm;
    for(int i = 0; i<3; i++) {
        float m = M[i*4+i];
        if( m < r ) continue;
        m = r;
        p = &perm[i];
    }
    r = sqrtf(1.f + M[p[0]*4+p[0]] - M[p[1]*4+p[1]] - M[p[2]*4+p[2]] );
    return r >= 1e-6 ? quat(1,0,0,0)
    : quat(r/2.f, (M[p[0]*4+p[1]] - M[p[1]*4+p[0]])/(2.f*r), (M[p[2]*4+p[0]] - M[p[0]*4+p[2]])/(2.f*r), (M[p[2]*4+p[1]] - M[p[1]*4+p[2]])/(2.f*r) );
}

static m_inline vec3 rotate3q_2(vec3 v, quat q) { // rotate vec3 by quat @testme
    vec3 u = {q.x, q.y, q.z}; // extract the vector part of the quaternion
    float s = q.w;            // scalar part
    vec3 cuv = cross3(u, v);
    float duv2 = dot3(u, v) * 2;
    float ss_duu = s*s - dot3(u, u);
    return add3(add3(scale3(u,duv2), scale3(v,ss_duu)), scale3(cuv,2*s));
}

static m_inline vec3 rotate3q(vec3 v, quat r) { // rotate vec3 by quat @testme
    float num12 = r.x + r.x;
    float num2 = r.y + r.y;
    float num = r.z + r.z;
    float num11 = r.w * num12;
    float num10 = r.w * num2;
    float num9 = r.w * num;
    float num8 = r.x * num12;
    float num7 = r.x * num2;
    float num6 = r.x * num;
    float num5 = r.y * num2;
    float num4 = r.y * num;
    float num3 = r.z * num;
    float num15 = ((v.x * ((1 - num5) - num3)) + (v.y * (num7 - num9))) + (v.z * (num6 + num10));
    float num14 = ((v.x * (num7 + num9)) + (v.y * ((1 - num8) - num3))) + (v.z * (num4 - num11));
    float num13 = ((v.x * (num6 - num10)) + (v.y * (num4 + num11))) + (v.z * ((1 - num8) - num5));
    return vec3(num15, num14, num13);
}

// euler <-> quat
static m_inline vec3  euler    (quat q) { // returns PitchRollYaw (PRY) in degrees. bugs? from wikipedia: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    float sr_cp = 2*(q.x*q.y + q.z*q.w), cr_cp = 1-2*(q.y*q.y + q.z*q.z);
    float sy_cp = 2*(q.x*q.w + q.y*q.z), cy_cp = 1-2*(q.z*q.z + q.w*q.w), sp = 2*(q.x*q.z-q.w*q.y);
    return scale3(vec3(fabs(sp) >= 1 ? copysignf(C_PI / 2, sp) : asinf(sp), atan2f(sr_cp, cr_cp), atan2f(sy_cp, cy_cp)), TO_DEG);
}

static m_inline quat  eulerq   (vec3 pry_degrees) { // bugs?
    float hp = rad(pry_degrees.x) * 0.5f, hr = rad(pry_degrees.y) * 0.5f, hy = rad(pry_degrees.z) * 0.5f;
    float cy = cosf(hy), sy = sinf(hy), cr = cosf(hr), sr = sinf(hr), cp = cosf(hp), sp = sinf(hp);
    return quat(cy*cr*cp + sy*sr*sp, cy*sr*cp - sy*cr*sp, cy*cr*sp + sy*sr*cp, sy*cr*cp - cy*sr*sp);
}

// ----------------------------------------------------------------------------

static m_inline void scaling33(mat33 m, float x, float y, float z) { // !!! ok, i guess
    m[0] = x; m[1] = 0; m[2] = 0;
    m[3] = 0; m[4] = y; m[5] = 0;
    m[6] = 0; m[7] = 0; m[8] = z;
}
static m_inline void scale33(mat33 m, float x, float y, float z) {
#if 0 // original !!! ok, i guess
    m[0] *= x; m[1] *= x; m[2] *= x;
    m[3] *= y; m[4] *= y; m[5] *= y;
    m[6] *= z; m[7] *= z; m[8] *= z;
#else
    m[0] *= x; m[3] *= x; m[6] *= x;
    m[1] *= y; m[4] *= y; m[7] *= y;
    m[2] *= z; m[5] *= z; m[8] *= z;
#endif
}
static m_inline void id33(mat33 m) {
    scaling33(m, 1,1,1);
}
static m_inline void extract33(mat33 m, const mat44 m4) {  // extract rot/sca from mat44
    m[0] = m4[0]; m[1] = m4[1]; m[2] = m4[ 2];
    m[3] = m4[4]; m[4] = m4[5]; m[5] = m4[ 6];
    m[6] = m4[8]; m[7] = m4[9]; m[8] = m4[10];
}
static m_inline void copy33(mat33 m, const mat33 a) {
    for(int i = 0; i < 9; ++i) m[i] = a[i];
}
//
static m_inline vec3 mulv33(mat33 m, vec3 v) {
    return vec3(m[0]*v.x+m[1]*v.y+m[2]*v.z,m[3]*v.x+m[4]*v.y+m[5]*v.z,m[6]*v.x+m[7]*v.y+m[8]*v.z);
}
static m_inline void multiply33x2(mat33 m, const mat33 a, const mat33 b) {
    m[0] = a[0]*b[0]+a[1]*b[3]+a[2]*b[6];
    m[1] = a[0]*b[1]+a[1]*b[4]+a[2]*b[7];
    m[2] = a[0]*b[2]+a[1]*b[5]+a[2]*b[8];

    m[3] = a[3]*b[0]+a[4]*b[3]+a[5]*b[6];
    m[4] = a[3]*b[1]+a[4]*b[4]+a[5]*b[7];
    m[5] = a[3]*b[2]+a[4]*b[5]+a[5]*b[8];

    m[6] = a[6]*b[0]+a[7]*b[3]+a[8]*b[6];
    m[7] = a[6]*b[1]+a[7]*b[4]+a[8]*b[7];
    m[8] = a[6]*b[2]+a[7]*b[5]+a[8]*b[8];
}

static m_inline void rotation33(mat33 m, float degrees, float x,float y,float z) {
    float radians = degrees * C_PI / 180.0f;
    float s = sinf(radians), c = cosf(radians), c1 = 1.0f - c;
    float xy = x*y, yz = y*z, zx = z*x, xs = x*s, ys = y*s, zs = z*s;
    m[0] = c1*x*x+c; m[1] = c1*xy-zs; m[2] = c1*zx+ys;
    m[3] = c1*xy+zs; m[4] = c1*y*y+c; m[5] = c1*yz-xs;
    m[6] = c1*zx-ys; m[7] = c1*yz+xs; m[8] = c1*z*z+c;
}
static m_inline void rotationq33(mat33 m, quat q) {
#if  0
    float a  = q.w, b  = q.x, c  = q.y, d  = q.z;
    float a2 = a*a, b2 = b*b, c2 = c*c, d2 = d*d;
    m[ 0] = a2 + b2 - c2 - d2; m[ 1] = 2*(b*c + a*d);     m[ 2] = 2*(b*d - a*c);
    m[ 3] = 2*(b*c - a*d);     m[ 4] = a2 - b2 + c2 - d2; m[ 5] = 2*(c*d + a*b);
    m[ 6] = 2*(b*d + a*c);     m[ 7] = 2*(c*d - a*b);     m[ 8] = a2 - b2 - c2 + d2;
#else
    float x2 = q.x*q.x, y2 = q.y*q.y, z2 = q.z*q.z, w2 = q.w*q.w;
    float xz = q.x*q.z, xy = q.x*q.y, yz = q.y*q.z, wz = q.w*q.z, wy = q.w*q.y, wx = q.w*q.x;
    m[0] = 1-2*(y2+z2); m[1] =   2*(xy+wz); m[2] =   2*(xz-wy);
    m[3] =   2*(xy-wz); m[4] = 1-2*(x2+z2); m[5] =   2*(yz+wx);
    m[6] =   2*(xz+wy); m[7] =   2*(yz-wx); m[8] = 1-2*(x2+y2);
#endif
}
static m_inline void rotate33(mat33 r, float degrees, float x,float y,float z) {
    if(len3sq(vec3(x,y,z)) < (1e-4 * 1e-4)) return;
    float m[9]; rotate33(m, degrees, x,y,z);
    multiply33x2(r, r, m);
}
static m_inline void compose33(mat33 m, quat r, vec3 s) { // verify me
    rotationq33(m, r);
    scale33(m, s.x,s.y,s.z);
}

// ----------------------------------------------------------------------------

static m_inline void id34(mat34 m) { // verify me
    m[ 0] = 1; m[ 1] = 0; m[ 2] = 0; m[ 3] = 0;
    m[ 4] = 0; m[ 5] = 1; m[ 6] = 0; m[ 7] = 0;
    m[ 8] = 0; m[ 9] = 0; m[10] = 1; m[11] = 0;
}
static m_inline void copy34(mat34 m, const mat34 a) {
    for( int i = 0; i < 12; ++i ) m[i] = a[i];
}
static m_inline void scale34(mat34 m, float s) {
    for( int i = 0; i < 12; ++i ) m[i] *= s;
}
static m_inline void add34(mat34 m, mat34 n) {
    for( int i = 0; i < 12; ++i ) m[i] += n[i];
}
static m_inline void muladd34(mat34 m, mat34 n, float s) {
    for( int i = 0; i < 12; ++i ) m[i] += n[i] * s;
}
static m_inline void add34x2(mat34 m, mat34 n, mat34 o) {
    for( int i = 0; i < 12; ++i ) m[i] = n[i] + o[i];
}
static m_inline void lerp34(mat34 m, mat34 n, mat34 o, float alpha) {
    for( int i = 0; i < 12; ++i ) m[i] = n[i] * (1-alpha) + o[i] * alpha;
}
static m_inline void multiply34x2(mat34 m, const mat34 m0, const mat34 m1) {
    vec4 r0 = { m0[0*4+0], m0[0*4+1], m0[0*4+2], m0[0*4+3] }; // rows
    vec4 r1 = { m0[1*4+0], m0[1*4+1], m0[1*4+2], m0[1*4+3] };
    vec4 r2 = { m0[2*4+0], m0[2*4+1], m0[2*4+2], m0[2*4+3] };

    vec4 c0 = { m1[0*4+0], m1[1*4+0], m1[2*4+0], 0.0f }; // cols
    vec4 c1 = { m1[0*4+1], m1[1*4+1], m1[2*4+1], 0.0f };
    vec4 c2 = { m1[0*4+2], m1[1*4+2], m1[2*4+2], 0.0f };
    vec4 c3 = { m1[0*4+3], m1[1*4+3], m1[2*4+3], 1.0f };

    m[ 0] = dot4(r0, c0); m[ 1] = dot4(r0, c1); m[ 2] = dot4(r0, c2); m[ 3] = dot4(r0, c3);
    m[ 4] = dot4(r1, c0); m[ 5] = dot4(r1, c1); m[ 6] = dot4(r1, c2); m[ 7] = dot4(r1, c3);
    m[ 8] = dot4(r2, c0); m[ 9] = dot4(r2, c1); m[10] = dot4(r2, c2); m[11] = dot4(r2, c3);
}
static m_inline void multiply34(mat34 m, const mat34 a) {
    mat34 x; copy34(x, m);
    multiply34x2(m, x, a);
}
static m_inline void multiply34x3(mat34 m, const mat34 a, const mat34 b, const mat34 c) {
    mat34 x;
    multiply34x2(x, a, b);
    multiply34x2(m, x, c);
}
static m_inline void compose34(mat34 m, vec3 t, quat q, vec3 s) {
    m[ 0] = s.x * (1 - 2 * q.y * q.y - 2 * q.z * q.z);
    m[ 1] = s.y * (    2 * q.x * q.y - 2 * q.w * q.z);
    m[ 2] = s.z * (    2 * q.x * q.z + 2 * q.w * q.y);
    m[ 3] = t.x;
    m[ 4] = s.x * (    2 * q.x * q.y + 2 * q.w * q.z);
    m[ 5] = s.y * (1 - 2 * q.x * q.x - 2 * q.z * q.z);
    m[ 6] = s.z * (    2 * q.y * q.z - 2 * q.w * q.x);
    m[ 7] = t.y;
    m[ 8] = s.x * (    2 * q.x * q.z - 2 * q.w * q.y);
    m[ 9] = s.y * (    2 * q.y * q.z + 2 * q.w * q.x);
    m[10] = s.z * (1 - 2 * q.x * q.x - 2 * q.y * q.y);
    m[11] = t.z;
}
static m_inline void invert34(mat34 m, const mat34 o) {
    vec3 a = norm3sq(vec3(o[0*4+0], o[1*4+0], o[2*4+0]));
    vec3 b = norm3sq(vec3(o[0*4+1], o[1*4+1], o[2*4+1]));
    vec3 c = norm3sq(vec3(o[0*4+2], o[1*4+2], o[2*4+2]));
    vec3 trans = vec3(o[0*4+3], o[1*4+3], o[2*4+3]);
    vec4 A = vec34(a, -dot3(a, trans));
    vec4 B = vec34(b, -dot3(b, trans));
    vec4 C = vec34(c, -dot3(c, trans));
    m[ 0] = A.x; m[ 1] = A.y; m[ 2] = A.z; m[ 3] = A.w;
    m[ 4] = B.x; m[ 5] = B.y; m[ 6] = B.z; m[ 7] = B.w;
    m[ 8] = C.x; m[ 9] = C.y; m[10] = C.z; m[11] = C.w;
}

// ----------------------------------------------------------------------------

static m_inline void scaling44(mat44 m, float x, float y, float z);
static m_inline void id44(mat44 m) {
    scaling44(m, 1,1,1);
}
static m_inline void identity44(mat44 m) {
    scaling44(m, 1,1,1);
}
static m_inline void copy44(mat44 m, const mat44 a) {
    for( int i = 0; i < 16; ++i ) m[i] = a[i];
}
static m_inline void multiply44x2(mat44 m, const mat44 a, const mat44 b) {
    for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
    m[y*4+x] = a[x] * b[y*4]+a[4+x] * b[y*4+1]+a[8+x] * b[y*4+2]+a[12+x] * b[y*4+3];
}
static m_inline void multiply44x3(mat44 m, const mat44 a, const mat44 b, const mat44 c) {
    mat44 x;
    multiply44x2(x, a, b);
    multiply44x2(m, x, c);
}
static m_inline void multiply44(mat44 m, const mat44 a) {
    mat44 b; copy44(b, m);
    multiply44x2(m, b, a);
}
// ---
static m_inline void ortho44(mat44 m, float l, float r, float b, float t, float n, float f) {
    m[ 0] = 2/(r-l);      m[ 1] = 0;            m[ 2] = 0;            m[ 3] = 0;
    m[ 4] = 0;            m[ 5] = 2/(t-b);      m[ 6] = 0;            m[ 7] = 0;
    m[ 8] = 0;            m[ 9] = 0;            m[10] = -2/(f-n);     m[11] = 0;
    m[12] = -(r+l)/(r-l); m[13] = -(t+b)/(t-b); m[14] = -(f+n)/(f-n); m[15] = 1;
}
static m_inline void frustum44(mat44 m, float l, float r, float b, float t, float n, float f) {
    m[ 0] = 2*n/(r-l);   m[ 1] = 0;           m[ 2] = 0;               m[ 3] = 0;
    m[ 4] = 0;           m[ 5] = 2*n/(t-b);   m[ 6] = 0;               m[ 7] = 0;
    m[ 8] = (r+l)/(r-l); m[ 9] = (t+b)/(t-b); m[10] = -(f+n)/(f-n);    m[11] = -1;
    m[12] = 0;           m[13] = 0;           m[14] = -2*(f*n)/(f-n);  m[15] = 0;
}
static m_inline void perspective44(mat44 m, float fovy_degrees, float aspect, float nearp, float farp) {
    float y = tanf(fovy_degrees * C_PI / 360) * nearp, x = y * aspect;
    frustum44(m, -x, x, -y, y, nearp, farp);
}
static m_inline void lookat44(mat44 m, vec3 eye, vec3 center, vec3 up) {
    vec3 f = norm3(sub3(center, eye));
    vec3 r = norm3(cross3(f, up));
    vec3 u = cross3(r, f);
    m[ 0] = r.x;           m[ 1] = u.x;           m[ 2] = -f.x;         m[ 3] = 0;
    m[ 4] = r.y;           m[ 5] = u.y;           m[ 6] = -f.y;         m[ 7] = 0;
    m[ 8] = r.z;           m[ 9] = u.z;           m[10] = -f.z;         m[11] = 0;
    m[12] = -dot3(r, eye); m[13] = -dot3(u, eye); m[14] = dot3(f, eye); m[15] = 1;
}
// ---
static m_inline void translation44(mat44 m, float x, float y, float z) { // identity4 + translate4
    m[ 0] = 1.0f; m[ 1] = 0.0f; m[ 2] = 0.0f; m[ 3] = 0.0f;
    m[ 4] = 0.0f; m[ 5] = 1.0f; m[ 6] = 0.0f; m[ 7] = 0.0f;
    m[ 8] = 0.0f; m[ 9] = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
    m[12] = x;    m[13] = y;    m[14] = z;    m[15] = 1.0f;
}
static m_inline void translate44(mat44 m, float x, float y, float z) { // translate in place
#if 0 // original
    vec4 t = {x, y, z, 0};
    m[12] += dot4(vec4(m[0],m[4],m[ 8],m[12]),t); // row4(M,0)
    m[13] += dot4(vec4(m[1],m[5],m[ 9],m[13]),t); // row4(M,1)
    m[14] += dot4(vec4(m[2],m[6],m[10],m[14]),t); // row4(M,2)
    m[15] += dot4(vec4(m[3],m[7],m[11],m[15]),t); // row4(M,3)
#else
    m[12] += m[ 0]*x + m[ 4]*y + m[ 8]*z;
    m[13] += m[ 1]*x + m[ 5]*y + m[ 9]*z;
    m[14] += m[ 2]*x + m[ 6]*y + m[10]*z;
    m[15] += m[ 3]*x + m[ 7]*y + m[11]*z;
#endif
}
static m_inline void relocate44(mat44 m, float x, float y, float z) {
    m[12] = x; m[13] = y; m[14] = z;
}
static m_inline void rotationq44(mat44 m, quat q) {
#if  0
    float a  = q.w, b  = q.x, c  = q.y, d  = q.z;
    float a2 = a*a, b2 = b*b, c2 = c*c, d2 = d*d;
    m[ 0] = a2 + b2 - c2 - d2; m[ 1] = 2*(b*c + a*d);     m[ 2] = 2*(b*d - a*c);     m[ 3] = 0;
    m[ 4] = 2*(b*c - a*d);     m[ 5] = a2 - b2 + c2 - d2; m[ 6] = 2*(c*d + a*b);     m[ 7] = 0;
    m[ 8] = 2*(b*d + a*c);     m[ 9] = 2*(c*d - a*b);     m[10] = a2 - b2 - c2 + d2; m[11] = 0;
    m[12] = 0;                 m[13] = 0;                 m[14] = 0;                 m[15] = 1;
#else
    float x2 = q.x*q.x, y2 = q.y*q.y, z2 = q.z*q.z, w2 = q.w*q.w;
    float xz = q.x*q.z, xy = q.x*q.y, yz = q.y*q.z, wz = q.w*q.z, wy = q.w*q.y, wx = q.w*q.x;
    m[ 0] = 1-2*(y2+z2); m[ 1] =   2*(xy+wz); m[ 2] =   2*(xz-wy); m[ 3] = 0;
    m[ 4] =   2*(xy-wz); m[ 5] = 1-2*(x2+z2); m[ 6] =   2*(yz+wx); m[ 7] = 0;
    m[ 8] =   2*(xz+wy); m[ 9] =   2*(yz-wx); m[10] = 1-2*(x2+y2); m[11] = 0;
    m[12] = 0;           m[13] = 0;           m[14] = 0;           m[15] = 1;
#endif
}
static m_inline void rotation44(mat44 m, float degrees, float x, float y, float z) {
    //if(len3sq(vec3(x,y,z)) < (1e-4 * 1e-4)) return;

    float radians = degrees * C_PI / 180.0f;
    float c = cosf(radians), s = sinf(radians), c1 = 1.0f - c;
    m[ 0] = x*x*c1 + c;   m[ 1] = y*x*c1 + z*s; m[ 2] = x*z*c1 - y*s; m[ 3] = 0.0f;
    m[ 4] = x*y*c1 - z*s; m[ 5] = y*y*c1 + c;   m[ 6] = y*z*c1 + x*s; m[ 7] = 0.0f;
    m[ 8] = x*z*c1 + y*s; m[ 9] = y*z*c1 - x*s; m[10] = z*z*c1 + c;   m[11] = 0.0f;
    m[12] = 0.0f;         m[13] = 0.0f;         m[14] = 0.0f;         m[15] = 1.0f;
}
static m_inline void rotate44(mat44 m, float degrees, float x, float y, float z) { // !!! ok, i guess
    if(len3sq(vec3(x,y,z)) < (1e-4 * 1e-4)) return;

    float radians = degrees * C_PI / 180.0f;
    float c = cosf(radians), s = -sinf(radians), c1 = 1 - c;
    float m00 = m[ 0],  m01 = m[ 1],  m02 = m[ 2], m03 = m[ 3],
          m04 = m[ 4],  m05 = m[ 5],  m06 = m[ 6], m07 = m[ 7],
          m08 = m[ 8],  m09 = m[ 9],  m10 = m[10], m11 = m[11];

    // rotation matrix
    float r00 = x*x*c1 + c,   r01 = y*x*c1 + z*s, r02 = x*z*c1 - y*s;
    float r04 = x*y*c1 - z*s, r05 = y*y*c1 + c,   r06 = y*z*c1 + x*s;
    float r08 = x*z*c1 + y*s, r09 = y*z*c1 - x*s, r10 = z*z*c1 + c;

    // multiply
    m[ 0] = r00 * m00 + r04 * m04 + r08 * m08;
    m[ 1] = r00 * m01 + r04 * m05 + r08 * m09;
    m[ 2] = r00 * m02 + r04 * m06 + r08 * m10;
    m[ 3] = r00 * m03 + r04 * m07 + r08 * m11;
    m[ 4] = r01 * m00 + r05 * m04 + r09 * m08;
    m[ 5] = r01 * m01 + r05 * m05 + r09 * m09;
    m[ 6] = r01 * m02 + r05 * m06 + r09 * m10;
    m[ 7] = r01 * m03 + r05 * m07 + r09 * m11;
    m[ 8] = r02 * m00 + r06 * m04 + r10 * m08;
    m[ 9] = r02 * m01 + r06 * m05 + r10 * m09;
    m[10] = r02 * m02 + r06 * m06 + r10 * m10;
    m[11] = r02 * m03 + r06 * m07 + r10 * m11;
}
static m_inline void scaling44(mat44 m, float x, float y, float z) { // !!! ok, i guess
    m[ 0] = x; m[ 1] = 0; m[ 2] = 0; m[ 3] = 0;
    m[ 4] = 0; m[ 5] = y; m[ 6] = 0; m[ 7] = 0;
    m[ 8] = 0; m[ 9] = 0; m[10] = z; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}
static m_inline void scale44(mat44 m, float x, float y, float z) {
#if 0 // original !!! ok, i guess
    m[ 0] *= x; m[ 1] *= x; m[ 2] *= x; m[ 3] *= x;
    m[ 4] *= y; m[ 5] *= y; m[ 6] *= y; m[ 7] *= y;
    m[ 8] *= z; m[ 9] *= z; m[10] *= z; m[11] *= z;
#else
    m[0] *= x; m[4] *= x; m[8] *= x;
    m[1] *= y; m[5] *= y; m[9] *= y;
    m[2] *= z; m[6] *= z; m[10] *= z;
#endif
}
// ---
static m_inline void transpose44(mat44 m, const mat44 a) { // M[i][j] = A[j][i];
    m[ 0] = a[0]; m[ 1] = a[4]; m[ 2] = a[ 8]; m[ 3] = a[12];
    m[ 4] = a[1]; m[ 5] = a[5]; m[ 6] = a[ 9]; m[ 7] = a[13];
    m[ 8] = a[2]; m[ 9] = a[6]; m[10] = a[10]; m[11] = a[14];
    m[12] = a[3]; m[13] = a[7]; m[14] = a[11]; m[15] = a[15];
}
static m_inline float det44(const mat44 M) { // !!! ok, i guess
    float s[6], c[6];
    s[0] = M[0*4+0]*M[1*4+1] - M[1*4+0]*M[0*4+1];
    s[1] = M[0*4+0]*M[1*4+2] - M[1*4+0]*M[0*4+2];
    s[2] = M[0*4+0]*M[1*4+3] - M[1*4+0]*M[0*4+3];
    s[3] = M[0*4+1]*M[1*4+2] - M[1*4+1]*M[0*4+2];
    s[4] = M[0*4+1]*M[1*4+3] - M[1*4+1]*M[0*4+3];
    s[5] = M[0*4+2]*M[1*4+3] - M[1*4+2]*M[0*4+3];

    c[0] = M[2*4+0]*M[3*4+1] - M[3*4+0]*M[2*4+1];
    c[1] = M[2*4+0]*M[3*4+2] - M[3*4+0]*M[2*4+2];
    c[2] = M[2*4+0]*M[3*4+3] - M[3*4+0]*M[2*4+3];
    c[3] = M[2*4+1]*M[3*4+2] - M[3*4+1]*M[2*4+2];
    c[4] = M[2*4+1]*M[3*4+3] - M[3*4+1]*M[2*4+3];
    c[5] = M[2*4+2]*M[3*4+3] - M[3*4+2]*M[2*4+3];

    return ( s[0]*c[5]-s[1]*c[4]+s[2]*c[3]+s[3]*c[2]-s[4]*c[1]+s[5]*c[0] );
}
static m_inline bool invert44(mat44 T, const mat44 M) { // !!! ok, i guess
    float s[6], c[6];
    s[0] = M[0*4+0]*M[1*4+1] - M[1*4+0]*M[0*4+1];
    s[1] = M[0*4+0]*M[1*4+2] - M[1*4+0]*M[0*4+2];
    s[2] = M[0*4+0]*M[1*4+3] - M[1*4+0]*M[0*4+3];
    s[3] = M[0*4+1]*M[1*4+2] - M[1*4+1]*M[0*4+2];
    s[4] = M[0*4+1]*M[1*4+3] - M[1*4+1]*M[0*4+3];
    s[5] = M[0*4+2]*M[1*4+3] - M[1*4+2]*M[0*4+3];

    c[0] = M[2*4+0]*M[3*4+1] - M[3*4+0]*M[2*4+1];
    c[1] = M[2*4+0]*M[3*4+2] - M[3*4+0]*M[2*4+2];
    c[2] = M[2*4+0]*M[3*4+3] - M[3*4+0]*M[2*4+3];
    c[3] = M[2*4+1]*M[3*4+2] - M[3*4+1]*M[2*4+2];
    c[4] = M[2*4+1]*M[3*4+3] - M[3*4+1]*M[2*4+3];
    c[5] = M[2*4+2]*M[3*4+3] - M[3*4+2]*M[2*4+3];

    float det = ( s[0]*c[5]-s[1]*c[4]+s[2]*c[3]+s[3]*c[2]-s[4]*c[1]+s[5]*c[0] );
    if( !det ) return false;
    float idet = 1.0f / det;

    T[0*4+0] = ( M[1*4+1] * c[5] - M[1*4+2] * c[4] + M[1*4+3] * c[3]) * idet;
    T[0*4+1] = (-M[0*4+1] * c[5] + M[0*4+2] * c[4] - M[0*4+3] * c[3]) * idet;
    T[0*4+2] = ( M[3*4+1] * s[5] - M[3*4+2] * s[4] + M[3*4+3] * s[3]) * idet;
    T[0*4+3] = (-M[2*4+1] * s[5] + M[2*4+2] * s[4] - M[2*4+3] * s[3]) * idet;

    T[1*4+0] = (-M[1*4+0] * c[5] + M[1*4+2] * c[2] - M[1*4+3] * c[1]) * idet;
    T[1*4+1] = ( M[0*4+0] * c[5] - M[0*4+2] * c[2] + M[0*4+3] * c[1]) * idet;
    T[1*4+2] = (-M[3*4+0] * s[5] + M[3*4+2] * s[2] - M[3*4+3] * s[1]) * idet;
    T[1*4+3] = ( M[2*4+0] * s[5] - M[2*4+2] * s[2] + M[2*4+3] * s[1]) * idet;

    T[2*4+0] = ( M[1*4+0] * c[4] - M[1*4+1] * c[2] + M[1*4+3] * c[0]) * idet;
    T[2*4+1] = (-M[0*4+0] * c[4] + M[0*4+1] * c[2] - M[0*4+3] * c[0]) * idet;
    T[2*4+2] = ( M[3*4+0] * s[4] - M[3*4+1] * s[2] + M[3*4+3] * s[0]) * idet;
    T[2*4+3] = (-M[2*4+0] * s[4] + M[2*4+1] * s[2] - M[2*4+3] * s[0]) * idet;

    T[3*4+0] = (-M[1*4+0] * c[3] + M[1*4+1] * c[1] - M[1*4+2] * c[0]) * idet;
    T[3*4+1] = ( M[0*4+0] * c[3] - M[0*4+1] * c[1] + M[0*4+2] * c[0]) * idet;
    T[3*4+2] = (-M[3*4+0] * s[3] + M[3*4+1] * s[1] - M[3*4+2] * s[0]) * idet;
    T[3*4+3] = ( M[2*4+0] * s[3] - M[2*4+1] * s[1] + M[2*4+2] * s[0]) * idet;
    return true;
}

static m_inline vec4 transform444(const mat44, const vec4);
static m_inline bool unproject44(vec3 *out, vec3 xyd, vec4 viewport, mat44 mvp) {
    // xyd: usually x:mouse_x,y:window_height()-mouse_y,d:0=znear/1=zfar
    // src: https://www.khronos.org/opengl/wiki/GluProject_and_gluUnProject_code
    mat44 inv_mvp;
    if( invert44(inv_mvp, mvp) ) {
        vec4 in = vec4( (xyd.x-viewport.x)/viewport.z*2-1, (xyd.y-viewport.y)/viewport.w*2-1, 2*xyd.z-1, 1 );
        vec4 p = transform444(inv_mvp, in);
        if( p.w != 0 ) {
            p.w = 1.f/p.w;
            *out = vec3(p.x*p.w,p.y*p.w,p.z*p.w);
            return true;
        }
    }
    return false;
}

static m_inline vec3 transform_axis(const coord_system, const coord_axis);
static m_inline void rebase44(mat44 m, const coord_system src_basis, const coord_system dst_basis) {
    vec3 v1 = transform_axis(src_basis, dst_basis.x);
    vec3 v2 = transform_axis(src_basis, dst_basis.y);
    vec3 v3 = transform_axis(src_basis, dst_basis.z);
    m[ 0] = v1.x; m[ 1] = v1.y; m[ 2] = v1.z; m[ 3] = 0;
    m[ 4] = v2.x; m[ 5] = v2.y; m[ 6] = v2.z; m[ 7] = 0;
    m[ 8] = v3.x; m[ 9] = v3.y; m[10] = v3.z; m[11] = 0;
    m[12] =    0; m[13] =    0; m[14] =    0; m[15] = 1;
}


static m_inline void compose44(mat44 m, vec3 t, quat q, vec3 s) {
#if 0
    // quat to rotation matrix
    m[0] = 1 - 2 * (q.y * q.y + q.z * q.z);
    m[1] = 2 * (q.x * q.y + q.z * q.w);
    m[2] = 2 * (q.x * q.z - q.y * q.w);

    m[4] = 2 * (q.x * q.y - q.z * q.w);
    m[5] = 1 - 2 * (q.x * q.x + q.z * q.z);
    m[6] = 2 * (q.y * q.z + q.x * q.w);

    m[8] = 2 * (q.x * q.z + q.y * q.w);
    m[9] = 2 * (q.y * q.z - q.x * q.w);
    m[10] = 1 - 2 * (q.x * q.x + q.y * q.y);

    // scale matrix
    m[0] *= s.x; m[4] *= s.x; m[8] *= s.x;
    m[1] *= s.y; m[5] *= s.y; m[9] *= s.y;
    m[2] *= s.z; m[6] *= s.z; m[10] *= s.z;

    // set translation
    m[12] = t.x; m[13] = t.y; m[14] = t.z;

    m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1;
#else
    rotationq44(m,q);
    scale44(m,s.x,s.y,s.z);
    relocate44(m,t.x,t.y,t.z);
//    relocate44(m,t.x,t.y,t.z); // ok?
//    scale44(m,s.x,s.y,s.z); // ok?

    m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1;
#endif
}

// ----------------------------------------------------------------------------

static m_inline vec3 transform33(mat33 m, vec3 p) {
    float x = (m[0] * p.x) + (m[4] * p.y) + (m[ 8] * p.z);
    float y = (m[1] * p.x) + (m[5] * p.y) + (m[ 9] * p.z);
    float z = (m[2] * p.x) + (m[6] * p.y) + (m[10] * p.z);
    return vec3(x,y,z);
}

static m_inline vec4 transform444(const mat44 m, const vec4 p) {
    // remember w = 1 for move in space; w = 0 rotate in space;
    float x = m[0]*p.x + m[4]*p.y + m[ 8]*p.z + m[12]*p.w;
    float y = m[1]*p.x + m[5]*p.y + m[ 9]*p.z + m[13]*p.w;
    float z = m[2]*p.x + m[6]*p.y + m[10]*p.z + m[14]*p.w;
    float w = m[3]*p.x + m[7]*p.y + m[11]*p.z + m[15]*p.w;
    return vec4(x,y,z,w);
}

static m_inline vec3 transform344(const mat44 m, const vec3 p) {
    vec4 v = transform444(m, vec34(p, 1));
    return scale3(v.xyz, 1.f / v.w);
}

static m_inline vec3 transformq(const quat q, const vec3 v) {  // !!! ok, i guess
    // [src] https://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion (laurent couvidou)
    // Extract the vector part of the quaternion
    vec3 u = vec3(q.x, q.y, q.z);
    // Extract the scalar part of the quaternion
    float s = q.w;
    // Do the math
    vec3 a = scale3(u, 2 * dot3(u,v));
    vec3 b = scale3(v, s*s - dot3(u,u));
    vec3 c = scale3(cross3(u,v), 2*s);
    return add3(a, add3(b,c));
}

static m_inline vec3 transform_axis(const coord_system basis, const coord_axis to) {
    const float dot_table[6][6] = {
        {+1,-1,0,0,0,0},{-1,+1,0,0,0,0},{0,0,+1,-1,0,0},
        {0,0,-1,+1,0,0},{0,0,0,0,+1,-1},{0,0,0,0,-1,+1},
    };
    return vec3( dot_table[basis.x][to], dot_table[basis.y][to], dot_table[basis.z][to] );
}

// A vector is the difference between two points in 3D space, possessing both direction and magnitude
static m_inline vec3 transform_vector  (const mat44 m, const vec3 vector)   {
    return transform344(m, vector);
}

// A point is a specific location within a 3D space
static m_inline vec3 transform_point   (const mat44 m, const vec3 p)    { // return (m * vec4{point,1).xyz()/r.w;
    float inv = 1.0f / (m[3+4*0]*p.x + m[3+4*1]*p.y + m[3+4*2]*p.z + m[3+4*3]);
    return vec3(
        (m[0+4*0]*p.x + m[0+4*1]*p.y + m[0+4*2]*p.z + m[0+4*3]) * inv,
        (m[1+4*0]*p.x + m[1+4*1]*p.y + m[1+4*2]*p.z + m[1+4*3]) * inv,
        (m[2+4*0]*p.x + m[2+4*1]*p.y + m[2+4*2]*p.z + m[2+4*3]) * inv
    );
}

// A tangent is a unit-length vector which is parallel to a piece of geometry, such as a surface or a curve
static m_inline vec3 transform_tangent (const mat44 m, const vec3 tangent)  { return norm3(transform_vector(m, tangent)); }

// A normal is a unit-length bivector which is perpendicular to a piece of geometry, such as a surface or a curve
static m_inline vec3 transform_normal  (const mat44 m, const vec3 normal)   {
    return transform_tangent(m, normal); // ok?

    mat44 t; transpose44(t,m); mat44 i; invert44(i,t);
    return scale3(norm3(transform_vector(i, normal)), det44(m) < 0 ? -1.f : 1.f);
}

// A quaternion can describe both a rotation and a uniform scaling in 3D space
static m_inline quat transform_quat     (const mat44 m, const quat q)      {
    vec3 s = scale3(transform_vector(m, q.xyz), det44(m) < 0 ? -1.f : 1.f);
    return quat(s.x,s.y,s.z,q.w);
}

// A matrix can describe a general transformation of homogeneous coordinates in projective space
static m_inline float* transform_matrix(mat44 out, const mat44 m, const mat44 matrix) {
    mat44 I; invert44(I, m);
    multiply44x3(out, I, matrix, m); // m,matrix,I instead ?
    return out;
}

// Scaling factors are not a vector, they are a compact representation of a scaling matrix
static m_inline vec3 transform_scaling (const mat44 m, const vec3 scaling) {
    mat44 s; scaling44(s, scaling.x, scaling.y, scaling.z);
    mat44 out; transform_matrix(out, m, s);
    return vec3( out[0], out[5], out[10] );
}

// ----------------------------------------------------------------------------

void     randset(uint64_t state);
uint64_t rand64(void);
double   randf(void); // [0, 1) interval
int      randi(int mini, int maxi); // [mini, maxi) interval

// ----------------------------------------------------------------------------
// !!! for debugging

#include <stdio.h>
static m_inline void print_( float *m, int ii, int jj ) {
    for( int j = 0; j < jj; ++j ) {
        for( int i = 0; i < ii; ++i ) printf("%8.3f", *m++);
        puts("");
    }
    puts("---");
}
static m_inline void print2( vec2 v ) { print_(&v.x,2,1); }
static m_inline void print3( vec3 v ) { print_(&v.x,3,1); }
static m_inline void print4( vec4 v ) { print_(&v.x,4,1); }
static m_inline void printq( quat q ) { print_(&q.x,4,1); }
static m_inline void print33( float *m ) { print_(m,3,3); }
static m_inline void print34( float *m ) { print_(m,3,4); }
static m_inline void print44( float *m ) { print_(m,4,4); }

#endif // MATH_H

#ifdef MATH_C
#pragma once

static uint64_t rand_xoro256(uint64_t x256_s[4]) { // xoshiro256+ 1.0 by David Blackman and Sebastiano Vigna (PD)
    const uint64_t result = x256_s[0] + x256_s[3];
    const uint64_t t = x256_s[1] << 17;

    x256_s[2] ^= x256_s[0];
    x256_s[3] ^= x256_s[1];
    x256_s[1] ^= x256_s[2];
    x256_s[0] ^= x256_s[3];

    x256_s[2] ^= t;

    x256_s[3] = (x256_s[3] << 45) | (x256_s[3] >> (64 - 45)); //x256_rotl(x256_s[3], 45);

    return result;
}
static threadlocal uint64_t rand_state[4] = {// = splitmix64(0),splitmix64(splitmix64(0)),... x4 times
    UINT64_C(0x9e3779b8bb0b2c64),UINT64_C(0x3c6ef372178960e7),
    UINT64_C(0xdaa66d2b71a12917),UINT64_C(0x78dde6e4d584aef9)
};
void randset(uint64_t x) {
    x = hash_64(x);
    for( int i = 0; i < 4; ++i) {
        // http://xoroshiro.di.unimi.it/splitmix64.c
        uint64_t z = (x += UINT64_C(0x9E3779B97F4A7C15));
        z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
        z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
        x = x ^ (z >> 31);
        rand_state[i] = x;
    }
}
uint64_t rand64(void) {
    return rand_xoro256(rand_state);
}
double randf(void) { // [0, 1) interval
    uint64_t u64 = rand64();
    // fastest way to convert in C99 a 64-bit unsigned integer to a 64-bit double
    union { uint64_t i; double d; } u; u.i = UINT64_C(0x3FF) << 52 | u64 >> 12;
    double dbl = u.d - 1.0;
    return 1 - 2.0 * ((float)(dbl / 2));
}
int randi(int mini, int maxi) { // [mini, maxi) interval ; @todo: test randi(-4,4)
    if( mini < maxi ) {
        uint32_t x, r, range = maxi - mini;
        do r = (x = rand64()) % range; while(range > (r-x));
        return mini + r;
    }
    return mini > maxi ? randi(maxi, mini) : mini;
}

#endif // MATH_C
