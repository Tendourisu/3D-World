/*******************************************************************************
【文件名】 Model.hpp
【功能模块和目的】 定义Model类模板，该类含有一个Line类对象的动态数组和一个Face类
对象的动态数组，提供了添加、修改、删除、清空、获取最小包围盒体积，及获取所有Point类
对象的动态数组构成的的方法
 Created by 朱昊东 on 2024/7/26
【更改记录】 
    2024/8/17
    - 修改了一些缩进问题
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
    - Model(std::string Name = "")
        构造函数，传入名称，默认为空
    - ~Model()
        析构函数(默认)
    - void SetName(const std::string& Name)
        设置名称
    - std::vector<std::shared_ptr<Point<N>>> CollectPoints() const
        获取所有Point对象的动态数组
    - void AddLine(
        const Point<N>& First,
        const Point<N>& Second)
        添加线
    - void AddFace(
        const Point<N>& First,
        const Point<N>& Second,
        const Point<N>& Third)
        添加面  
    - void AddLineUnchecked(const Line<N>& Line)
        添加线(不检查)
    - void AddFaceUnchecked(const Face<N>& Face)
        添加面(不检查)
    - void ModifyLine(
        std::size_t Index,
        int PointIndex,
        const Point<N>& Point
    )
        修改线
    - void ModifyFace(
        std::size_t Index,
        int PointIndex,
        const Point<N>& Point
    )
        修改面
    - bool RemoveLine(std::size_t Index)
        删除线
    - bool RemoveFace(std::size_t Index)
        删除面
    - void Clear()
        清空所有存储的数据
    - double GetMinBoxVolume() const
        获取最小包围盒体积
Created by 朱昊东 on 2024/7/26
【更改记录】 
    2024/8/17
    - 修改了一些缩进问题
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
        Model(std::string Name = ""): m_Name(Name) {}
        Model(const Model<N>& Other) = delete;// 禁用拷贝构造函数
        Model<N>& operator=(const Model<N>& Other) = delete;// 禁用拷贝赋值运算符
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
            - const std::string& Name（输入参数）：名称
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        void SetName(const std::string& Name) {
            m_Name = Name;
        }

        /***********************************************************************
        【函数名称】 CollectPoints
        【函数功能】 获取所有Point对象的动态数组
        【参数】 无
        【返回值】 std::vector<std::shared_ptr<Point<N>>>：Point对象的动态数组
        Created by 朱昊东 on 2024/7/26
        【更改记录】 
            2024/8/17
            - 修改了一些缩进问题
        ***********************************************************************/
        std::vector<std::shared_ptr<Point<N>>> CollectPoints() const{
            std::vector<std::shared_ptr<Point<N>>> Points;
            auto AddUniquePoints = [&](const auto& Elements) {
                for (const auto& Element : Elements) {
                    //遍历Elements的所有Element
                    for (const auto& Point : Element->GetPointsVector()) {
                        //遍历Element 的 PointsVector
                        if (std::none_of(
                            Points.begin(),
                            Points.end(), 
                            [&](const auto& p) {return p == Point;})) {
                            Points.push_back(Point);// 添加不重复的点
                        }
                    }
                }
            };
            AddUniquePoints(m_Lines);
            AddUniquePoints(m_Faces);
            return Points;
        }

        /***********************************************************************
        【函数名称】 AddLine
        【函数功能】 添加线
        【参数】 
            - const Point<N>& First（输入参数）：第一个点
            - const Point<N>& Second（输入参数）：第二个点
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 
            2024/8/17
            - 修改了一些缩进问题
        ***********************************************************************/
        void AddLine(
            const Point<N>& First,
            const Point<N>& Second
        ) {
            const Point<N> Points[2] = { First, Second };
            if (!Line<N>::IsValid(Points)) {
                throw ExceptionIdenticalPoint();
            }// 检查是否有相同的点
            for (auto Line: m_Lines) {
                if (Line->IsSame(Points)) {
                    throw ExceptionIdenticalElement();
                }
            }// 检查是否有相同的线
            Line<N> Line(
                std::make_shared<Point<N>>(First),
                std::make_shared<Point<N>>(Second));
            AddLineUnchecked(Line);
        }

        /***********************************************************************
        【函数名称】 AddFace
        【函数功能】 添加面
        【参数】 
            - const Point<N>& First（输入参数）：第一个点
            - const Point<N>& Second（输入参数）：第二个点
            - const Point<N>& Third（输入参数）：第三个点
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 
            2024/8/17
            - 修改了一些缩进问题
        ***********************************************************************/
        void AddFace(
            const Point<N>& First,
            const Point<N>& Second,
            const Point<N>& Third) {
            const Point<N> Points[3] = { First, Second, Third };
            if (!Face<N>::IsValid(Points)) {
                throw ExceptionIdenticalPoint();
            }// 检查是否有相同的点
            for (auto Face: m_Faces) {
                if (Face->IsSame(Points)) {
                    throw ExceptionIdenticalElement();
                }
            }// 检查是否有相同的面
            Face<N> Face(
                std::make_shared<Point<N>>(First),
                std::make_shared<Point<N>>(Second),
                std::make_shared<Point<N>>(Third));
            AddFaceUnchecked(Face);
        }

        /***********************************************************************
        【函数名称】 AddLineUnchecked
        【函数功能】 添加线(不检查)
        【参数】 
            - const Line<N>& Line（输入参数）：线对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        void AddLineUnchecked(const Line<N>& L){
            m_Lines.push_back(std::make_shared<Line<N>>(L));
        }

        /***********************************************************************
        【函数名称】 AddFaceUnchecked
        【函数功能】 添加面(不检查)
        【参数】 
            - const Face<N>& Face（输入参数）：面对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        void AddFaceUnchecked(const Face<N>& F){
            m_Faces.push_back(std::make_shared<Face<N>>(F));
        }

        /***********************************************************************
        【函数名称】 ModifyLine
        【函数功能】 修改线
        【参数】 
            - std::size_t Index（输入参数）：线的索引
            - int PointIndex（输入参数）：点的索引
            - const Point<N>& Point（输入参数）：新的点对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 
            2024/8/17
            - 修改了一些缩进问题
        ***********************************************************************/
        void ModifyLine(
            std::size_t Index,
            int PointIndex,
            const Point<N>& P) {
            if (Index >= m_Lines.size()) {
                throw ExceptionIndexOutOfBounds(Index);
            }
            m_Lines[Index]->ChangePoint(
                PointIndex, std::make_shared<Point<N>>(P));
            for (int i = 0; i < m_Lines.size(); i++) {
                if (i != Index && m_Lines[i]->IsSame(*m_Lines[Index])) {
                    throw ExceptionIdenticalElement();
                }
            }

        }

        /***********************************************************************
        【函数名称】 ModifyFace
        【函数功能】 修改面
        【参数】 
            - std::size_t Index（输入参数）：面的索引
            - int PointIndex（输入参数）：点的索引
            - const Point<N>& Point（输入参数）：新的点对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/26
        【更改记录】 
            2024/8/17
            - 修改了一些缩进问题
        ***********************************************************************/
        void ModifyFace(
            std::size_t Index,
            int PointIndex,
            const Point<N>& P) {
            if (Index >= m_Faces.size()) {
                throw ExceptionIndexOutOfBounds(Index);
            }
            m_Faces[Index]->ChangePoint(PointIndex, 
                std::make_shared<Point<N>>(P));
            for (int i = 0; i < m_Faces.size(); i++) {
                if (i != Index && m_Faces[i]->IsSame(*m_Faces[Index])) {
                    throw ExceptionIdenticalElement();
                }
            }
        }

        /***********************************************************************
        【函数名称】 RemoveLine
        【函数功能】 删除线
        【参数】 
            - std::size_t Index（输入参数）：线的索引
        【返回值】 bool：删除是否成功
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        bool RemoveLine(std::size_t Index) {
            if (Index >= m_Lines.size()) {
                return false;
            }
            m_Lines.erase(m_Lines.begin() + Index);
            return true;
        }

        /***********************************************************************
        【函数名称】 RemoveFace
        【函数功能】 删除面
        【参数】 
            - std::size_t Index（输入参数）：面的索引
        【返回值】 bool：删除是否成功
        Created by 朱昊东 on 2024/7/26
        【更改记录】 无
        ***********************************************************************/
        bool RemoveFace(std::size_t Index) {
            if (Index >= m_Faces.size()) {
                return false;
            }
            m_Faces.erase(m_Faces.begin() + Index);
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
        【更改记录】 
            2024/8/17
            - 修改了一些缩进问题
        ***********************************************************************/
        double GetMinBoxVolume() const {
            double Coordinates[2 * N];
            for (int i = 0; i < N; i++) {
                Coordinates[2 * i] = std::numeric_limits<double>::max();
                // 初始化为极大值
                Coordinates[2 * i + 1] = std::numeric_limits<double>::min();
                // 初始化为极小值
            }
            for (auto Point: CollectPoints()) {
                for (int i = 0; i < N; i++) {
                    Coordinates[2 * i] = std::min(
                        Coordinates[2 * i], Point->GetCoordinate(i));
                    Coordinates[2 * i + 1] = std::max(
                        Coordinates[2 * i + 1], Point->GetCoordinate(i));
                }
            }
            double Volume = 1;
            for (int i = 0; i < N; i++) {
                Volume *= Coordinates[2 * i + 1] - Coordinates[2 * i];
            }
            return Volume;
        }

    private:
        std::string m_Name;
        std::vector<std::shared_ptr<Line<N>>> m_Lines;
        std::vector<std::shared_ptr<Face<N>>> m_Faces;
};

#endif // MODEL_HPP