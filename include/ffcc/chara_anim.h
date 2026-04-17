#ifndef _FFCC_CHARA_ANIM_H_
#define _FFCC_CHARA_ANIM_H_

#include "ffcc/memory.h"
#include "ffcc/ref.h"

class CChunkFile;
class SRT;

class CChara
{
	class CAnim : public CRef
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
