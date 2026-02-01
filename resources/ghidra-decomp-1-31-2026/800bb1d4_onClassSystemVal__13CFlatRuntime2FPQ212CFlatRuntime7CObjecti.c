// Function: onClassSystemVal__13CFlatRuntime2FPQ212CFlatRuntime7CObjecti
// Entry: 800bb1d4
// Size: 1324 bytes

uint32_t *
onClassSystemVal__13CFlatRuntime2FPQ212CFlatRuntime7CObjecti
          (CFlatRuntime2 *flatRuntime2,CObject *object,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  void *pvVar4;
  
  pvVar4 = object->m_engineObject;
  uVar2 = (**(code **)(*(int *)((int)pvVar4 + 0x48) + 0xc))(pvVar4);
  if (((uVar2 & 5) == 5) || (param_3 != -0x1b)) {
    if (param_3 < -0x3f) {
      iVar3 = *(int *)((int)pvVar4 + 0x58);
      uVar2 = 0;
      if (param_3 < -0xd7f) {
        if (param_3 < -0xd97) {
          if (param_3 < -0xdb7) {
            if (param_3 == -0xdba) {
              uVar2 = *(uint *)((int)pvVar4 + 0x6ec);
            }
          }
          else if (param_3 < -0xda7) {
            uVar2 = (uint)*(ushort *)(iVar3 + (param_3 + 0xdb7) * 2 + 0xf0);
          }
          else {
            uVar2 = (uint)*(ushort *)(iVar3 + (param_3 + 0xda7) * 2 + 0xd0);
          }
        }
        else if (param_3 < -0xd83) {
          if (param_3 == -0xd92) {
            if (*(int *)((int)pvVar4 + 0xf8) == 0) {
              uVar2 = 0xffffffff;
            }
            else {
              iVar3 = *(int *)(*(int *)((int)pvVar4 + 0xf8) + 0x178);
              if (iVar3 == 0) {
                uVar2 = 0xffffffff;
              }
              else {
                uVar2 = *(uint *)(iVar3 + 0x14);
              }
            }
          }
          else if (-0xd93 < param_3) {
            uVar2 = (uint)*(ushort *)(iVar3 + (param_3 + 0xd91) * 2 + 0xb4);
          }
        }
        else if (param_3 < -0xd7f) {
          uVar2 = (uint)*(ushort *)(iVar3 + (param_3 + 0xd83) * 2 + 0xac);
        }
      }
      else if (param_3 < -399) {
        if ((param_3 < -999) && (-0xbe8 < param_3)) {
          uVar2 = param_3 + 0xbe7;
          iVar1 = (int)uVar2 >> 0x1f;
          uVar2 = -((uint)*(byte *)(iVar3 + ((int)uVar2 >> 3) +
                                            (uint)((int)uVar2 < 0 && (uVar2 & 7) != 0) + 0x8a4) &
                   1 << (iVar1 * 8 | uVar2 * 0x20000000 + iVar1 >> 0x1d) - iVar1) >> 0x1f;
        }
        else if ((param_3 < -499) && (-0x2f4 < param_3)) {
          uVar2 = (uint)*(short *)(iVar3 + (param_3 + 0x2f3) * 2 + 0x9a4);
        }
        else if (param_3 == -0x1aa) {
          uVar2 = (uint)*(ushort *)(iVar3 + 0xb4);
        }
        else if (param_3 < -0x1aa) {
          if (param_3 == -0x1c8) {
            if (*(int *)((int)pvVar4 + 0x6f0) == 0) {
              uVar2 = 0;
            }
            else {
              uVar2 = (uint)*(short *)(*(int *)((int)pvVar4 + 0x6f0) + 0x30);
            }
          }
          else if (param_3 < -0x1c8) {
            if (-0x1ca < param_3) {
              uVar2 = (uint)*(ushort *)(iVar3 + 0xbc8);
            }
          }
          else if (param_3 == -0x1b6) {
            uVar2 = (uint)*(ushort *)(iVar3 + 0x3de);
          }
        }
        else if (param_3 == -0x19c) {
          uVar2 = *(uint *)(iVar3 + 0x200);
        }
        else if (param_3 < -0x19c) {
          if (param_3 < -0x19d) {
            if (param_3 < -0x1a5) {
              uVar2 = (uint)*(short *)(iVar3 + (param_3 + 0x1a9) * 2 + 0xac);
            }
          }
          else {
            uVar2 = (uint)*(ushort *)(iVar3 + 0x3c8);
          }
        }
        else if ((param_3 < -0x191) && (-0x19a < param_3)) {
          uVar2 = (uint)*(ushort *)(iVar3 + (param_3 + 0x199) * 2 + 0x3b8);
        }
      }
      else if ((param_3 < -0x95) && (-0x176 < param_3)) {
        uVar2 = (uint)*(ushort *)(*(int *)(iVar3 + 0x24) + (param_3 + 0x175) * 2);
      }
      else if (param_3 == -0x45) {
        uVar2 = (uint)*(ushort *)(iVar3 + 0x22);
      }
      else if (param_3 < -0x45) {
        if (param_3 == -0x82) {
          uVar2 = (uint)*(ushort *)(iVar3 + 0x14);
        }
        else if (param_3 < -0x82) {
          if (param_3 == -0x84) {
            uVar2 = (uint)*(ushort *)(iVar3 + 0x18);
          }
          else if (param_3 < -0x84) {
            if (-0x95 < param_3) {
              uVar2 = (uint)*(ushort *)(iVar3 + (param_3 + 0x94) * 2 + 0x8c);
            }
          }
          else {
            uVar2 = (uint)*(ushort *)(iVar3 + 0x16);
          }
        }
        else if ((param_3 < -0x52) && (-0x7a < param_3)) {
          uVar2 = (uint)*(ushort *)(iVar3 + (-0x53 - param_3) * 2 + 0x3e);
        }
      }
      else if (param_3 == -0x41) {
        uVar2 = (uint)*(ushort *)(iVar3 + 0x1c);
      }
      else if (param_3 < -0x41) {
        if (param_3 == -0x43) {
          uVar2 = (uint)*(ushort *)(iVar3 + 0x1e);
        }
        else if (param_3 < -0x43) {
          uVar2 = (uint)*(ushort *)(iVar3 + 0x20);
        }
      }
      else if (param_3 < -0x3f) {
        uVar2 = (uint)*(ushort *)(iVar3 + 0x1a);
      }
      (flatRuntime2->flatRuntimeBase).m_lastResult = uVar2;
    }
    else {
      switch(param_3) {
      case -0x1b:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x60);
        break;
      case -0x19:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x520);
        break;
      case -0x18:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x1bc);
        break;
      case -0x17:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x170);
        break;
      case -0x16:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x16c);
        break;
      case -0x15:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x168);
        break;
      case -0x14:
      case -0x13:
      case -0x12:
      case -0x11:
        (flatRuntime2->flatRuntimeBase).m_lastResult =
             (int)*(short *)((int)pvVar4 + (param_3 + 0x14) * 2 + 0x510);
        break;
      case -0x10:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x504);
        break;
      case -0xf:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x500);
        break;
      case -0xd:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x188);
        break;
      case -0xc:
        (flatRuntime2->flatRuntimeBase).m_lastResult =
             (int)((uint)*(byte *)((int)pvVar4 + 0x50) << 0x19 |
                  (uint)(*(byte *)((int)pvVar4 + 0x50) >> 7)) >> 0x1f;
        break;
      case -0xb:
        (flatRuntime2->flatRuntimeBase).m_lastResult = (int)*(char *)((int)pvVar4 + 0x53);
        break;
      case -10:
        (flatRuntime2->flatRuntimeBase).m_lastResult =
             (int)((uint)*(byte *)((int)pvVar4 + 0x50) << 0x1c |
                  (uint)(*(byte *)((int)pvVar4 + 0x50) >> 4)) >> 0x1f;
        break;
      case -9:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x94);
        break;
      case -8:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint *)((int)pvVar4 + 0x4cc) >> 0x17 & 0xf;
        break;
      case -7:
        (flatRuntime2->flatRuntimeBase).m_lastResult =
             (int)((uint)*(byte *)((int)pvVar4 + 0x50) << 0x18) >> 0x1f;
        break;
      case -6:
        (flatRuntime2->flatRuntimeBase).m_lastResult = (int)*(short *)((int)pvVar4 + 0x30);
        break;
      case -5:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x184);
        break;
      case -4:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x1b4);
        break;
      case -3:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x164);
        break;
      case -2:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x160);
        break;
      case -1:
        (flatRuntime2->flatRuntimeBase).m_lastResult = *(uint32_t *)((int)pvVar4 + 0x15c);
      }
    }
  }
  else {
    if (1 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801da778);
    }
    (flatRuntime2->flatRuntimeBase).m_lastResult = 0;
  }
  return &(flatRuntime2->flatRuntimeBase).m_lastResult;
}

