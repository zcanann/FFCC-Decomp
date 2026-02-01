// Function: LookAt__8CGObjectFP8CGObjectPc
// Entry: 8007cdb4
// Size: 80 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LookAt__8CGObjectFP8CGObjectPc(CGObject *gObject,CGObject *param_2,char *param_3)

{
  int16_t iVar1;
  
  gObject->m_lookAtTarget = param_2;
  if (param_3 == (char *)0x0) {
    iVar1 = -1;
  }
  else {
    iVar1 = SearchNode__Q26CChara6CModelFPc(gObject->m_charaModelHandle->m_model,param_3);
  }
  gObject->m_lookAtTargetNodeIndex = iVar1;
  return;
}

