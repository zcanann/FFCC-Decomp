// Function: getNumFreeObject__13CFlatRuntime2Fi
// Entry: 8006da68
// Size: 1452 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint getNumFreeObject__13CFlatRuntime2Fi(CFlatRuntime2 *flatRuntime2,int param_2)

{
  uint uVar1;
  CGBaseObj *pCVar2;
  CGQuadObj *pCVar3;
  CGObject *pCVar4;
  CGItemObj *pCVar5;
  int iVar6;
  int iVar7;
  
  uVar1 = 0;
  if (param_2 == 3) {
    uVar1 = (uint)(-1 < (int)((uint)m_objParty[0].gCharaObj.gPrgObj.object.base_object.m_isActive <<
                             0x18));
    if (-1 < (int)((uint)m_objParty[1].gCharaObj.gPrgObj.object.base_object.object.m_0x44._0_1_ <<
                  0x18)) {
      uVar1 = uVar1 + 1;
    }
    if (-1 < (int)((uint)m_objParty[2].gCharaObj.gPrgObj.object.base_object.object.m_0x3C._0_1_ <<
                  0x18)) {
      uVar1 = uVar1 + 1;
    }
    if ((int)((uint)m_objParty[3].gCharaObj.gPrgObj.object.base_object.object.m_scriptPriority._0_1_
             << 0x18) < 0) {
      return uVar1;
    }
    return uVar1 + 1;
  }
  if (param_2 < 3) {
    if (param_2 == 1) {
      pCVar3 = m_gObjQuadArr;
      iVar6 = 3;
      do {
        if (-1 < (int)((uint)(pCVar3->field0_0x0).m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar3[1].field0_0x0.m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar3[2].field0_0x0.m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar3[3].field0_0x0.m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar3[4].field0_0x0.m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar3[5].field0_0x0.m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar3[6].field0_0x0.m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar3[7].field0_0x0.m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        pCVar3 = pCVar3 + 8;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      return uVar1;
    }
    if (param_2 < 1) {
      if (param_2 < 0) {
        return uVar1;
      }
      pCVar2 = m_gBaseObjArr;
      iVar6 = 5;
      do {
        if (-1 < (int)((uint)pCVar2->m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar2[1].m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar2[2].m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar2[3].m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar2[4].m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar2[5].m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar2[6].m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        if (-1 < (int)((uint)pCVar2[7].m_isActive << 0x18)) {
          uVar1 = uVar1 + 1;
        }
        pCVar2 = pCVar2 + 8;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      return uVar1;
    }
    pCVar4 = m_gObjArr;
    iVar6 = 7;
    do {
      if (-1 < (int)((uint)(pCVar4->base_object).m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar4[1].base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar4[2].base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar4[3].base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar4[4].base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar4[5].base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar4[6].base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar4[7].base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      pCVar4 = pCVar4 + 8;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    return uVar1;
  }
  if (param_2 == 5) {
    pCVar5 = m_objItem;
    iVar6 = 4;
    do {
      if (-1 < (int)((uint)(pCVar5->prgObj).object.base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar5[1].prgObj.object.base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar5[2].prgObj.object.base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar5[3].prgObj.object.base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar5[4].prgObj.object.base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar5[5].prgObj.object.base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar5[6].prgObj.object.base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      if (-1 < (int)((uint)pCVar5[7].prgObj.object.base_object.m_isActive << 0x18)) {
        uVar1 = uVar1 + 1;
      }
      pCVar5 = pCVar5 + 8;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    return uVar1;
  }
  if (4 < param_2) {
    return uVar1;
  }
  iVar6 = -0x7fd35720;
  iVar7 = 8;
  do {
    if (-1 < (int)((uint)*(byte *)(iVar6 + 0x4c) << 0x18)) {
      uVar1 = uVar1 + 1;
    }
    if (-1 < (int)((uint)*(byte *)(iVar6 + 0x78c) << 0x18)) {
      uVar1 = uVar1 + 1;
    }
    if (-1 < (int)((uint)*(byte *)(iVar6 + 0xecc) << 0x18)) {
      uVar1 = uVar1 + 1;
    }
    if (-1 < (int)((uint)*(byte *)(iVar6 + 0x160c) << 0x18)) {
      uVar1 = uVar1 + 1;
    }
    if (-1 < (int)((uint)*(byte *)(iVar6 + 0x1d4c) << 0x18)) {
      uVar1 = uVar1 + 1;
    }
    if (-1 < (int)((uint)*(byte *)(iVar6 + 0x248c) << 0x18)) {
      uVar1 = uVar1 + 1;
    }
    if (-1 < (int)((uint)*(byte *)(iVar6 + 0x2bcc) << 0x18)) {
      uVar1 = uVar1 + 1;
    }
    if (-1 < (int)((uint)*(byte *)(iVar6 + 0x330c) << 0x18)) {
      uVar1 = uVar1 + 1;
    }
    iVar6 = iVar6 + 0x3a00;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  return uVar1;
}

