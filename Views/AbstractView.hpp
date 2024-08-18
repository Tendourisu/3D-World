/*******************************************************************************
【文件名】 AbstractView.hpp
【功能模块和目的】 定义抽象类AbstractView，提供运行方法Run
 Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
#ifndef ABSTRACT_VIEW_HPP
#define ABSTRACT_VIEW_HPP

#include "../Controllers/Controller.hpp"

/*******************************************************************************
【类名】 AbstractView
【功能】 定义抽象类AbstractView，提供运行方法Run
【接口说明】
    - virtual void Run(Controller& Controller) const
        运行方法（纯虚函数），实现controller与用户的交互
 Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
class AbstractView {
    public:
        //运行方法（纯虚函数）
        virtual void Run(Controller& Controller) const = 0;
};

#endif // ABSTRACT_VIEW_HPP