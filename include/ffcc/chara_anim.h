#ifndef _FFCC_CHARA_ANIM_H_
#define _FFCC_CHARA_ANIM_H_

#include "ffcc/memory.h"
#include "ffcc/ref.h"

class CChunkFile;
class SRT;

class CChara
{
	class CAnimNode;

	class CAnim : public CRef
	{
		friend class CAnimNode;

		unsigned char m_flags;               // 0x08
		char m_interp;                      // 0x09
		unsigned char m_quantizeX;          // 0x0A
		unsigned char m_quantizeY;          // 0x0B
		unsigned char m_quantizeZ;          // 0x0C
		unsigned char _pad0D;               // 0x0D
		unsigned short m_nodeCount;         // 0x0E
		unsigned short m_frameCount;        // 0x10
		unsigned short _pad12;              // 0x12
		CAnimNode* m_nodes;                 // 0x14
		unsigned int m_interpOffset;        // 0x18
		unsigned int m_bankSize;            // 0x1C
		void* m_bank;                       // 0x20
		int m_lastFrame;                    // 0x24
		int m_bankAddress;                  // 0x28
		CMemory::CStage* m_stage;           // 0x2C

		CAnim();
		~CAnim();

		void Create(void*, CMemory::CStage*);
		void InitQuantize();
	};

	class CAnimNode
	{
		friend class CAnim;

		char m_name[16];                    // 0x00
		unsigned int m_dataOffset;          // 0x10
		unsigned int m_flags;               // 0x14

		CAnimNode();
		~CAnimNode();

		void Create(CChunkFile&);
		void Interp(CChara::CAnim*, SRT*, float);
	};
};

#endif // _FFCC_CHARA_ANIM_H_
