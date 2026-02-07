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
 * PAL Address: 0x8002261c
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSB::AddMessageCallback(MessageCallback callback, void* callerContext)
{
	CUSBCallbackEntry* callbackEntry = m_callbacks;
	int slot = 0;
	int remaining = 8;

	while (true)
	{
		if (callbackEntry->m_inUse == 0)
		{
			callbackEntry->m_inUse = 1;
			callbackEntry->m_callback = callback;
			callbackEntry->m_callerContext = callerContext;
			goto done;
		}

		if (callbackEntry->m_callback == callback)
		{
			System.Printf("CUSB.AddMessageCallback: 同じ");
			goto done;
		}

		slot++;
		callbackEntry++;
		remaining--;
		if (remaining == 0)
		{
			goto done;
		}
	}

done:
	if (slot == 8)
	{
		System.Printf("CUSB.AddMessageCallback: イベント");
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
	int slot = 0;

	if (!m_callbacks[0].m_inUse || m_callbacks[0].m_callback != callback)
	{
		slot = 1;
		if (!m_callbacks[1].m_inUse || m_callbacks[1].m_callback != callback)
		{
			slot = 2;
			if (!m_callbacks[2].m_inUse || m_callbacks[2].m_callback != callback)
			{
				slot = 3;
				if (!m_callbacks[3].m_inUse || m_callbacks[3].m_callback != callback)
				{
					slot = 4;
					if (!m_callbacks[4].m_inUse || m_callbacks[4].m_callback != callback)
					{
						slot = 5;
						if (!m_callbacks[5].m_inUse || m_callbacks[5].m_callback != callback)
						{
							slot = 6;
							if (!m_callbacks[6].m_inUse || m_callbacks[6].m_callback != callback)
							{
								slot = 7;
								if (!m_callbacks[7].m_inUse || m_callbacks[7].m_callback != callback)
								{
									slot = 8;
								}
								else
								{
									m_callbacks[7].m_inUse = 0;
								}
							}
							else
							{
								m_callbacks[6].m_inUse = 0;
							}
						}
						else
						{
							m_callbacks[5].m_inUse = 0;
						}
					}
					else
					{
						m_callbacks[4].m_inUse = 0;
					}
				}
				else
				{
					m_callbacks[3].m_inUse = 0;
				}
			}
			else
			{
				m_callbacks[2].m_inUse = 0;
			}
		}
		else
		{
			m_callbacks[1].m_inUse = 0;
		}
	}
	else
	{
		m_callbacks[0].m_inUse = 0;
	}

	if (slot == 8)
	{
		System.Printf("RemoveMessageCallback: callback not found\n");
	}
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
