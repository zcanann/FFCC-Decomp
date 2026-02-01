// Function: CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS
// Entry: 801259e4
// Size: 1168 bytes

/* WARNING: Removing unreachable block (ram,0x80125e58) */
/* WARNING: Removing unreachable block (ram,0x80125e50) */
/* WARNING: Removing unreachable block (ram,0x801259fc) */
/* WARNING: Removing unreachable block (ram,0x801259f4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CGPrgObj *
CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS
          (double param_1,int param_2,uint param_3,uint32_t *param_4,CGObject *gObject,
          undefined4 *param_6)

{
  float fVar1;
  int iVar2;
  CObject *gItemObj;
  CGPrgObj *gPrgObj;
  undefined4 uVar3;
  CCharaPcsCHandle *handle;
  CObject *object;
  void *pvVar4;
  double dVar5;
  double dVar6;
  CStack local_78;
  CVector CStack_74;
  float local_68;
  float local_64;
  float local_60;
  int local_5c;
  uint local_58;
  uint32_t *local_54;
  int local_50;
  float local_4c;
  
  iVar2 = getNumFreeObject__13CFlatRuntime2Fi((CFlatRuntime2 *)&CFlat,5);
  Printf__7CSystemFPce(&System,s_num_free_item____d_801dcec0,iVar2);
  if (iVar2 == 0) {
    iVar2 = 0;
    object = (CObject *)0x0;
    pvVar4 = (void *)0x989680;
    for (gItemObj = (CObject *)FindGItemObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
        gItemObj != (CObject *)0x0;
        gItemObj = (CObject *)
                   FindGItemObjNext__13CFlatRuntime2FP9CGItemObj
                             ((CFlatRuntime2 *)&CFlat,(CGItemObj *)gItemObj)) {
      if ((((gItemObj[0x11].m_0x44 == 0) &&
           ((int)((uint)*(byte *)&gItemObj[1].m_freeListNode << 0x1c |
                 (uint)(*(byte *)&gItemObj[1].m_freeListNode >> 4)) < 0)) &&
          ((*(byte *)((int)&gItemObj[1].m_freeListNode + 3) & 1) != 0)) &&
         ((int)gItemObj[1].m_vtable < (int)pvVar4)) {
        object = gItemObj;
        pvVar4 = gItemObj[1].m_vtable;
      }
    }
    if (object == (CObject *)0x0) {
      if (2 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801dced4);
      }
    }
    else {
      deleteObject__12CFlatRuntimeFPQ212CFlatRuntime7CObject((CFlatRuntime *)&CFlat,object);
      iVar2 = 1;
    }
    Printf__7CSystemFPce(&System,s_num_delete_item____d_801dcef8,iVar2);
    if (iVar2 == 0) {
      if (2 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801dcf10);
      }
      return (CGPrgObj *)0x0;
    }
  }
  if (gObject == (CGObject *)0x0) {
    local_50 = 0;
  }
  else {
    local_50 = (int)(gObject->base_object).object.m_particleId;
  }
  local_4c = (float)param_1;
  DAT_8032ee90 = param_3;
  local_5c = param_2;
  local_58 = param_3;
  local_54 = param_4;
  SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
            (&CFlat,0,1,7,5,&local_5c,&local_78);
  if (param_2 == 1) {
    gPrgObj = (CGPrgObj *)0x0;
  }
  else {
    gPrgObj = (CGPrgObj *)intToClass__13CFlatRuntime2Fi((CFlatRuntime2 *)&CFlat,local_78.m_arg);
    if (param_2 == 2) {
      gPrgObj[1].object.base_object.object.m_stackPointer = param_4;
      (gPrgObj->object).m_radiusCtrl.y = FLOAT_80331b18;
    }
    changeStat__8CGPrgObjFiii(gPrgObj,0x1b,0,0);
    if ((param_3 & 1) != 0) {
      dVar5 = (double)RandFPM__5CMathFf((double)FLOAT_80331b54,&Math);
      dVar6 = (double)(float)((double)gObject->m_rotBaseY + dVar5);
      dVar5 = (double)sin(dVar6);
      fVar1 = FLOAT_80331b1c;
      (gPrgObj->object).m_worldPosition.x =
           FLOAT_80331b1c * (float)dVar5 + (gObject->m_worldPosition).x;
      (gPrgObj->object).m_worldPosition.y = fVar1 + (gObject->m_worldPosition).y;
      dVar5 = (double)cos(dVar6);
      (gPrgObj->object).m_worldPosition.z =
           FLOAT_80331b1c * (float)dVar5 + (gObject->m_worldPosition).z;
      dVar5 = (double)CalcSafePos__8CGObjectFiP8CGObjectP3Vec
                                ((CGObject *)gPrgObj,0x41,gObject,&local_68);
      if ((double)FLOAT_80331b20 < dVar5) {
        moveVectorHRot__8CGObjectFfffi
                  ((double)(FLOAT_80331b8c + gObject->m_rotBaseY),(double)FLOAT_80331b20,
                   (double)(float)(dVar5 / (double)FLOAT_80331b90),gObject,3);
      }
      (gPrgObj->object).m_worldPosition.x = local_68;
      (gPrgObj->object).m_worldPosition.y = local_64;
      (gPrgObj->object).m_worldPosition.z = local_60;
      SetPosBG__8CGObjectFP3Veci((CGObject *)gPrgObj,&local_68,1);
    }
    if ((param_3 & 4) != 0) {
      (gPrgObj->object).m_worldPosition.x = (gObject->m_worldPosition).x;
      (gPrgObj->object).m_worldPosition.y = (gObject->m_worldPosition).y;
      (gPrgObj->object).m_worldPosition.z = (gObject->m_worldPosition).z;
      SetPosBG__8CGObjectFP3Veci((CGObject *)gPrgObj,&(gPrgObj->object).m_worldPosition,1);
      dVar5 = (double)cos(param_1);
      dVar6 = (double)(float)dVar5;
      dVar5 = (double)sin(param_1);
      uVar3 = __ct__7CVectorFfff((float)dVar5,FLOAT_80331b1c,(float)dVar6,&CStack_74);
      MoveVector__8CGObjectFP3Vecfiiii((double)FLOAT_80331b94,(CGObject *)gPrgObj,uVar3,1,0,1,0);
    }
    if ((param_3 & 2) != 0) {
      changeStat__8CGPrgObjFiii(gPrgObj,0x23,0,0);
      fVar1 = FLOAT_80331b98;
      (gPrgObj->object).m_worldPosition.x = (gObject->m_worldPosition).x;
      (gPrgObj->object).m_worldPosition.y = fVar1 + (gObject->m_worldPosition).y;
      (gPrgObj->object).m_worldPosition.z = (gObject->m_worldPosition).z;
      gPrgObj[1].object.base_object.object.m_id = (uint32_t)gObject;
      pvVar4 = gObject->m_scriptHandle[0xed];
      if (2 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801dcf34,pvVar4);
      }
      *(CGPrgObj **)(SoundBuffer + (int)pvVar4 * 4 + 0x4f4) = gPrgObj;
      handle = (CCharaPcsCHandle *)
               __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci
                         (0x194,(CCharaPcsCHandle *)Game.game.m_mainStage,s_itemobj_cpp_801dcf58,
                          0x28e);
      if (handle != (CCharaPcsCHandle *)0x0) {
        handle = (CCharaPcsCHandle *)__ct__Q29CCharaPcs7CHandleFv(handle);
      }
      *(CCharaPcsCHandle **)&gPrgObj[1].object.base_object.object.m_classIndex = handle;
      Add__Q29CCharaPcs7CHandleFv
                (*(CCharaPcsCHandle **)&gPrgObj[1].object.base_object.object.m_classIndex);
      LoadModelASync__Q29CCharaPcs7CHandleFiUlUl
                (*(CCharaPcsCHandle **)&gPrgObj[1].object.base_object.object.m_classIndex,2,
                 param_6[1],param_6[2]);
      if (2 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801dcf64);
      }
      gPrgObj[1].object.base_object.object.m_next = (CObject *)param_6[3];
      gPrgObj[1].object.base_object.object.m_waitCounter = param_6[4];
      gPrgObj[1].object.base_object.object.m_previous = (CObject *)*param_6;
    }
  }
  return gPrgObj;
}

