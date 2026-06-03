/**
@brief 图形实体的模型空间相关类定义
@file    BPModel.h
@author  北京构力科技有限公司
@date    2021-07-28
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/

#ifndef BP_BPDisplay_BPModel_H
#define BP_BPDisplay_BPModel_H

#include <vector>

namespace BIMBase {
    namespace Core
    {
        typedef ::p3d::pvector<BPEntityPtr>          BPEntityVector;
        typedef BPEntityVector* BPEntityVectorP;
        typedef BPEntityVector& BPEntityVectorR;
        typedef BPEntityVector const* BPEntityVectorCP;
        typedef BPEntityVector const& BPEntityVectorCR;


        /**
        @brief  模型空间基类
        @details 用于图形数据的管理
        @date 创建日期:2021-07-28
        */
        class BPModelBase : public ::BIMBase::BPRefCountedBase
        {
        public:

            /**
            @brief 析构函数
            */
            BIMBASEAPI_EXPORT virtual ~BPModelBase();

            /**
            @brief 获取所属的工程文件
            */
            BIMBASEAPI_EXPORT BPProjectP                    getBPProject(void);

            /**
            @brief 获取唯一ID
            @note 在所属的工程文件内唯一
            */
            BIMBASEAPI_EXPORT::BIMBase::PModelId            getModelId(void) const;

            /**
            @brief 获取模型空间名称
            */
            BIMBASEAPI_EXPORT p3d::Utf8String               getModelName(void) const;

            // ____<pkpm_inner_begin>____
            /**
            @brief 设置模型空间名称
            @param[in] modelName: 图层名称
            @deprecated 无替代函数
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus                setModelName(p3d::Utf8StringCR modelName);
            BIMBASEAPI_EXPORT p3d::P3DStatus                setModelType(p3d::platform::P3DModelType modelType);
            // ____<pkpm_inner_end>____

            /**
            @brief 获取模型空间类型
            @detail 目前仅支持enPhysical类型
            */
            BIMBASEAPI_EXPORT p3d::platform::P3DModelType   getModelType(void) const;


            /**
            @brief 创建一个空的几何图形容器
            @detail
            @param[in] layerId: 图层ID，默认为64
            */
            BIMBASEAPI_EXPORT BPGraphicsPtr                 createPhysicalGraphics(PLayerId layerId = DEFAULT_LAYER_ID);

            /**
            @brief 获取当前模型空间所有的图形实体
            @return 图形实体集合
            */
            BIMBASEAPI_EXPORT BPEntityVectorP               getGraphicEntitys(void);

            ///**
            //@brief 获取当前模型空间所有的测量实体
            //@return 测量实体集合
            //*/
            //BIMBASEAPI_EXPORT BPEntityVector               getMeasureEntitys(void) const;

            /**
            @brief 查询当前模型空间指定范围的图形实体
            @detail 此接口只查询当前模型空间的实体,不查询链接模型.
            @param[out] resEntities: 查询到的图形实体集合
            @param[in]  queryRange: 查询范围
            @param[in]  bOnlyVisible: 是否只查询可见的图形实体
            @return 是否查询成功
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus                getGraphicEntitys(BPEntityVector& resEntities, p3d::GeRange3dCR queryRange, bool bOnlyVisible = false);

            /**
            @brief 获取当前模型空间的包围盒
            @param[out] range3d: 空间范围
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus                getRange(p3d::GeRange3d& range3d) const;

            /**
            @brief 根据图形实体唯一ID查询指定的图形实体
            @param[in] entityId: 图形实体ID
            */
            BIMBASEAPI_EXPORT BPEntityPtr                   findEntityByID(BPEntityId id);

            // ____<pkpm_inner_begin>____
            BIMBASEAPI_EXPORT void                          SetDisplaySetForAll(bool allIn);
            BIMBASEAPI_EXPORT void                          SetUndisplayedFlagFor(p3d::pset<::BIMBase::BPEntityId> ids, bool yesNo);
            BIMBASEAPI_EXPORT void                          SetUndisplayedFlagForAll(bool yesNo);

            BIMBASEAPI_EXPORT BPModelP                      toBPModel() const;
            BIMBASEAPI_EXPORT BPModelLinkP                  toBPModelLinkP(void) const;

            BIMBASEAPI_EXPORT int                           getModelLinkCount() const;
            BIMBASEAPI_EXPORT BPModelLinkArrayCR            getAllModelLinks();

            /**
            @brief 删除指定的模型空间链接
            @details 如果要删除的modelLink有对应的BPModelElementLink数据,则会删除失败返回ERROR.应该通过BPModelElementLink的deleteFromProject接口删除.
            @param[in]  modelLink:  指定的模型空间链接
            @return 删除是否成功
            */
            BIMBASEAPI_EXPORT::p3d::StatusInt               deleteModelLink(BPModelLinkP modelLink);
            BIMBASEAPI_EXPORT BPModelLinkPtr                getModelLinkByIndex(int nIndex);
            BIMBASEAPI_EXPORT::p3d::P3DStatus               setClipEntityId(BPEntityId entiId);
            
            /**
            @brief 根据模型空间链接唯一ID获取相应的模型空间
            @param[in] modelLinkId: 模型空间链接唯一ID
            */
            BIMBASEAPI_EXPORT BPModelLinkPtr                getModelLinkById(Int32 modelLinkId);

			/**
			@brief 获得当前模型空间捕捉高亮是否开启的状态
			*/
			BIMBASEAPI_EXPORT::p3d::P3DStatus  isSnapHilite(bool& isSnapHilite) const;

			/**
		    @brief 设置当前模型空间的捕捉高亮是否开启
		    @param[in] isSnapHilite: 是否开启
		    */
			BIMBASEAPI_EXPORT::p3d::P3DStatus setSnapHilite(bool isSnapHilite);

            // ____<pkpm_inner_end>____


        private:
            BPModelBase();
            BPModelBase(BPModelBaseCR right);
            BPModelBaseR operator=(BPModelBaseR modelBase) = delete;


        };

        /**
        @brief  模型空间类
        @details  用于图形实体的管理
        @date 创建日期:2021-07-28
        */
        class BPModel : public BPModelBase
        {
        public:

            /**
            @brief 析构函数
            */
            BIMBASEAPI_EXPORT virtual ~BPModel();

            /**
            @brief 构造函数
            @param[in] project: 工程文件
            @param[in] modelId: 模型空间唯一ID
            */
            BIMBASEAPI_EXPORT BPModel(BPProjectCP project, ::BIMBase::PModelId modelId);

            // ____<pkpm_inner_begin>____
            /**
            @brief 是否加载指定部分的数据到内存
            */
            BIMBASEAPI_EXPORT bool                      isFilled(p3d::platform::P3DModelSections sections) const;

            /**
            @brief 获取指定模型空间部分的图形实体数量
            @return 返回-1获取失败,否则返回实体数量
            @deprecated 用getGraphicEntitys返回的列表进行计数
            */
            BIMBASEAPI_EXPORT int64_t                   getEntityCount(p3d::platform::P3DModelSections sections) const;

            /**
            @brief 清除当前模型空间的所有图形实体数据
            @param[in] evenIfDirty:
            @param[in] andFree:
            @deprecated
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus            emptyContent(bool evenIfDirty = false, bool andFree = false);

            /**
            @brief 设置背景色
            @note 目前是通过viewTable设置,暂不对外
            */
            BIMBASEAPI_EXPORT p3d::P3DStatus            setBackGroundColor(BPColorDef bkClor);
            BIMBASEAPI_EXPORT p3d::P3DStatus            getBackGroundColor(BPColorDef& bkClor) const;

            /**
            @brief 获取模型关联的图层组合
            @return 如果有图层组合关联到此Model，则返回此图层组合,否则返回空
            */
            BIMBASEAPI_EXPORT BPLayerGroupPtr     getRelatedLayerGroup() const;
            /**
            @brief 根据名称设置模型关联的图层组合
            @note 可以设置为空,表示恢复成文件级的图层
            @return 如果layerGroupName不存在或当前类型不是Model，则返回false，其他情况返回true
            */
            BIMBASEAPI_EXPORT bool setRelatedLayerGroupByName(p3d::WCharCP layerGroupName);
            /**
            @brief 设置模型关联的图层组合
            @note 可以设置为空,表示恢复成文件级的图层
            */
            BIMBASEAPI_EXPORT bool setRelatedLayerGroup(BPLayerGroupP layerGroup);

            /**
            @deprecated 用IBPProjectManager::getActiveModel代替
            */
            BIMBASEAPI_EXPORT static BPModelP           getActiveModel();

            /** 创建链接Model
            *
            * 返回的Model集合里包含已经加载到内存的和未加载到内存的
            * @return    BPModel集合
            * @note
            */
            BIMBASEAPI_EXPORT BPModelLinkPtr            createModelLink(BPProjectP project, p3d::Utf8StringCR modelName);

            BIMBASEAPI_EXPORT p3d::P3DStatus            setModelId(::BIMBase::PModelId);
            /**
            @brief 获取model全局的线型比例因子
            */
            BIMBASEAPI_EXPORT double getLineStyleScale() const;
            /**
            @brief 设置model全局的线型比例因子 调用视口刷新后生效
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus setLineStyleScale(double lineStyleScale);

            // ____<pkpm_inner_end>____

        private:
            BPModel();
            BPModel(BPModelCR model) = delete;
            BPModelR operator=(BPModelR model) = delete;

        private:
            ::BIMBase::PModelId            m_modelId;
            BPEntityArrayPtr    m_graphicEntityArray;
        };


        /**
        @brief  模型空间容器类
        @date 创建日期:2021-07-28
        */
        class BPModelArray : public BPRefCountedBase
        {
        public:
            typedef std::vector <BPModelBasePtr>::iterator iterator;
            typedef std::vector <BPModelBasePtr>::const_iterator const_iterator;

            /**
            @brief 构造函数
            */
            BIMBASEAPI_EXPORT BPModelArray();

            /**
            @brief 析构函数
            */
            BIMBASEAPI_EXPORT virtual ~BPModelArray();

            /**
            @brief 迭代器起始位置
            */
            BIMBASEAPI_EXPORT const_iterator    begin() const;

            /**
            @brief 迭代器结束位置
            */
            BIMBASEAPI_EXPORT const_iterator    end() const;

            /**
            @brief 元素数目
            */
            BIMBASEAPI_EXPORT size_t            size() const;

            /**
            @brief 获取指定索引位置的元素
            @param[in] nIndex: 索引值
            */
            BIMBASEAPI_EXPORT BPModelBaseP      at(int nIndex);

            /**
            @brief 存入指定的模型空间
            @param[in] modelBase: 模型空间指针
            */
            BIMBASEAPI_EXPORT void              insert(BPModelBaseP modelBase);

            /**
            @brief 清空容器内容
            */
            BIMBASEAPI_EXPORT void              clear();

            /**
            @brief 在当前容器中根据指定的modelId查询相应的模型空间
            @param[in] modelId: 模型空间唯一ID
            */
            BIMBASEAPI_EXPORT BPModelBaseP      findModelById(::BIMBase::PModelId modelId);

        private:
            std::vector<BPModelBasePtr>  m_modelList;
        };
    }
}

#endif // BP_BPDisplay_BPModel_H