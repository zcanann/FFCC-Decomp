// Function: initFinishedFuncLastBoss__8CGMonObjFv
// Entry: 8012f534
// Size: 100 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void initFinishedFuncLastBoss__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  
  initFinishedFuncDefault__8CGMonObjFv(gMonObj);
  SoundBuffer._1260_4_ = gMonObj;
  iVar1 = SearchNode__Q26CChara6CModelFPc
                    (((gMonObj->gObject).m_charaModelHandle)->m_model,&DAT_80331d50);
  SoundBuffer._1264_4_ = ((gMonObj->gObject).m_charaModelHandle)->m_model->m_nodes + iVar1;
  return;
}

