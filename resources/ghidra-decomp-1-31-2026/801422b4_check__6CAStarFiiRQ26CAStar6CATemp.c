// Function: check__6CAStarFiiRQ26CAStar6CATemp
// Entry: 801422b4
// Size: 1964 bytes

void check__6CAStarFiiRQ26CAStar6CATemp(CAStar *aStar,uint param_2,uint param_3,CATemp *aTemp)

{
  uint8_t *puVar1;
  bool bVar2;
  int32_t iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  CAPos *aPos;
  Vec *inVecA;
  int iVar9;
  double dVar10;
  CATemp CStack_254;
  CATemp local_1cc;
  uint8_t local_144 [4];
  uint8_t local_140 [4];
  uint8_t local_13c [4];
  uint8_t local_138 [4];
  uint8_t local_134 [4];
  uint8_t local_130 [4];
  uint8_t local_12c [4];
  uint8_t local_128 [4];
  uint8_t local_124 [4];
  uint8_t local_120 [4];
  uint8_t local_11c [4];
  uint8_t local_118 [4];
  uint8_t local_114 [4];
  uint8_t local_110 [4];
  uint8_t local_10c [4];
  uint8_t local_108 [4];
  uint8_t local_104 [4];
  uint8_t local_100 [4];
  uint8_t local_fc [4];
  uint8_t local_f8 [4];
  uint8_t local_f4 [4];
  uint8_t local_f0 [4];
  uint8_t local_ec [4];
  uint8_t local_e8 [4];
  uint8_t local_e4 [4];
  uint8_t local_e0 [4];
  uint8_t local_dc [4];
  uint8_t local_d8 [4];
  uint8_t local_d4 [4];
  uint8_t local_d0 [4];
  uint8_t local_cc [4];
  uint8_t local_c8 [4];
  int local_c4;
  float local_c0;
  int local_bc;
  Vec *local_b8;
  uint8_t local_b4 [4];
  uint8_t local_b0 [4];
  uint8_t local_ac [4];
  uint8_t local_a8 [4];
  uint8_t local_a4 [4];
  uint8_t local_a0 [4];
  uint8_t local_9c [4];
  uint8_t local_98 [4];
  uint8_t local_94 [4];
  int32_t local_90;
  uint8_t local_8c [4];
  uint8_t local_88 [4];
  uint8_t local_84 [4];
  uint8_t local_80 [4];
  uint8_t local_7c [4];
  uint8_t local_78 [4];
  uint8_t local_74 [4];
  uint8_t local_70 [4];
  uint8_t local_6c [4];
  uint8_t local_68 [4];
  uint8_t local_64 [4];
  uint8_t local_60 [4];
  int local_5c;
  uint8_t local_58 [4];
  uint8_t local_54 [12];
  
  aTemp->m_visited[param_2] = '\x01';
  if (param_2 == param_3) {
    if (aTemp->m_cost < (aStar->m_bestPath).m_cost) {
      uVar4 = *(undefined4 *)(aTemp->m_visited + 4);
      *(undefined4 *)(aStar->m_bestPath).m_visited = *(undefined4 *)aTemp->m_visited;
      *(undefined4 *)((aStar->m_bestPath).m_visited + 4) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_visited + 0xc);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 8) = *(undefined4 *)(aTemp->m_visited + 8);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0xc) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_visited + 0x14);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0x10) =
           *(undefined4 *)(aTemp->m_visited + 0x10);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0x14) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_visited + 0x1c);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0x18) =
           *(undefined4 *)(aTemp->m_visited + 0x18);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0x1c) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_visited + 0x24);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0x20) =
           *(undefined4 *)(aTemp->m_visited + 0x20);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0x24) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_visited + 0x2c);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0x28) =
           *(undefined4 *)(aTemp->m_visited + 0x28);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0x2c) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_visited + 0x34);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0x30) =
           *(undefined4 *)(aTemp->m_visited + 0x30);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0x34) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_visited + 0x3c);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0x38) =
           *(undefined4 *)(aTemp->m_visited + 0x38);
      *(undefined4 *)((aStar->m_bestPath).m_visited + 0x3c) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_path + 4);
      *(undefined4 *)(aStar->m_bestPath).m_path = *(undefined4 *)aTemp->m_path;
      *(undefined4 *)((aStar->m_bestPath).m_path + 4) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_path + 0xc);
      *(undefined4 *)((aStar->m_bestPath).m_path + 8) = *(undefined4 *)(aTemp->m_path + 8);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0xc) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_path + 0x14);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0x10) = *(undefined4 *)(aTemp->m_path + 0x10);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0x14) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_path + 0x1c);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0x18) = *(undefined4 *)(aTemp->m_path + 0x18);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0x1c) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_path + 0x24);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0x20) = *(undefined4 *)(aTemp->m_path + 0x20);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0x24) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_path + 0x2c);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0x28) = *(undefined4 *)(aTemp->m_path + 0x28);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0x2c) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_path + 0x34);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0x30) = *(undefined4 *)(aTemp->m_path + 0x30);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0x34) = uVar4;
      uVar4 = *(undefined4 *)(aTemp->m_path + 0x3c);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0x38) = *(undefined4 *)(aTemp->m_path + 0x38);
      *(undefined4 *)((aStar->m_bestPath).m_path + 0x3c) = uVar4;
      (aStar->m_bestPath).m_pathLength = aTemp->m_pathLength;
      (aStar->m_bestPath).m_cost = aTemp->m_cost;
    }
  }
  else {
    local_b8 = &aStar->m_portals[0].m_position;
    local_bc = 0;
    do {
      bVar2 = false;
      uVar7 = (uint)*(byte *)&local_b8[1].x;
      if (uVar7 == param_2) {
LAB_80142440:
        bVar2 = true;
      }
      else if (*(byte *)((int)&local_b8[1].x + 1) == param_2) goto LAB_80142440;
      if (bVar2) {
        if (uVar7 == param_2) {
          uVar7 = (uint)*(byte *)((int)&local_b8[1].x + 1);
        }
        if (aTemp->m_visited[uVar7] == '\0') {
          local_ec = *(uint8_t (*) [4])(aTemp->m_path + 0x18);
          local_f4 = *(uint8_t (*) [4])(aTemp->m_path + 0x10);
          local_e8 = *(uint8_t (*) [4])(aTemp->m_path + 0x1c);
          local_e4 = *(uint8_t (*) [4])(aTemp->m_path + 0x20);
          local_e0 = *(uint8_t (*) [4])(aTemp->m_path + 0x24);
          local_dc = *(uint8_t (*) [4])(aTemp->m_path + 0x28);
          local_d8 = *(uint8_t (*) [4])(aTemp->m_path + 0x2c);
          local_d4 = *(uint8_t (*) [4])(aTemp->m_path + 0x30);
          local_d0 = *(uint8_t (*) [4])(aTemp->m_path + 0x34);
          local_cc = *(uint8_t (*) [4])(aTemp->m_path + 0x38);
          local_c8 = *(uint8_t (*) [4])(aTemp->m_path + 0x3c);
          local_c4 = aTemp->m_pathLength;
          local_144 = *(uint8_t (*) [4])aTemp->m_visited;
          local_140 = *(uint8_t (*) [4])(aTemp->m_visited + 4);
          local_13c = *(uint8_t (*) [4])(aTemp->m_visited + 8);
          local_138 = *(uint8_t (*) [4])(aTemp->m_visited + 0xc);
          local_134 = *(uint8_t (*) [4])(aTemp->m_visited + 0x10);
          local_130 = *(uint8_t (*) [4])(aTemp->m_visited + 0x14);
          local_12c = *(uint8_t (*) [4])(aTemp->m_visited + 0x18);
          local_128 = *(uint8_t (*) [4])(aTemp->m_visited + 0x1c);
          local_124 = *(uint8_t (*) [4])(aTemp->m_visited + 0x20);
          local_120 = *(uint8_t (*) [4])(aTemp->m_visited + 0x24);
          local_11c = *(uint8_t (*) [4])(aTemp->m_visited + 0x28);
          local_118 = *(uint8_t (*) [4])(aTemp->m_visited + 0x2c);
          local_114 = *(uint8_t (*) [4])(aTemp->m_visited + 0x30);
          local_110 = *(uint8_t (*) [4])(aTemp->m_visited + 0x34);
          local_10c = *(uint8_t (*) [4])(aTemp->m_visited + 0x38);
          local_108 = *(uint8_t (*) [4])(aTemp->m_visited + 0x3c);
          local_104 = *(uint8_t (*) [4])aTemp->m_path;
          local_100 = *(uint8_t (*) [4])(aTemp->m_path + 4);
          local_fc = *(uint8_t (*) [4])(aTemp->m_path + 8);
          local_f8 = *(uint8_t (*) [4])(aTemp->m_path + 0xc);
          local_f0 = *(uint8_t (*) [4])(aTemp->m_path + 0x14);
          local_c0 = aTemp->m_cost;
          local_b4 = local_e8;
          local_b0 = local_e4;
          local_ac = local_e0;
          local_a8 = local_dc;
          local_a4 = local_d8;
          local_a0 = local_d4;
          local_9c = local_d0;
          local_98 = local_cc;
          local_94 = local_c8;
          local_90 = local_c4;
          local_58 = local_ec;
          dVar10 = (double)PSVECDistance(local_b8,&aStar->m_portals[uVar7].m_position);
          iVar9 = local_c4;
          local_c4 = local_c4 + 1;
          local_c0 = (float)((double)local_c0 + dVar10);
          local_104[iVar9] = (uint8_t)local_bc;
          local_144[uVar7] = '\x01';
          if (uVar7 == param_3) {
            if (local_c0 < (aStar->m_bestPath).m_cost) {
              *(uint8_t (*) [4])(aStar->m_bestPath).m_visited = local_144;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 4) = local_140;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 8) = local_13c;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0xc) = local_138;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0x10) = local_134;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0x14) = local_130;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0x18) = local_12c;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0x1c) = local_128;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0x20) = local_124;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0x24) = local_120;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0x28) = local_11c;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0x2c) = local_118;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0x30) = local_114;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0x34) = local_110;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0x38) = local_10c;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_visited + 0x3c) = local_108;
              *(uint8_t (*) [4])(aStar->m_bestPath).m_path = local_104;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 4) = local_100;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 8) = local_fc;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0xc) = local_f8;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0x10) = local_f4;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0x14) = local_f0;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0x18) = local_ec;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0x1c) = local_e8;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0x20) = local_e4;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0x24) = local_e0;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0x28) = local_dc;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0x2c) = local_d8;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0x30) = local_d4;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0x34) = local_d0;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0x38) = local_cc;
              *(uint8_t (*) [4])((aStar->m_bestPath).m_path + 0x3c) = local_c8;
              (aStar->m_bestPath).m_pathLength = local_c4;
              (aStar->m_bestPath).m_cost = local_c0;
            }
          }
          else {
            inVecA = &aStar->m_portals[0].m_position;
            iVar9 = 0;
            do {
              uVar6 = (uint)*(byte *)&inVecA[1].x;
              bVar2 = false;
              if (uVar6 == uVar7) {
LAB_8014276c:
                bVar2 = true;
              }
              else if (*(byte *)((int)&inVecA[1].x + 1) == uVar7) goto LAB_8014276c;
              if (bVar2) {
                if (uVar6 == uVar7) {
                  uVar6 = (uint)*(byte *)((int)&inVecA[1].x + 1);
                }
                if (local_144[uVar6] == '\0') {
                  local_54[0] = local_f8[0];
                  local_54[1] = local_f8[1];
                  local_54[2] = local_f8[2];
                  local_54[3] = local_f8[3];
                  local_1cc.m_path[4] = local_100[0];
                  local_1cc.m_path[5] = local_100[1];
                  local_1cc.m_path[6] = local_100[2];
                  local_1cc.m_path[7] = local_100[3];
                  local_8c[0] = local_f4[0];
                  local_8c[1] = local_f4[1];
                  local_8c[2] = local_f4[2];
                  local_8c[3] = local_f4[3];
                  local_1cc.m_path[0xc] = local_f8[0];
                  local_1cc.m_path[0xd] = local_f8[1];
                  local_1cc.m_path[0xe] = local_f8[2];
                  local_1cc.m_path[0xf] = local_f8[3];
                  local_88[0] = local_f0[0];
                  local_88[1] = local_f0[1];
                  local_88[2] = local_f0[2];
                  local_88[3] = local_f0[3];
                  local_1cc.m_path[0x10] = local_f4[0];
                  local_1cc.m_path[0x11] = local_f4[1];
                  local_1cc.m_path[0x12] = local_f4[2];
                  local_1cc.m_path[0x13] = local_f4[3];
                  local_84[0] = local_ec[0];
                  local_84[1] = local_ec[1];
                  local_84[2] = local_ec[2];
                  local_84[3] = local_ec[3];
                  local_1cc.m_path[0x14] = local_f0[0];
                  local_1cc.m_path[0x15] = local_f0[1];
                  local_1cc.m_path[0x16] = local_f0[2];
                  local_1cc.m_path[0x17] = local_f0[3];
                  local_80[0] = local_e8[0];
                  local_80[1] = local_e8[1];
                  local_80[2] = local_e8[2];
                  local_80[3] = local_e8[3];
                  local_1cc.m_path[0x18] = local_ec[0];
                  local_1cc.m_path[0x19] = local_ec[1];
                  local_1cc.m_path[0x1a] = local_ec[2];
                  local_1cc.m_path[0x1b] = local_ec[3];
                  local_7c[0] = local_e4[0];
                  local_7c[1] = local_e4[1];
                  local_7c[2] = local_e4[2];
                  local_7c[3] = local_e4[3];
                  local_1cc.m_path[0x1c] = local_e8[0];
                  local_1cc.m_path[0x1d] = local_e8[1];
                  local_1cc.m_path[0x1e] = local_e8[2];
                  local_1cc.m_path[0x1f] = local_e8[3];
                  local_78[0] = local_e0[0];
                  local_78[1] = local_e0[1];
                  local_78[2] = local_e0[2];
                  local_78[3] = local_e0[3];
                  local_1cc.m_path[0x20] = local_e4[0];
                  local_1cc.m_path[0x21] = local_e4[1];
                  local_1cc.m_path[0x22] = local_e4[2];
                  local_1cc.m_path[0x23] = local_e4[3];
                  local_74[0] = local_dc[0];
                  local_74[1] = local_dc[1];
                  local_74[2] = local_dc[2];
                  local_74[3] = local_dc[3];
                  local_1cc.m_path[0x24] = local_e0[0];
                  local_1cc.m_path[0x25] = local_e0[1];
                  local_1cc.m_path[0x26] = local_e0[2];
                  local_1cc.m_path[0x27] = local_e0[3];
                  local_70[0] = local_d8[0];
                  local_70[1] = local_d8[1];
                  local_70[2] = local_d8[2];
                  local_70[3] = local_d8[3];
                  local_1cc.m_path[0x28] = local_dc[0];
                  local_1cc.m_path[0x29] = local_dc[1];
                  local_1cc.m_path[0x2a] = local_dc[2];
                  local_1cc.m_path[0x2b] = local_dc[3];
                  local_6c[0] = local_d4[0];
                  local_6c[1] = local_d4[1];
                  local_6c[2] = local_d4[2];
                  local_6c[3] = local_d4[3];
                  local_1cc.m_path[0x2c] = local_d8[0];
                  local_1cc.m_path[0x2d] = local_d8[1];
                  local_1cc.m_path[0x2e] = local_d8[2];
                  local_1cc.m_path[0x2f] = local_d8[3];
                  local_68[0] = local_d0[0];
                  local_68[1] = local_d0[1];
                  local_68[2] = local_d0[2];
                  local_68[3] = local_d0[3];
                  local_1cc.m_path[0x30] = local_d4[0];
                  local_1cc.m_path[0x31] = local_d4[1];
                  local_1cc.m_path[0x32] = local_d4[2];
                  local_1cc.m_path[0x33] = local_d4[3];
                  local_64[0] = local_cc[0];
                  local_64[1] = local_cc[1];
                  local_64[2] = local_cc[2];
                  local_64[3] = local_cc[3];
                  local_1cc.m_path[0x34] = local_d0[0];
                  local_1cc.m_path[0x35] = local_d0[1];
                  local_1cc.m_path[0x36] = local_d0[2];
                  local_1cc.m_path[0x37] = local_d0[3];
                  local_60[0] = local_c8[0];
                  local_60[1] = local_c8[1];
                  local_60[2] = local_c8[2];
                  local_60[3] = local_c8[3];
                  local_1cc.m_path[0x38] = local_cc[0];
                  local_1cc.m_path[0x39] = local_cc[1];
                  local_1cc.m_path[0x3a] = local_cc[2];
                  local_1cc.m_path[0x3b] = local_cc[3];
                  local_1cc.m_path[0x3c] = local_c8[0];
                  local_1cc.m_path[0x3d] = local_c8[1];
                  local_1cc.m_path[0x3e] = local_c8[2];
                  local_1cc.m_path[0x3f] = local_c8[3];
                  local_5c = local_c4;
                  local_1cc.m_visited[0] = local_144[0];
                  local_1cc.m_visited[1] = local_144[1];
                  local_1cc.m_visited[2] = local_144[2];
                  local_1cc.m_visited[3] = local_144[3];
                  local_1cc.m_visited[4] = local_140[0];
                  local_1cc.m_visited[5] = local_140[1];
                  local_1cc.m_visited[6] = local_140[2];
                  local_1cc.m_visited[7] = local_140[3];
                  local_1cc.m_visited[8] = local_13c[0];
                  local_1cc.m_visited[9] = local_13c[1];
                  local_1cc.m_visited[10] = local_13c[2];
                  local_1cc.m_visited[0xb] = local_13c[3];
                  local_1cc.m_visited[0xc] = local_138[0];
                  local_1cc.m_visited[0xd] = local_138[1];
                  local_1cc.m_visited[0xe] = local_138[2];
                  local_1cc.m_visited[0xf] = local_138[3];
                  local_1cc.m_visited[0x10] = local_134[0];
                  local_1cc.m_visited[0x11] = local_134[1];
                  local_1cc.m_visited[0x12] = local_134[2];
                  local_1cc.m_visited[0x13] = local_134[3];
                  local_1cc.m_visited[0x14] = local_130[0];
                  local_1cc.m_visited[0x15] = local_130[1];
                  local_1cc.m_visited[0x16] = local_130[2];
                  local_1cc.m_visited[0x17] = local_130[3];
                  local_1cc.m_visited[0x18] = local_12c[0];
                  local_1cc.m_visited[0x19] = local_12c[1];
                  local_1cc.m_visited[0x1a] = local_12c[2];
                  local_1cc.m_visited[0x1b] = local_12c[3];
                  local_1cc.m_visited[0x1c] = local_128[0];
                  local_1cc.m_visited[0x1d] = local_128[1];
                  local_1cc.m_visited[0x1e] = local_128[2];
                  local_1cc.m_visited[0x1f] = local_128[3];
                  local_1cc.m_visited[0x20] = local_124[0];
                  local_1cc.m_visited[0x21] = local_124[1];
                  local_1cc.m_visited[0x22] = local_124[2];
                  local_1cc.m_visited[0x23] = local_124[3];
                  local_1cc.m_visited[0x24] = local_120[0];
                  local_1cc.m_visited[0x25] = local_120[1];
                  local_1cc.m_visited[0x26] = local_120[2];
                  local_1cc.m_visited[0x27] = local_120[3];
                  local_1cc.m_visited[0x28] = local_11c[0];
                  local_1cc.m_visited[0x29] = local_11c[1];
                  local_1cc.m_visited[0x2a] = local_11c[2];
                  local_1cc.m_visited[0x2b] = local_11c[3];
                  local_1cc.m_visited[0x2c] = local_118[0];
                  local_1cc.m_visited[0x2d] = local_118[1];
                  local_1cc.m_visited[0x2e] = local_118[2];
                  local_1cc.m_visited[0x2f] = local_118[3];
                  local_1cc.m_visited[0x30] = local_114[0];
                  local_1cc.m_visited[0x31] = local_114[1];
                  local_1cc.m_visited[0x32] = local_114[2];
                  local_1cc.m_visited[0x33] = local_114[3];
                  local_1cc.m_visited[0x34] = local_110[0];
                  local_1cc.m_visited[0x35] = local_110[1];
                  local_1cc.m_visited[0x36] = local_110[2];
                  local_1cc.m_visited[0x37] = local_110[3];
                  local_1cc.m_visited[0x38] = local_10c[0];
                  local_1cc.m_visited[0x39] = local_10c[1];
                  local_1cc.m_visited[0x3a] = local_10c[2];
                  local_1cc.m_visited[0x3b] = local_10c[3];
                  local_1cc.m_visited[0x3c] = local_108[0];
                  local_1cc.m_visited[0x3d] = local_108[1];
                  local_1cc.m_visited[0x3e] = local_108[2];
                  local_1cc.m_visited[0x3f] = local_108[3];
                  local_1cc.m_path[0] = local_104[0];
                  local_1cc.m_path[1] = local_104[1];
                  local_1cc.m_path[2] = local_104[2];
                  local_1cc.m_path[3] = local_104[3];
                  local_1cc.m_path[8] = local_fc[0];
                  local_1cc.m_path[9] = local_fc[1];
                  local_1cc.m_path[10] = local_fc[2];
                  local_1cc.m_path[0xb] = local_fc[3];
                  local_1cc.m_pathLength = local_c4;
                  local_1cc.m_cost = local_c0;
                  dVar10 = (double)PSVECDistance(inVecA,&aStar->m_portals[uVar6].m_position);
                  iVar3 = local_1cc.m_pathLength;
                  local_1cc.m_pathLength = local_1cc.m_pathLength + 1;
                  local_1cc.m_cost = (float)((double)local_1cc.m_cost + dVar10);
                  local_1cc.m_path[iVar3] = (uint8_t)iVar9;
                  local_1cc.m_visited[uVar6] = '\x01';
                  if (uVar6 == param_3) {
                    if (local_1cc.m_cost < (aStar->m_bestPath).m_cost) {
                      __as__Q26CAStar6CATempFRCQ26CAStar6CATemp(&aStar->m_bestPath,&local_1cc);
                    }
                  }
                  else {
                    aPos = aStar->m_portals;
                    iVar8 = 0;
                    do {
                      iVar5 = IsExist__Q26CAStar5CAPosFi(aPos,uVar6);
                      if (iVar5 != 0) {
                        iVar5 = GetOthers__Q26CAStar5CAPosFi(aPos,uVar6);
                        if (local_1cc.m_visited[iVar5] == '\0') {
                          __ct__Q26CAStar6CATempFRCQ26CAStar6CATemp(&CStack_254,&local_1cc);
                          dVar10 = (double)CalcLength__Q26CAStar5CAPosFRQ26CAStar5CAPos
                                                     (aPos,aStar->m_portals + iVar5);
                          CStack_254.m_cost = (float)((double)CStack_254.m_cost + dVar10);
                          puVar1 = CStack_254.m_path + CStack_254.m_pathLength;
                          CStack_254.m_pathLength = CStack_254.m_pathLength + 1;
                          *puVar1 = (uint8_t)iVar8;
                          check__6CAStarFiiRQ26CAStar6CATemp(aStar,iVar5,param_3,&CStack_254);
                        }
                      }
                      iVar8 = iVar8 + 1;
                      aPos = aPos + 1;
                    } while (iVar8 < 0x40);
                  }
                }
              }
              iVar9 = iVar9 + 1;
              inVecA = (Vec *)&inVecA[1].y;
            } while (iVar9 < 0x40);
          }
        }
      }
      local_bc = local_bc + 1;
      local_b8 = (Vec *)&local_b8[1].y;
    } while (local_bc < 0x40);
  }
  return;
}

