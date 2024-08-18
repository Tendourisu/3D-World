/*******************************************************************************
【文件名】 Controller.hpp
【功能模块和目的】 实现Controller类，提供对模型的操作
 Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <memory>
#include <string>
#include <vector>
#include "../Models/Line.hpp"
#include "../Models/Face.hpp"
#include "../Models/Model.hpp"
#include "../Models/Point.hpp"

using Line3D = Line<3>;
using Face3D = Face<3>;
using Model3D = Model<3>;
using Point3D = Point<3>;

/*******************************************************************************
【类名】 Controller
【功能】 Controller类，提供对模型的操作
【接口说明】
    - static Controller& GetInstance()
        获取Controller实例（单例模式）
    - Result LoadModel(std::string Path)
        加载模型
    - Result SaveModel(std::string Path) const
        保存模型
    - const std::vector<std::shared_ptr<Line3D>>& GetLines() const
        获取线集合
    - const std::vector<std::shared_ptr<Face3D>>& GetFaces() const
        获取面集合
    - Result GetLinePointsById(std::size_t ID,
                        std::vector<std::shared_ptr<Point3D>>* PointsPtr) const
        获取线的点集合
    - Result GetFacePointsById(std::size_t ID,
                        std::vector<std::shared_ptr<Point3D>>* PointsPtr) const
        获取面的点集合
    - Result RemoveLineById(std::size_t ID)
        移除线
    - Result RemoveFaceById(std::size_t ID)
        移除面
    - Result AddLine(
        double X1, double Y1, double Z1,
        double X2, double Y2, double Z2)
        添加线
    - Result AddFace(
        double X1, double Y1, double Z1, 
        double X2, double Y2, double Z2,
        double X3, double Y3, double Z3)
        添加面
    - Result ModifyLine(std::size_t ID, int PointIndex,
        double X, double Y, double Z)
        修改线
    - Result ModifyFace(std::size_t ID, int PointIndex,
        double X, double Y, double Z)
        修改面
    - Statistics GetStatistics() const
        获取统计信息
 Created by 朱昊东 on 2024/7/27
【更改记录】 
        2024/8/17
        - 修改了一些缩进问题
*******************************************************************************/
class Controller {
    public:
        static Controller& GetInstance();//单例模式
        Controller(const Controller& Other) = delete;//不允许拷贝构造
        Controller& operator=(const Controller& Other) = delete;//不允许拷贝赋值

        /***********************************************************************
        【类名】 Result
        【功能】 枚举类，表示操作结果
        【接口说明】
            - R_OK
                操作成功
            - R_FILE_EXTENSION_ERROR
                文件扩展名错误
            - R_FILE_OPEN_ERROR
                文件打开错误
            - R_FILE_FORMAT_ERROR
                文件格式错误
            - R_ID_OUT_OF_BOUNDS
                ID超出范围
            - R_IDENTICAL_POINTS
                点重复
            - R_IDENTICAL_ELEMENTS
                元素重复
            - R_POINT_INDEX_ERROR
                点索引错误
        Created by 朱昊东 on 2024/7/27
        【更改记录】 无
        ***********************************************************************/
        enum class Result {
            R_OK,
            R_FILE_EXTENSION_ERROR,
            R_FILE_OPEN_ERROR,
            R_FILE_FORMAT_ERROR,
            R_ID_OUT_OF_BOUNDS,
            R_IDENTICAL_POINTS,
            R_IDENTICAL_ELEMENTS,
            R_POINT_INDEX_ERROR,
        };

        /***********************************************************************
        【结构体名】 Statistics
        【功能】 结构体，表示统计信息
        【接口说明】
            - std::size_t TotalPointCount
                总点数
            - std::size_t TotalLineCount
                总线数
            - double TotalLineLength
                总线长
            - std::size_t TotalFaceCount
                总面数
            - double TotalFaceArea
                总面积
            - double MinBoxVolume
                最小包围盒体积
        Created by 朱昊东 on 2024/7/27
        【更改记录】 无
        ***********************************************************************/
        struct Statistics {
            std::size_t TotalPointCount;
            std::size_t TotalLineCount;
            double TotalLineLength;
            std::size_t TotalFaceCount;
            double TotalFaceArea;
            double MinBoxVolume;
        };
        //加载模型
        Result LoadModel(std::string Path);
        //保存模型
        Result SaveModel(std::string Path) const;
        //获取线集合
        const std::vector<std::shared_ptr<Line3D>>& GetLines() const;
        //获取面集合
        const std::vector<std::shared_ptr<Face3D>>& GetFaces() const;
        //获取指定线的点集合
        Result GetLinePointsById(std::size_t ID,
                    std::vector<std::shared_ptr<Point3D>>* PointsPtr) const;
        //获取指定面的点集合
        Result GetFacePointsById(std::size_t ID,
                    std::vector<std::shared_ptr<Point3D>>* PointsPtr) const;
        //移除指定线
        Result RemoveLineById(std::size_t ID);
        //移除指定面
        Result RemoveFaceById(std::size_t ID);
        //添加线
        Result AddLine(
            double X1, double Y1, double Z1, 
            double X2, double Y2, double Z2);
        //添加面
        Result AddFace(
            double X1, double Y1, double Z1, 
            double X2, double Y2, double Z2,
            double X3, double Y3, double Z3);
        //修改线
        Result ModifyLine(std::size_t ID, int PointIndex,
            double X, double Y, double Z);
        //修改面
        Result ModifyFace(std::size_t ID, int PointIndex, 
            double X, double Y, double Z);
        //获取统计信息
        Statistics GetStatistics() const;
    private:
        //构造函数
        Controller() = default;
        Model3D m_Model;
};

#endif // CONTROLLER_HPP