#include "ffcc/usb.h"

#include "ffcc/system.h"

extern void* __vt__8CManager;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSB::Init()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSB::Quit()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSB::Connect()
{ 
	m_connectionState = 7;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSB::Disconnect()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSB::Frame()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CUSB::Write(void*, int)
{
	return true;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CUSB::SendMessage(unsigned long, MCCChannel)
{
	return true;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CUSB::AddMessageCallback(MessageCallback callback, void* callerContext)
{
	CUSBCallbackEntry* callbackEntry;
	int i;
	int remaining;

	callbackEntry = m_callbacks;
	i = 0;
	remaining = 8;
	while (true)
	{
		if (callbackEntry->m_inUse == 0)
		{
			callbackEntry->m_inUse = 1;
			callbackEntry->m_callback = callback;
			callbackEntry->m_callerContext = callerContext;
			break;
		}

		if (callbackEntry->m_callback == callback)
		{
			System.Printf("CUSB.AddMessageCallback: 同じ");
			break;
		}

		i++;
		callbackEntry++;
		remaining--;
		if (remaining == 0)
		{
			break;
		}
	}

	if (i == 8)
	{
		System.Printf("CUSB.AddMessageCallback: イベント");
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSB::RemoveMessageCallback(MessageCallback callback)
{
    if (m_callbacks[0].m_inUse && m_callbacks[0].m_callback == callback)
    {
        m_callbacks[0].m_inUse = 0;
        return;
    }

    if (m_callbacks[1].m_inUse && m_callbacks[1].m_callback == callback)
    {
        m_callbacks[1].m_inUse = 0;
        return;
    }

    if (m_callbacks[2].m_inUse && m_callbacks[2].m_callback == callback)
    {
        m_callbacks[2].m_inUse = 0;
        return;
    }

    if (m_callbacks[3].m_inUse && m_callbacks[3].m_callback == callback)
    {
        m_callbacks[3].m_inUse = 0;
        return;
    }

    if (m_callbacks[4].m_inUse && m_callbacks[4].m_callback == callback)
    {
        m_callbacks[4].m_inUse = 0;
        return;
    }

    if (m_callbacks[5].m_inUse && m_callbacks[5].m_callback == callback)
    {
        m_callbacks[5].m_inUse = 0;
        return;
    }

    if (m_callbacks[6].m_inUse && m_callbacks[6].m_callback == callback)
    {
        m_callbacks[6].m_inUse = 0;
        return;
    }

    if (m_callbacks[7].m_inUse && m_callbacks[7].m_callback == callback)
    {
        m_callbacks[7].m_inUse = 0;
        return;
    }

    System.Printf("RemoveMessageCallback: callback not found\n");
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSB::Printf(char*, ...)
{
}

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
	*(volatile void**)&USB = &__vt__8CManager;
	*(volatile void**)&USB = &PTR_PTR_DAT_801e88a4;
}
