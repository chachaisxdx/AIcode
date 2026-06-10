#include "pch.h"
// 引入BPBase基础API头文件，提供核心图形/几何操作接口
#include "BPBase/BPBaseAPI.h"

// 命名空间声明：使用p3d核心库命名空间
using namespace p3d;
// 使用BIMBase基础库命名空间
using namespace BIMBase;
// 使用BIMBase实体核心库命名空间（包含实体/几何操作）
using namespace BIMBase::SolidCore;
// 使用BIMBase核心库命名空间（包含基础图形类）
using namespace BIMBase::Core;

// 引入当前示例类头文件
#include "BPHideLineExample.h"

// 使用BPTraffic命名空间（交通BIM相关）
USING_NAMESPACE_BPTRAFFIC;

/**
 * @brief 消隐线计算前的几何变换预处理
 * @param agenda 待处理的图形对象列表（包含Polyface/GeSolidBase等几何类型）
 * @param trans 几何变换矩阵（用于统一调整图形坐标）
 * @note 对图形列表中的每个元素执行坐标变换，为后续消隐线计算做准备
 */
void BPHideLineExample::preHideLine(const pvector<BPGraphicsPtr>& agenda, const GeTransform& trans)
{
	// 遍历图形列表中的每个图形对象
	for (auto& graphic : agenda)
	{
		// 遍历图形对象中的每个几何条目
		for (auto& entry : *graphic)
		{
			// 判断条目类型为多边形面（Polyface）
			if (entry->getType() == BPGraphics::Entry::Type::Polyface)
			{
				// 转换为Polyface句柄
				auto poly = entry->getAsPolyfaceHandleP();
				// 应用几何变换矩阵
				poly->transformBy(trans);
			}
			// 判断条目类型为几何实体基类（GeSolidBase）
			else if (entry->getType() == BPGraphics::Entry::Type::GeSolidBase)
			{
				// 转换为GeSolidBase指针
				auto solidBase = entry->getAsGeSolidBaseP();
				// 应用几何变换
				solidBase->transform(trans);
			}
		}
	}
}

/**
 * @brief 消隐线计算后的几何变换后处理
 * @param resSect 消隐线计算结果（键值对：图形ID -> 消隐线数据列表）
 * @param trans 几何变换矩阵（用于还原消隐线坐标）
 * @note 对计算出的消隐线曲线执行逆变换，恢复到原始坐标系
 */
void BPHideLineExample::afterHideLine(p3d::pmap<size_t, T_HideLineDataVector>& resSect, const GeTransform& trans)
{
	// 遍历消隐线计算结果
	for (auto resIter = resSect.begin(); resIter != resSect.end(); ++resIter)
	{
		// 遍历单个图形对应的所有消隐线曲线
		for (auto& curve : resIter->second)
		{
			// 对曲线应用变换矩阵，调整坐标
			curve.m_curve->setByTransform(trans);
		}
	}
}

/**
 * @brief 消隐线计算测试主函数
 * @return 执行结果（TRUE=成功，FALSE=失败）
 * @note 完整演示：创建测试几何→获取场景图形→设置剖切参数→计算消隐线→绘制消隐线
 */
BOOL BPHideLineExample::test()
{
	// ===================== 第一步：创建测试几何实体（球体、圆环、拉伸体） =====================
	// 创建原点坐标(0,0,0)
	GePoint3d geOrigin = GePoint3d::create(0, 0, 0);
	// 创建球体参数：原点为球心，半径100.0
	GeSphereInfo sphere(geOrigin, 100.0);
	// 根据球体参数创建几何实体
	IGeSolidBasePtr solidSphere = IGeSolidBase::createGeSphere(sphere);
	// 创建图形对象（关联到当前激活模型）
	BPGraphicsPtr sphereGra = new BPGraphics(BPModel::getActiveModel());
	// 将球体实体添加到图形对象
	sphereGra->addGeSolidBase(*solidSphere);
	// 保存图形对象到模型
	sphereGra->save();

	// 创建圆环参数：原点、X轴方向、Y轴方向、外径400、内径50、全周角、顺时针
	GeTorusPipeInfo  torus(GePoint3d::create(0, 0, 0),
		GeVec3d::create(1, 0, 0),
		GeVec3d::create(0, 1, 0),
		400, 50, GeAngle::getTwoPi(), true);
	// 创建圆环几何实体
	IGeSolidBasePtr torusBox = IGeSolidBase::createGeTorusPipe(torus);
	// 创建圆环图形对象
	BPGraphicsPtr torusGra = new BPGraphics(BPModel::getActiveModel());
	torusGra->addGeSolidBase(*torusBox);
	torusGra->save();

	// 定义拉伸体外轮廓点集（矩形，Z=-100平面）
	pvector<GePoint3d> outterPts = {
		GePoint3d::create(-100,-100,-100),GePoint3d::create(100,-100,-100),GePoint3d::create(100,100,-100),
		GePoint3d::create(-100,100,-100),GePoint3d::create(-100,-100,-100),
	};
	// 定义拉伸体内轮廓点集（内部镂空矩形）
	pvector<GePoint3d> innerPts = {
	GePoint3d::create(-50,-50,-100),GePoint3d::create(-50,50,-100),GePoint3d::create(50,50,-100),
	GePoint3d::create(50,-50,-100),GePoint3d::create(-50,-50,-100),
	};

	// 创建外轮廓线串（外环类型）
	GeCurveArrayPtr outterCurArr = GeCurveArray::createLinestringArray(outterPts, GeCurveArray::BOUNDARY_TYPE_Outer);
	// 创建内轮廓线串（内环类型）
	GeCurveArrayPtr innerCurArr = GeCurveArray::createLinestringArray(innerPts, GeCurveArray::BOUNDARY_TYPE_Inner);
	// 创建拉伸截面（奇偶区域类型，支持内外轮廓）
	GeCurveArrayPtr sectionPlane = GeCurveArray::create(GeCurveArray::BOUNDARY_TYPE_ParityRegion);
	// 添加外轮廓到截面
	sectionPlane->add(outterCurArr);
	// 添加内轮廓到截面
	sectionPlane->add(innerCurArr);

	// 创建拉伸参数：截面、拉伸方向(Z轴)、是否封口
	GeExtrusionInfo extru(sectionPlane, GeVec3d::create(0, 0, 100), true);
	// 创建拉伸几何实体（带镂空的长方体）
	IGeSolidBasePtr huiSolid = IGeSolidBase::createGeExtrusion(extru);
	// 创建拉伸体图形对象
	BPGraphicsPtr huiGra = new BPGraphics(BPModel::getActiveModel());
	huiGra->addGeSolidBase(*huiSolid);
	huiGra->save();

	// ===================== 第二步：获取场景中所有图形实体 =====================
	// 获取当前激活的工程对象
	BPProjectP pProject = BPProject::getActiveProject();
	if (nullptr == pProject)
		return FALSE;
	// 获取当前激活的模型对象
	BPModelBaseP pModel = pProject->getActiveModel();
	if (nullptr == pModel)
		return FALSE;
	// 获取模型中的所有图形实体
	BPEntityVectorP pEntityVector = pModel->getGraphicEntitys();
	if (nullptr == pEntityVector)
		return FALSE;

	// 存储场景中的图形对象列表
	T_GraphicsVector graphics;
	// 创建空的几何范围对象（用于计算场景包围盒）
	GeRange3d range = GeRange3d::createByNull();

	// 遍历所有图形实体
	for (auto& pEntity : *pEntityVector)
	{
		// 判断实体是否为图形类型
		if (pEntity->isGraphics())
		{
			// 计算当前图形的几何范围
			GeRange3d tm = GeRange3d::createByNull();
			pEntity->getRange(tm);
			// 扩展全局范围
			range.extendRange(tm);
			// 将实体转换为图形对象并加入列表
			graphics.push_back(BPGraphics::getGraphicsFromEntity(*pEntity));
		}
	}

	// ===================== 第三步：设置剖切平面和剖切盒参数 =====================
	// 初始化裁剪平面（消隐线计算的基准平面）
	GePlane3d plane;
	// 裁剪平面原点(0,0,0)
	GePoint3d originPt = GePoint3d::create(0, 0, 0);
	// 裁剪平面法向量（斜面：(1,1,1)方向，替代原Z轴负方向）
	GeVec3d planeNormal = GeVec3d::create(1, 1, 1);
	// 法向量归一化（确保方向向量长度为1）
	planeNormal.normalize();
	// 根据原点和法向量创建裁剪平面
	plane = GePlane3d::createByOriginAndNormal(originPt, planeNormal);

	// 初始化剖切盒变换矩阵（单位矩阵）
	GeTransform sectionBox = GeTransform::createIdentityMatrix();
	// 创建局部坐标系旋转矩阵：基于(1,1,1)向量，绕Z轴旋转2度（右手定则）
	GeRotMatrix localCoord = GeRotMatrix::createByVector(GeVec3d::create(1, 1, 1), 2, true);
	// 获取局部坐标系的X/Y/Z轴向量
	GeVec3d x, y, z;
	localCoord.getColumns(x, y, z);
	// 剖切盒尺寸
	double len = 1200.0;
	// 剖切盒原点（偏移X/Y轴各半长）
	GePoint3d origin = GePoint3d::create(0, 0, 0) - x * len * 0.5 - y * len * 0.5;
	// 创建剖切盒变换矩阵（基于原点和局部坐标系轴）
	sectionBox = GeTransform::createByOriginAndVectors(origin, x, y, z);

	// 创建剖切盒参数：原点、Z轴终点、X/Y轴、尺寸参数、是否封口
	GeBoxInfo box(
		origin,
		origin + z * len * 0.3,
		x, y, len, len, len, len, true
	);
	// 创建剖切盒几何实体
	IGeSolidBasePtr solidBox = IGeSolidBase::createGeBox(box);
	// 创建剖切盒图形对象
	BPGraphicsPtr boxGraphics = new BPGraphics(BPModel::getActiveModel());
	boxGraphics->addGeSolidBase(*solidBox);
	//boxGraphics->save();  // 调试用：保存剖切盒到模型，可可视化查看

	// 存储布尔运算后的图形对象列表
	pvector<::BIMBase::Core::BPGraphicsPtr> boolGraphicVec;

	// ===================== 第四步：执行剖切盒与场景图形的布尔交集运算 =====================
	// 获取当前角度公差（用于布尔运算精度控制）
	int angle;
	SolidCore::BPSolidBooleanUtil::getAngleTolerance(angle);
	// 设置角度公差为36（降低精度，提升运算速度）
	SolidCore::BPSolidBooleanUtil::setAngleTolerance(36);

	// 遍历场景图形，执行布尔交集运算（保留图形与剖切盒的重叠部分）
	for (auto& graphic : graphics)
	{
		::BIMBase::Core::BPGraphicsPtr boolGraphic = new BPGraphics(::BPModel::getActiveModel());
		// 布尔运算：交集（Intersection）= 剖切盒 ∩ 场景图形
		SolidCore::BPSolidBooleanUtil::doBoolean(boolGraphic, boxGraphics, graphic, BPBooleanOp::Intersection);
		// 保存布尔运算结果
		boolGraphicVec.push_back(boolGraphic);
	}
	// 恢复原始角度公差
	SolidCore::BPSolidBooleanUtil::setAngleTolerance(angle);

	// ===================== 第五步：计算消隐线并绘制 =====================
	// 调用消隐线计算核心函数，传入布尔运算后的图形和裁剪平面
	pmap<size_t, T_HideLineDataVector> ret = HideLineEntity(boolGraphicVec, plane);

	// 定义消隐线样式：线型1（虚线）、颜色绿色(0,255,0)
	BPSymbology symbol;
	symbol.style = 1;
	symbol.color = RGB(0, 255, 0);

	// 创建消隐线图形对象（关联到当前模型）
	BPGraphicsPtr hideLines = pModel->createPhysicalGraphics();
	// 遍历消隐线计算结果
	for (auto& hideLineVec : ret)
	{
		// 遍历单张图形的所有消隐线
		for (auto& hideLine : hideLineVec.second)
		{
			// 判断是否为隐藏线
			if (hideLine.m_isHidden)
			{
				// 绘制隐藏线：使用自定义样式（绿色虚线）
				hideLines->addGeCurveArray(*hideLine.m_curve.get(), symbol);
			}
			else
			{
				// 绘制可见线：使用默认样式
				hideLines->addGeCurveArray(*hideLine.m_curve.get());
			}
		}
	}
	// 保存消隐线图形到模型（完成绘制）
	hideLines->save();

	return TRUE;
}

/**
 * @brief 消隐线计算核心函数
 * @param graphics 待计算的图形对象列表（布尔运算后）
 * @param plane 裁剪平面（消隐线计算基准）
 * @return 消隐线计算结果（图形ID -> 消隐线数据列表）
 * @note 核心流程：坐标变换→消隐线计算→坐标还原
 */
P3D_NAMESPACE_NAME::pmap<size_t, BIMBase::SolidCore::T_HideLineDataVector> BPHideLineExample::HideLineEntity(T_GraphicsVector& graphics, ::p3d::GePlane3dCR plane/*, p3d::GeTransformCR sectionBox*/)
{
	// 转换常量平面为可修改引用
	GePlane3dR planeR = const_cast<GePlane3dR>(plane);

	// 声明变换矩阵：图形变换（预处理）、消隐线变换（后处理）
	GeTransform graphicTrans;
	GeTransform hiddenLineTrans;
	// 计算变换矩阵并重置裁剪平面（适配消隐线计算坐标系）
	BPHideLineEntity::computeTransformAndResetPlane(graphicTrans, hiddenLineTrans, planeR);

	// 预处理：对图形执行坐标变换
	preHideLine(graphics, graphicTrans);
	// 创建消隐线计算对象，传入图形和裁剪平面
	BPHideLineEntity hideLine(graphics, plane/*, sectionBox*/);
	// 执行消隐线计算并获取结果
	pmap<size_t, BIMBase::SolidCore::T_HideLineDataVector>lineRet = hideLine.getHideLineResult();
	// 后处理：对消隐线执行坐标还原
	afterHideLine(lineRet, hiddenLineTrans);

	return lineRet;
}

/**
 * @brief 消隐线测试入口函数（供外部调用）
 * @note 封装测试流程，注册后可通过BIM工具管理器调用
 */
void HideLine()
{
	// 创建消隐线示例对象
	BPHideLineExample hideLine;
	// 执行测试主函数
	hideLine.test();
}

// ===================== 函数注册（BIM工具管理器） =====================
// 注册宏开始
AutoDoRegisterFunctionsBegin
// 注册函数到BIM工具管理器：名称"testHideLine"，关联到HideLine函数
BIMBase::BPToolsManager::registerFun(L"testHideLine", &HideLine);
// 注册宏结束
AutoDoRegisterFunctionsEnd