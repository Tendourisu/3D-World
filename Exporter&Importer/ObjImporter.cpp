/*******************************************************************************
【文件名】 ObjImporter.cpp
【功能模块和目的】 实现ObjImporter类，用于导入.obj文件，
 Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "ObjImporter.hpp"
#include "../Errors.hpp"
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
bool ObjImporter::CheckExtension(std::string path) const {
    const std::string extension = ".obj";
    if (path.length() >= extension.length()) {
        return (0 == path.compare(path.length() - extension.length(), extension.length(), extension));
    } else {
        return false;
    }
}

/*******************************************************************************
【函数名称】 Load
【函数功能】 加载模型
【参数】 
    - std::ifstream& file（输入参数）：文件流对象
    - const Model3D& model（输入参数）：Model3D对象，三维模型
【返回值】 无
Created by 朱昊东 on 2024/7/26
【更改记录】 无
*******************************************************************************/
void ObjImporter::Load(std::ifstream &file, Model3D& model) const {
    std::vector<std::shared_ptr<Point3D>> points;
    while (!file.eof()) {
        std::string line;
        std::getline(file, line);
        if (line.length() == 0) continue;
        std::istringstream stream(line);
        char kind;
        stream >> kind;
        switch (kind) {
            case '#': {
                continue;
            }
            case 'g': {
                stream.get();
                std::string name;
                std::getline(stream, name);
                model.SetName(name);
                break;
            }
            case 'v': {
                double coords[3] = {0};
                stream >> coords[0] >> coords[1] >> coords[2];
                points.push_back(std::shared_ptr<Point3D>(new Point3D(coords)));
                break;
            }
            case 'l': {
                int indices[2] = {0};
                stream >> indices[0] >> indices[1];
                model.AddLineUnchecked(Line3D(points[indices[0]-1], points[indices[1]-1]));
                break;
            }
            case 'f': {
                int indices[3] = {0};
                stream >> indices[0] >> indices[1] >> indices[2];
                model.AddFaceUnchecked(Face3D(points[indices[0]-1], points[indices[1]-1], points[indices[2]-1]));
                break;
            }
            default: {
                throw ExceptionFileFormat();
            }
        }
    }
}