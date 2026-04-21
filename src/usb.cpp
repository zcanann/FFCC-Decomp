#include "ffcc/usb.h"

#include "ffcc/system.h"

CUSB USB;

static const char s_usbCallbackMissingFmt[] = "CUSB.AddMessageCallback: イベント関数は登録されていません。\n";
static const char s_usbCallbackDuplicateFmt[] = "CUSB.AddMessageCallback: 同じイベント関数が既に登録されています。\n";
static const char s_usbCallbackFullFmt[56] = {
    0x43, 0x55, 0x53, 0x42, 0x2E, 0x41, 0x64, 0x64, 0x4D, 0x65, 0x73, 0x73, 0x61, 0x67,
    0x65, 0x43, 0x61, 0x6C, 0x6C, 0x62, 0x61, 0x63, 0x6B, 0x3A, 0x20, 0x83, 0x43, 0x83,
    0x78, 0x83, 0x93, 0x83, 0x67, 0x8A, 0xD6, 0x90, 0x94, 0x82, 0xAA, 0x92, 0xC7, 0x89,
    0xC1, 0x82, 0xC5, 0x82, 0xAB, 0x82, 0xDC, 0x82, 0xB9, 0x82, 0xF1, 0x81, 0x42, 0x0A
};

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
void CUSB::Printf(char*, ...)
{
}

/*
 * --INFO--
 * PAL Address: 0x8002249c
 * PAL Size: 384b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSB::RemoveMessageCallback(MessageCallback callback)
{
    CUSBCallbackEntry* callbackEntry;
    unsigned int i;

    for (callbackEntry = m_callbacks, i = 0; i < 8; callbackEntry++, i++)
    {
        if (callbackEntry->m_inUse != 0 && callbackEntry->m_callback == callback)
        {
            callbackEntry->m_inUse = 0;
            break;
        }
    }

    if (i == 8U)
    {
        System.Printf(const_cast<char*>(s_usbCallbackMissingFmt));
    }
}

/*
 * --INFO--
 * PAL Address: 0x8002261c
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSB::AddMessageCallback(MessageCallback callback, void* callerContext)
{
	CUSBCallbackEntry* callbackEntry;
	unsigned int i;

	for (callbackEntry = m_callbacks, i = 0; i < 8; i++, callbackEntry++)
	{
		if (callbackEntry->m_inUse != 0)
		{
			if (callbackEntry->m_callback == callback)
			{
				System.Printf(const_cast<char*>(s_usbCallbackDuplicateFmt));
				break;
			}
			continue;
		}

		callbackEntry->m_inUse = 1;
		callbackEntry->m_callback = callback;
		callbackEntry->m_callerContext = callerContext;
		break;
	}

	if (i == 8U)
	{
		System.Printf(const_cast<char*>(s_usbCallbackFullFmt));
	}
}

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
int CUSB::IsConnected()
{
	return m_connectionState == 8;
}

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
int CUSB::SendMessage(unsigned long, MCCChannel)
{
	return true;
}

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
int CUSB::Write(void*, int)
{
	return true;
}

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
void CUSB::Frame()
{
}

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
void CUSB::Disconnect()
{
}

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
void CUSB::Connect()
{
	m_connectionState = 7;
}

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
void CUSB::Quit()
{
}

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
void CUSB::Init()
{
}
