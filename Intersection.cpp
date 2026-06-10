// 功能: 计算两个曲线区域的交线并显示
// 关键词: 交线计算, 曲线区域求交, 矩形平面求交, GeCurveFunction, 显示交线段
// 依赖类: BPGraphics, GeCurveArray, GeCurveFunction, BPModelBase

/**
 * @brief 计算两个曲线区域的交线并显示
 * @note  该函数创建两个图形对象：一个矩形平面（位于 Z=0 平面，范围 0~3000），
 *        一个竖立的矩形平面（位于 X=2000 平面，范围 Y:0~4000，Z:-1000~3000），
 *        计算它们的交线，并将交线作为第三个图形对象保存。
 *        实现步骤：
 *        1. 获取当前项目及活动模型，创建三个 BPGraphics 对象。
 *        2. 创建第一个矩形边界（XOY 平面矩形）并添加到 ptrGraphic1。
 *        3. 创建第二个矩形边界（XOZ 平面矩形）并添加到 ptrGraphic2。
 *        4. 调用 GeCurveFunction::calculateIntersectionSegmentsOfCurveRegions 计算交线段。
 *        5. 将交线段创建为曲线数组，添加到 ptrGraphic3。
 *        6. 保存三个图形对象到模型。
 */
void Intersection()
{
    // ========== 1. 获取当前工程与活动模型 ==========
    // 获取应用程序实例 -> 工程管理器 -> 当前主工程
    BPProjectP pProject = BPApplication::getInstance().getProjectManager()->getMainProject();
    // 工程为空则直接返回，避免空指针崩溃
    if (pProject == nullptr)
        return;

    // 获取当前工程中**激活的模型**（所有图形绘制都基于此模型）
    BPModelBaseP pModel = pProject->getActiveModel();

    // ========== 2. 创建三个图形对象 ==========
    // 图形对象1：用于存放第一个平面矩形
    BPGraphicsPtr ptrGraphic1 = pModel->createPhysicalGraphics();
    // 图形对象2：用于存放第二个平面矩形
    BPGraphicsPtr ptrGraphic2 = pModel->createPhysicalGraphics();
    // 图形对象3：用于存放**两个平面的交线**
    BPGraphicsPtr ptrGraphic3 = pModel->createPhysicalGraphics();

    // ========== 3. 创建第一个矩形（水平矩形，Z=0 平面） ==========
    // 定义点集合，用于存储矩形的四个角点
    pvector<GePoint3d> vctPoints;
    // 矩形左下角点 (0,0,0)
    vctPoints.push_back(GePoint3d::create(0, 0, 0));
    // 矩形右下角点 (3000,0,0)
    vctPoints.push_back(GePoint3d::create(3000, 0, 0));
    // 矩形右上角点 (3000,3000,0)
    vctPoints.push_back(GePoint3d::create(3000, 3000, 0));
    // 矩形左上角点 (0,3000,0)
    vctPoints.push_back(GePoint3d::create(0, 3000, 0));

    // 根据点集创建**闭合线串曲线数组**，类型为外边界
    GeCurveArrayPtr ptrCurveArray = GeCurveArray::createLinestringArray(vctPoints, GeCurveArray::BOUNDARY_TYPE_Outer);
    // 将曲线数组添加到第一个图形对象
    ptrGraphic1->addGeCurveArray(*ptrCurveArray);

    // ========== 4. 创建第二个矩形（竖直矩形，X=2000 平面） ==========
    // 定义第二个矩形的点集合
    pvector<GePoint3d> vctPoints2;
    // 矩形底部起点 (2000,0,-1000)
    vctPoints2.push_back(GePoint3d::create(2000, 0, -1000));
    // 矩形底部终点 (2000,4000,-1000)
    vctPoints2.push_back(GePoint3d::create(2000, 4000, -1000));
    // 矩形顶部终点 (2000,4000,3000)
    vctPoints2.push_back(GePoint3d::create(2000, 4000, 3000));
    // 矩形顶部起点 (2000,0,3000)
    vctPoints2.push_back(GePoint3d::create(2000, 0, 3000));

    // 根据点集创建第二个闭合曲线数组
    GeCurveArrayPtr ptrCurveArray2 = GeCurveArray::createLinestringArray(vctPoints2, GeCurveArray::BOUNDARY_TYPE_Outer);
    // 将曲线数组添加到第二个图形对象
    ptrGraphic2->addGeCurveArray(*ptrCurveArray2);

    // ========== 5. 计算两个曲线区域的交线段 ==========
    // 定义线段集合，用于接收计算出的交线
    pvector<GeSegment3d> vecSeg;
    // 调用几何计算工具，计算两个曲线区域的交线
    GeCurveFunction::calculateIntersectionSegmentsOfCurveRegions(*ptrCurveArray, *ptrCurveArray2, vecSeg);

    // ========== 6. 将交线构建为曲线数组 ==========
    // 创建空曲线数组，用于存放交线
    GeCurveArrayPtr ptrCurveArray3 = GeCurveArray::create(GeCurveArray::BOUNDARY_TYPE_None);
    // 遍历所有交线段
    for (auto seg : vecSeg)
    {
        // 将每一段交线转为几何曲线，并添加到曲线数组
        ptrCurveArray3->add(IGeCurveBase::createSegment(seg));
    }

    // 将交线曲线数组添加到第三个图形对象
    ptrGraphic3->addGeCurveArray(*ptrCurveArray3);

    // ========== 7. 保存所有图形到模型 ==========
    // 保存第一个矩形图形
    ptrGraphic1->save();
    // 保存第二个矩形图形
    ptrGraphic2->save();
    // 保存交线图形
    ptrGraphic3->save();
}

// ========== 函数注册 ==========
// 开始注册函数
AutoDoRegisterFunctionsBegin
// 将函数注册到工具管理器，外部可通过 "intersection" 调用
BPToolsManager::registerFun(_T("intersection"), &Intersection);
// 结束注册
AutoDoRegisterFunctionsEnd