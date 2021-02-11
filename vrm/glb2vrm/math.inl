//
// Taken from Foundation Math API from Our Machinery
// https://ourmachinery.com/
//

#include <emmintrin.h>

typedef struct tm_vec3_t
{
    float x, y, z;
} tm_vec3_t;

typedef struct tm_vec4_t
{
    float x, y, z, w;
} tm_vec4_t;

typedef struct tm_mat44_t
{
    float xx, xy, xz, xw;
    float yx, yy, yz, yw;
    float zx, zy, zz, zw;
    float wx, wy, wz, ww;
} tm_mat44_t;

static inline float tm_vec4_dot(tm_vec4_t lhs, tm_vec4_t rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

static inline tm_vec4_t tm_quaternion_mul(tm_vec4_t lhs, tm_vec4_t rhs)
{
    const tm_vec4_t res = {
        lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
        lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
    };
    return res;
}

static inline tm_vec4_t tm_quaternion_inverse(tm_vec4_t q)
{
    const tm_vec4_t res = {
        -q.x,
        -q.y,
        -q.z,
        q.w,
    };
    return res;
}

static inline tm_vec3_t tm_quaternion_rotate_vec3(tm_vec4_t q, tm_vec3_t v)
{
    const tm_vec4_t v4 = { v.x, v.y, v.z };
    const tm_vec4_t q_inv = tm_quaternion_inverse(q);
    const tm_vec4_t v4_rot = tm_quaternion_mul(q, tm_quaternion_mul(v4, q_inv));
    const tm_vec3_t res = {
        v4_rot.x,
        v4_rot.y,
        v4_rot.z,
    };
    return res;
}

static inline const tm_mat44_t *tm_mat44_identity(void)
{
    static tm_mat44_t id = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    return &id;
}

static inline void tm_mat44_from_quaternion(tm_mat44_t *res, tm_vec4_t q)
{
    const float d = tm_vec4_dot(q, q);
    const float s = (d != 0.f) ? 2.f / d : 1.f;

    const float xs = q.x * s;
    const float ys = q.y * s;
    const float zs = q.z * s;
    const float wx = q.w * xs;
    const float wy = q.w * ys;
    const float wz = q.w * zs;
    const float xx = q.x * xs;
    const float xy = q.x * ys;
    const float xz = q.x * zs;
    const float yy = q.y * ys;
    const float yz = q.y * zs;
    const float zz = q.z * zs;

    res->xx = 1.f - yy - zz;
    res->xy = xy + wz;
    res->xz = xz - wy;
    res->xw = 0.f;

    res->yx = xy - wz;
    res->yy = 1.f - xx - zz;
    res->yz = yz + wx;
    res->yw = 0.f;

    res->zx = xz + wy;
    res->zy = yz - wx;
    res->zz = 1.f - xx - yy;
    res->zw = 0.f;

    res->wx = 0;
    res->wy = 0;
    res->wz = 0;
    res->ww = 1.f;
}

// reference code from https://d3cw3dd2w32x2b.cloudfront.net/wp-content/uploads/2015/01/matrix-to-quat.pdf
// Converting a Rotation Matrix to a Quaternion, Mike Day @ Insomniac
static inline tm_vec4_t tm_mat44_to_quaternion(const tm_mat44_t *m)
{
    const float m00 = m->xx, m10 = m->yx, m20 = m->zx;
    const float m01 = m->xy, m11 = m->yy, m21 = m->zy;
    const float m02 = m->xz, m12 = m->yz, m22 = m->zz;

    float t;
    tm_vec4_t res;
    if (m22 < 0.f) {
        if (m00 > m11) {
            t = 1.f + m00 - m11 - m22;
            res.x = t;
            res.y = m01 + m10;
            res.z = m20 + m02;
            res.w = m12 - m21;
        } else {
            t = 1.f - m00 + m11 - m22;
            res.x = m01 + m10;
            res.y = t;
            res.z = m12 + m21;
            res.w = m20 - m02;
        }
    } else {
        if (m00 < -m11) {
            t = 1.f - m00 - m11 + m22;
            res.x = m20 + m02;
            res.y = m12 + m21;
            res.z = t;
            res.w = m01 - m10;
        } else {
            t = 1.f + m00 + m11 + m22;
            res.x = m12 - m21;
            res.y = m20 - m02;
            res.z = m01 - m10;
            res.w = t;
        }
    }

    float s = 0.5f / sqrtf(t);
    res.x *= s;
    res.y *= s;
    res.z *= s;
    res.w *= s;

    return res;
}

static inline float tm_mat44_determinant33(const tm_mat44_t *m)
{
    const float mxx = m->xx, mxy = m->xy, mxz = m->xz;
    const float myx = m->yx, myy = m->yy, myz = m->yz;
    const float mzx = m->zx, mzy = m->zy, mzz = m->zz;

    float det = 0;
    det += mxx * myy * mzz - mxx * myz * mzy;
    det += mxy * myz * mzx - mxy * myx * mzz;
    det += mxz * myx * mzy - mxz * myy * mzx;
    return det;
}

static inline void tm_mat44_to_translation_quaternion_scale(tm_vec3_t *t, tm_vec4_t *r, tm_vec3_t *s, const tm_mat44_t *m)
{
    memcpy(t, &m->wx, sizeof(*t));

    s->x = sqrtf(m->xx * m->xx + m->xy * m->xy + m->xz * m->xz);
    s->y = sqrtf(m->yx * m->yx + m->yy * m->yy + m->yz * m->yz);
    s->z = sqrtf(m->zx * m->zx + m->zy * m->zy + m->zz * m->zz);

    tm_mat44_t tmp;
    memcpy(&tmp, m, sizeof(tmp));
    tmp.xx *= 1.f / s->x, tmp.xy *= 1.f / s->x, tmp.xz *= 1.f / s->x;
    tmp.yx *= 1.f / s->y, tmp.yy *= 1.f / s->y, tmp.yz *= 1.f / s->y;
    tmp.zx *= 1.f / s->z, tmp.zy *= 1.f / s->z, tmp.zz *= 1.f / s->z;

    bool is_mirrored = tm_mat44_determinant33(&tmp) < 0.0f;
    if (!is_mirrored) {
        *r = tm_mat44_to_quaternion(&tmp);
    } else {
        s->x = -s->x;
        s->y = -s->y;
        s->z = -s->z;

        tm_mat44_t mirror = {
            -tmp.xx, -tmp.xy, -tmp.xz, tmp.xw,
            -tmp.yx, -tmp.yy, -tmp.yz, tmp.yw,
            -tmp.zx, -tmp.zy, -tmp.zz, tmp.zw,
            +tmp.wx, +tmp.wy, +tmp.wz, tmp.ww
        };
        *r = tm_mat44_to_quaternion(&mirror);
    }
}

static inline void tm_mat44_from_translation_quaternion_scale(tm_mat44_t *res, tm_vec3_t t, tm_vec4_t q, tm_vec3_t s)
{
    tm_mat44_from_quaternion(res, q);

    res->xx *= s.x;
    res->xy *= s.x;
    res->xz *= s.x;

    res->yx *= s.y;
    res->yy *= s.y;
    res->yz *= s.y;

    res->zx *= s.z;
    res->zy *= s.z;
    res->zz *= s.z;

    res->wx = t.x;
    res->wy = t.y;
    res->wz = t.z;
}

// Standard implementation of tm_mat44_mul (uses SSE, but doesn't require AVX).
static inline void tm_mat44_mul(tm_mat44_t *res, const tm_mat44_t *lhs, const tm_mat44_t *rhs)
{
    __m128 vx = _mm_loadu_ps(&rhs->xx);
    __m128 vy = _mm_loadu_ps(&rhs->yx);
    __m128 vz = _mm_loadu_ps(&rhs->zx);
    __m128 vw = _mm_loadu_ps(&rhs->wx);

    // row 0
    __m128 sx = _mm_set1_ps(lhs->xx);
    __m128 sy = _mm_set1_ps(lhs->xy);
    __m128 sz = _mm_set1_ps(lhs->xz);
    __m128 sw = _mm_set1_ps(lhs->xw);

    sx = _mm_mul_ps(sx, vx);
    sy = _mm_mul_ps(sy, vy);
    sz = _mm_mul_ps(sz, vz);
    sw = _mm_mul_ps(sw, vw);

    sx = _mm_add_ps(sx, sz);
    sy = _mm_add_ps(sy, sw);
    sx = _mm_add_ps(sx, sy);

    _mm_storeu_ps(&res->xx, sx);

    // row 1
    sx = _mm_set1_ps(lhs->yx);
    sy = _mm_set1_ps(lhs->yy);
    sz = _mm_set1_ps(lhs->yz);
    sw = _mm_set1_ps(lhs->yw);

    sx = _mm_mul_ps(sx, vx);
    sy = _mm_mul_ps(sy, vy);
    sz = _mm_mul_ps(sz, vz);
    sw = _mm_mul_ps(sw, vw);

    sx = _mm_add_ps(sx, sz);
    sy = _mm_add_ps(sy, sw);
    sx = _mm_add_ps(sx, sy);

    _mm_storeu_ps(&res->yx, sx);

    // row 2
    sx = _mm_set1_ps(lhs->zx);
    sy = _mm_set1_ps(lhs->zy);
    sz = _mm_set1_ps(lhs->zz);
    sw = _mm_set1_ps(lhs->zw);

    sx = _mm_mul_ps(sx, vx);
    sy = _mm_mul_ps(sy, vy);
    sz = _mm_mul_ps(sz, vz);
    sw = _mm_mul_ps(sw, vw);

    sx = _mm_add_ps(sx, sz);
    sy = _mm_add_ps(sy, sw);
    sx = _mm_add_ps(sx, sy);

    _mm_storeu_ps(&res->zx, sx);

    // row 3
    sx = _mm_set1_ps(lhs->wx);
    sy = _mm_set1_ps(lhs->wy);
    sz = _mm_set1_ps(lhs->wz);
    sw = _mm_set1_ps(lhs->ww);

    sx = _mm_mul_ps(sx, vx);
    sy = _mm_mul_ps(sy, vy);
    sz = _mm_mul_ps(sz, vz);
    sw = _mm_mul_ps(sw, vw);

    sx = _mm_add_ps(sx, sz);
    sy = _mm_add_ps(sy, sw);
    sx = _mm_add_ps(sx, sy);

    _mm_storeu_ps(&res->wx, sx);
}
