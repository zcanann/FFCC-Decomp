// Function: moveAStar__8CGMonObjFiiR3Vec
// Entry: 8011367c
// Size: 740 bytes

/* WARNING: Removing unreachable block (ram,0x80113944) */
/* WARNING: Removing unreachable block (ram,0x8011368c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void moveAStar__8CGMonObjFiiR3Vec(CGMonObj *gMonObj,uint param_2,int param_3,Vec *param_4)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  Vec *pVVar4;
  byte *pbVar5;
  uint8_t (*pauVar6) [2];
  double dVar7;
  Vec local_98;
  Vec local_8c;
  Vec local_80;
  Vec local_74;
  CVector aCStack_68 [2];
  CVector CStack_50;
  CVector CStack_44;
  CVector local_38;
  
  if (((*(uint *)&gMonObj->field_0x70c & 0x30000) != 0) && (ARRAY_8030918c._0_4_ != 0)) {
    if (*(short *)&gMonObj->field_0x73c == 0) {
      *(short *)&gMonObj->field_0x73c = (short)param_2;
    }
    if (((*(uint *)&gMonObj->field_0x70c & 0x10000) == 0) ||
       ((*(uint *)&gMonObj->field_0x70c & 0x40) != 0)) {
      if (((*(short *)&gMonObj->field_0x73c != 0) && (param_3 != 0)) &&
         (pVVar4 = (Vec *)getEscapePos__6CAStarFR3VecR3Vecii
                                    ((CAStar *)&DbgMenuPcs.field_0x2a5c,
                                     &(gMonObj->gObject).m_worldPosition,param_4,
                                     (int)*(short *)&gMonObj->field_0x73c,
                                     (int)*(short *)&gMonObj->field_0x73e), pVVar4 != (Vec *)0x0)) {
        uVar2 = (uint)*(byte *)&pVVar4[1].x;
        if (uVar2 == (int)*(short *)&gMonObj->field_0x73c) {
          uVar2 = (uint)*(byte *)((int)&pVVar4[1].x + 1);
        }
        pauVar6 = AStar.m_routeTable[(int)*(short *)&gMonObj->field_0x73c - 1] + uVar2 + 0x36;
        dVar7 = (double)PSVECDistance(&(gMonObj->gObject).m_worldPosition,pVVar4);
        if ((dVar7 < (double)(gMonObj->gObject).m_capsuleHalfHeight) || (param_2 == (*pauVar6)[0]))
        {
          *(undefined2 *)&gMonObj->field_0x73e = *(undefined2 *)&gMonObj->field_0x73c;
          *(ushort *)&gMonObj->field_0x73c = (ushort)(*pauVar6)[0];
          pVVar4 = (Vec *)(ARRAY_8030918c +
                          (uint)AStar.m_routeTable[(*pauVar6)[0] - 1][param_3 + 0x36][1] * 0x10 + 4)
          ;
        }
        dVar7 = (double)PSVECDistance(param_4,&(gMonObj->gObject).m_worldPosition);
        __ct__7CVectorFRC3Vec(&CStack_50,pVVar4);
        pVVar4 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_44,&(gMonObj->gObject).m_worldPosition);
        __ct__7CVectorFv(&local_80);
        PSVECSubtract(pVVar4,(Vec *)&CStack_50,&local_80);
        local_38.x = local_80.x;
        local_38.y = local_80.y;
        local_38.z = local_80.z;
        Normalize__7CVectorFv(&local_38);
        __ct__7CVectorFv(&local_8c);
        PSVECScale((float)dVar7,(Vec *)&local_38,&local_8c);
        local_74.x = local_8c.x;
        local_74.y = local_8c.y;
        local_74.z = local_8c.z;
        pVVar4 = (Vec *)__ct__7CVectorFRC3Vec(aCStack_68,&(gMonObj->gObject).m_worldPosition);
        __ct__7CVectorFv(&local_98);
        PSVECAdd(pVVar4,&local_74,&local_98);
        param_4->x = local_98.x;
        param_4->y = local_98.y;
        param_4->z = local_98.z;
      }
    }
    else {
      sVar1 = *(short *)&gMonObj->field_0x73c;
      if ((sVar1 != 0) && ((param_3 != 0 && (sVar1 != param_3)))) {
        iVar3 = sVar1 * 0x80 + -0x7fcf6e7c + param_3 * 2;
        pbVar5 = (byte *)(iVar3 + 0x40c);
        pVVar4 = (Vec *)(ARRAY_8030918c + (uint)*(byte *)(iVar3 + 0x40d) * 0x10 + 4);
        dVar7 = (double)PSVECDistance(&(gMonObj->gObject).m_worldPosition,pVVar4);
        if ((dVar7 < (double)(gMonObj->gObject).m_capsuleHalfHeight) || (param_2 == *pbVar5)) {
          *(ushort *)&gMonObj->field_0x73c = (ushort)*pbVar5;
          pVVar4 = (Vec *)(ARRAY_8030918c +
                          (uint)AStar.m_routeTable[*pbVar5 - 1][param_3 + 0x36][1] * 0x10 + 4);
        }
        param_4->x = pVVar4->x;
        param_4->y = pVVar4->y;
        param_4->z = pVVar4->z;
      }
    }
  }
  return;
}

