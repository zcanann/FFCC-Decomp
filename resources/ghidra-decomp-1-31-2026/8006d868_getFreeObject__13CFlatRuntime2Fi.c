// Function: getFreeObject__13CFlatRuntime2Fi
// Entry: 8006d868
// Size: 512 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CGObject * getFreeObject__13CFlatRuntime2Fi(CFlatRuntime2 *flatRuntime2,int param_2)

{
  CGBaseObj *pCVar1;
  CGQuadObj *pCVar2;
  CGObject *pCVar3;
  CGPartyObj *pCVar4;
  CGItemObj *pCVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  if (param_2 == 3) {
    pCVar4 = m_objParty;
    iVar6 = 0;
    iVar7 = 4;
    do {
      if (-1 < (int)((uint)(pCVar4->gCharaObj).gPrgObj.object.base_object.m_isActive << 0x18)) {
        return (CGObject *)((int)&m_objParty[0].gCharaObj + iVar6 * 0x6f8);
      }
      pCVar4 = (CGPartyObj *)&pCVar4->field_0x6f8;
      iVar6 = iVar6 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  else if (param_2 < 3) {
    if (param_2 == 1) {
      pCVar2 = m_gObjQuadArr;
      iVar6 = 0;
      iVar7 = 0x18;
      do {
        if (-1 < (int)((uint)(pCVar2->field0_0x0).m_isActive << 0x18)) {
          return (CGObject *)(m_gObjQuadArr + iVar6);
        }
        pCVar2 = pCVar2 + 1;
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    else if (param_2 < 1) {
      if (-1 < param_2) {
        pCVar1 = m_gBaseObjArr;
        iVar6 = 0;
        iVar7 = 0x28;
        do {
          if (-1 < (int)((uint)pCVar1->m_isActive << 0x18)) {
            return (CGObject *)(m_gBaseObjArr + iVar6);
          }
          pCVar1 = pCVar1 + 1;
          iVar6 = iVar6 + 1;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
    }
    else {
      pCVar3 = m_gObjArr;
      iVar6 = 0;
      iVar7 = 0x38;
      do {
        if (-1 < (int)((uint)(pCVar3->base_object).m_isActive << 0x18)) {
          return m_gObjArr + iVar6;
        }
        pCVar3 = pCVar3 + 1;
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
  }
  else if (param_2 == 5) {
    pCVar5 = m_objItem;
    iVar6 = 0;
    iVar7 = 0x20;
    do {
      if (-1 < (int)((uint)(pCVar5->prgObj).object.base_object.m_isActive << 0x18)) {
        return (CGObject *)(m_objItem + iVar6);
      }
      pCVar5 = pCVar5 + 1;
      iVar6 = iVar6 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  else if (param_2 < 5) {
    iVar6 = -0x7fd35720;
    iVar7 = 0;
    iVar8 = 0x40;
    do {
      if (-1 < (int)((uint)*(byte *)(iVar6 + 0x4c) << 0x18)) {
        return (CGObject *)(iVar7 * 0x740 + -0x7fd35720);
      }
      iVar6 = iVar6 + 0x740;
      iVar7 = iVar7 + 1;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  return (CGObject *)0x0;
}

