/*!
* Copyright (C), 2019-2028, Beijing GLory PKPM Tech. Co., Ltd.
* @file BPEntity.h
* @author GLory
* @date 三月 2020
* @note P3D图形元素管理
*/

#ifndef BP_BPData_BPEntity_H
#define BP_BPData_BPEntity_H


namespace BIMBase {
    namespace Core
    {
        /**
        @brief  实体类
        @details
        @date 创建日期:2021-07-29
        */
        class BPEntity : public ::BIMBase::BPRefCountedBase
        {
        public:
            /**
            @brief 构造函数
            @param[in] BPEntityCR right: 构造BPEntity所参考的BPEntity常引用
            */
            BIMBASEAPI_EXPORT                               BPEntity(BPEntityCR right);

            /**
            /**
            @brief 构造函数
            @param[in] BPEntityId const& entityId: 构造BPEntity所参考的BPEntity的Id
            @param[in] BPModelBaseCR pModel: BPEntity所在的BPModel基类常引用
            @note 使用前应判断BPEntityId的有效性
            @warning 无效的BPEntityId会导致错误
            @note 如果属于linkModel的entity,则参数pModel为一个BPModelLink实例.
            */
            BIMBASEAPI_EXPORT                               BPEntity(BPEntityId const& entityId, BPModelBaseCR pModel);

            /**
            @brief 析构函数
            */
            BIMBASEAPI_EXPORT virtual                       ~BPEntity();

            /**
            @brief 赋值函数
            @param[in] BPEntityCR source: 构造BPEntity所参考的BPEntity常引用
            */
            BIMBASEAPI_EXPORT BPEntityR                     operator= (BPEntityCR source);

            /**
            @brief 构造函数
            @param[in] BPEntityId: 构造BPEntity所参考的BPEntity的Id
            @param[in] BPProjectR: BPEntity所在的BPProject引用
            @note 使用前应判断BPEntityId的有效性
            @warning 无效的BPEntityId会导致错误
            */
            BIMBASEAPI_EXPORT                               BPEntity(BPEntityId, BPProjectR);

            /**
            @brief 获取BPEntityId
            @return 实体Id
            @warning 实体被加入到Model之前无有效的BPEntityId
            @see addToModel()
            */
            BIMBASEAPI_EXPORT BPEntityId                    getEntityId(void) const;

            /**
            @brief 获取实体所在的BPModel指针
            @return 所在的BPModel指针
            @note 实体被加入到Model之前无有效的BPEntityId
            @see getBPModelBase()
            */
            BIMBASEAPI_EXPORT BPModelP                      getBPModel() const;

            /**
            @brief 获取实体所在的BPModelBase指针
            @return 所在的BPModelBase指针
            @note 实体被加入到Model之前无有效的BPEntityId，当实体所在的Model被链接到其他Model中时，返回的BPModelBase指针为实体所在的ModelLink的指针
            @see getBPModel()
            */
            BIMBASEAPI_EXPORT BPModelBaseP                  getBPModelBase() const;

            /**
            @brief 获取实体所在的BPProject指针
            @return 所在的BPProject指针
            */
            BIMBASEAPI_EXPORT BPProjectP                    getBPProject() const;

            /**
            @brief 获取实体关联的BPData数据对象的Id
            @return 关联的BPDataId
            @note 并非所有实体都有关联的BPDataId，应判断BPDataId的有效性
            */
            BIMBASEAPI_EXPORT BPDataId                      getDataId() const;

            /**
            @brief 判断是否为图形实体
            @return
            - true    图形实体
            - false 非图形实体
            */
            BIMBASEAPI_EXPORT bool                          isGraphics(void) const;

            /**
            @brief 判断是否为三维实体
            @return
            - true    三维实体
            - false 非三维实体
            */
            BIMBASEAPI_EXPORT bool                          is3DEntity(void) const;

            /**
            @brief 判断实体有效性
            @return
            - true    有效实体
            - false 无效实体
            */
            BIMBASEAPI_EXPORT bool                          isValid() const;

            /**
            @brief 获取实体关联数据对象类型的SchemaName
            @param[out] ::p3d::PStringR schemaName: schema名称
            @return
            - ::p3d::P3DStatus::SUCCESS 获取成功
            - ::p3d::P3DStatus::ERROR 获取失败
            @note 实体无关联的BPData时无相关schema名称
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus               getSchemaName(::p3d::PStringR schemaName) const;

            /**
            @brief 获取实体关联数据对象类型的ClassName
            @param[out] ::p3d::PStringR className: class名称
            @return
            - ::p3d::P3DStatus::SUCCESS 获取成功
            - ::p3d::P3DStatus::ERROR 获取失败
            @note 实体无关联的BPData时无相关class名称
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus               getClassName(::p3d::PStringR className) const;

            /**
            @brief 获取实体关联数据对象类型的描述
            @param[out] ::p3d::PStringR desc: 数据对象类型描述
            @return
            - ::p3d::P3DStatus::SUCCESS 获取成功
            - ::p3d::P3DStatus::ERROR 获取失败
            @warning 实体无关联的BPData时无相关数据类型描述
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus               getClassDescription(::p3d::PStringR desc) const;

            /**
            @brief 获取实体关联数据对象类型Id
            @return 关联数据对象类型Id
            @warning 实体无关联的BPData时返回无效Id
            */
            BIMBASEAPI_EXPORT PClassId                      getClassId() const;

            /**
            @brief 判断关联的数据对象类型是否为给定类型
            @param[in] ::p3d::PStringCR schemaName: Schema名称
            @param[in] ::p3d::PStringCR className: Class名称
            @param[in] bool allowDerived: 是否判断派生类
            @return 是否为给定数据对象类型
            @note
            allowDerived = false时，实体关联数据对象类型与给定类型完全一致时返回true
            allowDerived = true时，实体关联数据对象类型为给定类型及其派生类时均返回true
            */
            BIMBASEAPI_EXPORT bool                          isKindOfType(::p3d::PStringCR schemaName, ::p3d::PStringCR className, bool allowDerived = false) const;

            /**
            @brief 将实体加入指定Model
            @return 加入操作标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus               addToModel(void);

            /**
            @brief 删除实体
            @return 删除操作标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            @note 仅删除实体，不删除实体关联的BPData数据对象
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus               deleteFromModel(void);

            /**
            @brief 用当前实体数据更新已经持久化存储的图形实体
            @details 当前实体必须是尚未存储图形实体,一般是在BPGraphics::finish()调用之后,但是未调用过BPGraphics::save()的情况,通过BPGraphics::getEntityR()接口返回的实体.
            @param[in] BPEntityP oldEntity: 被更新的实体指针
            @param[in] bool regenGeometry: 是否重新创建几何图形
            @return 更新操作标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            @note 若更新操作不影响实体几何图形的变化，如修改图层、颜色、线宽等，可设置regenGeometry = false，这时不会调用创建几何图形的计算流程，可提高操作性能
            @deprecated replaceWithNewEntity(BPEntityP newEntity);
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus               replaceInModel(BPEntityP oldEntity, bool regenGeometry = true);


            // ____<pkpm_inner_begin>____
            /**
            @brief 实体复制
            @param[in] BPEntityCR entity: 复制源实体常引用
            */
            BIMBASEAPI_EXPORT void                          duplicate(BPEntityCR entity);
            // ____<pkpm_inner_end>____

            /**
            @brief 获取实体显示信息,目前只支持基本图形实体
            @details 获取实体颜色、线宽、线型
            @param[out] UInt32 &color: 返回实体颜色索引
            @param[out] UInt32 &weight: 返回实体线宽
            @param[out] Int32 &style: 返回实体线型索引
            @note 目前只支持基本图形实体,对于一般的专业构件图形实体目前只能通过BPGraphics::getGraphicsFromEntity获取各part的颜色,TODO:对一般专业构件的支持
            */
            BIMBASEAPI_EXPORT void                          getSymbology(UInt32& color, UInt32& weight, Int32& style) const;
            
            /**
            @brief 设置实体显示信息
            @details 设置实体颜色、线宽、线型等显示属性，设置后需要调用replaceWithNewEntity方法进行刷新.
            @param[in] UInt32 &color: 实体颜色索引
            @param[in] UInt32 &weight: 实体线宽 ，索引取值和线宽（单位毫米）对应如下：
              取值：0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23
              线宽：0.00 0.05 0.09 0.13 0.15 0.18 0.20 0.25 0.30 0.35 0.40 0.50 0.53 0.60 0.70 0.80 0.90 1.00 1.06 1.20 1.40 1.58 2.00 2.11
            @param[in] Int32 &style: 实体线型索引
            */
            BIMBASEAPI_EXPORT void                          setSymbology(UInt32 color, UInt32 weight, Int32 style);

            /**
            @brief 获取实体颜色索引
            @param[out] UInt32 &color: 返回实体颜色索引
            */
            BIMBASEAPI_EXPORT void                          getColor(UInt32& color) const;

            /**
            @brief 设置实体颜色，设置后需要调用replaceWithNewEntity方法进行刷新.
            @param[in] UInt32 color: 实体颜色索引
            */
            BIMBASEAPI_EXPORT void                          setColor(UInt32 color);

            /**
            @brief 获取实体线宽
            @param[out] UInt32 &weight: 返回实体线宽
            */
            BIMBASEAPI_EXPORT void                          getWeight(UInt32& weight) const;

            /**
            @brief 设置实体线宽，设置后需要调用replaceWithNewEntity方法进行刷新.
            @param[in] UInt32 weight: 实体线宽，索引取值和线宽（单位毫米）对应如下：
              取值：0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23
              线宽：0.00 0.05 0.09 0.13 0.15 0.18 0.20 0.25 0.30 0.35 0.40 0.50 0.53 0.60 0.70 0.80 0.90 1.00 1.06 1.20 1.40 1.58 2.00 2.11
            */
            BIMBASEAPI_EXPORT void                          setWeight(UInt32 weight);

            /**
            @brief 获取实体线型
            @param[out] Int32 &style: 返回实体线型
            */
            BIMBASEAPI_EXPORT void                          getLineStyle(Int32& style) const;

            /**
            @brief 设置实体线型，设置后需要调用replaceWithNewEntity方法进行刷新.
            @param[in] Int32 style: 实体线型索引
            */
            BIMBASEAPI_EXPORT void                          setLineStyle(Int32 style);

            /**
            @brief 获取实体线型比例
            @param[out] double scale: 实体线型比例
            @note 仅对自定义线型生效
            */
            BIMBASEAPI_EXPORT void                          getLineStyleScaleFromEntity(double& scale) const;

            /**
            @brief 设置实体线型比例，设置后需要调用replaceWithNewEntity方法进行刷新.
            @param[in] double scale: 实体线型比例
            @note 仅对自定义线型生效
            */
            BIMBASEAPI_EXPORT void                          setLineStyleScaleToEntity(double scale);

            /**
            @brief 获取实体图层Id
            @return 实体图层Id
            */
            BIMBASEAPI_EXPORT PLayerId                      getLayerId() const;

            /**
            @brief 设置实体图层，设置后需要调用replaceWithNewEntity方法进行刷新.
            @param[out] PLayerId const &layerId: 返回实体图层Id
            @note 允许传入无效的图层id NULL_LAYER_ID
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus               setLayerId(PLayerId const& layerId);

            /**
            @brief 获取实体透明度
            @return 实体透明度值
            @note 透明度取值范围为0-1，1表示完全透明
            */
            BIMBASEAPI_EXPORT double                        getTransparency() const;

            /**
            @brief 设置实体透明度，设置后需要调用replaceWithNewEntity方法进行刷新.
            @param[in] double dTransparency: 实体透明度
            @note 透明度取值范围为0-1，1表示完全透明
            */
            BIMBASEAPI_EXPORT void                          setTransparency(double dTransparency);

            /**
            @brief 对当前entity应用一个仿射变换
            @param[in] transform: 变换矩阵
            */
            BIMBASEAPI_EXPORT  void                         setTransfrom(::p3d::GeTransformCR transform);

            /**
            @brief 对当前entity设置是否可以捕捉
             @param[in] bSnap: 是否可以捕捉
            */
            BIMBASEAPI_EXPORT  void                         setSnapPossible(bool bSnap);

            /**
            @brief 对当前entity的捕捉是否开启
            @return 当前entity的捕捉是否开启
             */
            BIMBASEAPI_EXPORT  bool                         isSnapPossible();


            /**
            @brief 获取当前实体的最后修改时间
            @details 返回从1970年1月1日零时距离当前本地时间,单位毫秒.
            @return 当前实体的最后修改时间
            */
            BIMBASEAPI_EXPORT UInt64                        getLastModifyTime() const;

            /**
            @brief 构造空实体对象
            */
            BIMBASEAPI_EXPORT static BPEntityPtr            create();

#pragma region PKPMInner


            // ____<pkpm_inner_begin>____

            /**
            @brief 获取实体类别
            */
            BIMBASEAPI_EXPORT p3d::platform::P3DEntityType   getEntityType() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus            applyActiveSettings();
            BIMBASEAPI_EXPORT::p3d::P3DStatus            applyActiveAreaSettings(int fillMode);
            BIMBASEAPI_EXPORT::p3d::P3DStatus            applyActiveAreaFill(int fillMode);
            BIMBASEAPI_EXPORT::p3d::P3DStatus            applyActiveSolidFill();
            BIMBASEAPI_EXPORT::p3d::P3DStatus            applyActiveGradientFill();
            // ____<pkpm_inner_end>____
            /**
            @brief 使实体数据无效
            */
            BIMBASEAPI_EXPORT void                invalidate() const;

            /**
            @brief 设置实体不可见标识
            @param[in] bool invisible: true-不可见；flase-可见
            @return
            - true 设置成功
            - false 设置失败
            @note 此设置为实体显示控制的最高级别，设置实体不可见标识为true时，即使实体在显示集内也不可见,@see setInDisplaySet()
            */
            BIMBASEAPI_EXPORT bool setInvisiblePermanent(bool invisible = true);

            /**
			@brief 获取实体隐藏状态
			@return
			- true 隐藏
			- false 未隐藏
			@note 此接口为获取实体显示控制的最高级别的状态
			*/
            BIMBASEAPI_EXPORT::p3d::P3DStatus getInvisiblePermanent(bool& invisible) const;

            /**
            @brief 判断是否在选择集中
            @return
            - true 在选择集中
            - false 不在选择集中
            @see getBool(bool& bOut)
            */
            BIMBASEAPI_EXPORT bool                isInSelectionSet() const;

            /**
            @brief 设置实体到显示集中
            @details 显示集中的实体在指定Model中可见
            @param[in] BPModelBaseP modelBase: 实体显示的Model
            @param[in] bool yesNo: 实体是否显示
            */
            BIMBASEAPI_EXPORT void                 setInDisplaySet(BPModelBaseP modelBase, bool yesNo);

            /**
            @brief 判断实体是否显示集中
            @details 判断实体是否在指定Model的显示集中
            @param[in] BPModelBaseP modelBase: 实体显示的Model
            @return
            - true 在显示集中
            - false 不在显示集中
            */
            BIMBASEAPI_EXPORT bool                 isInDisplaySet(BPModelBaseP modelBase);

            /**
            @brief 设置实体不显示标识
            @details 设置实体在指定Model中是否的不显示标识
            @param[in] BPModelBaseP modelBase: 实体显示的Model
            @param[in] bool yesNo: true-标识有效；false-标识无效
            */
            BIMBASEAPI_EXPORT void                 setUndisplayedFlag(BPModelBaseP modelBase, bool yesNo);

            /**
            @brief 判断实体显示状态
            @details 判断实体是否在指定model中显示
            @param[in] BPModelBaseP modelBase: 实体显示的Model
            @return
            - true 不显示
            - false 显示
            */
            BIMBASEAPI_EXPORT bool                 isUndisplayed(BPModelBaseP modelBase);

            /** 设置附加数据
            *
            * @param nDataId 附加数据块ID，必须在1-20范围内
            * @param dataPtr 附加数据块首地址
            * @param nDataSize 附加数据块大小，必须小于等于2M
            * @param bToUpdateIfExisted true：如果已经存在此ID的数据，则进行更新，false:如果已经存在此ID的数据则返回::p3d::P3DStatus::ERROR.
            * @return   附加成功返回::p3d::P3DStatus::SUCCESS，否则返回::p3d::P3DStatus::ERROR
            * @note 1.当前BPEntity可以是尚未存储的.
            *        2.必须保存或更新当前BPEntity后才能保存附加数据.
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus            setAttachData(const int nDataId, const void* dataPtr, const int nDataSize, bool bToUpdateIfExisted);

            /**
            @brief 临时接口,setAttachData的优化版本
            @details 如果当前entity处于非编辑状态,仅需要通过此接口设置附加数据,那么调用用完此接口不再需要调用replaceInModel接口,这样比setAttachData接口性能更好
                     ,尤其针对几何刷新/领域数据对象反序列化非常慢的构件.
            @note  注意:此接口是临时接口,后续版本会与setAttachData统一.
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus            setAttachData_beta(const int nDataId, const void* dataPtr, const int nDataSize, bool bToUpdateIfExisted);

            /** 获取指定ID的附加数据块的大小
            *
            * @param nLength 数据块的字节大小
            * @param nDataId 数据块的ID
            * @return   获取附加数据成功返回::p3d::P3DStatus::SUCCESS，失败或无附加数据则返回::p3d::P3DStatus::ERROR
            * @note
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus            getAttachDataLength(OUT Int32& nDataSize, const Int32 nDataId) const;

            /** 获取附加数据块
            *
            * @param data 获取到的附加数据块指针
            * @param nDataSize 附加数据块的实际大小
            * @param nDataId 附加数据块的ID
            * @return   获取附加数据成功返回::p3d::P3DStatus::SUCCESS，否则返回::p3d::P3DStatus::ERROR
            * @note
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus            getAttachData(OUT void* data, OUT Int32& nDataSize, const Int32 nDataId) const;

            // ____<pkpm_inner_begin>____
            struct BPCustomClassInfo
            {
                ::p3d::PString m_customClassName;
                ::p3d::PString m_displayLabel;
                ::p3d::PString m_description;
            };

            BIMBASEAPI_EXPORT static bool addCustomClassInfoToEntity(::BIMBase::Core::BPEntityP entityP, const BPCustomClassInfo& params);

            BIMBASEAPI_EXPORT static bool getCustomClassInfoFromEntity(::BIMBase::Core::BPEntityP entityP, BPCustomClassInfo& params);

            // ____<pkpm_inner_end>____
#pragma region DIM
            /// @-------------- for dimElement
            BIMBASEAPI_EXPORT bool entityIsDim() const;

            /// @brief 获取标注实体的样式
            BIMBASEAPI_EXPORT BPDimensionStylePtr        getDimensionStyle() const;

            /// @brief 设置标注实体的样式
            BIMBASEAPI_EXPORT void              applyDimensionStyle(BPDimensionStyleR dimStyle, bool retainOverrides);

            /// @brief 标注的点
            BIMBASEAPI_EXPORT int getDimNumPoints() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus extractDimPoint(P3D_NAMESPACE_NAME::GePoint3d& point, int iPoint) const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimPoint(P3D_NAMESPACE_NAME::GePoint3d const* point, int iPoint);

			/// @brief 直径、半径标注圆心大小
			BIMBASEAPI_EXPORT double getDimCenterSize() const;
			BIMBASEAPI_EXPORT::p3d::P3DStatus setDimCenterSize(double centerSize);

            /// @brief 直径、半径标注圆心标记类型
            BIMBASEAPI_EXPORT UInt16 getDimCenterMarkType() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimCenterMarkType(UInt16 centerMarkType);

            /// @brief 标注的高度
            BIMBASEAPI_EXPORT double getDimHeight() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimHeight(double dHeight);

            /// @brief 标注的Text-Offset
            BIMBASEAPI_EXPORT int getDimNumSegments() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus getDimTextOffset(int segmentNo, P3D_NAMESPACE_NAME::GePoint2d& offset) const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimTextOffset(int segmentNo, P3D_NAMESPACE_NAME::GePoint2dCR offset);

            BIMBASEAPI_EXPORT::p3d::P3DStatus getGeomTextOffset(P3D_NAMESPACE_NAME::GePoint2d& offset) const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setGeomTextOffset(P3D_NAMESPACE_NAME::GePoint2dCR offset);

            /// @brief 获取标注文字信息（目前只测试了线型标注）
            /// @brief 文字位置-方向-宽度-高度
            BIMBASEAPI_EXPORT::p3d::P3DStatus getDimTextInfo(P3D_NAMESPACE_NAME::GePoint3d& textPosition, P3D_NAMESPACE_NAME::GeVec3d& textDirection, double& dTextWidth, double& dTextHeight, int dimSegment = 1) const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus getLinearWitnessPoint(P3D_NAMESPACE_NAME::GeVec3d& xvec, P3D_NAMESPACE_NAME::GeVec3d& yvec, P3D_NAMESPACE_NAME::GeSegment3d& wit1, P3D_NAMESPACE_NAME::GeSegment3d& wit2, int dimSegment = 1) const;

            /// @brief 设置文字位置
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimTextPosition(P3D_NAMESPACE_NAME::GePoint3dCR textPosition, int segment = 1);

			/// @brief 获取文字替代
			BIMBASEAPI_EXPORT::p3d::P3DStatus getReplaceText(p3d::pvector<p3d::PString>& replaceTexts) const;
			/// @brief 设置文字替代
			BIMBASEAPI_EXPORT::p3d::P3DStatus setReplaceText(p3d::pvector<p3d::PString>replaceTexts);

            /// @brief 设置文字往4个方向偏移 dOffset设置为0，就是用默认对称的方法
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimTextUp(double dOffset, int dimSegment = 1);
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimTextDown(double dOffset, int dimSegment = 1);
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimTextLeft(double dOffset, int dimSegment = 1);
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimTextRight(double dOffset, int dimSegment = 1);

			/// @brief 获取文字显示文字
            BIMBASEAPI_EXPORT::p3d::P3DStatus getDimDisplayText(p3d::pvector<p3d::PString>& text);

            //-----------------------------------1.线------------------------
            /// @brief 尺寸线-颜色
            BIMBASEAPI_EXPORT UInt32 dimclrd() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimclrd(UInt32 clrValue);

            /// @brief 尺寸线-线型
            BIMBASEAPI_EXPORT Int32 dimltype() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimltype(Int32 lsValue);

            /// @brief 尺寸线-线宽
            BIMBASEAPI_EXPORT UInt32 dimlwd() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimlwd(UInt32 weightValue);
            
            /// @brief 尺寸线-超出标记
            BIMBASEAPI_EXPORT double dimdle() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimdle(double dValue);

            /// @brief 尺寸界线-颜色
            BIMBASEAPI_EXPORT UInt32 dimclre() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimclre(UInt32 clrValue);

            /// @brief 尺寸界线1-线型
            BIMBASEAPI_EXPORT Int32 dimltex1() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimltex1(Int32 lsValue);

            /// @brief 尺寸界线2-线型
            /// @note 尺寸界线2和尺寸界线1无法区分设置，所以这2个函数效果一样
            BIMBASEAPI_EXPORT Int32 dimltex2() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimltex2(Int32 lsValue);

            /// @brief 尺寸界线-线宽
            BIMBASEAPI_EXPORT UInt32 dimlwe() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimlwe(UInt32 weightValue);

            /// @brief 尺寸界线-超出尺寸线
            BIMBASEAPI_EXPORT double dimexe() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimexe(double dValue);

            /// @brief 尺寸界线-起点偏移量
            BIMBASEAPI_EXPORT double dimexo() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimexo(double dValue);

            /// @brief 尺寸界线1隐藏
            BIMBASEAPI_EXPORT bool dimse1() const;
            BIMBASEAPI_EXPORT::p3d::StatusInt setDimse1(bool bShow);

            /// @brief 尺寸界线2隐藏
            BIMBASEAPI_EXPORT bool dimse2() const;
            BIMBASEAPI_EXPORT::p3d::StatusInt setDimse2(bool bShow);

            bool _getArrowInfo(::p3d::PStringR arrowName, double& arrowSize, double& arrowSizeScale, bool& arrowWidthIsFix, int nArrowIndex) const;
            void _setForArrowType(::BIMBase::Core::P3DDimStyleProp_Terminator_Type termType, P3DDimStyleProp_Terminator_Arrowhead fillType, bool isThrought);
            ::p3d::P3DStatus _setDimblk(::p3d::PStringCR arrowName, int nArrowIndex);

            /// @brief 符号和箭头-箭头-第二个
            BIMBASEAPI_EXPORT::p3d::PString dimblk1New() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimblk1(::p3d::PStringCR arrowName); /// 新接口

            /// @brief 符号和箭头-箭头-第二个
            BIMBASEAPI_EXPORT::p3d::PString dimblk2New() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimblk2(::p3d::PStringCR arrowName); /// 新接口

            /// @brief 符号和箭头-箭头大小
            BIMBASEAPI_EXPORT double dimasz() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimasz(double dSize);

            //-----------------------------------3.文字------------------------
            /// @brief 文字-文字外观-文字样式
            BIMBASEAPI_EXPORT UInt32 dimtxsty() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimtxsty(UInt32 idTextStyle); //这个函数不要用了，因为只是修改id没有效果
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimtxsty2(BPTextStylePtr pTextStyle, ::BIMBase::Core::BPProjectR project);

            /// @brief 文字-文字外观-文字颜色
            BIMBASEAPI_EXPORT UInt32 dimclrt() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimclrt(UInt32 clrValue);

            /// @brief 文字-文字外观-文字高度
            BIMBASEAPI_EXPORT double dimtxt() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimtxt(double dSize);

            /// @brief 文字-文字外观-是否绘制文本框
            BIMBASEAPI_EXPORT bool dimgap1() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimgap1(bool has);

            /// @brief 文字-文字位置-垂直
            /// 0-居中 1-上方 2-外部
            BIMBASEAPI_EXPORT int dimtad() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimtad(int v);

            /// @brief 文字-文字位置-水平
            /// 0-居中 1-第一条尺寸界线 2-第二条尺寸界线
            BIMBASEAPI_EXPORT int dimjust() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimjust(int v);

            /// @brief 文字-文字位置-从尺寸线偏移
            BIMBASEAPI_EXPORT double dimgap() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimgap(double v);

            /// @brief 文字对齐
            BIMBASEAPI_EXPORT bool dimtoh() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimtoh(bool bDimtoh);

            /// @brief 文字移动
			BIMBASEAPI_EXPORT int dimtmove() const;
			BIMBASEAPI_EXPORT::p3d::P3DStatus setDimtmove(int v);

            //-----------------------------------4.调整------------------------

            /// @brief 调整-调整选项
            /// 0-文字和箭头 1-箭头 2-文字 3-文字或箭头
            BIMBASEAPI_EXPORT int dimatfit() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimatfit(int v);

            /// @brief 调整-调整选项-文字始终保持在尺寸界线之间
            BIMBASEAPI_EXPORT bool dimtix() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimtix(bool v);

            /// @brief 调整-标注特征比例-使用全局比例
            BIMBASEAPI_EXPORT double dimscale() const;
            //注意：若setDimscale传入的值为0或负数则直接返回ERROR
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimscale(double v);
            //将标注的比例设置为跟随模型空间比例
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimScaleFollowModel();
            /// @brief 调整-优化-在尺寸界线之间绘制尺寸线
            BIMBASEAPI_EXPORT bool dimtofl() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimtofl(bool v);

            //-----------------------------------5.主单位------------------------

            /// @brief 主单位-线性标注-单位格式
            /// 0-科学 1-小数 2-分数
            BIMBASEAPI_EXPORT int dimlunit() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimlunit(int v);

            /// @brief 主单位-线性标注-单位格式
            /// 0-7
            BIMBASEAPI_EXPORT int dimdec() const;
            BIMBASEAPI_EXPORT::p3d::P3DStatus setDimdec(int v);

			/// @brief 主单位-线性标注-测量比例
			BIMBASEAPI_EXPORT double dimlfac() const;
			BIMBASEAPI_EXPORT::p3d::P3DStatus setDimlfac(double v);

			//-----------------------------------5.2 角度主单位------------------------
/// @brief 主单位-线性标注-单位格式
/// 0-科学 1-小数 2-分数
			BIMBASEAPI_EXPORT int dimaunit() const;
			BIMBASEAPI_EXPORT::p3d::P3DStatus setDimaunit(int v);

			/// @brief 主单位-线性标注-单位格式
			/// 0-7
			BIMBASEAPI_EXPORT int dimadec() const;
			BIMBASEAPI_EXPORT::p3d::P3DStatus setDimadec(int v);
            /// @-------------- end for dimElement
#pragma endregion

            /// @-------------- for polyline
            BIMBASEAPI_EXPORT int polyline_numVerts() const;

            // @fillColor :if nullptr, edge color as fill color
            BIMBASEAPI_EXPORT bool                addSolidFill(uint32_t* fillColor = nullptr);



            // ____<pkpm_inner_end>____
#pragma endregion

            /**
            @brief 获取实体包围盒
            @details 获取实体所在范围可能的最大包围盒
            @param[out] p3d::GeRange3d &range: 返回包围盒
            @return 获取标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            - @note 此接口存在精度小于1mm的误差(向上取整),如果需要精确值可以使用calculateRange接口.
					返回的range有可能为无效值，需要通过isValidNum接口检查是否有效.
			*/
            BIMBASEAPI_EXPORT::p3d::P3DStatus            getRange(p3d::GeRange3d& range) const;

            /**
            @brief 计算实体包围盒
            @details 计算获取实体边界包围盒
            @param[out] p3d::GeRange3d &range: 返回包围盒
            @return 获取标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            @note 此接口通过几何图形计算边界包围盒，复杂几何实体大批量调用时需考虑性能问题
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus            calculateRange(p3d::GeRange3d& range);
            /**
			@brief 检查此实体是否支持特定的操作类型.
			*/
            BIMBASEAPI_EXPORT bool                       isSupportedOperation(BPEntityOperation oper) const;

			//! Convert a 2d entity to it's 3d form.
			//! @param[out]     eeh             The enity to convert.
			//! @param[in]      elevation       The z component to apply to 2d point data.
            BIMBASEAPI_EXPORT void convertTo3d(BPEntityR eeh, double elevation);

			//! Convert a 3d entity to it's 2d form.
			//! @param[out]     eeh             The entity to convert.
			//! @param[in]      flattenTrans    Transform to apply to flatten the entity to a plane.
			//! @param[in]      flattenDir      Direction used to compute flatten transform.
			//! @note A 3d only entity like CONE_ELM will be converted into a block containing curve geometry.
			//! @bsimethod
            BIMBASEAPI_EXPORT void convertTo2d(BPEntityR eeh, p3d::GeTransformCR flattenTrans, p3d::GeVec3dCR flattenDir);

			//! Test whether this entity is planar. Callers should be aware that the answer may be expensive to determine.
			//! @param[in]      el                  Entity to test
			//! @param[out]     normal              The normal vector. Only valid if the method returns true. May be NULL.
			//! @param[out]     point               A point on the plane. Only valid if the method returns true. May be NULL.
			//! @param[in]       inputDefaultNormal  A normal vector to be used in the case where the element does not define a plane (a line, for example).
			//! @bsimethod
            BIMBASEAPI_EXPORT inline  bool isPlanar(p3d::GeVec3dP normal, p3d::GePoint3dP point, p3d::GeVec3dCP inputDefaultNormal) const;


			//! set display Priority for drawing model entity.
			//! @param[in]      priority            // entity display priority 
			//! @bsimethod
            BIMBASEAPI_EXPORT inline  void setDisplayPriority(Int32 priority);

        private:
            BPEntity();
        protected:

            void* m_imp;

            bool m_bImpRef;
            
        };

        /**
        @brief  实体集
        @details  实体数组，包含多个实体指针的数据集
        @date 创建日期:2021-08-02
        */
        class BPEntityArray : public ::BIMBase::BPRefCountedBase
        {

        public:
            /**
            @brief 构造函数
            @details 构造实体集
            */
            BIMBASEAPI_EXPORT                   BPEntityArray();

            // ____<pkpm_inner_begin>____
            // TODO-NRG(18/09/2021):暂时不暴露
            /**
            @brief 构造函数
            @details 构造实体集
            @param[in] BPEntityArray&: 构造实体集所参考BPEntityArray引用
            @param[in] bool bRef: 引用方式
            */
            BIMBASEAPI_EXPORT                   BPEntityArray(BPEntityArray&, bool bRef = true);
            // ____<pkpm_inner_end>____

            /**
            @brief =操作
            @param[in] BPEntityArrayCR source: 构造实体集所参考BPEntityArray引用
            */
            BIMBASEAPI_EXPORT BPEntityArrayR    operator= (BPEntityArrayCR source);

            /**
            @brief 析构函数
            */
            BIMBASEAPI_EXPORT virtual           ~BPEntityArray();

            /**
            @brief 设置实体集容量
            @details 设置实体集包含的实体对象个数
            @param[in] int nEntries: 数量
            */
            BIMBASEAPI_EXPORT void                setCapacity(int nEntries);

            /**
            @brief 插入实体集
            @details 在实体集中插入实体对象
            @param[in] BPEntityR entity: 要插入的实体
            @param[in] bool atHead: 是否插入到首位（缺省为false，表示按顺序添加）
            */
            BIMBASEAPI_EXPORT void                insert(BPEntityR entity, bool atHead = false);

            /**
            @brief 删除实体集中实体
            @details 将实体从实体集中移除
            @param[in] uint32_t nIndex: 要移除的实体索引
            */
            BIMBASEAPI_EXPORT bool                erase(uint32_t nIndex);

            /**
            @brief 高亮实体集
            @details 将实体集中实体高亮显示
            */
            BIMBASEAPI_EXPORT void                hilite();

            /**
            @brief 清除实体集高亮显示
            @details 将实体集中实体恢复到原始显示状态
            */
            BIMBASEAPI_EXPORT void                clearHilite();

            /**
            @brief 清除实体集
            @details 清除实体集高亮显示并清除实体集中实体记录
            */
            BIMBASEAPI_EXPORT void                clear();

            /**
            @brief 清除实体集
            @details 将实体集中实体记录清除
            */
            BIMBASEAPI_EXPORT void                empty();

            /**
            @brief 判断实体集是否为空
            @details 判断实体集中是否包含实体记录
            @return 是否包含实体记录
            */
            BIMBASEAPI_EXPORT bool                isEmpty();

            /**
            @brief 通过BPViewport构造实体集
            @details 将指定BPViewport中显示的实体加入到实体集中
            */
            BIMBASEAPI_EXPORT void                queryFromViewport(BPViewportR viewPort);

            /**
            @brief 获取实体集中实体个数
            @return 实体个数
            */
            BIMBASEAPI_EXPORT int32_t            getCount() const;

            /**
            @brief 获取实体集中第一个实体指针
            @return 实体指针
            */
            BIMBASEAPI_EXPORT BPEntityPtr        getFirst() const;

            /**
            @brief 获取实体集中最后一个实体指针
            @return 实体指针
            */
            BIMBASEAPI_EXPORT BPEntityPtr        getLast() const;

            /**
            @brief 获取实体集中指定位置实体指针
            @param[in] size_t i: 实体索引
            @return 实体指针
            */
            BIMBASEAPI_EXPORT BPEntityPtr        getByIndex(size_t i) const;

            /**
            @brief 获取实体集中指定位置实体指针
            @param[in] uint32_t nIndex: 实体索引
            @return 实体指针
            */
            BIMBASEAPI_EXPORT BPEntityPtr        operator[](uint32_t nIndex) const;

            /**
            @brief 在所有活动视口中显示实体集中实体
            @param[in] BPDrawMode drawMode: 显示模式
            @param[in] BPDrawPurpose drawPurpose: 显示用途
            @see BPDrawMode, @see BPDrawPurpose
            */
            BIMBASEAPI_EXPORT void                drawInAllViews(BPDrawMode drawMode, BPDrawPurpose drawPurpose);

            /**
            @brief 在指定视口中显示实体集中实体
            @param[in] BPDrawMode drawMode: 显示模式
            @see BPDrawMode
            */
            BIMBASEAPI_EXPORT void                draw(BPViewportP viewport, BPDrawMode drawMode);

            /**
            @brief 在指定视口中显示实体集中实体
            @param[in] BPDrawMode drawMode: 显示模式
            @param[in] BPDrawPurpose drawPurpose: 显示用途
            @param[in] BPRedrawOperationP redrawOp: 显示绘制操作接口
            @note 可通过派生BPRedrawOperation并实现相关绘制操作接口可实现对显示流程和效果的控制
            @see BPDrawMode, @see BPDrawPurpose, @see BPRedrawOperation
            */
            BIMBASEAPI_EXPORT void                draw(BPViewportP viewport, BPDrawMode drawMode, BPDrawPurpose drawPurpose, BPRedrawOperationP redrawOp);

            /**
            @brief 将拾取实体加入实体集
            @details 将拾取数据转换为实体对象并加入到实体集中
            @param[in] BPPickDataCP pickData: 拾取数据
            @param[in] bool doGroups: 是否将拾取数据所在组对象中的其他实体加入到实体集中
            @param[in] bool allowLocked: 是否允许组对象中被锁定的其他实体加入到实体集中
            @return 加入到实体集中的实体指针
            */
            BIMBASEAPI_EXPORT BPEntityP         insertPickData(BPPickDataCP pickData, bool doGroups, bool allowLocked);

            // ____<pkpm_inner_begin>____
            /**
            @brief 在指定视口中显示实体集中实体
            @param[in] BPDrawMode drawMode: 显示模式
            @param[in] BPDrawPurpose drawPurpose: 显示用途
            @param[in] BPEntitySelectSetToolP redrawOp: 显示绘制操作接口
            @param[in] void * clip: 裁剪区域（一般设置为NULL）
            @param[in] void* abort: 中断显示控制（一般设置为NULL）
            @note BPEntitySelectSetTool为BPRedrawOperation的派生类，可在Tool中实现BPRedrawOperation相关接口
            @see BPDrawMode, @see BPDrawPurpose, @see BPRedrawOperation
            */
            BIMBASEAPI_EXPORT void                draw(BPViewportP viewport, BPDrawMode drawMode, BPDrawPurpose drawPurpose, BPEntitySelectSetToolP redrawOp, void* clip, void* abort);
            /**
            @brief 实体检索
            @details 在实体集中查找指定实体的索引
            @warning will be deprecated
            */
            BIMBASEAPI_EXPORT BPEntityPtr        find(BPEntityCR entity, size_t startIndex = 0, size_t endIndex = -1);
            // ____<pkpm_inner_end>____

        private:

            void* m_imp;

            bool m_bImpRef;

        };
    }
}
#endif // BP_BPData_BPEntity_H
