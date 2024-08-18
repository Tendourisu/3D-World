/*******************************************************************************
【文件名】ConsoleView.hpp
【功能模块和目的】 控制台视图类，通过console实现controller与用户的交互
 Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
#ifndef CONSOLE_VIEW_HPP
#define CONSOLE_VIEW_HPP


#include "../Controllers/Controller.hpp"
#include "AbstractView.hpp"

/*******************************************************************************
【类名】 ConsoleView
【功能】 控制台视图类，提供对模型的操作
【接口说明】
    - void Run(Controller& Controller) const
        运行方法，实现controller与用户的交互
    - bool LoadModel(Controller& Controller, std::string* path) const
        加载模型
    - void SaveModel(const Controller& Controller, std::string defaultPath) const
        保存模型
    - void ShowHelp() const
        显示帮助信息
    - void ShowStatistics(const Controller& Controller) const
        显示统计信息
    - void ListFaces(const Controller& Controller) const
        列出面
    - void ListFace_sPoints(const Controller& Controller) const
        列出面的点
    - void AddFace(Controller& Controller) const
        添加面
    - void RemoveFace(Controller& Controller) const
        移除面
    - void ModifyFace(Controller& Controller) const
        修改面
    - void ListLines(const Controller& Controller) const
        列出线
    - void ListLine_sPoints(const Controller& Controller) const
        列出线的点
    - void AddLine(Controller& Controller) const
        添加线
    - void RemoveLine(Controller& Controller) const
        移除线
    - void ModifyLine(Controller& Controller) const
        修改线
 Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
class ConsoleView: public AbstractView {
    public:
        //默认构造函数
        ConsoleView() = default;
        //运行方法
        void Run(Controller& Controller) const override;
    private:
        //加载模型
        bool LoadModel(Controller& Controller, std::string* path) const;
        //保存模型
        void SaveModel(const Controller& Controller, std::string defaultPath) const;
        //显示帮助信息
        void ShowHelp() const;
        //显示统计信息
        void ShowStatistics(const Controller& Controller) const;
        //列出面
        void ListFaces(const Controller& Controller) const;
        //列出面的点
        void ListFace_sPoints(const Controller& Controller) const;
        //添加面
        void AddFace(Controller& Controller) const;
        //移除面
        void RemoveFace(Controller& Controller) const;
        //修改面
        void ModifyFace(Controller& Controller) const;
        //列出线
        void ListLines(const Controller& Controller) const;
        //列出线的点
        void ListLine_sPoints(const Controller& Controller) const;
        //添加线
        void AddLine(Controller& Controller) const;
        //移除线
        void RemoveLine(Controller& Controller) const;
        //修改线
        void ModifyLine(Controller& Controller) const;
};


#endif // CONSOLE_VIEW_HPP