#include "ffcc/vector.h"

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common_Embedded/Math/fdlibm.h"

/*
 * --INFO--
 * PAL Address: 0x800C4E50
 * PAL Size: 76b
 * EN Address: 0x800C46D8
 * EN Size: 76b
 * JP Address: 0x800C258C
 * JP Size: 76b
 */
float CVector::GetRotateY()
{
    float zero = 0.0f;
    if (zero == this->x && zero == this->z)
    {
        return zero;
    }

    return (float)atan2((double)this->x, (double)this->z);
}

/*
 * --INFO--
 * PAL Address: 0x800C4E9C
 * PAL Size: 36b
 * EN Address: 0x800C4724
 * EN Size: 36b
 * JP Address: 0x800C25D8
 * JP Size: 36b
 */
void CVector::Normalize()
{
    PSVECNormalize((const Vec*)this, (Vec*)this);
}

/*
 * --INFO--
 * PAL Address: 0x800C4EC0
 * PAL Size: 20b
 * EN Address: 0x800C4748
 * EN Size: 20b
 * JP Address: 0x800C25FC
 * JP Size: 20b
 */
void CVector::Identity()
{
	float zero = 0.0f;
	this->x = this->y = this->z = zero;
}

/*
 * --INFO--
 * PAL Address: 0x800C4ED4
 * PAL Size: 28b
 * EN Address: 0x800C475C
 * EN Size: 28b
 * JP Address: 0x800C2610
 * JP Size: 28b
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
 * PAL Address: 0x800C4EF0
 * PAL Size: 16b
 * EN Address: 0x800C4778
 * EN Size: 16b
 * JP Address: 0x800C262C
 * JP Size: 16b
 */
CVector::CVector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

/*
 * --INFO--
 * PAL Address: 0x800C4F00
 * PAL Size: 4b
 * EN Address: 0x800C4788
 * EN Size: 4b
 * JP Address: 0x800C263C
 * JP Size: 4b
 */
CVector::CVector()
{
}
