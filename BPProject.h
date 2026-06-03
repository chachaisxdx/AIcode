/** 
@brief 工程文件访问类
@file    BPProject.h
@author  北京构力科技有限公司
@date    2021-10-25
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/

#ifndef BP_BPData_BPProject_H
#define BP_BPData_BPProject_H




namespace BIMBase {
    // 用于储存状态值的全局函数
    BIMBASEAPI_EXPORT Int16 getLastStatus();
    void setLastStatus(Int16);
}

namespace BIMBase {
    namespace Core
    {
        enum class BPProjectSaveOption
        {
            enDefault = 0,
            enFileCloseNotSave = 6,         // 专业关闭文件时不保存可以使用此标志
        };

        class BPModelItemInfo
        {
        private:
            BPModelItemInfo();

        public:
            BIMBASEAPI_EXPORT BPModelItemInfo(BIMBase::PModelIdCR modelId, p3d::Utf8StringCR modelName, p3d::Utf8StringCR description);

            BIMBASEAPI_EXPORT PModelIdCR          getModelId() const;
            BIMBASEAPI_EXPORT p3d::Utf8StringCR   getModelName() const;
            BIMBASEAPI_EXPORT p3d::Utf8StringCR   getDescription() const;
        private:
            PModelId            m_modelId;
            p3d::Utf8String     m_modelName;
            p3d::Utf8String     m_modeDescription;
        };
        typedef p3d::pvector<BPModelItemInfo>   BPModelItemInfoVector;
        typedef BPModelItemInfoVector&          BPModelItemInfoVectorR;
        typedef const BPModelItemInfoVectorR    BPModelItemInfoVectorCR;

        class BPProjectHandle;


		enum    class ModelTreeItemAccessAuthor
		{
			enReadOnly,
			enEdite

		};

		class BIMBASEAPI_EXPORT ModelTreeItemInfo
		{
        public:
            std::wstring               m_modeldisplayName;             //节点显示名称
			std::wstring               m_name;                         //节点唯一名称(modelName)
			std::wstring               m_fatherName;                   //节点父节点唯一名称
			bool                       m_isHideInModelTree;            //节点在模型UI上是否隐藏
			ModelTreeItemAccessAuthor  m_modelTreeItemAccessAuthor;    //是否可修改节点属性信息
			ModelTreeItemInfo();
            ModelTreeItemInfo(std::wstring fatherName, std::wstring name, std::wstring modeldisplayName, bool isHideInModelTree = false, ModelTreeItemAccessAuthor modelTreeItemAccessAuthor = ModelTreeItemAccessAuthor::enEdite);
        };

		// 引用组件信息，用于插件信息中.
		struct BPRefComponentItem
		{
            p3d::PString m_strComponentPath;			// 组件的路径
			bool		 m_bLoadRibbon;					// 是否加载组件的默认Ribbon
            p3d::PString m_strCustomRibbonPath;			// 用户自定义Ribbon，不受m_bLoadRibbon的影响.
		};

		class BPPluginInfo : public BPRefCountedBase
		{
		public:
			BPPluginInfo() :name(L""), ID(L""), appVersion(L""), bimbaseSDKVersion(L""), schemaVersion(L""), schemaFileDir(L""), schemaFileNameList(L"") {}
			p3d::PString name;
			p3d::PString ID;
			p3d::PString appVersion;        // 生成此工程数据的插件程序版本号
			p3d::PString bimbaseSDKVersion; // 生成此工程数据的插件程序基于的BIMBaseSDK版本号
			p3d::PString schemaVersion;     // 插件数据版本号
			p3d::PString schemaFileDir;     // 不向文件中存储，用于插件列表管理器数据
			p3d::PString schemaFileNameList;    //各个名称之间以半角分号(;)进行分隔(注意：从插件管理器得到的为增加插件机制之前版本的工程文件中此专业插件对应的Schema列表)
			p3d::PString pluginConfigFullName;  // 插件配置文件全路径.
			p3d::PString mainAssemblyName;      // 插件入口dll名称.
			bool         bPluginStatus;         // 此插件是否需要加载, 来自于插件配置文件:true(不需要加载), false(需要加载)
			bool         bCurPluginStatus;		// 插件当前的状态 bool：true(加载)，false(卸载)
            std::vector<BPRefComponentItem>	m_vecRefComponentList;	// 插件引用的组件列表(此数据未持久化,不能通过BPProject::getPluginInfo接口获取,暂时仅平台内部使用.)
			p3d::PString reserve;
		};
		typedef p3d::pvector<BPPluginInfoPtr>     BPPluginInfoList;
		typedef BPPluginInfoList& BPPluginInfoListR;
		typedef const BPPluginInfoListR     BPPluginInfoListCR;


        /**
        @brief  工程文件类
        @details  通过IBPProjectManager类可以获取工程文件实例
        @date 创建日期:2021-07-28
        */
        class BPProject : public BPRefCountedBase
        {
        public:

            /**
            @brief 文件打开模式
            @details
            */
            enum class BPOpenMode
            {
                enReadonly = 1 << 0,                /**< 只读模式*/
                enReadWrite = 1 << 1,               /**< 读写模式*/
                enCreate = enReadWrite | (1 << 2)   /**< 创建模式*/
            };

        public:

            /**
            @brief 工程文件析构函数
            */
            BIMBASEAPI_EXPORT virtual ~BPProject();

            /**
            @brief 判断当前工程文件实例是否是框架打开的主工程
            @return bool
            - true 是主工程
            - false 不是主工程
            */
            BIMBASEAPI_EXPORT bool                      isMainProject() const;

            // ____<pkpm_inner_begin>____
            /**
            @brief 获取当前工程文件名称
            @return 工程文件全路径
            @deprecated 用getProjectFullPath代替
            */
            BIMBASEAPI_EXPORT::p3d::P3DFileName         getProjectName() const;
            // TODO-NRG(26/08/2021): P3DFileName类不对外公开
            // ____<pkpm_inner_end>____

            /**
            @brief 获取当前工程文件名称
            @return 工程文件全路径
            */
            BIMBASEAPI_EXPORT::p3d::PString             getProjectFullPath() const;

            /**
            @brief 判断当前工程文件实例是否是只读模式
            @return bool
            - true 只读模式
            - false 不是只读模式
            */
            BIMBASEAPI_EXPORT bool                      isReadOnly() const;

            /**
            @brief 判断当前工程文件实例是否有未保存的修改
            @return bool
            - true 有未保存的修改
            - false 无未保存的修改
            */
            BIMBASEAPI_EXPORT bool                      hasPendingChanges();

            // ____<pkpm_inner_begin>____
            /**
            @brief 文件压缩
            @return 执行结果
            - SUCCESS 成功
            - ERROR 失败
            @deprecated
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus           compactFile();

            /**
            @brief 创建一个model实例
            @param[out] status&:  操作结果状态
            @param[in]  modelName:  Model的名称
            @param[in]  modelType:  Model的类型(暂不支持P3DModelType::Drawing类型)
            @param[in]  bIs3D:  是否是3D类型
            @param[in]  ifCreateView:  是否创建视图信息,如果此model要做为viewPort的主model进行显示,则需要设置为true,否则为了提高性能可以设置为false.
            @return 创建成功返回BPModel对象指针,否则返回nullptr.
            @deprecated 用createNewModel代替
            */
            BIMBASEAPI_EXPORT BPModelP                  createNewModel(::p3d::P3DStatus& status, p3d::Utf8StringCR modelName, p3d::platform::P3DModelType modelType, bool bIs3D,  BIMBase::Core::ModelTreeItemInfo modelTreeItemInfo, bool ifCreateView = true );
            // ____<pkpm_inner_end>____
            /**
            @brief 创建一个model实例
            @param[out] status&:  操作结果状态
            @param[in]  modelName:  Model的名称
            @param[in]  modelType:  Model的类型,(暂不支持P3DModelType::Drawing类型).
            @param[in]  modelId:  指定modelId,如果此modelId已经在文件中存在,则创建失败
            @return 创建成功返回BPModel对象指针,否则返回nullptr.
            @note 建议不使用ptr类型变量接返回值
            */
            BIMBASEAPI_EXPORT BPModelP                  createNewModel(::p3d::P3DStatus& status, p3d::Utf8StringCR modelName, p3d::platform::P3DModelType modelType, PModelId modelId, BIMBase::Core::ModelTreeItemInfo modelTreeItemInfo);

            /**
            @brief 获取当前工程文件内的活动model
            @return 活动模型空间
            */
            BIMBASEAPI_EXPORT BPModelBaseP              getActiveModel();

            /**
            @brief 根据指定的ID获取相应的模型空间。
            @details 如果此模型空间尚未加载到内存缓存，此方法不会进行加载操作，如果需要进行加载操作则调用loadModelById方法。如果模型空间未加载到内存则访问不到其下的entity数据。
            @param[in]  modelId:  指定modelId,
            @return 模型空间
            @see loadModelById(PModelId modelId)
            */
            BIMBASEAPI_EXPORT BPModelPtr                getModelById(PModelId modelId);

            /**
            @brief 根据指定的ID获取相应的模型空间。
            @details 如果此模型空间尚未加载到内存，则会首先会进行内存加载操作。如果不需要内存加载操作，调用getModelById方法。
            @param[in]  modelId:  指定modelId,
            @return 模型空间
            @see getModelById(PModelId modelId)
            */
            BIMBASEAPI_EXPORT BPModelP                  loadModelById(PModelId modelId);

            /**
            @brief 获取当前工程文件里的所有模型空间，如果模型空间尚未加载到内存，则会首先会进行内存加载操作。
            @details 返回的Model集合里包含已经加载到内存的和之前未加载到内存的
            @return 模型空间集合
            @note   此接口性能较差,能不用尽量不用，如果是根据ID获取指定的Model直接使用【loadModelById】接口即可!!!
            */
            BIMBASEAPI_EXPORT BPModelArrayR             getAllModelsCollection() const;

            BIMBASEAPI_EXPORT p3d::P3DStatus            getAllModelsItemList(BPModelItemInfoVectorR modelItemList) const;

            /**
            @brief 获取当前工程文件中已经加载到内存的模型空间
            @details 不包含未加载到内存的模型空间
            @return 模型空间集合
            */
            BIMBASEAPI_EXPORT BPModelArrayR             getLoadedModelsCollection() const;

            /**
            @brief 获取当前工程文件中的默认模型空间
            @details 每个工程中有唯一的一个默认模型空间.
            @return 默认模型空间
            */
            BIMBASEAPI_EXPORT PModelId                  getDefaultModelId() const;

            /**
            @brief 根据指定的模型空间ID查询已加载的模型空间，如果此模型空间尚未加载到内存，则返回空。
            @param[in]  modelId:  指定的模型空间唯一ID
            @return 模型空间
            */
            BIMBASEAPI_EXPORT BPModelPtr                findLoadedModelById(PModelId modelId) const;

            /**
            @brief 根据指定的模型空间名称查询模型空间
            @details 即使此模型空间尚未加载到内存也会返回相应的ID
            @param[in]  modelName:  指定的模型空间名称
            @return 模型空间
            */
            BIMBASEAPI_EXPORT PModelId                  findModelIdByName(::p3d::Utf8CP modelName) const;

            /**
            @brief 获取当前工程文件中模型空间的数目
            @return 模型空间数目
            */
            BIMBASEAPI_EXPORT int32_t                   getLoadedModelCount() const;

            /**
            @brief 判断指定的modelId在当前工程文件中是否有相应的模型空间
            @param[in]  modelId:  指定的模型空间唯一ID
            @return 是否有模型空间
            */
            BIMBASEAPI_EXPORT bool                      isValidModelID(PModelId modelId) const;

            /**
            @brief 根据指定的modelId删除当前相应的模型空间
			@details 如果要删除的model有对应的BPModelElement数据,则不能通过此接口直接删除,会返回ERROR.应该通过BPModelElement相关的接口(如deleteFromProject、BPModelElementManager::deleteModelElementBy*等)删除.
            @param[in]  modelId:  指定的模型空间唯一ID
            @return 删除是否成功
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus           deleteModel(PModelId modelId);

            // ____<pkpm_inner_begin>____
            /**
            @brief 对所有已经加载到内存的模型空间进行数据的加载操作
            @return 加载结果状态
            @deprecated 
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus           fillAllLoadedModels();
            // ____<pkpm_inner_end>____

            // ____<pkpm_inner_begin>____
            /**
            @brief 获取指定的模型空间的uor
            @details 每个主单位的像素个数
            */
            BIMBASEAPI_EXPORT static double             getUorPerMaster(BPModelBaseCR model);
            // ____<pkpm_inner_end>____


            /**
            @brief 获取指定的工程文件的三维空间范围,仅获取physical模型空间的范围.
            */
            BIMBASEAPI_EXPORT p3d::GeRange3d            getRange();

            /**
            @brief 在当前工程文件中根据指定的图形实体唯一ID查询相应的图形实体
            */
            BIMBASEAPI_EXPORT BPEntityPtr               getEntityById(BPEntityId entityId);

            // ____<pkpm_inner_begin>____
            /**
            @brief 在当前工程文件对应的事务管理器
            @deprecated 用BPApplication::getTransactionManager代替
            */
            BIMBASEAPI_EXPORT::BIMBase::BPTransactionManager& getTransactionManager() const;
            // ____<pkpm_inner_end>____

            // ____<pkpm_inner_begin>____
            /**
            @brief 协同下设置仓库的ID
            @details 每次新映射或第一次打开联机项目的时候，该ID会自动加1
            @param[in] repId: 仓库ID
            @return 执行结果
            - SUCCESS 成功
            - ERROR 失败
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus           changeRepositoryId(int repId);

            BIMBASEAPI_EXPORT int                       getRepositoryId() const;

            /**
            @brief 获取版本号
            @details 平台大版本 + 平台主版本  +  平台子版本  +  预留使用位  @  文件版本号  @ schema版本号 @ 应用程序版本号：应用程序变更集
            @return 版本号字符串
            */
            BIMBASEAPI_EXPORT p3d::PString              getVersions();
            BIMBASEAPI_EXPORT::p3d::P3DStatus           setVersions(p3d::PStringCR version);
			/**
			@brief 当前工程是否只读
			@details
			@return 当前工程是否只读
			*/
			BIMBASEAPI_EXPORT bool              getIsReadOnly() const;
			BIMBASEAPI_EXPORT::p3d::P3DStatus           setIsReadOnly(bool isReadOnly);
			// ____<pkpm_inner_end>____

            /**
            @brief 获取当前工程文件的句柄,句柄值不能用于持久化存储.
            @details 通过此文件句柄可以在IBPProjectManager中查到对应的BPProject实例指针,用于需要记录工程文件实例的地方,以提升程序的健壮性.
            @note 不建议以指针的形式进行记录.
            @return 版本号字符串
            */
            BIMBASEAPI_EXPORT BPProjectHandle           getProjectHandle()const;

            /**
            @brief 获取当前工程文件的guid
            @details guid字符串长度为38字节，格式为XXXXXXXX-XXXX-XXXX-XXXXXXXXXXXXXXXX，其中有效位为36字节.
            @return 长度为38字节的guid字符串
            @see updateGuid(p3d::Utf8CP newGuid)
            */
            BIMBASEAPI_EXPORT p3d::Utf8String           getGuid() const;
            // ____<pkpm_inner_begin>____

            BIMBASEAPI_EXPORT p3d::P3DStatus            getGuidByte(byte(&guid)[38]) const;
            // ____<pkpm_inner_end>____

            /**
            @brief  使用参数指定的guid值更新当前工程文件的guid,如果参数传入空值则使用自动生成的guid更新当前工程文件的guid.
            @details 每一个工程文件默认会有唯一的一个guid，此方法可以用指定的guid替换默认的guid.
            @param[in] newGuid: 长度为38字节的guid字符串，格式为XXXXXXXX-XXXX-XXXX-XXXXXXXXXXXXXXXX，其中有效位为36字节.或者一个空值,则自动生成一个guid来更新当前工程文件.
            @return 返回值说明
            - SUCCESS 更新成功
            - ERROR 更新失败
            @see getGuid()
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus            updateGuid(p3d::Utf8CP newGuid);

            // ____<pkpm_inner_begin>____
            /**
            @deprecated 用IBPProjectManager::getActiveProject代替
            */
            BIMBASEAPI_EXPORT static BPProjectP         getActiveProject();

            /**
            @deprecated 用IBPProjectManager::getMainProject代替
            */
            BIMBASEAPI_EXPORT static BPProjectP         getMainProject();

            /**
            @deprecated 无替代函数
            */
            BIMBASEAPI_EXPORT PModelId                  getFirstModelId() const;

            // ____<pkpm_inner_end>____

            /**
            @brief 获取工程文件中的插件列表信息
            @return true:成功, false:失败
            */
            BIMBASEAPI_EXPORT bool getPluginInfo(BPPluginInfoListR pluginInfoList) const;
        private:
            BPProject();
            BPProject(BPProjectCR) = delete;
            BPProjectR operator= (BPProjectCR from) = delete;
            p3d::P3DStatus      initData();
            p3d::P3DStatus      saveChanges(BPProjectSaveOption reason);
            p3d::P3DStatus      close(BPProjectSaveOption reason);

        };

        /** 
        @brief  工程文件访问句柄,不能用于持久化存储
        @date 创建日期:2021-09-22
        */
        class BPProjectHandle
        {
            friend class BPProject;
            friend class BPProjectManager;
        public:
            BIMBASEAPI_EXPORT BPProjectHandle(const BPProject& prj);

            /**
            @brief 创建一个未初始化的无效句柄
            @return 句柄实例.
            */
            BIMBASEAPI_EXPORT static BPProjectHandle createInstance();

            /**
            @brief 使当前句柄无效.
            @return 无
            */
            BIMBASEAPI_EXPORT void invalidate();

            /**
            @brief 判断当前句柄是否有效.
            @return true:有效, false:无效.
            */
            BIMBASEAPI_EXPORT bool isValidHandle() const;

            BIMBASEAPI_EXPORT bool operator<(BPProjectHandleCR rhs) const;
			BIMBASEAPI_EXPORT bool operator==(BPProjectHandleCR rhs) const;
            //使用编译器默认提供的拷贝构造、operator=即可
        private:
            BPProjectHandle();
            unsigned long long  m_PrjID;
        };
        typedef p3d::pvector<BPProjectHandle>          BPProjectHandleVector;

        /**
        @brief  工程文件管理
        @date 创建日期:2021-07-28
        */
        class IBPProjectManager
        {
        public:

            /**
            @brief 打开一个工程文件.
            @details 如果fileName参数指定的工程文件已经打开,并且打开模式与openModel参数指定的模式一致,则返回已经打开的工程文件指针,如果打开模式不一致,则返回null值.
            @param[out] status 打开成功还是失败
            @param[in] fileName 工程文件全路径，包含文件名称
            @param[in] openMode 打开模式
            @param[in] isShare 是否以共享模式打开,一般情况下建议此参数传true.如果为true,则后续再通过openProject接口打开同名的工程文件时不会再创建新的project实例,直接返回之前创建的project实例.
                               【特别说明:需要创建当前主工程(getMainProject接口返回的工程)与fileName指定的外部工程文件的链接的场合,此参数必须传true,否则可能存在未知的问题(如BPModelLink::getOriginalModel返回空值)】.
            @return 打开的工程文件
            @note  不能使用ptr类型变量接收返回值
            @see BPProject::BPOpenMode
            */
            BIMBASEAPI_EXPORT virtual BPProjectP                openProject(p3d::P3DStatus& status, p3d::PStringCR fileName, BPProject::BPOpenMode openModel,bool isShare = false);

            /**
            @brief 获取当前框架打的主工程文件
            @details 正常情况下会一直存在一个主工程实例,不会返回空指针.
            @param[out] P3DStatus 打开成功还是失败
            @param[in] fileName 工程文件全路径，包含文件名称
            @param[in] openMode 打开模式，可能的值有
            @return 主工程文件
            @note  不能使用ptr类型变量接收返回值
            */
            BIMBASEAPI_EXPORT virtual BPProjectP                getMainProject() const;

            /**
            @brief 从当前框架打开的文件集合中获取指定路径的工程文件
            @details 
            @param[in] fileName 工程文件全路径，包含文件名称
            @return 指定工程文件或NULL（未找到指定工程文件）
            @note  不能使用ptr类型变量接收返回值
            */
            BIMBASEAPI_EXPORT virtual BPProjectP                getOpenedProjectByFullname(::p3d::PString fileName) const;
            // ____<pkpm_inner_begin>____

            /**
            @brief 从当前框架打开的文件集合中获取指定GUID的工程文件
            @details
            @param[in] prjGuid 工程文件GUID
            @return 指定工程文件或NULL（未找到指定工程文件）
            @note  不能使用ptr类型变量接收返回值
            */
            BIMBASEAPI_EXPORT virtual BPProjectP                getOpenedProjectByGuid(byte prjGuid[38]) const;
            // ____<pkpm_inner_end>____

            // ____<pkpm_inner_begin>____
            /**
            @brief 获取当前活动的工程文件
            @details 一般情况下当前活动工程文件与主工程文件是同一个,除非当前活动Model从属于外部文件的情况.
            @return 活动工程文件
            @note  不能使用ptr类型变量接收返回值
            */
            BIMBASEAPI_EXPORT virtual BPProjectP                getActiveProject() const;

            // ____<pkpm_inner_end>____

            /**
            @brief 获取当前工程文件内的活动model
            @return 活动模型空间
            */
            BIMBASEAPI_EXPORT virtual BPModelBaseP              getActiveModel() const;

            /**
            @brief 获取所有的工程文件句柄
            @details
            @return 工程文件句柄集合
            @note 获取到的句柄不能用于持久化存储
            */
            BIMBASEAPI_EXPORT virtual BPProjectHandleVector     getProjectHandles() const;

            /**
            @brief 根据工程文件句柄获取相应的工程文件
            @details
            @param[in] projectHandle 工程文件句柄
            @return 工程文件
            */
            BIMBASEAPI_EXPORT virtual BPProjectP                getProjectByHandle(BPProjectHandleCR projectHandle);

            /**
            @brief 根据工程文件句柄获取相应的工程文件
            @details 可能会返回无效值
            @param[in] projectHandle 工程文件句柄
            @return 工程文件
            */
            BIMBASEAPI_EXPORT virtual BPProjectP                getProjectCacheByHandle(BPProjectHandleCR projectHandle);

            /**
            @brief 检查指定的工程文件指针的有效性
            @details
            @param[in] project 要检查的工程文件指针
            @return 有效返回true，否则返回false
            */
            BIMBASEAPI_EXPORT virtual bool                      isValid(BPProjectCP project);

            /**
            @brief 保存指定的工程文件
            @details
            @param[in] project 要保存的工程文件句柄
            @return 成功返回SUCCESS，失败返回ERROR
            */
            BIMBASEAPI_EXPORT virtual p3d::P3DStatus            saveProject(BPProjectHandleCR projectHandle);

            /**
            @brief 关闭指定的工程文件,需要注意的是如果要关闭的工程文件被其它工程链接,并且链接数据被加载,则此接口会执行失败.
            @details 一般用于打开外部文件进行操作完成后进行关闭时，不能调用于主工程文件的关闭。
            @param[in] projectHandle 要关闭的工程文件句柄
            @param[in] reason  默认会进行保存操作，如果不保存退出则此参数需要传入enFileCloseNotSave值
            @return 成功返回SUCCESS，失败返回ERROR
            @note 不能调用于主工程文件的关闭
            */
            BIMBASEAPI_EXPORT virtual p3d::P3DStatus            closeProject(BPProjectHandleCR projectHandle, BPProjectSaveOption reason = BPProjectSaveOption::enDefault);


        private:
            virtual void toInterface() = 0;
        };

        /**
        @brief  程序资源管理类
        @details  通过此类访问程序相关资源,如工程文件管理器、事务管理器等.与UIApplication生命周期相同。
        @date 创建日期:2021-07-28
        */
        class BPApplication : public BPNonCopyableClass
        {
        public:

            /**
            @brief 单例访问
            @return 应用程序唯一实体
            */
            BIMBASEAPI_EXPORT static BPApplicationR     getInstance();


            /**
            @brief 获取工程文件管理实例
            @return 已经授权成功返回文件管理实例指针,否则返回空.
            @note 在框架打开主工程之前返回值为nullptr.
            */
            BIMBASEAPI_EXPORT IBPProjectManagerP        getProjectManager() const;

            /**
            @brief 获取事务管理器
            @return 已经授权成功返回文件管理实例指针,否则返回空.
            @note 在框架打开主工程之前返回值为nullptr.
            */
            BIMBASEAPI_EXPORT BPTransactionManagerP     getTransactionManager() const;

            /**
            @brief 获取当前主程序模块全路径
            @details
            @return 全路径字符串
            */
            BIMBASEAPI_EXPORT p3d::PString getAppPath() const;


            /**
            @brief 重置依赖缓存
            @note 关闭非主工程前需调用此接口来重置依赖缓存
            */
            BIMBASEAPI_EXPORT void                      resetDependency();

            /**
            @brief 获取当前打开的工程文件全路径
            */
            BIMBASEAPI_EXPORT p3d::PStringCR getCurOpenProjectFullPathName()const;

        private:
            BPApplication();
            BPApplication(BPApplicationCR) = delete;
            BPApplicationR operator= (BPApplicationCR from) = delete;

        private:
            IBPProjectManagerP      m_projectManager;
            BPTransactionManagerP   m_transactionManager;
            p3d::PString            m_CurOpenFileName;
        };

        enum class BPCacheEventType
        {
            enProjectLoad,          /**<工程文件加载*/
            enProjectUnLoad,        /**<工程文件卸载*/
            enDomainLoad,           /**<专业加载*/
            enDomainUnLoad          /**<专业卸载*/
        };

        /**
        @brief 缓存事件参数
        */
        class BPCacheEventArg
        {
        public:

            /**
            @brief 构造函数
            @param[in] domain 专业代码,默认值0x000003EB表示【BIMBase建模软件】专业.
            */
            BIMBASEAPI_EXPORT BPCacheEventArg(BPProjectP project, UInt16 domain = 0x000003EB, void* userData = nullptr);

            /**
            @brief 获取工程文件,可为空.
            */
            BPProjectP getProject() const { return m_project; }

            /**
            @brief 获取专业代码
            @return 如果用户未指定,则返回默认值BIMBase建模软件专业代码.
            */
            UInt16 getDomainCode() const { return m_nDomainCode; }

            /**
            @brief 获取用户数据,可为空.
            */
            void* getUserData() const { return m_userData; }

        private:
            BPProjectP              m_project;
            UInt16                  m_nDomainCode;  // 当前专业或要切换到的专业
            void*                   m_userData;
        };

        /**
        @brief 缓存管理事件
        @details 一般情况是一个缓存管理类继承此类后,当程序或数据状态变化时会调用相应的虚接口函数,用户可以在此函数里对缓存进行一致性的管理.
        */
        class BPCacheEventListener
        {
        public:
            /**
            @brief 主工程文件级的缓存加载事件
            @details 工程文件加载完成后触发此事件
            */
            BIMBASEAPI_EXPORT virtual void onProjectCacheLoad(BPCacheEventArgCR arg);

            /**
            @brief 主工程文件级的缓存卸载事件
            @details 工程文件关闭完成后触发此事件
            */
            BIMBASEAPI_EXPORT virtual void onProjectCacheUnLoad(BPCacheEventArgCR arg) = 0;

            /**
            @brief 专业级的缓存加载事件
            @details 新专业切换完成后触发此事件
            */
            BIMBASEAPI_EXPORT virtual void onDomainCacheLoad(BPCacheEventArgCR arg);

            /**
            @brief 专业级的缓存卸载事件
            @details 新专业切换完成后触发此事件
            */
            BIMBASEAPI_EXPORT virtual void onDomainCacheUnLoad(BPCacheEventArgCR arg);

        protected:
            BIMBASEAPI_EXPORT BPCacheEventListener();
        };

        /**
        @brief 缓存管理事件监听器中心
        @date 创建日期:2024-04-25
        */
        class BPCacheManagerEventListenerCenter : public BPNonCopyableClass
        {
        public:
            BIMBASEAPI_EXPORT void   addListener(BPCacheEventListenerP listener, BPRegisterModule hm = BIMBase::getRegisterHModule());
            BIMBASEAPI_EXPORT void   dropListener(BPCacheEventListenerP listener, BPRegisterModule hm = BIMBase::getRegisterHModule());

            BIMBASEAPI_EXPORT static   BPCacheManagerEventListenerCenter& getInstance();
        };

    }
}// P3D namespace end

#endif // BP_BPData_BPProject_H
