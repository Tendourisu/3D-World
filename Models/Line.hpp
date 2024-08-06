/*******************************************************************************
【文件名】 Line.hpp
【功能模块和目的】 定义Line类模板，该类继承自Element类，拥有两个N维空间中的
 Point类对象
 Created by 朱昊东 on 2024/7/25
【更改记录】 无
*******************************************************************************/
#ifndef LINE_HPP
#define LINE_HPP

#include <memory>
#include <ostream>
#include <string>
#include "Element.hpp"
#include "Point.hpp"

/*******************************************************************************
【类名】 Line
【功能】 Line类模板继承自Element类，拥有两个N维空间中的Point类对象，提供了
 计算长度和输出字符串的方法
【接口说明】
    - Line(const std::shared_ptr<Point<N>>& first,
           const std::shared_ptr<Point<N>>& second)
        构造函数，传入两个点对象
    - Line(const std::shared_ptr<Point<N>>* points)
        构造函数，传入两个点对象的指针
    - Line(const Line<N>& other)
        拷贝构造函数
    - Line<N>& operator=(const Line<N>& other)
        拷贝赋值运算符
    - ~Line()
        析构函数(默认)
    - void SetFirst(const std::shared_ptr<Point<N>>& first)
        设置第一个点对象
    - void SetSecond(const std::shared_ptr<Point<N>>& second)
        设置第二个点对象
    - double GetLength() const
        返回长度
    - std::string ToString() const
        将线对象转换为字符串
*******************************************************************************/
template <std::size_t N>
class Line: public Element<N, 2> {
    public:
        /***********************************************************************
        【函数名称】 Line
        【函数功能】 构造函数，使用给定的点数组初始化元素
        【参数】 
            - const std::shared_ptr<Point<N>>& first（输入参数）：
            指向 Point<N> 对象的指针
            - const std::shared_ptr<Point<N>>& second（输入参数）：
            指向 Point<N> 对象的指针
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        Line(
            const std::shared_ptr<Point<N>>& first,
            const std::shared_ptr<Point<N>>& second
        ){
            std::shared_ptr<Point<N>> points[] = { first, second };
            this->SetPoints(points);
        }

        /***********************************************************************
        【函数名称】 Line
        【函数功能】 构造函数，使用给定的点数组初始化元素
        【参数】 
            - const std::shared_ptr<Point<N>>* points（输入参数）：
            指向 Point<N> 对象数组的指针
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        Line(const std::shared_ptr<Point<N>>* points) {
            this->SetPoints(points);
        }

        /***********************************************************************
        【函数名称】 Line
        【函数功能】 拷贝构造函数，使用另一个 Line 对象初始化元素
        【参数】 
            - const Line<N>& other（输入参数）：
            另一个 Line 对象的引用
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        Line(const Line<N>& other): Element<N, 2>(other) {}

        /***********************************************************************
        【函数名称】 operator=
        【函数功能】 拷贝赋值运算符，使用另一个 Line 对象赋值当前对象
        【参数】 
            - const Line<N>& other（输入参数）：
            另一个 Line 对象的引用
        【返回值】 Line<N>& ：当前对象的引用
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        Line<N>& operator=(const Line<N>& other){
            if (this != &other) {
                Element<N, 2>::operator=(other);
            }
            return *this;
        }

        /***********************************************************************
        【函数名称】 ~Line
        【函数功能】 虚析构函数
        【参数】 无
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        ~Line() override = default;
                
        const std::shared_ptr<Point<N>>& First  { Element<N, 2>::m_Points[0] };
        const std::shared_ptr<Point<N>>& Second  { Element<N, 2>::m_Points[1] };

        /***********************************************************************
        【函数名称】 SetFirst
        【函数功能】 设置第一个点对象
        【参数】 
            - const std::shared_ptr<Point<N>>& first（输入参数）：
            指向 Point<N> 对象的指针
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        void SetFirst(const std::shared_ptr<Point<N>>& first){
            this->SetPoint(0, first);
        }

        /***********************************************************************
        【函数名称】 SetSecond
        【函数功能】 设置第二个点对象
        【参数】 
            - const std::shared_ptr<Point<N>>& second（输入参数）：
            指向 Point<N> 对象的指针
        【返回值】 无
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        void SetSecond(const std::shared_ptr<Point<N>>& second){
            this->SetPoint(1, second);
        }

        /***********************************************************************
        【函数名称】 GetLength
        【函数功能】 计算并返回线段的长度
        【参数】 无
        【返回值】 double ：线段的长度
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        double GetLength() const{
        return Point<N>::Distance(*First, *Second);
        }

        /***********************************************************************
        【函数名称】 ToString
        【函数功能】 将线对象转换为字符串
        【参数】 无
        【返回值】 std::string ：线对象的字符串表示
        Created by 朱昊东 on 2024/7/25
        【更改记录】 无
        ***********************************************************************/
        std::string ToString() const override{
            std::ostringstream stream;
            stream << "Line ";
            stream << Element<N, 2>::ToString();
            return stream.str();
        }    
    protected:
        Line() = default;
};

#endif // LINE_HPP