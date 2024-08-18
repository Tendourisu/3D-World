/*******************************************************************************
【文件名】 Controller.cpp
【功能模块和目的】 实现Controller类，提供对模型的操作
Created by 朱昊东 on 2024/7/28
【更改记录】 
    2024/8/17
    - 修改了一些缩进问题
*******************************************************************************/
#include <memory>
#include <string>
#include <vector>
#include "Controller.hpp"
#include "../Exporter&Importer/ObjExporter.hpp"
#include "../Exporter&Importer/ObjImporter.hpp"
#include "../Models/Model.hpp"

/*******************************************************************************
【函数名称】 GetInstance
【函数功能】 获取Controller类的单例对象
【参数】 无
【返回值】 Controller&：Controller类的单例对象
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
Controller& Controller::GetInstance() {
    static Controller s_Instance;
    return s_Instance;
}

/*******************************************************************************
【函数名称】 LoadModel
【函数功能】 加载模型
【参数】 
    - std::string Path（输入参数）：字符串，文件路径
【返回值】 Result：操作结果
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
Controller::Result Controller::LoadModel(std::string Path) {
    ObjImporter importer;
    try {
        importer.Import(Path, m_Model);
    }
    catch (ExceptionFileExtension) {
        return Result::R_FILE_EXTENSION_ERROR;
    }
    catch (ExceptionFileOpen) {
        return Result::R_FILE_OPEN_ERROR;
    }
    catch (ExceptionFileFormat) {
        return Result::R_FILE_FORMAT_ERROR;
    }
    catch (ExceptionIdenticalPoint) {
        return Result::R_IDENTICAL_POINTS;
    }
    return Result::R_OK;
}

/*******************************************************************************
【函数名称】 SaveModel  
【函数功能】 保存模型
【参数】 
    - std::string Path（输入参数）：字符串，文件路径
【返回值】 Result：操作结果
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
Controller::Result Controller::SaveModel(std::string Path) const {
    ObjExporter exporter;
    try {
        exporter.Export(Path, m_Model);
    }
    catch (ExceptionFileExtension) {
        return Result::R_FILE_EXTENSION_ERROR;
    }
    catch (ExceptionFileOpen) {
        return Result::R_FILE_OPEN_ERROR;
    }
    return Result::R_OK;
}

/*******************************************************************************
【函数名称】 GetPoints
【函数功能】 获取点
【参数】 无
【返回值】 std::vector<std::shared_ptr<Line3D>>&：线的智能指针构成的向量
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
const std::vector<std::shared_ptr<Line3D>>& Controller::GetLines() const {
    return m_Model.Lines;
}

/*******************************************************************************
【函数名称】 GetPoints
【函数功能】 获取点
【参数】 无
【返回值】 std::vector<std::shared_ptr<Face3D>>&：面的智能指针构成的向量
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
const std::vector<std::shared_ptr<Face3D>>& Controller::GetFaces() const {
    return m_Model.Faces;
}

/*******************************************************************************
【函数名称】 GwtLinePointsById
【函数功能】 获取指定线的点
【参数】 
    - std::size_t ID（输入参数）：size_t，线的ID
    - std::vector<std::shared_ptr<Point3D>>* pointsPtr（输出参数）：Point3D智能
    指针的动态数组
【返回值】 Result：操作结果
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
Controller::Result Controller::GetLinePointsById(std::size_t ID,
                    std::vector<std::shared_ptr<Point3D>>* PointsPtr) const {
    if (ID == 0 || ID > m_Model.Lines.size()) {
        return Result::R_ID_OUT_OF_BOUNDS;
    }
    *PointsPtr = m_Model.Lines[ID-1]->GetPointsVector();
    return Result::R_OK;
}

/*******************************************************************************
【函数名称】 GwtFacePointsById
【函数功能】 获取指定面的点
【参数】 
    - std::size_t ID（输入参数）：线的ID
    - std::vector<std::shared_ptr<Point3D>>* pointsPtr（输出参数）：Point3D智能
    指针的动态数组
【返回值】 Result：操作结果
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
Controller::Result Controller::GetFacePointsById(std::size_t ID,
    std::vector<std::shared_ptr<Point3D>>* PointsPtr) const {
    if (ID == 0 || ID > m_Model.Faces.size()) {
        return Result::R_ID_OUT_OF_BOUNDS;
    }
    *PointsPtr = m_Model.Faces[ID-1]->GetPointsVector();
    return Result::R_OK;
}

/*******************************************************************************
【函数名称】 RemoveLineById
【函数功能】 删除指定的线
【参数】 
    - std::size_t ID（输入参数）：线的ID
【返回值】 Result：操作结果
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/

Controller::Result Controller::RemoveLineById(std::size_t ID) {
    if (m_Model.RemoveLine(ID - 1)) {
        //m_LineStates.erase(m_LineStates.begin() + ID - 1);
        return Result::R_OK;
    }
    else {
        return Result::R_ID_OUT_OF_BOUNDS;
    }
}

/*******************************************************************************
【函数名称】 RemoveFaceById
【函数功能】 删除指定的面
【参数】 
    - std::size_t id（输入参数）：面的ID
【返回值】 Result：操作结果
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
Controller::Result Controller::RemoveFaceById(std::size_t ID) {
    if (m_Model.RemoveFace(ID - 1)) {
        //m_FaceStates.erase(m_FaceStates.begin() + ID - 1);
        return Result::R_OK;
    }
    else {
        return Result::R_ID_OUT_OF_BOUNDS;
    }
}

/*******************************************************************************
【函数名称】 AddLine
【函数功能】 添加线
【参数】 
    - double X1（输入参数）：double，第一个点的x坐标
    - double Y1（输入参数）：double，第一个点的y坐标
    - double Z1（输入参数）：double，第一个点的z坐标
    - double X2（输入参数）：double，第二个点的x坐标
    - double Y2（输入参数）：double，第二个点的y坐标
    - double Z2（输入参数）：double，第二个点的z坐标
【返回值】 Result：操作结果
Created by 朱昊东 on 2024/7/28
【更改记录】 
    2024/8/17
    - 修改了一些缩进问题
*******************************************************************************/

Controller::Result Controller::AddLine(
    double X1, double Y1, double Z1,
    double X2, double Y2, double Z2) {
    double firstCoords[] = { X1, Y1, Z1 };
    double secondCoords[] = { X2, Y2, Z2 };
    Point3D first(firstCoords);
    Point3D second(secondCoords);
    try {
        m_Model.AddLine(first, second);
    }
    catch (ExceptionIdenticalPoint) {
        return Result::R_IDENTICAL_POINTS;
    }
    catch (ExceptionIdenticalElement) {
        return Result::R_IDENTICAL_ELEMENTS;
    }
    //m_LineStates.push_back(State::S_CREATED);
    return Result::R_OK;
}

/*******************************************************************************
【函数名称】 AddFace
【函数功能】 添加面
【参数】 
    - double X1（输入参数）：double，第一个点的x坐标
    - double Y1（输入参数）：double，第一个点的y坐标
    - double Z1（输入参数）：double，第一个点的z坐标
    - double X2（输入参数）：double，第二个点的x坐标
    - double Y2（输入参数）：double，第二个点的y坐标
    - double Z2（输入参数）：double，第二个点的z坐标
    - double X3（输入参数）：double，第三个点的x坐标
    - double Y3（输入参数）：double，第三个点的y坐标
    - double Z3（输入参数）：double，第三个点的z坐标
【返回值】 Result：操作结果
Created by 朱昊东 on 2024/7/28
【更改记录】 
    2024/8/17
    - 修改了一些缩进问题
*******************************************************************************/

Controller::Result Controller::AddFace(
    double X1, double Y1, double Z1, 
    double X2, double Y2, double Z2,
    double X3, double Y3, double Z3) {
    double firstCoords[] = { X1, Y1, Z1 };
    double secondCoords[] = { X2, Y2, Z2 };
    double thirdCoords[] = { X3, Y3, Z3 };
    Point3D first(firstCoords);
    Point3D second(secondCoords);
    Point3D third(thirdCoords);
    try {
        m_Model.AddFace(first, second, third);
    }
    catch (ExceptionIdenticalPoint) {
        return Result::R_IDENTICAL_POINTS;
    }
    catch (ExceptionIdenticalElement) {
        return Result::R_IDENTICAL_ELEMENTS;
    }
    //m_FaceStates.push_back(State::S_CREATED);
    return Result::R_OK;
}

/*******************************************************************************
【函数名称】 ModifyLine
【函数功能】 修改线
【参数】 
    - std::size_t ID（输入参数）：size_t，线的ID
    - int PointIndex（输入参数）：int，点的索引
    - double X（输入参数）：double，点的x坐标
    - double Y（输入参数）：double，点的y坐标
    - double Z（输入参数）：double，点的z坐标
【返回值】 Result：操作结果
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
Controller::Result Controller::ModifyLine(std::size_t ID, int PointIndex,
                                          double X, double Y, double Z) {
    // check here for invalid access
    // as we cannot distinguish which index overflows
    if (ID == 0 || ID > m_Model.Lines.size()) {
        return Result::R_ID_OUT_OF_BOUNDS;
    }
    double Coords[] = { X, Y, Z };
    try {
        m_Model.ModifyLine(ID - 1, PointIndex - 1, Point3D(Coords));
    }
    catch (ExceptionIndexOutOfBounds) {
        return Result::R_POINT_INDEX_ERROR;
    }
    //m_LineStates[ID - 1] = State::S_MODIFIED;
    return Result::R_OK;
}

/*******************************************************************************
【函数名称】 ModifyFace
【函数功能】 修改面
【参数】 
    - std::size_t ID（输入参数）：size_t，面的ID
    - int PointIndex（输入参数）：int，点的索引
    - double X（输入参数）：double，点的x坐标
    - double Y（输入参数）：double，点的y坐标
    - double Z（输入参数）：double，点的z坐标
【返回值】 Result：操作结果
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
Controller::Result Controller::ModifyFace(std::size_t ID, int PointIndex,
                                          double X, double Y, double Z) {
    // same as Controller::ModifyLine
    if (ID == 0 || ID > m_Model.Faces.size()) {
        return Result::R_ID_OUT_OF_BOUNDS;
    }
    double Coords[] = { X, Y, Z };
    try {
        m_Model.ModifyFace(ID - 1, PointIndex - 1, Point3D(Coords));
    }
    catch (ExceptionIndexOutOfBounds) {
        return Result::R_POINT_INDEX_ERROR;
    }
    //m_FaceStates[ID - 1] = State::S_MODIFIED;
    return Result::R_OK;
}

/*******************************************************************************
【函数名称】 GetStatistics
【函数功能】 获取统计信息
【参数】 无
【返回值】 Statistics：统计信息
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
Controller::Statistics Controller::GetStatistics() const {
    Statistics Stats {
        .TotalPointCount = m_Model.Lines.size() * 2 + m_Model.Faces.size() * 3,
        .TotalLineCount = m_Model.Lines.size(),
        .TotalLineLength = 0,
        .TotalFaceCount = m_Model.Faces.size(),
        .TotalFaceArea = 0,
        .MinBoxVolume = m_Model.GetMinBoxVolume()
    };
    for (auto line: m_Model.Lines) {
        Stats.TotalLineLength += line->GetLength();
    }
    for (auto face: m_Model.Faces) {
        Stats.TotalFaceArea += face->GetArea();
    }
    return Stats;
}