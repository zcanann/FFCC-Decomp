// Function: __ct__Q26CChara5CNodeFv
// Entry: 80070110
// Size: 96 bytes

CNode * __ct__Q26CChara5CNodeFv(CNode *node)

{
  __ct__7CVectorFv(&node->m_dynPosition);
  __ct__7CVectorFv(&node->m_dynVel);
  node->m_refData = (CNodeCRefData *)0x0;
  node->field1_0x4 = (void *)0x0;
  node->m_animNode0 = (void *)0x0;
  node->m_animNode1 = (void *)0x0;
  node->m_flags = node->m_flags & 0x7f | 0x80;
  return node;
}

