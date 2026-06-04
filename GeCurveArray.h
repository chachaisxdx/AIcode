#pragma once
/**
@brief     曲线类GeCurveArray
@details   本文件包括曲线类的成员变量，构造函数和其它相关接口。
@file      GeCurveArray.h
@author    北京构力科技有限公司
@date      2021-07-16
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/
#ifndef P3D_P3DGEOMOBJECT_GECURVEARRAY_H
#define P3D_P3DGEOMOBJECT_GECURVEARRAY_H

namespace P3D_NAMESPACE_NAME {

	/**
	@brief     曲线类
	@details   包括曲线类的成员变量，构造函数和其它相关接口。
	*/
    class GeCurveArray : public RefCountedBase, public pvector<IGeCurveBasePtr>
    {
    public:



        enum BoundaryType
        {
            BOUNDARY_TYPE_None = 0,

            BOUNDARY_TYPE_Open = 1,

            BOUNDARY_TYPE_Outer = 2,

            BOUNDARY_TYPE_Inner = 3,

            BOUNDARY_TYPE_ParityRegion = 4,

            BOUNDARY_TYPE_UnionRegion = 5,
        };

        enum InOutClassification
        {
            INOUT_Unknown = 0,
            INOUT_In = 1,
            INOUT_Out = 2,
            INOUT_On = 3
        };

        friend struct CurveArrayWrapper;

    protected:
        BoundaryType    m_boundaryType;
        friend class RefCountedPtr<IGeCurveBase>;
    public:
        /**
        *@brief 判断数值成员变量是否为有效数值
        *@return true有效，false存在无效数值的成员变量
        
        */
        P3DGEOMOBJECT_EXPORT bool isValidNum() const;

        /**
        *@brief 判断曲线的数据组织是否为有效几何
        *@return true有效，false无效
        
        */
        P3DGEOMOBJECT_EXPORT bool isValidGeom() const;

		/**
		 @brief 设置曲线类型
		 @param[in] BoundaryType：曲线类型
		 */
        P3DGEOMOBJECT_EXPORT void setBoundaryType(BoundaryType BoundaryType);

		/**
		 @brief 设置子曲线类型
		 @param[in] index：子曲线index
		 @param[in] boundaryType：子曲线类型
		 @return 返回是否设置成功
		 - true  设置成功
		 - false 设置失败
		 */
        P3DGEOMOBJECT_EXPORT bool setChildBoundaryType(size_t index, BoundaryType boundaryType);

		/**
		 @brief 获取子曲线类型
		 @param[in] index：子曲线index
		 @param[out] boundaryType：子曲线类型
		 */
        P3DGEOMOBJECT_EXPORT bool getChildBoundaryType(size_t index, BoundaryType& boundaryType) const;

		/**
		 @brief 获取子曲线
		 @param[in] index：子曲线index
		 @return 返回子曲线
		 */
        P3DGEOMOBJECT_EXPORT IGeCurveBasePtr getCurveBasePointerByIndex(size_t index) const;

		/**
		 @brief 获取子曲线序号
		 @param[in] primitive：子曲线指针
		 @param[out] index：子曲线index
		 @return 返回是否成功
		 */
        P3DGEOMOBJECT_EXPORT bool getIndexByCurveBasePointer(IGeCurveBaseCP primitive, size_t& index) const;

		/**
		 @brief 获取曲线组中基本曲线的数量
		 @return 基本曲线的数量
		 */
        P3DGEOMOBJECT_EXPORT size_t getNumOfCurveBases() const;


        P3DGEOMOBJECT_EXPORT IGeCurveBasePtr getCurveBasePointerById(GeCurveBaseIdCR id) const;

		/**
		 @brief 构造函数，创建曲线组
		 @param[in] boundaryType：曲线组类型
		 */
        P3DGEOMOBJECT_EXPORT explicit GeCurveArray(BoundaryType boundaryType);



    public:
		/**
		 @brief 判断曲线组中是否只有一条基本曲线，并返回基本曲线类型
		 @return 基本曲线的类型
		 */
        P3DGEOMOBJECT_EXPORT IGeCurveBase::CurveBaseType onlyOneCurveBase() const;

		/**
		 @brief 获取曲线类型
		 @return 曲线类型
		 */
        P3DGEOMOBJECT_EXPORT BoundaryType getBoundaryType() const;

		/**
		 @brief 获取曲线是否为开放曲线类型，Open
		 @return 返回是否是开放曲线
		 - true  是开放曲线
		 - false 不是开放曲线
		 */
        P3DGEOMOBJECT_EXPORT bool isOpenBoundaryType() const;

		/**
		 @brief 获取曲线是否为闭合曲线类型，Outer或Inner
		 @return 返回是否是闭合曲线
		 - true  是闭合曲线
		 - false 不是闭合曲线
		 */
        P3DGEOMOBJECT_EXPORT bool isClosedBoundaryType() const;

		/**
		 @brief 获取曲线是否为ParityRegion
		 @return 返回获取结果
		 - true  是ParityRegion
		 - false 不是ParityRegion
		 */
        P3DGEOMOBJECT_EXPORT bool isParityRegionBoundaryType() const;

		/**
		 @brief 获取曲线是否为UnionRegion
		 @return 返回获取结果
		 - true  是UnionRegion
		 - false 不是UnionRegion
		 */
        P3DGEOMOBJECT_EXPORT bool isUnionRegionBoundaryType() const;

		/**
		 @brief 判断曲线是否为有效类型
		 @return 返回是否为有效类型
		 - true  是有效类型
		 - false 不是有效类型
		 */
        P3DGEOMOBJECT_EXPORT bool isValidBoundaryType() const;

		/**
		 @brief 获取曲线起点和终点是否相等
		 @return 返回是否相等
		 - true  相等
		 - false 不相等
		 */
        P3DGEOMOBJECT_EXPORT bool isStartEqualEnd() const;

		/**
		 @brief 判断曲线组中是否只有一条圆弧，并返回该圆弧
		 @param[out] ellipse：获取曲线中的圆弧
		 @return 是否成功
		 */
        P3DGEOMOBJECT_EXPORT bool isOnlyOuterEllipse(GeEllipse3dR ellipse) const;

		/**
		 @brief 判断曲线组为open类型时，起止点是否相等
		 @return 起止点是否相等
		 */
        P3DGEOMOBJECT_EXPORT bool isStartEqualEndOnBoundary() const;


		/**
		 @brief 判断当前曲线是否为矩形
		 @param[out] localToWorld：矩阵变换，以起点为原点，X、Y轴为起点所在两条边，Z轴为单位法向量
		 @param[out] worldToLocal：矩阵变换，将矩形的每条边对应到0..1
		 @return 返回是否是矩形
		 - true  是矩形
		 - false 不是矩形
		 */
        P3DGEOMOBJECT_EXPORT bool isRectangle(GeTransformR localToWorld, GeTransformR worldToLocal) const;

		/**
		 @brief 交换index0和index1对应的曲线
		 @param[in] index0：曲线index
		 @param[in] index1：曲线index
		 @return 返回交换结果
		 - true 交换成功
		 - false 交换失败
		 */
        P3DGEOMOBJECT_EXPORT bool swapByIndex(size_t index0, size_t index1);

		/**
		 @brief 与other交换内容
		 @param[in] other：被交换的曲线
		 */
        P3DGEOMOBJECT_EXPORT void swapContents(GeCurveArrayR other);

		/**
		 @brief 根据类型创建GeCurveArray
		 @param[in] BoundaryType：GeCurveArray类型
		 @return 一个 GeCurveArray对象
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr create(BoundaryType boundaryType);

		/**
		 @brief 根据类型和基本曲线创建GeCurveArray
		 @param[in] boundaryType：GeCurveArray类型
		 @param[in] primitive：基本曲线
		 @return 一个 GeCurveArray对象
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr create(BoundaryType boundaryType, IGeCurveBasePtr primitive);

		/**
		 @brief 克隆当前曲线创建一条新曲线
		 @return 克隆创建的新曲线
		 */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr clone() const;


        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr cloneDereferenced(bool allowExtrapolation = false, bool maximumDeref = true) const;

		/**
		 @brief 克隆当前曲线，并倒圆角后创建一条新曲线
		 @param[in] radius：倒圆角半径
		 @return 克隆创建的新曲线
		 */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr cloneWithEllipseChamfering(double radius) const;


        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr cloneWithGapsClosed(GeCurveGapOptionsCR options) const;



        P3DGEOMOBJECT_EXPORT size_t addCurveBaseFromCurveArray(GeCurveArrayCR source);

		/**
		 @brief 向GeCurveArray中添加曲线
		 @param[in] child：添加的曲线
		 */
        P3DGEOMOBJECT_EXPORT void add(IGeCurveBasePtr child);

		/**
		 @brief 向GeCurveArray中添加曲线
		 @param[in] child：添加的曲线
		 */
        P3DGEOMOBJECT_EXPORT void add(GeCurveArrayPtr child);



        /** 
        @brief 偏移曲线组
        @param[in] options: 偏移参数
        @return 返回偏移后的曲线组对象
        */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr cloneOffsetCurves2D(GeCurveOffsetOptionsCR options);

        /**
        @brief 对曲线组定义的面进行偏移
        @param[in] options: 偏移参数
        @return 返回偏移后的曲线组对象
        @note 最大倒角为90度
        */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr cloneAreaOffset(GeCurveOffsetOptionsCR options) const;


        P3DGEOMOBJECT_EXPORT size_t getNumByCurveType(IGeCurveBase::CurveBaseType targetType) const;


        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr cloneWithSplits(GeCurveArrayCR splitterCurves, bool primitivesOnly = false);

		/**
		 @brief 获取当前曲线在平面上方、下方、平面上的部分曲线
		 @param[in] plane：拆分平面
		 @param[out] belowCollector：平面下方的曲线
		 @param[out] aboveCollector：平面上方的曲线
		 @param[out] onCollector：平面上的曲线
		 */
        P3DGEOMOBJECT_EXPORT void getAppendSplitCurvesByPlane(GePlane3dCR plane, GeCurveArrayP belowCollector, GeCurveArrayP aboveCollector, GeCurveArrayP onCollector);


		/**
		 @brief 克隆当前曲线，并将所有linestring拆分为线段
		 @return 克隆创建的新曲线
		 */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr cloneWithDecomLinestrings() const;

		/**
		 @brief 获取曲线长度及重心点
		 @param[out] length：曲线长度
		 @param[out] centroid：曲线重心点
		 @return 返回是否获取成功
		 - true  获取成功
		 - false 获取失败
		 */
        P3DGEOMOBJECT_EXPORT bool  getLengthAndCentroid(double& length, GePoint3dR centroid) const;

		/**
		 @brief 获取区域的重心、法向量、面积
		 @param[out] centroid：重心
		 @param[out] normal：法向量
		 @param[out] area：面积
		 @return 返回是否获取成功
		 - true  获取成功
		 - false 获取失败
		 */
        P3DGEOMOBJECT_EXPORT bool getCentroidAndNormalAndArea(GePoint3dR centroid, GeVec3dR normal, double& area) const;


        P3DGEOMOBJECT_EXPORT bool getMeasureParaAreaProducts(GeMatrix4dR products) const;



        P3DGEOMOBJECT_EXPORT bool getMeasureParaDifferentialAreaRotationProducts
        (
            GeRay3dCR rotationAxis,
            GeTransformR rotationToWorld,
            GeMatrix4dR products
        ) const;



        P3DGEOMOBJECT_EXPORT bool getMeasureParaDifferentialWireRotationProducts
        (
            GeRay3dCR rotationAxis,
            GeTransformR rotationToWorld,
            GeMatrix4dR products
        ) const;



        P3DGEOMOBJECT_EXPORT bool getMeasureParatWireProducts(GeMatrix4dR products) const;

		/**
		 @brief 获取区域投影到二维的的重心、面积
		 @param[out] centroid：重心
		 @param[out] area：面积
		 @return 返回是否获取成功
		 - true  获取成功
		 - false 获取失败
		 */
        P3DGEOMOBJECT_EXPORT bool  getCentroidAndArea2D(GePoint3dR centroid, double& area) const;

		/**
		 @brief 获取曲线投影在射线上的范围
		 @param[in] ray：投影射线
		 @return 投影范围
		 */
        P3DGEOMOBJECT_EXPORT GeRange1d getRangeOfProjectionOnRay(GeRay3dCR ray) const;


		/**
		 @brief 克隆当前曲线到根据frameType确定的局部坐标系，
		 局部坐标系xy方向与曲线起点确定的局部坐标系xy方向平行
		 @param[in] frameType：局部坐标系类型
		 @param[out] localToWorld：局部坐标系到世界坐标系的变换矩阵
		 @param[out] worldToLocal：世界坐标系到局部坐标系的变换矩阵
		 @param[out] localRange：曲线在局部坐标系的range
		 @return 经变换的克隆曲线
		 */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr cloneWithInLocalCoordinates
        (
            LocalCoordinateSelect frameType,
            GeTransformR localToWorld,
            GeTransformR worldToLocal,
            GeRange3dR localRange
        ) const;

		/**
		 @brief 查找该曲线组中是否有基本曲线能定义明确的坐标系，坐标系原点为基本曲线起点
		 @param[out] frame：曲线定义的坐标系
		 @return 返回查找结果
		 - true 查找成功
		 - false 查找失败
		 */
        P3DGEOMOBJECT_EXPORT bool getTransformFrame(GeTransformR frame) const;

		/**
		 @brief 查找该曲线组中是否有基本曲线能定义明确的坐标系
		 @param[out] frame：曲线定义的坐标系
		 @param[in] searchPreference：0：以曲线起点和终点构成的向量为X轴； \n
									  1：曲线起点切线为x向量，终点切线为y向量，若x、y平行，使用默认坐标系； \n
									  2：若x、y平行，使用选项0定义的坐标系
		 @return 返回查找结果
		 - true 查找成功
		 - false 查找失败
		 */
        P3DGEOMOBJECT_EXPORT bool getTransformFrame(GeTransformR frame, int searchPreference) const;


		/**
		 @brief 计算uv系数对应的点坐标及切向量
		 @param[in] uProport：u方向坐标
		 @param[in] vProport：v方向坐标
		 @param[out] xyz：uv坐标对应的曲线上点
		 @return 返回查找结果
		 - true 查找成功
		 - false 查找失败
		 */
        P3DGEOMOBJECT_EXPORT bool getPointByUVProport
        (
            double uProport,
            double vProport,
            GePoint3dR xyz,
            GeVec3dR dXdu,
            GeVec3dR dXdv
        ) const;


		/**
		 @brief 根据类型和点集创建GeCurveArray
		 @param[in] points：点集
		 @param[in] boundaryType：GeCurveArray类型
		 @param[in] forceXYOrientation：当类型为inner时，使GeCurveArray中的线为顺时针方向；当类型为outer时，使GeCurveArray中的线为逆时针方向
		 @return 一个 GeCurveArray对象
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr createLinestringArray(pvector<GePoint3d> const& points,
            BoundaryType boundaryType = GeCurveArray::BOUNDARY_TYPE_Open,
            bool forceXYOrientation = false);


		/**
		 @brief 根据类型和点集创建GeCurveArray
		 @param[in] points：点集数组首指针
		 @param[in] numPoints：点集数组点个数
		 @param[in] boundaryType：GeCurveArray类型
		 @param[in] forceXYOrientation：当类型为inner时，使GeCurveArray中的线为顺时针方向；当类型为outer时，使GeCurveArray中的线为逆时针方向
		 @return 一个 GeCurveArray对象
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr createLinestringArray(
            GePoint3dCP points,
            size_t numPoints,
            BoundaryType boundaryType = GeCurveArray::BOUNDARY_TYPE_Open,
            bool forceXYOrientation = false);

		/**
		 @brief 根据类型和二维点集创建GeCurveArray
		 @param[in] points：点集数组首指针
		 @param[in] numPoints：点集数组点个数
		 @param[in] boundaryType：GeCurveArray类型
		 @param[in] forceXYOrientation：当类型为inner时，使GeCurveArray中的线为顺时针方向；当类型为outer时，使GeCurveArray中的线为逆时针方向
		 @return 一个 GeCurveArray对象
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr createLinestringArray(
            GePoint2dCP points,
            size_t numPoints,
            BoundaryType boundaryType = GeCurveArray::BOUNDARY_TYPE_Open,
            bool forceXYOrientation = false);

		/**
		 @brief 根据矩形上的点创建矩形
		 @param[in] x0：起始坐标点x值
		 @param[in] y0：起始坐标点y值
		 @param[in] x1：对角坐标点x值
		 @param[in] y1：对角坐标点y值
		 @param[in] z： 所有坐标点z值
		 @param[in] boundaryType：GeCurveArray类型
		 @return 一个 GeCurveArray对象
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr createRectangle(double x0, double y0, double x1, double y1, double z,
            BoundaryType boundaryType = GeCurveArray::BOUNDARY_TYPE_Outer);

		/**
		 @brief 根据线段创建GeCurveArray
		 @param[in] segments：线段list
		 @return 一个 GeCurveArray
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr create(pvector<GeSegment3d> const& segments);


		/**
		 @brief 根据GeEllipse3d创建GeCurveArray
		 @param[in] arc：弧线
		 @param[in] boundaryType：GeCurveArray类型
		 @param[in] forceXYOrientation：当类型为inner时，使GeCurveArray中的线为顺时针方向；当类型为outer时，使GeCurveArray中的线为逆时针方向
		 @return 一个 GeCurveArray
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr createEllipseCurve(GeEllipse3dCR arc, BoundaryType boundaryType = GeCurveArray::BOUNDARY_TYPE_Outer, bool forceXYOrientation = false);

		/**
		 @brief 创建曲线，并将child作为子曲线加入曲线中
		 @param[in] child：子曲线
		 @param[in] boundaryType：GeCurveArray类型
		 @return 一个 GeCurveArray
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr create(IGeCurveBasePtr child, BoundaryType boundaryType = GeCurveArray::BOUNDARY_TYPE_Open);


		/**
		 @brief 克隆曲线，并将所有子曲线克隆为样条曲线，原曲线类型不变
		 @return 一个 GeCurveArray
		 */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr cloneAsBsplineCurves() const;

		/**
		 @brief 克隆曲线，并将所有子曲线克隆为stroke，原曲线类型不变
		 @return 一个 GeCurveArray
		 */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr createByStrokePoints(IFacetSettingR options) const;


        P3DGEOMOBJECT_EXPORT void getStrokePoints(pvector <GePoint3d>& points, IFacetSettingR options) const;

		/**
		 @brief 获取曲线上对应长度的点
		 @param[in] distances：待获取点的长度，其中长度为对应点距曲线起点的长度，
		 若曲线中存在不首尾相连的子曲线，跨度距离不参与计算
		 @param[out] locations：长度对应的曲线上点
		 @return 一个 GeCurveArray
		 */
        P3DGEOMOBJECT_EXPORT bool getSpacedPoints(pvector<double> const& distances, pvector<GeCurveLocationInfo>& locations) const;
				
		/**
		 @brief 将曲线转换为一条样条曲线
		 @param[out] curve：得到的样条曲线
		 @return 是否成功
		 - 0  获取成功
		 - 1  获取失败
		 */
        P3DGEOMOBJECT_EXPORT P3DStatus getBsplineCurve(GeBsplineCurveR curve) const;

		/**
		 @brief 将曲线转换为一条样条曲线
		 @return 得到的样条曲线
		 */
        P3DGEOMOBJECT_EXPORT GeBsplineCurvePtr getBsplineCurve() const;

		/**
		 @brief 获取空间点对应的曲线上的最近点，最近点不可超出曲线
		 @param[in] spacePoint：空间点
		 @param[out] location：最近点信息
		 @return 是否成功
		 - true  获取成功
		 - false  获取失败
		 */
        P3DGEOMOBJECT_EXPORT bool getClosestPointBounded(GePoint3dCR spacePoint, GeCurveLocationInfoR location) const;

		/**
		 @brief 获取空间点对应的曲线上的最近点
		 @param[in] spacePoint：空间点
		 @param[out] location：最近点信息
		 @param[in] extend0：是否可在起点位置超出曲线
		 @param[in] extend1：是否可在终点位置超出曲线
		 @return 是否成功
		 - true  获取成功
		 - false  获取失败
		 */
        P3DGEOMOBJECT_EXPORT bool getClosestPointBounded(GePoint3dCR spacePoint, GeCurveLocationInfoR location, bool extend0, bool extend1) const;

		/**
		 @brief 将曲线和点变换到xy平面后，获取点对应的曲线上的最近点，最近点为原始曲线上点，不可超出曲线
		 @param[in] spacePoint：空间点
		 @param[in] worldToLocal：变换矩阵
		 @param[out] location：最近点信息
		 @return 是否成功
		 - true  获取成功
		 - false  获取失败
		 */
        P3DGEOMOBJECT_EXPORT bool getClosestPointBounded2D(GePoint3dCR spacePoint, GeMatrix4dCP worldToLocal, GeCurveLocationInfoR location) const;

		/**
		 @brief 将曲线和点变换到xy平面后，获取点对应的曲线上的最近点，最近点为原始曲线上点，不可超出曲线
		 @param[in] spacePoint：空间点
		 @param[in] worldToLocal：变换矩阵
		 @param[out] location：最近点信息
		 @param[in] extend0：是否可在起点位置超出曲线
		 @param[in] extend1：是否可在终点位置超出曲线
		 @return 是否成功
		 - true  获取成功
		 - false  获取失败
		 */
        P3DGEOMOBJECT_EXPORT bool getClosestPointBounded2D(GePoint3dCR spacePoint, GeMatrix4dCP worldToLocal, GeCurveLocationInfoR location, bool extend0, bool extend1) const;

		/**
		 @brief 获取空间点对应的曲线上的最近点，如果曲线为面类型，获取空间点投影到曲线区域内的点
		 @param[in] spacePoint：空间点
		 @param[out] curveOrRegionPoint：曲线上或区域内的点
		 @return 空间点与曲线位置关系
		 */
        P3DGEOMOBJECT_EXPORT GeCurveArray::InOutClassification getClosestCurveOrRegionPoint(GePoint3dCR spacePoint, GePoint3dR curveOrRegionPoint) const;

		/**
		 @brief 获取曲线起点和终点
		 @param[out] pointA：起点
		 @param[out] pointB：终点
		 @return 返回是否获取成功
		 - true 获取成功
		 - false 获取失败
		 */
        P3DGEOMOBJECT_EXPORT bool getStartEndPoint(GePoint3dR pointA, GePoint3dR pointB) const;

		/**
		 @brief 获取曲线起点、终点及切向量
		 @param[out] pointA：起点
		 @param[out] pointB：终点
		 @param[out] unitTangentA：起点切向单位向量
		 @param[out] unitTangentB：终点切向单位向量
		 @return 返回是否获取成功
		 - true 获取成功
		 - false 获取失败
		 */
        P3DGEOMOBJECT_EXPORT bool getStartEndPoint(GePoint3dR pointA, GePoint3dR pointB, GeVec3dR unitTangentA, GeVec3dR unitTangentB) const;

		/**
		 @brief 获取曲线起点
		 @param[out] point：起点
		 @return 返回是否获取成功
		 - true 获取成功
		 - false 获取失败
		 */
        P3DGEOMOBJECT_EXPORT bool getStartPoint(GePoint3dR point) const;

		/**
		 @brief 获取曲线长度
		 @return 曲线长度
		 */
        P3DGEOMOBJECT_EXPORT double getLength() const;

		/**
		 @brief 获取变换后曲线长度
		 @param[in] worldToLocal：变换矩阵
		 @return 曲线长度
		 */
        P3DGEOMOBJECT_EXPORT double getLength(GeRotMatrixCP worldToLocal) const;

		/**
		 @brief 获取曲线首尾距离
		 @return 曲线首尾距离
		 */
        P3DGEOMOBJECT_EXPORT double getFastLength() const;

		/**
		 @brief 获取曲线中非首尾相连处最大距离
		 */
        P3DGEOMOBJECT_EXPORT double maxGapDistanceOfAdjacentCurves() const;

		/**
		 @brief 获取曲线最大坐标值
		 */
        P3DGEOMOBJECT_EXPORT double getFastMaxAbs() const;

		/**
		 @brief 判断该曲线与other的类型是否相同
		 @param[in] other：曲线
		 @return 返回是否相同
		 - true 相同
		 - false 不相同
		 */
        P3DGEOMOBJECT_EXPORT bool isEqualType(GeCurveArrayCR other) const;

		/**
		 @brief 判断该曲线与other在容差tolerance范围内是否相等
		 @param[in] other：曲线
		 @param[in] tolerance：容差
		 @return 返回是否相等
		 - true 相等
		 - false 不相等
		 */
        P3DGEOMOBJECT_EXPORT bool isEqual(GeCurveArrayCR other, double tolerance = 0.0) const;


		/**
		@brief     获取当前曲线的Range
		@param[out] range：当前曲线的Range
		@return 返回是否获取成功
		 - true 获取成功
		 - false 获取失败
		*/
        P3DGEOMOBJECT_EXPORT bool getRange(GeRange3dR range) const;

		/**
		@brief     获取当前曲线变换后的Range
		@param[out] range：曲线变换后的Range
		@param[in] transform：变换矩阵
		@return 返回是否获取成功
		 - true 获取成功
		 - false 获取失败
		*/
        P3DGEOMOBJECT_EXPORT bool getRange(GeRange3dR range, GeTransformCR transform) const;

		/**
		@brief    判断当前曲线是否在平面上
		@param[out] localToWorld：局部坐标系到世界坐标系变换矩阵
		@param[out] worldToLocal：世界坐标系到局部坐标系变换矩阵
		@param[out] range：曲线在局部坐标系的range
		@return 返回是否获取成功
		 - true 获取成功
		 - false 获取失败
		*/
        P3DGEOMOBJECT_EXPORT bool isPlanar(GeTransformR localToWorld, GeTransformR worldToLocal, GeRange3dR range) const;

		/**
		@brief    判断当前曲线是否在平面上
		@param[out] localToWorld：局部坐标系到世界坐标系变换矩阵
		@param[out] worldToLocal：世界坐标系到局部坐标系变换矩阵
		@param[out] range：曲线在局部坐标系的range
		@param[in] normal：在某些不确定的情况下，用于确定法向
		@return 返回是否获取成功
		 - true 获取成功
		 - false 获取失败
		*/
        P3DGEOMOBJECT_EXPORT bool isPlanarWithDefaultNormal(GeTransformR localToWorld, GeTransformR worldToLocal, GeRange3dR range, GeVec3dCP normal) const;

		/**
		@brief    获取有效索引。当传入index为负时，为逆序索引
		@param[in] index：待判断索引
		@return 有效索引
		*/
        P3DGEOMOBJECT_EXPORT size_t correctIndex(int index) const;

		/**
		@brief    将index转换为有效索引后获取对应的子曲线
		@param[in] index：索引
		@return 索引对应的子曲线
		*/
        P3DGEOMOBJECT_EXPORT IGeCurveBasePtr getByCorrectIndex(ptrdiff_t index) const;

		/**
		@brief   获取点位置信息对应的子曲线索引
		@param[in] location：点位置信息
		@return 子曲线索引
		*/
        P3DGEOMOBJECT_EXPORT size_t getIndexByCurveLocationInfo(GeCurveLocationInfo const& location) const;

		/**
		 @brief 获取子曲线索引
		 @param[in] primitive：待查找的子曲线
		 @return 子曲线索引
		 */
        P3DGEOMOBJECT_EXPORT size_t getIndexByCurveBasePointer(IGeCurveBaseCP primitive) const;

		/**
		 @brief 获取子曲线直接父曲线
		 @param[in] primitive：待查找的子曲线
		 @return 父曲线
		 */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr getParentByCurveBasePointer(IGeCurveBaseCP primitive) const;

		/**
		 @brief 根据点位置信息的子曲线索引及点分数位比较，相等时返回0，location0<location1时返回-1，location0>location1时返回1
		 @param[in] location0：待查找的子曲线
		 @param[in] location1：待查找的子曲线
		 @return 比较结果
		 */
        P3DGEOMOBJECT_EXPORT int compareCurveLocationInfo(GeCurveLocationInfo const& location0, GeCurveLocationInfo const& location1) const;

		/**
		 @brief 获取传入tolerance与根据MaxAbs计算的容差的较大值
		 @param[in] tolerance：待比较容差
		 @return 较大容差
		 */
        P3DGEOMOBJECT_EXPORT double getLargerTolerance(double tolerance) const;


		/**
		 @brief 将曲线从(index0，proportPara0)到(index1，proportPara1)的部分克隆为新曲线。
		 若(index0，proportPara0)>(index1，proportPara1),则逆序克隆
		 @param[in] index0：起点子曲线索引
		 @param[in] proportPara0：起点分数位
		 @param[in] index1：终点子曲线索引
		 @param[in] proportPara1：终点分数位
		 @return 克隆后曲线
		 */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr cloneWithIndexesAndProportParas(int index0, double proportPara0, int index1, double proportPara1) const;

		/**
		 @brief 将曲线从(index0，proportPara0)到(index1，proportPara1)的部分克隆为新曲线。
		 若(index0，proportPara0)>(index1，proportPara1),则逆序克隆
		 @param[in] index0：起点子曲线索引
		 @param[in] proportPara0：起点分数位
		 @param[in] index1：终点子曲线索引
		 @param[in] proportPara1：终点分数位
		 @param[in] allowExtrapolation：是否允许曲线延长
		 @return 克隆后曲线
		 */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr cloneWithIndexesAndProportParas(int index0, double proportPara0, int index1, double proportPara1, bool allowExtrapolation) const;

		/**
		 @brief 将曲线完全反向克隆
		 @return 克隆后曲线
		 */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr cloneWithReversed() const;

		/**
		 @brief 判断当前曲线是否含有不是segment或linestring的子曲线
		 @return 含有返回true，不含返回false
		 */
        P3DGEOMOBJECT_EXPORT bool isContainNonLinearCurves() const;

		/**
		 @brief 获取曲线与平面的交点信息
		 @param[in] plane：待计算相交的平面
		 @param[out] intersections：交点信息
		 @param[in] tolerance：容差
		 */
        P3DGEOMOBJECT_EXPORT void getIntersectionsWithPlane(GePlane3dCR plane, pvector<GeCurveLocationInfoPair>& intersections, double tolerance = 0.0) const;

		/**
		 @brief 获取区域与平面的交点组信息，每组交点为一条交线的起终点
		 @param[in] plane：待计算相交的平面
		 @param[out] intersections：交点信息
		 @param[in] tolerance：容差
		 @return 返回是否获取成功
		 - true 获取成功
		 - false 获取失败
		 */
        P3DGEOMOBJECT_EXPORT bool getIntersectionsOfClosedCurveWithPlane(GePlane3dCR plane, pvector<GeCurveLocationInfoPair>& intersections, double tolerance = 0.0) const;

		/**
		 @brief 获取区域与平面的所有交线，若交线不止一条，返回的曲线为CURVE_BASE_TYPE_CurveArray类型
		 @param[in] plane：待计算相交的平面
		 @param[in] tolerance：容差
		 @return 交线
		 */
        P3DGEOMOBJECT_EXPORT IGeCurveBasePtr getIntersectionsWithPlane(GePlane3dCR plane, double tolerance = 0.0) const;

        /**
        *@brief: 判断点 xyz 是否在该GeCurveArray对象在 xy 平面的投影范围内
        *@param xyz：空间点
        *@return  位置信息      
        */
        P3DGEOMOBJECT_EXPORT GeCurveArray::InOutClassification getPointLocationType2D(GePoint3dCR xyz) const;
		
        /**
        *@brief 判断曲线区域与射线的相交信息
        *@param ray：射线
        *@param hitDetail: 交点信息
        *@return 返回交点是否在GeCurveArray对象内；
                 INOUT_In: 在GeCurveArray对象内;
                 INOUT_Out:在GeCurveArray对象外;
                 INOUT_On: 在GeCurveArray对象边界上;
                 INOUT_Unknown: GeCurveArray不是区域对象;
        */
        P3DGEOMOBJECT_EXPORT GeCurveArray::InOutClassification getIntersectionLocationTypeWithRay
        (
            GeRay3dCR ray,
            GeSolidLocationInfoR hitDetail
        ) const;

		/**
		 @brief 对曲线做变换
		 @param[in] transform：曲线变换矩阵
		 @return 返回变换是否成功
		 - true  变换成功
		 - false 变换失败
		 */
        P3DGEOMOBJECT_EXPORT bool setByTransform(GeTransformCR transform);

		/**
		 @brief 将曲线反向
		 @return 返回反向是否成功
		 */
        P3DGEOMOBJECT_EXPORT bool setByReverse();

		/**
		 @brief 合并曲线的相邻单元，相邻的segment或linestring合并为linestring，共线中间点去除，相邻同圆圆弧合并。
		 */
        P3DGEOMOBJECT_EXPORT void setByConsolidateAdjacentCurves();

		/**
		 @brief 合并曲线的相邻单元，相邻的segment或linestring合并为linestring，相邻同圆圆弧合并。
		 @param[in] doSimplifyLinestrings：为true时去除共线中间点
		 */
        P3DGEOMOBJECT_EXPORT void setByConsolidateAdjacentCurves(bool doSimplifyLinestrings);

		/**
		 @brief 简化曲线终linestring的点
		 @param[in] distanceTol：去除在距离误差内的邻近点
		 @param[in] eliminateOverdraw：为true时去除共线中间点
		 */
        P3DGEOMOBJECT_EXPORT void setBySimplifyLinestrings(double distanceTol, bool eliminateOverdraw, bool wrap);

		/**
		 @brief 根据曲线数据调整曲线中子曲线的顺序、类型、方向。
		 当子曲线A的起点在子曲线B内，且areaA<areaB时认为子曲线A在子曲线B内部。
		 @param[in] fullGeometryCheck：为true时，还需要进行复杂的曲线相交判断用于确定曲线位置关系
		 @return 是否成功
		 */
        P3DGEOMOBJECT_EXPORT bool setByUpdateOuterInner2D(bool fullGeometryCheck = false);

		/**
		 @brief 调整曲线中子曲线顺序，使相邻子曲线端点距离最小，尽量首尾相连
		 @return 相邻子曲线端点最大距离
		 */
        P3DGEOMOBJECT_EXPORT double reorderForSmallGaps();

		/**
		 @brief 整理顺序混乱的曲线为多组首尾相连的子曲线
		 返回最终曲线类型为None，子曲线类型为Open或Outer
		 @return 整理好的曲线
		 */
        P3DGEOMOBJECT_EXPORT GeCurveArrayPtr assembleChains();
		

		/**
		 @brief 曲线区域求并
		 @param[in] regionA：待求并的曲线区域
		 @param[in] regionB：待求并的曲线区域
		 @param[out] newToOld：结果曲线中子曲线与原始子曲线对应关系
		 @return 求并结果曲线
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr getCurveArrayByAreaUnion(GeCurveArrayCR regionA, GeCurveArrayCR regionB, GeCurvePrimitivePtrPairArray* newToOld = NULL);

		/**
		 @brief 曲线区域求差
		 @param[in] regionA：待求并的曲线区域
		 @param[in] regionB：待求并的曲线区域
		 @param[out] newToOld：结果曲线中子曲线与原始子曲线对应关系
		 @return 求差结果曲线
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr getCurveArrayByAreaDifference(GeCurveArrayCR regionA, GeCurveArrayCR regionB, GeCurvePrimitivePtrPairArray* newToOld = NULL);

		/**
		 @brief 曲线区域求交
		 @param[in] regionA：待求并的曲线区域
		 @param[in] regionB：待求并的曲线区域
		 @param[out] newToOld：结果曲线中子曲线与原始子曲线对应关系
		 @return 求交结果曲线
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr getCurveArrayByAreaIntersection(GeCurveArrayCR regionA, GeCurveArrayCR regionB, GeCurvePrimitivePtrPairArray* newToOld = NULL);

		/**
		 @brief 曲线区域求异或
		 @param[in] regionA：待求并的曲线区域
		 @param[in] regionB：待求并的曲线区域
		 @param[out] newToOld：结果曲线中子曲线与原始子曲线对应关系
		 @return 求异或结果曲线
		 */
        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr getCurveArrayByAreaParity(GeCurveArrayCR regionA, GeCurveArrayCR regionB, GeCurvePrimitivePtrPairArray* newToOld = NULL);



        P3DGEOMOBJECT_EXPORT static GeCurveArrayPtr getCurveArrayByAreaAnalysis
        (GeCurveArrayCR region, AreaSelect select1, BoolSelect select2, bool reverse);






    };


};


#endif