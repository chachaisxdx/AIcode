#pragma once
/**
@brief    PolyfaceHandle文件
@details  本文件包括PolyfaceHandle的初始化等相关函数。
@file      PolyfaceHandle.h
@author    北京构力科技有限公司
@date      2021-01-08
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/
#ifndef P3D_P3DGEOMOBGECT_POLYFACEHANDLE_H
#define P3D_P3DGEOMOBGECT_POLYFACEHANDLE_H


namespace P3D_NAMESPACE_NAME
{
	/**
	@brief    三角面片类
	@details  包括三角面片类的初始化等相关函数。
	*/
    class PolyfaceHandle : public RefCountedBase, public PolyfacePipeOperatorTmp
	{
	protected:
		PolyfaceHandle();
	public:
		/**
		@brief 合并相同点
		*/
		P3DGEOMOBJECT_EXPORT void combineCoordinate();
		P3DGEOMOBJECT_EXPORT void clearTags(uint32_t numPerFace, uint32_t meshStyle);
		P3DGEOMOBJECT_EXPORT bool addFacetIndices
			(
			size_t  numIndex,
			int     *pointIndices,
			int     *normalIndices = NULL,
			int     *paramIndices = NULL,
			int     *colorIndices = NULL
			);
		P3DGEOMOBJECT_EXPORT bool addFacetIndices
			(
			pvector<int> &pointIndices,
			pvector<int> *normalIndices = NULL,
			pvector<int> *paramIndices = NULL,
			pvector<int> *colorIndices = NULL
			);
		P3DGEOMOBJECT_EXPORT void setIlluminationName(wchar_t const *name);
		P3DGEOMOBJECT_EXPORT void setTextureId(uintptr_t id);

	public:
		/**
		@brief 拷贝当前polyface所有数据到dest
		*/
		P3DGEOMOBJECT_EXPORT void copyTo(PolyfacePipeOperatorTmp& dest);
		/**
		@brief 获取三维点
		@return 返回获取的三维点
		*/
		P3DGEOMOBJECT_EXPORT TemplateVectorGePoint3dR getPointR();
		/**
		@brief 获取纹理坐标，一般需调用buildPerFaceParameters计算后有值
		*/
		P3DGEOMOBJECT_EXPORT TemplateVectorGePoint2dR getParamR();
		/**
		@brief 获取法向数组，一般需调用buildPerFaceNormals计算后有值
		*/
		P3DGEOMOBJECT_EXPORT TemplateVectorGeVec3dR   getNormalR();
		P3DGEOMOBJECT_EXPORT TemplateVectorRgbFactorR getRgbFactorR();
		P3DGEOMOBJECT_EXPORT TemplateVectorUInt32R    getRgbUIntR();
		P3DGEOMOBJECT_EXPORT TemplateVectorUInt32R    getRgbTableR();
		P3DGEOMOBJECT_EXPORT TemplateVectorRgbFloatR  getRgbFloatR();
		/**
		@brief 获取多边形顶点序号，顶点序号以1起始，0为各多边形分隔，负值索引起始的边在显示时隐藏。与getPointR一起使用
		*/
		P3DGEOMOBJECT_EXPORT TemplateVectorIntR       getPointIndexR();
		/**
		@brief 获取多边形顶点的纹理坐标序号，0为各多边形分隔。与getParamR一起使用
		*/
		P3DGEOMOBJECT_EXPORT TemplateVectorIntR       getParamIndexR();
		/**
		@brief 获取多边形顶点的法向序号，0为各多边形分隔。与getNormalR一起使用
		*/
		P3DGEOMOBJECT_EXPORT TemplateVectorIntR       getNormalIndexR();
		P3DGEOMOBJECT_EXPORT TemplateVectorIntR       getRgbIndexR();
        P3DGEOMOBJECT_EXPORT PString&                 getTagNameR();

		/**
		@brief 获取多边形面序号，0为各多边形分隔。一般需调用buildPerFaceFaceData计算后有值
		*/
        P3DGEOMOBJECT_EXPORT TemplateVectorIntR       getFaceIndexR();

		/**
		@brief 获取多边形面信息，一般需调用buildPerFaceFaceData计算后有值
		*/
        P3DGEOMOBJECT_EXPORT TemplateVector<FacetParamRange>&  getFaceDataR();

		/**
		@brief 获取多边形边信息，一般需调用addEdgeIndeces计算后有值
		*/
        P3DGEOMOBJECT_EXPORT TemplateVector<PolyEdgesIndices>& getEdgeIndicesR();
		/**
		@brief 清除所有index数据
		*/
		P3DGEOMOBJECT_EXPORT void clearIndexVectors();

		/**
		@brief 清除所有数据
		*/
		P3DGEOMOBJECT_EXPORT void clearVectors();

		/**
		@brief 为所有index数据添加分隔符0
		*/
		P3DGEOMOBJECT_EXPORT void stopActiveIndexVectors();
		P3DGEOMOBJECT_EXPORT void activateVectorsForIndexing(IPolyfacePipeOperatorR source);
		P3DGEOMOBJECT_EXPORT void activateVectorsForPolylineIndexing(IPolyfacePipeOperatorR source);
		P3DGEOMOBJECT_EXPORT void activeFlagsByAvailableData();
		P3DGEOMOBJECT_EXPORT bool convertToVariableSizeSignedOneBasedIndexedFaceLoops();

		P3DGEOMOBJECT_EXPORT bool convertTableColorToColorIndices(TemplateVectorIntCP faceToTableColor, TemplateVectorIntCP vertexToTableColor);
		
		P3DGEOMOBJECT_EXPORT void removeTwoEdgeFacesFromVariableSizeOneBasedMesh();

		/**
		@brief 初始化一个polyface，其中多边形边数不固定
		*/
		P3DGEOMOBJECT_EXPORT static PolyfaceHandlePtr createVariableSizeIndexed();

		/**
		@brief 初始化一个polyface，其中多边形边数固定
		@param[in] numPerBlock: 多边形边数，小于3时无效
		*/
		P3DGEOMOBJECT_EXPORT static PolyfaceHandlePtr createFixedSizeIndexed(int numPerBlock);

		/**
		@brief 初始化一个polyface，其中为四边形，通过表格中的点定义
		@param[in] numPerRow: 表格行数，小于2时无效
		*/
		P3DGEOMOBJECT_EXPORT static PolyfaceHandlePtr createQuadticGrid(int numPerRow);

		/**
		@brief 初始化一个polyface，其中为三角形，通过表格中的点定义四边形，再将四边形拆分为三角形
		@param[in] numPerRow: 表格行数，小于2时无效
		*/
		P3DGEOMOBJECT_EXPORT static PolyfaceHandlePtr createTriangleGrid(int numPerRow);
		P3DGEOMOBJECT_EXPORT static PolyfaceHandlePtr createPlaneTriangulation(pvector <GePoint3d> const &points, double fringeExpansionFactor = 0.10, bool retainFringeTriangles = false);
		
		/**
		@brief 初始化一个polyface，其中每个面通过未排序的numPerFace个点定义
		@param[in] numPerFace: 面的点数，可设置3或4
		*/
		P3DGEOMOBJECT_EXPORT static PolyfaceHandlePtr createFixedSizeCoordinates(int numPerFace);

		/**
		@brief 初始化一个polyface，同createVariableSizeIndexed
		*/
		P3DGEOMOBJECT_EXPORT static PolyfaceHandlePtr createNewOne();

		P3DGEOMOBJECT_EXPORT bool hasAddtionColors(bool &colorsAreByVertex, bool &colorsAreByFace, bool &colorsAreBySector);

		/**
		@brief 复制所有数据到dest
		@param[out] dest: 复制后的polyface
		*/
		P3DGEOMOBJECT_EXPORT void copyTo(PolyfaceHandle& dest);
		P3DGEOMOBJECT_EXPORT void setNewFace(FacetParamRange* faceData, size_t endIndex = 0);

		/**
		@brief 将所有面进行三角化
		@return 三角化成功时返回success
		*/
        P3DGEOMOBJECT_EXPORT P3DStatus triangulate();

		/**
		@brief 将所有非平面或边数大于maxEdge的面进行三角化
		@param[in] maxEdge: 三角化后最大边数
		@return 三角化成功时返回true
		*/
        P3DGEOMOBJECT_EXPORT bool triangulate(size_t maxEdge);
		P3DGEOMOBJECT_EXPORT static PolyfaceHandlePtr createUnifiedIndexMesh(IPolyfacePipeOperatorCR source);
		
		/**
		@brief 计算polyface边信息
		@param[in] drawMethodIndex: 暂未使用该参数，可传0
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT P3DStatus addEdgeIndeces(size_t drawMethodIndex);
		P3DGEOMOBJECT_EXPORT bool compactIndexArrays();

		/**
		@brief 对polyface做矩阵变换
		@param[in] transform: 变换矩阵
		@param[in] reverseIndicesIfMirrored: 当为true时，如果矩阵是镜像矩阵，为保持法向关系，将面的点序反向
		*/
		P3DGEOMOBJECT_EXPORT void geTransform
			(
			GeTransformCR transform,
			bool        reverseIndicesIfMirrored = true
			);

		/**
		@brief 对data中的所有polyface做矩阵变换
		@param[in] data: 待变换的polyface，并返回变换后的polyface
		@param[in] transform: 变换矩阵
		@param[in] reverseIndicesIfMirrored: 当为true时，如果矩阵是镜像矩阵，为保持法向关系，将面的点序反向
		*/
		static P3DGEOMOBJECT_EXPORT void geTransform
			(
			pvector<PolyfaceHandlePtr> &data,
			GeTransformCR transform,
			bool        reverseIndicesIfMirrored = true
			);

		/**
		@brief 将所有面法向反向
		*/
		P3DGEOMOBJECT_EXPORT void reverseNormals();

		/**
		@brief 添加多边形
		@param[in] xyz: 三维点数组指针
		@param[in] n: 三维点个数
		@param[in] normal: 三维点法向
		@param[in] param: 三维点纹理坐标
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT bool addPolygon(GePoint3dCP xyz, size_t n, GeVec3dCP normal = NULL, GePoint2dCP param = NULL);
		
		P3DGEOMOBJECT_EXPORT bool addPolygon(int vnum, GePoint3dCP xyzPts, GePoint2dCP uvPts, int smoothGroup = 0);
		/**
		@brief 增加三维点
		@param[in] xyz: 多个三维点
		@param[in] normal: 三维点法向
		@param[in] param: 三维点纹理坐标
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT bool addPolygon(pvector<GePoint3d> const &xyz, pvector<GeVec3d> const *normal = NULL, pvector<GePoint2d> const *param = NULL);
		
		/**
		@brief 沿向量拉伸polyface，并围合侧面
		@param[in] sweepVector: 拉伸向量
		@param[in] triangulateSides: 侧面是否三角化
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT bool sweepToSolid(GeVec3dCR sweepVector, bool triangulateSides);

		/**
		@brief 清空当前数据，从source拷贝所有数据
		*/
		P3DGEOMOBJECT_EXPORT void copyFrom(IPolyfacePipeOperatorCR source);
		P3DGEOMOBJECT_EXPORT bool addIfMatchedLayout(IPolyfacePipeOperatorCR source);

		/**
		@brief 根据设定的平滑参数，计算每个面上顶点的近似法向
		@param[in] maxSingleEdgeAngle: 最大单个二面角
		@param[in] triangulateSides: 最大累计二面角
		@param[in] markAllTransitionsVisible: 设为true时，当边连接的两个面法向不同是，显示该边
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT bool buildApproximateNormals(double maxSingleEdgeAngle = 0.2, double maxAccumulatedAngle = 0.3, bool markAllTransitionsVisible = true);
		
		/**
		@brief 计算纹理坐标
		@param[in] selector: 定位方式
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT bool buildPerFaceParameters(LocalCoordinateSelect selector);

		/**
		@brief 清除法向数据，并设置active状态
		*/
		P3DGEOMOBJECT_EXPORT void clearNormals(bool active);

		/**
		@brief 清除纹理坐标数据，并设置active状态
		*/
		P3DGEOMOBJECT_EXPORT void clearParameters(bool active);

		/**
		@brief 计算面法向
		*/
		P3DGEOMOBJECT_EXPORT bool buildPerFaceNormals();

		P3DGEOMOBJECT_EXPORT bool buildPerFaceFaceData();

		/**
		@brief 当边连接的面的二面角补角小于smoothAngle时，设置边隐藏
		@param[in] smoothAngle: 最大二面角
		*/
		P3DGEOMOBJECT_EXPORT bool setInvisibleEdges
			(
			double smoothAngle,                 
			GeVec3dCP silhouetteVector = nullptr
			);

		/**
		@brief 设置拓扑边界可见
		@param[in] preserveOtherVisibility: 是否保留其他可见边
		*/
		P3DGEOMOBJECT_EXPORT bool setTopologicalBoundariesVisible
			(
			bool preserveOtherVisibility 
			);

		/**
		@brief 设置所有边可见
		*/
		P3DGEOMOBJECT_EXPORT void setAllEdgesVisible();

		/**
		@brief 根据面片平面range拆分polyface
		@param[in] targetFaceCount: 拆分后polyface最大面片数，当小于1时，按照targetMeshCount个数拆分
		@param[in] targetMeshCount: 拆分得到的polyface个数，当小于2时，按照targetFaceCount设置个数拆分
		@param[out] submeshArray: 返回的各部分polyface
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT bool partitionByPlaneRange
			(
			size_t targetFaceCount,
			size_t targetMeshCount,
			pvector<PolyfaceHandlePtr> &submeshArray
			);

		/**
		@brief 根据面片顺序拆分polyface
		@param[in] targetFaceCount: 拆分后polyface最大面片数，当小于1时，按照targetMeshCount个数拆分
		@param[in] targetMeshCount: 拆分得到的polyface个数，当小于2时，按照targetFaceCount设置个数拆分
		@param[out] submeshArray: 返回的各部分polyface
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT bool partitionMaintainFaceOrder
			(
			size_t targetFaceCount,
			size_t targetMeshCount,
			pvector<PolyfaceHandlePtr> &submeshArray
			);
		/**
		@brief 根据连接关系拆分polyface
		@param[in] connectivityType: 0表示点连接关系，1表示边连接关系，2表示根据显示边拆分
		@param[out] blockedReadIndexArray: 返回的各部分polyface
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT bool partitionByConnectivity(int connectivityType, pvector<PolyfaceHandlePtr> &submeshArray);

		/**
		@brief 根据面片平面range拆分polyface
		@param[in] targetFaceCount: 拆分后polyface最大面片数，当小于1时，按照targetMeshCount个数拆分
		@param[in] targetMeshCount: 拆分得到的polyface个数，当小于2时，按照targetFaceCount设置个数拆分
		@param[out] blockedReadIndexArray: 返回的各部分查询序号，每个部分通过-1分隔
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT bool partitionByPlaneRange
			(
			size_t targetFaceCount,
			size_t targetMeshCount,
			pvector<ptrdiff_t> &blockedReadIndexArray
			);

		/**
		@brief 根据面片顺序拆分polyface
		@param[in] targetFaceCount: 拆分后polyface最大面片数，当小于1时，按照targetMeshCount个数拆分
		@param[in] targetMeshCount: 拆分得到的polyface个数，当小于2时，按照targetFaceCount设置个数拆分
		@param[out] blockedReadIndexArray: 返回的各部分查询序号，每个部分通过-1分隔
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT bool partitionMaintainFaceOrder
			(
			size_t targetFaceCount,
			size_t targetMeshCount,
			pvector<ptrdiff_t> &blockedReadIndexArray
			);
		/**
		@brief 根据连接关系拆分polyface
		@param[in] connectivityType: 0表示点连接关系，1表示边连接关系，2表示交叉未绘制的边
		@param[out] blockedReadIndexArray: 返回的各部分查询序号，每个部分通过-1分隔
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT bool partitionByConnectivity(int connectivityType, pvector<ptrdiff_t> &blockedReadIndexArray);

		/**
		@brief 根据拆分的readindex获取拆分的polyface
		@param[in] blockedReadIndex: 拆分的readindex
		@param[out] submeshArray: 拆分的polyface
		@return 是否成功
		*/
		P3DGEOMOBJECT_EXPORT bool copyPartitions
			(
			pvector<ptrdiff_t> &blockedReadIndex,
			pvector<PolyfaceHandlePtr> &submeshArray
			);
		static P3DGEOMOBJECT_EXPORT void selectBlockedIndices
			(
			pvector<ptrdiff_t> const &blockedReadIndex,
			pvector<ptrdiff_t> const &selectedReadIndex,
			bool keepIfSelected,
			pvector<ptrdiff_t> &blockedReadIndexOut
			);
		P3DGEOMOBJECT_EXPORT bool getMaxSingleFacetParamLength(GeVec2dR uvLength);
		P3DGEOMOBJECT_EXPORT bool getMaxSingleFacetLocalXYLength(GeVec2dR xySize);

		/**
		@brief 获取所有可见轮廓
		@param[out] numOpen: 开放轮廓数
		@param[out] numClosed: 闭合轮廓数
		@return 所有可见轮廓集合l .
		*/
		P3DGEOMOBJECT_EXPORT GeCurveArrayPtr getBoundaryStrings(size_t &numOpen, size_t &numClosed);
		P3DGEOMOBJECT_EXPORT void  fillMissingIndexArrays();

	};
}


#endif