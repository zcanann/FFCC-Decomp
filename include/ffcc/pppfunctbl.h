#ifndef _FFCC_FUNCTBL_H_
#define _FFCC_FUNCTBL_H_

#include "ffcc/LocationTitle2.h"
#include "ffcc/partMng.h"
#include "ffcc/pppAccele.h"
#include "ffcc/pppAlignmentScale.h"
#include "ffcc/pppAngAccele.h"
#include "ffcc/pppAngle.h"
#include "ffcc/pppAngMove.h"
#include "ffcc/pppBindOnlyPos.h"
#include "ffcc/pppBlurChara.h"
#include "ffcc/pppBreathModel.h"
#include "ffcc/pppCallBackDistance.h"
#include "ffcc/pppChangeBGColor.h"
#include "ffcc/pppChangeTex.h"
#include "ffcc/pppCharaBreak.h"
#include "ffcc/pppCharaZEnvCtrl.h"
#include "ffcc/pppColAccele.h"
#include "ffcc/pppColMove.h"
#include "ffcc/pppColor.h"
#include "ffcc/pppColum.h"
#include "ffcc/pppConformBGNormal.h"
#include "ffcc/pppConstrainCameraDir.h"
#include "ffcc/pppConstrainCameraDir2.h"
#include "ffcc/pppConstrainCameraForLoc.h"
#include "ffcc/pppCorona.h"
#include "ffcc/pppCrystal.h"
#include "ffcc/pppCrystal2.h"
#include "ffcc/pppDrawMatrix.h"
#include "ffcc/pppDrawMatrixFront.h"
#include "ffcc/pppDrawMatrixFrontLnr.h"
#include "ffcc/pppDrawMatrixLoc.h"
#include "ffcc/pppDrawMatrixNoRot.h"
#include "ffcc/pppDrawMatrixWood.h"
#include "ffcc/pppDrawMdl.h"
#include "ffcc/pppDrawMdlTs.h"
#include "ffcc/pppDrawShape.h"
#include "ffcc/pppDrawShape2.h"
#include "ffcc/pppEmission.h"
#include "ffcc/pppEraseCharaParts.h"
#include "ffcc/pppFilter.h"
#include "ffcc/pppFovAdjustMatrix.h"
#include "ffcc/pppKeDMat.h"
#include "ffcc/pppKeLns.h"
#include "ffcc/pppKeShpTail.h"
#include "ffcc/pppKeShpTail2X.h"
#include "ffcc/pppKeShpTail3X.h"
#include "ffcc/pppKeZCrctShp.h"
#include "ffcc/pppLaser.h"
#include "ffcc/pppLensFlare.h"
#include "ffcc/pppLerpPos.h"
#include "ffcc/pppLight.h"
#include "ffcc/pppLocationTitle.h"
#include "ffcc/pppMana2.h"
#include "ffcc/pppMatrixLoc.h"
#include "ffcc/pppMatrixScl.h"
#include "ffcc/pppMatrixXYZ.h"
#include "ffcc/pppMatrixXZY.h"
#include "ffcc/pppMatrixYXZ.h"
#include "ffcc/pppMatrixYZX.h"
#include "ffcc/pppMatrixZXY.h"
#include "ffcc/pppMatrixZYX.h"
#include "ffcc/pppMiasma.h"
#include "ffcc/pppMove.h"
#include "ffcc/pppParHitSph.h"
#include "ffcc/pppParHitSphMat.h"
#include "ffcc/pppParMatrix.h"
#include "ffcc/pppParMoveLine.h"
#include "ffcc/pppParMoveMatrix.h"
#include "ffcc/pppPObjPoint.h"
#include "ffcc/pppPoint.h"
#include "ffcc/pppPointAp.h"
#include "ffcc/pppPointApMtx.h"
#include "ffcc/pppPointRAp.h"
#include "ffcc/pppRain.h"
#include "ffcc/pppRandChar.h"
#include "ffcc/pppRandCV.h"
#include "ffcc/pppRandDownChar.h"
#include "ffcc/pppRandDownCV.h"
#include "ffcc/pppRandDownFloat.h"
#include "ffcc/pppRandDownFV.h"
#include "ffcc/pppRandDownHCV.h"
#include "ffcc/pppRandDownInt.h"
#include "ffcc/pppRandDownIV.h"
#include "ffcc/pppRandDownShort.h"
#include "ffcc/pppRandFloat.h"
#include "ffcc/pppRandFV.h"
#include "ffcc/pppRandHCV.h"
#include "ffcc/pppRandInt.h"
#include "ffcc/pppRandIV.h"
#include "ffcc/pppRandShort.h"
#include "ffcc/pppRandUpChar.h"
#include "ffcc/pppRandUpCV.h"
#include "ffcc/pppRandUpFloat.h"
#include "ffcc/pppRandUpFV.h"
#include "ffcc/pppRandUpHCV.h"
#include "ffcc/pppRandUpInt.h"
#include "ffcc/pppRandUpIV.h"
#include "ffcc/pppRandUpShort.h"
#include "ffcc/pppRyjMegaBirth.h"
#include "ffcc/pppRyjMegaBirthModel.h"
#include "ffcc/pppScale.h"
#include "ffcc/pppScaleLoopAuto.h"
#include "ffcc/pppSclAccele.h"
#include "ffcc/pppSclMove.h"
#include "ffcc/pppScreenBlur.h"
#include "ffcc/pppScreenBreak.h"
#include "ffcc/pppScreenQuake.h"
#include "ffcc/pppSDrawMatrix.h"
#include "ffcc/pppSpMatrix.h"
#include "ffcc/pppSRandCV.h"
#include "ffcc/pppSRandDownCV.h"
#include "ffcc/pppSRandDownFV.h"
#include "ffcc/pppSRandDownHCV.h"
#include "ffcc/pppSRandFV.h"
#include "ffcc/pppSRandHCV.h"
#include "ffcc/pppSRandUpCV.h"
#include "ffcc/pppSRandUpFV.h"
#include "ffcc/pppSRandUpHCV.h"
#include "ffcc/pppVertexAp.h"
#include "ffcc/pppVertexApAt.h"
#include "ffcc/pppVertexApLc.h"
#include "ffcc/pppVertexApMtx.h"
#include "ffcc/pppVertexAttend.h"
#include "ffcc/pppVtMime.h"
#include "ffcc/pppWDrawMatrix.h"
#include "ffcc/pppWDrawMatrixFront.h"
#include "ffcc/pppWDrawMatrixFrontLoop.h"
#include "ffcc/pppWDrawMatrixLoop.h"
#include "ffcc/pppYmBreath.h"
#include "ffcc/pppYmCallBack.h"
#include "ffcc/pppYmChangeTex.h"
#include "ffcc/pppYmCheckBGHeight.h"
#include "ffcc/pppYmDeformationMdl.h"
#include "ffcc/pppYmDeformationScreen.h"
#include "ffcc/pppYmDeformationShp.h"
#include "ffcc/pppYmDrawMdlTexAnm.h"
#include "ffcc/pppYmLaser.h"
#include "ffcc/pppYmLookOn.h"
#include "ffcc/pppYmMana.h"
#include "ffcc/pppYmMegaBirthShpTail2.h"
#include "ffcc/pppYmMegaBirthShpTail3.h"
#include "ffcc/pppYmMelt.h"
#include "ffcc/pppYmMiasma.h"
#include "ffcc/pppYmMoveCircle.h"
#include "ffcc/pppYmMoveParabola.h"
#include "ffcc/pppYmTraceMove.h"
#include "ffcc/pppYmTracer.h"
#include "ffcc/pppYmTracer2.h"

struct _pppSysProgTbl
{
    pppProg* m_progs;
};

static pppProg s_pppSysProgTable[159] = {
    {
        (char*)"pppDummyFunc",
        0,
        0,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppAccele",
        0,
        (void*)pppAccele,
        0,
        { 0, 0, 0 },
        (void*)pppAcceleCon,
        (void*)pppAcceleCon,
        0,
        0
    },
    {
        (char*)"pppAngAccele",
        0,
        (void*)pppAngAccele,
        0,
        { 0, 0, 0 },
        (void*)pppAngAcceleCon,
        (void*)pppAngAcceleCon,
        0,
        0
    },
    {
        (char*)"pppAngle",
        0,
        (void*)pppAngle,
        0,
        { 0, 0, 0 },
        (void*)pppAngleCon,
        (void*)pppAngleCon,
        0,
        0
    },
    {
        (char*)"pppAngMove",
        0,
        (void*)pppAngMove,
        0,
        { 0, 0, 0 },
        (void*)pppAngMoveCon,
        (void*)pppAngMoveCon,
        0,
        0
    },
    {
        (char*)"pppColAccele",
        0,
        (void*)pppColAccele,
        0,
        { 0, 0, 0 },
        (void*)pppColAcceleCon,
        (void*)pppColAcceleCon,
        0,
        0
    },
    {
        (char*)"pppColMove",
        0,
        (void*)pppColMove,
        0,
        { 0, 0, 0 },
        (void*)pppColMoveCon,
        (void*)pppColMoveCon,
        0,
        0
    },
    {
        (char*)"pppColor",
        0,
        (void*)pppColor,
        0,
        { 0, 0, 0 },
        (void*)pppColorCon,
        (void*)pppColorCon,
        0,
        0
    },
    {
        (char*)"pppMatrix",
        0,
        (void*)pppMatrixXYZ,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixLoc",
        0,
        (void*)pppMatrixLoc,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixScl",
        0,
        (void*)pppMatrixScl,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixXYZ",
        0,
        (void*)pppMatrixXYZ,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixXZY",
        0,
        (void*)pppMatrixXZY,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixYXZ",
        0,
        (void*)pppMatrixYXZ,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixYZX",
        0,
        (void*)pppMatrixYZX,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixZXY",
        0,
        (void*)pppMatrixZXY,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixZYX",
        0,
        (void*)pppMatrixZYX,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMove",
        0,
        (void*)pppMove,
        0,
        { 0, 0, 0 },
        (void*)pppMoveCon,
        (void*)pppMoveCon,
        0,
        0
    },
    {
        (char*)"pppParMatrix",
        0,
        (void*)pppParMatrix,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppPObjPoint",
        0,
        (void*)pppPObjPoint,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppPoint",
        0,
        (void*)pppPoint,
        0,
        { 0, 0, 0 },
        (void*)pppPointCon,
        (void*)pppPointCon,
        0,
        0
    },
    {
        (char*)"pppPointAp",
        0,
        (void*)pppPointAp,
        0,
        { 0, 0, 0 },
        (void*)pppPointApCon,
        0,
        0,
        0
    },
    {
        (char*)"pppPointRAp",
        0,
        (void*)pppPointRAp,
        0,
        { 0, 0, 0 },
        (void*)pppPointRApCon,
        0,
        0,
        0
    },
    {
        (char*)"pppRandChar",
        0,
        (void*)pppRandChar,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandCV",
        0,
        (void*)pppRandCV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownChar",
        0,
        (void*)pppRandDownChar,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownCV",
        0,
        (void*)pppRandDownCV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownFloat",
        0,
        (void*)pppRandDownFloat,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownFV",
        0,
        (void*)pppRandDownFV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownHCV",
        0,
        (void*)pppRandDownHCV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownInt",
        0,
        (void*)pppRandDownInt,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownIV",
        0,
        (void*)pppRandDownIV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownShort",
        0,
        (void*)pppRandDownShort,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandFloat",
        0,
        (void*)pppRandFloat,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandFV",
        0,
        (void*)pppRandFV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandHCV",
        0,
        (void*)pppRandHCV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandInt",
        0,
        (void*)pppRandInt,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandIV",
        0,
        (void*)pppRandIV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandShort",
        0,
        (void*)pppRandShort,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpChar",
        0,
        (void*)pppRandUpChar,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpCV",
        0,
        (void*)pppRandUpCV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpFloat",
        0,
        (void*)pppRandUpFloat,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpFV",
        0,
        (void*)pppRandUpFV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpHCV",
        0,
        (void*)pppRandUpHCV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpInt",
        0,
        (void*)pppRandUpInt,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpIV",
        0,
        (void*)pppRandUpIV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpShort",
        0,
        (void*)pppRandUpShort,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppScale",
        0,
        (void*)pppScale,
        0,
        { 0, 0, 0 },
        (void*)pppScaleCon,
        (void*)pppScaleCon,
        0,
        0
    },
    {
        (char*)"pppSclAccele",
        0,
        (void*)pppSclAccele,
        0,
        { 0, 0, 0 },
        (void*)pppSclAcceleCon,
        (void*)pppSclAcceleCon,
        0,
        0
    },
    {
        (char*)"pppSclMove",
        0,
        (void*)pppSclMove,
        0,
        { 0, 0, 0 },
        (void*)pppSclMoveCon,
        (void*)pppSclMoveCon,
        0,
        0
    },
    {
        (char*)"pppSMatrix",
        0,
        0,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandCV",
        0,
        (void*)pppSRandCV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandDownCV",
        0,
        (void*)pppSRandDownCV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandDownFV",
        0,
        (void*)pppSRandDownFV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandDownHCV",
        0,
        (void*)pppSRandDownHCV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandFV",
        0,
        (void*)pppSRandFV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandHCV",
        0,
        (void*)pppSRandHCV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandUpCV",
        0,
        (void*)pppSRandUpCV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandUpFV",
        0,
        (void*)pppSRandUpFV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandUpHCV",
        0,
        (void*)pppSRandUpHCV,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppVertexAp",
        0,
        (void*)pppVertexAp,
        0,
        { 0, 0, 0 },
        (void*)pppVertexApCon,
        0,
        0,
        0
    },
    {
        (char*)"pppVertexApAt",
        0,
        (void*)pppVertexApAt,
        0,
        { 0, 0, 0 },
        (void*)pppVertexApAtCon,
        (void*)pppVertexApAtCon,
        0,
        0
    },
    {
        (char*)"pppVertexApLc",
        0,
        (void*)pppVertexApLc,
        0,
        { 0, 0, 0 },
        (void*)pppVertexApLcCon,
        (void*)pppVertexApLcCon,
        0,
        0
    },
    {
        (char*)"pppVertexAttend",
        0,
        (void*)pppVertexAttend,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppVtMime",
        0,
        (void*)pppVtMime,
        (void*)pppDrawVtMime,
        { 0, 0, 0 },
        (void*)pppVtMimeCon,
        (void*)pppVtMimeCon2,
        0,
        (void*)pppVtMimeDes
    },
    {
        (char*)"pppDrawMatrix",
        0,
        0,
        (void*)pppDrawMatrix,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppDrawMatrixFront",
        0,
        0,
        (void*)pppDrawMatrixFront,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppDrawMdl",
        0,
        0,
        (void*)pppDrawMdl,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppDrawShape",
        0,
        (void*)pppCalcShape,
        (void*)pppDrawShape,
        { 0, 0, 0 },
        (void*)pppDrawShapeConstruct,
        (void*)pppDrawShapeConstruct,
        0,
        0
    },
    {
        (char*)"pppRyjMegaBirth",
        0,
        (void*)pppRyjMegaBirth,
        (void*)pppRyjDrawMegaBirth,
        { 0, 0, 0 },
        (void*)pppRyjMegaBirthCon,
        0,
        0,
        (void*)pppRyjMegaBirthDes
    },
    {
        (char*)"pppRyjMegaBirthModel",
        0,
        (void*)pppRyjMegaBirthModel,
        (void*)pppRyjDrawMegaBirthModel,
        { 0, 0, 0 },
        (void*)pppRyjMegaBirthModelCon,
        0,
        0,
        (void*)pppRyjMegaBirthModelDes
    },
    {
        (char*)"pppDrawMdlTs",
        0,
        (void*)pppDrawMdlTs,
        (void*)pppDrawDrawMdlTs,
        { 0, 0, 0 },
        (void*)pppDrawMdlTsCon,
        (void*)pppDrawMdlTsCon,
        0,
        0
    },
    {
        (char*)"pppKeShpTail",
        0,
        (void*)pppKeShpTail,
        (void*)pppKeShpTailDraw,
        { 0, 0, 0 },
        (void*)pppKeShpTailCon,
        0,
        0,
        0
    },
    {
        (char*)"pppKeShpTail2X",
        0,
        (void*)pppKeShpTail2X,
        (void*)pppKeShpTail2XDraw,
        { 0, 0, 0 },
        (void*)pppKeShpTail2XCon,
        0,
        0,
        (void*)pppKeShpTail2XDes
    },
    {
        (char*)"pppKeZCrctShp",
        0,
        0,
        (void*)pppKeZCrctShpDraw,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppKeShpTail3X",
        0,
        (void*)pppKeShpTail3X,
        (void*)pppKeShpTail3XDraw,
        { 0, 0, 0 },
        (void*)pppKeShpTail3XCon,
        0,
        0,
        (void*)pppKeShpTail3XDes
    },
    {
        (char*)"pppMoveLoop",
        0,
        (void*)pppMove,
        0,
        { 0, 0, 0 },
        (void*)pppMoveCon,
        0,
        0,
        0
    },
    {
        (char*)"pppAngMoveLoop",
        0,
        (void*)pppAngMove,
        0,
        { 0, 0, 0 },
        (void*)pppAngMoveCon,
        0,
        0,
        0
    },
    {
        (char*)"pppSclMoveLoop",
        0,
        (void*)pppSclMove,
        0,
        { 0, 0, 0 },
        (void*)pppSclMoveCon,
        0,
        0,
        0
    },
    {
        (char*)"pppPointLoop",
        0,
        (void*)pppPoint,
        0,
        { 0, 0, 0 },
        (void*)pppPointCon,
        0,
        0,
        0
    },
    {
        (char*)"pppAngleLoop",
        0,
        (void*)pppAngle,
        0,
        { 0, 0, 0 },
        (void*)pppAngleCon,
        0,
        0,
        0
    },
    {
        (char*)"pppScaleLoop",
        0,
        (void*)pppScale,
        0,
        { 0, 0, 0 },
        (void*)pppScaleCon,
        0,
        0,
        0
    },
    {
        (char*)"pppColorLoop",
        0,
        (void*)pppColor,
        0,
        { 0, 0, 0 },
        (void*)pppColorCon,
        0,
        0,
        0
    },
    {
        (char*)"pppDrawMdlLoop",
        0,
        (void*)pppDrawMdlTs,
        (void*)pppDrawDrawMdlTs,
        { 0, 0, 0 },
        (void*)pppDrawMdlTsCon,
        0,
        (void*)pppDrawMdlTsCon3,
        0
    },
    {
        (char*)"pppYmDrawMdlTexAnm",
        0,
        (void*)pppFrameYmDrawMdlTexAnm,
        (void*)pppRenderYmDrawMdlTexAnm,
        { 0, 0, 0 },
        (void*)pppConstructYmDrawMdlTexAnm,
        0,
        0,
        (void*)pppDestructYmDrawMdlTexAnm
    },
    {
        (char*)"pppDrawMatrixWood",
        0,
        0,
        (void*)pppDrawMatrixWood,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppDrawMatrixNoRot",
        0,
        0,
        (void*)pppDrawMatrixNoRot,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmMegaBirthShpTail2",
        0,
        (void*)pppFrameYmMegaBirthShpTail2,
        (void*)pppRenderYmMegaBirthShpTail2,
        { 0, 0, 0 },
        (void*)pppConstructYmMegaBirthShpTail2,
        0,
        0,
        (void*)pppDestructYmMegaBirthShpTail2
    },
    {
        (char*)"pppYmMegaBirthShpTail3",
        0,
        (void*)pppFrameYmMegaBirthShpTail3,
        (void*)pppRenderYmMegaBirthShpTail3,
        { 0, 0, 0 },
        (void*)pppConstructYmMegaBirthShpTail3,
        0,
        0,
        (void*)pppDestructYmMegaBirthShpTail3
    },
    {
        (char*)"pppKeLnsFls",
        0,
        0,
        (void*)pppKeLnsFlsDraw,
        { 0, 0, 0 },
        (void*)pppKeLnsFlsCon,
        0,
        0,
        0
    },
    {
        (char*)"pppKeLnsLp",
        0,
        0,
        (void*)pppKeLnsLpDraw,
        { 0, 0, 0 },
        (void*)pppKeLnsLpCon,
        (void*)pppKeLnsLpCon2,
        0,
        0
    },
    {
        (char*)"pppKeDMat",
        0,
        0,
        (void*)pppKeDMatDraw,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmDeformationShp",
        0,
        (void*)pppFrameYmDeformationShp,
        (void*)pppRenderYmDeformationShp,
        { 0, 0, 0 },
        (void*)pppConstructYmDeformationShp,
        (void*)pppConstruct2YmDeformationShp,
        0,
        (void*)pppDestructYmDeformationShp
    },
    {
        (char*)"pppWDrawMatrix",
        0,
        0,
        (void*)pppWDrawMatrix,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppWDrawMatrixFront",
        0,
        0,
        (void*)pppWDrawMatrixFront,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppParMoveLine",
        0,
        (void*)pppParMoveLine,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmMiasma",
        0,
        (void*)pppFrameYmMiasma,
        (void*)pppRenderYmMiasma,
        { 0, 0, 0 },
        (void*)pppConstructYmMiasma,
        (void*)pppConstruct2YmMiasma,
        0,
        (void*)pppDestructYmMiasma
    },
    {
        (char*)"pppYmDeformationScreen",
        0,
        (void*)pppFrameYmDeformationScreen,
        (void*)pppRenderYmDeformationScreen,
        { 0, 0, 0 },
        (void*)pppConstructYmDeformationScreen,
        (void*)pppConstruct2YmDeformationScreen,
        0,
        (void*)pppDestructYmDeformationScreen
    },
    {
        (char*)"pppYmTracer",
        0,
        (void*)pppFrameYmTracer,
        (void*)pppRenderYmTracer,
        { 0, 0, 0 },
        (void*)pppConstructYmTracer,
        (void*)pppConstruct2YmTracer,
        0,
        (void*)pppDestructYmTracer
    },
    {
        (char*)"pppParHitSph",
        0,
        (void*)pppParHitSph,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmMelt",
        0,
        (void*)pppFrameYmMelt,
        (void*)pppRenderYmMelt,
        { 0, 0, 0 },
        (void*)pppConstructYmMelt,
        0,
        0,
        (void*)pppDestructYmMelt
    },
    {
        (char*)"pppYmCallBack",
        0,
        (void*)pppFrameYmCallBack,
        0,
        { 0, 0, 0 },
        (void*)pppConstructYmCallBack,
        0,
        0,
        (void*)pppDestructYmCallBack
    },
    {
        (char*)"pppYmBreath",
        0,
        (void*)pppFrameYmBreath,
        (void*)pppRenderYmBreath,
        { 0, 0, 0 },
        (void*)pppConstructYmBreath,
        (void*)pppConstruct2YmBreath,
        0,
        (void*)pppDestructYmBreath
    },
    {
        (char*)"pppWDrawMatrixLoop",
        0,
        0,
        (void*)pppWDrawMatrixLoop,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppWDrawMatrixFrontLoop",
        0,
        0,
        (void*)pppWDrawMatrixFrontLoop,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmMoveCircle",
        0,
        (void*)pppFrameYmMoveCircle,
        0,
        { 0, 0, 0 },
        (void*)pppConstructYmMoveCircle,
        0,
        0,
        0
    },
    {
        (char*)"pppDrawMatrixFrontLnr",
        0,
        0,
        (void*)pppDrawMatrixFrontLnr,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmDeformationMdl",
        0,
        (void*)pppFrameYmDeformationMdl,
        (void*)pppRenderYmDeformationMdl,
        { 0, 0, 0 },
        (void*)pppConstructYmDeformationMdl,
        (void*)pppConstruct2YmDeformationMdl,
        0,
        (void*)pppDestructYmDeformationMdl
    },
    {
        (char*)"pppPointApMtx",
        0,
        (void*)pppPointApMtx,
        0,
        { 0, 0, 0 },
        (void*)pppPointApMtxCon,
        0,
        0,
        0
    },
    {
        (char*)"pppVertexApMtx",
        0,
        (void*)pppVertexApMtx,
        0,
        { 0, 0, 0 },
        (void*)pppVertexApMtxCon,
        0,
        0,
        0
    },
    {
        (char*)"pppSDrawMatrix",
        0,
        0,
        (void*)pppSDrawMatrix,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmLaser",
        0,
        (void*)pppFrameYmLaser,
        (void*)pppRenderYmLaser,
        { 0, 0, 0 },
        (void*)pppConstructYmLaser,
        (void*)pppConstruct2YmLaser,
        0,
        (void*)pppDestructYmLaser
    },
    {
        (char*)"pppSpMatrix",
        0,
        (void*)pppSpMatrix,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmChangeTex",
        0,
        (void*)pppFrameYmChangeTex,
        (void*)pppRenderYmChangeTex,
        { 0, 0, 0 },
        (void*)pppConstructYmChangeTex,
        0,
        0,
        (void*)pppDestructYmChangeTex
    },
    {
        (char*)"pppYmMoveParabola",
        0,
        (void*)pppFrameYmMoveParabola,
        0,
        { 0, 0, 0 },
        (void*)pppConstructYmMoveParabola,
        0,
        0,
        0
    },
    {
        (char*)"pppParMoveMatrix",
        0,
        (void*)pppParMoveMatrix,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmTraceMove",
        0,
        (void*)pppFrameYmTraceMove,
        0,
        { 0, 0, 0 },
        (void*)pppConstructYmTraceMove,
        0,
        0,
        0
    },
    {
        (char*)"pppYmMana",
        0,
        (void*)pppFrameYmMana,
        (void*)pppRenderYmMana,
        { 0, 0, 0 },
        (void*)pppConstructYmMana,
        0,
        0,
        (void*)pppDestructYmMana
    },
    {
        (char*)"pppYmLookOn",
        0,
        (void*)pppFrameYmLookOn,
        0,
        { 0, 0, 0 },
        (void*)pppConstructYmLookOn,
        0,
        0,
        0
    },
    {
        (char*)"pppYmCheckBGHeight",
        0,
        (void*)pppFrameYmCheckBGHeight,
        0,
        { 0, 0, 0 },
        (void*)pppConstructYmCheckBGHeight,
        0,
        0,
        0
    },
    {
        (char*)"pppLocationTitle",
        0,
        (void*)pppFrameLocationTitle,
        (void*)pppRenderLocationTitle,
        { 0, 0, 0 },
        (void*)pppConstructLocationTitle,
        0,
        0,
        (void*)pppDestructLocationTitle
    },
    {
        (char*)"pppLocationTitle2",
        0,
        (void*)pppFrameLocationTitle2,
        (void*)pppRenderLocationTitle2,
        { 0, 0, 0 },
        (void*)pppConstructLocationTitle2,
        0,
        0,
        (void*)pppDestructLocationTitle2
    },
    {
        (char*)"pppDrawShape2",
        0,
        (void*)pppCalcShape2,
        (void*)pppDrawShape2,
        { 0, 0, 0 },
        (void*)pppDrawShape2Construct,
        (void*)pppDrawShape2Construct,
        0,
        0
    },
    {
        (char*)"pppLight",
        0,
        (void*)pppLight,
        0,
        { 0, 0, 0 },
        (void*)pppLightCon,
        (void*)pppLightCon,
        0,
        0
    },
    {
        (char*)"pppBreathModel",
        0,
        (void*)pppFrameBreathModel,
        (void*)pppRenderBreathModel,
        { 0, 0, 0 },
        (void*)pppConstructBreathModel,
        0,
        0,
        (void*)pppDestructBreathModel
    },
    {
        (char*)"pppCrystal",
        0,
        (void*)pppFrameCrystal,
        (void*)pppRenderCrystal,
        { 0, 0, 0 },
        (void*)pppConstructCrystal,
        0,
        0,
        (void*)pppDestructCrystal
    },
    {
        (char*)"pppRain",
        0,
        (void*)pppFrameRain,
        (void*)pppRenderRain,
        { 0, 0, 0 },
        (void*)pppConstructRain,
        0,
        0,
        (void*)pppDestructRain
    },
    {
        (char*)"pppBlurChara",
        0,
        (void*)pppFrameBlurChara,
        (void*)pppRenderBlurChara,
        { 0, 0, 0 },
        (void*)pppConstructBlurChara,
        0,
        0,
        (void*)pppDestructBlurChara
    },
    {
        (char*)"pppLensFlare",
        0,
        (void*)pppFrameLensFlare,
        (void*)pppRenderLensFlare,
        { 0, 0, 0 },
        (void*)pppConstructLensFlare,
        0,
        0,
        (void*)pppDestructLensFlare
    },
    {
        (char*)"pppCorona",
        0,
        (void*)pppFrameCorona,
        (void*)pppRenderCorona,
        { 0, 0, 0 },
        (void*)pppConstructCorona,
        0,
        0,
        (void*)pppDestructCorona
    },
    {
        (char*)"pppColum",
        0,
        (void*)pppFrameColum,
        (void*)pppRenderColum,
        { 0, 0, 0 },
        (void*)pppConstructColum,
        0,
        0,
        (void*)pppDestructColum
    },
    {
        (char*)"pppLightLoop",
        0,
        (void*)pppLight,
        0,
        { 0, 0, 0 },
        (void*)pppLightCon,
        (void*)pppLightCon,
        (void*)pppLightCon3,
        0
    },
    {
        (char*)"pppEmission",
        0,
        (void*)pppFrameEmission,
        (void*)pppRenderEmission,
        { 0, 0, 0 },
        (void*)pppConstructEmission,
        (void*)pppConstruct2Emission,
        0,
        (void*)pppDestructEmission
    },
    {
        (char*)"pppEraseCharaParts",
        0,
        (void*)pppFrameEraseCharaParts,
        0,
        { 0, 0, 0 },
        (void*)pppConstructEraseCharaParts,
        0,
        0,
        (void*)pppDestructEraseCharaParts
    },
    {
        (char*)"pppYmTracer2",
        0,
        (void*)pppFrameYmTracer2,
        (void*)pppRenderYmTracer2,
        { 0, 0, 0 },
        (void*)pppConstructYmTracer2,
        (void*)pppConstruct2YmTracer2,
        0,
        (void*)pppDestructYmTracer2
    },
    {
        (char*)"pppMana2",
        0,
        (void*)pppFrameMana2,
        (void*)pppRenderMana2,
        { 0, 0, 0 },
        (void*)pppConstructMana2,
        0,
        0,
        (void*)pppDestructMana2
    },
    {
        (char*)"pppConformBGNormal",
        0,
        (void*)pppFrameConformBGNormal,
        0,
        { 0, 0, 0 },
        (void*)pppConstructConformBGNormal,
        0,
        0,
        0
    },
    {
        (char*)"pppAlignmentScale",
        0,
        (void*)pppFrameAlignmentScale,
        0,
        { 0, 0, 0 },
        (void*)pppConstructAlignmentScale,
        0,
        0,
        0
    },
    {
        (char*)"pppMiasma",
        0,
        (void*)pppFrameMiasma,
        (void*)pppRenderMiasma,
        { 0, 0, 0 },
        (void*)pppConstructMiasma,
        (void*)pppConstruct2Miasma,
        0,
        (void*)pppDestructMiasma
    },
    {
        (char*)"pppBindOnlyPos",
        0,
        (void*)pppFrameBindOnlyPos,
        0,
        { 0, 0, 0 },
        (void*)pppConstructBindOnlyPos,
        0,
        0,
        0
    },
    {
        (char*)"pppLerpPos",
        0,
        (void*)pppFrameLerpPos,
        0,
        { 0, 0, 0 },
        (void*)pppConstructLerpPos,
        0,
        0,
        (void*)pppDestructLerpPos
    },
    {
        (char*)"pppScaleLoopAuto",
        0,
        (void*)pppScaleLoopAuto,
        0,
        { 0, 0, 0 },
        (void*)pppScaleLoopAutoCon,
        0,
        0,
        0
    },
    {
        (char*)"pppChangeBGColor",
        0,
        (void*)pppFrameChangeBGColor,
        0,
        { 0, 0, 0 },
        (void*)pppConChangeBGColor,
        0,
        0,
        (void*)pppDesChangeBGColor
    },
    {
        (char*)"pppScreenBreak",
        0,
        (void*)pppFrameScreenBreak,
        (void*)pppRenderScreenBreak,
        { 0, 0, 0 },
        (void*)pppConScreenBreak,
        (void*)pppCon2ScreenBreak,
        0,
        (void*)pppDesScreenBreak
    },
    {
        (char*)"pppScreenBlur",
        0,
        (void*)pppFrameScreenBlur,
        (void*)pppRenderScreenBlur,
        { 0, 0, 0 },
        (void*)pppConScreenBlur,
        (void*)pppCon2ScreenBlur,
        0,
        (void*)pppDesScreenBlur
    },
    {
        (char*)"pppScreenQuake",
        0,
        (void*)pppFrameScreenQuake,
        (void*)pppRenderScreenQuake,
        { 0, 0, 0 },
        (void*)pppConScreenQuake,
        (void*)pppCon2ScreenQuake,
        0,
        (void*)pppDesScreenQuake
    },
    {
        (char*)"pppCrystal2",
        0,
        (void*)pppFrameCrystal2,
        (void*)pppRenderCrystal2,
        { 0, 0, 0 },
        (void*)pppConstructCrystal2,
        0,
        0,
        (void*)pppDestructCrystal2
    },
    {
        (char*)"pppChangeTex",
        0,
        (void*)pppFrameChangeTex,
        (void*)pppRenderChangeTex,
        { 0, 0, 0 },
        (void*)pppConstructChangeTex,
        (void*)pppConstruct2ChangeTex,
        0,
        (void*)pppDestructChangeTex
    },
    {
        (char*)"pppCharaBreak",
        0,
        (void*)pppFrameCharaBreak,
        (void*)pppRenderCharaBreak,
        { 0, 0, 0 },
        (void*)pppConstructCharaBreak,
        (void*)pppConstruct2CharaBreak,
        0,
        (void*)pppDestructCharaBreak
    },
    {
        (char*)"pppCallBackDistance",
        0,
        (void*)pppFrameCallBackDistance,
        0,
        { 0, 0, 0 },
        (void*)pppConstructCallBackDistance,
        0,
        0,
        (void*)pppDestructCallBackDistance
    },
    {
        (char*)"pppParHitSphMat",
        0,
        (void*)pppParHitSphMat,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppConstrainCameraDir",
        0,
        (void*)pppFrameConstrainCameraDir,
        0,
        { 0, 0, 0 },
        (void*)pppConstructConstrainCameraDir,
        (void*)pppConstruct2ConstrainCameraDir,
        0,
        (void*)pppDestructConstrainCameraDir
    },
    {
        (char*)"pppFilter",
        0,
        (void*)pppFrameFilter,
        (void*)pppRenderFilter,
        { 0, 0, 0 },
        (void*)pppConstructFilter,
        0,
        0,
        (void*)pppDestructFilter
    },
    {
        (char*)"pppConstrainCameraForLoc",
        0,
        (void*)pppFrameConstrainCameraForLoc,
        0,
        { 0, 0, 0 },
        (void*)pppConstructConstrainCameraForLoc,
        (void*)pppConstruct2ConstrainCameraForLoc,
        (void*)fn_80167EC4,
        (void*)pppDestructConstrainCameraForLoc
    },
    {
        (char*)"pppDrawMatrixLoc",
        0,
        0,
        (void*)pppDrawMatrixLoc,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppCharaZEnvCtrl",
        0,
        (void*)pppFrameCharaZEnvCtrl,
        0,
        { 0, 0, 0 },
        (void*)pppConCharaZEnvCtrl,
        0,
        0,
        (void*)pppDesCharaZEnvCtrl
    },
    {
        (char*)"pppConstrainCameraDir2",
        0,
        (void*)pppFrameConstrainCameraDir2,
        0,
        { 0, 0, 0 },
        (void*)pppConstructConstrainCameraDir,
        (void*)pppConstruct2ConstrainCameraDir,
        0,
        (void*)pppDestructConstrainCameraDir
    },
    {
        (char*)"pppFovAdjustMatrix",
        0,
        (void*)pppFrameFovAdjustMatrix,
        0,
        { 0, 0, 0 },
        (void*)pppConstructFovAdjustMatrix,
        0,
        0,
        (void*)pppDestructFovAdjustMatrix
    },
    {
        (char*)"pppLaser",
        0,
        (void*)pppFrameLaser,
        (void*)pppRenderLaser,
        { 0, 0, 0 },
        (void*)pppConstructLaser,
        (void*)pppConstruct2Laser,
        0,
        (void*)pppDestructLaser
    },
};

static _pppSysProgTbl pppSysProgTbl = {
    s_pppSysProgTable,
};

static inline pppProg* pppGetSysProgTable()
{
    return pppSysProgTbl.m_progs;
}

#endif // _FFCC_FUNCTBL_H_
