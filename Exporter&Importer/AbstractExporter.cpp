/*******************************************************************************
【文件名】 AbstractExporter.cpp
【功能模块和目的】 实现抽象类AbstractExporter，提供导出方法Export
 Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
#include <fstream>
#include <string>
#include "AbstractExporter.hpp"
#include "../Errors.hpp"

/*******************************************************************************
【函数名称】 Export
【函数功能】 导出model到path
【参数】 
    - std::string path（输入参数）：字符串，文件路径
    - const Model3D& model（输入参数）：Model3D对象，三维模型
【返回值】 无
Created by 朱昊东 on 2024/7/26
【更改记录】 无
*******************************************************************************/
void AbstractExporter::Export(std::string path, const Model3D& model) const {
    if (!CheckExtension(path)) {
        throw ExceptionFileExtension();
    }//检查扩展名
    std::ofstream file;
    file.open(path, std::ios::trunc);//打开文件
    if (!file.is_open()) {
        throw ExceptionFileOpen();
    }//打开失败
    Save(file, model);
    file.close();
}