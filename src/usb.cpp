#include "ffcc/usb.h"

#include "ffcc/system.h"

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
	for (int i = 0; i < 8; i++)
	{
		if (m_callbacks[i].m_inUse == 0)
		{
			m_callbacks[i].m_inUse = 1;
			m_callbacks[i].m_callback = callback;
			m_callbacks[i].m_callerContext = callerContext;
			return;
		}

		if (m_callbacks[i].m_callback == callback)
		{
			System.Printf("CUSB.AddMessageCallback: 同じ");
			return;
		}
	}

	System.Printf("CUSB.AddMessageCallback: イベント");
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
 * Address: 80022704
 * Size: 32b
 */
void __sinit_usb_cpp()
{
	USB.m_managerStringTable = &PTR_PTR_DAT_801e88a4;
}
