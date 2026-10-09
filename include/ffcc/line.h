#ifndef _FFCC_LINE_H_
#define _FFCC_LINE_H_

#include <dolphin/mtx.h>

struct CLineSegment {
    Vec delta;
    Vec normal;
    float length;
    float startLength;
};

template <int PointCount>
struct CLine {
    CLine();
    int Calc(Vec*, float*, unsigned long*, float*, Vec*, float);
    int IsInner(Vec*, float);
    void Draw();
    void CalcBound();

    Vec min;
    Vec max;
    unsigned int pointCount;
    unsigned int unused;
    float unk20[3];
    unsigned int m_mask;
    Vec points[PointCount];
    CLineSegment segments[PointCount - 1];
    float totalLength;
};

template <int PointCount>
inline CLine<PointCount>::CLine()
{
    pointCount = 0;
}

template <int PointCount>
int CLine<PointCount>::Calc(Vec* outPos, float* outDistance, u32* outIndex, float* outT, Vec* queryPos, float maxDistance)
{
    float bestPosX;
    float bestPosY;
    float bestPosZ;
    const int infiniteRange = (0.0f == maxDistance);
    float bestDistance = infiniteRange ? 10000000.0f : maxDistance;
    const float maxDistanceSq = maxDistance * maxDistance;
    float bestT;
    u32 bestIndex;
    int found = 0;
    Vec candidatePosition;

    for (u32 i = 0; i < pointCount - 1; i++) {
        float distanceSq = PSVECSquareDistance(&points[i], queryPos);
        if (distanceSq < maxDistanceSq || infiniteRange) {
            candidatePosition = points[i];
            float distance = sqrtf(distanceSq);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestPosX = candidatePosition.x;
                bestPosY = candidatePosition.y;
                bestPosZ = candidatePosition.z;
                bestIndex = i;
                bestT = 0.0f;
                found = 1;
            }
        }

        if (i == pointCount - 2) {
            distanceSq = PSVECSquareDistance(&points[i + 1], queryPos);
            if (distanceSq < maxDistanceSq || infiniteRange) {
                candidatePosition = points[i + 1];
                float distance = sqrtf(distanceSq);
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestPosX = candidatePosition.x;
                    bestPosY = candidatePosition.y;
                    bestPosZ = candidatePosition.z;
                    bestIndex = i;
                    bestT = 1.0f;
                    found = 1;
                }
            }
        }

        const float dotQuery = PSVECDotProduct(queryPos, &segments[i].delta);
        const float dotStart = PSVECDotProduct(&points[i], &segments[i].delta);
        const float t = (-dotStart + dotQuery) / (segments[i].length * segments[i].length);
        if (((t >= 0.0f) && (t <= 1.0f)) || infiniteRange) {
            Vec scaled;
            PSVECScale(&segments[i].delta, &scaled, t);
            PSVECAdd(&points[i], &scaled, &candidatePosition);
            const float distance = PSVECDistance(queryPos, &candidatePosition);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestPosX = candidatePosition.x;
                bestPosY = candidatePosition.y;
                bestPosZ = candidatePosition.z;
                bestIndex = i;
                bestT = t;
                found = 1;
            }
        }
    }

    if (found != 0) {
        if (outPos != nullptr) {
            outPos->x = bestPosX;
            outPos->y = bestPosY;
            outPos->z = bestPosZ;
        }
        if (outDistance != nullptr) {
            *outDistance = bestDistance;
        }
        if (outIndex != nullptr) {
            *outIndex = bestIndex;
        }
        if (outT != nullptr) {
            *outT = bestT;
        }
    }

    return found;
}

template <int PointCount>
void CLine<PointCount>::Draw()
{
    if (pointCount == 0) {
        return;
    }

    GXBegin((GXPrimitive)0xB0, GX_VTXFMT0, (u16)(pointCount & 0xFFFF));
    for (u32 i = 0; i < pointCount; i++) {
        float x;
        float y;
        float z;
        z = points[i].z;
        y = points[i].y;
        x = points[i].x;
        GXWGFifo.f32 = x;
        GXWGFifo.f32 = y;
        GXWGFifo.f32 = z;
    }

    GXBegin((GXPrimitive)0xB0, GX_VTXFMT0, (u16)(pointCount & 0xFFFF));
    for (u32 i = 0; i < pointCount; i++) {
        float x = points[i].x;
        float y = 5.0f + points[i].y;
        float z = points[i].z;
        GXWGFifo.f32 = x;
        GXWGFifo.f32 = y;
        GXWGFifo.f32 = z;
    }

    GXBegin((GXPrimitive)0xA8, GX_VTXFMT0, (u16)((pointCount & 0x7FFF) << 1));
    for (u32 i = 0; i < pointCount; i++) {
        float x;
        float y;
        float z;
        z = points[i].z;
        y = points[i].y;
        x = points[i].x;
        GXWGFifo.f32 = x;
        GXWGFifo.f32 = y;
        GXWGFifo.f32 = z;
        {
            float raisedY = 5.0f + points[i].y;
            float raisedZ = points[i].z;
            float raisedX = points[i].x;
            GXWGFifo.f32 = raisedX;
            GXWGFifo.f32 = raisedY;
            GXWGFifo.f32 = raisedZ;
        }
    }
}

template <int PointCount>
void CLine<PointCount>::CalcBound()
{
    min.x = 10000000.0f;
    min.y = 10000000.0f;
    min.z = 10000000.0f;
    max.x = -10000000.0f;
    max.y = -10000000.0f;
    max.z = -10000000.0f;
    totalLength = 0.0f;

    for (u32 i = 0; i < pointCount; i++) {
        if (points[i].x < min.x) {
            min.x = points[i].x;
        }
        if (points[i].y < min.y) {
            min.y = points[i].y;
        }
        if (points[i].z < min.z) {
            min.z = points[i].z;
        }

        if (points[i].x > max.x) {
            max.x = points[i].x;
        }
        if (points[i].y > max.y) {
            max.y = points[i].y;
        }
        if (points[i].z > max.z) {
            max.z = points[i].z;
        }

        if (i != 0) {
            PSVECSubtract(&points[i], &points[i - 1], &segments[i - 1].delta);
            segments[i - 1].length = PSVECMag(&segments[i - 1].delta);
            segments[i - 1].startLength = totalLength;
            totalLength += segments[i - 1].length;
            if (segments[i - 1].length != 0.0f) {
                PSVECNormalize(&segments[i - 1].delta, &segments[i - 1].normal);
            }
        }
    }
}

template <int PointCount>
int CLine<PointCount>::IsInner(Vec* position, float margin)
{
    if (pointCount != 0) {
        if ((min.x - margin) <= position->x && (min.y - margin) <= position->y &&
            (min.z - margin) <= position->z && (max.x + margin) >= position->x &&
            (max.y + margin) >= position->y && (max.z + margin) >= position->z) {
            return 1;
        }
    }

    return 0;
}

#endif // _FFCC_LINE_H_
