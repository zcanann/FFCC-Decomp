#include "dolphin/math.h"
#include "dolphin/mtx.h"
#include "dolphin/os.h"

float sqrtf(float x);
float sinf(float x);
float cosf(float x);
float acosf(float x);
float atan2f(float y, float x);

void C_QUATAdd(const Quaternion* p, const Quaternion* q, Quaternion* r)
{
    ASSERTMSGLINE(77, p, "QUATAdd():  NULL QuaternionPtr 'p' ");
    ASSERTMSGLINE(78, q, "QUATAdd():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(79, r, "QUATAdd():  NULL QuaternionPtr 'r' ");

    r->x = p->x + q->x;
    r->y = p->y + q->y;
    r->z = p->z + q->z;
    r->w = p->w + q->w;
}

void PSQUATAdd(const register Quaternion* p, const register Quaternion* q, register Quaternion* r)
{
    register f32 pxy, qxy, rxy, pzw, qzw, rzw;

    asm {
        psq_l pxy, 0(p), 0, 0
        psq_l qxy, 0(q), 0, 0
        ps_add rxy, pxy, qxy
        psq_st rxy, 0(r), 0, 0
        psq_l pzw, 8(p), 0, 0
        psq_l qzw, 8(q), 0, 0
        ps_add rzw, pzw, qzw
        psq_st rzw, 8(r), 0, 0
    }
}

void C_QUATSubtract(const Quaternion* p, const Quaternion* q, Quaternion* r)
{
    ASSERTMSGLINE(133, p, "QUATSubtract():  NULL QuaternionPtr 'p' ");
    ASSERTMSGLINE(134, q, "QUATSubtract():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(135, r, "QUATSubtract():  NULL QuaternionPtr 'r' ");

    r->x = p->x - q->x;
    r->y = p->y - q->y;
    r->z = p->z - q->z;
    r->w = p->w - q->w;
}

void PSQUATSubtract(const register Quaternion* p, const register Quaternion* q, register Quaternion* r)
{
    register f32 pxy, qxy, rxy, pzw, qzw, rzw;

    asm {
        psq_l pxy, 0(p), 0, 0
        psq_l qxy, 0(q), 0, 0
        ps_sub rxy, pxy, qxy
        psq_st rxy, 0(r), 0, 0
        psq_l pzw, 8(p), 0, 0
        psq_l qzw, 8(q), 0, 0
        ps_sub rzw, pzw, qzw
        psq_st rzw, 8(r), 0, 0
    }
}

void C_QUATMultiply(const Quaternion* p, const Quaternion* q, Quaternion* pq)
{
    Quaternion* r;
    Quaternion pqTmp;

    ASSERTMSGLINE(193, p, "QUATMultiply():  NULL QuaternionPtr 'p' ");
    ASSERTMSGLINE(194, q, "QUATMultiply():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(195, pq, "QUATMultiply():  NULL QuaternionPtr 'pq' ");

    if (p == pq || q == pq) {
        r = &pqTmp;
    } else {
        r = pq;
    }

    r->w = (p->w * q->w) - (p->x * q->x) - (p->y * q->y) - (p->z * q->z);
    r->x = (p->w * q->x) + (p->x * q->w) + (p->y * q->z) - (p->z * q->y);
    r->y = (p->w * q->y) + (p->y * q->w) + (p->z * q->x) - (p->x * q->z);
    r->z = (p->w * q->z) + (p->z * q->w) + (p->x * q->y) - (p->y * q->x);

    if (r == &pqTmp) {
        *pq = pqTmp;
    }
}

void PSQUATMultiply(register const Quaternion *a, register const Quaternion *b, register Quaternion *ab)
{
    asm {
        psq_l f0, 0(a), 0, 0
        psq_l f1, 8(a), 0, 0
        psq_l f2, 0(b), 0, 0
        ps_neg f5, f0
        psq_l f3, 8(b), 0, 0
        ps_neg f6, f1
        ps_merge01 f4, f5, f0
        ps_muls0 f7, f1, f2
        ps_muls0 f5, f5, f2
        ps_merge01 f1, f6, f1
        ps_muls1 f8, f4, f2
        ps_madds0 f7, f4, f3, f7
        ps_muls1 f2, f1, f2
        ps_madds0 f5, f1, f3, f5
        ps_madds1 f8, f6, f3, f8
        ps_merge10 f7, f7, f7
        ps_madds1 f2, f0, f3, f2
        ps_merge10 f5, f5, f5
        ps_add f7, f7, f2
        psq_st f7, 0(ab), 0, 0
        ps_sub f5, f5, f8
        psq_st f5, 8(ab), 0, 0
    }
}

void C_QUATScale(const Quaternion* q, Quaternion* r, f32 scale)
{
    ASSERTMSGLINE(306, q, "QUATScale():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(307, r, "QUATScale():  NULL QuaternionPtr 'r' ");

    r->x = q->x * scale;
    r->y = q->y * scale;
    r->z = q->z * scale;
    r->w = q->w * scale;
}

void PSQUATScale(const register Quaternion* q, register Quaternion* r, register f32 scale)
{
    register f32 rxy, rzw;

    asm {
        psq_l rxy, 0(q), 0, 0
        psq_l rzw, 8(q), 0, 0
        ps_muls0 rxy, rxy, scale
        psq_st rxy, 0(r), 0, 0
        ps_muls0 rzw, rzw, scale
        psq_st rzw, 8(r), 0, 0
    }
}

f32 C_QUATDotProduct(const Quaternion* p, const Quaternion* q)
{
    ASSERTMSGLINE(357, p, "QUATDotProduct():  NULL QuaternionPtr 'p' ");
    ASSERTMSGLINE(358, q, "QUATDotProduct():  NULL QuaternionPtr 'q' ");

    return (q->x * p->x) + (q->y * p->y) + (q->z * p->z) + (q->w * p->w);
}

f32 PSQUATDotProduct(const register Quaternion* p, const register Quaternion* q)
{
    register f32 pxy, pzw, qxy, qzw, dp;

    asm {
        psq_l pxy, 0(p), 0, 0
        psq_l qxy, 0(q), 0, 0
        ps_mul dp, pxy, qxy
        psq_l pzw, 8(p), 0, 0
        psq_l qzw, 8(q), 0, 0
        ps_madd dp, pzw, qzw, dp
        ps_sum0 dp, dp, dp, dp
    }

    return dp;
}

void C_QUATNormalize(const Quaternion* src, Quaternion* unit)
{
    f32 mag;

    ASSERTMSGLINE(407, src, "QUATNormalize():  NULL QuaternionPtr 'src' ");
    ASSERTMSGLINE(408, unit, "QUATNormalize():  NULL QuaternionPtr 'unit' ");

    mag = (src->x * src->x) + (src->y * src->y) + (src->z * src->z) + (src->w * src->w);
    if (mag >= 0.00001f) {
        mag = 1.0f / sqrtf(mag);

        unit->x = src->x * mag;
        unit->y = src->y * mag;
        unit->z = src->z * mag;
        unit->w = src->w * mag;
    } else {
        unit->x = unit->y = unit->z = unit->w = 0.0f;
    }
}

void PSQUATNormalize(const register Quaternion *src, register Quaternion *unit)
{
    {
        register f32 vv1, vv2, vv3;
        register f32 vv4, vv5, vv6;
        register f32 vv7, vv8;
        register f32 vv9 = 0.00001f;
        register f32 vvA = 0.5f;
        register f32 vvB = 3.0f;
        asm
        {
            psq_l    vv1, 0(src), 0, 0;
            ps_mul   vv3, vv1, vv1;
            psq_l    vv2, 8(src), 0, 0;
            ps_sub   vv6, vv9, vv9;
            ps_madd  vv3, vv2, vv2, vv3;
            ps_sum0  vv3, vv3, vv3, vv3;
            frsqrte  vv4, vv3;
            ps_sub   vv5, vv3, vv9;
            fmul     vv7, vv4, vv4;
            fmul     vv8, vv4, vvA;
            fnmsub   vv7, vv7, vv3, vvB;
            fmul     vv4, vv7, vv8;
            ps_sel   vv4, vv5, vv4, vv6;
            ps_muls0 vv1, vv1, vv4;
            ps_muls0 vv2, vv2, vv4;
            psq_st   vv1, 0(unit), 0, 0;
            psq_st   vv2, 8(unit), 0, 0;
        }
    }
}

void C_QUATInverse(const Quaternion* src, Quaternion* inv)
{
    f32 mag, norminv;

    ASSERTMSGLINE(498, src, "QUATInverse():  NULL QuaternionPtr 'src' ");
    ASSERTMSGLINE(499, inv, "QUATInverse():  NULL QuaternionPtr 'inv' ");

    mag = (src->x * src->x) + (src->y * src->y) + (src->z * src->z) + (src->w * src->w);
    if (mag == 0.0f) {
        mag = 1.0f;
    }

    norminv = 1.0f / mag;
    inv->x = -src->x * norminv;
    inv->y = -src->y * norminv;
    inv->z = -src->z * norminv;
    inv->w =  src->w * norminv;
}

void PSQUATInverse(const register Quaternion* src, register Quaternion* inv)
{
    register f32 sxy, szw;
    register f32 izz, iww;
    register f32 mag, nmag;
    register f32 norminv, nninv;
    register f32 nwork0;
    register f32 c_two;
    register f32 c_zero;
    register f32 c_one = 1.0f;

    asm {
        psq_l sxy, 0x0(src), 0, 0
        ps_mul mag, sxy, sxy
        ps_sub c_zero, c_one, c_one
        psq_l szw, 0x8(src), 0, 0
        ps_madd mag, szw, szw, mag
        ps_add c_two, c_one, c_one
        ps_sum0 mag, mag, mag, mag
        fcmpu cr0, mag, c_zero
        beq L_PSQUATInverse_one
        fres norminv, mag
        ps_neg nmag, mag
        ps_nmsub nwork0, mag, norminv, c_two
        ps_mul norminv, norminv, nwork0
        b L_PSQUATInverse_done
    L_PSQUATInverse_one:
        fmr norminv, c_one
    L_PSQUATInverse_done:
        ps_neg nninv, norminv
        ps_muls1 iww, norminv, szw
        ps_muls0 sxy, sxy, nninv
        psq_st iww, 0xc(inv), 1, 0
        ps_muls0 izz, szw, nninv
        psq_st sxy, 0x0(inv), 0, 0
        psq_st izz, 0x8(inv), 1, 0
    }
}

void C_QUATDivide(const Quaternion* p, const Quaternion* q, Quaternion* r)
{
    Quaternion qtmp;

    ASSERTMSGLINE(606, p, "QUATDivide():  NULL QuaternionPtr 'p' ");
    ASSERTMSGLINE(607, q, "QUATDivide():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(608, r, "QUATDivide():  NULL QuaternionPtr 'r' ");

    C_QUATInverse(q, &qtmp);
    C_QUATMultiply(&qtmp, p, r);
}

void PSQUATDivide(const Quaternion* p, const Quaternion* q, Quaternion* r)
{
    Quaternion qtmp;

    PSQUATInverse(q, &qtmp);
    PSQUATMultiply(&qtmp, p, r);
}

void C_QUATExp(const Quaternion* q, Quaternion* r)
{
    f32 theta, scale;

    ASSERTMSGLINE(643, q, "QUATExp():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(644, r, "QUATExp():  NULL QuaternionPtr 'r' ");
    ASSERTMSGLINE(647, q->w == 0.0f, "QUATExp():  'q' is not a pure quaternion. ");

    theta = sqrtf((q->x * q->x) + (q->y * q->y) + (q->z * q->z));
    scale = 1.0f;

    if (theta > 0.00001f) {
        scale = sinf(theta) / theta;
    }

    r->x = scale * q->x;
    r->y = scale * q->y;
    r->z = scale * q->z;
    r->w = cosf(theta);
}

void C_QUATLogN(const Quaternion* q, Quaternion* r)
{
    f32 theta, scale;

    ASSERTMSGLINE(676, q, "QUATLogN():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(677, r, "QUATLogN():  NULL QuaternionPtr 'r' ");

    scale = (q->x * q->x) + (q->y * q->y) + (q->z * q->z);
    scale = sqrtf(scale);
    theta = atan2f(scale, q->w);

    if (scale > 0.0f) {
        scale = theta / scale;
    }

    r->x = scale * q->x;
    r->y = scale * q->y;
    r->z = scale * q->z;
    r->w = 0.0f;
}

void C_QUATMakeClosest(const Quaternion* q, const Quaternion* qto, Quaternion* r)
{
    f32 dot;

    ASSERTMSGLINE(722, q, "QUATMakeClosest():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(723, qto, "QUATMakeClosest():  NULL QuaternionPtr 'qto' ");
    ASSERTMSGLINE(724, r, "QUATMakeClosest():  NULL QuaternionPtr 'r' ");

    dot = (q->x * qto->x) + (q->y * qto->y) + (q->z * qto->z) + (q->w * qto->w);
    if (dot < 0.0f) {
        r->x = -q->x;
        r->y = -q->y;
        r->z = -q->z;
        r->w = -q->w;
    } else {
        *r = *q;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80186FD4
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void C_QUATRotAxisRad(Quaternion *q, const Vec *axis, f32 rad)
{
    f32 tmp, tmp2, tmp3;
    Vec dst;

    tmp = rad;
    PSVECNormalize(axis, &dst);

    tmp2 = 0.5f * tmp;
    tmp3 = sinf(0.5f * tmp);
    tmp = tmp3;
    tmp3 = cosf(tmp2);

    q->x = tmp * dst.x;
    q->y = tmp * dst.y;
    q->z = tmp * dst.z;
    q->w = tmp3;
}

#pragma fp_contract off
void C_QUATMtx(Quaternion *r, const Mtx m)
{
    f32 vv0, vv1;
    s32 i, j, k;
    s32 idx[3] = { 1, 2, 0 };
    f32 vec[3];
    vv0 = m[0][0] + m[1][1] + m[2][2];
    if (vv0 > 0.0f) {
        vv1 = (f32)sqrtf(vv0 + 1.0f);
        r->w = vv1 * 0.5f;
        vv1 = 0.5f / vv1;
        r->x = (m[2][1] - m[1][2]) * vv1;
        r->y = (m[0][2] - m[2][0]) * vv1;
        r->z = (m[1][0] - m[0][1]) * vv1;
    }
    else {
        i = 0;
        if (m[1][1] > m[0][0])
            i = 1;
        if (m[2][2] > m[i][i])
            i = 2;
        j = idx[i];
        k = idx[j];
        vv1 = (f32)sqrtf((m[i][i] - (m[j][j] + m[k][k])) + 1.0f);
        vec[i] = vv1 * 0.5f;
        if (vv1 != 0.0f)
            vv1 = 0.5f / vv1;
        r->w = (m[k][j] - m[j][k]) * vv1;
        vec[j] = (m[i][j] + m[j][i]) * vv1;
        vec[k] = (m[i][k] + m[k][i]) * vv1;
        r->x = vec[0];
        r->y = vec[1];
        r->z = vec[2];
    }
}
#pragma fp_contract on

void C_QUATLerp(const Quaternion *p, const Quaternion *q, Quaternion *r, f32 t)
{
    f32 value;
    f32 pValue;

    pValue = p->x;
    value = t * (q->x - pValue);
    r->x = pValue + value;

    pValue = p->y;
    value = t * (q->y - pValue);
    r->y = pValue + value;

    pValue = p->z;
    value = t * (q->z - pValue);
    r->z = pValue + value;

    value = t * (q->w - p->w);
    r->w = p->w + value;
}

/*
 * --INFO--
 * PAL Address: 0x8018731C
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma fp_contract off
void C_QUATSlerp(const Quaternion *p, const Quaternion *q, Quaternion *r, f32 t)
{
    f32 theta, sin_th, cos_th;
    f32 tp, tq;

    cos_th = p->x * q->x + p->y * q->y + p->z * q->z + p->w * q->w;
    tq = 1.0f;

    if (cos_th < 0.0f) {
        cos_th = -cos_th;
        tq = -tq;
    }

    if (cos_th <= 0.99999f) {
        theta = acosf(cos_th);
        sin_th = sinf(theta);

        tp = sinf((1.0f - t) * theta) / sin_th;
        tq *= sinf(t * theta) / sin_th;
    } else {
        tp = 1.0f - t;
        tq *= t;
    }

    r->x = (tp * p->x) + (tq * q->x);
    r->y = (tp * p->y) + (tq * q->y);
    r->z = (tp * p->z) + (tq * q->z);
    r->w = (tp * p->w) + (tq * q->w);
}
#pragma fp_contract on

void C_QUATSquad(const Quaternion* p, const Quaternion* a, const Quaternion* b, const Quaternion* q, Quaternion* r, f32 t)
{
    Quaternion pq, ab;
    f32 t2;

    ASSERTMSGLINE(927, p, "QUATSquad():  NULL QuaternionPtr 'p' ");
    ASSERTMSGLINE(928, a, "QUATSquad():  NULL QuaternionPtr 'a' ");
    ASSERTMSGLINE(929, b, "QUATSquad():  NULL QuaternionPtr 'b' ");
    ASSERTMSGLINE(930, q, "QUATSquad():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(931, r, "QUATSquad():  NULL QuaternionPtr 'r' ");

    t2 = 2.0f * t * (1.0f - t);
    C_QUATSlerp(p, q, &pq, t);
    C_QUATSlerp(a, b, &ab, t);
    C_QUATSlerp(&pq, &ab, r, t2);
}

void C_QUATCompA(const Quaternion* qprev, const Quaternion* q, const Quaternion* qnext, Quaternion* a)
{
    Quaternion qm, qp, lqm, lqp, qpqm, exq;

    ASSERTMSGLINE(958, qprev, "QUATCompA():  NULL QuaternionPtr 'qprev' ");
    ASSERTMSGLINE(959, q, "QUATCompA():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(960, qnext, "QUATCompA():  NULL QuaternionPtr 'qnext' ");
    ASSERTMSGLINE(961, a, "QUATCompA():  NULL QuaternionPtr 'a' ");

    C_QUATDivide(qprev, q, &qm);
    C_QUATLogN(&qm, &lqm);
    C_QUATDivide(qnext, q, &qp);
    C_QUATLogN(&qp, &lqp);
    C_QUATAdd(&lqp, &lqm, &qpqm);
    C_QUATScale(&qpqm, &qpqm, -0.25f);
    C_QUATExp(&qpqm, &exq);
    C_QUATMultiply(q, &exq, a);
}
