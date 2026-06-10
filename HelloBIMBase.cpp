// 功能: 弹出提示框显示Hello BIMBase，用于测试插件/函数是否正常运行
// 关键词: 测试函数, 消息框, 弹窗提示, AfxMessageBox, 环境测试
// 依赖类: 无（MFC基础弹窗函数）

#include "pch.h"

/**
 * @brief 显示 Hello BIMBase 消息框
 * @note  该函数弹出一个模态对话框，显示 "Hello BIMBase！" 字符串。
 *        常用于测试 BIMBase 环境是否正常初始化。
 */
void HelloBimBase()
{
    // 弹出MFC模态消息框，显示测试文本
    AfxMessageBox(L"Hello BIMBase！");
}

// 自动注册函数到BIM工具管理器（固定注册语法）
AutoDoRegisterFunctionsBegin
// 注册测试弹窗函数，外部可通过"hellobimbase"调用
BPToolsManager::registerFun(_T("hellobimbase"), &HelloBimBase);
// 结束函数注册
AutoDoRegisterFunctionsEnd