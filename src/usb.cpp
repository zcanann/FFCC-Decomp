#include "ffcc/usb.h"

#include "ffcc/system.h"

CUSB USB;

static const char s_usbCallbackMissingFmt[] = "CUSB.AddMessageCallback: イベント関数は登録されていません。\n";
static const char s_usbCallbackDuplicateFmt[] = "CUSB.AddMessageCallback: 同じイベント関数が既に登録されています。\n";
static const char s_usbCallbackFullFmt[] = "CUSB.AddMessageCallback: イベント関数が追加できません。\n";

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
