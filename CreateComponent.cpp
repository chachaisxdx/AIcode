// 功能: 从模型构件创建组件原型，并生成多个组件实例（偏移摆放）
// 关键词: 创建组件, 组件原型, 组件实例, 构件组装, 偏移放置, BPComponentUtil
// 依赖类: BPComponentUtil, BPComponentPrototype, BPComponentElement, BPEntityUtil

#include "pch.h"

/**
 * @brief 创建组件（Component）
 * @note  该函数获取当前模型中的所有构件，基于它们创建组件原型，然后创建两个组件实例。
 *        实现步骤：
 *        1. 获取当前项目及活动模型。
 *        2. 获取模型中所有构件的 DataKey。
 *        3. 调用 BPComponentUtil::formComponentPrototype() 创建组件原型，名称为 "组件"。
 *        4. 基于原型创建第一个组件实例（位置为单位矩阵）。
 *        5. 基于原型创建第二个组件实例（位置为 X 方向偏移 3000）。
 *        注意：组件实例会添加到当前项目中。
 */
void CreateComponent()
{
    // 获取当前主工程对象
    BPProjectP pProject = BPApplication::getInstance().getProjectManager()->getMainProject();
    if (pProject == nullptr)
        return;

    // 获取当前活动模型（组件创建的载体）
    BPModelBaseP pModel = pProject->getActiveModel();

    // 定义实体ID集合，用于存储模型中的所有构件
    p3d::pset<BPEntityId> entitySet;
    // 定义数据键集合，用于存储构件对应的DataKey
    pvector<BPDataKey>  vctKey;

    // 获取当前模型下的所有实体（构件）
    BPEntityUtil::getEntitiesOfModel(entitySet, *pProject, pModel->getModelId());

    // 遍历所有实体ID，获取有效的构件数据键 DataKey
    for (auto entityId : entitySet)
    {
        // 根据实体ID构造实体对象
        BPEntity entity(entityId, *BPProject::getActiveProject());
        // 获取实体对应的数据键（用于标识构件）
        BPDataKey key = BPDataUtil::getDataKeyOnEntity(entity);
        // 如果数据键有效，则加入列表
        if (key.isValid())
            vctKey.push_back(key);
    }

    // 创建空的组件原型对象
    BPComponentPrototypePtr ptrPrototype = BPComponentPrototype::create();

    // 根据构件数据键，创建组件原型（命名为“组件”）
    if (!BPComponentUtil::formComponentPrototype(vctKey, pProject, L"组件", ptrPrototype))
        return;

    // ========== 创建第一个组件实例 ==========
    // 创建空组件实例对象
    BPComponentElementPtr ptrElement1 = BPComponentElement::create();
    // 基于原型创建组件实例，使用单位矩阵（放置在原点）
    bool bStatus2 = BPComponentUtil::formComponentElement(ptrPrototype, ptrElement1, pProject, GeTransform::createIdentityMatrix());

    // ========== 创建第二个组件实例 ==========
    // 创建空组件实例对象
    BPComponentElementPtr ptrElement2 = BPComponentElement::create();
    // 基于原型创建组件实例，使用X轴偏移3000的变换矩阵
    BPComponentUtil::formComponentElement(ptrPrototype, ptrElement2, pProject, GeTransform::create(3000, 0, 0));
}

// 注册函数到工具管理器，外部可通过名称调用
AutoDoRegisterFunctionsBegin
BPToolsManager::registerFun(_T("createcomponent"), &CreateComponent);
AutoDoRegisterFunctionsEnd