#include "ffcc/usb.h"

#include "ffcc/system.h"

CUSB USB;

/*
 * --INFO--
 * PAL Address: 0x80022700
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSB::Init()
{
}

/*
 * --INFO--
 * PAL Address: 0x800226fc
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSB::Quit()
{
}

/*
 * --INFO--
 * PAL Address: 0x800226f0
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSB::Connect()
{
	m_connectionState = 7;
}

/*
 * --INFO--
 * PAL Address: 0x800226ec
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSB::Disconnect()
{
}

/*
 * --INFO--
 * PAL Address: 0x800226e8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSB::Frame()
{
}

/*
 * --INFO--
 * PAL Address: 0x800226e0
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CUSB::Write(void*, int)
{
	return true;
}

/*
 * --INFO--
 * PAL Address: 0x800226d8
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CUSB::SendMessage(unsigned long, MCCChannel)
{
	return true;
}

/*
 * --INFO--
 * PAL Address: 0x800226c4
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CUSB::IsConnected()
{
	return m_connectionState == 8;
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
				System.Printf("CUSB.AddMessageCallback: 同じイベント関数が既に登録されています。\n");
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
		System.Printf("CUSB.AddMessageCallback: イベント関数が追加できません。\n");
	}
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
        System.Printf("CUSB.AddMessageCallback: イベント関数は登録されていません。\n");
    }
}

/*
 * --INFO--
 * PAL Address: 0x8002244c
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSB::Printf(char*, ...)
{
}
