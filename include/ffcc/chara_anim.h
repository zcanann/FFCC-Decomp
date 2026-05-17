#ifndef _FFCC_CHARA_ANIM_H_
#define _FFCC_CHARA_ANIM_H_

#include "ffcc/memory.h"
#include "ffcc/ref.h"

class CChunkFile;
class SRT;

class CChara
{
public:
	class CAnimNode;

	class CAnim : public CRef
	{
	public:
		CAnim();
		~CAnim();

		void Create(void*, CMemory::CStage*);
		void InitQuantize();
		unsigned char m_flags;
		char m_interp;
		unsigned char m_quantizeX;
		unsigned char m_quantizeY;
		unsigned char m_quantizeZ;
		unsigned char _padD;
		unsigned short m_nodeCount;
		unsigned short m_frameCount;
		CChara::CAnimNode* m_nodes;
		unsigned int m_interpOffset;
		unsigned int m_bankSize;
		void* m_bank;
		int m_lastFrame;
		int m_bankAddress;
		CMemory::CStage* m_stage;
	};

	class CAnimNode
	{
	public:
		CAnimNode();
		~CAnimNode();

		void Create(CChunkFile&);
		void Interp(CChara::CAnim*, SRT*, float);
		char m_name[16];
		unsigned int m_dataOffset;
		unsigned int m_flags;
	};

	unsigned char _pad0[0x205C];
	void* m_animAmemBase;
	unsigned char _pad2060[0x14];
	int m_animBankAddress;
};

#endif // _FFCC_CHARA_ANIM_H_
