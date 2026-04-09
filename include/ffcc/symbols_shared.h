#ifndef _FFCC_SYMBOLS_SHARED_H_
#define _FFCC_SYMBOLS_SHARED_H_

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const float kPppAcceleZero;
extern const float kPppMoveZero;
extern const float kPppKeLnsZero;
extern const float kKeLnsLineDefaultLength;
extern const float kPppBreathModelZero;
extern const float kPppChangeTexInit;
extern char kAStarGroupDebugFormat[];
extern char kAStarGroupDebugLabel[];
extern char kAStarPortalDebugFormat[];
extern const f32 kVecInvSqrtHalfConst;
extern const f32 kVecInvSqrtThreeConst;
extern const f32 kQuatNormalizeEpsilon;
extern const f32 kQuatHalf;
extern const f32 kQuatNormalizeThree;
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
extern const f32 kMenuInitOne;
extern const f32 kMenuOrthoBottom;
extern const f32 kMenuOrthoRight;
extern const f32 kMenuOrthoFar;

extern unsigned char gFontResArchiveData[];

extern const float kMapOctTreeDefaultOffsetZ;

extern const f32 kPppConformBgNormalZero;
extern const f32 kPppConformBgNormalOne;
extern const f32 kPppConformBgNormalDownRayY;
extern const f32 kPppConformBgNormalCylinderRadius;
extern const f32 kPppConformBgNormalCylinderHeight;
extern const f32 kPppConformBgNormalGroundSnapLimit;

extern const float kPppFilterScreenMin;
extern const float kPppFilterScreenMaxX;
extern const float kPppFilterScreenMaxY;

extern const float kPppScreenQuakeZero;
extern const float kPppKeShpTail2XZero;
extern const float kPppKeShpTail2XAlphaScale;
extern const float kPppKeShpTail3XOne;
extern const float kPppYmMegaBirthShpTail2Zero;
extern const float kPppYmMegaBirthShpTail3Zero;
extern const float kPppRyjMegaBirthZero;
extern const float kPppYmDeformationShpZero;
extern const f32 kPppLaserZero;
extern const double kPppColorScale;
extern const float kPppDrawDepthScaleNear;
extern const float kPppDrawDepthScaleFar;
extern const float kPppParHitSphZero;
extern const float kPppParHitSphMatZero;
extern const float kPppYmMeltZero;
extern const float kVectorZero;
extern const f32 kPppYmLaserOne;
extern const float kPppYmTraceMoveZero;
extern const float kPppYmTraceMoveOne;
extern const float kPppYmCheckBGHeightAxisZero;
extern const float kPppYmCheckBGHeightProbeDirY;
extern const float kPppYmCheckBGHeightCylinderScale;
extern const float kPppYmCheckBGHeightCylinderOffset;
extern const float kPppLightZero;
extern const float kPppLightOne;
extern const float kPppLightDefaultCosAtten;
extern const float kPppLightSpotScale;
extern const float kPppRainTexCoordBase;
extern const float kPppLensFlareZero;
extern const float kPppLensFlareAlphaScale;
extern const float kPppLensFlareCameraToObjectScale;
extern const float kPppLensFlareDepthToZScale;
extern const double kPppLensFlareUnusedDouble;
extern const float kPppCoronaViewDirX;
extern const float kPppCoronaViewDirY;
extern const float kPppCoronaViewDirZ;
extern const float kPppCoronaDistanceScaleBase;
extern const f32 kThpDrawLodBias;
extern const float kPppConstrainCameraDirScaleBase;
extern const float kPppConstrainCameraDirDistanceBase;
extern const float kPppConstrainCameraDirScaleMul;
extern const float kPppConstrainCameraDirInitScale;
extern const float kPppConstrainCameraDir2ScaleBase;
extern const float kPppConstrainCameraDir2DistanceBase;
extern const float kPppConstrainCameraDir2ScaleMul;
extern const float kPppConstrainCameraForLocZero;
extern int gPppCalcDisabled;
extern unsigned char gPppInConstructor;
extern u8 gPppDefaultValueBuffer[];
extern float gPartScreenMatrixRow2X;
extern float gPartScreenMatrixRow2Y;
extern float gPartScreenMatrixRow2W;
extern int gPppHeapUseRateWords[3];
extern char* gDebugSpinnerText;
extern unsigned char gDebugSpinnerTextInitialized;
extern int gDebugSpinnerFrame;
extern unsigned char gDebugSpinnerFrameInitialized;
extern u8* gCharaPartWorkPtr;
extern unsigned char* gMcPcsSingletonPtr;
extern const float kMaterialEditorControlMaxInit;
extern const float kMaterialEditorControlMinInit;
extern unsigned int kMaterialEditorDefaultColorRgba;
extern char sMaterialEditorSpinnerText[];
extern char sDebugSpinnerText[];
extern const float kPppHeapUseRateDivisor;
extern const float kPartColorIdentityOne;

extern const f32 kFunnyShapeNdcMax;
extern const f32 kFunnyShapeNdcMin;
extern const f32 kFunnyShapeOrthoFarZ;
extern const f32 kFunnyShapeViewportOrigin;
extern const f32 kFunnyShapeViewportWidth;
extern const f32 kFunnyShapeViewportHeight;

extern const double kCharaViewerColorCenterBias;
extern const float kCharaViewerZero;
extern const float kCharaViewerGridMax;
extern const float kCharaViewerUnitStep;
extern const float kCharaViewerGridSpacing;
extern const float kCharaViewerGridMin;
extern const double kCharaViewerColorWhiteBias;
extern const float kCharaViewerFineStep;
extern const float kCharaViewerLerpScale;
extern char kCharaViewerDefaultModelPath[];
extern const float kCharaViewerLightPosX;
extern const float kCharaViewerLightPosY;
extern const float kCharaViewerLightPosZ;
extern const float kCharaViewerLightTargetX;
extern const float kCharaViewerLightTargetY;
extern const float kCharaViewerLightTargetZ;

#ifdef __cplusplus
}
#endif

#endif // _FFCC_SYMBOLS_SHARED_H_
