/*******************************************************************************
【文件名】 main.cpp
【功能模块和目的】 主函数，程序入口
 Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
#include "Controllers/Controller.hpp"
#include "Views/ConsoleView.hpp"
using namespace std;

int main() {
    ConsoleView View;
    Controller& Controller = Controller::GetInstance();
    View.Run(Controller);
    return 0;
}