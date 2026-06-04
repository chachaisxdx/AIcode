/**
@brief   按钮事件基类
@details 该类包含了按钮触发后所携带的交互信息，包括交互时  视口信息，坐标信息等，  待完善
@file    BPBaseButtonEvent.h
@author  北京构力科技有限公司
@date    2021-08-07
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/
#pragma once


namespace BIMBase {
    namespace Core
    {
        /**
        @brief  类简要描述   待完善
        @details  类详细描述
        @date 创建日期:2021-08-07
        */
        class BPBaseButtonEvent : public BPRefCountedBase
        {
        public:
            enum CoordSource
            {
                FROM_User = 0,
                FROM_Precision = 1,
                FROM_TentativePoint = 2,
                FROM_ElemSnap = 3,
            };

            enum Qualifier
            {
                enQUALIFIER_None = 0,
                enQUALIFIER_Shift = 0x0004,
                enQUALIFIER_Control = 0x0008,
                enQUALIFIER_Menu = 0x0010,
            };

            BIMBASEAPI_EXPORT BPBaseButtonEvent();
            BIMBASEAPI_EXPORT BPBaseButtonEvent(p3d::GePoint3dCR point, p3d::GePoint3dCR rawPoint, p3d::GePoint3dCR viewPt, Core::BPViewportR vp, CoordSource from, unsigned int keyModifiers, int source = 400);
            BIMBASEAPI_EXPORT ~BPBaseButtonEvent();
            BIMBASEAPI_EXPORT void initEvent(p3d::GePoint3dCR point, p3d::GePoint3dCR rawPoint, p3d::GePoint3dCR viewPt, Core::BPViewportP vp, CoordSource from, unsigned int keyModifiers, int source = 400);
            BIMBASEAPI_EXPORT void setKeyModifiers(unsigned int wKeys);
            BIMBASEAPI_EXPORT void setCoordSource(CoordSource from);
            BIMBASEAPI_EXPORT bool isValid() const;
            BIMBASEAPI_EXPORT void invalidate();
            BIMBASEAPI_EXPORT bool isDoubleClick() const;
            BIMBASEAPI_EXPORT void setPoint(p3d::GePoint3dCP pt);

            BIMBASEAPI_EXPORT p3d::GePoint3dCP  getPoint() const;
            BIMBASEAPI_EXPORT p3d::GePoint3dCP  getRawPoint() const;
            BIMBASEAPI_EXPORT p3d::GePoint3dCP  getViewPoint() const;
            BIMBASEAPI_EXPORT void              setViewport(Core::BPViewportP viewport);
            BIMBASEAPI_EXPORT Core::BPViewportP getViewport() const;
            BIMBASEAPI_EXPORT int               getViewNum() const;
            BIMBASEAPI_EXPORT CoordSource       getCoordSource() const;
            BIMBASEAPI_EXPORT int               getButtonSource() const;
            BIMBASEAPI_EXPORT bool              isControlKey() const;
            BIMBASEAPI_EXPORT bool              isShiftKey() const;
            BIMBASEAPI_EXPORT bool              isAltKey() const;
            BIMBASEAPI_EXPORT unsigned int      getKeyModifiers() const;

        private:
            BIMBASEAPI_EXPORT  BPBaseButtonEvent(bool);

            void* m_P3DBaseButtonEventImpP;

            bool m_bImpRef;
            bool m_bIsDoubleClick;

        };
    };
};

