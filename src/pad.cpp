#include "ffcc/pad.h"

#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "ffcc/joybus.h"
#include "ffcc/p_dbgmenu.h"

#include "dolphin/pad.h"
#include "dolphin/si.h"

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/FILE_POS.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/direct_io.h"

#include <string.h>

CPad Pad;

void* operator new[](unsigned long, CMemory::CStage*, char*, int);

extern "C" {
unsigned char BYTE_ARRAY_8024430c[0x34] = {};
}
extern "C" float FLOAT_8032f820;
extern "C" float FLOAT_8032f824;
extern "C" float FLOAT_8032f828;
extern "C" double DOUBLE_8032f830;
extern "C" double DOUBLE_8032f838;

static const char s_CPad[] = "CPad";
static const char s_pad_cpp[] = "pad.cpp";
static const char s_rb[] = "rb";
static const char s_replay_dat[] = "/replay.dat";
static const char s_replay_host_msg[] =
    "\x43\x50\x61\x64\x2E\x49\x6E\x69\x74\x3A\x20\x68\x6F\x73\x74\x82\xA9\x82\xE7\x96\xF1\x25\x64\x95\x62\x82\xCC"
    "\x83\x8A\x83\x76\x83\x8C\x83\x43\x83\x66\x81\x5B\x83\x5E\x82\xF0\x93\xC7\x82\xDD\x8D\x9E\x82\xDD\x82\xDC\x82"
    "\xB5\x82\xBD\x81\x42\x0A";

CPad::CPad()
{
	_1b4_4_ = 0;
	_1b8_4_ = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80021008
 * PAL Size: 416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPad::Init()
{
	FILE* fp;
	int frames;
	int size;

	PADInit();
	memset(reinterpret_cast<char*>(this) + 4, 0, 0x1A4);
	_1a8_4_ = 0;
	_1ac_4_ = 0;
	_1b0_4_ = 0;
	_1bc_4_ = 0;
	_1c0_4_ = 0xFFFFFFFF;
	_1c8_4_ = 1;

	if (System.IsGdev())
	{
		_1ac_4_ = Memory.CreateStage(0x800000, const_cast<char*>(s_CPad), 1);
		if (_1ac_4_ != 0)
		{
			_1b0_4_ = new (reinterpret_cast<CMemory::CStage*>(_1ac_4_), const_cast<char*>(s_pad_cpp), 0x54)
				unsigned char[0x69780C];
			if ((_1b4_4_ != 0) && ((fp = fopen(s_replay_dat, s_rb)) != 0))
			{
				fseek(fp, 0, 2);
				size = ftell(fp);
				fseek(fp, 0, 0);
				fread(_1b0_4_, 1, size, fp);
				fclose(fp);
				*reinterpret_cast<unsigned int*>(_1b0_4_ + 4) = 0;
				frames = *reinterpret_cast<int*>(_1b0_4_ + 8);
				System.Printf(const_cast<char*>(s_replay_host_msg), frames / 30);
			}
			else
			{
				*reinterpret_cast<unsigned int*>(_1b0_4_) = 0xC;
				*reinterpret_cast<unsigned int*>(_1b0_4_ + 8) = 0;
				*reinterpret_cast<unsigned int*>(_1b0_4_ + 4) = 1;
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80020fb0
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPad::Quit()
{
	char* const base = reinterpret_cast<char*>(this);
	void* replayBuf = *reinterpret_cast<void**>(base + 0x1B0);
	if (replayBuf != nullptr)
	{
		operator delete[](replayBuf);
		*reinterpret_cast<void**>(base + 0x1B0) = nullptr;
	}

	CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(base + 0x1AC);
	if (stage != nullptr)
	{
		Memory.DestroyStage(stage);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80020494
 * PAL Size: 2844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPad::Frame()
{
	float fVar2;
	float fVar3;
	double dVar4;
	double dVar5;
	int iVar6;
	u16 uVar1;
	u16 uVar8;
	u16* puVar7;
	s8 cVar9;
	u16* puVar10;
	int iVar11;
	u16* puVar12;
	u16* puVar13;
	int iVar14;
	u32 uVar15;
	u32 uVar16;
	u32 uVar17;
	u16* puVar18;
	int iVar19;
	u16 local_98[8];
	u16 local_88[24];
	u8* self = reinterpret_cast<u8*>(this);

	PADRead(reinterpret_cast<PADStatus*>(local_88));
	PADClamp(reinterpret_cast<PADStatus*>(local_88));
	memcpy(BYTE_ARRAY_8024430c, local_88, 0x30);
	*reinterpret_cast<u32*>(self + 0x1C4) = 0;
	uVar17 = 0;
	puVar18 = local_98;
	puVar7 = puVar18;
	do
	{
		iVar6 = SIProbe(uVar17);
		iVar6 = __cntlzw(0x40000 - iVar6);
		*reinterpret_cast<u8*>(puVar7) =
			static_cast<u8>(((iVar6 << 2) & 0x80) | (*reinterpret_cast<u8*>(puVar7) & 0x7F));
		uVar8 = Joybus.GetCtrlMode(uVar17);
		iVar6 = 0;
		*puVar7 = static_cast<u16>((uVar8 & 0x3FFF) | (*puVar7 & 0xC000));
		if ((static_cast<s8>(*reinterpret_cast<u8*>(puVar7)) < 0) && ((*puVar7 & 0x3FFF) == 0))
		{
			iVar6 = 1;
		}
		*reinterpret_cast<u8*>(puVar7) =
			static_cast<u8>((iVar6 << 6) | (*reinterpret_cast<u8*>(puVar7) & 0xBF));
		puVar7[1] = 0;
		if (static_cast<s8>(*reinterpret_cast<u8*>(puVar7)) < 0)
		{
			uVar8 = Joybus.GetPadData(uVar17);
			puVar7[1] = uVar8;
		}
		uVar17 = uVar17 + 1;
		puVar7 = puVar7 + 2;
	} while (uVar17 < 4);

	iVar6 = reinterpret_cast<int>(_1b0_4_);
	if ((iVar6 != 0) && ((iVar14 = _1bc_4_), -1 < iVar14))
	{
		if (*reinterpret_cast<int*>(iVar6 + 4) == 0)
		{
			if (iVar14 < 0x1A5E0)
			{
				iVar6 = 0;
				iVar19 = 0;
				puVar7 = local_88;
				puVar13 = local_98;
				iVar11 = 4;
				do
				{
					uVar8 = *puVar7;
					puVar10 = reinterpret_cast<u16*>(reinterpret_cast<int>(_1b0_4_) + iVar14 * 0x40 + iVar6 + 0x0C);
					*puVar7 = *puVar10;
					*reinterpret_cast<u8*>(puVar7 + 1) = *reinterpret_cast<u8*>(puVar10 + 1);
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 3) =
						*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar10) + 3);
					*reinterpret_cast<u8*>(puVar7 + 2) = *reinterpret_cast<u8*>(puVar10 + 2);
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 5) =
						*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar10) + 5);
					*reinterpret_cast<u8*>(puVar7 + 3) = *reinterpret_cast<u8*>(puVar10 + 3);
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 7) =
						*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar10) + 7);
					*reinterpret_cast<u8*>(puVar7 + 4) = *reinterpret_cast<u8*>(puVar10 + 4);
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 9) =
						*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar10) + 9);
					*reinterpret_cast<u8*>(puVar7 + 5) = *reinterpret_cast<u8*>(puVar10 + 5);
					puVar10 = reinterpret_cast<u16*>(reinterpret_cast<int>(_1b0_4_) + iVar14 * 0x40 + iVar19 + 0x3C);
					uVar1 = puVar10[1];
					*puVar13 = *puVar10;
					puVar13[1] = uVar1;
					if ((uVar8 & PAD_TRIGGER_Z) != 0)
					{
						*puVar7 = static_cast<u16>(*puVar7 | uVar8);
					}
					puVar7 = puVar7 + 6;
					iVar6 = iVar6 + 0x0C;
					iVar19 = iVar19 + 4;
					puVar13 = puVar13 + 2;
					iVar11 = iVar11 + -1;
				} while (iVar11 != 0);
			}
		}
		else if (*reinterpret_cast<int*>(iVar6 + 8) < 0x1A5E0)
		{
			iVar6 = 0;
			iVar14 = 0;
			puVar7 = local_88;
			puVar13 = local_98;
			iVar19 = 4;
			do
			{
				uVar8 = *puVar13;
				uVar1 = puVar13[1];
				iVar11 = *reinterpret_cast<int*>(reinterpret_cast<int>(_1b0_4_) + 8) * 0x40 + iVar6;
				iVar6 = iVar6 + 0x0C;
				puVar13 = puVar13 + 2;
				puVar12 = reinterpret_cast<u16*>(reinterpret_cast<int>(_1b0_4_) + iVar11 + 0x0C);
				*puVar12 = *puVar7;
				*reinterpret_cast<u8*>(puVar12 + 1) = *reinterpret_cast<u8*>(puVar7 + 1);
				*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar12) + 3) =
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 3);
				*reinterpret_cast<u8*>(puVar12 + 2) = *reinterpret_cast<u8*>(puVar7 + 2);
				*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar12) + 5) =
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 5);
				*reinterpret_cast<u8*>(puVar12 + 3) = *reinterpret_cast<u8*>(puVar7 + 3);
				*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar12) + 7) =
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 7);
				*reinterpret_cast<u8*>(puVar12 + 4) = *reinterpret_cast<u8*>(puVar7 + 4);
				*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar12) + 9) =
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 9);
				puVar10 = puVar7 + 5;
				puVar7 = puVar7 + 6;
				*reinterpret_cast<u8*>(puVar12 + 5) = *reinterpret_cast<u8*>(puVar10);
				iVar11 = *reinterpret_cast<int*>(reinterpret_cast<int>(_1b0_4_) + 8) * 0x40 + iVar14;
				iVar14 = iVar14 + 4;
				puVar10 = reinterpret_cast<u16*>(reinterpret_cast<int>(_1b0_4_) + iVar11 + 0x3C);
				*puVar10 = uVar8;
				puVar10[1] = uVar1;
				iVar19 = iVar19 + -1;
			} while (iVar19 != 0);
			*reinterpret_cast<int*>(reinterpret_cast<int>(_1b0_4_) + 8) =
				*reinterpret_cast<int*>(reinterpret_cast<int>(_1b0_4_) + 8) + 1;
			*reinterpret_cast<int*>(_1b0_4_) = *reinterpret_cast<int*>(_1b0_4_) + 0x40;
		}
	}

	puVar13 = local_88;
	puVar10 = reinterpret_cast<u16*>(self + 0x154);
	uVar16 = 0;
	uVar17 = 0;
	puVar7 = puVar13;
	do
	{
		cVar9 = *reinterpret_cast<s8*>(puVar7 + 5);
		uVar15 = 0x80000000 >> uVar17;
		if (cVar9 == -1)
		{
			cVar9 = Joybus.GBAReady(uVar17);
			if (cVar9 == 0)
			{
				uVar16 = uVar16 | uVar15;
			}
			_1a8_4_ = _1a8_4_ & ~uVar15;
		}
		else if (cVar9 < -1)
		{
			if (cVar9 == -3)
			{
				_1a8_4_ = _1a8_4_ | uVar15;
			}
			else if (-4 < cVar9)
			{
				_1a8_4_ = _1a8_4_ & ~uVar15;
			}
		}
		else if (cVar9 < 1)
		{
			_1a8_4_ = _1a8_4_ | uVar15;
		}
		uVar17 = uVar17 + 1;
		puVar7 = puVar7 + 6;
	} while (uVar17 < 4);

	if ((uVar16 & 0xF0000000) != 0)
	{
		PADReset(uVar16 & 0xF0000000);
	}

	fVar2 = FLOAT_8032f820;
	*reinterpret_cast<u16*>(self + 0x1A0) = *puVar10;
	uVar17 = 0;
	*reinterpret_cast<u16*>(self + 0x158) = 0;
	*puVar10 = 0;
	*reinterpret_cast<u16*>(self + 0x1A2) = *reinterpret_cast<u16*>(self + 0x156);
	*reinterpret_cast<u16*>(self + 0x15A) = 0;
	*reinterpret_cast<u16*>(self + 0x156) = 0;
	*reinterpret_cast<u16*>(self + 0x15C) = *reinterpret_cast<u16*>(self + 0x15E);
	*reinterpret_cast<u32*>(self + 0x18C) = 0;
	*reinterpret_cast<u32*>(self + 0x190) = 0;
	*reinterpret_cast<u16*>(self + 0x15E) = 0;
	*reinterpret_cast<u16*>(self + 0x160) = 0;
	*reinterpret_cast<u16*>(self + 0x164) = 0;
	*reinterpret_cast<u16*>(self + 0x162) = 0;
	*reinterpret_cast<u8*>(self + 0x16B) = 0;
	*reinterpret_cast<u8*>(self + 0x16A) = 0;
	*reinterpret_cast<u8*>(self + 0x169) = 0;
	*reinterpret_cast<u8*>(self + 0x168) = 0;
	*reinterpret_cast<u8*>(self + 0x167) = 0;
	*reinterpret_cast<u8*>(self + 0x166) = 0;
	*reinterpret_cast<float*>(self + 0x180) = fVar2;
	*reinterpret_cast<float*>(self + 0x17C) = fVar2;
	*reinterpret_cast<float*>(self + 0x178) = fVar2;
	*reinterpret_cast<float*>(self + 0x174) = fVar2;
	*reinterpret_cast<float*>(self + 0x170) = fVar2;
	*reinterpret_cast<float*>(self + 0x16C) = fVar2;
	*reinterpret_cast<u16*>(self + 0x188) = 0;
	*reinterpret_cast<u16*>(self + 0x186) = 0;
	*reinterpret_cast<u16*>(self + 0x184) = 0;
	*reinterpret_cast<u32*>(self + 0x198) = 0;
	iVar6 = reinterpret_cast<int>(self);
	do
	{
		puVar12 = reinterpret_cast<u16*>(iVar6 + 4);
		iVar14 = 0;
		iVar19 = 2;
		puVar7 = puVar10;
		do
		{
			if ((iVar14 != 0) || (*reinterpret_cast<s8*>(puVar13 + 5) != -3))
			{
				puVar12[0x26] = static_cast<u16>(*reinterpret_cast<u16*>(iVar6 + 0x34) | *puVar12);
				if (iVar14 == 0)
				{
					uVar8 = *puVar18;
					*reinterpret_cast<u16*>(iVar6 + 0x0C) = *reinterpret_cast<u16*>(iVar6 + 0x0E);
					uVar16 = (__cntlzw(1 - (uVar8 & 0x3FFF)) >> 5) & 0xFF;
					*reinterpret_cast<s8*>(iVar6 + 0x44) = *reinterpret_cast<s8*>(puVar13 + 5);
					*reinterpret_cast<u32*>(iVar6 + 0x54) = uVar16;
					*reinterpret_cast<u32*>(iVar6 + 0x48) = 0;
					*reinterpret_cast<u32*>(iVar6 + 0x3C) = 0;
					*reinterpret_cast<u32*>(iVar6 + 0x40) = 0;
					if ((*reinterpret_cast<s8*>(iVar6 + 0x44) == 0) || (((*reinterpret_cast<u8*>(puVar18) >> 6) & 1) != 0))
					{
						if (((*reinterpret_cast<u8*>(puVar18) >> 6) & 1) == 0)
						{
							*puVar12 = *puVar13;
						}
						else
						{
							*puVar12 = puVar18[1];
						}
						if (*reinterpret_cast<u8*>(puVar13 + 3) > 99)
						{
							*puVar12 = static_cast<u16>(*puVar12 | PAD_TRIGGER_L);
						}
						if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar13) + 7) > 99)
						{
							*puVar12 = static_cast<u16>(*puVar12 | PAD_TRIGGER_R);
						}
						if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x100) != 0)
						{
							uVar16 = static_cast<int>(*reinterpret_cast<s8*>(iVar6 + 0x18)) >> 0x1F;
							if ((_1c8_4_ <= static_cast<u32>((uVar16 ^ static_cast<int>(*reinterpret_cast<s8*>(iVar6 + 0x18))) - uVar16)) ||
								((uVar16 = static_cast<int>(*reinterpret_cast<s8*>(iVar6 + 0x19)) >> 0x1F),
								 (_1c8_4_ <= static_cast<u32>((uVar16 ^ static_cast<int>(*reinterpret_cast<s8*>(iVar6 + 0x19))) - uVar16))))
							{
								*puVar12 = static_cast<u16>(*puVar12 & 0xFFF0);
								*reinterpret_cast<u32*>(iVar6 + 0x40) = 1;
								if (_1c8_4_ <= static_cast<u32>(*reinterpret_cast<s8*>(iVar6 + 0x18)))
								{
									*puVar12 = static_cast<u16>(*puVar12 | PAD_BUTTON_RIGHT);
								}
								if (static_cast<int>(*reinterpret_cast<s8*>(iVar6 + 0x18)) <= -static_cast<int>(_1c8_4_))
								{
									*puVar12 = static_cast<u16>(*puVar12 | PAD_BUTTON_LEFT);
								}
								if (_1c8_4_ <= static_cast<u32>(*reinterpret_cast<s8*>(iVar6 + 0x19)))
								{
									*puVar12 = static_cast<u16>(*puVar12 | PAD_BUTTON_UP);
								}
								if (static_cast<int>(*reinterpret_cast<s8*>(iVar6 + 0x19)) <= -static_cast<int>(_1c8_4_))
								{
									*puVar12 = static_cast<u16>(*puVar12 | PAD_BUTTON_DOWN);
								}
							}
						}
						*reinterpret_cast<u32*>(iVar6 + 0x48) = *reinterpret_cast<u32*>(iVar6 + 0x48) | 1;
						*reinterpret_cast<u8*>(iVar6 + 0x18) = *reinterpret_cast<u8*>(puVar13 + 1);
						*reinterpret_cast<u16*>(iVar6 + 0x0E) = 0;
						if (*reinterpret_cast<s8*>(iVar6 + 0x18) < 0)
						{
							*reinterpret_cast<u16*>(iVar6 + 0x0E) = *reinterpret_cast<u16*>(iVar6 + 0x0E) | 1;
						}
						if (0 < *reinterpret_cast<s8*>(iVar6 + 0x18))
						{
							*reinterpret_cast<u16*>(iVar6 + 0x0E) = *reinterpret_cast<u16*>(iVar6 + 0x0E) | 2;
						}
						*reinterpret_cast<u8*>(iVar6 + 0x19) = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar13) + 3);
						if (*reinterpret_cast<s8*>(iVar6 + 0x19) < 0)
						{
							*reinterpret_cast<u16*>(iVar6 + 0x0E) = *reinterpret_cast<u16*>(iVar6 + 0x0E) | 4;
						}
						if (0 < *reinterpret_cast<s8*>(iVar6 + 0x19))
						{
							*reinterpret_cast<u16*>(iVar6 + 0x0E) = *reinterpret_cast<u16*>(iVar6 + 0x0E) | 8;
						}
						dVar4 = DOUBLE_8032f830;
						dVar5 = DOUBLE_8032f838;
						fVar2 = FLOAT_8032f824;
						fVar3 = FLOAT_8032f828;
						*reinterpret_cast<u8*>(iVar6 + 0x1A) = *reinterpret_cast<u8*>(puVar13 + 2);
						*reinterpret_cast<u8*>(iVar6 + 0x1B) = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar13) + 5);
						*reinterpret_cast<u8*>(iVar6 + 0x16) = *reinterpret_cast<u8*>(puVar13 + 3);
						*reinterpret_cast<u8*>(iVar6 + 0x17) = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar13) + 7);
						*reinterpret_cast<float*>(iVar6 + 0x24) =
							static_cast<float>(static_cast<double>(*reinterpret_cast<s8*>(iVar6 + 0x18))) * fVar2;
						*reinterpret_cast<float*>(iVar6 + 0x28) =
							static_cast<float>(static_cast<double>(*reinterpret_cast<s8*>(iVar6 + 0x19))) * fVar2;
						*reinterpret_cast<float*>(iVar6 + 0x2C) =
							static_cast<float>(static_cast<double>(*reinterpret_cast<s8*>(iVar6 + 0x1A))) * fVar2;
						*reinterpret_cast<float*>(iVar6 + 0x30) =
							static_cast<float>(static_cast<double>(*reinterpret_cast<s8*>(iVar6 + 0x1B))) * fVar2;
						*reinterpret_cast<float*>(iVar6 + 0x1C) =
							static_cast<float>(static_cast<double>(*reinterpret_cast<u8*>(iVar6 + 0x16))) / fVar3;
						*reinterpret_cast<float*>(iVar6 + 0x20) =
							static_cast<float>(static_cast<double>(*reinterpret_cast<u8*>(iVar6 + 0x17))) / fVar3;
						static_cast<void>(dVar4);
						static_cast<void>(dVar5);
					}
					else
					{
						*puVar12 = 0;
						fVar2 = FLOAT_8032f820;
						*reinterpret_cast<u8*>(iVar6 + 0x18) = 0;
						*reinterpret_cast<u8*>(iVar6 + 0x19) = 0;
						*reinterpret_cast<u8*>(iVar6 + 0x1A) = 0;
						*reinterpret_cast<u8*>(iVar6 + 0x1B) = 0;
						*reinterpret_cast<u8*>(iVar6 + 0x16) = 0;
						*reinterpret_cast<u8*>(iVar6 + 0x17) = 0;
						*reinterpret_cast<float*>(iVar6 + 0x24) = fVar2;
						*reinterpret_cast<float*>(iVar6 + 0x28) = fVar2;
						*reinterpret_cast<float*>(iVar6 + 0x2C) = fVar2;
						*reinterpret_cast<float*>(iVar6 + 0x30) = fVar2;
						*reinterpret_cast<float*>(iVar6 + 0x1C) = fVar2;
						*reinterpret_cast<float*>(iVar6 + 0x20) = fVar2;
					}
				}
				else if (static_cast<s8>(*reinterpret_cast<u8*>(puVar18)) < 0)
				{
					uVar8 = puVar18[1];
					*reinterpret_cast<u32*>(iVar6 + 0x48) = *reinterpret_cast<u32*>(iVar6 + 0x48) | 1;
					*puVar12 = uVar8;
				}
				puVar12[2] = static_cast<u16>(*puVar12 & (puVar12[0x26] ^ *puVar12));
				if (iVar14 == 0)
				{
					*reinterpret_cast<u16*>(iVar6 + 0x12) =
						static_cast<u16>(puVar12[0x26] & (puVar12[0x26] ^ *puVar12));
					*reinterpret_cast<u16*>(iVar6 + 0x10) =
						static_cast<u16>(*reinterpret_cast<u16*>(iVar6 + 0x0E) &
						                 (*reinterpret_cast<u16*>(iVar6 + 0x0C) ^ *reinterpret_cast<u16*>(iVar6 + 0x0E)));
					*reinterpret_cast<u16*>(iVar6 + 0x14) = static_cast<u16>(puVar12[0x26] & *puVar12 & 0x1F7F);
					if (*reinterpret_cast<s16*>(iVar6 + 0x14) == 0)
					{
						*reinterpret_cast<u32*>(iVar6 + 0x4C) = 0;
					}
					else
					{
						*reinterpret_cast<int*>(iVar6 + 0x4C) = *reinterpret_cast<int*>(iVar6 + 0x4C) + 1;
						if (*reinterpret_cast<u32*>(iVar6 + 0x4C) < 0x10)
						{
							*reinterpret_cast<u16*>(iVar6 + 0x14) = 0;
						}
						else if ((*reinterpret_cast<u32*>(iVar6 + 0x4C) & 1) != 0)
						{
							*reinterpret_cast<u16*>(iVar6 + 0x14) = 0;
						}
					}
					*reinterpret_cast<u16*>(iVar6 + 0x14) =
						static_cast<u16>(*reinterpret_cast<u16*>(iVar6 + 0x14) | puVar12[2]);
					if (*reinterpret_cast<int*>(iVar6 + 0x3C) == 0)
					{
						*reinterpret_cast<u16*>(iVar6 + 0x38) = 0;
						*reinterpret_cast<u16*>(iVar6 + 0x36) = 0;
						*reinterpret_cast<u16*>(iVar6 + 0x34) = 0;
					}
					else
					{
						*reinterpret_cast<u16*>(iVar6 + 0x34) = *puVar12;
						*reinterpret_cast<u16*>(iVar6 + 0x36) = puVar12[2];
						*reinterpret_cast<u16*>(iVar6 + 0x38) = *reinterpret_cast<u16*>(iVar6 + 0x14);
						*reinterpret_cast<u16*>(iVar6 + 0x0E) = 0;
						*reinterpret_cast<u16*>(iVar6 + 0x10) = 0;
						*reinterpret_cast<u16*>(iVar6 + 0x14) = 0;
						puVar12[2] = 0;
						*reinterpret_cast<u16*>(iVar6 + 0x12) = 0;
						*puVar12 = 0;
					}
				}
				puVar7[2] = static_cast<u16>(puVar7[2] | puVar12[2]);
				*puVar7 = static_cast<u16>(*puVar7 | *puVar12);
				if (iVar14 == 0)
				{
					*reinterpret_cast<u32*>(self + 0x18C) =
						*reinterpret_cast<u32*>(self + 0x18C) | *reinterpret_cast<u32*>(iVar6 + 0x3C);
					*reinterpret_cast<u32*>(self + 0x190) =
						*reinterpret_cast<u32*>(self + 0x190) | *reinterpret_cast<u32*>(iVar6 + 0x40);
					*reinterpret_cast<u16*>(self + 0x162) =
						static_cast<u16>(*reinterpret_cast<u16*>(self + 0x162) | *reinterpret_cast<u16*>(iVar6 + 0x12));
					*reinterpret_cast<u16*>(self + 0x15E) =
						static_cast<u16>(*reinterpret_cast<u16*>(self + 0x15E) | *reinterpret_cast<u16*>(iVar6 + 0x0E));
					*reinterpret_cast<u16*>(self + 0x160) =
						static_cast<u16>(*reinterpret_cast<u16*>(self + 0x160) | *reinterpret_cast<u16*>(iVar6 + 0x10));
					*reinterpret_cast<u16*>(self + 0x164) =
						static_cast<u16>(*reinterpret_cast<u16*>(self + 0x164) | *reinterpret_cast<u16*>(iVar6 + 0x14));
					*reinterpret_cast<u16*>(self + 0x186) =
						static_cast<u16>(*reinterpret_cast<u16*>(self + 0x186) | *reinterpret_cast<u16*>(iVar6 + 0x36));
					*reinterpret_cast<u16*>(self + 0x184) =
						static_cast<u16>(*reinterpret_cast<u16*>(self + 0x184) | *reinterpret_cast<u16*>(iVar6 + 0x34));
					*reinterpret_cast<u16*>(self + 0x188) =
						static_cast<u16>(*reinterpret_cast<u16*>(self + 0x188) | *reinterpret_cast<u16*>(iVar6 + 0x38));
					cVar9 = *reinterpret_cast<s8*>(iVar6 + 0x18);
					uVar15 = static_cast<int>(*reinterpret_cast<s8*>(self + 0x168)) >> 0x1F;
					uVar16 = static_cast<int>(cVar9) >> 0x1F;
					if (static_cast<int>((uVar15 ^ static_cast<int>(*reinterpret_cast<s8*>(self + 0x168))) - uVar15) <
					    static_cast<int>((uVar16 ^ static_cast<int>(cVar9)) - uVar16))
					{
						*reinterpret_cast<s8*>(self + 0x168) = cVar9;
						*reinterpret_cast<float*>(self + 0x174) = *reinterpret_cast<float*>(iVar6 + 0x24);
					}
					cVar9 = *reinterpret_cast<s8*>(iVar6 + 0x19);
					uVar15 = static_cast<int>(*reinterpret_cast<s8*>(self + 0x169)) >> 0x1F;
					uVar16 = static_cast<int>(cVar9) >> 0x1F;
					if (static_cast<int>((uVar15 ^ static_cast<int>(*reinterpret_cast<s8*>(self + 0x169))) - uVar15) <
					    static_cast<int>((uVar16 ^ static_cast<int>(cVar9)) - uVar16))
					{
						*reinterpret_cast<s8*>(self + 0x169) = cVar9;
						*reinterpret_cast<float*>(self + 0x178) = *reinterpret_cast<float*>(iVar6 + 0x28);
					}
					cVar9 = *reinterpret_cast<s8*>(iVar6 + 0x1A);
					uVar15 = static_cast<int>(*reinterpret_cast<s8*>(self + 0x16A)) >> 0x1F;
					uVar16 = static_cast<int>(cVar9) >> 0x1F;
					if (static_cast<int>((uVar15 ^ static_cast<int>(*reinterpret_cast<s8*>(self + 0x16A))) - uVar15) <
					    static_cast<int>((uVar16 ^ static_cast<int>(cVar9)) - uVar16))
					{
						*reinterpret_cast<s8*>(self + 0x16A) = cVar9;
						*reinterpret_cast<float*>(self + 0x17C) = *reinterpret_cast<float*>(iVar6 + 0x2C);
					}
					cVar9 = *reinterpret_cast<s8*>(iVar6 + 0x1B);
					uVar15 = static_cast<int>(*reinterpret_cast<s8*>(self + 0x16B)) >> 0x1F;
					uVar16 = static_cast<int>(cVar9) >> 0x1F;
					if (static_cast<int>((uVar15 ^ static_cast<int>(*reinterpret_cast<s8*>(self + 0x16B))) - uVar15) <
					    static_cast<int>((uVar16 ^ static_cast<int>(cVar9)) - uVar16))
					{
						*reinterpret_cast<s8*>(self + 0x16B) = cVar9;
						*reinterpret_cast<float*>(self + 0x180) = *reinterpret_cast<float*>(iVar6 + 0x30);
					}
					if (*reinterpret_cast<u8*>(self + 0x166) < *reinterpret_cast<u8*>(iVar6 + 0x16))
					{
						*reinterpret_cast<u8*>(self + 0x166) = *reinterpret_cast<u8*>(iVar6 + 0x16);
						*reinterpret_cast<float*>(self + 0x16C) = *reinterpret_cast<float*>(iVar6 + 0x1C);
					}
					if (*reinterpret_cast<u8*>(self + 0x167) < *reinterpret_cast<u8*>(iVar6 + 0x17))
					{
						*reinterpret_cast<u8*>(self + 0x167) = *reinterpret_cast<u8*>(iVar6 + 0x17);
						*reinterpret_cast<float*>(self + 0x170) = *reinterpret_cast<float*>(iVar6 + 0x20);
					}
				}
			}
			puVar12 = puVar12 + 1;
			puVar7 = puVar7 + 1;
			iVar14 = iVar14 + 1;
			iVar19 = iVar19 + -1;
		} while (iVar19 != 0);
		uVar17 = uVar17 + 1;
		puVar13 = puVar13 + 6;
		puVar18 = puVar18 + 2;
		iVar6 = iVar6 + 0x54;
	} while (uVar17 < 4);

	if (-1 < _1bc_4_)
	{
		_1bc_4_ = _1bc_4_ + 1;
	}
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPad::SaveReplayData()
{
	// TODO
}
