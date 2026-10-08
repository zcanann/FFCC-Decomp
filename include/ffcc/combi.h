#ifndef _FFCC_COMBI_H_
#define _FFCC_COMBI_H_

class CCombi2Set
{
public:
    unsigned short m_item;
    unsigned short m_minFrames;
    unsigned short m_maxFrames;
};

class CCombi2
{
public:
    /*
     * --INFO--
     * PAL Address: UNUSED
     * PAL Size: TODO
     * EN Address: 0x80132aac
     * EN Size: 60b
     * JP Address: TODO
     * JP Size: TODO
     */
    int GetNumSet()
    {
        int i;
        for (i = 0; i < 4; i++) {
            if (m_sets[i].m_item == 0) {
                break;
            }
        }
        return i;
    }

    CCombi2Set m_sets[4];
    unsigned short m_command;
};

#endif
