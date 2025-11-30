#include "ffcc/vector.h"

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common_Embedded/Math/fdlibm.h"
#include "dolphin/mtx.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CVector::CVector()
{
	// TODO
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
CVector::CVector(const Vec& vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CVector::Identity()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
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
    float x = this->x;
    bool canPerformAtan = false;

    if (x != 0.0f)
        canPerformAtan = true;
    else {
		float z = this->z;
		
        if (z != 0.0f)
            canPerformAtan = true;
        else
            return 0.0f;
    }

    return (float)atan2((double)x, (double)this->z);
}
