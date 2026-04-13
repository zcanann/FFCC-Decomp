#include "ffcc/vector.h"

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common_Embedded/Math/fdlibm.h"
#include "ffcc/symbols_shared.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CVector::GetRotateY()
{
    const float zero = kVectorZero;
    if (zero == this->x && zero == this->z)
    {
        return zero;
    }

    return (float)atan2((double)this->x, (double)this->z);
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
void CVector::Identity()
{
	const float zero = kVectorZero;
	this->z = zero;
	this->y = zero;
	this->x = zero;
}

/*
 * --INFO--
 * PAL Address: 0x800D0B3C
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CVector::CVector(const Vec& vec)
{
	float x = vec.x;
	float y = vec.y;
	this->x = x;
	this->y = y;
	this->z = vec.z;
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
CVector::CVector()
{
}
