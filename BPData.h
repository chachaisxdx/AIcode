/*!
* Copyright (C), 2019-2028, Beijing GLory PKPM Tech. Co., Ltd.
* @file BPData.h
* @author GLory
* @date 三月 2020
* @note
*/

#ifndef BP_BPData_BPData_H
#define BP_BPData_BPData_H


namespace BIMBase {
    namespace Core
    {
        typedef p3d::pvector<BPDataClass> P3DDerivedClassList;
        typedef p3d::pvector<BPDataClass> P3DBaseClassList;
        typedef p3d::pvector<BPDataSchema> P3DSchemaList;
        typedef p3d::pvector<BPDataClass> P3DClassList;
        typedef p3d::pvector<BPDataProperty> BPDataPropertyList;

        /**
        @brief 领域数据定义属性
        @date 创建日期:2021-8-13
        */
        class BPDataProperty
        {
            friend class BPDataClass;
        public:
            BIMBASEAPI_EXPORT BPDataProperty();

            /**
            @brief 拷贝构造
            @param[in] from
            @note 浅拷贝
            */
            BIMBASEAPI_EXPORT BPDataProperty(BPDataPropertyCR from);

            BIMBASEAPI_EXPORT p3d::PString      getTypeName();

            BIMBASEAPI_EXPORT p3d::PStringCR    getPropertyName();

            BIMBASEAPI_EXPORT p3d::PStringCR    getDescription();

            BIMBASEAPI_EXPORT p3d::PStringCR    getDisplayLabel();

            BIMBASEAPI_EXPORT bool              isValid() const;

            BIMBASEAPI_EXPORT bool              isReadOnly();

            BIMBASEAPI_EXPORT bool              isPrimitiveType();

            BIMBASEAPI_EXPORT bool              isStructType();

            BIMBASEAPI_EXPORT bool              isArrayType();

            /**
            @brief 获取数据定义
            @param[out] dataClass：数据定义
            @return P3DStatus
            - SUCCESS 获取成功
            - ERROR 获取失败
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus                getClass(BPDataClassR dataClass) const;

            /**
            @brief 当前属性是Struct类型时获取相应的类定义
            @details 如果当前属性不是Struct类型，则返回ERROR
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus                getStructClass(BPDataClassR dataClass) const;
        private:

            void* m_imp;


        };

        /**
        @brief 领域数据定义
        @date 创建日期:2021-8-13
        */
        class BPDataClass
        {
            friend class BPDataProperty;
            friend class BPDataSchema;
            friend class BPSchemaManager;
            friend class BPData;
        public:

            BIMBASEAPI_EXPORT BPDataClass();

            /**
            @brief 拷贝构造
            @note 浅拷贝
            */
            BIMBASEAPI_EXPORT BPDataClass(BPDataClassCR from);

            BIMBASEAPI_EXPORT bool              isValid() const;

            BIMBASEAPI_EXPORT PClassId          getClassId() const;

            BIMBASEAPI_EXPORT p3d::PStringCR    getSchemaName() const;

            BIMBASEAPI_EXPORT p3d::PStringCR    getClassName() const;

            BIMBASEAPI_EXPORT p3d::PStringCR    getDescription() const;

            BIMBASEAPI_EXPORT p3d::PStringCR    getDisplayLabel() const;

            BIMBASEAPI_EXPORT p3d::P3DStatus    getSchema(BPDataSchemaR schema) const;

            /**
            @brief 获取派生类列表
            @param[out] derivedClassList：派生类列表
            @return P3DStatus
            - SUCCESS 获取成功
            - ERROR 获取失败
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        getDerivedClassList(P3DDerivedClassList& derivedClassList) const;

            /**
            @brief 获取基类列表
            @param[out] derivedClassList：派生类列表
            @return P3DStatus
            - SUCCESS 获取成功
            - ERROR 获取失败
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        getBaseClassList(P3DBaseClassList& baseClassList) const;

            /**
            @brief 判断当前对象是否为某类或其子类的数据对象
            @param[in] schemaName；className
            @return 布尔值
            - true 是
            - false 否，或参数有误
            */
            BIMBASEAPI_EXPORT bool                  isKindOf(p3d::WCharCP schemaName, p3d::WCharCP className) const;

            /**
            @brief 判断当前对象是否为某类或其子类的数据对象
            @param[in] classP：数据定义的指针
            @return 布尔值
            - true 是
            - false 否
            */
            BIMBASEAPI_EXPORT bool                  isKindOf(BPDataClassP classP) const;

            /**
            @brief 判断当前对象是否为关系类数据
            */
            BIMBASEAPI_EXPORT bool                  isRelationshipClass()const;

            /**
            @brief 获取源数据类型
            @param[out] sourceClass：源数据类型
            @return P3DStatus
            - SUCCESS 获取成功
            - ERROR 获取失败
            @note 仅用于关系类数据
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        getSourceClass(BPDataClassR sourceClass) const;

            /**
            @brief 获取目标数据类型列表
            @param[out] targetClassList：目标数据类型列表
            @return P3DStatus
            - SUCCESS 获取成功
            - ERROR 获取失败
            @note 仅用于关系类数据
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        getTargetClassList(P3DClassList& targetClassList) const;

            /**
            @brief 获取属性类型列表
            @param[out] propertyList：属性列表
            @return P3DStatus
            - SUCCESS 获取成功
            - ERROR 获取失败
            @note 仅用于领域数据
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        getPropertyList(BPDataPropertyList& propertyList);

            BIMBASEAPI_EXPORT bool                  operator<(BPDataClassCR rhs)const;


        private:


            void*    m_imp;


        };

        /**
        @brief 领域数据定义集
        @date 创建日期:2021-8-13
        */
        class BPDataSchema
        {
            friend class BPDataProperty;
            friend class BPDataClass;
            friend class BPSchemaManager;
        public:
            BIMBASEAPI_EXPORT BPDataSchema();

            /**
            @brief 拷贝构造
            @param[in] from
            @note 浅拷贝
            */
            BIMBASEAPI_EXPORT                       BPDataSchema(BPDataSchemaCR from);

            BIMBASEAPI_EXPORT bool                  isValid() const;

            BIMBASEAPI_EXPORT p3d::PStringCR        getSchemaName() const;

            /**
            @brief 获取clssName的列表
            @param[out] classList：className的列表
            @return P3DStatus
            - SUCCESS 获取成功
            - ERROR 获取失败
            @note 获取到的className为此DataSchema下的全部的className
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus       getClassList(P3DClassList& classList)const;

        private:

            void* m_imp;

        };

        /**
        @brief schema管理类
        @details 主要用于根据schemaName，className以及classId得到对应的dataClass
        */
        class BPSchemaManager
        {
            friend class BPDataProperty;
            friend class BPDataClass;
            friend class BPDataSchema;
        public:
            /**
            @brief 查询对应名称的数据定义
            @details 通过schemaName和className得到dataClass
            @param[out] dataClass: 领域数据定义
            @param[in]  schemaName；
            className；
            project:工程文件
            @return P3DStatus状态码
            - SUCCESS 获取成功
            - ERROR 获取失败
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus         getClassByName(BPDataClassR dataClass, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className, BPProjectCR project);

            /**
            @brief 查询对应数据类id的数据定义
            @details 通过classId得到dataClass
            @param[out] dataClass: 领域数据定义
            @param[in]  classId: 数据类id；
            project：工程文件
            @return P3DStatus状态码
            - SUCCESS 获取成功
            - ERROR 获取失败
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus         getClassById(BPDataClassR dataClass, PClassIdCR classId, BPProjectCR project);

            /**
            @brief 获取文件对应的数据定义表
            @details 获取文件对应的schemaName和className的表
            @param[out] scheamaList: 数据定义的列表
            @param[in]  project: 工程文件
            @return P3DStatus状态码
            - SUCCESS 获取成功
            - ERROR 获取失败
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus        getSchemaListOfFile(P3DSchemaList& scheamaList, ::BIMBase::Core::BPProjectCR project);

            /**
            @brief 根据schemaName和className获得classId
            @param[in]  project：工程文件；
            schemaName；
            className
            @return PClassId
            - 非-1 获取成功
            - -1 获取失败
            @see p3d::P3DStatus getClassNameByClassId(OUT p3d::Utf8StringR schemaName, OUT p3d::Utf8StringR className, PClassIdCR classId, BPProjectCR project)
            */
            BIMBASEAPI_EXPORT static PClassId               getClassIdByClassName(BPProjectCR project, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className);

            /**
            @brief 根据classId获取schemaName和className
            @param[out] schemaName；
            className
            @param[in]  classId；
            project：工程文件
            @return P3DStatus
            - SUCCESS 获取成功
            - ERROR 获取失败
            @see PClassId getClassIdByClassName(BPProjectCR project, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className)
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus         getClassNameByClassId(OUT p3d::Utf8StringR schemaName, OUT p3d::Utf8StringR className, PClassIdCR classId, BPProjectCR project);

            /**
            @brief 根据schemaName和className获取类型描述
            @param[in]  project：工程文件；
            schemaName；
            className
            @return utf8字符串
            */
            BIMBASEAPI_EXPORT static p3d::Utf8String        getClassDescriptionByClassName(BPProjectCR project, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className);

            /**
            @brief 根据schemaName和className获取显示标签
            @param[in]  project：工程文件；
            schemaName；
            className
            @return utf8字符串
            */
            BIMBASEAPI_EXPORT static p3d::Utf8String        getClassDisplayLabelByClassName(BPProjectCR project, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className);

            /**
            @brief 加载指定目录(包含子目录)的Schema文件数据到指定的工程文件中
            @param[in]  project：工程文件；
            schemaDir：指定schema目录；
            schemaArrayPath：依赖的schema目录列表
            bGenerateClassInfo: 是否生成class数据,为了提高性能,如果连续多次调用此接口加载schema,则只需要最后一次调用设置为true即可.
			@return P3DStatus
			- SUCCESS 获取成功
			- ERROR 获取失败
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus         loadSchemasToProject(BPProjectCR project, const p3d::PString& schemaDir, p3d::pvector<p3d::PString>& dependentSchemaPath, bool bGenerateClassInfo = true);

        private:
            BPSchemaManager();
            BPSchemaManagerR operator= (BPSchemaManagerCR from);
            BPSchemaManager(BPSchemaManagerCR from);
        };

        /**
        @brief  领域数据
        @details  用于记录领域数据或表示数据之间关联关系的关系类数据
        @date 创建日期:2021-07-29
        */
        class BPData : public BPRefCountedBase
        {

        private:
            BPData();
            BPData(BPDataCR model) = delete;
            BPDataR operator=(BPDataR model) = delete;

        public:

            /**
            @brief 获取BPData对应的schemaName
            @return schemaName的utf8字符串
            @see p3d::Utf8String getClassName(void) const
            */
            BIMBASEAPI_EXPORT p3d::Utf8String       getSchemaName(void) const;

            /**
            @brief 获取BPData对应的className
            @return className的utf8字符串
            @see p3d::Utf8String getSchemaName(void) const
            */
            BIMBASEAPI_EXPORT p3d::Utf8String       getClassName(void) const;

            /**
            @brief 根据属性名称获取BPValue
            @details 用于非数组类型的属性
            @param[out] value: 属性值
            @param[in]  propertyName: 属性名称
            @return P3DStatus状态码
            - SUCCESS 获取成功
            - ERROR 获取失败
            @see p3d::P3DStatus setValue(p3d::Utf8StringCR propertyName, BPValueCR value);
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        getValue(BPValueR value, p3d::Utf8StringCR propertyName) const;

            /**
            @brief 根据属性索引获取BPValue
            @details 用于非数组类型的属性
            @param[out] value: 属性值
            @param[in]  propertyIndex: 属性索引
            @return P3DStatus状态码
            - SUCCESS 获取成功
            - ERROR 获取失败
            @see p3d::P3DStatus setValue(uint32_t propertyIndex, BPValueCR value)
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        getValue(BPValueR value, uint32_t propertyIndex) const;

            /**
            @brief 根据属性索引获取BPValue
            @details 用于数组类型的属性
            @param[out] value: 属性值
            @param[in]  propertyIndex: 属性索引；
            arrayIndex：数组索引
            @return P3DStatus状态码
            - SUCCESS 获取成功
            - ERROR 获取失败
            @see p3d::P3DStatus setValue(uint32_t propertyIndex, BPValueCR value, uint32_t arrayIndex)
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        getValue(BPValueR value, uint32_t propertyIndex, uint32_t arrayIndex) const;

            /**
            @brief 根据属性名称获取BPValue
            @details 用于数组类型的属性
            @param[out] value: 属性值
            @param[in]  propertyName: 属性名称；
            arrayIndex：数组标号
            @return P3DStatus状态码
            - SUCCESS 获取成功
            - ERROR 获取失败
            @see p3d::P3DStatus setValue(p3d::Utf8StringCR propertyName, BPValueCR value, uint32_t arrayIndex)
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        getValue(BPValueR value, p3d::Utf8StringCR propertyName, uint32_t arrayIndex) const;

            /**
            @brief 根据属性名称将BPValue写入BPData
            @details 用于非数组类型的属性
            @param[in]  propertyName: 属性名称；
            value：属性值
            @return P3DStatus状态码
            - SUCCESS 写入成功
            - ERROR 写入失败
            @see p3d::P3DStatus getValue(BPValueR value, p3d::Utf8StringCR propertyName) const
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        setValue(p3d::Utf8StringCR propertyName, BPValueCR value);

            /**
            @brief 根据属性编号将BPValue写入BPData
            @details 用于非数组类型的属性
            @param[in]  propertyIndex: 属性编号；
            value：属性值
            @return P3DStatus状态码
            - SUCCESS 写入成功
            - ERROR 写入失败
            @see p3d::P3DStatus getValue(BPValueR value, uint32_t propertyIndex) const
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        setValue(uint32_t propertyIndex, BPValueCR value);

            /**
            @brief 根据属性编号将BPValue写入BPData
            @details 用于数组类型的属性
            @param[in]  propertyIndex: 属性编号；
            value：属性值；
            arrayIndex：数组编号
            @return P3DStatus状态码
            - SUCCESS 写入成功
            - ERROR 写入失败
            @see p3d::P3DStatus getValue(BPValueR value, uint32_t propertyIndex, uint32_t arrayIndex) const
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        setValue(uint32_t propertyIndex, BPValueCR value, uint32_t arrayIndex);

            /**
            @brief 根据属性名称将BPValue写入BPData
            @details 用于数组类型的属性
            @param[in]  propertyName: 属性名称；
            value：属性值；
            arrayIndex：数组编号
            @return P3DStatus状态码
            - SUCCESS 写入成功
            - ERROR 写入失败
            @see p3d::P3DStatus getValue(BPValueR value, p3d::Utf8StringCR propertyName, uint32_t arrayIndex) const
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        setValue(p3d::Utf8StringCR propertyName, BPValueCR value, uint32_t arrayIndex);

            /**
            @brief 将BPData写入到文件
            @details 应用于对应的BPData在文件中不存在，需要写入到文件的情况
            @param[in]  isAutoGenDataId: 是否自动分配dataId（默认为自动分配）；
            dataId：指定的id值（默认为不指定id）
            @return P3DStatus状态码
            - SUCCESS 写入成功
            - ERROR 写入失败
            @see p3d::P3DStatus updateToProject()
            @note 若isAutoGenP3dDataId为false, dataId为需要设定的Id值;如果为true, dataId必须为默认值
            @waring 当传入的dataId为重复时返回ERROR
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        addToProject(bool isAutoGenDataId = true, ::BIMBase::BPDataId dataId = ::BIMBase::BPDataId(-1LL));

            /**
            @brief 将BPData的变化更新到文件
            @details 应用于对应的BPData已经存在于文件，但其发生了改变，需要更新的情况
            @return P3DStatus状态码
            - SUCCESS 更新成功
            - ERROR 更新失败
            @see p3d::P3DStatus addToProject(bool isAutoGenDataId = true, BPDataId dataId = BPDataId(-1LL))
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus        updateToProject();

            /**
             @brief 获取源BPData的唯一ID
             @details 此接口仅应用于关系类的数据,如果仅使用dataKey值可以调用此接口,不必调用会引起反序列化的getSource接口.
             @see
             */
            BIMBASEAPI_EXPORT BPDataKey             getSourceDataKey()const;

            /**
            @brief 获取源BPData
            @details 此接口仅应用于关系类的数据
            @return BPData实例的指针
            @see BPDataPtr getTarget()
            */
            BIMBASEAPI_EXPORT BPDataPtr             getSource()const;

            /**
            @brief 获取目标BPData的唯一ID
            @details 此接口仅应用于关系类的数据,如果仅使用dataKey值可以调用此接口,不必调用会引起反序列化的getSource接口.
            @see
            */
            BIMBASEAPI_EXPORT BPDataKey             getTargetDataKey()const;

            /**
            @brief 获取目标BPData
            @details 此接口仅应用于关系类的数据
            @return BPData实例的指针
            @see BPDataPtr getSource()
            */
            BIMBASEAPI_EXPORT BPDataPtr             getTarget()const;


            /**
            @brief 获取BPDataId
            @return 数据对象Id
            */
            BIMBASEAPI_EXPORT BPDataId              getId() const;

            /**
            @brief 获取classId
            @return 数据类id
            - 非-1 获取成功
            - -1   获取失败
            */
            BIMBASEAPI_EXPORT PClassId              getClassId() const;

            /**
            @brief 获取DataClass
            @return 数据类别定义
            */
            BIMBASEAPI_EXPORT BPDataClass           getClass() const;

            /**
            @brief 获取BPDataKey
            */
            BIMBASEAPI_EXPORT BPDataKey            getDataKey() const;

            /**
            @brief 判断当前对象是否为某类或其子类的数据对象
            @param[in] schemaName；className
            @return 布尔值
            - true 是
            - false 非，或输入参数有误
            */
            BIMBASEAPI_EXPORT bool                 isKindOfClass(p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className);

            /**
            @brief 为指定属性分配指定大小的数组空间
            @details 用于BPData中可存储数组类型的属性
            @param[in]  propertyString: 属性名称；
            size：数组大小
            @return P3DStatus
            - SUCCESS 成功
            - ERROR 失败
            @see p3d::P3DStatus clearArray(p3d::Utf8StringCR propertyString)
            @note 指定的属性必须为数组类型
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus       addArrayElements(p3d::Utf8StringCR propertyString, uint32_t size);

            /**
            @brief 清空指定属性的数组
            @details 用于BPData中可存储数组类型的属性
            @param[in] propertyString: 属性名称
            @return P3DStatus
            - SUCCESS 成功
            - ERROR 失败
            @see p3d::P3DStatus addArrayElements(p3d::Utf8StringCR propertyString, uint32_t size)
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus       clearArray(p3d::Utf8StringCR propertyString);

            /**
            @brief 将BPData的内容导出为xml格式
            @param[out] ecDataXml: 转换成的xml格式字符串
            @param[in] isStandAlone：true包含xml头,false不包含xml头；
            writeDataId：ecDataXml中输出的是否包含dataId
            @return P3DStatus状态码
            - SUCCESS 导出成功
            - ERROR 导出失败
            @see p3d::P3DStatus readFromXmlString(BPDataPtr& instancePtr, p3d::Utf8StringCR xmlString, p3d::Utf8StringCR schemaName, ::BIMBase::Core::BPProjectCR project)
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus       writeToXmlString(p3d::Utf8StringR ecDataXml, bool isStandAlone, bool writeDataId);

            /**
            @brief 将xml格式的数据写入为BPData
            @param[out] dataPtr: 转化为的BPData指针
            @param[in]  xmlString: xml格式的字符串；
            schemaName；
            project：工程文件
            @return P3DStatus状态码
            - SUCCESS 写入成功
            - ERROR 写入失败
            @see p3d::P3DStatus writeToXmlString(p3d::Utf8StringR ecInstanceXml, bool isStandAlone, bool writeDataId);
            */
            BIMBASEAPI_EXPORT static p3d::P3DStatus     readFromXmlString(BPDataPtr& dataPtr, p3d::Utf8StringCR xmlString, p3d::Utf8StringCR schemaName, ::BIMBase::Core::BPProjectCR project);

            /**
            @brief 拷贝属性值到BPData
            @details 仅拷贝源BPData中的属性值字段
            @param[in] sourceData: 源BPData
            @return P3DStatus状态码
            - SUCCESS 拷贝成功
            - ERROR 拷贝失败
            @note 如果拷贝的为关系类数据，则不会拷贝source和target
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus            copyValues(BPDataR sourceData);


            // ____<pkpm_inner_begin>____
            /**
            @brief 获取当前领域数据所属的工程文件
            */
            BIMBASEAPI_EXPORT BPProjectP getProject() const;

            /**
            @brief 如果有多个entity,则返回第一个
            @param[in] sourceData: 源BPData
            @return P3DStatus状态码
            - SUCCESS 
            - ERROR 非图形对象返回ERROR
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus getPrimaryEntity(BPEntityPtr& entity) const;    // 非图形对象返回ERROR

            // ____<pkpm_inner_end>____
        };

        typedef p3d::pvector<BPDataPtr>              BPDataList;
        typedef BPDataList                  *BPDataListP, &BPDataListR;
        typedef BPDataList const            *BPDataListCP;
        typedef BPDataList const            &BPDataListCR;
        /**
        @brief  数据集
        @details  数据数组，包含多个数据指针的数据集
        @date 创建日期:2021-08-02
        */
        class BPDataArray : public ::BIMBase::BPRefCountedBase
        {

        public:
            /**
            @brief 构造函数
            @details 构造数据集
            */
            BIMBASEAPI_EXPORT                   BPDataArray();

            // ____<pkpm_inner_begin>____
            // TODO-NRG(18/09/2021):暂时不暴露
            /**
            @brief 构造函数
            @details 构造数据集
            @param[in] BPDataArray&: 构造数据集所参考BPDataArray引用
            @param[in] bool bRef: 引用方式
            */
            BIMBASEAPI_EXPORT                   BPDataArray(BPDataArray&, bool bRef = true);
            // ____<pkpm_inner_end>____

            /**
            @brief =操作
            @param[in] BPDataArrayCR source: 构造数据集所参考BPDataArray引用
            */
            BIMBASEAPI_EXPORT BPDataArrayR    operator= (BPDataArrayCR source);

            /**
            @brief 析构函数
            */
            BIMBASEAPI_EXPORT virtual           ~BPDataArray();

            /**
            @brief 插入数据集
            @details 在数据集中插入数据对象
            @param[in] BPDataR entity: 要插入的数据
            @param[in] bool atHead: 是否插入到首位（缺省为false，表示按顺序添加）
            */
            BIMBASEAPI_EXPORT void                insert(BPDataR entity, bool atHead = false);

            /**
            @brief 删除数据集中数据
            @details 将数据从数据集中移除
            @param[in] uint32_t nIndex: 要移除的数据索引
            */
            BIMBASEAPI_EXPORT bool                erase(uint32_t nIndex);

            /**
            @brief 高亮数据集
            @details 将数据集中数据高亮显示
            */
            BIMBASEAPI_EXPORT void                hilite();

            /**
            @brief 清除数据集高亮显示
            @details 将数据集中数据恢复到原始显示状态
            */
            BIMBASEAPI_EXPORT void                clearHilite();

            /**
            @brief 清除数据集
            @details 清除数据集高亮显示并清除数据集中数据记录
            */
            BIMBASEAPI_EXPORT void                clear();

            /**
            @brief 清除数据集
            @details 将数据集中数据记录清除
            */
            BIMBASEAPI_EXPORT void                empty();

            /**
            @brief 判断数据集是否为空
            @details 判断数据集中是否包含数据记录
            @return 是否包含数据记录
            */
            BIMBASEAPI_EXPORT bool                isEmpty();

            /**
            @brief 获取数据集中数据个数
            @return 数据个数
            */
            BIMBASEAPI_EXPORT int32_t            getCount() const;

            /**
            @brief 获取数据集中第一个数据指针
            @return 数据指针
            */
            BIMBASEAPI_EXPORT BPDataPtr        getFirst() const;

            /**
            @brief 获取数据集中最后一个数据指针
            @return 数据指针
            */
            BIMBASEAPI_EXPORT BPDataPtr        getLast() const;

            /**
            @brief 获取数据集中指定位置数据指针
            @param[in] size_t i: 数据索引
            @return 数据指针
            */
            BIMBASEAPI_EXPORT BPDataPtr        getByIndex(size_t i) const;

            /**
            @brief 获取数据集中指定位置数据指针
            @param[in] uint32_t nIndex: 数据索引
            @return 数据指针
            */
            BIMBASEAPI_EXPORT BPDataPtr        operator[](uint32_t nIndex) const;

            // ____<pkpm_inner_begin>____
            /**
            @brief 数据检索
            @details 在数据集中查找指定数据的索引
            @warning will be deprecated
            */
            BIMBASEAPI_EXPORT BPDataPtr        find(BPDataCR entity, size_t startIndex = 0, size_t endIndex = -1);
            // ____<pkpm_inner_end>____

        private:

            class BPDataArrayImp : public ::BIMBase::BPRefCountedBase
            {
                friend class BPDataArray;
                std::vector<BPDataPtr> m_datas;
            };

            typedef p3d::RefCountedPtr<BPDataArrayImp>             BPDataArrayImpPtr;
            BPDataArrayImpPtr m_Imp;
            bool m_bImpRef;

        };
    }
}


#endif    // BP_BPData_BPData_H