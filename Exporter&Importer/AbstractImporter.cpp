/*******************************************************************************
【文件名】 AbstractImporter.cpp
【功能模块和目的】 实现抽象类AbstractImporter，提供导入方法Import
 Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
#include <string>
#include <fstream>
#include "AbstractImporter.hpp"
#include "../Errors.hpp"

/*******************************************************************************
【函数名称】 Import
【函数功能】 导入model到path
【参数】 
    - std::string path（输入参数）：字符串，文件路径
    - const Model3D& model（输入参数）：Model3D对象，三维模型
【返回值】 无
Created by 朱昊东 on 2024/7/26
【更改记录】 无
*******************************************************************************/
void AbstractImporter::Import(std::string path, Model3D& model) const {
    if (!CheckExtension(path)) {
        throw ExceptionFileExtension();
    }//检查扩展名
    std::ifstream file;
    file.open(path, std::ios::in);//打开文件
    if (!file.is_open()) {
        throw ExceptionFileOpen();
    }//打开失败
    Load(file, model);
    file.close();
}