/**
@brief 拾取管理
@file    BPEntityLocateManager.h
@author  北京构力科技有限公司
@date    2021-08-06
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/
#pragma once


namespace BIMBase {
    namespace Core
    {
        typedef class BPPickData const* BPPickDataCP;

        /**
        @brief 拾取过滤状态码
        @details 只针对高亮和选择高亮
        */
        enum class BPLocateFilterStatus
        {
            enLocate_Reject = 0,//不拾取
            enLocate_Neutral = 1,//默认值
            enLocate_Accept = 2//拾取
        };

        typedef BPLocateFilterStatus(*LocateFilterFunc)(::p3d::PStringP reasonDesc, BPEntityCP entity, BPPickDataCP pickData);

        /**
        @brief 面拾取过滤方式
        @details
        */
        enum class BPLocateSurfacesOpt
        {
            enNever = 0,
            enByView = 1,
            enAlways = 2,
        };

        /**
        @brief 几何拾取参数
        @details
        */
		struct BPPickGeomParams
		{
			BPPickGeomParams() {
				m_bAptureOverride = false;
                m_dPickAperture = 0.0;
			}

            /**
            @brief 是否重写拾取靶区大小.如果为false则使用系统设置.
            */
			bool m_bAptureOverride;

            /**
            @brief 拾取靶区大小
            */
			double m_dPickAperture;
		};

        /**
        @brief  图形元素拾取管理类
        @date 创建日期:2021-08-06
        */
        class BPEntityLocateManager : public ::BIMBase::BPNonCopyableClass, public BIMBase::BPRegisterBase
        {
        public:

            /**
            @brief 析构函数
            */
            BIMBASEAPI_EXPORT virtual                           ~BPEntityLocateManager();

            /**
            @brief 设置BPPickData
            @param[out] nErrorCode：错误码；
            @param[out] reasonDesc：无法拾取的原因；
                        newSearch：是否需要重新寻找（true：重新寻找，false：使用缓存的数据）；
                        points：拾取位置的三维坐标；
                        vp：视口；
                        filterHits：是否进行过滤拾取
            @return BPPickData指针
            @see bool BPEntitySelectSetTool::_onPostLocate(BPPickDataCP pickData, ::p3d::PStringR cantAcceptReason)
            */
            BIMBASEAPI_EXPORT BPPickDataPtr                     doLocatePickData(int& nErrorCode, p3d::PStringR reasonDesc, bool newSearch, p3d::GePoint3dCP points, BPViewportPtr vp, bool filterHits = true);

            /**
            @brief 获取BPEntityLocateManager唯一实例
            @return BPEntityLocateManager类的实例
            */
            BIMBASEAPI_EXPORT static BPEntityLocateManagerR	    getInstance(void);

            /**
            @brief 设置面拾取方式
            @param[in] locSurfOpt：面拾取模式
            @return BPLocateSurfacesOpt 之前设置的面拾取模式
            */
            BIMBASEAPI_EXPORT BPLocateSurfacesOpt               setLocateSurfaces(BPLocateSurfacesOpt locSurfOpt);

            /**
            @brief 获取当前拾取信息
            @return BPPickData指针
            */
            BIMBASEAPI_EXPORT BPPickDataPtr                     getCurrPickData();

            /**
            @brief 获取下一个拾取的信息
            @return BPPickData智能指针
            */
            BIMBASEAPI_EXPORT BPPickDataPtr                     getNextPickData() const;

            /**
            @brief 设置拾取过滤器
            @param[in] filterFunction：拾取过滤器
            */
            BIMBASEAPI_EXPORT void                              setFilterFunction(LocateFilterFunc filterFunction, BPRegisterModule hm = BIMBase::getRegisterHModule());

            /**
            @brief 基本几何体的拾取，此接口只支持从Polyface类型的几何上拾取数据.
            @details 从Polyface几何体中拾取点、边、面这三种基本几何点，目前此接口不支持从基本实体里拾取。
            @param[out] geomIndexVec：拾取到的数据
            @param[in]  hitGeoType：拾取几何体的类型,可以是点/边/面；
                        pickPoint：拾取的三维坐标点；
                        vp：视口；
                        entity：被拾取的实体；
                        bHilite：是否高亮；
                        hiliteColor：高亮颜色
                        pickParams：拾取参数
            @return P3DStatus
            - SUCCESS 获取成功
            - ERROR 获取失败
            @note geomIndexVec		拾取到的数据：拾取面的场合,返回面的起始顶点的索引、此面在整个实体中的索引；
                                                  拾取边的场合,返回所属面的索引、此边所在面中的索引值、此面在整个实体中的索引；
                                                  拾取点的场合,返回所属面的索引、此点所在面的索引值、此面在整个实体中的索引；
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus                    doLocateEntityGeom(BPPickGeomType hitGeoType, p3d::GePoint3dCR pickPoint, BPViewportCP vp, BPEntityCR entity,
                OUT p3d::pvector<int>& geomIndexVec, bool bHilite, UInt32 hiliteColor, BPPickGeomParams pickParams = BPPickGeomParams());
            /**
            @brief 获取拾取面法线的旋转
            @param[in]  pickData：拾取的构件数据；
            @param[out] rMatrix：被拾取面的旋转矩阵；
                        p3d:pickPoint：拾取的三维坐标点；
            @return :P3DStatus
             - SUCCESS 获取成功
             - ERROR 获取失败
            */
             BIMBASEAPI_EXPORT p3d::P3DStatus                 getPickDataPlaneInfo(OUT ::p3d::GeRotMatrixR rMatrix, OUT p3d::GePoint3dR origin, IN BIMBase::Core::BPPickDataPtr pickData);

            /**
            @brief 拾取Solid几何体上的面
            @param[in]  pickPoint：拾取的三维坐标点；
                        vp：视窗信息；
                        entity：被拾取的entity；
                        bHilite：是否高亮；
                        hiliteColor：高亮颜色
                        pickParams：拾取参数
            @return IGeometryPtr
            */
            BIMBASEAPI_EXPORT p3d::IGeometryPtr                 pickSolidGeomFace(p3d::GePoint3dCR pickPoint, BPViewportCP vp, BPEntityCR entity, bool bHilite = false, UInt32 hiliteColor = 0, BPPickGeomParams pickParams = BPPickGeomParams());

            /**
            @brief 拾取Solid类型的几何体上的点、边或面
            @param[out] geomIndexVec：拾取到的几何数据：
                                        1、拾取点的场合，返回拾取到的点在CurvePrimitiveLineString几何体中的索引值，几何体数据由返回值得到.
                                        2、拾取边的场合，返回拾取到的边在CurvePrimitiveLineString或CurvePrimitiveLine几何体中边的索引值及总边数.
                                        3、拾取面的场合，引参数无任何数据，忽略.
            @param[in]  hitGeoType：拾取几何体的类型,可以是点、边或面.
            @param[in]  pickPoint：拾取位置的三维坐标
            @param[in]  vp：视口
            @param[in]  entity：被拾取图形实体
            @param[in]  bHilite：是否高亮，目前此参数无效
            @param[in]  hiliteColor：高亮颜色，目前此参数无效
            @param[in]  pickParams：拾取参数
            @return IGeometryPtr 拾取到的几何体
                                 拾取点的场合是CurvePrimitiveLineString类型的几何数据
                                 拾取边的场合是CurvePrimitiveLineString或CurvePrimitiveLine类型的几何数据
                                 拾取面的场合是GeCurveArray类型几何数据
            */
            BIMBASEAPI_EXPORT p3d::IGeometryPtr pickSolidGeom(OUT p3d::pvector<int>& geomIndexVec, BPPickGeomType hitGeoType, p3d::GePoint3dCR pickPoint, BPViewportCP vp, BPEntityCR entity,
            bool bHilite = false, UInt32 hiliteColor = 0, BPPickGeomParams pickParams = BPPickGeomParams());

            /**
            @brief 拾取过滤
            @param[in] pickData：拾取信息
            @return BPLocateFilterStatus
            - enLocate_Reject 不过滤
            - enLocate_Neutral 默认值，交给其他地方处理
            - enLocate_Accept 过滤
            */
            BIMBASEAPI_EXPORT BPLocateFilterStatus              locateFileter(BPPickDataCP pickData);
            /**
            @brief 靶框范围
            */
            BIMBASEAPI_EXPORT double getAperture();
            
            // ____<pkpm_inner_begin>____
            BIMBASEAPI_EXPORT void                              setupToolLocate(BPModelBaseR, bool allowLocked);

            [[deprecated("use getSelectedSnapModesFromUI(BPSnapMode& snapModes) of BPSnap.h replace")]]
            BIMBASEAPI_EXPORT void                              getSnapModeValsArray(p3d::pvector<BPSnapMode>& modes);
            [[deprecated("use addSnapModeToUI(BPSnapMode snapMode, bool bRemove) of BPSnap.h replace")]]
            BIMBASEAPI_EXPORT void                              addSnapMode(BPSnapMode mode);

            BIMBASEAPI_EXPORT void                              showErrorExplanation(p3d::WCharCP cantAcceptExplanation, int reason);
            BIMBASEAPI_EXPORT void                              showPathInfo(BPPickDataCP path);
            BIMBASEAPI_EXPORT BPPickDataPtr                     getAppFilterPath();

            // ____<pkpm_inner_end>____

            UN_REGISTER_PLUGIN_DEF()
        private:
            BPEntityLocateManager();

            void* m_refImp;

        };



    };
}; // namespace BIMBase

