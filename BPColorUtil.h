/**
@brief BPColorUtil 颜色类
@details 可用于索引色、rgb等不同格式的颜色转换
@file    BPColorUtil.h
@author  北京构力科技有限公司
@date    2021-08-12
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/
#ifndef P3D_P3DBase_BPColorUtil_H
#define P3D_P3DBase_BPColorUtil_H

namespace BIMBase {
    namespace Core
    {
        /**
        @brief  颜色工具类
        @details  可用于索引色、rgb等不同格式的颜色转换
        @date 创建日期:2021-08-12
        */
        class BPColorUtil : public ::BIMBase::BPNonCopyableClass
        {
        public:
            /**
            @brief 获取索引色
            @details 根据BPColorDef获取索引色，如果没有，createIfNotPresent为true则创建自定义索引色，为false返回最接近的索引色
            @param[in] colorDef:颜色定义
            @param[in] project:工程文件
            @param[in] createIfNotPresent:如果没有是否创建
            @return 索引色
            */
            static BIMBASEAPI_EXPORT UInt32                getEntityColor(BPColorDef const& colorDef, Core::BPProjectR project, bool createIfNotPresent);
            /**
            @brief 获取索引色
            @details 根据BPColorDef获取索引色，如果没有返回最接近的索引色
            @param[in] colorDef:颜色
            @param[in] project:工程文件
            @return 索引色
            */
            static BIMBASEAPI_EXPORT UInt32                findEntityColor(BPColorDef const& colorDef, BPProjectR project);
            /**
            @brief 根据索引色获取颜色
            @param[out] colorDef:颜色定义，如果为null则不返回
            @param[out] colorIndex:索引色，如果为null则不返回
            @param[out] isTrueColor:是否为自定义索引色，如果为null则不返回
            @param[in] entityColor:颜色定义
            @param[in] 工程文件
            @return 获取标识
            - ::p3d::P3DStatus::SUCCESS 成功
            - ::p3d::P3DStatus::ERROR 失败
            */
            static BIMBASEAPI_EXPORT p3d::P3DStatus        extractEntityColor(BPColorDef* colorDef, UInt32* colorIndex, bool* isTrueColor, UInt32 entityColor, BPProjectR project);
            /**
            @brief 创建索引色
            @param[in] colorDef:颜色定义
            @param[in] project:工程文件
            @return 索引色
            */
            static BIMBASEAPI_EXPORT UInt32                createEntityColor(BPColorDef const& colorDef, Core::BPProjectR project);
            /**
            @brief 根据原生索引色获取颜色定义
            @details 获取原生索引色，如果没有则返回0号索引色
            @param[in] index:索引色 project:工程文件
            @return 颜色
            @warning 此函数仅用于获取原生索引色，用户自定义的非原生索引色无法获取
            */
            static BIMBASEAPI_EXPORT BPColorDef const&     getColor(int colorIndex, BPProjectR project);
            // ____<pkpm_inner_begin>____
            /**
            @brief 获取索引色
            @details 根据BPRgbaColor获取索引色，如果没有，createIfNotPresent为true则创建，为false返回最接近的索引色
            @param[in] colorDef:rgb project:工程文件 createIfNotPresent:如果没有是否创建
            @return 索引色
            */
            static BIMBASEAPI_EXPORT UInt32                getEntityColor(BPRgbaColor const& colorDef, BPProjectR project, bool createIfNotPresent);
            /**
            @brief 是否为用户添加的非原生索引色
            @param[in] colorIndex:索引色
            @return bool
            */
            static BIMBASEAPI_EXPORT bool                   isTrueColorIndex(UInt32 colorIndex);
            // ____<pkpm_inner_end>____

        private:
            BPColorUtil();
            ~BPColorUtil();
        };
    }
}

#endif // P3D_P3DBase_BPColorUtil_H