#ifndef _FFCC_CHARA_ANIM_H_
#define _FFCC_CHARA_ANIM_H_

#include "ffcc/memory.h"

class CChunkFile;
class SRT;

void i2f2_7(float*, unsigned short*, float);
void i2f_7(float*, unsigned short*);
void i2f2_6(float*, unsigned short*, float);
void i2f_6(float*, unsigned short*);
void i2f2_5(float*, unsigned short*, float);
void i2f_5(float*, unsigned short*);

class CChara
{
	class CAnim
	{
		CAnim();
		~CAnim();

		void Create(void*, CMemory::CStage*);
		void InitQuantize();
	};

	class CAnimNode
	{
		CAnimNode();
		~CAnimNode();

		void Create(CChunkFile&);
		void Interp(CChara::CAnim*, SRT*, float);
	};
};

#endif // _FFCC_CHARA_ANIM_H_
