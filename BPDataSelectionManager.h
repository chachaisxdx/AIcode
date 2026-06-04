/*!
* Copyright (C), 2019-2028, Beijing GLory PKPM Tech. Co., Ltd.
* @file BPDataSelectionManager.h
* @author Glory
* @date 2024/03/26
* @note 基于数据的选择集管理
*/
#pragma once

namespace BIMBase
{
    namespace Core {

        /**
        @brief  选择集事件监听基类
        @date 创建日期:2021-08-10
        */
        class    BPDataSelectionEventListener : public ::BIMBase::BPNonCopyableClass
        {
        public:
            friend class BPDataSelectionManager;
        public:
            /**
            @brief 选择集变更事件
            */
            virtual void _onSelectionChanged() = 0;
        protected:
            BIMBASEAPI_EXPORT explicit BPDataSelectionEventListener() {};
            BIMBASEAPI_EXPORT virtual ~BPDataSelectionEventListener() {};

        private:

        };

        /**
        @brief  选择集管理
        @details
        @date 创建日期:2021-07-29
        */
        class BPDataSelectionManager : public ::BIMBase::BPNonCopyableClass, public BPEventPool<BPDataSelectionEventListener>//, public BIMBase::BPRegisterBase
        {
        public:
            /**
            @brief 获取BPDataSelectionManager唯一实例
            @return BPDataSelectionManager类的实例
            */
            BIMBASEAPI_EXPORT static BPDataSelectionManager& getInstance(void);

            /**
            @brief 向选择集中添加指定的BPData
            @param[in] data：指定的BPData的指针
            @return P3DStatus
            - SUCCESS 写入成功
            - ERROR 写入失败
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus addData(Core::BPDataPtr data, BPRegisterModule hm = BIMBase::getRegisterHModule());

            /**
            @brief 向选择集中添加一组BPData
            @param[in] dataArr：指定的BPData数组
            @return P3DStatus
            - SUCCESS 写入成功
            - ERROR 写入失败
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus addDataArrary(Core::BPDataArrayPtr dataArr, BPRegisterModule hm = BIMBase::getRegisterHModule());

            /**
            @brief 删除指定的BPData
            @param[in] data：指定BPData的指针
            @return P3DStatus
            - SUCCESS 删除成功
            - ERROR 删除失败
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus removeData(Core::BPDataPtr data);

            /**
            @brief 从选择集中删除一组BPData
            @param[in] dataArr：指定的BPData数组
            @return P3DStatus
            - SUCCESS 删除成功
            - ERROR 删除失败
            */
            BIMBASEAPI_EXPORT::p3d::P3DStatus removeDataArray(Core::BPDataArrayPtr dataArr);

            /**
            @brief 清空选择集
            */
            BIMBASEAPI_EXPORT void emptyAll(void);

            /**
            @brief 根据标号拿到指定的BPData
            @param[in] nIndex：索引
            @return BPData的智能指针
            - 非空 获取成功
            - nullptr 获取失败
            */
            BIMBASEAPI_EXPORT Core::BPDataPtr     getDataByIndex(size_t nIndex);

            /**
            @brief 获取选择集的大小
            @return size_t：选择集的size
            */
            BIMBASEAPI_EXPORT size_t getCount(void) const;

            /**
            @brief 添加事件监听
            @param[in] selectionListener：选择集事件监听
            */
            BIMBASEAPI_EXPORT void addListener(BPDataSelectionEventListener* selectionListener, BPRegisterModule hm = BIMBase::getRegisterHModule());

            /**
            @brief 删除事件监听
            @param[in] selectionListener：选择集事件监听
            */
            BIMBASEAPI_EXPORT void dropListener(BPDataSelectionEventListener* selectionListener, BPRegisterModule hm = BIMBase::getRegisterHModule());


            void sendChangedEvent(BPRegisterModule hm = BIMBase::getRegisterHModule());
        protected:
            BPDataSelectionManager();
            BPDataSelectionManager(BPDataSelectionManager& other) = delete;
            void operator=(const BPDataSelectionManager& other) = delete;
            UN_REGISTER_PLUGIN_DEF()

            // ____<pkpm_inner_begin>____
        private:
            std::vector< Core::BPDataPtr> m_datas;
            //EventHandlerList<BPDataSelectionEventListener>* m_listeners;
            static BPDataSelectionManager* s_manager;

            struct  _registerRecord
            {
                std::map<ProjectEventType, bool> m_mapEventCall;
                bool m_bCallHandler;                    //是否已经分发消息，dropListener后会重新发送

                _registerRecord()
                {
                    m_bCallHandler = false;
                }
            };

            std::map<BPRegisterModule, _registerRecord> s_mapRegisterRecord;  //注册记录状态
            // ____<pkpm_inner_end>____
        };
    };

}
