/*!
* Copyright (C), 2019-2028, Beijing GLory PKPM Tech. Co., Ltd.
* @file BPDataUtil.h
* @author GLory
* @date 三月 2020
* @note
*/
#ifndef BP_BPData_BPDataUtil_H
#define BP_BPData_BPDataUtil_H



namespace BIMBase {
    namespace Core
    {
        typedef p3d::pmultimap<::p3d::PString, BPDataId> BPDataKeyMultiMap;
        typedef BPDataKeyMultiMap::value_type        BPDataKeyMultiMapPair;
        typedef BPDataKeyMultiMap::iterator          BPDataKeyMultiMapIterator;
        typedef BPDataKeyMultiMap::const_iterator    BPDataKeyMultiMapConstIterator;


        enum class BPDataFlag : uint8_t
        {
            enNormal = 0,
            enArray = 1,
            enReserve = 2
        };

        /**
        @brief  BPData工具类
        @details  用于处理于BPData相关的逻辑，内部均为静态接口，不实例化
        @date 创建日期:2021-07-29
        */
        class BPDataUtil
        {
        public:
            /**
            @brief 构建级协同环境下，根据下载的二进制构建P3DData
            */
            BIMBASEAPI_EXPORT static BPDataPtr createBPDataByByteArray(BPDataKeyCR dataKey, ::p3d::PStringCR schemaName, ::p3d::PStringCR className, BPProjectCR project, const BYTE* data, Int32 dataSize);
            /**
            @brief 构建级协同环境下，根据P3DData生成要上传数据的二进制数组
            */
            BIMBASEAPI_EXPORT static void* getByteArrayByBPData(BPDataKeyCR dataKey, BPProjectCR project, Int32& dataSize);
            
            /**
            @brief 创建指定类型的BPData
            @param[in]  project：工程文件；
            schemaName；
            className；
            flag：数据标识
            @return BPData智能指针
            */
            BIMBASEAPI_EXPORT static BPDataPtr          createDataByName(BPProjectCR project, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className, BPDataFlag flag);

            /**
            @brief 判断某个类型是否从属于某个基类型
            @param[in]  baseSchemaName：基类schemaName；
            baseClassName：基类className；
            derivedSchemaName：派生类shcemaName；
            derivedClassName：派生类className；
            project：工程文件
            @return 布尔值
            - true 相同或属于
            - false 不同且不属于
            */
            BIMBASEAPI_EXPORT static bool               isTypeofClass(p3d::Utf8StringCR baseSchemaName, p3d::Utf8StringCR baseClassName, p3d::Utf8StringCR derivedSchemaName, p3d::Utf8StringCR derivedClassName, BPProjectCR project);

            /**
            @brief 判断某个类型是否从属于某个基类型
            @param[in]  baseClassId：基类classId；
            derivedClassId：派生类classId；
            project：工程文件
            @return 布尔值
            - true 相同或属于
            - false 不同且不属于
            */
            BIMBASEAPI_EXPORT static bool               isTypeofClass(PClassId const& baseClassId, PClassId const& derivedClassId, BPProjectCR project);

            /**
            @brief 删除指定类型的BPData
			@details 如果有关联的BPModelElement或者BPModelElementLink数据，则不能通过此接口直接删除data，返回ERROR.应该通过BPModelElement或者BPModelElementLink相关的接口删除(如deleteFromProject).
			@param[in]  schemaName；
            className；
            project：工程文件
            @return P3DStatus状态码
            - SUCCESS 删除成功
            - ERROR 删除失败
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus     deleteDatasByClassName(p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className, BPProjectR project);

            /**
            @brief 删除指定的数据,如果存在绑定的entity数据则不删除,返回失败.
            @details 如果有关联的BPModelElement或者BPModelElementLink数据，则不能通过此接口直接删除data，返回ERROR.应该通过BPModelElement或者BPModelElementLink相关的接口删除(如deleteFromProject).
			@param[in]  dataKey：BPData的key值,
            @param[in]  project：工程文件
            @return P3DStatus状态码
            - SUCCESS 删除成功
            - ERROR 删除失败
            @note 因为图形基于数据生成的考虑,如果存在绑定的entity数据,则不允许删除数据.可以先删除图形数据或者解除绑定关系再进行数据的删除操作.
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus     deleteDataByKey(BPDataKeyCR dataKey, BPProjectCR project);

            /**
            @brief 建立绑定关系
            @param[in]  entityId：被绑定BPEntity的id；
            dataKey：被绑定BPData的key值；
            project：entityId，dataKey所在的工程文件
            @return P3DStatus状态码
            - SUCCESS 绑定成功
            - ERROR 绑定失败
            @see p3d::P3DStatus removeBindingEntityFromData(BPEntityId& entityId, BPDataKeyCR dataKey, BPProjectP project)
            @note entityId并非输出参数
            @warning 不能在不同文件中绑定，entityId，dataKey必须来自于project所指的文件
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus     bindEntityToData(BPEntityId& entityId, BPDataKeyCR dataKey, BPProjectP project);

            /**
            @brief 解除绑定关系
            @param[in]  entityId：被绑定BPEntity的id；
            dataKey：被绑定BPData的key值；
            project：entityId，dataKey所在的工程文件
            @return P3DStatus状态码
            - SUCCESS 解除成功
            - ERROR 解除失败
            @see p3d::P3DStatus bindEntityToData(BPEntityId& entityId, BPDataKeyCR dataKey, BPProjectP project)
            @warning 不能在不同文件中解除绑定，entityId，dataKey必须来自于project所指的文件
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus     removeBindingEntityFromData(BPEntityId& entityId, BPDataKeyCR dataKey, BPProjectP project);

            /**
            @brief 获取指定BPData上绑定的所有entityId
            @param[out] entityIdSet：entityId数组
            @param[in]  dataKey：指定BPData的key值；
            project：工程文件
            @return P3DStatus状态码
            - SUCCESS 获取成功
            - ERROR 获取失败
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus     getAllBindingEntityFromData(std::set<BPEntityId>& entityIdSet, BPDataKeyCR dataKey, BPProjectP project);

            /**
            @brief 根据指定信息查询BPData
            @param[out] datas：BPData的列表
            @param[in]  schemaName；
            className；
            keyword：属性名称；
            value ：属性值；
            project：工程文件；
            compareOp：条件查询选项（默认为相同）
            @return P3DStatus状态码
            - SUCCESS 获取成功
            - ERROR 获取失败
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus     getDataFromSchemaNameWhere(BPDataListR datas, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className,
                                                                    p3d::WCharCP keyword, BPValueCR value, BPProjectCR project, BPCompareOp compareOp = BPCompareOp::enEQ);

            /**
            @brief 根据指定信息快速查询BPData
            @param[out] dataKeys：BPDataKey的列表
            @param[in]  schemaName；
            className；
            keyword：属性名称；
            value ：属性值；
            project：工程文件；
            compareOp：条件查询选项（默认为相同）
            @return P3DStatus状态码
            - SUCCESS 获取成功
            - ERROR 获取失败
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus     getDataFromSchemaNameWhere_Quick(std::vector<BPDataKey>& dataKeys, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className,
                p3d::WCharCP keyword, BPValueCR value, BPProjectCR project, BPCompareOp compareOp = BPCompareOp::enEQ);

            /**
            @brief 根据key值查询BPData
            @param[in]  dataKey：BPData的key值；
            project：工程文件
            @return BPData智能指针
            */
            BIMBASEAPI_EXPORT static BPDataPtr          getDataByKey(BPDataKeyCR dataKey, BPProjectCR project);

            /**
           @brief 根据key值查询此数据是否存在
           @param[in]  dataKey：BPData的key值；
           project：工程文件
           @return true： 有数据；false ：没有数据
           */
            BIMBASEAPI_EXPORT static bool          checkDataExistByKey(BPDataKeyCR dataKey, BPProjectCR project);

            /**
            @brief 获取BPEntity绑定的BPData
            @param[in] entity：图形实体
            @return BPData智能指针
            */
            BIMBASEAPI_EXPORT static BPDataPtr          getDataOnEntity(BPEntityCR entity);

            /**
            @brief 获取BPEntity绑定的BPData的key值
            @param[in] entity：图形实体
            @return BPDataKey
            */
            BIMBASEAPI_EXPORT static BPDataKey          getDataKeyOnEntity(BPEntityCR entity);


            /**
            @brief 获取BPDataId
            @param[in]  project：工程文件；
            entityId
            @return BPDataId
            */
            BIMBASEAPI_EXPORT static BPDataId           getDataId(BPProjectCR project, const ::BIMBase::BPEntityId& entityId);

            /**
            @brief 获取BPDataKey
            @param[in]  project：工程文件；
            entityId
            @return BPDataKey
            */
            BIMBASEAPI_EXPORT static BPDataKey                 getDataKeyByEntityId(BPProjectCR proj, const BPEntityId& p3dId);

            /**
            @brief 根据schemaName和className查询BPData
            @param[out] datas：BPData的列表
            @param[in]  schemaName；
            className；
            project：工程文件
            @return P3DStatus
            - SUCCESS 获取成功
            - ERROR 获取失败
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus     getDataFromSchemaName(BPDataListR datas, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className, BPProjectCR project);

            /**
            @brief 查询BPData
            @param[in]  project：工程文件；
            dataId；
            schemaName；
            className；
            @return BPData智能指针
            */
            BIMBASEAPI_EXPORT static BPDataPtr          getBPData(BPProjectCR project, ::BIMBase::BPDataId dataId, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className);


            // ____<pkpm_inner_begin>____
            // @deprecated, add for backward compatibility (23/05/2020)        

            /**
            @brief 根据指定信息查询BPData
            @param[in]  project：工程文件；
            schemaName；
            className；
            guid：Guid属性值
            @return BPData智能指针
            @warning
            */
            BIMBASEAPI_EXPORT static BPDataPtr getDataByGuid(BPProjectCR project, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className, p3d::Utf8StringCR guid);


            /**
            @brief 获取BPDataId
            @param[in]  project：工程文件；
            entity
            @return BPDataId
            @warning        //pkpminner
            */
            BIMBASEAPI_EXPORT static BPDataId getDataId(BPProjectCR project, BPEntityCR entity);

            /**
            @brief 拆分classFullName
            @param[out] schemaName，className
            @param[in] classFullName
            @return P3DStatus
            - SUCCESS 拆分成功
            - ERROR 拆分失败
            @warning            //pkpminner
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus parseClassFullName(p3d::Utf8StringR schemaName, p3d::Utf8StringR className, p3d::Utf8StringCR classFullName);

            /**
            @brief xxx
            @return P3DStatus
            - SUCCESS 获取成功
            - ERROR 获取失败
            @warning        //pkpminner
            @deprecated 用P3DGlobalVariableManager::generateGuidString()代替
            */
            BIMBASEAPI_EXPORT static p3d::Utf8String generateGuidString();

            /**
            @brief 多条件查询BPData
            @param[out] datas：BPData的列表
            @param[in] project：工程文件；schemaName；className；conditions：条件集合
            @return P3DStatus
            - SUCCESS 获取成功
            - ERROR 获取失败
            @warning        //pkpminner
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus queryDataByCondition(std::vector<BPDataPtr>& datas, BPProjectCR project, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className,
                std::vector<std::tuple<p3d::Utf8String, BPValue, BPCompareOp>>& conditions);

            //协同使用
            BIMBASEAPI_EXPORT static p3d::P3DStatus getAllDataFromProject(BPDataListR datas, BPProjectCR project);
            BIMBASEAPI_EXPORT static p3d::P3DStatus getAllDataByDomains(BPDataListR datas, BPProjectCR project, const std::vector<UInt16>& domains);
            BIMBASEAPI_EXPORT static p3d::P3DStatus getAllRelationAndSourceTargetKeys(p3d::pvector<BPDataKey>& relationshipKeys, p3d::pvector<BPDataKey>& sourceDataKeys, p3d::pvector<BPDataKey>& targetDataKeys, BPProjectCR project);

            BIMBASEAPI_EXPORT static p3d::P3DStatus getDataFromSchemaName(BPDataListR datas, ::p3d::PStringCR schemaName, ::p3d::PStringCR className, BPProjectCR project);
            BIMBASEAPI_EXPORT static p3d::P3DStatus getDataFromSchemaNameWhere(BPDataListR datas, ::p3d::PStringCR schemaName, ::p3d::PStringCR className, p3d::WCharCP keyword,
                BPValueCR value, BPProjectCR project, BPCompareOp compareOp = BPCompareOp::enEQ);


            BIMBASEAPI_EXPORT static p3d::P3DStatus getDataFromClassId(BPDataListR datas, p3d::Utf8StringCR classId, BPProjectCR project);

            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getCurveVectorFromECValue(p3d::GeCurveArrayPtr& curve, BPValueCR curveValue);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setCurveVectorToECValue(BPValueR curveValue, p3d::GeCurveArrayPtr const curve);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getPrimitiveCurveValue(p3d::IGeCurveBasePtr& curve, BPValueCR curveValue);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setPrimitiveCurveValue(BPValueR curveValue, p3d::IGeCurveBaseCR curve);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setIntToBytes(const int& i, byte* bytes, int size = 4);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getIntFromBytes(int& i, byte* bytes, int size = 4);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setIntToBytes(const int& i, std::vector<byte>& bytes);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getIntFromBytes(int& i, const std::vector<byte>& bytes);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getDoubleFromBytes(double& d, std::vector<byte>& bytes);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setDoubleToBytes(const double& d, std::vector<byte>& bytes);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getSizeFromBytes(size_t& s, std::vector<byte>& bytes);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setSizeToBytes(const size_t& s, std::vector<byte>& bytes);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setUIntToBytes(const unsigned int& i, byte* bytes, int size = 4);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getUIntFromBytes(unsigned int& i, byte* bytes, int size = 4);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getSymbologyFromBytes(BPSymbology& sym, const std::vector<byte>& memData);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setSymbologyToBytes(std::vector<byte>& memData, BPSymbology const& sym);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getPrimitiveCurveFromBytes(p3d::IGeCurveBasePtr& curve, const std::vector<byte>& memData);//Deprecated
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setPrimitiveCurveToBytes(std::vector<byte>& memData, p3d::IGeCurveBaseCR curve);//Deprecated
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getCurveVectorFromBytes(p3d::GeCurveArrayPtr& curveVector, const std::vector<byte>& memData);//Deprecated
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setCurveVectorToBytes(std::vector<byte>& memData, p3d::GeCurveArrayCR const curve);//Deprecated
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getPointsFromBytes(std::vector<p3d::GePoint3d>& points, const std::vector<byte>& memData);//Deprecated
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setPointsToBytes(std::vector<byte>& memData, const p3d::pvector<p3d::GePoint3d>& pts);//Deprecated
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getPoint3DFromBytes(p3d::GePoint3dR pt, const std::vector<byte>& bytes, int& offset);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setPoint3DToBytes(p3d::GePoint3dCR pt, std::vector<byte>& bytes);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus getVector3DFromBytes(p3d::GeVec3dR vect, const std::vector<byte>& bytes, int& offset);
            BIMBASEAPI_EXPORT static ::p3d::P3DStatus setVector3DToBytes(p3d::GeVec3dCR vect, std::vector<byte>& bytes);
            // ____<pkpm_inner_end>____
        };
    }
}
#endif//BP_BPData_BPDataUtil_H
