// Function: onFrame__9CGItemObjFv
// Entry: 80126d08
// Size: 428 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFrame__9CGItemObjFv(CGPrgObj *param_1)

{
  CCharaPcsCHandle *handle;
  int iVar1;
  Vec *position;
  CVector CStack_28;
  undefined4 local_18;
  uint uStack_14;
  
  handle = *(CCharaPcsCHandle **)&param_1[1].object.base_object.object.m_classIndex;
  if ((handle != (CCharaPcsCHandle *)0x0) &&
     (iVar1 = IsLoadModelASyncCompleted__Q29CCharaPcs7CHandleFv(handle), iVar1 != 0)) {
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801dd010);
    }
    (param_1->object).m_charaModelHandle =
         *(CCharaPcsCHandle **)&param_1[1].object.base_object.object.m_classIndex;
    *(undefined4 *)&param_1[1].object.base_object.object.m_classIndex = 0;
    if ((param_1->object).m_worldParamA == 2.84464e-43) {
      LoadAnim__8CGObjectFPciiiUl(&param_1->object);
      SetAnimSlot__8CGObjectFii(&param_1->object,0,0);
      PlayAnim__8CGObjectFiiiiiPSc(&param_1->object,0,1,0,0xffff,0xffff,0);
      iVar1 = *(int *)(*(int *)(SoundBuffer._1260_4_ + 0xf8) + 0x178);
      if (iVar1 == 0) {
        iVar1 = -1;
      }
      else {
        iVar1 = *(int *)(iVar1 + 0x14);
      }
      local_18 = 0x43300000;
      uStack_14 = (uint)*(ushort *)
                         (Game.game.unkCFlatData0[2] + (int)(param_1->object).m_worldParamB * 0x48 +
                         0x10);
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)(FLOAT_80331b50 *
                          (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80331b60) +
                         FLOAT_80331b4c),param_1,
                 iVar1 << 8 |
                 *(uint *)(*(int *)(param_1[1].object.base_object.object.m_id + 0x58) + 0x3b4),
                 (int)param_1[1].object.base_object.object.m_localBase,&param_1->object,0x12909);
      position = (Vec *)__ct__7CVectorFfff(FLOAT_80331b20,FLOAT_80331b20,FLOAT_80331b20,&CStack_28);
      SetDamageCol__8CGObjectFiPcffP3Vec
                ((double)FLOAT_80331bb8,(double)FLOAT_80331bb8,&param_1->object,0,&DAT_80331bc8,
                 position);
      (param_1->object).m_damageColliders[1].m_localPosition.x = 1.12104e-44;
      addSubStat__8CGPrgObjFv(param_1);
    }
  }
  onFrame__8CGPrgObjFv(param_1);
  return;
}

