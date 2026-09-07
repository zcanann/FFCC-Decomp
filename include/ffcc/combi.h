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
        int count = 0;
        if (m_sets[0].m_item != 0) {
            count = 1;
            if (m_sets[1].m_item != 0) {
                count = 2;
                if (m_sets[2].m_item != 0) {
                    count = 3;
                    if (m_sets[3].m_item != 0) {
                        count = 4;
                    }
                }
            }
        }
        return count;
    }

    CCombi2Set m_sets[4];
    unsigned short m_command;
};

#endif
