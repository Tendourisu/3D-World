#ifndef OBJ_IMPORTER_HPP
#define OBJ_IMPORTER_HPP

#include <fstream>
#include <string>
#include "AbstractImporter.hpp"
#include "../Models/Model.hpp"

class ObjImporter: public AbstractImporter {
    protected:
        bool CheckExtension(std::string path) const override;
        void Load(std::ifstream& file, Model3D& model) const override;
};

#endif // OBJ_IMPORTER_HPP