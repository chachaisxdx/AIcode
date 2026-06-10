// 功能: 创建模型填充区域（Hatch），加载填充样式并设置填充与背景色
// 关键词: 模型填充, Hatch, 填充样式, 闭合区域填充, 自定义填充色, 矩形填充
// 依赖类: BPHatch, BPHatchPatternManager, GeCurveArray, BPModelBase

#include "pch.h"

/**
 * @brief 创建模型填充（Model Hatch）
 * @note  该函数加载所有填充样式，然后创建一个矩形填充区域，应用第一种填充样式，
 *        并设置自定义背景颜色为红色，最后将填充对象添加到当前活动模型中。
 *        实现步骤：
 *        1. 加载所有填充样式。
 *        2. 获取第一个填充样式的名称。
 *        3. 构建矩形填充边界（四个角点）。
 *        4. 创建填充区域（GeCurveArray）。
 *        5. 创建 BPHatch 对象，使用第一个填充样式。
 *        6. 设置自定义背景色为红色。
 *        7. 将填充对象添加到当前模型中。
 */
void CreateModelHatch()
{
    // 加载系统所有填充样式（预加载，确保样式可用）
    BIMBase::Data::BPHatchPatternManager::getInstance().loadPatterns();
    // 获取所有填充样式的名称与样式数据
    pmap<PString, pvector<BPPat>> mapPat = BIMBase::Data::BPHatchPatternManager::getInstance().getPatterns();
    // 如果没有任何填充样式，直接返回
    if (mapPat.size() == 0)
        return;

    // 定义矩形区域的四个角点，用于创建闭合填充边界
    pvector<GePoint3d> vctPoints;
    vctPoints.push_back(GePoint3d::create(0, 0, 0));
    vctPoints.push_back(GePoint3d::create(3000, 0, 0));
    vctPoints.push_back(GePoint3d::create(3000, 3000, 0));
    vctPoints.push_back(GePoint3d::create(0, 3000, 0));

    // 根据点集创建外边界曲线（矩形轮廓）
    GeCurveArrayPtr ptrCurveArray = GeCurveArray::createLinestringArray(vctPoints, GeCurveArray::BOUNDARY_TYPE_Outer);
    // 创建奇偶规则填充区域（标准填充区域类型）
    GeCurveArrayPtr ptrCurveRegion = GeCurveArray::create(GeCurveArray::BOUNDARY_TYPE_ParityRegion);
    // 将外边界添加到填充区域中
    ptrCurveRegion->add(ptrCurveArray);

    // 接收创建填充时的错误信息
    PString sError;
    // 使用第一个填充样式创建填充对象
    BPHatchPtr ptrHatch = BPHatch::create(mapPat.begin()->first, ptrCurveRegion.get(), sError);

    // 定义自定义填充背景色（暗红色）
    COLORREF colorDef = RGB(200, 0, 0);
    // 给填充对象设置自定义背景色
    ptrHatch->setCustomSheetColor(colorDef);

    // 如果填充对象创建失败，直接返回
    if (ptrHatch.isNull())
        return;

    // ========== 获取当前工程与活动模型 ==========
    BIMBase::Core::BPProjectP pProject = BIMBase::Core::BPApplication::getInstance().getProjectManager()->getMainProject();
    if (pProject == NULL)
        return;

    // 获取当前活动模型
    BPModelBaseP pModel = pProject->getActiveModel();

    // 将填充对象添加到工程与模型中
    ::p3d::P3DStatus status = ptrHatch->addToProject(*pProject, pModel->getModelId());
}

// ========== 注册函数到工具管理器 ==========
AutoDoRegisterFunctionsBegin
// 注册创建模型填充函数，外部可通过字符串调用
BPToolsManager::registerFun(_T("createmodelhatch"), &CreateModelHatch);
AutoDoRegisterFunctionsEnd