#ifndef OBJ_EXPORTER_HPP
#define OBJ_EXPORTER_HPP

#include <string>
#include "AbstractExporter.hpp"
#include "../Models/Model.hpp"

class ObjExporter: public AbstractExporter {
    protected:
        bool CheckExtension(std::string path) const override;
        void Save(std::ofstream& file, const Model3D& model) const override;
};

#endif // OBJ_EXPORTER_HPP