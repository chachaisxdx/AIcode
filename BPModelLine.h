/**
@brief 基本图素直线
@file    BPModelLine.h
@author  北京构力科技有限公司
@date    2021-10-15
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/
#pragma once

BPDATACORE_TYPEDEFS(BPModelLine);
BPDATACORE_TYPEPTRDEFS(BPModelLine);
namespace BIMBase {
    namespace Data
    {
        class BPModelLine :public BPModelCurve
        {
            CVAR_DEF_BEGIN(BPModelLine)
                CVAR_DEF(double, Length)
                CVAR_DEF_END
            BPPRIMARYELEM_CREATE(BPModelLine)
        public:
            virtual ::p3d::Utf8String _getClassName() const override { return "PBLine3d"; }
            virtual ::p3d::Utf8String _getSchemaName() const  override { return "PBM_Graphics"; }
            BPPRIMARYELEM_EXPORT BPModelLine();
            BPPRIMARYELEM_EXPORT BPModelLine(::p3d::GePoint3dCR startPoint, ::p3d::GePoint3dCR endPoint);
            BPPRIMARYELEM_EXPORT ~BPModelLine();
            BPPRIMARYELEM_EXPORT static BPModelLineP Create(::p3d::GePoint3dCR startPoint, ::p3d::GePoint3dCR endPoint, ::p3d::GeVec3dCR normal);
            BPPRIMARYELEM_EXPORT virtual ::p3d::GePoint3d _getEndPoint(int idx)const;
            //
            BPPRIMARYELEM_EXPORT BPModelLine Set(::p3d::GePoint3dCR startPoint, ::p3d::GePoint3dCR endPoint);
            //
            BPPRIMARYELEM_EXPORT::p3d::GePoint3d GetStartPoint()const;
            BPPRIMARYELEM_EXPORT void SetStartPoint(::p3d::GePoint3dCR pt);
            //
            BPPRIMARYELEM_EXPORT::p3d::GePoint3d GetMidPoint()const;
            //
            BPPRIMARYELEM_EXPORT::p3d::GePoint3d GetEndPoint()const;
            BPPRIMARYELEM_EXPORT void SetEndPoint(::p3d::GePoint3dCR pt);
            //
            BPPRIMARYELEM_EXPORT::p3d::GeVec3d GetDirection()const;

        protected:
            BPPRIMARYELEM_EXPORT bool _createdByInternalEntity() const override;
            BPPRIMARYELEM_EXPORT virtual ::p3d::P3DStatus _generateEntityInternal(OUT BIMBase::Core::BPEntityR newEntity, ::BIMBase::Core::BPModelR model, ::BIMBase::Core::BPProjectR project) override;
        };

        BPPRIMARYELEM_EXTENSION(BPModelLine)
    };
};