// 功能: 跨文件复制构件，将当前工程选中构件复制到另一个工程文件中
// 关键词: 跨文件复制, 构件复制, 打开工程, 复制到另一个模型, 跨工程拷贝
// 依赖类: BPSelectionSetManager, BPDataUtil, BPProject, BPObjectExtensionManager

#include "pch.h"

/**
 * @brief 跨文件复制构件
 * @note  该函数将当前项目中选中的第一个构件复制到另一个指定的项目文件中。
 *        实现步骤：
 *        1. 获取当前项目，检查是否有选中的构件。
 *        2. 获取选中构件的实体和数据对象。
 *        3. 获取对应的 IBPObject 对象。
 *        4. 打开目标工程文件（路径硬编码为 D:\\project\\test1.p3d）。
 *        5. 在目标工程中查找名为 "SYSTEM_AXIS" 的模型。
 *        6. 将对象添加到目标工程的指定模型中。
 *        7. 保存目标工程。
 *        注意：目标工程路径需根据实际情况修改。
 */
void CrossFileToCopy()
{
    // 获取当前主工程对象
    BPProjectP pProject = BPApplication::getInstance().getProjectManager()->getMainProject();
    if (pProject == nullptr)
        return;

    // 检查是否有选中的构件，未选中则直接返回
    if (BPSelectionSetManager::getInstance().getCount() == 0)
        return;

    // 获取选中的第一个构件实体
    BIMBase::Core::BPEntityPtr ptrEntity = BIMBase::Core::BPSelectionSetManager::getInstance().getEntityByIndex(0);
    if (ptrEntity.isNull())
        return;

    // 获取实体对应的业务数据对象
    BIMBase::Core::BPDataPtr ptrData = BPDataUtil::getDataOnEntity(*ptrEntity);
    if (!ptrData.isValid())
        return;

    // 获取可复制的业务对象（用于跨工程拷贝）
    IBPObjectPtr ptrObjCopy = BPObjectExtensionManager::getInstance().getBPObject(*pProject, ptrData->getDataKey());
    if (ptrObjCopy.isNull())
        return;

    // 目标工程文件路径（需要根据实际环境修改）
    p3d::PString docPath = L"D:\\project\\test1.p3d";
    p3d::P3DStatus status;

    // 以读写模式打开目标工程文件
    BIMBase::Core::BPProjectP _project = BPApplication::getInstance().getProjectManager()->openProject(status, docPath, BIMBase::Core::BPProject::BPOpenMode::enReadWrite);
    if (_project == nullptr)
        return;

    // 在目标工程中查找名为 "SYSTEM_AXIS" 的模型ID
    PModelId modelId = _project->findModelIdByName("SYSTEM_AXIS");

    // 将复制的构件对象添加到目标工程的指定模型中
    ::p3d::P3DStatus sta = ptrObjCopy->addToProject(*_project, modelId);

    // 保存目标工程
    p3d::P3DStatus staSave = BPApplication::getInstance().getProjectManager()->saveProject(_project->getProjectHandle());
}

// 注册函数到工具管理器
AutoDoRegisterFunctionsBegin
BPToolsManager::registerFun(_T("crossfiletocopy"), &CrossFileToCopy);
AutoDoRegisterFunctionsEnd