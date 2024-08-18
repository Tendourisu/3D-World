/*******************************************************************************
【文件名】 ObjExporter.cpp
【功能模块和目的】 实现ObjExporter类，用于导出.obj文件，
 Created by 朱昊东 on 2024/7/27
【更改记录】 
    2024/7/28 朱昊东
    - 修复了Save函数中输出模型的起始序号应该为1的问题
*******************************************************************************/
#include <fstream>
#include <filesystem>
#include <string>
#include "ObjExporter.hpp"
#include "../Models/Model.hpp"

/*******************************************************************************
【函数名称】 CheckExtension
【函数功能】 检查扩展名为.obj
【参数】 
    - std::string Path（输入参数）：字符串，文件路径
【返回值】 无
Created by 朱昊东 on 2024/7/26
【更改记录】 无
*******************************************************************************/
bool ObjExporter::CheckExtension(std::string Path) const {
    const std::string extension = ".obj";
    if (Path.length() >= extension.length()) {
        return (0 == Path.compare(Path.length() - extension.length(),
            extension.length(), extension));
    } else {
        return false;
    }
}

/*******************************************************************************
【函数名称】 Save
【函数功能】 保存模型
【参数】 
    - std::ofstream& File（输入参数）：文件流对象
    - const Model3D& Model（输入参数）：Model3D对象，三维模型
【返回值】 无
Created by 朱昊东 on 2024/7/26
【更改记录】 
    2024/7/28 朱昊东
    - 修复了输出模型的起始序号应该为1的问题
*******************************************************************************/
void ObjExporter::Save(std::ofstream& File, const Model3D& Model) const {
    File << "g " << Model.Name << std::endl;//输出模型名
    for (auto Point: Model.CollectPoints()) {
        File << "v ";
        for (int i = 0; i < 3; i++) {
            File << " " << Point->GetCoordinate(i); 
        }
        File << std::endl;
    }//输出点

    std::vector<std::shared_ptr<Point<3>>> Points = Model.CollectPoints();
    auto FindPointIndex = [&Points](const std::shared_ptr<Point<3>> Point)
        -> int {
        auto it = std::find(Points.begin(), Points.end(), Point);
        if (it != Points.end()) {
            return std::distance(Points.begin(), it) + 1;
        }
        return -1; // 如果没有找到，返回 -1
    };//查找point在points中的序号

    for (auto Line: Model.Lines) {
        File << "l  ";
        File << FindPointIndex(Line->First) << " ";
        File << FindPointIndex(Line->Second) << std::endl;
    }
    for (auto Face: Model.Faces) {
        File << "f  ";
        File << FindPointIndex(Face->First) << " ";
        File << FindPointIndex(Face->Second) << " ";
        File << FindPointIndex(Face->Third) << std::endl;
    }
    File.close();
}
