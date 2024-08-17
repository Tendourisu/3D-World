/*******************************************************************************
【文件名】 Model.hpp
【功能模块和目的】 定义Model类模板，该类含有一个Line类对象的动态数组和一个Face类
对象的动态数组，提供了添加、修改、删除、清空、获取最小包围盒体积，及获取所有Point类
对象的动态数组构成的的方法
 Created by 朱昊东 on 2024/7/26
【更改记录】 无
*******************************************************************************/
#ifndef MODEL_HPP
#define MODEL_HPP

#include <algorithm>
#include <memory>
#include <limits>
#include <string>
#include <vector>
#include "Face.hpp"
#include "Line.hpp"
#include "Point.hpp"
#include "../Errors.hpp"

/*******************************************************************************
【类名】 Model
【功能】 Model类模板含有一个Line类对象的动态数组和一个Face类对象的动态数组，提供了
获取所有Point类对象构成的动态数组、添加、修改、删除、清空、获取最小包围盒体积等方法
【接口说明】
    - Model(std::string name = "")
        构造函数，传入名称，默认为空
    - ~Model()
        析构函数(默认)
    - void SetName(const std::string& name)
        设置名称
    - std::vector<std::shared_ptr<Point<N>>> CollectPoints() const
        获取所有Point对象的动态数组
    - void AddLine(
        const Point<N>& first,
        const Point<N>& second
    )
        添加线
    - void AddFace(
        const Point<N>& first,
        const Point<N>& second,
        const Point<N>& third
    )
        添加面  
    - void AddLineUnchecked(const Line<N>& line)
        添加线(不检查)
    - void AddFaceUnchecked(const Face<N>& face)
        添加面(不检查)
    - void ModifyLine(
        std::size_t index,
        int pointIndex,
        const Point<N>& point
    )
        修改线
    - void ModifyFace(
        std::size_t index,
        int pointIndex,
        const Point<N>& point
    )
        修改面
    - bool RemoveLine(std::size_t index)
        删除线
    - bool RemoveFace(std::size_t index)
        删除面
    - void Clear()
        清空所有存储的数据
    - double GetMinBoxVolume() const
        获取最小包围盒体积
Created by 朱昊东 on 2024/7/26
【更改记录】 无
*******************************************************************************/
template <std::size_t N>
class Model {
    public:
        /***********************************************************************
        【函数名称】 Model
        【函数功能】 构造函数，传入名称，默认为空
        【参数】 
            - std::string name（输入参数）：名称
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        Model(std::string name = ""): m_Name(name) {}
        Model(const Model<N>& other) = delete;// 禁用拷贝构造函数
        Model<N>& operator=(const Model<N>& other) = delete;// 禁用拷贝赋值运算符
        /***********************************************************************
        【函数名称】 ~Model
        【函数功能】 析构函数(默认)
        【参数】 无
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        virtual ~Model() = default;
        
        const std::string& Name { m_Name };
        const std::vector<std::shared_ptr<Line<N>>>& Lines { m_Lines };
        const std::vector<std::shared_ptr<Face<N>>>& Faces { m_Faces };

        /***********************************************************************
        【函数名称】 SetName
        【函数功能】 设置名称
        【参数】 
            - const std::string& name（输入参数）：名称
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        void SetName(const std::string& name) {
            m_Name = name;
        }

        /***********************************************************************
        【函数名称】 CollectPoints
        【函数功能】 获取所有Point对象的动态数组
        【参数】 无
        【返回值】 std::vector<std::shared_ptr<Point<N>>>：Point对象的动态数组
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        std::vector<std::shared_ptr<Point<N>>> CollectPoints() const{
            std::vector<std::shared_ptr<Point<N>>> points;

            auto addUniquePoints = [&](const auto& elements) {
                for (const auto& element : elements) {
                    //遍历elements的所有element
                    for (const auto& point : element->GetPointsVector()) {
                        //遍历element 的 PointsVector
                        if (std::none_of(
                            points.begin(),
                            points.end(), 
                            [&](const auto& p) {return p == point;})) {
                            points.push_back(point);// 添加不重复的点
                        }
                    }
                }
            };

            addUniquePoints(m_Lines);
            addUniquePoints(m_Faces);

            return points;
        }

        /***********************************************************************
        【函数名称】 AddLine
        【函数功能】 添加线
        【参数】 
            - const Point<N>& first（输入参数）：第一个点
            - const Point<N>& second（输入参数）：第二个点
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        void AddLine(
            const Point<N>& first,
            const Point<N>& second
        ) {
            const Point<N> points[2] = { first, second };
            if (!Line<N>::IsValid(points)) {
                throw ExceptionIdenticalPoint();
            }// 检查是否有相同的点
            for (auto line: m_Lines) {
                if (line->IsSame(points)) {
                    throw ExceptionIdenticalElement();
                }
            }// 检查是否有相同的线
            Line<N> line(std::make_shared<Point<N>>(first),
                         std::make_shared<Point<N>>(second));
            AddLineUnchecked(line);
        }

        /***********************************************************************
        【函数名称】 AddFace
        【函数功能】 添加面
        【参数】 
            - const Point<N>& first（输入参数）：第一个点
            - const Point<N>& second（输入参数）：第二个点
            - const Point<N>& third（输入参数）：第三个点
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        void AddFace(
            const Point<N>& first,
            const Point<N>& second,
            const Point<N>& third
        ){
            const Point<N> points[3] = { first, second, third };
            if (!Face<N>::IsValid(points)) {
                throw ExceptionIdenticalPoint();
            }// 检查是否有相同的点
            for (auto face: m_Faces) {
                if (face->IsSame(points)) {
                    throw ExceptionIdenticalElement();
                }
            }// 检查是否有相同的面
            Face<N> face(std::make_shared<Point<N>>(first),
                         std::make_shared<Point<N>>(second),
                         std::make_shared<Point<N>>(third));
            AddFaceUnchecked(face);
        }

        /***********************************************************************
        【函数名称】 AddLineUnchecked
        【函数功能】 添加线(不检查)
        【参数】 
            - const Line<N>& line（输入参数）：线对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        void AddLineUnchecked(const Line<N>& line){
            m_Lines.push_back(std::make_shared<Line<N>>(line));
        }

        /***********************************************************************
        【函数名称】 AddFaceUnchecked
        【函数功能】 添加面(不检查)
        【参数】 
            - const Face<N>& face（输入参数）：面对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        void AddFaceUnchecked(const Face<N>& face){
            m_Faces.push_back(std::make_shared<Face<N>>(face));
        }

        /***********************************************************************
        【函数名称】 ModifyLine
        【函数功能】 修改线
        【参数】 
            - std::size_t index（输入参数）：线的索引
            - int pointIndex（输入参数）：点的索引
            - const Point<N>& point（输入参数）：新的点对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        void ModifyLine(
            std::size_t index,
            int pointIndex,
            const Point<N>& point
        ) {
            if(index >= m_Lines.size()){
                throw ExceptionIndexOutOfBounds(index);
            }
            m_Lines[index]->ChangePoint(pointIndex, 
                                        std::make_shared<Point<N>>(point));
            for (int i = 0; i < m_Lines.size(); i++) {
                if (i != index && m_Lines[i]->IsSame(*m_Lines[index])) {
                    throw ExceptionIdenticalElement();
                }
            }

        }

        /***********************************************************************
        【函数名称】 ModifyFace
        【函数功能】 修改面
        【参数】 
            - std::size_t index（输入参数）：面的索引
            - int pointIndex（输入参数）：点的索引
            - const Point<N>& point（输入参数）：新的点对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        void ModifyFace(
            std::size_t index,
            int pointIndex,
            const Point<N>& point
        ) {
            if(index >= m_Faces.size()) {
                throw ExceptionIndexOutOfBounds(index);
            }
            m_Faces[index]->ChangePoint(pointIndex, 
                                        std::make_shared<Point<N>>(point));
            for (int i = 0; i < m_Faces.size(); i++) {
                if (i != index && m_Faces[i]->IsSame(*m_Faces[index])) {
                    throw ExceptionIdenticalElement();
                }
            }
        }

        /***********************************************************************
        【函数名称】 RemoveLine
        【函数功能】 删除线
        【参数】 
            - std::size_t index（输入参数）：线的索引
        【返回值】 bool：删除是否成功
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        bool RemoveLine(std::size_t index) {
            if(index >= m_Lines.size()) {
                return false;
            }
            m_Lines.erase(m_Lines.begin() + index);
            return true;
        }

        /***********************************************************************
        【函数名称】 RemoveFace
        【函数功能】 删除面
        【参数】 
            - std::size_t index（输入参数）：面的索引
        【返回值】 bool：删除是否成功
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        bool RemoveFace(std::size_t index) {
            if(index >= m_Faces.size()) {
                return false;
            }
            m_Faces.erase(m_Faces.begin() + index);
            return true;
        }

        /***********************************************************************
        【函数名称】 Clear
        【函数功能】 清空所有存储的数据
        【参数】 无
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        void Clear() {
            m_Lines.clear();
            m_Faces.clear();
        }

        /***********************************************************************
        【函数名称】 GetMinBoxVolume
        【函数功能】 获取最小包围盒体积
        【参数】 无
        【返回值】 double：最小包围盒体积
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        double GetMinBoxVolume() const {
            double coordinates[2 * N];
            for (int i = 0; i < N; i++) {
                coordinates[2 * i] = std::numeric_limits<double>::max();
                // 初始化为极大值
                coordinates[2 * i + 1] = std::numeric_limits<double>::min();
                // 初始化为极小值
            }
            for (auto point: CollectPoints()) {
                for (int i = 0; i < N; i++) {
                    coordinates[2 * i] = std::min(coordinates[2 * i], 
                                                  point->GetCoordinate(i));
                    coordinates[2 * i + 1] = std::max(coordinates[2 * i + 1],
                                                      point->GetCoordinate(i));
                }
            }
            double volume = 1;
            for (int i = 0; i < N; i++) {
                volume *= coordinates[2 * i + 1] - coordinates[2 * i];
            }
            return volume;
        }

    private:
        std::string m_Name;
        std::vector<std::shared_ptr<Line<N>>> m_Lines;
        std::vector<std::shared_ptr<Face<N>>> m_Faces;
};

#endif // MODEL_HPP