#include <fstream>
#include <filesystem>
#include <string>
#include "ObjExporter.hpp"
#include "../Models/Model.hpp"

bool ObjExporter::CheckExtension(std::string path) const {
    const std::string extension = ".obj";
    if (path.length() >= extension.length()) {
        return (0 == path.compare(path.length() - extension.length(), extension.length(), extension));
    } else {
        return false;
    }
}

void ObjExporter::Save(std::ofstream& file, const Model3D& model) const {
    file << "g " << model.Name << std::endl;
    for (auto point: model.CollectPoints()) {
        file << "v ";
        for (int i = 0; i < 3; i++) {
            file << " " << point->GetCoordinate(i); 
        }
        file << std::endl;
    }

    std::vector<std::shared_ptr<Point<3>>> points = model.CollectPoints();
    auto findPointIndex = [&points](const std::shared_ptr<Point<3>> point) -> int {
        auto it = std::find(points.begin(), points.end(), point);
        if (it != points.end()) {
            return std::distance(points.begin(), it);
        }
        return -1; // 如果没有找到，返回 -1
    };

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
