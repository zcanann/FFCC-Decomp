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
#include <stddef.h>

CPad Pad;

void* operator new[](unsigned long, CMemory::CStage*, char*, int);

static const char s_CPad[] = "CPad";
static const char s_replay_dat[] = "/replay.dat";
static const char s_replay_host_msg[] = {
    0x43, 0x50, 0x61, 0x64, 0x2E, 0x49, 0x6E, 0x69, 0x74, 0x3A, 0x20, 0x68, 0x6F,
    0x73, 0x74, 0x82, 0xA9, 0x82, 0xE7, 0x96, 0xF1, 0x25, 0x64, 0x95, 0x62, 0x82,
    0xCC, 0x83, 0x8A, 0x83, 0x76, 0x83, 0x8C, 0x83, 0x43, 0x83, 0x66, 0x81, 0x5B,
    0x83, 0x5E, 0x82, 0xF0, 0x93, 0xC7, 0x82, 0xDD, 0x8D, 0x9E, 0x82, 0xDD, 0x82,
    0xDC, 0x82, 0xB5, 0x82, 0xBD, 0x81, 0x42, 0x0A, 0x00, 0x00, 0x00, 0x00,
};

extern "C" {
PADStatus g_pad[4];
}

typedef char ReplayFrame_size_check[(sizeof(CPad::ReplayFrame) == 0x40) ? 1 : -1];
typedef char ReplayBuffer_size_check[(sizeof(CPad::ReplayBuffer) == 0x69780C) ? 1 : -1];
typedef char CPad_ReplayFrame_gba_offset_check[(offsetof(CPad::ReplayFrame, gba) == 0x30) ? 1 : -1];
typedef char CPad_ReplayBuffer_frames_offset_check[(offsetof(CPad::ReplayBuffer, frames) == 0xC) ? 1 : -1];
typedef char CPad_m_replayBuffer_offset_check[(offsetof(CPad, m_replayBuffer) == 0x1B0) ? 1 : -1];
typedef char CPad_m_replayFrame_offset_check[(offsetof(CPad, m_replayFrame) == 0x1BC) ? 1 : -1];

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CPad::SaveReplayData()
{
    ReplayBuffer* replay = m_replayBuffer;

    if ((replay != 0) && (replay->recordMode != 0) && (replay->cursor <= sizeof(ReplayBuffer)) &&
        (replay->frameCount != 0)) {
        FILE* fp = fopen(s_replay_dat, "wb");
        if (fp != 0) {
            fwrite(replay, 1, replay->cursor, fp);
            fclose(fp);
        }
    }
}


/*
 * --INFO--
 * PAL Address: 0x80020494
 * PAL Size: 2844b
 * EN Address: 0x8002A444
 * EN Size: 3472b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPad::Frame()
{
	Gba gbaStatus[4];
	PADStatus padStatus[4];

	PADRead(padStatus);
	PADClamp(padStatus);
	memcpy(g_pad, padStatus, sizeof(g_pad));
	m_debugPadLock = 0;

	for (u32 port = 0; port < 4; port++) {
		Gba* gba = &gbaStatus[port];
		gba->connected = SIProbe(port) == SI_GBA;
		gba->ctrlMode = Joybus.GetCtrlMode(port);
		gba->noController = gba->connected && gba->ctrlMode == 0;
		gba->button = 0;
		if (gba->connected) {
			gba->button = Joybus.GetPadData(port);
		}
	}

	int replayFrame = m_replayFrame;
	if (m_replayBuffer != 0 && replayFrame >= 0) {
		if (m_replayBuffer->recordMode != 0) {
			if (m_replayBuffer->frameCount < 0x1A5E0) {
				for (int port = 0; port < 4; port++) {
					m_replayBuffer->frames[m_replayBuffer->frameCount].pad[port] = padStatus[port];
					m_replayBuffer->frames[m_replayBuffer->frameCount].gba[port] = gbaStatus[port];
				}
				m_replayBuffer->frameCount++;
				m_replayBuffer->cursor += sizeof(ReplayFrame);
			}
		} else if (replayFrame < 0x1A5E0) {
			for (int port = 0; port < 4; port++) {
				u16 buttons = padStatus[port].button;
				padStatus[port] = m_replayBuffer->frames[replayFrame].pad[port];
				gbaStatus[port] = m_replayBuffer->frames[replayFrame].gba[port];
				if ((buttons & PAD_TRIGGER_Z) != 0) {
					padStatus[port].button |= buttons;
				}
			}
		}
	}

	u32 resetMask = 0;
	for (u32 port = 0; port < 4; port++) {
		u32 mask = 0x80000000 >> port;
		switch (padStatus[port].err) {
		case PAD_ERR_NONE:
		case PAD_ERR_NOT_READY:
			_1a8_4_ |= mask;
			break;
		case PAD_ERR_NO_CONTROLLER:
			if (static_cast<u8>(Joybus.GBAReady(port)) == 0) {
				resetMask |= mask;
			}
			_1a8_4_ &= ~mask;
			break;
		case PAD_ERR_TRANSFER:
			_1a8_4_ &= ~mask;
			break;
		}
	}
	if ((resetMask & 0xF0000000) != 0) {
		PADReset(resetMask & 0xF0000000);
	}

	PADStatus* rawPad = padStatus;
	Gba* gba = gbaStatus;
	u32 port;
	PadInput* input;
	s8 axisValue;

	const float zero = 0.0f;
	PadInput* merged = &m_padInputs[4];
	merged->buttonPrev[0] = merged->button[0];
	port = 0;
	merged->buttonDown[0] = 0;
	merged->button[0] = 0;
	merged->buttonPrev[1] = merged->button[1];
	merged->buttonDown[1] = 0;
	merged->button[1] = 0;
	merged->stickBitsPrev = merged->stickBits;
	merged->holdOverride = 0;
	merged->digitalStickOverride = 0;
	merged->stickBits = 0;
	merged->stickBitsDown = 0;
	merged->repeatButton = 0;
	merged->buttonUp = 0;
	merged->substickY = 0;
	merged->substickX = 0;
	merged->stickY = 0;
	merged->stickX = 0;
	merged->triggerRight = 0;
	merged->triggerLeft = 0;
	merged->substickYF = zero;
	merged->substickXF = zero;
	merged->stickYF = zero;
	merged->stickXF = zero;
	merged->triggerRightF = zero;
	merged->triggerLeftF = zero;
	merged->lockedButton[2] = 0;
	merged->lockedButton[1] = 0;
	merged->lockedButton[0] = 0;
	merged->activeMask = 0;
	input = m_padInputs;
	do
	{
		for (int channel = 0; channel < 2; channel++)
		{
			if ((channel != 0) || (rawPad->err != PAD_ERR_NOT_READY))
			{
				input->buttonPrev[channel] = static_cast<u16>(input->lockedButton[0] | input->button[channel]);
				if (channel == 0)
				{
					input->stickBitsPrev = input->stickBits;
					input->err = rawPad->err;
					input->gbaMode = gba->ctrlMode == 1;
					input->activeMask = 0;
					input->holdOverride = 0;
					input->digitalStickOverride = 0;
					if ((input->err == PAD_ERR_NONE) || gba->noController)
					{
						if (gba->noController)
						{
							input->button[channel] = gba->button;
						}
						else
						{
							input->button[channel] = rawPad->button;
						}
						if (rawPad->triggerLeft >= 100)
						{
							input->button[channel] = static_cast<u16>(input->button[channel] | PAD_TRIGGER_L);
						}
						if (rawPad->triggerRight >= 100)
						{
							input->button[channel] = static_cast<u16>(input->button[channel] | PAD_TRIGGER_R);
						}
						if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x100) != 0)
						{
							if (__abs(input->stickX) >= m_stickDigitalThreshold ||
							    __abs(input->stickY) >= m_stickDigitalThreshold)
							{
								input->button[channel] = static_cast<u16>(input->button[channel] & 0xFFF0);
								input->digitalStickOverride = 1;
								if (m_stickDigitalThreshold <= static_cast<int>(input->stickX))
								{
									input->button[channel] = static_cast<u16>(input->button[channel] | PAD_BUTTON_RIGHT);
								}
								if (-static_cast<int>(m_stickDigitalThreshold) >= static_cast<int>(input->stickX))
								{
									input->button[channel] = static_cast<u16>(input->button[channel] | PAD_BUTTON_LEFT);
								}
								if (m_stickDigitalThreshold <= static_cast<int>(input->stickY))
								{
									input->button[channel] = static_cast<u16>(input->button[channel] | PAD_BUTTON_UP);
								}
								if (-static_cast<int>(m_stickDigitalThreshold) >= static_cast<int>(input->stickY))
								{
									input->button[channel] = static_cast<u16>(input->button[channel] | PAD_BUTTON_DOWN);
								}
							}
						}
						input->activeMask = input->activeMask | 1;
						input->stickX = rawPad->stickX;
						input->stickBits = 0;
						if (input->stickX < 0)
						{
							input->stickBits = input->stickBits | 1;
						}
						if (0 < input->stickX)
						{
							input->stickBits = input->stickBits | 2;
						}
						input->stickY = rawPad->stickY;
						if (input->stickY < 0)
						{
							input->stickBits = input->stickBits | 4;
						}
						if (0 < input->stickY)
						{
							input->stickBits = input->stickBits | 8;
						}
						const float analogScale = 0.0078125f;
						const float triggerMax = 255.0f;
						input->substickX = rawPad->substickX;
						input->substickY = rawPad->substickY;
						input->triggerLeft = rawPad->triggerLeft;
						input->triggerRight = rawPad->triggerRight;
						input->stickXF =
							static_cast<float>(input->stickX) * analogScale;
						input->stickYF =
							static_cast<float>(input->stickY) * analogScale;
						input->substickXF =
							static_cast<float>(input->substickX) * analogScale;
						input->substickYF =
							static_cast<float>(input->substickY) * analogScale;
						input->triggerLeftF =
							static_cast<float>(input->triggerLeft) / triggerMax;
						input->triggerRightF =
							static_cast<float>(input->triggerRight) / triggerMax;
					}
					else
					{
						input->button[channel] = 0;
						input->stickX = 0;
						input->stickY = 0;
						input->substickX = 0;
						input->substickY = 0;
						input->triggerLeft = 0;
						input->triggerRight = 0;
						input->stickXF = zero;
						input->stickYF = zero;
						input->substickXF = zero;
						input->substickYF = zero;
						input->triggerLeftF = zero;
						input->triggerRightF = zero;
					}
				}
				else if (gba->connected)
				{
					input->activeMask = input->activeMask | 1;
					input->button[channel] = gba->button;
				}
				input->buttonDown[channel] = static_cast<u16>(input->button[channel] & (input->buttonPrev[channel] ^ input->button[channel]));
				if (channel == 0)
				{
					input->buttonUp =
						static_cast<u16>(input->buttonPrev[channel] & (input->buttonPrev[channel] ^ input->button[channel]));
					input->stickBitsDown =
						static_cast<u16>(input->stickBits &
						                 (input->stickBitsPrev ^ input->stickBits));
					input->repeatButton = static_cast<u16>(input->buttonPrev[channel] & input->button[channel] & 0x1F7F);
					if (input->repeatButton != 0)
					{
						input->hasInputMask++;
						if (input->hasInputMask < 0x10)
						{
							input->repeatButton = 0;
						}
						else if ((input->hasInputMask & 1) != 0)
						{
							input->repeatButton = 0;
						}
					}
					else
					{
						input->hasInputMask = 0;
					}
					input->repeatButton =
						static_cast<u16>(input->repeatButton | input->buttonDown[channel]);
					if (input->holdOverride != 0)
					{
						input->lockedButton[0] = input->button[channel];
						input->lockedButton[1] = input->buttonDown[channel];
						input->lockedButton[2] = input->repeatButton;
						input->stickBits = 0;
						input->stickBitsDown = 0;
						input->repeatButton = 0;
						input->buttonDown[channel] = 0;
						input->buttonUp = 0;
						input->button[channel] = 0;
					}
					else
					{
						input->lockedButton[2] = 0;
						input->lockedButton[1] = 0;
						input->lockedButton[0] = 0;
					}
				}
				merged->buttonDown[channel] = static_cast<u16>(merged->buttonDown[channel] | input->buttonDown[channel]);
				merged->button[channel] = static_cast<u16>(merged->button[channel] | input->button[channel]);
				if (channel == 0)
				{
					merged->holdOverride =
						merged->holdOverride | input->holdOverride;
					merged->digitalStickOverride =
						merged->digitalStickOverride | input->digitalStickOverride;
					merged->buttonUp =
						static_cast<u16>(merged->buttonUp | input->buttonUp);
					merged->stickBits =
						static_cast<u16>(merged->stickBits | input->stickBits);
					merged->stickBitsDown =
						static_cast<u16>(merged->stickBitsDown | input->stickBitsDown);
					merged->repeatButton =
						static_cast<u16>(merged->repeatButton | input->repeatButton);
					merged->lockedButton[1] =
						static_cast<u16>(merged->lockedButton[1] | input->lockedButton[1]);
					merged->lockedButton[0] =
						static_cast<u16>(merged->lockedButton[0] | input->lockedButton[0]);
					merged->lockedButton[2] =
						static_cast<u16>(merged->lockedButton[2] | input->lockedButton[2]);
					axisValue = input->stickX;
					if (__abs(merged->stickX) < __abs(axisValue))
					{
						merged->stickX = axisValue;
						merged->stickXF = input->stickXF;
					}
					axisValue = input->stickY;
					if (__abs(merged->stickY) < __abs(axisValue))
					{
						merged->stickY = axisValue;
						merged->stickYF = input->stickYF;
					}
					axisValue = input->substickX;
					if (__abs(merged->substickX) < __abs(axisValue))
					{
						merged->substickX = axisValue;
						merged->substickXF = input->substickXF;
					}
					axisValue = input->substickY;
					if (__abs(merged->substickY) < __abs(axisValue))
					{
						merged->substickY = axisValue;
						merged->substickYF = input->substickYF;
					}
					if (merged->triggerLeft < input->triggerLeft)
					{
						merged->triggerLeft = input->triggerLeft;
						merged->triggerLeftF = input->triggerLeftF;
					}
					if (merged->triggerRight < input->triggerRight)
					{
						merged->triggerRight = input->triggerRight;
						merged->triggerRightF = input->triggerRightF;
					}
				}
			}
		}
		port = port + 1;
		input++;
		rawPad++;
		gba++;
	} while (port < 4);

	if (m_replayFrame >= 0)
	{
		m_replayFrame++;
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
	if (m_replayBuffer != 0)
	{
		delete[] reinterpret_cast<unsigned char*>(m_replayBuffer);
		m_replayBuffer = 0;
	}

	CMemory::CStage* stage = reinterpret_cast<CMemory::CStage*>(_1ac_4_);
	if (stage != 0)
	{
		Memory.DestroyStage(stage);
	}
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
	memset(m_padInputs, 0, sizeof(m_padInputs));
	_1a8_4_ = 0;
	_1ac_4_ = 0;
	m_replayBuffer = 0;
	m_replayFrame = 0;
	m_debugPadPort = 0xFFFFFFFF;
	m_stickDigitalThreshold = 1;

	if (System.IsGdev())
	{
		_1ac_4_ = Memory.CreateStage(0x800000, const_cast<char*>(s_CPad), 1);
		if (_1ac_4_ != 0)
		{
			m_replayBuffer = reinterpret_cast<ReplayBuffer*>(new (reinterpret_cast<CMemory::CStage*>(_1ac_4_), "pad.cpp", 0x54)
				unsigned char[sizeof(ReplayBuffer)]);
			if ((_1b4_4_ != 0) && ((fp = fopen(s_replay_dat, "rb")) != 0))
			{
				fseek(fp, 0, 2);
				size = ftell(fp);
				fseek(fp, 0, 0);
				fread(m_replayBuffer, 1, size, fp);
				fclose(fp);
				m_replayBuffer->recordMode = 0;
				frames = m_replayBuffer->frameCount;
				System.Printf(const_cast<char*>(s_replay_host_msg), frames / 30);
			}
			else
			{
				m_replayBuffer->cursor = 0xC;
				m_replayBuffer->frameCount = 0;
				m_replayBuffer->recordMode = 1;
			}
		}
	}
}
