// 功能: 创建模型直线并设置线型、线宽、颜色属性
// 关键词: 创建直线, BPModelLine, 设置线型, 设置线宽, 设置颜色, BPEntity
// 依赖类: BPModelLine, BPEntity, BPEntityUtil, BPColorUtil
#include "pch.h"


void createModelLine()
{
	// 获取应用程序单例 -> 获取工程管理器 -> 获取当前主工程
	BPProjectP pProject = BPApplication::getInstance().getProjectManager()->getMainProject();
	// 工程指针为空，直接返回避免崩溃
	if (pProject == nullptr)
		return;

	// 获取当前工程中激活的模型（绘制元素的载体）
	BPModelBaseP pModel = pProject->getActiveModel();

	// 创建线对象：定义起点(3000,3000,0)和终点(4000,4000,0)
	BPModelLine line(GePoint3d::create(3000, 3000, 0), GePoint3d::create(4000, 4000, 0));

	// 将直线对象添加到工程与指定模型中，返回操作状态
	::p3d::P3DStatus status = line.addToProject(*pProject, pModel->getModelId());

	// 定义实体数组，用于存储模型中的所有实体
	BPEntityArray entityArray;
	// 获取当前模型下的所有实体对象
	BPEntityUtil::getEntitiesOfModel(entityArray, *pProject, pModel->getModelId());
	// 获取第一个实体（即刚刚创建的直线）
	BPEntityPtr entityptr = entityArray.getByIndex(0);

	// 改变线型
	// 0—P_Continuous、1-P_Dot、2-P_Dash1、3-P_Dash2、4-P_Dash_Dot1、5-P_Dash3、6-P_Dash_Double_dot、7-P_Dash_Dot2
	entityptr->setLineStyle(1);

	// 改变线宽
	// 线宽索引值0-23对应0.00mm-2.11mm，与CAD线宽完全一致
	entityptr->setWeight(23);

	// 改变颜色
	// 使用BPColorUtil进行RGB颜色与索引色转换
	UInt32 color = BPColorUtil::getEntityColor(RGB(255, 0, 0), *pProject, true);
	// 给实体设置颜色
	entityptr->setColor(color);

	// 将修改后的属性更新同步到模型中
	entityptr->replaceInModel(entityptr.get(), false);
}

// 注册函数到工具管理器，外部可通过按钮/菜单调用
AutoDoRegisterFunctionsBegin
// 注册：创建模型直线示例
BPToolsManager::registerFun(_T("createModelLineDemo"), &createModelLine);
AutoDoRegisterFunctionsEnd