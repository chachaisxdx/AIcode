/*!
* Copyright (C), 2019-2028, Beijing GLory PKPM Tech. Co., Ltd.
* @file BPEntityUtil.h
* @author GLory
* @date 三月 2020
* @note
*/

#ifndef BP_BPData_BPEntityUtil_H
#define BP_BPData_BPEntityUtil_H

namespace BIMBase {
    namespace Core
    {
        /**
        @brief  无限线参数
        @date 创建日期:2022-01-26
        */
        struct BPInifiteLineParam
        {
            BPInifiteLineParam()
            {
                startPoint = { 0 };
                endPoint = { 0 };
                infiniteStartDir = true;
                infiniteEndDir = true;
                memset(&symbo, 0x00, sizeof(BPSymbology));
                dTransparency = 0.0;
            }
            p3d::GePoint3d      startPoint;
            p3d::GePoint3d      endPoint;
            bool                infiniteStartDir;
            bool                infiniteEndDir;
            BPSymbology         symbo;
            double              dTransparency;
        };
        typedef const BPInifiteLineParam& BPInifiteLineParamCR;

        /**
        @brief  实体工具类
        @details  实体检索，查询，编辑等通用功能
        @date 创建日期:2021-08-02
        */
        class BPEntityUtil
        {
        public:
            /**
            @brief 根据空间范围查询实体
            @details 查询指定工程文件中在指定空间范围内的实体
            @param[out] BPEntityArrayR entities: 符合查询条件的实体集
            @param[in] p3d::GeRange3dCR range: 指定查询的空间范围
            @param[in] BPProjectCR project: 指定的工程文件
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntitiesByRange(BPEntityArrayR entities, p3d::GeRange3dCR range, BPProjectCR project);
            
            /**
            @brief 根据空间范围查询指定数据类型实体
            @details 查询指定工程文件中在指定空间范围内的实体，实体关联的数据类型符合指定的classId
            @param[out] BPEntityArrayR entities: 符合查询条件的实体集
            @param[in] p3d::GeRange3dCR range: 指定查询的空间范围
            @param[in] BPProjectCR project: 指定的工程文件
            @param[in] PClassId classId: 指定的关联数据的类型Id,如果为INVALID_CLASS_ID则不进行查询并且返回ERROR
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntitiesByRange(BPEntityArrayR entities, p3d::GeRange3dCR range, BPProjectCR project, PClassId classId);

            /**
            @brief 根据空间范围查询实体
            @details 查询指定工程文件中在指定空间范围内的实体
            @param[out] pset<BPEntityId> &entityIdSet: 符合查询条件的实体Id集合
            @param[in] p3d::GeRange3dCR range: 指定查询的空间范围
            @param[in] BPProjectCR project: 指定的工程文件
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntitiesByRange(::p3d::pset<BPEntityId> &entityIdSet, p3d::GeRange3dCR range, BPProjectCR project);
            
            /**
            @brief 根据空间范围查询指定数据类型实体
            @details 查询指定工程文件中在指定空间范围内的实体，实体关联的数据类型符合指定的classId
            @param[out] pset<BPEntityId> &entityIdSet: 符合查询条件的实体Id集合
            @param[in] p3d::GeRange3dCR range: 指定查询的空间范围
            @param[in] BPProjectCR project: 指定的工程文件
            @param[in] PClassId classId: 指定的关联数据的类型Id,如果为INVALID_CLASS_ID则不进行查询并且返回ERROR
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntitiesByRange(::p3d::pset<BPEntityId> &entityIdSet, p3d::GeRange3dCR range, BPProjectCR project, PClassId classId);

			/**
			@brief 根据空间范围查询指定数据类型实体
			@details 查询指定工程文件的指定Model中，XY平面区域在Z轴方向上拉伸体形成的三维空间，包含和穿过的实体集合
			@param[out] pset<BPEntityId> &entityIdSet: 符合查询条件的实体Id集合
			@param[in] BPProjectCR project: 指定的工程文件
			@param[in] PModelId const& modelId：指定查询的ModelId
			@param[in] GeCurveArrayCR curve: 投影到XY平面的区域
			@param[in] double high: Z方向的拉伸长度
			@param[in] bool isOverlapMode: 查询结果是否包含与查询区域部分重叠的实体, true:包含 false:不包含.			
			@param[in] bool bIncludeUndisplayedEntity: 查询结果是否包含通过右键菜单隐藏的(不包含通过图层、显示条件等方式隐藏的)实体. true:会将隐藏的实体也查询出来，false:不查询隐藏的实体.
			@param[in] bool bIncludeModelLinkEntity: 查询结果是否包含由modelId指定的model下modelLink的实体. true:包含，false:不包含.
			@return 查询操作状态标识
			- ::p3d::P3DStatus::SUCCESS 成功
			- ::p3d::P3DStatus::ERROR 失败
			* @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
			*/
			BIMBASEAPI_EXPORT static ::p3d::P3DStatus		getEntitiesByCurveArray(::p3d::pset<BPEntityId>& entityIdSet, BPProjectR project, PModelId modelId, 
                                                                                    P3D_NAMESPACE_NAME::GeCurveArrayCR curveArray, double high, bool isOverlapMode = true, 
                                                                                    bool bIncludeUndisplayedEntity = false, bool bIncludeModelLinkEntity = false);


            /**
            @brief 查询Model中实体
            @details 查询指定工程文件中在指定Model中的实体
            @param[out] BPEntityArrayR entities: 符合查询条件的实体集
            @param[in] BPProjectCR project: 指定的工程文件
            @param[in] PModelId const& modelId: 指定查询的ModelId
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntitiesOfModel(BPEntityArrayR entities, BPProjectCR project, PModelId const& modelId);

            /**
            @brief 查询Model中实体
            @details 查询指定工程文件中在指定Model中的实体，实体在指定空间范围内
            @param[out] BPEntityArrayR entities: 符合查询条件的实体集
            @param[in] p3d::GeRange3dCR range: 指定查询的空间范围
            @param[in] BPProjectCR project: 指定的工程文件
            @param[in] PModelId const& modelId: 指定查询的ModelId
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntitiesOfModel(OUT BPEntityArrayR entities, p3d::GeRange3dCR range, BPProjectCR project, PModelId const& modelId);

            /**
            @brief 查询Model中实体
            @details 查询指定工程文件中在指定Model中的实体
            @param[out] pset<BPEntityId> &entityIdSet: 符合查询条件的实体Id集合
            @param[in] BPProjectCR project: 指定的工程文件
            @param[in] PModelId const& modelId: 指定查询的ModelId
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntitiesOfModel(::p3d::pset<BPEntityId> &entityIdSet, BPProjectCR project, PModelId const& modelId);
            
            /**
            @brief 查询当前视口的Model中实体
            @details 查询指定工程文件在当前视口的Model中的实体
            @param[out] BPEntityArrayR entities: 符合查询条件的实体集
            @param[in] p3d::GeRange3dCR range: 指定查询的空间范围
            @param[in] BPProjectCR project: 指定的工程文件
            @param[in] PModelId const& modelId: 指定查询的ModelId
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntitiesOfModelInCurrentView(BPEntityArrayR entities, BPProjectR project, PModelId const& modelId);

            /**
            @brief 查询满足指定条件的实体
            @details 根据指定的条件查询相应的实体,此函数执行时会首先对outEntities参数做清空处理
            @param[out] BPEntityArrayR entities: 符合查询条件的实体集
            @param[in] p3d::GeRange3dCR range: 指定查询的空间范围
            @param[in] PModelId const& modelId: 指定查询的ModelId
            @param[in] Utf8StringCR schemaName: 指定关联数据类型的schemaName
            @param[in] Utf8StringCR className: 指定关联数据类型的className
            @param[in] BPProjectCR project: 指定的工程文件
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            无效的ModelId返回ERROR
            无效的schemaName或className返回ERROR
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus         getEntities(OUT BPEntityArrayR outEntities, p3d::GeRange3dCR range, PModelId const& modelId, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className, BPProjectCR project);

            /**
            @brief 查询满足指定条件的实体
            @details 查询指定工程文件在指定Model中的特定关联数据类型的实体,此函数执行时会首先对outEntities参数做清空处理
            @param[out] BPEntityArrayR entities: 符合查询条件的实体集
            @param[in] BPProjectCR project: 指定的工程文件
            @param[in] PModelId const& modelId: 指定查询的ModelId
            @param[in] Utf8StringCR schemaName: 指定关联数据类型的schemaName
            @param[in] Utf8StringCR className: 指定关联数据类型的className
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            无效的ModelId返回ERROR
            无效的schemaName或className返回ERROR
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntities(BPEntityArrayR entities, BPProjectCR project, PModelId const& modelId, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className);
            
            /**
            @brief 查询满足指定条件的实体
            @details 查询指定工程文件中特定关联数据类型的实体,,此函数执行时会首先对outEntities参数做清空处理
            @param[out] BPEntityArrayR entities: 符合查询条件的实体集
            @param[in] BPProjectCR project: 指定的工程文件
            @param[in] Utf8StringCR schemaName: 指定关联数据类型的schemaName
            @param[in] Utf8StringCR className: 指定关联数据类型的className
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            无效的schemaName或className返回ERROR
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntities(BPEntityArrayR entities, BPProjectCR project, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className);
            
            /**
            @brief 查询满足指定条件的实体
            @details 查询视口中指定空间两点连线穿过的实体
            @param[out] BPEntityArrayR entities: 符合查询条件的实体集
            @param[in] GePoint3dCR startPoint: 线段起点
            @param[in] GePoint3dCR endPoint: 线段终点
            @param[in] BPViewportR viewPort: 指定视口
			@param[in] bool isOverlapMode: 查询结果是否包含与查询区域部分重叠的实体, true:包含 false:不包含.
			@return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntities(BPEntityArrayR entities, p3d::GePoint3dCR startPoint, p3d::GePoint3dCR endPoint, BPViewportR viewPort, bool isOverlapMode = true);
            
            /**
            @brief 查询满足指定条件的实体（不查询ModelLink中的实体）
            @details 查询视口中指定点集连接成的多边形包含和穿过的实体
            @param[out] BPEntityArrayR entities: 符合查询条件的实体集
            @param[in] BPViewportR viewPort: 指定视口
            @param[in] pvector<p3d::GePoint3d> const& shapePoints: 空间点集
			@param[in] bool isOverlapMode: 查询结果是否包含与查询区域部分重叠的实体, true:包含 false:不包含.
			@return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntities(BPEntityArrayR entities, BPViewportR viewPort, p3d::pvector<p3d::GePoint3d> const& shapePoints, bool isOverlapMode = true);

            /**
            @brief 查询满足指定条件的实体
            @details 查询指定工程文件中特定关联数据类型的实体,,此函数执行时会首先对outEntities参数做清空处理
            @param[out] pset<BPEntityId> &entityIdSet: 符合查询条件的实体Id集合
            @param[in] BPProjectCR project: 指定的工程文件
            @param[in] Utf8StringCR schemaName: 指定关联数据类型的schemaName
            @param[in] Utf8StringCR className: 指定关联数据类型的className
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            无效的schemaName或className返回ERROR
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntities(::p3d::pset<BPEntityId> &entityIdSet, BPProjectCR project, ::p3d::Utf8StringCR schemaName, ::p3d::Utf8StringCR className);
            
            /**
            @brief 查询满足指定条件的实体
            @details 查询指定工程文件在指定Model中的特定关联数据类型的实体,此函数执行时会首先对outEntities参数做清空处理
            @param[out] pset<BPEntityId> &entityIdSet: 符合查询条件的实体Id集合
            @param[in] BPProjectCR project: 指定的工程文件
            @param[in] PModelId const& modelId: 指定查询的ModelId
            @param[in] Utf8StringCR schemaName: 指定关联数据类型的schemaName
            @param[in] Utf8StringCR className: 指定关联数据类型的className
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            无效的ModelId返回ERROR
            无效的schemaName或className返回ERROR
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntities(::p3d::pset<BPEntityId> &entityIdSet, BPProjectCR project, PModelId const& modelId, ::p3d::Utf8StringCR schemaName, ::p3d::Utf8StringCR className);

            /**
            @brief 获取视口中可见实体
            @details 查询指定视口中全部可见实体
            @param[out] BPEntityArrayR entities: 符合查询条件的实体集
            @param[in] BPViewportR viewPort: 指定视口
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getAllVisibleEntities(BPEntityArrayR entities, BPViewportCR viewPort);
            
            /**
            @brief 获取视口中可见实体
            @details 查询视口指定指定空间范围内全部可见实体
            @param[out] BPEntityArrayR entities: 符合查询条件的实体集
            @param[in] BPViewportR viewPort: 指定视口
            @param[in] p3d::GeRange3dCR testRange: 指定查询的空间范围
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getAllVisibleEntities(BPEntityArrayR entities, BPViewportCR viewPort, p3d::GeRange3dCR testRange);
            
            /**
            @brief 获取视口中可见实体
            @details 查询指定视口中全部可见实体
            @param[out] pset<BPEntityId> &entityIdSet: 符合查询条件的实体Id集合
            @param[in] BPViewportR viewPort: 指定视口
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0.
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getAllVisibleEntities(::p3d::pset<::BIMBase::BPEntityId> &entities, BPViewportCR viewPort);

            // ____<pkpm_inner_begin>____
            /**
             @brief 查询数据对象关联实体,如果指定的模型空间内有多个图形实体,则只返回查到的第一个.
             @details 获取关联指定数据对象的实体Id
             @param[in] BPProjectCR project: 指定的工程文件
             @param[in] BPDataKeyCR dataKey: 指定的数据对象Key
             @param[in] PModelId const& modelId: 数据对象关联实体所在的ModelId
             @return 关联数据对象的实体Id
             * @note  需判断返回BPEntityId的有效性
             @deprecated 已废弃，用getEntitiesWithData(::p3d::pset<BPEntityId> &entityIdSet, BPProjectCR project, BPDataKeyCR dataKey)接口代替
             */
            BIMBASEAPI_EXPORT static BPEntityId             getPrimaryEntityWithData(BPProjectCR project, BPDataKeyCR dataKey, PModelId const& modelId);

            /**
            @brief 查询满足条件的图素（查询指定modelRef列表中的实体）
            @param[out] elements: 查询到的图素
            @param[in] viewPort: 搜索的视口
            @param[in] shapePoints: 选择框的角点
            @param[in] modelRefArray: 要搜索的model的列表，可写入BPModel和BPModelLink
			@param[in] bool isOverlapMode: 查询结果是否包含与查询区域部分重叠的实体, true:包含 false:不包含.
			@return 程序执行结果
            - enERROR  查询失败
            - enSUCCESS 查询成功
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus getEntities(BPEntityArrayR elements, BPViewportR viewPort, p3d::pvector<p3d::GePoint3d> const& shapePoints, BPModelArrayCR modelRefArray, bool isOverlapMode = true);

            // ____<pkpm_inner_end>____

            /**
            @brief 查询数据对象关联实体
            @details 获取关联指定数据对象的实体Id
            @param[out] pset<BPEntityId> &entityIdSet: 符合查询条件的实体Id集合
            @param[in] BPProjectCR project: 指定的工程文件
            @param[in] BPDataKeyCR dataKey: 指定的数据对象Key
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  返回值为SUCCESS表示查询操作正常执行完成,查询结果的数目可能为0
            数据对象有可能关联不同Model中的多个实体
            */
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus       getEntitiesWithData(::p3d::pset<BPEntityId> &entityIdSet, BPProjectCR project, BPDataKeyCR dataKey);
            
            /**
            @brief 实体矩阵变换
            @param[in] BPEntityR entity: 实体引用
            @param[in] GeTransformCR transform: 变换矩阵常引用
            @param[in] bool isSave: 是否保存实体数据
            @return 实体显示的图形对象
            @see BPGraphics
            @note isSave = true时，此操作会保存进行矩阵变换后的实体数据
            isSave = false时，实体数据不会变化，返回的BPGraphics为实体进行矩阵变换后的图形数据，一般用于动态显示时临时绘制变换图形
            */
            BIMBASEAPI_EXPORT static BPGraphicsPtr          transformEntity(BPEntityR entity, p3d::GeTransformCR transform, bool isSave);
            /*
            // classFullName&&classId
            BIMBASEAPI_EXPORT static bool       getClassIdByClassFullName(BPProjectR project, PClassIdR classId, ::p3d::Utf8StringCR classFullName);
            BIMBASEAPI_EXPORT static PClassId   getClassIdByClassFullName(BPProjectR project, ::p3d::Utf8StringCR classFullName);
            BIMBASEAPI_EXPORT static bool       getClassIdBySchemaNameAndClassName(BPProjectR project, PClassIdR classId, ::p3d::Utf8StringCR schemaName, ::p3d::Utf8StringCR className);
            BIMBASEAPI_EXPORT static PClassId   getClassIdBySchemaNameAndClassName(BPProjectR project, ::p3d::Utf8StringCR schemaName, ::p3d::Utf8StringCR className);
            BIMBASEAPI_EXPORT static bool       getClassFullNameByClassId(::p3d::Utf8StringR classFullName, PClassId classId, BPProjectCR project);
            */
            BIMBASEAPI_EXPORT static PClassId               getEntityClassId(BPProjectCR project, const BPEntityId& entityId);

            // ____<pkpm_inner_begin>____

            /**
            @brief 删除实体
            @details 根据ModelId和PEntityId删除对应实体
            @param[in] PEntityId entityId:
            @param[in] const PModelId modelId:
            @param[in] BPProjectCR project: 指定的工程文件
            @return 查询操作状态标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            * @note  此操作不删除实体关联的数据对象
            */
            //PEntityId is different with BPEntityId, will be deprecated,replaced with BPEntity::deleteFromModel
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus deleteEntity(BPEntityId entityId, BPProjectCR project);

            // will be deprecated
            BIMBASEAPI_EXPORT static BPGraphicsPtr transformEntity(BPEntityR entity, p3d::GeTransformCR transform, bool isSaveGraph, bool isSaveData);

            /**
            @brief 实体组合
            @details 将实体集中实体组合成一个图块实体
            @param[in] BPEntityArrayR entities: 被组合的实体集
            @return 被组合后的实体指针
            @note 生成的图块类型为常规独立图块,图块基点为实体集中第一个实体包围盒的左下角点,图块名称为"p3dEntityList"
            */
            // 暂为专业内部使用,后续提供明确的图块创建接口,或根据需求提供实体图形合并接口(结果为扩展类型)
            BIMBASEAPI_EXPORT static BPEntityPtr makeBlock(BPEntityArrayCR entities);

            /**
            @brief 创建无限线图形实体
            @details 起终点只标识方向，与具体数值无关
            @param[in] startPoint : 起点
            @param[in] startPoint : 终点
            @param[in] infiniteStartDir : 起点方向无限长
            @param[in] infiniteEndDir : 终点方向无限长
            @param[in] symbo : 显示特性
            @return 无限线图形实体
            */
            BIMBASEAPI_EXPORT static BPEntityPtr createInfiniteLine(BPModelR model, BPInifiteLineParamCR param);

			//拷贝entity，model为null时在entity所在model拷贝
            BIMBASEAPI_EXPORT static p3d::P3DStatus	copyEntity(BPEntityCR srcEntity, BPEntityPtr& destEntity, BPModelCP destModel = nullptr);

            //协同使用这三个接口
            // 获取entity的数据大小。目前仅支持标注、填充等内核图形实体，后续可一统一支持。暂时不对外提供
            BIMBASEAPI_EXPORT static p3d::P3DStatus     getEntityDataSize(BPEntityCR entity, OUT Int32& nEntitySize);
            // 序列化entity：读取entity的二进制数据块,参数nEntitySize的值通过getEntityDataSize得到.
            BIMBASEAPI_EXPORT static p3d::P3DStatus     readEntityData(BPEntityCR entity, OUT void* entityDataBuffer, const Int32 nEntitySize);
            // 反序列化entity: 返回未保存的P3DEntity实例，如需保存，则要调用addToModel.
            BIMBASEAPI_EXPORT static BPEntityPtr       writeDataToEntity(const void* entityDataBuffer, const Int32 nEntitySize, BPModelBaseP modelBase);

            // ____<pkpm_inner_end>____

        };
    }
}

#endif // BP_BPData_BPEntityUtil_H
