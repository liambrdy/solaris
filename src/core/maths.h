#ifndef _MATHS_H
#define _MATHS_H

#include "core.h"

#include <string.h>

typedef union vec2_u {
    f32 elements[2];
    struct {
        union {
            f32 x, r, s, u;
        };
        union {
            f32 y, g, t, v;
        };
    };
} vec2;

typedef union vec3_u {
    f32 elements[3];
    struct {
        union {
            f32 x, r, s, u;
        };
        union {
            f32 y, g, t, v;
        };
        union {
            f32 z, b, p, w;
        };
    };
} vec3;

typedef union vec4_u {
    f32 elements[4];
    struct {
        union {
            f32 x, r, s;
        };
        union {
            f32 y, g, t;
        };
        union {
            f32 z, b, p;
        };
        union {
            f32 w, a, q;
        };
    };
} vec4;

typedef vec4 quat;

typedef union mat4_u {
    f32 data[16];
} mat4;

#define PI 3.14159265358979323846f
#define PI_2 2.0f * PI
#define HALF_PI 0.5f * PI
#define QUARTER_PI 0.25f * PI
#define ONE_OVER_PI 1.0f / PI
#define ONE_OVER_TWO_PI 1.0f / PI_2
#define SQRT_TWO 1.41421356237309504880f
#define SQRT_THREE 1.73205080756887729352f
#define SQRT_ONE_OVER_TWO 0.70710678118654752440f
#define SQRT_ONE_OVER_THREE 0.57735026918962576450f
#define DEG2RAD_MULTIPLIER PI / 180.0f
#define RAD2DEG_MULTIPLIER 180.0f / PI

#define SEC_TO_MS_MULTIPLIER 1000.0f
#define MS_TO_SEC_MULTIPLIER 0.0001f
#define INFINITY 1e30f
#define FLOAT_EPSILON 1.192092896e-07f

f32 Sin(f32 x);
f32 Cos(f32 x);
f32 Tan(f32 x);
f32 Acos(f32 x);
f32 Sqrt(f32 x);
f32 Abs(f32 x);

inline b32 IsPowerOf2(u64 value) {
    return (value != 0) && ((value & (value - 1)) == 0);
}

i32 Random();
i32 RandomInRange(i32 min, i32 max);

f32 FRandom();
f32 FRandomInRange(f32 min, f32 max);

vec2 Vec2Create(f32 x, f32 y);
vec2 Vec2Zero();
vec2 Vec2One();
vec2 Vec2Up();
vec2 Vec2Down();
vec2 Vec2Right();
vec2 Vec2Left();
vec2 Vec2Add(vec2 v0, vec2 v1);
vec2 Vec2Sub(vec2 v0, vec2 v1);
vec2 Vec2Mul(vec2 v0, vec2 v1);
vec2 Vec2Div(vec2 v0, vec2 v1);
f32 Vec2LengthSquared(vec2 v);
f32 Vec2Length(vec2 v);
void Vec2Normalize(vec2 *v);
vec2 Vec2Normalized(vec2 v);
b32 Vec2Compare(vec2 v0, vec2 v1, f32 tolerance);
f32 Vec2Distance(vec2 p0, vec2 p1);

vec3 Vec3Create(f32 x, f32 y, f32 z);
vec3 Vec3FromVec4(vec4 v);
vec4 Vec3ToVec4(vec3 v, f32 w);
vec3 Vec3Zero();
vec3 Vec3One();
vec3 Vec3Up();
vec3 Vec3Down();
vec3 Vec3Left();
vec3 Vec3Right();
vec3 Vec3Forward();
vec3 Vec3Back();
vec3 Vec3Add(vec3 v0, vec3 v1);
vec3 Vec3Sub(vec3 v0, vec3 v1);
vec3 Vec3Mul(vec3 v0, vec3 v1);
vec3 Vec3MulScalar(vec3 v, f32 a);
vec3 Vec3Div(vec3 v0, vec3 v1);
f32 Vec3LengthSquared(vec3 v);
f32 Vec3Length(vec3 v);
void Vec3Normalize(vec3 *v);
vec3 Vec3Normalized(vec3 v);
f32 Vec3Dot(vec3 v0, vec3 v1);
vec3 Vec3Cross(vec3 v0, vec3 v1);
b32 Vec3Compare(vec3 v0, vec3 v1, f32 tolerance);
f32 Vec3Distance(vec3 v0, vec3 v1);

#define v3(x, y, z) Vec3Create(x, y, z)

vec4 Vec4Create(f32 x, f32 y, f32 z, f32 w);
vec4 Vec4Zero();
vec4 Vec4One();
vec4 Vec4Add(vec4 v0, vec4 v1);
vec4 Vec4Sub(vec4 v0, vec4 v1);
vec4 Vec4Mul(vec4 v0, vec4 v1);
vec4 Vec4Div(vec4 v0, vec4 v1);
f32 Vec4LengthSquared(vec4 v);
f32 Vec4Length(vec4 v);
void Vec4Normalize(vec4 *v);
vec4 Vec4Normalized(vec4 v);
f32 Vec4DotF32(f32 a0, f32 a1, f32 a2, f32 a3, f32 b0, f32 b1, f32 b2, f32 b3);

mat4 Mat4Identity();
mat4 Mat4Mul(mat4 m0, mat4 m1);
mat4 Mat4Orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 nearClip, f32 farClip);
mat4 Mat4Perspective(f32 fovRadians, f32 aspectRatio, f32 nearClip, f32 farClip);
mat4 Mat4LookAt(vec3 position, vec3 target, vec3 up);
mat4 Mat4Transposed(mat4 matrix);
mat4 Mat4Inverse(mat4 matrix);
mat4 Mat4Translation(vec3 position);
mat4 Mat4Scale(vec3 scale);
mat4 Mat4EulerX(f32 angleRadians);
mat4 Mat4EulerY(f32 angleRadians);
mat4 Mat4EulerZ(f32 angleRadians);
mat4 Mat4EulerXYZ(f32 xRadians, f32 yRadians, f32 zRadians);

vec3 Mat4Forward(mat4 matrix);
vec3 Mat4Backward(mat4 matrix);
vec3 Mat4Up(mat4 matrix);
vec3 Mat4Down(mat4 matrix);
vec3 Mat4Left(mat4 matrix);
vec3 Mat4Right(mat4 matrix);

// ------------------------------------------
// Quaternion Functions
// ------------------------------------------

quat QuatIdentity();
f32 QuatNormal(quat q);
quat QuatNormalize(quat q);
quat QuatConjugate(quat q);
quat QuatInverse(quat q);
quat QuatMul(quat q_0, quat q_1);
f32 QuatDot(quat q_0, quat q_1);


mat4 QuatToMat4(quat q);

mat4 QuatToRotationMatrix(quat q, vec3 center);
quat QuatFromAxisAngle(vec3 axis, f32 angle, b32 normalize);
quat QuatSlerp(quat q_0, quat q_1, f32 percentage);

f32 DegToRed(f32 degrees);
f32 RadToDeg(f32 radians);

#endif