// 功能: 将模型中所有构件组合成一个组，并设置组模式
// 关键词: 创建组合, 构件分组, group, 组合管理, BPGroupUtil, BPGroupManager
// 依赖类: BPGroupUtil, BPGroupManager, BPEntityUtil, BPDataUtil

#include "pch.h"

/**
 * @brief 创建组合（Group）
 * @note  该函数获取当前活动模型中的所有构件，将其组合成一个名为 "组合" 的组合对象，
 *        并将组合模式设置为开始组状态。
 *        实现步骤：
 *        1. 获取当前项目及活动模型。
 *        2. 获取模型中所有实体的 EntityId。
 *        3. 遍历实体，获取对应的 DataKey。
 *        4. 调用 BPGroupUtil::group() 创建组合，名称为 L"组合"。
 *        5. 调用 setGroupMode 将组合模式设为 enGroup（开始组）。
 */
void CreateGroup()
{
    // 获取当前主工程对象
    BPProjectP pProject = BPApplication::getInstance().getProjectManager()->getMainProject();
    if (pProject == nullptr)
        return;

    // 获取当前活动模型（组合操作的载体）
    BPModelBaseP pModel = pProject->getActiveModel();

    // 定义实体ID集合，用于存储模型中的所有构件
    p3d::pset<BPEntityId> entitySet;
    // 定义数据键列表，用于存储构件的唯一标识
    vector<BPDataKey>  vctKey;

    // 获取当前模型下的所有实体（构件）
    BPEntityUtil::getEntitiesOfModel(entitySet, *pProject, pModel->getModelId());

    // 遍历所有实体ID，提取有效的数据键 DataKey
    for (auto entityId : entitySet)
    {
        // 根据实体ID构造实体对象
        BPEntity entity(entityId, *BPProject::getActiveProject());
        // 获取实体对应的数据键（用于标识构件）
        BPDataKey key = BPDataUtil::getDataKeyOnEntity(entity);
        // 只加入有效数据键
        if (key.isValid())
            vctKey.push_back(key);
    }

    // 将所有构件按数据键组合成一个名为 "组合" 的组
    BPGroupUtil::group(vctKey, L"组合");

    // 设置全局组合模式为：开始组状态
    BPGroupManager::getInstance().setGroupMode(BPGroupMode::enGroup);
}

// 注册函数到工具管理器，外部可通过名称调用
AutoDoRegisterFunctionsBegin
BPToolsManager::registerFun(_T("creategroup"), &CreateGroup);
AutoDoRegisterFunctionsEnd