// Function: __ct__Q26CChara5CAnimFv
// Entry: 800bfde0
// Size: 152 bytes

CRef * __ct__Q26CChara5CAnimFv(CRef *param_1)

{
  __ct__4CRefFv(param_1);
  param_1->vtable = &PTR_PTR_s_CChara_CAnim_80210534;
  *(undefined2 *)((int)&param_1[1].refCount + 2) = 0;
  param_1[2].refCount = 0;
  param_1[4].vtable = (void *)0x0;
  *(byte *)&param_1[1].vtable = *(byte *)&param_1[1].vtable & 0x7f | 0x80;
  *(byte *)&param_1[1].vtable = *(byte *)&param_1[1].vtable & 0xbf;
  *(undefined *)((int)&param_1[1].vtable + 2) = 5;
  *(undefined *)((int)&param_1[1].vtable + 3) = 0xb;
  *(undefined *)&param_1[1].refCount = 10;
  *(undefined *)((int)&param_1[1].vtable + 1) = 0;
  param_1[3].vtable = (void *)0x0;
  param_1[5].vtable = (void *)0x0;
  param_1[3].refCount = 0;
  param_1[5].refCount = 0;
  param_1[4].refCount = 0;
  return param_1;
}

