#include "ffcc/vector.h"
#include "ffcc/symbols_shared.h"

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common_Embedded/Math/fdlibm.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CVector::CVector()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CVector::CVector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CVector::CVector(const Vec& vec)
{
    float y = vec.y;
    x = vec.x;
    float z = vec.z;
    this->y = y;
    this->z = z;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CVector::Identity()
{
	float zero = kVectorZero;
	this->z = zero;
	this->y = zero;
	this->x = zero;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CVector::Normalize()
{
    PSVECNormalize((const Vec*)this, (Vec*)this);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CVector::GetRotateY()
{
    const float zero = 0.0f;
    if (this->x == zero && this->z == zero)
    {
        return zero;
    }

    return (float)atan2((double)this->x, (double)this->z);
}
