/**
@brief 用户领域数据扩展基类及管理
@details BIMBase平台所有的用户领域数据类都需要进行注册,以支持从BPData持久对象转换到BPObject内存对象的反序列化操作.
@file    BPObjectExtensionManager.h
@author  北京构力科技有限公司
@date    2021-08-02
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/
#pragma once

BPDATACORE_TYPEDEFS(IBPObjectExtension)
BPDATACORE_TYPEDEFS(BPObjectExtensionManager)


namespace BIMBase
{
    namespace Data
    {
        /**
        @brief  用户领域数据类扩展基类
        @details  用于支持从BPData持久对象转换到BPObject内存对象的反序列化操作,或者用于创建一个空的用户领域数据实例.每一个用户领域数据类必须实现一个基于此类的派生类,并且实现反序列化虚接口.
        @date 创建日期:2021-08-02
        */
        class IBPObjectExtension
        {
        public:

            /**
            @brief 创建一个空的用户领域数据实例
            @return 用户领域数据实例指针
            */
            BPDATACORE_EXPORT IBPObjectPtr   getBPObject();

            /**
            @brief 反序列化一个BPData到用户领域数据实例.
            @return 用户领域数据实例指针
            @note
            @warning
            */
            BPDATACORE_EXPORT IBPObjectPtr   getBPObject(::BIMBase::Core::BPDataCR data);

        protected:

            /**
            @brief 用户领域数据类扩展必须实现此接口返回一个空的用户领域数据实例.
            @return 用户领域数据实例指针
            */
            virtual IBPObjectPtr            _getBPObject() = 0;

            /**
            @brief 用户领域数据类扩展必须实现此接口返回一个用户领域数据实例,这个实例的属性数据根据BPData数据反序列化而来.
            @return 用户领域数据实例指针
            */
            virtual IBPObjectPtr            _getBPObject(::BIMBase::Core::BPDataCR data) = 0;

        };//IBPObjectExtension



        // ____<pkpm_inner_begin>____
        class BPGraphicElement;
        using BPEntityDrawCallBack = std::function<int(BIMBase::Core::BPEntityR, BIMBase::Core::BPViewContextR, BPGraphicElement*)>;
        using BPEntityDrawTransformCallBack = std::function<int(p3d::GeTransformR, BIMBase::Core::BPEntityCR, BPGraphicElement*)>;
        // ____<pkpm_inner_end>____


        /**
        @brief  用户领域数据类扩展管理
        @details  用于用户领域数据类扩展的注册及数据实例的创建和反序列化等操作.
        @date 创建日期:2021-08-02
        */
        class BPObjectExtensionManager:public BPNonCopyableClass, public BIMBase::BPRegisterBase
        {
        public:
            /**
            @brief 单例访问
            @return 单例实例引用
            */
            BPDATACORE_EXPORT static BPObjectExtensionManagerR getInstance();

            /**
            @brief 清除所有已注册的IBPObjectExtension
            @return 无
            */
            BPDATACORE_EXPORT void destroy();

            /**
            @brief 根据schema注册一个IBPObjectExtension实例
            @return 无
            */
            BPDATACORE_EXPORT void registerBPObjectExtension(p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className, IBPObjectExtensionP objectExtension, BPRegisterModule hm = BIMBase::getRegisterHModule());

            /**
            @brief 根据classId注册一个IBPObjectExtension实例
            @return 无
            */
            BPDATACORE_EXPORT void registerBPObjectExtension(::BIMBase::Core::BPProjectCR project, BIMBase::PClassId classId, IBPObjectExtensionP objectExtension, BPRegisterModule hm = BIMBase::getRegisterHModule());

            /**
            @brief 清除由schema指定的已注册的IBPObjectExtension实例
            @return 无
            */
            BPDATACORE_EXPORT void unRegisterBPObjectExtension(p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className, IBPObjectExtensionP& objectExtension);

            /**
            @brief 清除由classId指定的已注册的IBPObjectExtension实例
            @return 无
            */
            BPDATACORE_EXPORT void unRegisterBPObjectExtension(::BIMBase::Core::BPProjectCR project, BIMBase::PClassId classId, IBPObjectExtensionP& pObjectExtension);

            /**
            @brief 根据classId查询已注册的IBPObjectExtension实例
            @return IBPObjectExtension实例指针
            */
            BPDATACORE_EXPORT IBPObjectExtensionP getBPObjectExtension(::BIMBase::Core::BPProjectCR project, BIMBase::PClassIdCR classId);

            /**
            @brief 根据schema查询已注册的IBPObjectExtension实例
            @return IBPObjectExtension实例指针
            */
            BPDATACORE_EXPORT IBPObjectExtensionP getBPObjectExtension(p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className);

            /**
            @brief 根据classId创建出一个空的用户领域数据实例.
            @return 用户领域数据基类指针
            */
            BPDATACORE_EXPORT IBPObjectPtr getBPObject(::BIMBase::Core::BPProjectCR project, BIMBase::PClassIdCR classId);

            /**
            @brief 根据schema创建出一个空的用户领域数据实例.
            @return 用户领域数据基类指针
            */
            BPDATACORE_EXPORT IBPObjectPtr getBPObject(::BIMBase::Core::BPProjectCR project, p3d::Utf8StringCR schemaName, p3d::Utf8StringCR className);

            /**
            @brief 根据BPData实例反序列化出相应的用户领域数据实例.
            @return 用户领域数据基类指针
            */
            BPDATACORE_EXPORT IBPObjectPtr getBPObject(::BIMBase::Core::BPDataCR data);

            /**
            @brief 根据BPDataKey反序列化出相应的用户领域数据实例.
            @return 用户领域数据基类指针
            */
            BPDATACORE_EXPORT IBPObjectPtr getBPObject(::BIMBase::Core::BPProjectCR project, ::BIMBase::BPDataKeyCR dataKey);

            /**
            @brief 根据指定的entity反序列化出相应的用户领域数据实例.
            @details 这个entity需要是一个已经持久化的实例,并且与特定的BPData实例存在绑定关系.
            @return 用户领域数据类指针
            */
            BPDATACORE_EXPORT IBPObjectPtr getBPObject(::BIMBase::Core::BPEntityCR entity);

            /**
            @brief 根据指定的entityId反序列化出相应的用户领域数据实例.
            @details 这个entity与特定的BPData实例存在绑定关系.
            @return 用户领域数据类指针
            */
            BPDATACORE_EXPORT IBPObjectPtr getBPObject(::BIMBase::BPEntityId const& entityId, ::BIMBase::Core::BPModelBaseR model);


            // ____<pkpm_inner_begin>____
            static BPObjectExtensionManagerR Get() { return getInstance(); };
            // 为了兼容专业原有的逻辑
            BPDATACORE_EXPORT void setCallBackFunc(BPEntityDrawCallBack cb1, BPEntityDrawTransformCallBack cb2);
            // ____<pkpm_inner_end>____

        protected:

            BPDATACORE_EXPORT BPObjectExtensionManager();
            BPDATACORE_EXPORT BPObjectExtensionManager(BPObjectExtensionManagerCR other);
            BPDATACORE_EXPORT BPObjectExtensionManagerR operator= (BPObjectExtensionManagerCR right);

        protected:
            static BPObjectExtensionManagerP    s_manager;

        };//BPObjectExtensionManager
    };
};

