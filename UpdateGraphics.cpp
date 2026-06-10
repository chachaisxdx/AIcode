// 功能: 更新图形对象，复制并追加新曲线后替换原有实体图形
// 关键词: 更新图形, 复制图形, 修改实体, 添加曲线, updateEntityWithGraphics
// 依赖类: BPGraphics, BPEntity, GeCurveArray, BPGraphicsUtils

#include "pch.h"

/**
 * @brief 更新图形对象
 * @note  该函数创建一个基础图形（矩形边界），复制该图形，然后添加额外的曲线，
 *        最后更新实体中的图形。
 *        实现步骤：
 *        1. 获取当前项目及活动模型，创建两个 BPGraphics 对象。
 *        2. 创建第一个矩形边界（XOY 平面矩形）并添加到 ptrGraphic1。
 *        3. 保存 ptrGraphic1 为实体，获取实体 ID。
 *        4. 复制 ptrGraphic1 到 ptrGraphic2。
 *        5. 在 ptrGraphic2 中添加第二个矩形边界（XOZ 平面矩形）。
 *        6. 调用 updateEntityWithGraphics 更新原实体的图形为 ptrGraphic2。
 */
void UpdateGraphics()
{
    // 获取当前主工程对象
    BPProjectP pProject = BPApplication::getInstance().getProjectManager()->getMainProject();
    if (pProject == nullptr)
        return;

    // 获取当前活动模型，作为图形载体
    BPModelBaseP pModel = pProject->getActiveModel();

    // 创建两个物理图形对象
    // ptrGraphic1：原始图形
    // ptrGraphic2：修改后的新图形
    BPGraphicsPtr ptrGraphic1 = pModel->createPhysicalGraphics();
    BPGraphicsPtr ptrGraphic2 = pModel->createPhysicalGraphics();

    // ========== 构建第一个矩形曲线（水平矩形） ==========
    pvector<GePoint3d> vctPoints;
    vctPoints.push_back(GePoint3d::create(0, 0, 0));
    vctPoints.push_back(GePoint3d::create(3000, 0, 0));
    vctPoints.push_back(GePoint3d::create(3000, 3000, 0));
    vctPoints.push_back(GePoint3d::create(0, 3000, 0));

    // 根据点集创建闭合外边界曲线
    GeCurveArrayPtr ptrCurveArray = GeCurveArray::createLinestringArray(vctPoints, GeCurveArray::BOUNDARY_TYPE_Outer);
    // 将曲线添加到第一个图形
    ptrGraphic1->addGeCurveArray(*ptrCurveArray);

    // ========== 构建第二个矩形曲线（竖直矩形） ==========
    pvector<GePoint3d> vctPoints2;
    vctPoints2.push_back(GePoint3d::create(2000, 0, -1000));
    vctPoints2.push_back(GePoint3d::create(2000, 4000, -1000));
    vctPoints2.push_back(GePoint3d::create(2000, 4000, 3000));
    vctPoints2.push_back(GePoint3d::create(2000, 0, 3000));

    // 创建竖直矩形的曲线数组
    GeCurveArrayPtr ptrCurveArray2 = GeCurveArray::createLinestringArray(vctPoints2, GeCurveArray::BOUNDARY_TYPE_Outer);

    // 保存原始图形到模型，获取实体ID
    BPEntityId en = ptrGraphic1->save();

    // 根据实体ID构造实体对象
    BPEntity entity(en, *pProject);

    // 将图形1复制到图形2（完整拷贝原有图形内容）
    BPGraphicsUtils::copyPhysicalGraphics(*ptrGraphic2, *ptrGraphic1);

    // 向图形2中追加第二个矩形曲线（实现图形更新）
    ptrGraphic2->addGeCurveArray(*ptrCurveArray2);

    // 用更新后的图形2替换原实体的图形
    ptrGraphic2->updateEntityWithGraphics(&entity, false);
}

// 注册函数到工具管理器
AutoDoRegisterFunctionsBegin
BPToolsManager::registerFun(_T("updategraphics"), &UpdateGraphics);
AutoDoRegisterFunctionsEnd