/** 
@brief 平台枚举定义
@file    P3DKJEnumDefine.h
@author  北京构力科技有限公司
@date    2021-09-14
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/

#ifndef P3D_P3DDC_P3DKJEnumDefine_H
#define P3D_P3DDC_P3DKJEnumDefine_H

namespace p3d {
    namespace platform 
    {
        enum class P3DModelType : Int8
        {
            enPhysical = 0,
            enSheet = 1,
            enDrawing = 2,
        };

        // ____<pkpm_inner_begin>____
        enum class P3DModelSections : Int32
        {
            enNone = 0,
            enDictionary = (1 << 0),
            enControlEntitys = (1 << 1),
            enGraphicEntitys = (1 << 2),
            enModel = (enControlEntitys | enGraphicEntitys),

            enValid = (enDictionary | enModel),

            enAll = 0x7fffffff

        };
        // ____<pkpm_inner_end>____

        enum class P3DSelectionMode
        {
            enNew = 0,
            New = enNew,
            enAdd = 1,
            Add = enAdd,
            enSubtract = 2,
            Subtract = enSubtract,
            enInverse = 3,
            Inverse = enInverse,
            enClear = 4,
            Clear = enClear,
            enAll = 5,
            All = enAll
        };


        enum class P3DVirtualKey
        {
            enShift = VK_SHIFT,
            Shift = enShift,
            enControl = VK_CONTROL,
            Control = enControl,
            enAlt = VK_MENU,
            Alt = enAlt,
            enTab = VK_TAB,
            Tab = enTab,
            enReturn = VK_RETURN,
            Return = enReturn,
            enEscape = VK_ESCAPE,
            Escape = enEscape,
            enEnd = VK_END,
            End = enEnd,
            enHome = VK_HOME,
            Home = enHome,
            enLeft = VK_LEFT,
            Left = enLeft,
            enUp = VK_UP,
            Up = enUp,
            enRight = VK_RIGHT,
            Right = enRight,
            enDown = VK_DOWN,
            Down = enDown,
            enDelete = VK_DELETE,
            Delete = enDelete
        };

        enum class  P3DTextEntityJustification
        {
            enLeftTop = 0,
            LeftTop = enLeftTop,
            enLeftMiddle = 1,
            LeftMiddle = enLeftMiddle,
            enLeftBaseline = 2,
            LeftBaseline = enLeftBaseline,
            enLeftDescender = 16,
            LeftDescender = enLeftDescender,
            enCenterTop = 6,
            CenterTop = enCenterTop,
            enCenterMiddle = 7,
            CenterMiddle = enCenterMiddle,
            enCenterBaseline = 8,
            CenterBaseline = enCenterBaseline,
            enCenterDescender = 20,
            CenterDescender = enCenterDescender,
            enRightTop = 12,
            RightTop = enRightTop,
            enRightMiddle = 13,
            RightMiddle = enRightMiddle,
            enRightBaseline = 14,
            RightBaseline = enRightBaseline,
            enRightDescender = 24,
            RightDescender = enRightDescender,

            LeftMarginTop = 3,
            LeftMarginMiddle = 4,
            LeftMarginBaseline = 5,
            LeftMarginDescender = 18,
            RightMarginTop = 9,
            RightMarginMiddle = 10,
            RightMarginBaseline = 11,
            RightMarginDescender = 22,

            LeftCap = 15,
            LeftMarginCap = 17,
            CenterCap = 19,
            RightCap = 23,
            RightMarginCap = 21,

            Invalid = 127
        };

        enum class P3DStackedFractionSection
        {
            enNone = 0,
            enNumerator = 1,
            enDenominator = 2
        };

        enum class P3DCoordSystem
        {
            enScreen = 0,
            enView = 1,
            enNpc = 2,
            enWorld = 3,
            enActive = 4,
            enFrustum = 5,
        };


        enum class P3DFontType : UInt8
        {
            enNone = 0,
            enTrueType = 2,
            enShx = 3,
        };

        enum class P3DGraphicType : UInt8
        {
            enNone = 0,
            enCurveBase = 1,
            enGeCurveArray = 2,
            enPolyface = 3,
            enGeBsplineCurve = 4,
            enGeBsplineSurface = 5,
            enSolidPrimitive = 6,
            enText = 7,
            enSolidEntity = 8,
        };

        enum class P3DAlignmentMode : UInt8
        {
            enNone = 0,
            enAlongLocalInDrawing = 1,
            enAlongDrawing = 2,
            enBillboard = 3
        };

        enum class P3DRelationshipEventType : UInt8
        {
            enPreAdd = 0,
            enPostAdd,
            enPreDelete,
            enPostDelete
        };

        enum class P3DUsesFence
        {
            enCheck,
            enRequired,
            enNone,
        };

        enum class P3DUsesSelection
        {
            enCheck,
            enRequired,
            enNone,
        };

        enum class P3DUsesDragSelect
        {
            enBox,
            enLine,
            enNone,
        };

        enum class DimStyleBallAndChainModeProp : int
        {
            enNone = 0,
            enOn = 1,
            enAuto = 2,
            enCOUNT = 3,
        };

        enum class DimStyleBallAndChainAlignmentProp : int
        {
            enAuto = 0,
            enLeft = 1,
            enRight = 2,
            enCOUNT = 3,
        };

        enum class DimStyleArrowTypeProp : int
        {
            enNone = 0,
            enArrow = 1,
            enStroke = 2,
            enOrigin = 3,
            enDot = 4,
            enNote = 5,
            enCOUNT = 6,
        };

        enum class DimStyleBallAndChainTypeProp : int
        {
            enNone = 0,
            enLine = 1,
            enArc = 2,
            enBSpline = 3,
            enCOUNT = 4,
        };

        enum class DimStyleGeneralAlignmentProp : int
        {
            enView = 0,
            enDrawing = 1,
            enTrue = 2,
            enArbitrary = 3,
            enCOUNT = 4,
        };

        enum class DimStyleGeneralRadialModeProp : int
        {
            enCenterMark = 0,
            enRadius = 1,
            enDiameter = 2,
            enRadiusExtended = 3,
            enDiameterExtended = 4,
            enCOUNT = 5,
        };

        enum class DimStyleMLeaderFrameTypeProp : int
        {
            enNone = 0,
            enLine = 1,
            enBox = 2,
            enRotatedBox = 3,
            enCircle = 4,
            enCapsule = 5,
            enHexagon = 6,
            enRotatedHexagon = 7,
            enTriangle = 8,
            enPentagon = 9,
            enOctagon = 10,
            enCOUNT = 11,
        };

        enum class DimStyleMLeaderHJustificationProp : int
        {
            enLeft = 0,
            enRight = 1,
            enDynamic = 2,
            enCenter = 3,
            enCOUNT = 4,
        };

        enum class DimStyleMLeaderVJustificationProp : int
        {
            enTop = 0,
            enCenter = 1,
            enBottom = 2,
            enDynamic = 3,
            enCOUNT = 4,
        };

        enum class DimStyleMLeaderTextRotationProp : int
        {
            enHorizontal = 0,
            enVertical = 1,
            enAlongLine = 2,
            enAlongLineDynamic = 3,
            enCOUNT = 4,
        };

        enum class DimStyleMLeaderHorModelLinkProp : int
        {
            enAuto = 0,
            enLeft = 1,
            enRight = 2,
            enCOUNT = 3,
        };

        enum class DimStyleMLeaderVerModelLinkProp : int
        {
            enTop = 0,
            enTopLine = 1,
            enMiddle = 2,
            enBottomLine = 3,
            enBottom = 4,
            enDynamicLine = 5,
            enDynamicCorner = 6,
            enUnderline = 7,
            enTopUnder = 8,
            enTopUnderline = 9,
            enBottomUnderline = 10,
            enBottomUp = 11,
            enAllUnderline = 12,
            enCOUNT = 13,
        };

        enum  class DimStyleSymbolStandardProp : UShort
        {
            enNone = 0,
            enDiameter = 1,
            enRadius = 2,
            enArea = 3,
            enSphericalRadius = 4,
            enSphericalDiameter = 5,
            enCOUNT = 6,
        };

        enum class DimStyleSymbolCustomTypeProp : int
        {
            enDefault = 0,
            enCharacter = 1,
            enCOUNT = 2,
        };

        enum class DimStyleSymbolPreSufTypeProp : int
        {
            enNone = 0,
            enCharacter = 1,
            enBlock = 2,
            enCOUNT = 3,
        };

        enum class DimStyleSymbolArrowTypeProp : int
        {
            enDefault = 0,
            enCharacter = 1,
            enBlock = 2,
            enCOUNT = 3,
        };

        enum class DimStyleTypeProp : int
        {
            enCOUNT = 64,
        };

        enum class DimStyleArrowModeProp : int
        {
            enAuto = 0,
            enReversed = 1,
            enInside = 2,
            enOutside = 3,
            enCOUNT = 4,
        };

        enum class DimStyleArrowheadProp : int
        {
			enOpen = 0,
			enClosed = 1,
			enFilled = 2,
            enCOUNT = 3,
        };

        enum  class DimStyleTextJustificationProp : int
        {
            enMiddle = 0,
            enLeft = 1,
            enCenterLeft = 2,
            enRight = 3,
            enCenterRight = 4,
            enCOUNT = 5,
        };

        enum class DimStyleAnglePrecisionProp : int
        {
            en0Place = 0,
            en1Place = 1,
            en2Places = 2,
            en3Places = 3,
            en4Places = 4,
            en5Places = 5,
            en6Places = 6,
            enCOUNT = 7,
        };

        enum class DimStyleDMSPrecisionModeProp : int
        {

            enFixed = 0,

            enFloating = 1,

            enCOUNT = 2,
        };

        enum class DimStyleTextStackedFractionAlignmentProp : int
        {
            enTop = 0,
            enCenter = 1,
            enBottom = 2,
            enCOUNT = 3,
        };

        enum class DimStyleTextStackedFractionTypeProp : int
        {
            enFromFont = 0,
            enHorizontal = 1,
            enDiagonal = 2,
            enCOUNT = 3,
        };

        enum class DimStyleTextPositionProp : int
        {
            enManual = 0,
            enSemiAuto = 1,
            enAuto = 2,
            enCOUNT = 3,
        };

        enum class DimStyleTextLocationProp : int
        {
            enInline = 0,
            enAbove = 1,
            enOutside = 2,
            enTopLeft = 3,
            enCOUNT = 4,
        };

        enum class DimStyleTextSuperscriptModeProp : int
        {
            enFromFont = 0,
            enGenerated = 1,
            enCOUNT = 2,
        };

        enum class DimStyleValueFormatProp : int
        {
            enMetricUnit = 0,
            enMetricUnitLabel = 1,
            enSIUnit = 2,
            enSIUnitLabel = 3,
            enMUDashSU = 4,
            enMULabelSULabel = 5,
            enMULabelDashSULabel = 6,
            enCOUNT = 7,
        };

        enum class DimStyleValueComparisonProp : int
        {
            enLess = 0,
            enLessOrEqual = 1,
            enGreater = 2,
            enGreaterOrEqual = 3,
            enCOUNT = 4,
        };

        enum class DimStyleTextVerticalProp : UShort
        {
            enNoFit = 0,
            enNever = 1,
            enAlways = 2,
            enCOUNT = 3,
        };

        enum class DimStyleValueThousandsOptsProp : int
        {
            enNone = 0,
            enComma = 1,
            enSpace = 2,
            enCOUNT = 3,
        };

        enum class DimStyleTextFrameTypeProp : int
        {
            enNone = 0,
            enBox = 1,
            enCapsule = 2,
            enCOUNT = 3,
        };

        enum class DimStyleValueLabelLineFormatProp : int
        {
            enStandard = 0,
            enLengthAbove = 1,
            enLengthBelow = 2,
            enAngleAbove = 3,
            enAngleBelow = 4,
            enAngleOverLength = 5,
            enLengthAngleAbove = 6,
            enLengthAngleBelow = 7,
            enCOUNT = 8,
        };


        enum class DimStyleFitOptionsProp : int
        {

            enMoveArrowFirst = 0,
            enReverseArrow = 1,
            enKeepArrowInside = 2,
            enKeepArrowOutside = 3,
            enKeepTextInside = 4,
            enMoveTextFirst = 5,
            enMoveBoth = 6,
            enBestFit = 7,
            enCOUNT = 8,
        };

        enum class DimStyleProp : int
        {
            enInvalid = 0,
            enGeneralAlignmentInterger = 1000,
            enGeneralCenterMarkSizeDistance,
            enGeneralColor,
            enGeneralLineStyle,
            enGeneralWeight,
            enGeneralDimensionScale,
            enGeneralDimStyleDescriptionWchar,
            enGeneralDimStyleNameWchar,
            enGeneralFont,
            enGeneralIgnoreLayerSymbologyBool,
            enGeneralOverrideColorBool,
            enGeneralOverrideLineStyleBool,
            enGeneralOverrideWeightBool,
            enGeneralRadialModeInterger,
            enGeneralRelativeDimLineBool,
            enGeneralShowCenterMarkTemplateFlag,
            enGeneralStackedTemplateFlag,
            enGeneralStackOffsetDistance,
            enGeneralFitOptionInterger,
            enGeneralSuppressUnfitArrowBool,
            enGeneralPushTextRightBool,
            enGeneralTightFitTextAboveBool,
            enGeneralUseMinLeaderBool,
            enGeneralFitInclinedTextBoxBool,
            enGeneralFrozenInSharedBlockBool,
            enGeneralExtendDimLineUnderTextBool,
            enGeneralLineStyleScaleDouble,
            enDimTypeInterger,
            enBallAndChainAlignmentInterger = 2000,
            enBallAndChainArrowInterger,
            enBallAndChainTypeInterger,
            enBallAndChainIsActiveBool,
            enBallAndChainShowTextLeaderBool,
            enBallAndChainNoDockOnDimLineBool,
            enBallAndChainElbowLengthDouble,
            enMLeaderElbowLengthDouble,
            enBallAndChainUseElbowLengthBool,
            enBallAndChainModeInterger,
            enExtensionLineColor = 3000,
            enExtensionLineExtendDouble,
            enExtensionLineJoinBool,
            enExtensionLineLeftTemplateFlag,
            enExtensionLineLineStyle,
            enExtensionLineOffsetDouble,
            enExtensionLineOverrideColorBool,
            enExtensionLineOverrideLineStyleBool,
            enExtensionLineOverrideWeightBool,
            enExtensionLineRightTemplateFlag,
            enExtensionLineShowAnyBool,
            enExtensionLineWeight,
            enExtensionLineAngleChordAlignTemplateFlag,
            enMLeaderFrameTypeInterger = 4000,
            enMLeaderJustificationInterger,
            enMLeaderShowLeaderBool,
            enMLeaderVerticalJustificationInterger,
            enMLeaderLeaderTypeBool,
            enMLeaderTextRotationInterger,
            enMLeaderHorModelLinkInterger,
            enMLeaderVerLeftModelLinkInterger,
            enMLeaderVerRightModelLinkInterger,
            enMLeaderLeftMarginDouble,
            enMLeaderLowerMarginDouble,
            enMLeaderScaleFrameBool,
            enMLeaderFrameScaleDouble,
            enMLeaderBlockNameWchar,//内容块名称
            enMLeaderBlockConTypeBool,//内容块链接样式,是否插入点,否为中心点
            enMLeaderBlockByLineAngleDouble,//内容块角度
            enMLeaderBlockColor,//内容块颜色
            enMLeaderBlockScaleDouble,//内容块比例
            enMLeaderHasBlockBool,//是否有内容块
            enMLeaderLineMaxCount,//引线最大段数量
            enMLeaderDefaultName,//默认文字
            enMLeaderCustomAngleBool,//是否自定义文字角度
            enMLeaderNoteAngleDouble,//文字角度
            enMLeaderConTextBool,//文字链接方式，是否水平连接true:水平连接；false：垂直连接
            enMLeaderUpConTextWithLineBool,//文字垂直链接方式，是否有上划线
            enMLeaderDownConTextWithLineBool,//文字垂直链接方式，是否有下划线
            enMLeaderLinkToTextBool,//引线是否链接到文字
            enMLeaderHasDimensionLine,//是否有引线
            enMLeaderHasNote,//是否有内容
            enMLeaderBlockByLineBool ,//内容块是否随引线

            enPlacementCompatibleV3Bool = 5000,
            enPlacementLayer,
            enPlacementOverrideLayerBool,
            enPlacementTextPositionInterger,
            enPlacementUseReferenceScaleBool,
            enPlacementUseStyleAnnotationScaleBool,
            enPlacementAnnotationScale,
            enSymbolDiameterChar = 6000,
            enSymbolDiameterFont,
            enSymbolDiameterTypeInterger,
            enSymbolLowerPrefixChar,
            enSymbolLowerSuffixChar,
            enSymbolMainPrefixChar,
            enSymbolMainSuffixChar,
            enSymbolPlusMinusChar,
            enSymbolPlusMinusTypeInterger,
            enSymbolPrefixTemplateFlag,
            enSymbolPrefixCellNameWchar,
            enSymbolPrefixChar,
            enSymbolPrefixFont,
            enSymbolPrefixTypeInterger,
            enSymbolSuffixTemplateFlag,
            enSymbolSuffixCellNameWchar,
            enSymbolSuffixChar,
            enSymbolSuffixFont,
            enSymbolSuffixTypeInterger,
            enSymbolTolPrefixChar,
            enSymbolTolSuffixChar,
            enSymbolUpperPrefixChar,
            enSymbolUpperSuffixChar,
            enArrowBlockNameWchar = 7000,
            enArrowChar,
            enArrowFont,
            enArrowTypeInterger,
            enArrowColor,
            enArrowDotBlockNameWchar,
            enArrowDotChar,
            enArrowDotFont,
            enArrowDotTypeInterger,
            enArrowFirstTemplateFlag,
            enArrowHeightDouble,
            enArrowJointTemplateFlag,
            enArrowLeftTemplateFlag,
            enArrowLineStyle,
            enArrowMinLeaderDouble,
            enArrowModeInterger,
            enArrowNoLineThruArrowBool,
            enArrowNoLineThruDotBool,
            enArrowNoLineThruOriginBool,
            enArrowNoLineThruStrokeBool,
            enArrowOriginBlockNameWchar,
            enArrowOriginChar,
            enArrowOriginFont,
            enArrowOriginTypeInterger,
            enArrowOverrideColorBool,
            enArrowOverrideLineStyleBool,
            enArrowOverrideWeightBool,
            enArrowRightTemplateFlag,
            enArrowheadInterger,
            enArrowStrokeBlockNameWchar,
            enArrowStrokeChar,
            enArrowStrokeFont,
            enArrowStrokeTypeInterger,
            enArrowWeight,
            enArrowWidthDouble,
            enArrowNoteInterger,
            enArrowNoteTypeInterger,
            enArrowNoteBlockNameWchar,
            enArrowNoteChar,
            enArrowNoteFont,
            enArrowUniformBlockScaleBool,
            enArrowDimLineThruArrowBool,
            enArrowDimLineThruDotBool,
            enArrowDimLineThruOriginBool,
            enArrowDimLineThruStrokeBool,
            enArrorDimLineThruExtndLength,
            enArrowStrokeAngleDouble,
            enArrowStrokeBlockByLineBool,
            enArrowStrokeBlockTypeBool,
            enTextArcLengthSymbolTemplateFlag = 8000,
            enTextAutoLiftBool,
            enTextBoxBool,
            enTextCapsuleBool,
            enTextColor,
            enTextDecimalCommaBool,
            enTextEmbedBool,
            enTextFontBool,
            enTextHeightDistance,
            enTextHorizontalBool,
            enTextHorizontalMarginDouble,
            enTextJustificationInterger,
            enTextLeadingZeroBool,
            enTextNoFitVerticalTemplateFlag,
            enTextOmitLeadingDelimiterBool,
            enTextOverrideColorBool,
            enTextOverrideHeightBool,
            enTextOverrideWeightBool,
            enTextOverrideWidthBool,
            enTextSecLeadingZeroBool,
            enTextShowSecondaryBool,
            enTextUnderlineBool,
            enTextVerticalTemplateFlag,
            enTextVerticalMarginDouble,
            enTextWeight,
            enTextWidthDistance,
            enTextTextStyle,
            enTextTextStyleIdInterger,
            enTextStackedFractionAlignmentInterger,
            enTextStackedFractionsBool,
            enTextStackedFractionTypeInterger,
            enTextStackedFractionScaleDouble,
            enTextOverrideStackedFractionsBool,
            enTextOverrideUnderlineBool,
            enTextLocationInterger,
            enTextVerticalOptsTemplateFlag,
            enTextFrameTypeInterger,
            enTextInlineTextLiftDouble,
            enTextSuperscriptModeInterger,
            enToleranceLowerValueDistance = 9000,
            enToleranceModeBool,
            enToleranceShowBool,
            enToleranceStackEqualBool,
            enToleranceTextHorizontalMarginDouble,
            enToleranceTextScaleDouble,
            enToleranceTextVerticalMarginDouble,
            enToleranceTextVerticalSeparationDouble,
            enToleranceUpperValueDistance,
            enToleranceAccuracy,
            enToleranceSecAccuracy,
            enToleranceShowSignForZeroBool,
            enValueAccuracy = 10000,
            enValueAltAccuracy,
            enValueValueAltIsActiveBool,
            enValueAltSecAccuracy,
            enValueAltSecIsActiveBool,
            enValueAltSecShowDelimiterBool,
            enValueAltSecShowMasterUnitBool,
            enValueAltSecShowSubUnitBool,
            enValueAltSecShowUnitLabelBool,
            enValueAltSecShowWhenThresholdEqualBool,
            enValueAltSecShowWhenThresholdLessBool,
            enValueAltSecShowZeroMasterUnitBool,
            enValueAltSecThresholdDistance,
            enValueAltShowDelimiterBool,
            enValueAltShowMasterUnitBool,
            enValueAltShowSubUnitBool,
            enValueAltShowUnitLabelBool,
            enValueAltShowWhenThresholdEqualBool,
            enValueAltShowWhenThresholdLessBool,
            enValueAltShowZeroMasterUnitBool,
            enValueAltThresholdDistance,
            enValueAngleFormatInterger,
            enValueAngleLeadingZeroBool = 10023,
            enValueAngleMeasureBool,
            enValueAnglePrecisionInterger,
            enValueAngleTrailingZerosBool,
            enValueRoundLSDBool,
            enValueSecAccuracy,
            enValueSecShowDelimiterBool,
            enValueSecShowMasterUnitBool,
            enValueSecShowSubUnitBool,
            enValueSecShowTrailingZerosBool,
            enValueSecShowUnitLabelBool,
            enValueSecShowZeroMasterUnitBool,
            enValueShowDelimiterBool,
            enValueShowMasterUnitBool,
            enValueShowSubUnitBool,
            enValueShowTrailingZerosBool,
            enValueShowUnitLabelBool,
            enValueShowZeroMasterUnitBool,
            enValueNoReduceFractionBool,
            enValueNoReduceAltFractionBool,
            enValueNoReduceTolFractionBool,
            enValueSuperscriptLSDBool,
            enValueThousandsSeparatorBool,
            enValueThousandsSpaceBool,
            enValueUnit,
            enValueUnitLabelMasterWchar,
            enValueUnitLabelSecMasterWchar,
            enValueUnitLabelSecSubWchar,
            enValueUnitLabelSubWchar,
            enValueUnitSec,
            enValueUseWorkingUnitsBool,
            enValueOrdDecrementReverseBool,
            enValueOrdUseDatumValueBool,
            enValueOrdDatumValueDistance,
            enValueLabelLineSuppressAngleBool,
            enValueLabelLineSuppressLengthBool,
            enValueLabelLineInvertLabelsBool,
            enValueNoReduceSecFractionBool,
            enValueNoReduceAltSecFractionBool,
            enValueNoReduceTolSecFractionBool,
            enValueLabelLineAdjacentLabelsBool,
            enValueOrdFreeLocationBool,
            enValueFormatInterger,
            enValueAltFormatInterger,
            enValueSecFormatInterger,
            enValueAltSecFormatInterger,
            enValueAltThresholdComparisonInterger,
            enValueAltSecThresholdComparisonInterger,
            enValueThousandsOptsInterger,
            enValueUnitMasterOneUnit,
            enValueUnitSubOneUnit,
            enValueSecUnitMasterOneUnit,
            enValueSecUnitSubOneUnit,
            enValueLabelLineFormatInterger,
            enValueShowZeroSubUnitBool,
            enValueAltShowZeroSubUnitBool,
            enValueSecShowZeroSubUnitBool,
            enValueAltSecShowZeroSubUnitBool,
            enValueDMSPrecisionModeInterger,
            enValueRoundOffDouble,
            enValueSecRoundOffDouble,
            enValueSpaceAfterNonStackedFractionBool,
            enGeneralShowCenterMarkLeftTemplateFlag = 10085,
            enGeneralShowCenterMarkRightTemplateFlag,
            enGeneralShowCenterMarkTopTemplateFlag,
            enGeneralShowCenterMarkBottomTemplateFlag,
        };

        enum class DimStyleCategoryProp : int
        {
            enRoot = -10000,

            enGeneral = -10100,
            enPlacement = -10101,
            enBallAndChain = -10102,
            enTolerance = -10103,

            enValue = -10200,
            enAngle = -10201,
            enMetric = -10202,
            enFractions = -10203,
            enPrimary = -10204,
            enPrimaryAlt = -10205,
            enSecondary = -10206,
            enSecondaryAlt = -10207,
            enDINDimensioning = -10208,

            enGraphics = -10300,
            enDimLines = -10301,
            enExtLines = -10302,
            enTerminators = -10303,
            enFitOptions = -10304,

            enText = -10400,
            enFormat = -10401,
            enStyle = -10402,

            enNotes = -10500,

            enSymbols = -10600,
            enPrefix = -10601,
            enSuffix = -10602,
            enDiameter = -10603,
            enPlusMinus = -10604,
            enArrowTerm = -10605,
            enStrokeTerm = -10606,
            enOriginTerm = -10607,
            enDotTerm = -10608,
            enNoteTerm = -10609,

            enTools = -10700,
            enLinearTool = -10701,
            enAngleTool = -10702,
            enArcSizeTool = -10703,
            enAngleLocTool = -10704,
            enRadialTool = -10705,
            enOrdinateTool = -10706,
        };

        enum class DimensionPartType : byte
        {
            enInherit = 0,
            enExtLeft = 1,
            enExtRight = 2,
            enTextUpper = 3,
            enTextLower = 4,
            enTextSingle = 5,
            enArrowLeft = 6,
            enArrowRight = 7,
            enDimLine = 8,
            enCenter = 9,
            enTextSymbols = 10,
            enChain = 11,
        };

        enum class DimensionPartSubType : byte
        {
            enNone = 0x00,
            enTolUpper = 0x01,
            enTolLower = 0x02,
            enTolSingle = 0x03,
            enLimitUpper = 0x04,
            enLimitLower = 0x05,
            enLimitSingle = 0x06,
            enPrefix = 0x07,
            enSuffix = 0x08,
            enArrowSymbol = 0x09,
            enLeader = 0x0A,
        };

        enum class DimensionTextPartType : byte
        {
            enPrimary = (byte)DimensionPartType::enTextUpper,
            enSecondary = (byte)DimensionPartType::enTextLower,
        };

        enum class DimensionTextPartSubType : byte
        {
            enMain = (byte)DimensionPartSubType::enNone,
            enTolerancePlus = (byte)DimensionPartSubType::enTolUpper,
            enToleranceMinus = (byte)DimensionPartSubType::enTolLower,
            enLimitUpper = (byte)DimensionPartSubType::enLimitUpper,
            enLimitLower = (byte)DimensionPartSubType::enLimitLower,
        };

        enum class DimStyleValueListProp : int
        {
            enInvalidStrId = 0,
            enBallAndChainAlignmentStrId = -100,
            enBallAndChainTypeStrId = -101,
            enGeneralAlignment = -102,
            enGeneralRadialModeStrId = -103,
            enMLeaderFrameTypeStrId = -104,
            enMLeaderJustificationStrId = -105,
            enMLeaderVerticalJustificationStrId = -106,
            enMLeaderTextRotationStrId = -107,
            enMLeaderHorModelLinkStrId = -108,
            enMLeaderVerModelLinkStrId = -109,
            enSymbolStandardStrId = -110,
            enSymbolCustomTypeStrId = -111,
            enSymbolPreSufTypeStrId = -112,
            enSymbolArrowTypeStrId = -113,
            enArrowModeStrId = -114,
            enArrowheadStrId = -115,
            enTextJustificationStrId = -116,
            enValueAngleFormatStrId = -117,
            enValueAnglePrecisionStrId = -118,
            enTextStackedFractionAlignmentStrId = -119,
            enTextStackedFractionTypeStrId = -120,
            enPlacementTextPositionStrId = -121,
            enTextLocationStrId = -122,
            enAccuracyStrId = -123,
            enArrowTypeLeftStrId = -124,
            enArrowTypeRightStrId = -125,
            enArrowTypeFirstStrId = -126,
            enArrowTypeJointStrId = -127,
            enArrowTypeNoteStrId = -128,
            enRadialToolLeaderStrId = -129,
            enValueFormatStrId = -130,
            enValueComparisonStrId = -131,
            enTextVerticalStrId = -132,
            enValueThousandsOptsStrId = -133,
            enOnOffStrId = -134,
            enTextHorizontalStrId = -135,
            enValueAngleMeasureStrid = -136,
            enTextFrameTypeStrId = -137,
            enToleranceModeStrId = -138,
            enMLeaderTypeStrId = -139,
            enValueLabelLineFormatStrId = -140,
            enIndex = -141,
            enTextSuperScriptModeStrId = -142,
            enFitOptionStrId = -143,
            enBallAndChainModeStrId = -144,
            enFitInclinedTextBoxStrId = -145,
            enDimStyleTypeId = -146,
        };

        enum P3DTextStyleProperty
        {
            TextStyle_InvalidProperty = 0,
            TextStyle_Color = 1,
            TextStyle_ColorFlag = 2,
            TextStyle_Font = 3,
            TextStyle_ShxBigFont = 4,
            TextStyle_Width = 5,
            TextStyle_Height = 6,
            TextStyle_Slant = 7,
            TextStyle_Underline = 8,
            TextStyle_Overline = 9,
            TextStyle_Italics = 10,
            TextStyle_Bold = 11,
            TextStyle_Superscript = 12,
            TextStyle_Subscript = 13,

            TextStyle_Backgroundstyleflag = 14,
            TextStyle_Backgroundstyle = 15,
            TextStyle_Backgroundweight = 16,
            TextStyle_Backgroundcolor = 17,
            TextStyle_Backgroundfillcolor = 18,
            TextStyle_Backgroundborder = 19,

            TextStyle_Underlinestyle = 20,
            TextStyle_Underlineweight = 21,
            TextStyle_Underlinecolor = 22,
            TextStyle_Underlinestyleflag = 23,
            TextStyle_UnderlineOffset = 24,

            TextStyle_Overlinestyle = 25,
            TextStyle_Overlineweight = 26,
            TextStyle_Overlinecolor = 27,
            TextStyle_Overlinestyleflag = 28,
            TextStyle_OverlineOffset = 29,

            TextStyle_LineSpacing = 30,
            TextStyle_FixedSpacing = 31,
            TextStyle_LineOffset = 32,
            TextStyle_InterCharSpacing = 33,
            TextStyle_LineSpacingType = 34,
            TextStyle_AcadInterCharSpacing = 35,
            TextStyle_Justification = 36,
            TextStyle_NodeJustification = 37,
            TextStyle_FullJustification = 38,
            TextStyle_LineLength = 39,
            TextStyle_Direction = 40,
            TextStyle_Backwards = 41,
            TextStyle_Upsidedown = 42,
            TextStyle_Fractions = 43,
            TextStyle_WidthFactor = 44,
            TextStyle_Vertical = 45,
            TextStyle_AcadShapeFile = 46,
            TextStyle_RightToLeft = 47,

			TextStyle_BoxedText         = 48,
			TextStyle_BoxedLineColor    = 49,
			TextStyle_BoxedLineStyle    = 50,
			TextStyle_BoxedLineWeight   = 51,
			TextStyle_BoxedTextGap      = 52,

        };

        /**
        @brief 属性文字标记.
        */
		enum class P3DPropertyTextType
		{
			enError = -1,               /**< 未知错误类型*/
			enNormalText = 0,           /**< 普通文字实体*/
			enPropertyTemplate,         /**< 属性文字模板实体*/
			enPropertyInstance          /**< 属性文字实例实体*/
		};

        /**
        @brief Entity的类型
        */
		enum class P3DEntityType
		{
			enError = -1,               /**< 未知错误类型*/
			enNormal = 0,               /**< 单一实体类型*/
			enSharedBlockDef,           /**< 共享块定义实体类型*/
			enSharedBlock,              /**< 共享块实例实体类型*/
			enIsolateBlock,             /**< 独立的块实例实体类型*/
            enSingleLineText,           /**< 单行文字实体类型*/
            enMultiLineText             /**< 多行文字实体类型*/

		};

        /**
        @brief  文字边框设置标记
        @date 创建日期:2024-11-27
        */
        enum class P3DTextBorderFlag : UInt16    // 6 bits
        {
            enNone = 0,                                 /** 不绘制*/

			enOverall,                         /** 画整体一个边框*/
			enFirstLine,                       /** 首行画边框*/
			enLastLine,                        /** 尾行画边框*/
			enEveryOne,                        /** 每行都画边框*/
			enOnlySpecified,                   /** 仅指定的行(可以是多个)画边框,行号另外的参数给出.*/
			enOnlySpecifiedNot,                /**仅指定的行(可以是多个)不画边框，行号另外给出.*/
			enSpecifiedMultiLines              /**仅指定的连续的行(可以是多个)画边框，行号另外给出.*/
        };

#if defined (__cplusplus)
        inline P3DTextBorderFlag operator& (P3DTextBorderFlag a, P3DTextBorderFlag b) { return static_cast<P3DTextBorderFlag>(static_cast<std::underlying_type<P3DTextBorderFlag>::type>(a) & static_cast<std::underlying_type<P3DTextBorderFlag>::type>(b)); }
#endif

    }; // end platform namespace
}; // end p3d namespace

#endif
