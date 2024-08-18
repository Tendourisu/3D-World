/*******************************************************************************
【文件名】 AbstractImporter.hpp
【功能模块和目的】 定义抽象类AbstractImporter，提供导入方法Import，并指定虚函数 
检查扩展名和加载模型
 Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
#ifndef ABSTRACT_IMPORTER_HPP
#define ABSTRACT_IMPORTER_HPP

#include <fstream>
#include <string>
#include "../Models/Model.hpp"

using Line3D = Line<3>;
using Face3D = Face<3>;
using Model3D = Model<3>;
using Point3D = Point<3>;

/*******************************************************************************
【类名】 AbstractImporter
【功能】 定义抽象类AbstractImporter，提供导入方法Import，并指定虚函数检查扩展名和
加载模型
【接口说明】
    - void Import(std::string Path, Model3D& Model) const
        导入模型
    - virtual bool CheckExtension(std::string Path) const
        检查扩展名
    - virtual void Load(std::ifstream& File, Model3D& Model) const
        加载模型
 Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
class AbstractImporter {
    public:
        void Import(std::string Path, Model3D& Model) const;

    protected:
        //检查扩展名
        virtual bool CheckExtension(std::string Path) const = 0;
        //加载模型
        virtual void Load(std::ifstream& File, Model3D& Model) const = 0;
};

#endif // ABSTRACT_IMPORTER_HPP