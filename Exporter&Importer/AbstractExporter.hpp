/*******************************************************************************
【文件名】 AbstractExporter.hpp
【功能模块和目的】 定义抽象类AbstractExporter，提供导出方法Export，并指定虚函数
检查扩展名和保存模型
 Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
#ifndef ABSTRACT_EXPORTER_HPP
#define ABSTRACT_EXPORTER_HPP

#include <fstream>
#include <string>
#include "../Models/Model.hpp"

using Line3D = Line<3>;
using Face3D = Face<3>;
using Model3D = Model<3>;
using Point3D = Point<3>;

/*******************************************************************************
【类名】 AbstractExporter
【功能】 定义抽象类AbstractExporter，提供导出方法Export，并指定虚函数检查扩展名和
保存模型
【接口说明】
    - void Export(std::string path, const Model3D& model) const
        导出模型
    - virtual bool CheckExtension(std::string path) const
        检查扩展名
    - virtual void Save(std::ofstream& file, const Model3D& model) const
        保存模型
   
【更改记录】 无
*******************************************************************************/
class AbstractExporter {
    public:
        //导出model到path
        void Export(std::string path, const Model3D& model) const;
    
    protected:
        //检查扩展名
        virtual bool CheckExtension(std::string path) const = 0;
        //保存模型
        virtual void Save(std::ofstream& file, const Model3D& model) const = 0;
};

#endif // ABSTRACT_EXPORTER_HPP