// Function: pppRenderScreenBreak
// Entry: 8012d458
// Size: 168 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderScreenBreak(pppScreenBreak *pppScreenBreak,UnkB *param_2,UnkC *param_3)

{
  CCharaPcsCHandle *handle;
  CModel *model;
  int iVar1;
  
  iVar1 = param_3->m_serializedDataOffsets[2];
  handle = (CCharaPcsCHandle *)
           GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
  model = (CModel *)GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
  SearchNode__Q26CChara6CModelFPc(model,s_f999_root_801dd4c8);
  if ((&pppScreenBreak->field_0xa4)[iVar1] == '\0') {
    GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
              (&Graphic,DAT_80238034,*(undefined4 *)(&pppScreenBreak->field_0x90 + iVar1),0,0,0x280,
               0x1c0,0,1,4,0);
    (&pppScreenBreak->field_0xa4)[iVar1] = 1;
  }
  return;
}

