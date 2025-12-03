#ifndef _GXFUNC_H_
#define _GXFUNC_H_

enum _GXTevStageID : int;
enum _GXTevMode : int;
enum _GXTevColorArg : int;
enum _GXTevAlphaArg : int;
enum _GXTevOp : int;
enum _GXTevBias : int;
enum _GXTevScale : int;
enum _GXTevRegID : int;
enum _GXCompare : int;
enum _GXAlphaOp : int;
enum _GXTexCoordID : int;
enum _GXTexMapID : int;
enum _GXChannelID : int;
enum _GXTevSwapSel : int;
enum _GXTevColorChan : int;
enum _GXBlendMode : int;
enum _GXBlendFactor : int;
enum _GXLogicOp : int;

void _GXSetTev0_Init(_GXTevStageID);
void _GXSetTev_Init();
void _GXSetTevOp(_GXTevStageID, _GXTevMode);
void _GXSetTevColorIn(_GXTevStageID, _GXTevColorArg, _GXTevColorArg, _GXTevColorArg, _GXTevColorArg);
void _GXSetTevAlphaIn(_GXTevStageID, _GXTevAlphaArg, _GXTevAlphaArg, _GXTevAlphaArg, _GXTevAlphaArg);
void _GXSetTevColorOp(_GXTevStageID, _GXTevOp, _GXTevBias, _GXTevScale, unsigned char, _GXTevRegID);
void _GXSetTevAlphaOp(_GXTevStageID, _GXTevOp, _GXTevBias, _GXTevScale, unsigned char, _GXTevRegID);
void _GXSetAlphaCompare(_GXCompare, unsigned char, _GXAlphaOp, _GXCompare, unsigned char);
void _GXSetTevOrder(_GXTevStageID, _GXTexCoordID, _GXTexMapID, _GXChannelID);
void _GXSetTevSwapMode(_GXTevStageID, _GXTevSwapSel, _GXTevSwapSel);
void _GXSetTevSwapModeTable(_GXTevSwapSel, _GXTevColorChan, _GXTevColorChan, _GXTevColorChan, _GXTevColorChan);
void _GXSetPixel_Init();
void _GXSetBlendMode(_GXBlendMode, _GXBlendFactor, _GXBlendFactor, _GXLogicOp);
void _InitGxFunc();

#endif // _GXFUNC_H_
