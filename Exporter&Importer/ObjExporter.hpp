/*******************************************************************************
【文件名】 ObjExporter.hpp
【功能模块和目的】 定义ObjExporter类，用于导出.obj文件，
 Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
#ifndef OBJ_EXPORTER_HPP
#define OBJ_EXPORTER_HPP

#include <string>
#include "AbstractExporter.hpp"
#include "../Models/Model.hpp"

/*******************************************************************************
【类名】 ObjExporter
【功能】 ObjExporter类，用于导出模型到.obj文件
【接口说明】
    - bool CheckExtension(std::string Path) const override
        检查扩展名为.obj
    - void Save(std::ofstream& File, const Model3D& Model) const override
        保存模型
 Created by 朱昊东 on 2024/7/27
   
【更改记录】 无
*******************************************************************************/
class ObjExporter: public AbstractExporter {
    protected:
        //检查扩展名
        bool CheckExtension(std::string Path) const override;
        //保存模型s
        void Save(std::ofstream& File, const Model3D& Model) const override;
};

#endif // OBJ_EXPORTER_HPP