#ifndef _PPP_POINT_H_
#define _PPP_POINT_H_

struct _pppPObject;
struct _pppCtrlTable;

struct pppPointStep
{
    int m_graphId;
    float m_unknown4;
    float m_x;
    float m_y;
    float m_z;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppPoint(_pppPObject* pObject, pppPointStep* step, _pppCtrlTable* ctrlTable);
void pppPointCon(_pppPObject* pObject, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POINT_H_
