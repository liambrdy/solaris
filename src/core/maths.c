#include "maths.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>

static b32 randSeeded = false;

f32 Sin(f32 x) {
    return sinf(x);
}

f32 Cos(f32 x) {
    return cosf(x);
}

f32 Tan(f32 x) {
    return tanf(x);
}

f32 Acos(f32 x) {
    return acosf(x);
}

f32 Sqrt(f32 x) {
    return sqrtf(x);
}

f32 Abs(f32 x) {
    return fabsf(x);
}

i32 Random() {
    if (!randSeeded) {
        srand(time(NULL));
        randSeeded = true;
    }
    return rand();
}

i32 RandomInRange(i32 min, i32 max) {
    return (Random() % (max - min + 1)) + min;
}

f32 FRandom() {
    return (float)Random() / (f32)RAND_MAX;
}

f32 FRandomInRange(f32 min, f32 max) {
    return min + ((float)Random() / ((f32)RAND_MAX / (max - min)));
}

// Linear Algebra

vec2 Vec2Create(f32 x, f32 y) {
    vec2 outVec;
    outVec.x = x;
    outVec.y = y;
    return outVec;
}

vec2 Vec2Zero() {
    return Vec2Create(0.0f, 0.0f);
}

vec2 Vec2One() {
    return Vec2Create(1.0f, 1.0f);
}

vec2 Vec2Up() {
    return Vec2Create(0.0f, 1.0f);
}

vec2 Vec2Down() {
    return Vec2Create(0.0f, -1.0f);
}

vec2 Vec2Right() {
    return Vec2Create(1.0f, 0.0f);
}

vec2 Vec2Left() {
    return Vec2Create(-1.0f, 0.0f);
}

vec2 Vec2Add(vec2 v0, vec2 v1) {
    return Vec2Create(v0.x + v1.x, v0.y + v1.y);
}

vec2 Vec2Sub(vec2 v0, vec2 v1) {
    return Vec2Create(v0.x - v1.x, v0.y - v1.y);
}

vec2 Vec2Mul(vec2 v0, vec2 v1) {
    return Vec2Create(v0.x * v1.x, v0.y * v1.y);
}

vec2 Vec2Div(vec2 v0, vec2 v1) {
    return Vec2Create(v0.x / v1.x, v0.y / v1.y);
}

f32 Vec2LengthSquared(vec2 v) {
    return v.x*v.x + v.y*v.y;
}

f32 Vec2Length(vec2 v) {
    return Sqrt(Vec2LengthSquared(v));
}

void Vec2Normalize(vec2 *v) {
    const f32 length = Vec2Length(*v);
    v->x /= length;
    v->y /= length;
}

vec2 Vec2Normalized(vec2 v) {
    Vec2Normalize(&v);
    return v;
}

b32 Vec2Compare(vec2 v0, vec2 v1, f32 tolerance) {
    if (Abs(v0.x - v1.x) > tolerance) {
        return false;
    }

    if (Abs(v0.y - v1.y) > tolerance) {
        return false;
    }

    return true;
}

f32 Vec2Distance(vec2 p0, vec2 p1) {
    vec2 d = Vec2Sub(p0, p1);
    return Vec2Length(d);
}

vec3 Vec3Create(f32 x, f32 y, f32 z) {
    vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}

#define v3(x, y, z) Vec3Create(x, y, z)

vec3 Vec3FromVec4(vec4 v) {
    return Vec3Create(v.x, v.y, v.z);
}

vec4 Vec3ToVec4(vec3 v, f32 w) {
    return (vec4){v.x, v.y, v.z, w};
}

vec3 Vec3Zero() {
    return Vec3Create(0.0f, 0.0f, 0.0f);
}

vec3 Vec3One() {
    return Vec3Create(1.0f, 1.0f, 1.0f);
}

vec3 Vec3Up() {
    return Vec3Create(0.0f, 1.0f, 0.0f);
}

vec3 Vec3Down() {
    return Vec3Create(0.0f, -1.0f, 0.0f);
}

vec3 Vec3Left() {
    return Vec3Create(-1.0f, 0.0f, 0.0f);
}

vec3 Vec3Right() {
    return Vec3Create(1.0f, 0.0f, 0.0f);
}

vec3 Vec3Forward() {
    return Vec3Create(0.0f, 0.0f, -1.0f);
}

vec3 Vec3Back() {
    return Vec3Create(0.0f, 0.0f, 1.0f);
}

vec3 Vec3Add(vec3 v0, vec3 v1) {
    return Vec3Create(v0.x+v1.x, v0.y+v1.y, v0.z+v1.z);
}

vec3 Vec3Sub(vec3 v0, vec3 v1) {
    return Vec3Create(v0.x-v1.x, v0.y-v1.y, v0.z-v1.z);
}

vec3 Vec3Mul(vec3 v0, vec3 v1) {
    return Vec3Create(v0.x*v1.x, v0.y*v1.y, v0.z*v1.z);
}

vec3 Vec3MulScalar(vec3 v, f32 a) {
    return Vec3Create(v.x*a, v.y*a, v.z*a);
}

vec3 Vec3Div(vec3 v0, vec3 v1) {
    return Vec3Create(v0.x/v1.x, v0.y/v1.y, v0.z/v1.z);
}

f32 Vec3LengthSquared(vec3 v) {
    return v.x*v.x + v.y*v.y + v.z*v.z;
}

f32 Vec3Length(vec3 v) {
    return Sqrt(Vec3LengthSquared(v));
}

void Vec3Normalize(vec3 *v) {
    const f32 length = Vec3Length(*v);
    v->x /= length;
    v->y /= length;
    v->z /= length;
}

vec3 Vec3Normalized(vec3 v) {
    Vec3Normalize(&v);
    return v;
}

f32 Vec3Dot(vec3 v0, vec3 v1) {
    f32 d = 0.0f;
    d += v0.x * v1.x;
    d += v0.y * v1.y;
    d += v0.z * v1.z;
    return d;
}

vec3 Vec3Cross(vec3 v0, vec3 v1) {
    return Vec3Create(
        v0.y*v1.z - v0.z*v1.y,
        v0.z*v1.x - v0.x*v1.z,
        v0.x*v1.y - v0.y*v1.x);
}

b32 Vec3Compare(vec3 v0, vec3 v1, f32 tolerance) {
    if (Abs(v0.x - v1.x) > tolerance) {
        return false;
    }

    if (Abs(v0.y - v1.y) > tolerance) {
        return false;
    }

    if (Abs(v0.z - v1.z) > tolerance) {
        return false;
    }

    return true;
}

f32 Vec3Distance(vec3 v0, vec3 v1) {
    vec3 d = Vec3Sub(v0, v1);
    return Vec3Length(d);
}

vec4 Vec4Create(f32 x, f32 y, f32 z, f32 w) {
    vec4 outVector;
    outVector.x = x;
    outVector.y = y;
    outVector.z = z;
    outVector.w = w;

    return outVector;
}

vec4 Vec4Zero() {
    return Vec4Create(0.0f, 0.0f, 0.0f, 0.0f);   
}

vec4 Vec4One() {
    return Vec4Create(1.0f, 1.0f, 1.0f, 1.0f);
}

vec4 Vec4Add(vec4 v0, vec4 v1) {
    vec4 res;
    for (u64 i = 0; i < 4; i++) {
        res.elements[i] = v0.elements[i] + v1.elements[i];
    }
    return res;
}

vec4 Vec4Sub(vec4 v0, vec4 v1) {
    vec4 res;
    for (u64 i = 0; i < 4; i++) {
        res.elements[i] = v0.elements[i] - v1.elements[i];
    }
    return res;
}

vec4 Vec4Mul(vec4 v0, vec4 v1) {
    vec4 res;
    for (u64 i = 0; i < 4; i++) {
        res.elements[i] = v0.elements[i] * v1.elements[i];
    }
    return res;
}

vec4 Vec4Div(vec4 v0, vec4 v1) {
    vec4 res;
    for (u64 i = 0; i < 4; i++) {
        res.elements[i] = v0.elements[i] / v1.elements[i];
    }
    return res;
}

f32 Vec4LengthSquared(vec4 v) {
    return v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w;
}

f32 Vec4Length(vec4 v) {
    return Sqrt(Vec4LengthSquared(v));
}

void Vec4Normalize(vec4 *v) {
    const f32 length = Vec4Length(*v);
    v->x /= length;
    v->y /= length;
    v->z /= length;
    v->w /= length;
}

vec4 Vec4Normalized(vec4 v) {
    Vec4Normalize(&v);
    return v;
}

f32 Vec4DotF32(
    f32 a0, f32 a1, f32 a2, f32 a3,
    f32 b0, f32 b1, f32 b2, f32 b3) {
    
    f32 d = 
        a0 * b0 +
        a1 * b1 + 
        a2 * b2 + 
        a3 * b3;
    return d;
}

mat4 Mat4Identity() {
    mat4 outMat;
    
    memset(outMat.data, 0, 16 * sizeof(f32));
    outMat.data[0] = 1.0f;
    outMat.data[5] = 1.0f;
    outMat.data[10] = 1.0f;
    outMat.data[15] = 1.0f;
    return outMat;
}

mat4 Mat4Mul(mat4 m0, mat4 m1) {
    mat4 out = Mat4Identity();

    const f32 *m0Ptr = m0.data;
    const f32 *m1Ptr = m1.data;
    f32 *dstPtr = out.data;

    for (i32 i = 0; i < 4; i++) {
        for (i32 j = 0; j < 4; j++) {
            *dstPtr = 
                m0Ptr[0  + j] * m1Ptr[4 * i + 0] +
                m0Ptr[4  + j] * m1Ptr[4 * i + 1] +
                m0Ptr[8  + j] * m1Ptr[4 * i + 2] +
                m0Ptr[12 + j] * m1Ptr[4 * i + 3];
            dstPtr++;
        }
    }
    return out;
}

mat4 Mat4Orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 nearClip, f32 farClip) {
    mat4 outMatrix = Mat4Identity();

    f32 lr = 1.0f / (left - right);
    f32 bt = 1.0f / (bottom - top);
    f32 nf = 1.0f / (nearClip - farClip);

    outMatrix.data[0] = -2.0f * lr;
    outMatrix.data[5] = -2.0f * bt;
    outMatrix.data[10] = 2.0f * nf;

    outMatrix.data[12] = (left + right) * lr;
    outMatrix.data[13] = (top + bottom) * bt;
    outMatrix.data[14] = (farClip + nearClip) * nf;
    return outMatrix;
}

mat4 Mat4Perspective(f32 fovRadians, f32 aspectRatio, f32 nearClip, f32 farClip) {
    f32 halfTanFov = Tan(fovRadians * 0.5f);
    mat4 outMatrix;
    memset(outMatrix.data, 0, 16 * sizeof(f32));
    outMatrix.data[0] = 1.0f / (aspectRatio * halfTanFov);
    outMatrix.data[5] = 1.0f / halfTanFov;
    outMatrix.data[10] = -((farClip + nearClip) / (farClip - nearClip));
    outMatrix.data[11] = -1.0f;
    outMatrix.data[14] = -((2.0f * farClip * nearClip) / (farClip - nearClip));
    return outMatrix;
}

mat4 Mat4LookAt(vec3 position, vec3 target, vec3 up) {
    mat4 outMatrix;
    vec3 zAxis;
    zAxis.x = target.x - position.x;
    zAxis.y = target.y - position.y;
    zAxis.z = target.z - position.z;

    zAxis = Vec3Normalized(zAxis);
    vec3 xAxis = Vec3Normalized(Vec3Cross(zAxis, up));
    vec3 yAxis = Vec3Cross(xAxis, zAxis);

    outMatrix.data[0] = xAxis.x;
    outMatrix.data[1] = yAxis.x;
    outMatrix.data[2] = -zAxis.x;
    outMatrix.data[3] = 0;
    outMatrix.data[4] = xAxis.y;
    outMatrix.data[5] = yAxis.y;
    outMatrix.data[6] = -zAxis.y;
    outMatrix.data[7] = 0;
    outMatrix.data[8] = xAxis.z;
    outMatrix.data[9] = yAxis.z;
    outMatrix.data[10] = -zAxis.z;
    outMatrix.data[11] = 0;
    outMatrix.data[12] = -Vec3Dot(xAxis, position);
    outMatrix.data[13] = -Vec3Dot(yAxis, position);
    outMatrix.data[14] = Vec3Dot(zAxis, position);
    outMatrix.data[15] = 1.0f;

    return outMatrix;
}

mat4 Mat4Transposed(mat4 matrix) {
    mat4 outMatrix = Mat4Identity();
    outMatrix.data[0] = matrix.data[0];
    outMatrix.data[1] = matrix.data[4];
    outMatrix.data[2] = matrix.data[8];
    outMatrix.data[3] = matrix.data[12];
    outMatrix.data[4] = matrix.data[1];
    outMatrix.data[5] = matrix.data[5];
    outMatrix.data[6] = matrix.data[9];
    outMatrix.data[7] = matrix.data[13];
    outMatrix.data[8] = matrix.data[2];
    outMatrix.data[9] = matrix.data[6];
    outMatrix.data[10] = matrix.data[10];
    outMatrix.data[11] = matrix.data[14];
    outMatrix.data[12] = matrix.data[3];
    outMatrix.data[13] = matrix.data[7];
    outMatrix.data[14] = matrix.data[11];
    outMatrix.data[15] = matrix.data[15];
    return outMatrix;
}

mat4 Mat4Inverse(mat4 matrix) {
    const f32* m = matrix.data;

    f32 t0 = m[10] * m[15];
    f32 t1 = m[14] * m[11];
    f32 t2 = m[6] * m[15];
    f32 t3 = m[14] * m[7];
    f32 t4 = m[6] * m[11];
    f32 t5 = m[10] * m[7];
    f32 t6 = m[2] * m[15];
    f32 t7 = m[14] * m[3];
    f32 t8 = m[2] * m[11];
    f32 t9 = m[10] * m[3];
    f32 t10 = m[2] * m[7];
    f32 t11 = m[6] * m[3];
    f32 t12 = m[8] * m[13];
    f32 t13 = m[12] * m[9];
    f32 t14 = m[4] * m[13];
    f32 t15 = m[12] * m[5];
    f32 t16 = m[4] * m[9];
    f32 t17 = m[8] * m[5];
    f32 t18 = m[0] * m[13];
    f32 t19 = m[12] * m[1];
    f32 t20 = m[0] * m[9];
    f32 t21 = m[8] * m[1];
    f32 t22 = m[0] * m[5];
    f32 t23 = m[4] * m[1];

    mat4 outMatrix;
    f32* o = outMatrix.data;

    o[0] = (t0 * m[5] + t3 * m[9] + t4 * m[13]) - (t1 * m[5] + t2 * m[9] + t5 * m[13]);
    o[1] = (t1 * m[1] + t6 * m[9] + t9 * m[13]) - (t0 * m[1] + t7 * m[9] + t8 * m[13]);
    o[2] = (t2 * m[1] + t7 * m[5] + t10 * m[13]) - (t3 * m[1] + t6 * m[5] + t11 * m[13]);
    o[3] = (t5 * m[1] + t8 * m[5] + t11 * m[9]) - (t4 * m[1] + t9 * m[5] + t10 * m[9]);

    f32 d = 1.0f / (m[0] * o[0] + m[4] * o[1] + m[8] * o[2] + m[12] * o[3]);

    o[0] = d * o[0];
    o[1] = d * o[1];
    o[2] = d * o[2];
    o[3] = d * o[3];
    o[4] = d * ((t1 * m[4] + t2 * m[8] + t5 * m[12]) - (t0 * m[4] + t3 * m[8] + t4 * m[12]));
    o[5] = d * ((t0 * m[0] + t7 * m[8] + t8 * m[12]) - (t1 * m[0] + t6 * m[8] + t9 * m[12]));
    o[6] = d * ((t3 * m[0] + t6 * m[4] + t11 * m[12]) - (t2 * m[0] + t7 * m[4] + t10 * m[12]));
    o[7] = d * ((t4 * m[0] + t9 * m[4] + t10 * m[8]) - (t5 * m[0] + t8 * m[4] + t11 * m[8]));
    o[8] = d * ((t12 * m[7] + t15 * m[11] + t16 * m[15]) - (t13 * m[7] + t14 * m[11] + t17 * m[15]));
    o[9] = d * ((t13 * m[3] + t18 * m[11] + t21 * m[15]) - (t12 * m[3] + t19 * m[11] + t20 * m[15]));
    o[10] = d * ((t14 * m[3] + t19 * m[7] + t22 * m[15]) - (t15 * m[3] + t18 * m[7] + t23 * m[15]));
    o[11] = d * ((t17 * m[3] + t20 * m[7] + t23 * m[11]) - (t16 * m[3] + t21 * m[7] + t22 * m[11]));
    o[12] = d * ((t14 * m[10] + t17 * m[14] + t13 * m[6]) - (t16 * m[14] + t12 * m[6] + t15 * m[10]));
    o[13] = d * ((t20 * m[14] + t12 * m[2] + t19 * m[10]) - (t18 * m[10] + t21 * m[14] + t13 * m[2]));
    o[14] = d * ((t18 * m[6] + t23 * m[14] + t15 * m[2]) - (t22 * m[14] + t14 * m[2] + t19 * m[6]));
    o[15] = d * ((t22 * m[10] + t16 * m[2] + t21 * m[6]) - (t20 * m[6] + t23 * m[10] + t17 * m[2]));

    return outMatrix;
}

mat4 Mat4Translation(vec3 position) {
    mat4 outMatrix = Mat4Identity();
    outMatrix.data[12] = position.x;
    outMatrix.data[13] = position.y;
    outMatrix.data[14] = position.z;
    return outMatrix;
}

mat4 Mat4Scale(vec3 scale) {
    mat4 outMatrix = Mat4Identity();
    outMatrix.data[0] = scale.x;
    outMatrix.data[5] = scale.y;
    outMatrix.data[10] = scale.z;
    return outMatrix;
}

mat4 Mat4EulerX(f32 angleRadians) {
    mat4 outMatrix = Mat4Identity();
    f32 c = Cos(angleRadians);
    f32 s = Sin(angleRadians);

    outMatrix.data[5] = c;
    outMatrix.data[6] = s;
    outMatrix.data[9] = -s;
    outMatrix.data[10] = c;
    return outMatrix;
}

mat4 Mat4EulerY(f32 angleRadians) {
    mat4 outMatrix = Mat4Identity();
    f32 c = Cos(angleRadians);
    f32 s = Sin(angleRadians);

    outMatrix.data[0] = c;
    outMatrix.data[2] = -s;
    outMatrix.data[8] = s;
    outMatrix.data[10] = c;
    return outMatrix;
}

mat4 Mat4EulerZ(f32 angleRadians) {
    mat4 outMatrix = Mat4Identity();

    f32 c = Cos(angleRadians);
    f32 s = Sin(angleRadians);

    outMatrix.data[0] = c;
    outMatrix.data[1] = s;
    outMatrix.data[4] = -s;
    outMatrix.data[5] = c;
    return outMatrix;
}

mat4 Mat4EulerXYZ(f32 xRadians, f32 yRadians, f32 zRadians) {
    mat4 rx = Mat4EulerX(xRadians);
    mat4 ry = Mat4EulerY(yRadians);
    mat4 rz = Mat4EulerZ(zRadians);
    mat4 outMatrix = Mat4Mul(rx, ry);
    outMatrix = Mat4Mul(outMatrix, rz);
    return outMatrix;
}


vec3 Mat4Forward(mat4 matrix) {
    vec3 forward;
    forward.x = -matrix.data[2];
    forward.y = -matrix.data[6];
    forward.z = -matrix.data[10];
    Vec3Normalize(&forward);
    return forward;
}

vec3 Mat4Backward(mat4 matrix) {
    vec3 backward;
    backward.x = matrix.data[2];
    backward.y = matrix.data[6];
    backward.z = matrix.data[10];
    Vec3Normalize(&backward);
    return backward;
}

vec3 Mat4Up(mat4 matrix) {
    vec3 up;
    up.x = matrix.data[1];
    up.y = matrix.data[5];
    up.z = matrix.data[9];
    Vec3Normalize(&up);
    return up;
}

vec3 Mat4Down(mat4 matrix) {
    vec3 down;
    down.x = -matrix.data[1];
    down.y = -matrix.data[5];
    down.z = -matrix.data[9];
    Vec3Normalize(&down);
    return down;
}

vec3 Mat4Left(mat4 matrix) {
    vec3 right;
    right.x = -matrix.data[0];
    right.y = -matrix.data[4];
    right.z = -matrix.data[8];
    Vec3Normalize(&right);
    return right;
}

vec3 Mat4Right(mat4 matrix) {
    vec3 left;
    left.x = matrix.data[0];
    left.y = matrix.data[4];
    left.z = matrix.data[8];
    Vec3Normalize(&left);
    return left;
}

// ------------------------------------------
// Quaternion
// ------------------------------------------

quat QuatIdentity() {
    return (quat){0, 0, 0, 1.0f};
}

f32 QuatNormal(quat q) {
    return Sqrt(
        q.x * q.x +
        q.y * q.y +
        q.z * q.z +
        q.w * q.w);
}

quat QuatNormalize(quat q) {
    f32 normal = QuatNormal(q);
    return (quat){
        q.x / normal,
        q.y / normal,
        q.z / normal,
        q.w / normal};
}

quat QuatConjugate(quat q) {
    return (quat){
        -q.x,
        -q.y,
        -q.z,
        q.w};
}

quat QuatInverse(quat q) {
    return QuatNormalize(QuatConjugate(q));
}

quat QuatMul(quat q_0, quat q_1) {
    quat out_quaternion;

    out_quaternion.x = q_0.x * q_1.w +
                       q_0.y * q_1.z -
                       q_0.z * q_1.y +
                       q_0.w * q_1.x;

    out_quaternion.y = -q_0.x * q_1.z +
                       q_0.y * q_1.w +
                       q_0.z * q_1.x +
                       q_0.w * q_1.y;

    out_quaternion.z = q_0.x * q_1.y -
                       q_0.y * q_1.x +
                       q_0.z * q_1.w +
                       q_0.w * q_1.z;

    out_quaternion.w = -q_0.x * q_1.x -
                       q_0.y * q_1.y -
                       q_0.z * q_1.z +
                       q_0.w * q_1.w;

    return out_quaternion;
}

f32 QuatDot(quat q_0, quat q_1) {
    return q_0.x * q_1.x +
           q_0.y * q_1.y +
           q_0.z * q_1.z +
           q_0.w * q_1.w;
}

mat4 QuatToMat4(quat q) {
    mat4 outMatrix = Mat4Identity();

    // https://stackoverflow.com/questions/1556260/convert-quaternion-rotation-to-rotation-matrix

    quat n = QuatNormalize(q);

    outMatrix.data[0] = 1.0f - 2.0f * n.y * n.y - 2.0f * n.z * n.z;
    outMatrix.data[1] = 2.0f * n.x * n.y - 2.0f * n.z * n.w;
    outMatrix.data[2] = 2.0f * n.x * n.z + 2.0f * n.y * n.w;

    outMatrix.data[4] = 2.0f * n.x * n.y + 2.0f * n.z * n.w;
    outMatrix.data[5] = 1.0f - 2.0f * n.x * n.x - 2.0f * n.z * n.z;
    outMatrix.data[6] = 2.0f * n.y * n.z - 2.0f * n.x * n.w;

    outMatrix.data[8] = 2.0f * n.x * n.z - 2.0f * n.y * n.w;
    outMatrix.data[9] = 2.0f * n.y * n.z + 2.0f * n.x * n.w;
    outMatrix.data[10] = 1.0f - 2.0f * n.x * n.x - 2.0f * n.y * n.y;

    return outMatrix;
}

// Calculates a rotation matrix based on the quaternion and the passed in center point.
mat4 QuatToRotationMatrix(quat q, vec3 center) {
    mat4 outMatrix;

    f32* o = outMatrix.data;
    o[0] = (q.x * q.x) - (q.y * q.y) - (q.z * q.z) + (q.w * q.w);
    o[1] = 2.0f * ((q.x * q.y) + (q.z * q.w));
    o[2] = 2.0f * ((q.x * q.z) - (q.y * q.w));
    o[3] = center.x - center.x * o[0] - center.y * o[1] - center.z * o[2];

    o[4] = 2.0f * ((q.x * q.y) - (q.z * q.w));
    o[5] = -(q.x * q.x) + (q.y * q.y) - (q.z * q.z) + (q.w * q.w);
    o[6] = 2.0f * ((q.y * q.z) + (q.x * q.w));
    o[7] = center.y - center.x * o[4] - center.y * o[5] - center.z * o[6];

    o[8] = 2.0f * ((q.x * q.z) + (q.y * q.w));
    o[9] = 2.0f * ((q.y * q.z) - (q.x * q.w));
    o[10] = -(q.x * q.x) - (q.y * q.y) + (q.z * q.z) + (q.w * q.w);
    o[11] = center.z - center.x * o[8] - center.y * o[9] - center.z * o[10];

    o[12] = 0.0f;
    o[13] = 0.0f;
    o[14] = 0.0f;
    o[15] = 1.0f;
    return outMatrix;
}

quat QuatFromAxisAngle(vec3 axis, f32 angle, b32 normalize) {
    const f32 half_angle = 0.5f * angle;
    f32 s = Sin(half_angle);
    f32 c = Cos(half_angle);

    quat q = (quat){s * axis.x, s * axis.y, s * axis.z, c};
    if (normalize) {
        return QuatNormalize(q);
    }
    return q;
}

quat QuatSlerp(quat q_0, quat q_1, f32 percentage) {
    quat out_quaternion;
    // Source: https://en.wikipedia.org/wiki/Slerp
    // Only unit quaternions are valid rotations.
    // Normalize to avoid undefined behavior.
    quat v0 = QuatNormalize(q_0);
    quat v1 = QuatNormalize(q_1);

    // Compute the cosine of the angle between the two vectors.
    f32 dot = QuatDot(v0, v1);

    // If the dot product is negative, slerp won't take
    // the shorter path. Note that v1 and -v1 are equivalent when
    // the negation is applied to all four components. Fix by
    // reversing one quaternion.
    if (dot < 0.0f) {
        v1.x = -v1.x;
        v1.y = -v1.y;
        v1.z = -v1.z;
        v1.w = -v1.w;
        dot = -dot;
    }

    const f32 DOT_THRESHOLD = 0.9995f;
    if (dot > DOT_THRESHOLD) {
        // If the inputs are too close for comfort, linearly interpolate
        // and normalize the result.
        out_quaternion = (quat){
            v0.x + ((v1.x - v0.x) * percentage),
            v0.y + ((v1.y - v0.y) * percentage),
            v0.z + ((v1.z - v0.z) * percentage),
            v0.w + ((v1.w - v0.w) * percentage)};

        return QuatNormalize(out_quaternion);
    }

    // Since dot is in range [0, DOT_THRESHOLD], acos is safe
    f32 theta_0 = Acos(dot);          // theta_0 = angle between input vectors
    f32 theta = theta_0 * percentage;  // theta = angle between v0 and result
    f32 sin_theta = Sin(theta);       // compute this value only once
    f32 sin_theta_0 = Sin(theta_0);   // compute this value only once

    f32 s0 = Cos(theta) - dot * sin_theta / sin_theta_0;  // == sin(theta_0 - theta) / sin(theta_0)
    f32 s1 = sin_theta / sin_theta_0;

    return (quat){
        (v0.x * s0) + (v1.x * s1),
        (v0.y * s0) + (v1.y * s1),
        (v0.z * s0) + (v1.z * s1),
        (v0.w * s0) + (v1.w * s1)};
}

f32 DegToRed(f32 degrees) {
    return degrees * DEG2RAD_MULTIPLIER;
}

f32 RadToDeg(f32 radians) {
    return radians * RAD2DEG_MULTIPLIER;
}