#include "ffcc/usb.h"

#include "ffcc/symbols_shared.h"
#include "ffcc/system.h"
extern "C" char __vt__8CManager[];

/*
 * --INFO--
 * PAL Address: 0x80022704
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_usb_cpp()
{
	void* vtbl = __vt__8CManager;
	*reinterpret_cast<void**>(&USB) = vtbl;
	*reinterpret_cast<void**>(&USB) = __vt__4CUSB;
}

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
        System.Printf(s_CUSBAddMessageCallbackNotRegistered_801D6F9C);
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
				System.Printf(s_CUSBDuplicateMessageCallback_801D6FDC);
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
		System.Printf(s_CUSBMessageCallbackTableFull_801D7020);
	}
}

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
bool CUSB::IsConnected()
{
	if (m_connectionState == 8)
	{
		return true;
	}

	return false;
}

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
bool CUSB::SendMessage(unsigned long, MCCChannel)
{
	return true;
}

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
bool CUSB::Write(void*, int)
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
