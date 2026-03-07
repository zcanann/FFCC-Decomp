#ifndef _FFCC_SYMBOLS_SHARED_H_
#define _FFCC_SYMBOLS_SHARED_H_

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern float kPppAcceleZero;
extern float kPppMoveZero;
extern const float kPppKeLnsZero;
extern const float kKeLnsLineDefaultLength;
extern float kPppBreathModelZero;
extern float kPppChangeTexInit;
extern char kAStarGroupDebugFormat[];
extern char kAStarGroupDebugLabel[];
extern char kAStarPortalDebugFormat[];
extern f32 kVecInvSqrtHalfConst;
extern f32 kVecInvSqrtThreeConst;
extern unsigned int gGbaStatusWordTriplet0[];
extern unsigned int gGbaStatusWordTriplet1[];
extern unsigned int gGbaStatusWordTriplet2[];
extern unsigned int gGbaStatusWordTriplet3[];
extern unsigned int gGbaStatusWordTable[];
extern u8 gSingMenuItemIconByType[];
extern char* gSingMenuTextTableEn[];
extern char* gSingMenuTextTableDe[];
extern char* gSingMenuTextTableIt[];
extern char* gSingMenuTextTableFr[];
extern char* gSingMenuTextTableEs[];
extern char* gSingMenuHairTableFr[];
extern char* gSingMenuAttrTableEn[];
extern char* gSingMenuAttrTableDe[];
extern char* gSingMenuAttrTableIt[];
extern char* gSingMenuAttrTableFr[];
extern char* gSingMenuAttrTableEs[];
extern unsigned char gMenuProcessTable[];
extern f32 kMenuInitOne;

extern unsigned char gFontResArchiveData[];

extern float kMapOctTreeDefaultOffsetZ;

extern f32 kPppConformBgNormalZero;
extern f32 kPppConformBgNormalOne;
extern f32 kPppConformBgNormalDownRayY;
extern f32 kPppConformBgNormalCylinderRadius;
extern f32 kPppConformBgNormalCylinderHeight;
extern f32 kPppConformBgNormalGroundSnapLimit;

extern float kPppFilterScreenMin;
extern float kPppFilterScreenMaxX;
extern float kPppFilterScreenMaxY;

extern float kPppScreenQuakeZero;
extern float kPppKeShpTail2XZero;
extern float kPppKeShpTail2XAlphaScale;
extern float kPppKeShpTail3XOne;
extern float kPppYmMegaBirthShpTail2Zero;
extern float kPppYmMegaBirthShpTail3Zero;
extern float kPppRyjMegaBirthZero;
extern float kPppYmDeformationShpZero;
extern const f32 kPppLaserZero;
extern double kPppColorScale;
extern float kPppDrawDepthScaleNear;
extern float kPppDrawDepthScaleFar;
extern float kPppParHitSphZero;
extern float kPppParHitSphMatZero;
extern float kPppYmMeltZero;
extern float kVectorZero;
extern f32 kPppYmLaserOne;
extern float kPppYmTraceMoveZero;
extern float kPppYmCheckBGHeightAxisZero;
extern float kPppYmCheckBGHeightProbeDirY;
extern float kPppYmCheckBGHeightCylinderScale;
extern float kPppYmCheckBGHeightCylinderOffset;
extern float kPppLightZero;
extern float kPppLightOne;
extern float kPppLightDefaultCosAtten;
extern float kPppLightSpotScale;
extern float kPppRainTexCoordBase;
extern float kPppCoronaViewDirX;
extern float kPppCoronaViewDirY;
extern float kPppCoronaViewDirZ;
extern float kPppCoronaDistanceScaleBase;
extern f32 kThpDrawLodBias;
extern float kPppConstrainCameraDirScaleBase;
extern float kPppConstrainCameraDirDistanceBase;
extern float kPppConstrainCameraDirScaleMul;
extern float kPppConstrainCameraDirInitScale;
extern float kPppConstrainCameraForLocZero;
extern float gPartScreenMatrixRow2X;
extern float gPartScreenMatrixRow2Y;
extern float gPartScreenMatrixRow2W;
extern int gPppHeapUseRateWords[3];
extern char* gDebugSpinnerText;
extern unsigned char gDebugSpinnerTextInitialized;
extern int gDebugSpinnerFrame;
extern unsigned char gDebugSpinnerFrameInitialized;
extern u8* gCharaPartWorkPtr;
extern unsigned int gMcPcsSingletonPtr;
extern float kMaterialEditorControlMaxInit;
extern float kMaterialEditorControlMinInit;
extern unsigned int kMaterialEditorDefaultColorRgba;
extern char sMaterialEditorSpinnerText[];
extern char sDebugSpinnerText[];
extern float kPppHeapUseRateDivisor;
extern float kPartColorIdentityOne;

extern f32 kFunnyShapeNdcMax;
extern f32 kFunnyShapeNdcMin;
extern f32 kFunnyShapeOrthoFarZ;
extern f32 kFunnyShapeViewportOrigin;
extern f32 kFunnyShapeViewportWidth;
extern f32 kFunnyShapeViewportHeight;

extern double kCharaViewerColorCenterBias;
extern float kCharaViewerZero;
extern float kCharaViewerGridMax;
extern float kCharaViewerUnitStep;
extern float kCharaViewerGridSpacing;
extern float kCharaViewerGridMin;
extern double kCharaViewerColorWhiteBias;
extern float kCharaViewerFineStep;
extern float kCharaViewerLerpScale;
extern char kCharaViewerDefaultModelPath[];
extern float kCharaViewerLightPosX;
extern float kCharaViewerLightPosY;
extern float kCharaViewerLightPosZ;
extern float kCharaViewerLightTargetX;
extern float kCharaViewerLightTargetY;
extern float kCharaViewerLightTargetZ;

#ifdef __cplusplus
}
#endif

#endif // _FFCC_SYMBOLS_SHARED_H_
