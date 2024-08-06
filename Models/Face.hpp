/*******************************************************************************
【文件名】 Face.hpp
【功能模块和目的】 定义Face类模板，该类继承自Element类，拥有三个N维空间中的
 Point类对象
 Created by 朱昊东 on 2024/7/25
【更改记录】 无
*******************************************************************************/
#ifndef FACE_HPP
#define FACE_HPP

#include <cmath>
#include <memory>
#include <ostream>
#include <string>
#include "Element.hpp"
#include "Point.hpp"

/*******************************************************************************
【类名】 Face
【功能】 Face类模板继承自Element类，拥有三个N维空间中的Point类对象，提供了
 计算面积和输出字符串的方法
【接口说明】
    - Face()
        受保护的默认构造函数，不允许直接调用
    - Face(const std::shared_ptr<Point<N>>& first,
        const std::shared_ptr<Point<N>>& second,
        const std::shared_ptr<Point<N>>& third)
        构造函数，传入三个点对象
    - Face(const std::shared_ptr<Point<N>>* points)
        构造函数，传入三个点对象的指针
    - Face(const Face<N>& other)
        拷贝构造函数
    - Face<N>& operator=(const Face<N>& other)
        拷贝赋值运算符
    - ~Face()
        析构函数(默认)
    - void SetFirst(const std::shared_ptr<Point<N>>& first)
        设置第一个点对象
    - void SetSecond(const std::shared_ptr<Point<N>>& second)
        设置第二个点对象
    - void SetThird(const std::shared_ptr<Point<N>>& third)
        设置第三个点对象
    - double GetArea() const
        返回面积
    - std::string ToString() const
        将面对象转换为字符串
 Created by 朱昊东 on 2024/7/25
【更改记录】 无
*******************************************************************************/
template <std::size_t N>
class Face: public Element<N, 3> {
    public:
        /***********************************************************************
        【函数名称】 Face
        【函数功能】 构造函数，使用给定的点数组初始化元素
        【参数】 
            - const std::shared_ptr<Point<N>>& first（输入参数）：
            指向 Point<N> 对象的指针
            - const std::shared_ptr<Point<N>>& second（输入参数）：
            指向 Point<N> 对象的指针
            - const std::shared_ptr<Point<N>>& third（输入参数）：
            指向 Point<N> 对象的指针
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        Face(
            const std::shared_ptr<Point<N>>& first,
            const std::shared_ptr<Point<N>>& second,
            const std::shared_ptr<Point<N>>& third
        ) {
            std::shared_ptr<Point<N>> points[] = { first, second, third };
            this->SetPoints(points);
        }

        /***********************************************************************
        【函数名称】 Face
        【函数功能】 构造函数，使用给定的点数组指针初始化元素
        【参数】 
            - const std::shared_ptr<Point<N>>* points（输入参数）：点对象数组指针
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        Face(const std::shared_ptr<Point<N>>* points) {
            this->SetPoints(points);
        }
        /***********************************************************************
        【函数名称】 Face
        【函数功能】 拷贝构造函数，使用另一个 Face 对象初始化元素
        【参数】 
            - const Face<N>& other（输入参数）：另一个 Face 对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        Face(const Face<N>& other): Element<N, 3>(other) {}

        /***********************************************************************
        【函数名称】 operator=
        【函数功能】 赋值操作符，赋值另一个 Face 对象
        【参数】
            - const Face<N>& other（输入参数）：另一个 Face 对象
        【返回值】 Face<N>&: 当前对象的引用
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        Face<N>& operator=(const Face<N>& other) {
            if (this != &other) {
                Element<N, 3>::operator=(other);
            }
            return *this;
        }

        /***********************************************************************
        【函数名称】 ~Face
        【函数功能】 析构函数
        【参数】 无
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        ~Face() override = default;
                
        const std::shared_ptr<Point<N>>& First { Element<N, 3>::m_Points[0] };
        const std::shared_ptr<Point<N>>& Second { Element<N, 3>::m_Points[1] };
        const std::shared_ptr<Point<N>>& Third { Element<N, 3>::m_Points[2] };
        //对于Face对象的三个点对象的智能指针的引用绑定Getter

        /***********************************************************************
        【函数名称】 SetFirst
        【函数功能】 设置第一个点对象
        【参数】 
            - const std::shared_ptr<Point<N>>& first（输入参数）：第一个点对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        void SetFirst(const std::shared_ptr<Point<N>>& first) {
            this->SetPoint(0, first);
        }

        /***********************************************************************
        【函数名称】 SetSecond
        【函数功能】 设置第二个点对象
        【参数】 
            - const std::shared_ptr<Point<N>>& second（输入参数）：第二个点对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        void SetSecond(const std::shared_ptr<Point<N>>& second) {
            this->SetPoint(1, second);
        }

        /***********************************************************************
        【函数名称】 SetThird
        【函数功能】 设置第三个点对象
        【参数】 
            - const std::shared_ptr<Point<N>>& third（输入参数）：第三个点对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        void SetThird(const std::shared_ptr<Point<N>>& third) {
            this->SetPoint(2, third);
        }

        /***********************************************************************
        【函数名称】 GetArea
        【函数功能】 计算并返回面对象的面积
        【参数】 无
        【返回值】 double: 面对象的面积
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        double GetArea() const{
            double a = Point<N>::Distance(*First, *Second);
            double b = Point<N>::Distance(*Second, *Third);
            double c = Point<N>::Distance(*Third, *First);
            double p = (a + b + c) / 2;
            return std::sqrt(p * (p - a) * (p - b) * (p - c));

        }

        /***********************************************************************
        【函数名称】 ToString
        【函数功能】 将面对象转换为字符串
        【参数】 无
        【返回值】 std::string: 面对象的字符串表示
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        std::string ToString() const override {
            std::ostringstream stream;
            stream << "Face ";
            stream << Element<N, 3>::ToString();
            return stream.str();
        } 
    protected:
        Face() = default;   
};

#endif // FACE_HPP