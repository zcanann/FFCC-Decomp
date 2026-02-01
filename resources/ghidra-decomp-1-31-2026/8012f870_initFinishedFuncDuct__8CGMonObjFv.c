// Function: initFinishedFuncDuct__8CGMonObjFv
// Entry: 8012f870
// Size: 76 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void initFinishedFuncDuct__8CGMonObjFv(CGMonObj *gMonObj)

{
  initFinishedFuncDefault__8CGMonObjFv(gMonObj);
  *(CGMonObj **)
   ((int)&m_boss__8CGMonObj + ((int)(gMonObj->gObject).m_scriptHandle[4] + -0x8e) * 4 + 0x18) =
       gMonObj;
  return;
}

