#include <iostream>
#include "ConsoleView.hpp"
#include "../Controllers/Controller.hpp"

#include "ConsoleView.hpp"
#include <iostream>
#include <limits>

void ConsoleView::Run(Controller& controller) const {
    std::string command;
    std::cout << "welcome to the 3DWorld!"<< std::endl
              <<"Please enter your 3D model file with path:";
    std::string filePath;
    std::cin >> filePath;
    if (!LoadModel(controller, &filePath)) {
            return ;
        }

    while (true) {
        std::cout << "Please enter a command "
                  << "(use 'help' to display available commands): ";
        std::cin >> command;
        if (command == "save") {
            SaveModel(controller, filePath);
            continue;
        } else if (command == "list_faces") {
            ListFaces(controller);
            continue;
        } else if (command == "list_face's_points"){
            ListFace_sPoints(controller);
            continue;
        } else if (command == "add_face") {
            AddFace(controller);
            continue;
        } else if (command == "remove_face") {
            RemoveFace(controller);
            continue;
        } else if (command == "modify_face") {
            ModifyFace(controller);
            continue;
        } else if (command == "list_lines") {
            ListLines(controller);
            continue;
        } else if (command == "list_line's_points"){
            ListLine_sPoints(controller);
            continue;
        } else if (command == "add_line") {
            AddLine(controller);
            continue;
        } else if (command == "remove_line") {
            RemoveLine(controller);
            continue;
        } else if (command == "modify_line") {
            ModifyLine(controller);
            continue;
        } else if (command == "statistics") {
            ShowStatistics(controller);
            continue;
        } else if (command == "help") {
            ShowHelp();
            continue;
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "unknown command: " << command << std::endl;
        }
    }
}

bool ConsoleView::LoadModel(Controller& controller, std::string* path) const {
    auto result = controller.LoadModel(*path);
    if (result == Controller::Result::R_FILE_EXTENSION_ERROR) {
        std::cout << "error: Invalid file extension." << std::endl;
        return false;
    }
    else if (result == Controller::Result::R_FILE_OPEN_ERROR) {
        std::cout << "error: Cannot open file '"
                  << *path << "'." << std::endl;
        return false;
    }
    else if (result == Controller::Result::R_FILE_FORMAT_ERROR) {
        std::cout << "error: File '"
                  << *path << "' has invalid format." << std::endl;
        return false;
    }
    else if (result == Controller::Result::R_IDENTICAL_POINTS) {
        std::cout << "error: File '"
                  << *path << "' contains invalid elements." << std::endl;
        return false;
    }
    std::cout << "Successfully loaded '"
              << *path << "'." << std::endl;
    return true;
}


void ConsoleView::SaveModel(const Controller& controller, std::string defaultPath) const {
    std::cout << "(Enter nothing to use default value '" << defaultPath << "')" << std::endl;
    std::cout << "Save to: ";
    std::string fileName;
    std::cin >> fileName;
    if (fileName.empty()) {
        fileName = defaultPath;
    }
    auto result = controller.SaveModel(fileName);
    if (result == Controller::Result::R_FILE_EXTENSION_ERROR) {
        std::cout << "error: Invalid file extension." << std::endl;
        return;
    }
    else if (result == Controller::Result::R_FILE_OPEN_ERROR) {
        std::cout << "error: Cannot open file '"
                  << fileName << "'." << std::endl;
        return;
    }
    std::cout << "Successfully saved to '"
              << fileName << "'." << std::endl;
}

void ConsoleView::ShowHelp() const {
    std::cout << "可用命令:\n"
              << "  save                - Save the model\n"
              << "  list_faces          - List all faces\n"
              << "  list_face's_points  - List points of the specified face\n"
              << "  add_face            - Add face\n"
              << "  remove_face         - Remove face\n"
              << "  modify_face         - Modify face\n"
              << "  list_lines          - List all lines\n"
              << "  list_line's_points  - List points of the specified line\n"
              << "  add_line            - Add line\n"
              << "  remove_line         - Removw line\n"
              << "  modify_line         - Modify line\n"
              << "  statistics          - Show statistics\n"
              << "  help                - Show available\n"
              << "  exit                - exit the program\n";
}

void ConsoleView::ShowStatistics(const Controller& controller) const {
    auto stat = controller.GetStatistics();
    std::cout << "Statistics:\n";
    
    std::cout << "  Total Point Count:" << "\t"
              << stat.TotalPointCount << std::endl;
    std::cout << "  Total Line Count:" << "\t"
              << stat.TotalLineCount << std::endl;
    std::cout << "  Total Line Length:" << "\t"
              << stat.TotalLineLength << std::endl;
    std::cout << "  Total Face Count:" << "\t"
              << stat.TotalFaceCount << std::endl;
    std::cout << "  Total Face Area:" << "\t"
              << stat.TotalFaceArea << std::endl;
    std::cout << "  Min Box Value:" << "\t"
              << stat.MinBoxVolume << std::endl;
}

void ConsoleView::ListFaces(const Controller& controller) const {
    const auto& faces = controller.GetFaces();
    for (size_t i = 0; i < faces.size(); i++) {
        const auto& face = faces[i];
        std::cout << "Face " << i + 1 << ": ";
        std::cout << *face << std::endl;
        std::cout << "    Area: " << face->GetArea() << std::endl;
    }
}

void ConsoleView::ListFace_sPoints(const Controller& controller) const {
    std::cout << "Select a face to inspect" << std::endl;
    const auto& faces = controller.GetFaces();
    for (size_t i = 0; i < faces.size(); i++) {
        const auto& face = faces[i];
        std::cout << "Face " << i + 1 << ": ";
        std::cout << *face << std::endl;
    }
    std::cout << "Your choose : ";
    int id = 0;
    std::cin >> id;
    std::vector<std::shared_ptr<Point3D>> points;
    auto result = controller.GetFacePointsById(id, &points);
    if (result == Controller::Result::R_ID_OUT_OF_BOUNDS) {
        std::cout << "error: #" << id << " is not a valid face id." << std::endl;
    }
    else {
        std::cout << "Points in face #" << id << ":" << std::endl;
        for (int i = 0; i < 3; i++) {
            std::cout << "  #" << i << points[i]->ToString() << std::endl;
        }
    }
}

void ConsoleView::AddFace(Controller& controller) const {
    double x1;
    double y1;
    double z1;
    double x2;
    double y2;
    double z2;
    double x3;
    double y3;
    double z3;
    std::cout << "Enter 3 Points' coordinates x1 y1 z1 x2 y2 z2 x3 y3 z3 : ";
    std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
    auto result = controller.AddFace(x1, y1, z1, x2, y2, z2, x3, y3, z3);
    if (result == Controller::Result::R_IDENTICAL_POINTS) {
        std::cout << "error: Identical points within element." << std::endl;
    }
    else if (result == Controller::Result::R_IDENTICAL_ELEMENTS) {
        std::cout << "error: Identical elements within model." << std::endl;
    }
    else {
        std::cout << "Successfully created face." << std::endl;
    }
}

void ConsoleView::RemoveFace(Controller& controller) const {
    std::cout << "Select a face to remove" << std::endl;
    const auto& faces = controller.GetFaces();
    for (size_t i = 0; i < faces.size(); i++) {
        const auto& face = faces[i];
        std::cout << "Face " << i + 1 << ": ";
        std::cout << *face << std::endl;
    }
    std::cout << "Your choose : ";
    int id = 0;
    std::cin >> id;
    auto result = controller.RemoveFaceById(id);
    if (result == Controller::Result::R_ID_OUT_OF_BOUNDS) {
        std::cout << "error: #" << id << " is not a valid face id." << std::endl;
    }
    else {
        std::cout << "Successfully removed face #" << id << "." << std::endl;
    }
}

void ConsoleView::ModifyFace(Controller& controller) const {
    std::cout << "Select a face to modify" << std::endl;
    const auto& faces = controller.GetFaces();
    for (size_t i = 0; i < faces.size(); i++) {
        const auto& face = faces[i];
        std::cout << "Face " << i + 1 << ": ";
        std::cout << *face << std::endl;
    }
    std::cout << "Your choice : ";
    int id = 0;
    std::cin >> id;

    std::cout << "Point index [1~3]: ";
    int pointIndex;
    std::cin >> pointIndex;

    std::cout << "Coodinates x y z : ";
    double x;
    double y;
    double z;
    std::cin >> x >> y >> z;

    auto result = controller.ModifyFace(id, pointIndex, x, y, z);
    if (result == Controller::Result::R_ID_OUT_OF_BOUNDS) {
        std::cout << "error: #" << id << " is not a valid face id."<< std::endl;
    }
    else if (result == Controller::Result::R_POINT_INDEX_ERROR) {
        std::cout << "error: Invalid point index '" << pointIndex << "'." << std::endl;
    }
    else {
        std::cout << "Successfully modified face #" << id << "." << std::endl;
    }
}

void ConsoleView::ListLines(const Controller& controller) const {
    const auto& lines = controller.GetLines();
    for (size_t i = 0; i < lines.size(); i++) {
        const auto& line = lines[i];
        std::cout << "Line " << i + 1 << ": ";
        std::cout << *line << std::endl;
        std::cout << "    Length: " << line->GetLength() << std::endl;
    }
}

void ConsoleView::ListLine_sPoints(const Controller& controller) const {
    std::cout << "Select a line to inspect" << std::endl;
    const auto& lines = controller.GetLines();
    for (size_t i = 0; i < lines.size(); i++) {
        const auto& line = lines[i];
        std::cout << "Line " << i + 1 << ": ";
        std::cout << *line << std::endl;
    }
    std::cout << "Your choose : ";
    int id = 0;
    std::cin >> id;
    std::vector<std::shared_ptr<Point3D>> points;
    auto result = controller.GetLinePointsById(id, &points);
    if (result == Controller::Result::R_ID_OUT_OF_BOUNDS) {
        std::cout << "error: #" << id << " is not a valid line id." << std::endl;
    }
    else {
        std::cout << "Points in line #" << id << ":" << std::endl;
        for (int i = 0; i < 3; i++) {
            std::cout << "  #" << i << points[i]->ToString() << std::endl;
        }
    }
}

void ConsoleView::AddLine(Controller& controller) const {
    double x1;
    double y1;
    double z1;
    double x2;
    double y2;
    double z2;
    std::cout << "Enter 2 Points' coordinates x1 y1 z1 x2 y2 z2 : ";
    std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
    auto result = controller.AddLine(x1, y1, z1, x2, y2, z2);
    if (result == Controller::Result::R_IDENTICAL_POINTS) {
        std::cout << "error: Identical points within element." << std::endl;
    }
    else if (result == Controller::Result::R_IDENTICAL_ELEMENTS) {
        std::cout << "error: Identical elements within model." << std::endl;
    }
    else {
        std::cout << "Successfully created line." << std::endl;
    }
}

void ConsoleView::RemoveLine(Controller& controller) const {
    std::cout << "Select a line to remove" << std::endl;
    const auto& lines = controller.GetLines();
    for (size_t i = 0; i < lines.size(); i++) {
        const auto& line = lines[i];
        std::cout << "Line " << i + 1 << ": ";
        std::cout << *line << std::endl;
    }
    std::cout << "Your choose : ";
    int id = 0;
    std::cin >> id;
    auto result = controller.RemoveLineById(id);
    if (result == Controller::Result::R_ID_OUT_OF_BOUNDS) {
        std::cout << "error: #" << id << " is not a valid line id." << std::endl;
    }
    else {
        std::cout << "Successfully removed line #" << id << "." << std::endl;
    }
}

void ConsoleView::ModifyLine(Controller& controller) const {
    std::cout << "Select a line to modify" << std::endl;
    const auto& lines = controller.GetLines();
    for (size_t i = 0; i < lines.size(); i++) {
        const auto& line = lines[i];
        std::cout << "Line" << i + 1 << ": ";
        std::cout << *line << std::endl;
    }
    std::cout << "Your choice : ";
    int id = 0;
    std::cin >> id;

    std::cout << "Point index [1~2]: ";
    int pointIndex;
    std::cin >> pointIndex;

    std::cout << "Coodinates x y z : ";
    double x;
    double y;
    double z;
    std::cin >> x >> y >> z;

    auto result = controller.ModifyLine(id, pointIndex, x, y, z);
    if (result == Controller::Result::R_ID_OUT_OF_BOUNDS) {
        std::cout << "error: #" << id << " is not a valid line id."<< std::endl;
    }
    else if (result == Controller::Result::R_POINT_INDEX_ERROR) {
        std::cout << "error: Invalid point index '" << pointIndex << "'." << std::endl;
    }
    else {
        std::cout << "Successfully modified line #" << id << "." << std::endl;
    }
}