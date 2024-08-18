/*******************************************************************************
【文件名】 ObjImporter.hpp
【功能模块和目的】 实现ObjImporter类，用于导入.obj文件
 Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
#ifndef OBJ_IMPORTER_HPP
#define OBJ_IMPORTER_HPP

#include <fstream>
#include <string>
#include "AbstractImporter.hpp"
#include "../Models/Model.hpp"

/*******************************************************************************
【类名】 ObjImporter
【功能】 ObjImporter类，用于导入.obj文件
【接口说明】
    - bool CheckExtension(std::string Path) const override
        检查扩展名为.obj
    - void Load(std::ifstream& File, Model3D& Model) const override
        加载模型
 Created by 朱昊东 on 2024/7/27
   
【更改记录】 无
*******************************************************************************/
class ObjImporter: public AbstractImporter {
    protected:
        //检查扩展名
        bool CheckExtension(std::string Path) const override;
        //加载模型
        void Load(std::ifstream& File, Model3D& Model) const override;
};

#endif // OBJ_IMPORTER_HPP