/*******************************************************************************
【文件名】 ObjExporter.cpp
【功能模块和目的】 实现ObjExporter类，用于导出.obj文件，
 Created by 朱昊东 on 2024/7/27
【更改记录】 2024/7/28 朱昊东
        修改了Save函数中输出模型的起始序号应该为1的问题
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
    - std::string path（输入参数）：字符串，文件路径
【返回值】 无
Created by 朱昊东 on 2024/7/26
【更改记录】 无
*******************************************************************************/
bool ObjExporter::CheckExtension(std::string path) const {
    const std::string extension = ".obj";
    if (path.length() >= extension.length()) {
        return (0 == path.compare(path.length() - extension.length(),
                                  extension.length(), extension));
    } else {
        return false;
    }
}

/*******************************************************************************
【函数名称】 Save
【函数功能】 保存模型
【参数】 
    - std::ofstream& file（输入参数）：文件流对象
    - const Model3D& model（输入参数）：Model3D对象，三维模型
【返回值】 无
Created by 朱昊东 on 2024/7/26
【更改记录】 2024/7/28 朱昊东
        修改了输出模型的起始序号应该为1的问题
*******************************************************************************/
void ObjExporter::Save(std::ofstream& file, const Model3D& model) const {
    file << "g " << model.Name << std::endl;//输出模型名
    for (auto point: model.CollectPoints()) {
        file << "v ";
        for (int i = 0; i < 3; i++) {
            file << " " << point->GetCoordinate(i); 
        }
        file << std::endl;
    }//输出点

    std::vector<std::shared_ptr<Point<3>>> points = model.CollectPoints();
    auto findPointIndex = [&points](const std::shared_ptr<Point<3>> point) -> int {
        auto it = std::find(points.begin(), points.end(), point);
        if (it != points.end()) {
            return std::distance(points.begin(), it) + 1;
        }
        return -1; // 如果没有找到，返回 -1
    };//查找point在points中的序号

    for (auto line: model.Lines) {
        file << "l  ";
        file << findPointIndex(line->First) << " ";
        file << findPointIndex(line->Second) << std::endl;
    }
    for (auto face: model.Faces) {
        file << "f  ";
        file << findPointIndex(face->First) << " ";
        file << findPointIndex(face->Second) << " ";
        file << findPointIndex(face->Third) << std::endl;
    }
    file.close();
}
