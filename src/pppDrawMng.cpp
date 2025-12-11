#include "ffcc/pppDrawMng.h"

#include "ffcc/graphic.h"
#include "ffcc/p_chara.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawMng::ClearOt()
{
	int count = sizeof(m_primitiveRefs) / sizeof(pppDrawPrimitive*);
	pppDrawPrimitive** primitiveRef = m_primitiveRefs;

	if (Game.game.m_currentMapId == 0x21)
	{
		m_depthScale = 0.0512f; // FLOAT_80330330
	}
	else
	{
		m_depthScale = 0.512f; // FLOAT_80330334
	}

	do
	{
		count--;
		*primitiveRef++ = (pppDrawMng::pppDrawPrimitive*)nullptr;
	}
	while (count != 0);

	m_nextFree = m_primitivePool;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawMng::DrawOt()
{
    int count = sizeof(m_primitiveRefs) / sizeof(m_primitiveRefs[0]);   // 0x400
    pppDrawPrimitive** slot = m_primitiveRefs + (count - 1);
    unsigned char lastType = 3;

    do
    {
        pppDrawPrimitive* prim = *slot;
		
        if (prim != 0)
        {
            do
            {
                unsigned char type = prim->m_type;

                switch (type)
                {
                case 0:
                    if (lastType != type)
                    {
                        pppInitDrawEnv(0);
                    }

                    pppEnvStPtr = (_pppEnvSt*)((char*)(*(void**)prim->m_handle) + 4);
                    pppMngStPtr = (_pppMngSt*)prim->m_handle;

                    pppSetFpMatrix((_pppMngSt*)prim->m_handle);
                    _pppDrawPart((_pppMngSt*)prim->m_handle);
                    break;
                case 1:
                    Graphic.SetDrawDoneDebugDataPartControl(0x7ffe);

                    if (lastType != prim->m_type)
                    {
                        pppInitDrawEnv(0);
                        CharaPcs.InitEnv(4);
                    }

                    ((CCharaPcs::CHandle*)prim->m_handle)->Draw(4);

                    Graphic.SetDrawDoneDebugDataPartControl(0x7fff);
                    break;

                default:
                    break;
                }

                lastType = prim->m_type;
                prim = prim->m_next;
            }
            while (prim != 0);
        }

        count--;
        slot--;
    }
    while (count != 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawMng::AddPrimOt(unsigned long otIndex, _pppMngSt* pppMngSt)
{
	if (m_nextFree >= m_primitivePool + sizeof(m_primitivePool) / sizeof(pppDrawPrimitive))
	{
		return;
	}

	pppDrawPrimitive* primative = m_nextFree++;

	primative->m_type = 0;
	primative->m_handle = pppMngSt;
	primative->m_next = m_primitiveRefs[otIndex];
	m_primitiveRefs[otIndex] = primative;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawMng::AddPrim(float depth, _pppMngSt* pppMngSt, signed char offset)
{
	int index = 0x100 - static_cast<int>(depth * m_depthScale);

	if (index < 0 || index >= (int)(sizeof(m_primitiveRefs) / sizeof(pppDrawPrimitive*)))
	{
		return;
	}

	if (offset != 0)
	{
		index += static_cast<int>(offset);

		if (index < 0)
		{
			index = 0;
		}
		else if (index >= (int)(sizeof(m_primitiveRefs) / sizeof(pppDrawPrimitive*)))
		{
			index = sizeof(m_primitiveRefs) / sizeof(pppDrawPrimitive*) - 1;
		}
	}

	if (m_nextFree >= m_primitivePool + sizeof(m_primitivePool) / sizeof(pppDrawPrimitive))
	{
		return;
	}

	pppDrawPrimitive* primative = m_nextFree++;

	primative->m_type = 0;
	primative->m_handle = pppMngSt;
	primative->m_next = m_primitiveRefs[index];
	m_primitiveRefs[index] = primative;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawMng::AddPrim(float depth, CCharaPcs::CHandle* handle)
{
	pppDrawPrimitive* primative;
	int index = 0x100 - (int)(depth * m_depthScale);

	if (index < 0 || index >= (int)(sizeof(m_primitiveRefs) / sizeof(pppDrawPrimitive*)))
	{
		return;
	}

	primative = m_nextFree;

	if (primative >= m_primitivePool + sizeof(m_primitivePool) / sizeof(pppDrawPrimitive)) {
		return;
	}

	m_nextFree++;

	primative->m_type = 1;
	primative->m_handle = handle;
	primative->m_next = m_primitiveRefs[index];
	m_primitiveRefs[index] = primative;
}
