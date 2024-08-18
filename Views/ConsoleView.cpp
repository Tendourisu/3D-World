/*******************************************************************************
【文件名】 ConsoleView.cpp
【功能模块和目的】 控制台视图类，通过console实现controller与用户的交互
 Created by 朱昊东 on 2024/7/29
【更改记录】 
    2024/8/15
    - 修改了Run方法，使得用户可以在文件加载失败时重新输入文件路径
    2024/8/17
    - 修改了一些缩进问题
*******************************************************************************/
#include <iostream>
#include "ConsoleView.hpp"
#include "../Controllers/Controller.hpp"

#include "ConsoleView.hpp"
#include <iostream>
#include <limits>

/*******************************************************************************
【函数名称】 Run
【函数功能】 运行方法，实现controller与用户的交互
【参数】 
    - Controller& Controller（输入参数）：Controller对象，控制器
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 
    2024/8/15
    - 修改了Run方法，使得用户可以在文件加载失败时重新输入文件路径
    2024/8/17
    - 修改了一些缩进问题
*******************************************************************************/
void ConsoleView::Run(Controller& Controller) const {
    std::string Command;
    std::cout << "welcome to the 3DWorld!"<< std::endl;
              
    std::string FilePath;
    while (true) {
        std::cout <<"Please enter your 3D model file with Path:";
        std::cin >> FilePath;
        if (LoadModel(Controller, &FilePath)) {
            break;
        } else {
            std::cout << "Fail to load the file, please try again" << std::endl;
        }
    }

    while (true) {
        std::cout
            << "Please enter a Command "
            << "(use 'help' to display available commands): ";
        std::cin >> Command;
        if (Command == "1") {
            SaveModel(Controller, FilePath);
            continue;
        } else if (Command == "2") {
            ListFaces(Controller);
            continue;
        } else if (Command == "3") {
            ListFace_sPoints(Controller);
            continue;
        } else if (Command == "4") {
            AddFace(Controller);
            continue;
        } else if (Command == "5") {
            RemoveFace(Controller);
            continue;
        } else if (Command == "6") {
            ModifyFace(Controller);
            continue;
        } else if (Command == "7") {
            ListLines(Controller);
            continue;
        } else if (Command == "8") {
            ListLine_sPoints(Controller);
            continue;
        } else if (Command == "9") {
            AddLine(Controller);
            continue;
        } else if (Command == "10") {
            RemoveLine(Controller);
            continue;
        } else if (Command == "11") {
            ModifyLine(Controller);
            continue;
        } else if (Command == "12") {
            ShowStatistics(Controller);
            continue;
        } else if (Command == "13") {
            ShowHelp();
            continue;
        } else if (Command == "help") {
            ShowHelp();
            continue;
        } else if (Command == "14") {
            break;
        } else {
            std::cout << "unknown Command: " << Command << std::endl;
        }
    }
}

/*******************************************************************************
【函数名称】 LoadModel
【函数功能】 加载模型
【参数】 
    - Controller& Controller（输入参数）：Controller对象，控制器
    - std::string* Path（输入参数）：字符串指针，文件路径
【返回值】 bool ：是否成功加载
Created by 朱昊东 on 2024/7/29
【更改记录】 
    2024/8/17
    - 修改了一些缩进问题
*******************************************************************************/
bool ConsoleView::LoadModel(Controller& Controller, std::string* Path) const {
    auto Result = Controller.LoadModel(*Path);
    if (Result == Controller::Result::R_FILE_EXTENSION_ERROR) {
        std::cout << "error: Invalid file extension." << std::endl;
        return false;
    }
    else if (Result == Controller::Result::R_FILE_OPEN_ERROR) {
        std::cout 
            << "error: Cannot open file '"
            << *Path << "'." << std::endl;
        return false;
    }
    else if (Result == Controller::Result::R_FILE_FORMAT_ERROR) {
        std::cout 
            << "error: File '"
            << *Path << "' has invalid format." << std::endl;
        return false;
    }
    else if (Result == Controller::Result::R_IDENTICAL_POINTS) {
        std::cout 
            << "error: File '"
            << *Path << "' contains invalid elements." << std::endl;
        return false;
    }
    std::cout 
        << "Successfully loaded '"
        << *Path << "'." << std::endl;
    return true;
}

/*******************************************************************************
【函数名称】 SaveModel
【函数功能】 保存模型
【参数】 
    - const Controller& Controller（输入参数）：Controller对象，控制器
    - std::string DefaultPath（输入参数）：字符串，默认路径
【返回值】 bool ：是否成功保存
Created by 朱昊东 on 2024/7/29
【更改记录】 
    2024/8/17
    - 修改了一些缩进问题
*******************************************************************************/
void ConsoleView::SaveModel(const Controller& Controller, std::string DefaultPath) const {
    std::cout << "(Enter nothing to use default value '" << DefaultPath << "')" << std::endl;
    std::cout << "Save to: ";
    std::string FileName;
    std::cin >> FileName;
    if (FileName.empty()) {
        FileName = DefaultPath;
    }
    auto Result = Controller.SaveModel(FileName);
    if (Result == Controller::Result::R_FILE_EXTENSION_ERROR) {
        std::cout << "error: Invalid file extension." << std::endl;
        return;
    }
    else if (Result == Controller::Result::R_FILE_OPEN_ERROR) {
        std::cout
            << "error: Cannot open file '"
            << FileName << "'." << std::endl;
        return;
    }
    std::cout
        << "Successfully saved to '"
        << FileName << "'." << std::endl;
}

/*******************************************************************************
【函数名称】 ShowHelp
【函数功能】 显示帮助信息
【参数】 无
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 
    2024/8/17
    - 修改了一些缩进问题
*******************************************************************************/
void ConsoleView::ShowHelp() const {
    std::cout 
        << "可用命令:\n"
        << "1  save                - Save the model\n"
        << "2  list_faces          - List all faces\n"
        << "3  list_face's_points  - List points of the specified face\n"
        << "4  add_face            - Add face\n"
        << "5  remove_face         - Remove face\n"
        << "6  modify_face         - Modify face\n"
        << "7  list_lines          - List all lines\n"
        << "8  list_line's_points  - List points of the specified line\n"
        << "9  add_line            - Add line\n"
        << "10 remove_line         - Removw line\n"
        << "11 modify_line         - Modify line\n"
        << "12 statistics          - Show statistics\n"
        << "13 help                - Show available commands\n"
        << "14 exit                - exit the program\n";
}

/*******************************************************************************
【函数名称】 ShowStatistics
【函数功能】 显示统计信息
【参数】 
    - const Controller& Controller（输入参数）：Controller对象，控制器
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 
    2024/8/17
    - 修改了一些缩进问题
*******************************************************************************/
void ConsoleView::ShowStatistics(const Controller& Controller) const {
    auto stat = Controller.GetStatistics();
    std::cout << "Statistics:\n";
    
    std::cout
        << "  Total Point Count:" << "\t"
        << stat.TotalPointCount << std::endl;
    std::cout 
        << "  Total Line Count:" << "\t"
        << stat.TotalLineCount << std::endl;
    std::cout
        << "  Total Line Length:" << "\t"
        << stat.TotalLineLength << std::endl;
    std::cout 
        << "  Total Face Count:" << "\t"
        << stat.TotalFaceCount << std::endl;
    std::cout
        << "  Total Face Area:" << "\t"
        << stat.TotalFaceArea << std::endl;
    std::cout
        << "  Min Box Value:" << "\t"
        << stat.MinBoxVolume << std::endl;
}

/*******************************************************************************
【函数名称】 ListFaces
【函数功能】 列出面
【参数】 
    - const Controller& Controller（输入参数）：Controller对象，控制器
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
void ConsoleView::ListFaces(const Controller& Controller) const {
    const auto& Faces = Controller.GetFaces();
    for (size_t i = 0; i < Faces.size(); i++) {
        const auto& Face = Faces[i];
        std::cout << "Face " << i + 1 << ": ";
        std::cout << *Face << std::endl;
        std::cout << "    Area: " << Face->GetArea() << std::endl;
    }
}

/*******************************************************************************
【函数名称】 ListFace_sPoints
【函数功能】 列出面的点
【参数】 
    - const Controller& Controller（输入参数）：Controller对象，控制器
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
void ConsoleView::ListFace_sPoints(const Controller& Controller) const {
    std::cout << "Select a face to inspect" << std::endl;
    const auto& Faces = Controller.GetFaces();
    for (size_t i = 0; i < Faces.size(); i++) {
        const auto& Face = Faces[i];
        std::cout << "Face " << i + 1 << ": ";
        std::cout << *Face << std::endl;
    }
    std::cout << "Your choose : ";
    int ID = 0;
    std::cin >> ID;
    std::vector<std::shared_ptr<Point3D>> Points;
    auto Result = Controller.GetFacePointsById(ID, &Points);
    if (Result == Controller::Result::R_ID_OUT_OF_BOUNDS) {
        std::cout << "error: #" << ID << " is not a valid face ID." << std::endl;
    }
    else {
        std::cout << "Points in face #" << ID << ":" << std::endl;
        for (int i = 0; i < 3; i++) {
            std::cout << "  #" << i << Points[i]->ToString() << std::endl;
        }
    }
}

/*******************************************************************************
【函数名称】 AddFace
【函数功能】 添加面
【参数】 
    - Controller& Controller（输入参数）：Controller对象，控制器
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
void ConsoleView::AddFace(Controller& Controller) const {
    double X1;
    double Y1;
    double Z1;
    double X2;
    double Y2;
    double Z2;
    double X3;
    double Y3;
    double Z3;
    std::cout << "Enter 3 Points' coordinates X1 Y1 Z1 X2 Y2 Z2 x3 y3 z3 : ";
    std::cin >> X1 >> Y1 >> Z1 >> X2 >> Y2 >> Z2 >> X3 >> Y3 >> Z3;
    auto Result = Controller.AddFace(X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3);
    if (Result == Controller::Result::R_IDENTICAL_POINTS) {
        std::cout << "error: Identical points within element." << std::endl;
    }
    else if (Result == Controller::Result::R_IDENTICAL_ELEMENTS) {
        std::cout << "error: Identical elements within model." << std::endl;
    }
    else {
        std::cout << "Successfully created face." << std::endl;
    }
}

/*******************************************************************************
【函数名称】 RemoveFace
【函数功能】 移除面
【参数】 
    - Controller& Controller（输入参数）：Controller对象，控制器
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
void ConsoleView::RemoveFace(Controller& Controller) const {
    std::cout << "Select a face to remove" << std::endl;
    const auto& Faces = Controller.GetFaces();
    for (size_t i = 0; i < Faces.size(); i++) {
        const auto& Face = Faces[i];
        std::cout << "Face " << i + 1 << ": ";
        std::cout << *Face << std::endl;
    }
    std::cout << "Your choose : ";
    int ID = 0;
    std::cin >> ID;
    auto Result = Controller.RemoveFaceById(ID);
    if (Result == Controller::Result::R_ID_OUT_OF_BOUNDS) {
        std::cout << "error: #" << ID << " is not a valid face ID." << std::endl;
    }
    else {
        std::cout << "Successfully removed face #" << ID << "." << std::endl;
    }
}

/*******************************************************************************
【函数名称】 ModifyFace
【函数功能】 修改面
【参数】 
    - Controller& Controller（输入参数）：Controller对象，控制器
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
void ConsoleView::ModifyFace(Controller& Controller) const {
    std::cout << "Select a face to modify" << std::endl;
    const auto& Faces = Controller.GetFaces();
    for (size_t i = 0; i < Faces.size(); i++) {
        const auto& Face = Faces[i];
        std::cout << "Face " << i + 1 << ": ";
        std::cout << *Face << std::endl;
    }
    std::cout << "Your choice : ";
    int ID = 0;
    std::cin >> ID;

    std::cout << "Point index [1~3]: ";
    int PointIndex;
    std::cin >> PointIndex;

    std::cout << "Coodinates X Y Z : ";
    double X;
    double Y;
    double Z;
    std::cin >> X >> Y >> Z;
    auto Result = Controller.ModifyFace(ID, PointIndex, X, Y, Z);
    if (Result == Controller::Result::R_ID_OUT_OF_BOUNDS) {
        std::cout << "error: #" << ID << " is not a valid face ID."<< std::endl;
    }
    else if (Result == Controller::Result::R_POINT_INDEX_ERROR) {
        std::cout << "error: Invalid point index '" << PointIndex << "'." << std::endl;
    }
    else {
        std::cout << "Successfully modified face #" << ID << "." << std::endl;
    }
}

/*******************************************************************************
【函数名称】 ListLines
【函数功能】 列出线
【参数】 
    - Controller& Controller（输入参数）：Controller对象，控制器
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
void ConsoleView::ListLines(const Controller& Controller) const {
    const auto& Lines = Controller.GetLines();
    for (size_t i = 0; i < Lines.size(); i++) {
        const auto& Line = Lines[i];
        std::cout << "Line " << i + 1 << ": ";
        std::cout << *Line << std::endl;
        std::cout << "    Length: " << Line->GetLength() << std::endl;
    }
}

/*******************************************************************************
【函数名称】 ListLine_sPoints
【函数功能】 列出线的点
【参数】 
    - Controller& Controller（输入参数）：Controller对象，控制器
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
void ConsoleView::ListLine_sPoints(const Controller& Controller) const {
    std::cout << "Select a Line to inspect" << std::endl;
    const auto& Lines = Controller.GetLines();
    for (size_t i = 0; i < Lines.size(); i++) {
        const auto& Line = Lines[i];
        std::cout << "Line " << i + 1 << ": ";
        std::cout << *Line << std::endl;
    }
    std::cout << "Your choose : ";
    int ID = 0;
    std::cin >> ID;
    std::vector<std::shared_ptr<Point3D>> Points;
    auto Result = Controller.GetLinePointsById(ID, &Points);
    if (Result == Controller::Result::R_ID_OUT_OF_BOUNDS) {
        std::cout << "error: #" << ID << " is not a valid Line ID." << std::endl;
    }
    else {
        std::cout << "Points in Line #" << ID << ":" << std::endl;
        for (int i = 0; i < 3; i++) {
            std::cout << "  #" << i << Points[i]->ToString() << std::endl;
        }
    }
}

/*******************************************************************************
【函数名称】 AddLine
【函数功能】 添加线
【参数】 
    - Controller& controller（输入参数）：Controller对象，控制器
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
void ConsoleView::AddLine(Controller& Controller) const {
    double X1;
    double Y1;
    double Z1;
    double X2;
    double Y2;
    double Z2;
    std::cout << "Enter 2 Points' coordinates X1 Y1 Z1 X2 Y2 Z2 : ";
    std::cin >> X1 >> Y1 >> Z1 >> X2 >> Y2 >> Z2;
    auto Result = Controller.AddLine(X1, Y1, Z1, X2, Y2, Z2);
    if (Result == Controller::Result::R_IDENTICAL_POINTS) {
        std::cout << "error: Identical points within element." << std::endl;
    }
    else if (Result == Controller::Result::R_IDENTICAL_ELEMENTS) {
        std::cout << "error: Identical elements within model." << std::endl;
    }
    else {
        std::cout << "Successfully created Line." << std::endl;
    }
}

/*******************************************************************************
【函数名称】 RemoveLine
【函数功能】 移除线
【参数】 
    - Controller& Controller（输入参数）：Controller对象，控制器
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
void ConsoleView::RemoveLine(Controller& Controller) const {
    std::cout << "Select a Line to remove" << std::endl;
    const auto& Lines = Controller.GetLines();
    for (size_t i = 0; i < Lines.size(); i++) {
        const auto& Line = Lines[i];
        std::cout << "Line " << i + 1 << ": ";
        std::cout << *Line << std::endl;
    }
    std::cout << "Your choose : ";
    int ID = 0;
    std::cin >> ID;
    auto Result = Controller.RemoveLineById(ID);
    if (Result == Controller::Result::R_ID_OUT_OF_BOUNDS) {
        std::cout << "error: #" << ID << " is not a valid Line ID." << std::endl;
    }
    else {
        std::cout << "Successfully removed Line #" << ID << "." << std::endl;
    }
}

/*******************************************************************************
【函数名称】 ModifyLine
【函数功能】 修改线
【参数】 
    - Controller& Controller（输入参数）：Controller对象，控制器
【返回值】 无
Created by 朱昊东 on 2024/7/29
【更改记录】 无
*******************************************************************************/
void ConsoleView::ModifyLine(Controller& Controller) const {
    std::cout << "Select a Line to modify" << std::endl;
    const auto& Lines = Controller.GetLines();
    for (size_t i = 0; i < Lines.size(); i++) {
        const auto& Line = Lines[i];
        std::cout << "Line" << i + 1 << ": ";
        std::cout << *Line << std::endl;
    }
    std::cout << "Your choice : ";
    int ID = 0;
    std::cin >> ID;

    std::cout << "Point index [1~2]: ";
    int PointIndex;
    std::cin >> PointIndex;

    std::cout << "Coodinates X Y Z : ";
    double X;
    double Y;
    double Z;
    std::cin >> X >> Y >> Z;

    auto Result = Controller.ModifyLine(ID, PointIndex, X, Y, Z);
    if (Result == Controller::Result::R_ID_OUT_OF_BOUNDS) {
        std::cout << "error: #" << ID << " is not a valid Line ID."<< std::endl;
    }
    else if (Result == Controller::Result::R_POINT_INDEX_ERROR) {
        std::cout << "error: Invalid point index '" << PointIndex << "'." << std::endl;
    }
    else {
        std::cout << "Successfully modified Line #" << ID << "." << std::endl;
    }
}