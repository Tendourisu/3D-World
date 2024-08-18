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
    std::vector<std::shared_ptr<Point3D>> Points;
    while (!file.eof()) {
        std::string LineContent;
        std::getline(file, LineContent);
        if (LineContent.length() == 0) continue;
        std::istringstream Stream(LineContent);
        char Kind;
        Stream >> Kind;
        switch (Kind) {
            case '#' : {
                continue;
            }
            case 'g' : {
                Stream.get();
                std::string Name;
                std::getline(Stream, Name);
                model.SetName(Name);
                break;
            }
            case 'v' : {
                double Coords[3] = {0};
                Stream >> Coords[0] >> Coords[1] >> Coords[2];
                Points.push_back(std::shared_ptr<Point3D>(new Point3D(Coords)));
                break;
            }
            case 'l' : {
                int Indices[2] = {0};
                Stream >> Indices[0] >> Indices[1];
                model.AddLineUnchecked(Line3D(Points[Indices[0]-1], Points[Indices[1]-1]));
                break;
            }
            case 'f' : {
                int Indices[3] = {0};
                Stream >> Indices[0] >> Indices[1] >> Indices[2];
                model.AddFaceUnchecked(Face3D(Points[Indices[0]-1], Points[Indices[1]-1], Points[Indices[2]-1]));
                break;
            }
            default : {
                throw ExceptionFileFormat();
            }
        }
    }
}