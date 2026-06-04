/**
@brief 注册工具基类
@file    BPTool.h
@author  北京构力科技有限公司
@date    2021-08-16
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/
#pragma once


namespace BIMBase {
    namespace Core
    {

        class BPTool : public BPRefCountedBase, ::BIMBase::BPNonCopyableClass
        {
        public:

            /**
            @brief 装载工具
            */
            BIMBASEAPI_EXPORT virtual ::p3d::StatusInt  installTool() = 0;

            /**
            @brief 退出工具
            */
            BIMBASEAPI_EXPORT virtual void              callExitTool() = 0;

            BIMBASEAPI_EXPORT virtual ::p3d::PStringCR  getToolId() const = 0;

            /**
            @brief 获取当前活动的布置或选择工具
            @Note  可能是布置工具或选择工具其一
            */
            BIMBASEAPI_EXPORT static BPTool*            getActivePrimitiveTool();

            /**
            @brief 判断此时是否激活了默认选择工具
            @return bool
            - true  当前活动的工具是默认选择工具
            - false 当前活动的工具不是默认选择工具
            */
            BIMBASEAPI_EXPORT static bool               isDefaultSelectToolActived();

            /**
            @brief 判断此时是否激活了视图工具
            @return bool
            - true  存在视图工具
            - false 不存在视图工具
            */
            BIMBASEAPI_EXPORT static bool               isViewToolActived();

            // ____<pkpm_inner_begin>____
            /**
            @brief 开启或关闭默认选择工具预拾取
            @note  需注意调用时机, 在当前激活工具为默认选择工具时调用该接口会重启默认选择工具
            @return bool
            - true  开启拾取
            - false 关闭拾取
            */
            BIMBASEAPI_EXPORT static void               enableDefaultSelectToolLocate(bool yesNo);

            BIMBASEAPI_EXPORT static bool               isDefaultSelectToolLocateEnabled();

            BIMBASEAPI_EXPORT void                      finishTransaction();
            // ____<pkpm_inner_end>____
        };
    };
};


