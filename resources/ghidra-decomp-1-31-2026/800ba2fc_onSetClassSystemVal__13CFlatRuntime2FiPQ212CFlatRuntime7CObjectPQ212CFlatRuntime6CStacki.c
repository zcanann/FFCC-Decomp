// Function: onSetClassSystemVal__13CFlatRuntime2FiPQ212CFlatRuntime7CObjectPQ212CFlatRuntime6CStacki
// Entry: 800ba2fc
// Size: 3800 bytes

void onSetClassSystemVal__13CFlatRuntime2FiPQ212CFlatRuntime7CObjectPQ212CFlatRuntime6CStacki
               (int param_1,int param_2,int param_3,CStack *cstack,int param_5)

{
  int iVar1;
  byte bVar2;
  uint32_t uVar3;
  uint uVar4;
  int iVar5;
  undefined8 local_20;
  
  uVar4 = (**(code **)(*(int *)(param_3 + 0x48) + 0xc))(param_3);
  if (((uVar4 & 5) == 5) || (param_2 != -0x1b)) {
    if (param_2 < -0x3f) {
      iVar5 = *(int *)(param_3 + 0x58);
      if (param_2 < -0xd7f) {
        if (param_2 == -0xdb8) {
          cstack[-1].m_arg = (uint)*(ushort *)(param_3 + 0x6d4);
          if (param_5 == 0) {
            *(short *)(param_3 + 0x6d4) = (short)cstack->m_arg;
          }
          else if (param_5 < 0) {
            if (-2 < param_5) {
              *(short *)(param_3 + 0x6d4) = *(short *)(param_3 + 0x6d4) - (short)cstack->m_arg;
            }
          }
          else if (param_5 < 2) {
            *(short *)(param_3 + 0x6d4) = *(short *)(param_3 + 0x6d4) + (short)cstack->m_arg;
          }
        }
        else if (param_2 < -0xdb8) {
          if (param_2 == -0xdba) {
            cstack[-1].m_arg = *(uint32_t *)(param_3 + 0x6ec);
            if (param_5 == 0) {
              *(uint32_t *)(param_3 + 0x6ec) = cstack->m_arg;
            }
            else if (param_5 < 0) {
              if (-2 < param_5) {
                *(uint32_t *)(param_3 + 0x6ec) = *(int *)(param_3 + 0x6ec) - cstack->m_arg;
              }
            }
            else if (param_5 < 2) {
              *(uint32_t *)(param_3 + 0x6ec) = *(int *)(param_3 + 0x6ec) + cstack->m_arg;
            }
          }
          else if (-0xdbb < param_2) {
            cstack[-1].m_arg = (uint)*(ushort *)(param_3 + 0x6d6);
            if (param_5 == 0) {
              *(short *)(param_3 + 0x6d6) = (short)cstack->m_arg;
            }
            else if (param_5 < 0) {
              if (-2 < param_5) {
                *(short *)(param_3 + 0x6d6) = *(short *)(param_3 + 0x6d6) - (short)cstack->m_arg;
              }
            }
            else if (param_5 < 2) {
              *(short *)(param_3 + 0x6d6) = *(short *)(param_3 + 0x6d6) + (short)cstack->m_arg;
            }
          }
        }
        else if (param_2 < -0xd97) {
          if (param_2 < -0xda7) {
            iVar5 = iVar5 + (param_2 + 0xdb7) * 2;
            cstack[-1].m_arg = (uint)*(ushort *)(iVar5 + 0xf0);
            if (param_5 == 0) {
              *(short *)(iVar5 + 0xf0) = (short)cstack->m_arg;
            }
            else if (param_5 < 0) {
              if (-2 < param_5) {
                *(short *)(iVar5 + 0xf0) = *(short *)(iVar5 + 0xf0) - (short)cstack->m_arg;
              }
            }
            else if (param_5 < 2) {
              *(short *)(iVar5 + 0xf0) = *(short *)(iVar5 + 0xf0) + (short)cstack->m_arg;
            }
          }
          else {
            iVar5 = iVar5 + (param_2 + 0xda7) * 2;
            cstack[-1].m_arg = (uint)*(ushort *)(iVar5 + 0xd0);
            if (param_5 == 0) {
              *(short *)(iVar5 + 0xd0) = (short)cstack->m_arg;
            }
            else if (param_5 < 0) {
              if (-2 < param_5) {
                *(short *)(iVar5 + 0xd0) = *(short *)(iVar5 + 0xd0) - (short)cstack->m_arg;
              }
            }
            else if (param_5 < 2) {
              *(short *)(iVar5 + 0xd0) = *(short *)(iVar5 + 0xd0) + (short)cstack->m_arg;
            }
          }
        }
      }
      else if (param_2 < -399) {
        if ((param_2 < -999) && (-0xbe8 < param_2)) {
          uVar4 = param_2 + 0xbe7;
          iVar1 = (int)uVar4 >> 0x1f;
          iVar5 = iVar5 + ((int)uVar4 >> 3) + (uint)((int)uVar4 < 0 && (uVar4 & 7) != 0);
          uVar4 = 1 << (iVar1 * 8 | uVar4 * 0x20000000 + iVar1 >> 0x1d) - iVar1;
          uVar3 = -((int)-(*(byte *)(iVar5 + 0x8a4) & uVar4) >> 0x1f);
          cstack[-1].m_arg = uVar3;
          if (param_5 == 0) {
            uVar3 = cstack->m_arg;
          }
          else if (param_5 < 0) {
            if (-2 < param_5) {
              uVar3 = uVar3 - cstack->m_arg;
            }
          }
          else if (param_5 < 2) {
            uVar3 = uVar3 + cstack->m_arg;
          }
          bVar2 = (byte)uVar4;
          if (uVar3 == 0) {
            *(byte *)(iVar5 + 0x8a4) = *(byte *)(iVar5 + 0x8a4) & ~bVar2;
          }
          else {
            *(byte *)(iVar5 + 0x8a4) = *(byte *)(iVar5 + 0x8a4) | bVar2;
          }
        }
        else if ((param_2 < -499) && (-0x2f4 < param_2)) {
          iVar5 = iVar5 + (param_2 + 0x2f3) * 2;
          cstack[-1].m_arg = (int)*(short *)(iVar5 + 0x9a4);
          if (param_5 == 0) {
            *(short *)(iVar5 + 0x9a4) = (short)cstack->m_arg;
          }
          else if (param_5 < 0) {
            if (-2 < param_5) {
              *(short *)(iVar5 + 0x9a4) = *(short *)(iVar5 + 0x9a4) - (short)cstack->m_arg;
            }
          }
          else if (param_5 < 2) {
            *(short *)(iVar5 + 0x9a4) = *(short *)(iVar5 + 0x9a4) + (short)cstack->m_arg;
          }
        }
        else if (param_2 == -0x19d) {
          cstack[-1].m_arg = (uint)*(ushort *)(iVar5 + 0x3c8);
          if (param_5 == 0) {
            *(short *)(iVar5 + 0x3c8) = (short)cstack->m_arg;
          }
          else if (param_5 < 0) {
            if (-2 < param_5) {
              *(short *)(iVar5 + 0x3c8) = *(short *)(iVar5 + 0x3c8) - (short)cstack->m_arg;
            }
          }
          else if (param_5 < 2) {
            *(short *)(iVar5 + 0x3c8) = *(short *)(iVar5 + 0x3c8) + (short)cstack->m_arg;
          }
        }
        else if (param_2 < -0x19d) {
          if (param_2 < -0x1a9) {
            if (param_2 == -0x1b6) {
              cstack[-1].m_arg = (uint)*(ushort *)(iVar5 + 0x3de);
              if (param_5 == 0) {
                *(short *)(iVar5 + 0x3de) = (short)cstack->m_arg;
              }
              else if (param_5 < 0) {
                if (-2 < param_5) {
                  *(short *)(iVar5 + 0x3de) = *(short *)(iVar5 + 0x3de) - (short)cstack->m_arg;
                }
              }
              else if (param_5 < 2) {
                *(short *)(iVar5 + 0x3de) = *(short *)(iVar5 + 0x3de) + (short)cstack->m_arg;
              }
            }
          }
          else if (param_2 < -0x1a5) {
            iVar5 = iVar5 + (param_2 + 0x1a9) * 2;
            cstack[-1].m_arg = (int)*(short *)(iVar5 + 0xac);
            if (param_5 == 0) {
              *(short *)(iVar5 + 0xac) = (short)cstack->m_arg;
            }
            else if (param_5 < 0) {
              if (-2 < param_5) {
                *(short *)(iVar5 + 0xac) = *(short *)(iVar5 + 0xac) - (short)cstack->m_arg;
              }
            }
            else if (param_5 < 2) {
              *(short *)(iVar5 + 0xac) = *(short *)(iVar5 + 0xac) + (short)cstack->m_arg;
            }
          }
        }
        else if (param_2 < -0x199) {
          if (param_2 < -0x19b) {
            cstack[-1].m_arg = *(uint32_t *)(iVar5 + 0x200);
            if (param_5 == 0) {
              *(uint32_t *)(iVar5 + 0x200) = cstack->m_arg;
            }
            else if (param_5 < 0) {
              if (-2 < param_5) {
                *(uint32_t *)(iVar5 + 0x200) = *(int *)(iVar5 + 0x200) - cstack->m_arg;
              }
            }
            else if (param_5 < 2) {
              *(uint32_t *)(iVar5 + 0x200) = *(int *)(iVar5 + 0x200) + cstack->m_arg;
            }
          }
        }
        else if (param_2 < -0x191) {
          iVar5 = iVar5 + (param_2 + 0x199) * 2;
          cstack[-1].m_arg = (uint)*(ushort *)(iVar5 + 0x3b8);
          if (param_5 == 0) {
            *(short *)(iVar5 + 0x3b8) = (short)cstack->m_arg;
          }
          else if (param_5 < 0) {
            if (-2 < param_5) {
              *(short *)(iVar5 + 0x3b8) = *(short *)(iVar5 + 0x3b8) - (short)cstack->m_arg;
            }
          }
          else if (param_5 < 2) {
            *(short *)(iVar5 + 0x3b8) = *(short *)(iVar5 + 0x3b8) + (short)cstack->m_arg;
          }
        }
      }
      else if ((param_2 < -0x95) && (-0x176 < param_2)) {
        iVar1 = (param_2 + 0x175) * 2;
        cstack[-1].m_arg = (uint)*(ushort *)(*(int *)(iVar5 + 0x24) + iVar1);
        if (param_5 == 0) {
          *(short *)(*(int *)(iVar5 + 0x24) + iVar1) = (short)cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(short *)(*(int *)(iVar5 + 0x24) + iVar1) =
                 *(short *)(*(int *)(iVar5 + 0x24) + iVar1) - (short)cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(short *)(*(int *)(iVar5 + 0x24) + iVar1) =
               *(short *)(*(int *)(iVar5 + 0x24) + iVar1) + (short)cstack->m_arg;
        }
      }
      else if (param_2 < -0x52) {
        if (param_2 < -0x84) {
          if (-0x95 < param_2) {
            iVar5 = iVar5 + (param_2 + 0x94) * 2;
            cstack[-1].m_arg = (uint)*(ushort *)(iVar5 + 0x8c);
            if (param_5 == 0) {
              *(short *)(iVar5 + 0x8c) = (short)cstack->m_arg;
            }
            else if (param_5 < 0) {
              if (-2 < param_5) {
                *(short *)(iVar5 + 0x8c) = *(short *)(iVar5 + 0x8c) - (short)cstack->m_arg;
              }
            }
            else if (param_5 < 2) {
              *(short *)(iVar5 + 0x8c) = *(short *)(iVar5 + 0x8c) + (short)cstack->m_arg;
            }
          }
        }
        else if (-0x7a < param_2) {
          iVar5 = iVar5 + (-0x53 - param_2) * 2;
          cstack[-1].m_arg = (uint)*(ushort *)(iVar5 + 0x3e);
          if (param_5 == 0) {
            *(short *)(iVar5 + 0x3e) = (short)cstack->m_arg;
          }
          else if (param_5 < 0) {
            if (-2 < param_5) {
              *(short *)(iVar5 + 0x3e) = *(short *)(iVar5 + 0x3e) - (short)cstack->m_arg;
            }
          }
          else if (param_5 < 2) {
            *(short *)(iVar5 + 0x3e) = *(short *)(iVar5 + 0x3e) + (short)cstack->m_arg;
          }
        }
      }
      else if (param_2 == -0x40) {
        cstack[-1].m_arg = (uint)*(ushort *)(iVar5 + 0x1a);
        if (param_5 == 0) {
          *(short *)(iVar5 + 0x1a) = (short)cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(short *)(iVar5 + 0x1a) = *(short *)(iVar5 + 0x1a) - (short)cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(short *)(iVar5 + 0x1a) = *(short *)(iVar5 + 0x1a) + (short)cstack->m_arg;
        }
      }
      else if ((param_2 < -0x40) && (-0x42 < param_2)) {
        cstack[-1].m_arg = (uint)*(ushort *)(iVar5 + 0x1c);
        if (param_5 == 0) {
          *(short *)(iVar5 + 0x1c) = (short)cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(short *)(iVar5 + 0x1c) = *(short *)(iVar5 + 0x1c) - (short)cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(short *)(iVar5 + 0x1c) = *(short *)(iVar5 + 0x1c) + (short)cstack->m_arg;
        }
      }
      *(undefined4 *)(param_1 + 0x96c) = 0;
    }
    else {
      switch(param_2) {
      case -0x1b:
        cstack[-1].m_arg = *(uint32_t *)(param_3 + 0x60);
        if (param_5 == 0) {
          *(uint32_t *)(param_3 + 0x60) = cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(uint32_t *)(param_3 + 0x60) = *(int *)(param_3 + 0x60) - cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(uint32_t *)(param_3 + 0x60) = *(int *)(param_3 + 0x60) + cstack->m_arg;
        }
        break;
      case -0x1a:
        uVar4 = 0;
        cstack[-1].m_arg = (uint32_t)FLOAT_80330bc8;
        if (param_5 == 0) {
          uVar4 = (uint)(float)cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            uVar4 = (uint)((float)(4503601774854144.0 - DOUBLE_80330bd0) - (float)cstack->m_arg);
          }
        }
        else if (param_5 < 2) {
          uVar4 = (uint)((float)(4503601774854144.0 - DOUBLE_80330bd0) + (float)cstack->m_arg);
        }
        local_20 = (double)CONCAT44(0x43300000,uVar4 ^ 0x80000000);
        *(char *)(param_3 + 0x56) =
             (char)(int)(FLOAT_80330bcc * (float)(local_20 - DOUBLE_80330bd0));
        break;
      case -0x18:
        cstack[-1].m_arg = *(uint32_t *)(param_3 + 0x1bc);
        if (param_5 == 0) {
          *(uint32_t *)(param_3 + 0x1bc) = cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(float *)(param_3 + 0x1bc) = *(float *)(param_3 + 0x1bc) - (float)cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(float *)(param_3 + 0x1bc) = *(float *)(param_3 + 0x1bc) + (float)cstack->m_arg;
        }
        break;
      case -0x17:
        cstack[-1].m_arg = *(uint32_t *)(param_3 + 0x170);
        if (param_5 == 0) {
          *(uint32_t *)(param_3 + 0x170) = cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(float *)(param_3 + 0x170) = *(float *)(param_3 + 0x170) - (float)cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(float *)(param_3 + 0x170) = *(float *)(param_3 + 0x170) + (float)cstack->m_arg;
        }
        break;
      case -0x16:
        cstack[-1].m_arg = *(uint32_t *)(param_3 + 0x16c);
        if (param_5 == 0) {
          *(uint32_t *)(param_3 + 0x16c) = cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(float *)(param_3 + 0x16c) = *(float *)(param_3 + 0x16c) - (float)cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(float *)(param_3 + 0x16c) = *(float *)(param_3 + 0x16c) + (float)cstack->m_arg;
        }
        break;
      case -0x15:
        cstack[-1].m_arg = *(uint32_t *)(param_3 + 0x168);
        if (param_5 == 0) {
          *(uint32_t *)(param_3 + 0x168) = cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(float *)(param_3 + 0x168) = *(float *)(param_3 + 0x168) - (float)cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(float *)(param_3 + 0x168) = *(float *)(param_3 + 0x168) + (float)cstack->m_arg;
        }
        break;
      case -0x14:
      case -0x13:
      case -0x12:
      case -0x11:
        iVar5 = param_3 + (param_2 + 0x14) * 2;
        cstack[-1].m_arg = (int)*(short *)(iVar5 + 0x510);
        if (param_5 == 0) {
          *(short *)(iVar5 + 0x510) = (short)cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(short *)(iVar5 + 0x510) = *(short *)(iVar5 + 0x510) - (short)cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(short *)(iVar5 + 0x510) = *(short *)(iVar5 + 0x510) + (short)cstack->m_arg;
        }
        break;
      case -0x10:
        cstack[-1].m_arg = *(uint32_t *)(param_3 + 0x504);
        if (param_5 == 0) {
          *(uint32_t *)(param_3 + 0x504) = cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(uint32_t *)(param_3 + 0x504) = *(int *)(param_3 + 0x504) - cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(uint32_t *)(param_3 + 0x504) = *(int *)(param_3 + 0x504) + cstack->m_arg;
        }
        break;
      case -0xf:
        cstack[-1].m_arg = *(uint32_t *)(param_3 + 0x500);
        if (param_5 == 0) {
          *(uint32_t *)(param_3 + 0x500) = cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(uint32_t *)(param_3 + 0x500) = *(int *)(param_3 + 0x500) - cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(uint32_t *)(param_3 + 0x500) = *(int *)(param_3 + 0x500) + cstack->m_arg;
        }
        break;
      case -0xd:
        cstack[-1].m_arg = *(uint32_t *)(param_3 + 0x188);
        if (param_5 == 0) {
          *(uint32_t *)(param_3 + 0x188) = cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(float *)(param_3 + 0x188) = *(float *)(param_3 + 0x188) - (float)cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(float *)(param_3 + 0x188) = *(float *)(param_3 + 0x188) + (float)cstack->m_arg;
        }
        break;
      case -0xb:
        cstack[-1].m_arg = (int)*(char *)(param_3 + 0x53);
        if (param_5 == 0) {
          *(char *)(param_3 + 0x53) = (char)cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(char *)(param_3 + 0x53) = *(char *)(param_3 + 0x53) - (char)cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(char *)(param_3 + 0x53) = *(char *)(param_3 + 0x53) + (char)cstack->m_arg;
        }
        break;
      case -10:
        cstack[-1].m_arg =
             (int)((uint)*(byte *)(param_3 + 0x50) << 0x1c | (uint)(*(byte *)(param_3 + 0x50) >> 4))
             >> 0x1f;
        if (param_5 == 0) {
          *(byte *)(param_3 + 0x50) =
               (byte)((int)(char)cstack->m_arg << 3) & 8 | *(byte *)(param_3 + 0x50) & 0xf7;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(byte *)(param_3 + 0x50) =
                 (byte)((int)(char)((char)((int)((uint)*(byte *)(param_3 + 0x50) << 0x1c) >> 0x1f) -
                                   (char)cstack->m_arg) << 3) & 8 | *(byte *)(param_3 + 0x50) & 0xf7
            ;
          }
        }
        else if (param_5 < 2) {
          *(byte *)(param_3 + 0x50) =
               (byte)((int)(char)((char)((int)((uint)*(byte *)(param_3 + 0x50) << 0x1c) >> 0x1f) +
                                 (char)cstack->m_arg) << 3) & 8 | *(byte *)(param_3 + 0x50) & 0xf7;
        }
        break;
      case -9:
        cstack[-1].m_arg = *(uint32_t *)(param_3 + 0x94);
        if (param_5 == 0) {
          *(uint32_t *)(param_3 + 0x94) = cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(uint32_t *)(param_3 + 0x94) = *(int *)(param_3 + 0x94) - cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(uint32_t *)(param_3 + 0x94) = *(int *)(param_3 + 0x94) + cstack->m_arg;
        }
        break;
      case -5:
        cstack[-1].m_arg = *(uint32_t *)(param_3 + 0x184);
        if (param_5 == 0) {
          *(uint32_t *)(param_3 + 0x184) = cstack->m_arg;
        }
        else if (param_5 < 0) {
          if (-2 < param_5) {
            *(float *)(param_3 + 0x184) = *(float *)(param_3 + 0x184) - (float)cstack->m_arg;
          }
        }
        else if (param_5 < 2) {
          *(float *)(param_3 + 0x184) = *(float *)(param_3 + 0x184) + (float)cstack->m_arg;
        }
      }
    }
  }
  else if (1 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,&DAT_801da778);
  }
  return;
}

