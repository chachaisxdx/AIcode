/**
@brief 基础定义头文件
@details 详细描述
@file    BPDefine.h
@author  北京构力科技有限公司
@date    2021-08-06
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/

#ifndef P3D_P3DDefine_H
#define P3D_P3DDefine_H


#define BIMBase_PUBLIC_BRANCH
#define BIMBASE_EXPORT_INTERFACE        __declspec(dllexport)
#define BIMBASE_IMPORT_INTERFACE        __declspec(dllimport)

#define BIMBASE_TYPEDEFS(_name_) \
    namespace BIMBase { \
        class _name_; \
        typedef _name_*          _name_##P;  \
        typedef _name_&          _name_##R;  \
        typedef _name_ const*    _name_##CP; \
        typedef _name_ const&    _name_##CR; \
        }


// BIMBase Platform type redefine
#if !defined (BIMBASE_PLATFORM_TYPE)
typedef int8_t              Int8;
typedef uint8_t             UInt8;
typedef int16_t             Int16;
typedef uint16_t            UInt16;
typedef int32_t             Int32;
typedef uint32_t            UInt32;
typedef int64_t             Int64;
typedef uint64_t            UInt64;

typedef unsigned short      UShort;
typedef unsigned long       ULong;
typedef short               Short;
typedef unsigned int        UInt;
typedef unsigned char       UChar;
typedef unsigned char       Byte;
typedef unsigned char       byte;
typedef long                Long32;
typedef unsigned long       ULong32;


#endif // BIMBASE_PLATFORM_TYPE


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace BIMBase
{
    class BPNonCopyableClass
    {
    private:
        BPNonCopyableClass(BPNonCopyableClass const&);
        BPNonCopyableClass& operator= (BPNonCopyableClass const&);

    protected:
        BPNonCopyableClass() {}
        virtual ~BPNonCopyableClass() {}
    };
}



#if defined (__BIMBASEAPI_PROJECT__)
#define BIMBASEAPI_EXPORT     BIMBASE_EXPORT_INTERFACE
#else
#define BIMBASEAPI_EXPORT     BIMBASE_IMPORT_INTERFACE
#endif

#ifndef P3DAssert
#ifdef NDEBUG
#define P3DAssert(_Expression)     ((void)0)
#else
#define P3DAssert(_Expression)  assert(_Expression)
#endif
#endif


#define DEFINE_P_SUPER(ParentClassName) private: typedef ParentClassName P_Super; public:


namespace BIMBase {
    const UInt32      DEFAULT_LAYER_ID = 64;
    const Int32       NULL_LAYER_ID = 0xffffffff;
    const Int32       INVALID_MODEL_ID = -2;
    const Int64       INVALID_CLASS_ID = -1LL;

    typedef UInt64                PEntityId;

    typedef Int32   PModelLinkId;
    typedef const PModelLinkId& PModelLinkIdCR;


    using PClassId = Int64;
    using PClassIdR = Int64&;
    using PClassIdCR = Int64 const&;

    /**
    @brief  图层在工程文件唯一ID
    @details  DEFAULT_LAYER_ID表示默认图层
    @date 创建日期:2021-08-19
    */
    class PLayerId
    {
    public:
        UInt32 m_id;
        PLayerId() {
            m_id = DEFAULT_LAYER_ID;
            return;
        }

        PLayerId(UInt32 u) : m_id((UInt32)u) {
            return;
        }

        bool isValid() const {
            if (m_id == NULL_LAYER_ID)
            {
                return false;
            }
            return true;
        }

        PLayerId& operator=(UInt32 rhs) {
            m_id = (UInt32)rhs;
            return *this;
        }

        //! Compare two UInt32 for equality
        bool operator==(PLayerId const& rhs) const {
            return rhs.m_id == m_id;
        }

        //! Compare two UInt32 for inequality
        bool operator!=(PLayerId const& rhs) const {
            return !(*this == rhs);
        }

        //! Compare two 
        bool operator<(PLayerId const& rhs) const {
            return m_id < rhs.m_id;
        }

        bool operator<(UInt32 const& rhs) const {
            return m_id < rhs;
        }

        bool operator<=(PLayerId const& rhs) const {
            return m_id <= rhs.m_id;
        }

        bool operator<=(UInt32 const& rhs) const {
            return m_id <= rhs;
        }

        bool operator>(PLayerId const& rhs) const {
            return m_id > rhs.m_id;
        }

        bool operator>(UInt32 const& rhs) const {
            return m_id > rhs;
        }

        bool operator>=(PLayerId const& rhs) const {
            return m_id >= rhs.m_id;
        }

        bool operator>=(UInt32 const& rhs) const {
            return m_id >= rhs;
        }

        UInt32 getValue() const {
            return m_id;
        }
    };

    /**
    @brief  特定的工程文件内模型空间的唯一ID
    @details  INVALID_MODEL_ID表示无效值
    @date 创建日期:2021-08-19
    */
    class PModelId
    {
    public:
        Int32 m_id;

        /**
        @brief 构造函数,初始化为无效值.
        */
        PModelId() : m_id(INVALID_MODEL_ID) {}

        /**
        @brief 单参构造函数
        @param[in] idVal:  模型空间ID值
        */
        PModelId(Int32 idVal) : m_id(idVal) {}

        /**
        @brief 判断ID值是否有效
        */
        bool isValid() const {
            if (m_id == INVALID_MODEL_ID || m_id == -2)
            {
                return false;
            }
            return true;
        }

        /**
        @brief 赋值函数
        */
        PModelId& operator=(Int32 rhs) {
            m_id = rhs;
            return *this;
        }

        /**
        @brief 判断是否相等
        */
        bool operator==(PModelId const& rhs) const {
            return rhs.m_id == m_id;
        }

        /**
        @brief 判断是否不相等
        */
        bool operator!=(PModelId const& rhs) const {
            return !(*this == rhs);
        }

        /**
        @brief 判断是否小于
        */
        bool operator<(PModelId const& rhs) const {
            return m_id < rhs.m_id;
        }

        /**
        @brief 判断是否小于
        */
        bool operator<(Int32 const& rhs) const {
            return m_id < rhs;
        }

        /**
        @brief 判断是否小于等于
        */
        bool operator<=(PModelId const& rhs) const {
            return m_id <= rhs.m_id;
        }

        /**
        @brief 判断是否小于等于
        */
        bool operator<=(Int32 const& rhs) const {
            return m_id <= rhs;
        }

        /**
        @brief 判断是否大于
        */
        bool operator>(PModelId const& rhs) const {
            return m_id > rhs.m_id;
        }

        /**
        @brief 判断是否大于
        */
        bool operator>(Int32 const& rhs) const {
            return m_id > rhs;
        }

        /**
        @brief 判断是否大于等于
        */
        bool operator>=(PModelId const& rhs) const {
            return m_id >= rhs.m_id;
        }

        /**
        @brief 判断是否大于等于
        */
        bool operator>=(Int32 const& rhs) const {
            return m_id >= rhs;
        }

        /**
        @brief 获取整型值
        */
        Int32 getValue() const {
            return m_id;
        }
    };

    /**
    @brief  特定的工程文件内图形实体的唯一ID
    @date 创建日期:2021-08-19
    */
    class BPEntityId
    {
    public:
        PModelId    m_modelId;
        PEntityId    m_entityId;

    public:

        /**
        @brief 无参构造函数,默认为无效值.
        */
        BPEntityId() : m_modelId(INVALID_MODEL_ID), m_entityId(0) {};

        // ____<pkpm_inner_begin>____
        BPEntityId(PModelId const& modelId, UInt64 const& entityId) :m_modelId(modelId), m_entityId(entityId) {}
        // ____<pkpm_inner_end>____

        /**
        @brief 拷贝构造函数
        */
        BPEntityId(BPEntityId const& entityId) :m_modelId(entityId.m_modelId), m_entityId(entityId.m_entityId) {}

        /**
        @brief 参数为长整型的构造函数
        @param[in] entityId64: 图形实体ID值
        */
        explicit BPEntityId(Int64 const& entityId64) {
            setValue(entityId64);
        }

        /**
        @brief 赋值函数
        @param[in] entityId64: 图形实体ID
        */
        BPEntityId& operator = (BPEntityId const& entityId) {
            this->m_modelId = entityId.m_modelId;
            this->m_entityId = entityId.m_entityId;
            return *this;
        }

        /**
        @brief 判断是否小于
        */
        bool operator < (BPEntityId const& other) const {
            if (m_modelId != other.m_modelId)
            {
                return m_modelId < other.m_modelId;
            }

            return m_entityId < other.m_entityId;
        }

        /**
        @brief 判断是否有效
        */
        bool isValid() const {
            return m_modelId > INVALID_MODEL_ID&& m_entityId >= 0;
        }

        /**
        @brief 使当前ID值无效
        */
        void invalidate()
        {
            m_modelId = INVALID_MODEL_ID;
            m_entityId = 0;
            return;
        }

        /**
        @brief 判断是否等于
        */
        bool operator==(const BPEntityId& rhs) const {
            return m_entityId == rhs.m_entityId && m_modelId == rhs.m_modelId;
        }

        /**
        @brief 判断是否不等于
        */
        bool operator!=(const BPEntityId& rhs) const {
            return !(*this == rhs);
        }

        /**
        @brief 获取长整型值
        */
        Int64 getValue() const
        {
            if (0 != (m_entityId & 0xFFFFFFFF00000000))
            {
                return -1;
            }
            Int64 instanceId64_t = 0;
            instanceId64_t = m_modelId.getValue();
            instanceId64_t = (instanceId64_t << 32) | (m_entityId & 0x00000000FFFFFFFF);
            return instanceId64_t;
        }

        /**
        @brief 设置长整型值
        */
        bool setValue(Int64 const& entityId64_t)
        {
            if (-1 == entityId64_t)
            {
                return false;
            }
            m_modelId = ((entityId64_t >> 32) & 0x00000000FFFFFFFF);
            m_entityId = (entityId64_t & 0x00000000FFFFFFFF);
            return isValid();
        }
        
    };


    // ____<pkpm_inner_begin>____
    class BPStringUtil
    {
    public:
        static p3d::PString toPString(const char* utf8str)
        {
            p3d::PString outWStr;
            p3d::P3DStringHelper::utf8ToWChar(outWStr, utf8str);
            return outWStr;
        }

        static p3d::Utf8String toUtf8String(const wchar_t* wStr)
        {
            p3d::Utf8String outWStr;
            p3d::P3DStringHelper::wCharToUtf8(outWStr, wStr);
            return outWStr;
        }
    };
    // ____<pkpm_inner_end>____

    /**
    @brief  颜色RGB值
    @date 创建日期:2021-08-19
    */
    struct BPRgbColor
    {
        Byte    red;
        Byte    green;
        Byte    blue;
    };

    /**
    @brief  颜色RGBA值
    @date 创建日期:2021-08-19
    */
    struct BPRgbaColor
    {
        Byte    red;
        Byte    green;
        Byte    blue;
        Byte    alpha;
    };

    /**
    @brief  颜色定义
    @date 创建日期:2021-08-19
    */
    union BPColorDef
    {
        BPRgbColor      m_rgb;
        BPRgbaColor     m_rgba;
        UInt32          m_int;

        void SetColors(Byte r, Byte g, Byte b, Byte a) {
            m_rgba.red = r; m_rgba.green = g; m_rgba.blue = b; m_rgba.alpha = a;
        }

        operator UInt32() const {
            return m_int;
        }

        BPColorDef() {
            m_int = 0;
        }

        BPColorDef(BPRgbColor rgb) {
            m_int = 0; m_rgb = rgb;
        }

        BPColorDef(UInt32 intval) {
            m_int = intval;
        }

        BPColorDef(Byte red, Byte green, Byte blue) {
            SetColors(red, green, blue, 0);
        }

        BPColorDef(Byte red, Byte green, Byte blue, Byte alpha) {
            SetColors(red, green, blue, alpha);
        }
    };

	enum class BPEntityOperation
	{
		enUnknown = 0,      /**<未知*/
		enCopy,             /**<复制*/
	};

    enum class BPModelContentType
    {
        enPlan2D,
        enView3D,
        enDrawing,
    };

    enum class BPDrawMode : Int8
    {
        enNormal = 0,
        enErase = 1,
        enHilite = 2,
        enTempDraw = 3,
        enFlash = 11,
    };

    enum class BPDrawPurpose : Int8
    {
        enNotSpecified = 0,
        enUpdate = 1,
        enHilite = 5,
        enUnhilite = 6,
        enDynamics = 15,
        enFlash = 23,
        enCaptureGeometry = 26,
        enForceRedraw = 29,
        // ____<pkpm_inner_begin>____
        enUpdateDynamic = 2,
        enUpdateHealing = 3,
        enChangedPre = 9,
        enChangedPost = 10,
        enRestoredPre = 11,
        enRestoredPost = 12,
        enRangeCalculation = 20,
        enPlot = 21,
        enPick = 22,
        enTransientChanged = 25,
        enGenerateThumbnail = 27,
        enFenceAccept = 30,
        enRegionFlood = 31,
        enFitView = 32,
        enGraphicsCreate = 34,
        enCaptureShadowList = 35,
        enExportVisibleEdges = 36,
        enInterferenceDetection = 37,
        enCutGraphicsCreate = 38,
        enModelFacet = 39,
        enMeasure = 40,
        enVisibilityCalculation = 41,
        enProxyHashExtraction = 42,
        enComputeModelRefRange = 43,
        enBPDbConvert = 44,
        // ____<pkpm_inner_end>____
    };

    enum class BPSnapStatus : Int16
    {
        eSuccess = ::p3d::P3DStatus::SUCCESS,
        eAborted = 1,
        eNoEntitys = 2,
        eDisabled = 100,
        eNoSnapPossible = 200,
        eNotSnappable = 300,
        eRefNotSnappable = 301,
        eFilteredByLevel = 400,
        eFilteredByUser = 500,
        eFilteredByApp = 600,
        eFilteredByAppQuietly = 700,
        eDoSnapByDefaultProcess = 800,
    };

    enum class BPPickGeomType
    {
        enUnKnown = -1,
        enNone = 0,
        enPoint = 1,
        enSegment = 1 << 1,
        enCurve = 1 << 2,
        enArc = 1 << 3,
        enSurface = 1 << 4,
        enAll = (enPoint | enSegment | enCurve | enArc | enSurface)
    };

    //错误码转换
    enum class BPLastErrorCode
    {
        enError = -1,
        enSuccess = 0,
        enP3DDataAlreadyExisted,
        enP3DDataAlreadyDeleted,                    // 已经删除
        enP3DDataNotFound,                          // 没有找到
        enP3DRelationshipDataAlreadyExisted,
        enP3DRelationshipDataAlreadyDeleted,
        enP3DRelationshipDataNotFound
    };

    enum BPValueType ENUM_UNDERLYING_TYPE(unsigned short)
    {
        PRIMITIVETYPE_Unknown = 0,

            PRIMITIVETYPE_Double = 0x101,
            PRIMITIVETYPE_Integer = 0x201,
            PRIMITIVETYPE_Boolean = 0x301,
            PRIMITIVETYPE_Long = 0x401,
            PRIMITIVETYPE_Point2D = 0x501,
            PRIMITIVETYPE_Point3D = 0x601,
            PRIMITIVETYPE_IGeometry = 0x701,
            PRIMITIVETYPE_String = 0x801,
            PRIMITIVETYPE_Binary = 0x901,
            PRIMITIVETYPE_DateTime = 0xa01,
			PRIMITIVETYPE_Json = 0xb01,
    };

    struct BPSymbology
    {
        Int32           style;  /**<0:实线, 1:点线, 2:短虚线, 3:虚线（比短虚线长）, 4:点画线（稀疏一点，线长一点）, 5:虚线，比2短虚线更短一点, 6:双点画线, 7:点画线（密集一点，线短一点） */
        UInt32          weight;
        UInt32          color;
    };

    enum class BPEntityDisplayPropertyModify
    {
        enUnknown = -1, /**< 未知*/
        enNone = 0,     /**< 显示属性无修改*/
        enSymbology = 1,    /**< 仅修改颜色/图层/线型/线宽/透明度*/
        enMaterial = 2,     /**< 仅修改材质*/
    };

    enum
    {
        COLOR_BYLAYER = 0xffffffff,
        COLOR_BYBLOCK = 0xfffffffe,
        STYLE_BYLAYER = 0x7fffffff,
        STYLE_BYBLOCK = 0x7ffffffe,
        WEIGHT_BYLAYER = 0xffffffff,
        WEIGHT_BYBLOCK = 0xfffffffe,
        LAYER_BYBLOCK = 64,
    };

    enum BPSelectionSetAction
    {
        SELECT_NOTHING = 0,
        SELECT_STRETCH = 1,
        SELECT_WINDOW = 2,
        SELECT_DRAG = 3,
        SELECT_DRAG_NEW = 4,
        SELECT_SS_EMPTY = 6,
        SELECT_SS_CHANGED = 8,
        SELECT_DOUBLECLICK_HANDLE = 10,
        SELECT_DOUBLECLICK = 11,
    };

    enum class BPSelectionMode
    {
        enNew = 0,
        enAdd = 1,
        enSubtract = 2,
        enInverse = 3,
        enClear = 4,
        enAll = 5
    };

    enum class BPStackedFractionSection
    {
        enNone = 0,
        enNumerator = 1,
        enDenominator = 2
    };

    enum class BPStackedFractionType
    {
        enNone = 0,
        enNoBar = 1,
        enDiagonalBar = 2,
        enHorizontalBar = 3
    }; // BPStackedFractionType

    enum class BPCompareOp    // 条件查询选项
    {
        enEQ,
        enNE,
        enGT,
        enGE,
        enLT,
        enLE,
        enIS_IN,
        enNOT_IN,
    };

    enum class BPDimensionType
    {
        None = 0,
        SizeArrow = 1,
        SizeStroke = 2,
        LocateSingle = 3,
        LocateStacked = 4,
        AngleSize = 5,
        ArcSize = 6,
        AngleLocation = 7,
        ArcLocation = 8,
        AngleLines = 9,
        AngleAxis = 10,
        Radius = 11,
        Diameter = 12,
        DiameterParallel = 13,
        DiameterPerpendicular = 14,
        CustomLinear = 15,
        Ordinate = 16,
        RadiusExtended = 17,
        DiameterExtended = 18,
        Center = 19,

        AngleAxisX = 50,
        AngleAxisY = 51,
        LabelLine = 52,
        Note = 53,

        MaxThatHasTemplate = 19,
        MaxTemplate        = 24,
        Max = 53,
    };

    enum class BPAngleFormatVals
    {
        enNone = -2,
        enActive = -1,
        enDegrees = 0,
        enDegMinSec = 1,
        enCentesimal = 2,
        enRadians = 3,
        enDegMin = 4,
        enSurveyor = 5,
    };

	enum class PropertysPurpose
	{
		enProperty = 0,
		enExtension = 1
	};

    //dimstyle
	const byte c_dimPrecisionInterger = 0x00;
	const byte c_dimFractionHalf = 0x01;
	const byte c_dimFractionOneFourth = 0x02;
	const byte c_dimFractionOneEighth = 0x04;
	const byte c_dimFractionOneSixteenth = 0x08;
	const byte c_dimFractionOneThirtySecond = 0x10;
	const byte c_dimFractionOneSixtyFourth = 0x20;

	const byte c_dimPrecisionAlternate = 0x40;

	const byte  c_scientific1Place = (c_dimPrecisionAlternate | 0x00);
	const byte  c_scientific2Places = (c_dimPrecisionAlternate | 0x01);
	const byte  c_scientific3Places = (c_dimPrecisionAlternate | 0x02);
	const byte  c_scientific4Places = (c_dimPrecisionAlternate | 0x03);
	const byte  c_scientific5Places = (c_dimPrecisionAlternate | 0x04);
	const byte  c_scientific6Places = (c_dimPrecisionAlternate | 0x05);
	const byte  c_scientific7Places = (c_dimPrecisionAlternate | 0x06);
	const byte  c_scientific8Places = (c_dimPrecisionAlternate | 0x07);

	const byte c_decimal1Place = 0x80;
	const byte c_decimal2Places =  0x81;
	const byte c_decimal3Places = 0x82;
	const byte c_decimal4Places = 0x83;
	const byte c_decimal5Places = 0x84;
	const byte c_decimal6Places = 0x85;
	const byte c_decimal7Places = 0x86;
	const byte c_decimal8Places = 0x87;
    
    // 需要底层支持
    // 现在添加这几个发现是小数，而且位数越来越大
    // 底层并不支持整形
	//const byte c_decimal1PlaceInterger = 0xff;
	//const byte c_dimScientific1Interger = 0x89;

	enum class DimStyleValuePrecisionProp : byte
	{
		enWholeDecimalInterger = c_dimPrecisionInterger,
		en1Decimal = c_decimal1Place,
		en2Decimals = c_decimal2Places,
		en3Decimals = c_decimal3Places,
		en4Decimals = c_decimal4Places,
		en5Decimals = c_decimal5Places,
		en6Decimals = c_decimal6Places,
		en7Decimals = c_decimal7Places,
		en8Decimals = c_decimal8Places,
		//enWholeFractionInterger = c_dimPrecisionInterger,
		enHalf = c_dimFractionHalf,
		enQuarter = c_dimFractionOneFourth,
		enEighth = c_dimFractionOneEighth,
		enSixteenth = c_dimFractionOneSixteenth,
		enThirtySecond = c_dimFractionOneThirtySecond,
		enSixtyFourth = c_dimFractionOneSixtyFourth,
		//enWholeScientific1Interger = c_dimScientific1Interger,
		enScientific1Decimal = c_scientific1Place,
		enScientific2Decimals = c_scientific2Places,
		enScientific3Decimals = c_scientific3Places,
		enScientific4Decimals = c_scientific4Places,
		enScientific5Decimals = c_scientific5Places,
		enScientific6Decimals = c_scientific6Places,
		enScientific7Decimals = c_scientific7Places,
		enScientific8Decimals = c_scientific8Places,
	};


}


#define BASE_TYPE_DEF(_typename_) \
        typedef _typename_*          _typename_##P;  \
        typedef _typename_&          _typename_##R;  \
        typedef _typename_ const*    _typename_##CP; \
        typedef _typename_ const&    _typename_##CR; \


#define BIMBASE_TYPE_DEF(_typename_) \
        class  _typename_; \
        typedef _typename_*          _typename_##P;  \
        typedef _typename_&          _typename_##R;  \
        typedef _typename_ const*    _typename_##CP; \
        typedef _typename_ const&    _typename_##CR; \

#define BIMBASE_STRUCT_TYPE_DEF(_typename_) \
        namespace BIMBase{namespace Core \
    {\
        struct  _typename_; \
        typedef _typename_*          _typename_##P;  \
        typedef _typename_&          _typename_##R;  \
        typedef _typename_ const*    _typename_##CP; \
        typedef _typename_ const&    _typename_##CR; \
    }}

#define BASE_STRUCT_TYPE_DEF(_typename_) \
        namespace BIMBase\
    {\
        struct  _typename_; \
        typedef _typename_*          _typename_##P;  \
        typedef _typename_&          _typename_##R;  \
        typedef _typename_ const*    _typename_##CP; \
        typedef _typename_ const&    _typename_##CR; \
    }

#define BASE_CLASS_TYPE_DEF(_typename_) \
        namespace BIMBase\
    {\
        class  _typename_; \
        typedef _typename_*          _typename_##P;  \
        typedef _typename_&          _typename_##R;  \
        typedef _typename_ const*    _typename_##CP; \
        typedef _typename_ const&    _typename_##CR; \
    }


#define BIMBASE_ENUM_TYPE_DEF(_typename_) \
        enum  _typename_; \
        typedef _typename_*          _typename_##P;  \
        typedef _typename_&          _typename_##R;  \
        typedef _typename_ const*    _typename_##CP; \
        typedef _typename_ const&    _typename_##CR; \

#define ADD_BIMBASE_TYPEDEF_S1(_namespace_, _old_class_name_, _new_class_name) \
    namespace BIMBase{namespace Core \
    {\
    typedef class _namespace_ :: _old_class_name_*          _new_class_name##P, &_new_class_name##R;  \
    typedef class _namespace_ :: _old_class_name_ const*    _new_class_name##CP; \
    typedef class _namespace_ :: _old_class_name_ const&    _new_class_name##CR; \
    }}

#define BIMBASE_TYPE_DEFS(_classname_) \
    namespace BIMBase{namespace Core{ class _classname_;}} \
    ADD_BIMBASE_TYPEDEF_S1(::BIMBase::Core, _classname_, _classname_)

#define ADD_BIMBASE_PLATFORM_TYPEDEF_S1(_namespace_, _old_class_name_, _new_class_name) \
    namespace BIMBase \
    {\
    typedef class _namespace_ :: _old_class_name_*          _new_class_name##P, &_new_class_name##R;  \
    typedef class _namespace_ :: _old_class_name_ const*    _new_class_name##CP; \
    typedef class _namespace_ :: _old_class_name_ const&    _new_class_name##CR; \
    }

#define BIMBASE_PLATFORM_TYPE_DEFS(_classname_) \
    namespace BIMBase{ class _classname_;} \
    ADD_BIMBASE_PLATFORM_TYPEDEF_S1(BIMBase, _classname_, _classname_)

#define BIMBASE_PLATFORM_REF_COUNTED_PTR(_classname_) \
    namespace BIMBase{namespace Core{ class _classname_; }}    \
    namespace BIMBase{namespace Core{ typedef ::BIMBase::BPRefCountedPtr<::BIMBase::Core::_classname_> _classname_##Ptr; }}

#define BIMBASE_REF_COUNTED_PTR(_classname_) \
    namespace BIMBase{class _classname_; }    \
    namespace BIMBase{typedef ::BIMBase::BPRefCountedPtr<::BIMBase::_classname_> _classname_##Ptr; }


BASE_STRUCT_TYPE_DEF(BPSymbology)
BASE_CLASS_TYPE_DEF(PLayerId)
BIMBASE_TYPE_DEFS(BPViewLink)


#endif // P3D_P3DDefine_H