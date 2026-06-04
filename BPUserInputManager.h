/**
@brief     命令调用管理类
@file      BPUserInputManager.h
@author    北京构力科技股份有限公司
@date      2021-02-26
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/

#pragma once

namespace BIMBase
{
    /**
    @brief     命令调用管理类
    */
    class BPUserInputManager
    {
    public:
        /**
        @brief：同步命令
        @param[in] str: 已注册的命令
        */
        static BIMBASEAPI_EXPORT void exeCommand(::p3d::Utf8CP str);

        /**
        @brief：查找命令
        @param[in] str: 待查找的命令
        */
        static BIMBASEAPI_EXPORT bool ifHasCommand(::p3d::Utf8CP str);

        /**
        @brief：向命令栏输出提示信息
        @param[in] prompt: 提示信息内容
        */
        static BIMBASEAPI_EXPORT bool outPutPromptToCommandBar(::p3d::Utf8StringCR prompt);

        // ____<pkpm_inner_begin>____
        static BIMBASEAPI_EXPORT void exeCommand(::p3d::WCharCP str);

        static BIMBASEAPI_EXPORT bool ifHasCommand(::p3d::WCharCP str);

        static bool isAVoidedCommandStr(wchar_t const* str);
        // ____<pkpm_inner_end>____
    };

};

