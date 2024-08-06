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
    - void Run(Controller& controller) const
        运行方法，实现controller与用户的交互
    - bool LoadModel(Controller& controller, std::string* path) const
        加载模型
    - void SaveModel(const Controller& controller, std::string defaultPath) const
        保存模型
    - void ShowHelp() const
        显示帮助信息
    - void ShowStatistics(const Controller& controller) const
        显示统计信息
    - void ListFaces(const Controller& controller) const
        列出面
    - void ListFace_sPoints(const Controller& controller) const
        列出面的点
    - void AddFace(Controller& controller) const
        添加面
    - void RemoveFace(Controller& controller) const
        移除面
    - void ModifyFace(Controller& controller) const
        修改面
    - void ListLines(const Controller& controller) const
        列出线
    - void ListLine_sPoints(const Controller& controller) const
        列出线的点
    - void AddLine(Controller& controller) const
        添加线
    - void RemoveLine(Controller& controller) const
        移除线
    - void ModifyLine(Controller& controller) const
        修改线
 Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
class ConsoleView: public AbstractView {
    public:
        //默认构造函数
        ConsoleView() = default;
        //运行方法
        void Run(Controller& controller) const override;
    private:
        //加载模型
        bool LoadModel(Controller& controller, std::string* path) const;
        //保存模型
        void SaveModel(const Controller& controller, std::string defaultPath) const;
        //显示帮助信息
        void ShowHelp() const;
        //显示统计信息
        void ShowStatistics(const Controller& controller) const;
        //列出面
        void ListFaces(const Controller& controller) const;
        //列出面的点
        void ListFace_sPoints(const Controller& controller) const;
        //添加面
        void AddFace(Controller& controller) const;
        //移除面
        void RemoveFace(Controller& controller) const;
        //修改面
        void ModifyFace(Controller& controller) const;
        //列出线
        void ListLines(const Controller& controller) const;
        //列出线的点
        void ListLine_sPoints(const Controller& controller) const;
        //添加线
        void AddLine(Controller& controller) const;
        //移除线
        void RemoveLine(Controller& controller) const;
        //修改线
        void ModifyLine(Controller& controller) const;
};


#endif // CONSOLE_VIEW_HPP