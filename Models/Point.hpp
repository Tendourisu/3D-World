/*******************************************************************************
【文件名】 Point.hpp
【功能模块和目的】定义 Point 类模板，用于表示 N 维点及其相关操作
Created by 朱昊东 on 2024/7/23
【更改记录】 2024/7/26:
    修改static bool IsSame(const Point<N>& p1, const Point<N>& p2)
*******************************************************************************/

#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>
#include <ostream>
#include <sstream>
#include <string>
#include "../Errors.hpp"

/*******************************************************************************
【类名】 Point
【功能】提供坐标设置、获取和比较等功能
【接口说明】 
    - Point() 
        默认构造函数，创建坐标全为 0 的点
    - Point(const double* coordinates)
        通过数组初始化坐标的构造函数
    - Point(const Point<N>& other)
        拷贝构造函数
    - Point<N>& operator=(const Point<N>& other)
        赋值运算符重载
    - virtual ~Point()
        虚析构函数
    - double GetCoordinate(std::size_t index) const
        基于下标以获取指定坐标
    - double operator[](std::size_t index) const
        下标运算符重载，等同于 GetCoordinate
    - void SetCoordinate(std::size_t index, double value)
        基于下标设置指定坐标
    - void SetCoordinates(const double* coordinates)
        通过数组设置全体坐标
    - static bool IsSame(const Point<N>& p1, const Point<N>& p2) 
        判断两个点是否相同
    - bool IsSame(const Point<N> &other) const
        判断当前点与另一点是否相同
    - template <std::size_t M> 
        static double Distance(const Point<N> p1, const Point<M> p2) 
        计算两点间的距离
    - template <std::size_t M> 
        double Distance(const Point<M> &other) const
        计算当前点与另一点间的距离
    - virtual std::string ToString() const
        将点转换为字符串
    - bool operator==(const Point<N> &other) const
        相等运算符重载
    - bool operator!=(const Point<N> &other) const
        不等运算符重载
    - friend std::ostream& operator<<(std::ostream& stream, 
                                      const Point<N>& point)
        输出流运算符重载
    - friend std::istream& operator>>(std::istream& stream, Point<N>& point)
        输入流运算符重载
Created by 朱昊东 on 2024/7/23
【更改记录】 2024/7/26:
    修改static bool IsSame(const Point<N>& p1, const Point<N>& p2)
*******************************************************************************/

template <std::size_t N>
class Point {
    public:
        /***********************************************************************
        【函数名称】 Point
        【函数功能】 默认构造函数，创建坐标全为 0 的点
        【参数】 无
        【返回值】 无
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        Point() {
            double zeros[N] = {0};
            SetCoordinates(zeros);
        }

        /***********************************************************************
        【函数名称】 Point
        【函数功能】 构造函数，使用坐标数组初始化点
        【参数】 
            - const double* coordinates (输入参数): 坐标数组
        【返回值】 无
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        Point(const double* coordinates) {
            SetCoordinates(coordinates);
        }

        /***********************************************************************
        【函数名称】 Point
        【函数功能】 拷贝构造函数，使用另一个点初始化
        【参数】 
            - const Point<N>& other (输入参数): 另一个点
        【返回值】 无
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        Point(const Point<N>& other): Point(other.m_Coordinates) {}

        /***********************************************************************
        【函数名称】 operator=
        【函数功能】 赋值操作符，赋值另一个点的坐标
        【参数】 
            - const Point<N>& other (输入参数): 另一个点
        【返回值】 Point<N>&: 当前对象的引用
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/               
        Point<N>& operator=(const Point<N>& other) {
            if (this != &other) {
                SetCoordinates(other.m_Coordinates);
            }
            return *this;
        }

        /***********************************************************************
        【函数名称】 ~Point
        【函数功能】 虚析构函数（默认）
        【参数】 无
        【返回值】 无
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        virtual ~Point() = default;

        /***********************************************************************
        【函数名称】 GetCoordinate
        【函数功能】 基于下标以获取指定坐标
        【参数】 
            - std::size_t index (输入参数): 坐标的下标
        【返回值】 double: 指定下标的坐标值
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        double GetCoordinate(std::size_t index) const {
            if (index >= N) {
                throw ExceptionIndexOutOfBounds(index);//thorw下标越界异常
            }
            return m_Coordinates[index];
        }

        /***********************************************************************
        【函数名称】 operator[]
        【函数功能】 下标运算符重载，等同于 GetCoordinate
        【参数】 
            - std::size_t index (输入参数): 坐标的下标
        【返回值】 double: 指定下标的坐标值
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        double operator[](std::size_t index) const {
            return GetCoordinate(index);
        }

        /***********************************************************************
        【函数名称】 SetCoordinate
        【函数功能】 基于下标设置指定坐标
        【参数】 
            - std::size_t index (输入参数): 坐标的下标
            - double value (输入参数): 要设置的坐标值
        【返回值】 无
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        void SetCoordinate(std::size_t index, double value) {
            if (index >= N) {
                throw ExceptionIndexOutOfBounds(index);
            }
            m_Coordinates[index] = value;
        }

        /***********************************************************************
        【函数名称】 SetCoordinates
        【函数功能】 通过数组设置全体坐标
        【参数】 
            - const double* coordinates (输入参数): 坐标数组
        【返回值】 无
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        void SetCoordinates(const double* coordinates) {
            for (int i = 0; i < N; i++) {
                SetCoordinate(i, coordinates[i]);
            }
        }

        /***********************************************************************
        【函数名称】 IsSame
        【函数功能】 判断两个点是否相同
        【参数】 
            - const Point<N>& p1 (输入参数): 第一个点
            - const Point<N>& p2 (输入参数): 第二个点
        【返回值】 bool: 如果两个点相同则返回 true，否则返回 false
        Created by 朱昊东 on 2024/7/23
        【更改记录】 2024/7/26:
            修改double类型的比较方式，由直接比较改为比较绝对值差大于1e-6以满足
            浮点数比较的精度要求
        ***********************************************************************/
        static bool IsSame(const Point<N>& p1, const Point<N>& p2) {
            for (int i = 0; i < N; i++) {
                if (std::fabs(p1.GetCoordinate(i) 
                            - p2.GetCoordinate(i)) > 1e-6) {
                    return false;
                }
            }
            return true;
        }
        bool IsSame(const Point<N> &other) const {
            return IsSame(*this, other);
        }

        /***********************************************************************
        【函数名称】 Distance
        【函数功能】 计算两点间的距离
        【参数】 
            - const Point<N> p1 (输入参数): 第一个点
            - const Point<M> p2 (输入参数): 第二个点
        【返回值】 double: 两点间的距离，允许这两个点的维数不同
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        template <std::size_t M>
        static double Distance(const Point<N> p1, const Point<M> p2) {
            if (N == M) {
                double sumOfSquares = 0;
                for (int i = 0; i < N; i++) {
                    sumOfSquares += std::pow(p1.GetCoordinate(i)
                                           - p2.GetCoordinate(i), 2);
                }
                return std::sqrt(sumOfSquares);
            }
            else if (N > M) {
                double sumOfSquares = 0;
                for (int i = 0; i < M; i++) {
                    sumOfSquares += std::pow(p1.GetCoordinate(i)
                                           - p2.GetCoordinate(i), 2);
                }
                for (int i = M; i < N; i++) {
                    sumOfSquares += std::pow(p1.GetCoordinate(i) , 2);
                }
                return std::sqrt(sumOfSquares);
            }//p1的维数大于p2的维数
            else {
                double sumOfSquares = 0;
                for (int i = 0; i < N; i++) {
                    sumOfSquares += std::pow(p1.GetCoordinate(i)
                                           - p2.GetCoordinate(i), 2);
                }
                for (int i = M; i < M; i++) {
                    sumOfSquares += std::pow(p2.GetCoordinate(i) , 2);
                }
                return std::sqrt(sumOfSquares);
            }//p1的维数小于p2的维数
        }
        
        /***********************************************************************
        【函数名称】 Distance
        【函数功能】 计算当前点与另一点间的距离
        【参数】 
            - const Point<M>& other (输入参数): 另一个点
        【返回值】 double: 两点间的距离
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        template <std::size_t M>
        double Distance(const Point<M> &other) const {
            return Distance(*this, other);
        }

        /***********************************************************************
        【函数名称】 ToString
        【函数功能】 返回点的字符串表示
        【参数】 无
        【返回值】 std::string: 点的字符串表示
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/        
        virtual std::string ToString() const {
            std::ostringstream stream;
            stream << "[ ";
            for (int i = 0; i < N; i++) {
                stream << GetCoordinate(i) << " ";
            }
            stream << "]";
            return stream.str();//格式为[ 1 2 3 ]
        }

        /***********************************************************************
        【函数名称】 operator==
        【函数功能】 相等运算符重载，判断两个点是否相同
        【参数】 
            - const Point<N>& other (输入参数): 另一个点
        【返回值】 bool: 如果两个点相同则返回 true，否则返回 false
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        bool operator==(const Point<N> &other) const {
            return IsSame(other);
        }

        /***********************************************************************
        【函数名称】 operator!=
        【函数功能】 不等运算符重载，判断两个点是否不同
        【参数】 
            - const Point<N>& other (输入参数): 另一个点
        【返回值】 bool: 如果两个点不同则返回 true，否则返回 false
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        bool operator!=(const Point<N> &other) const {
            return !IsSame(other);
        }

        /***********************************************************************
        【函数名称】 operator<<
        【函数功能】 输出点的字符串表示
        【参数】 
            - std::ostream& stream (输入参数): 输出流
            - const Point<N>& point (输入参数): 点对象
        【返回值】 std::ostream&: 输出流
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        friend std::ostream& operator<<(std::ostream& stream,
                                        const Point<N>& point) {
            stream << point.ToString();
            return stream;
        }

        /***********************************************************************
        【函数名称】 operator>>
        【函数功能】 从输入流中读取点的坐标
        【参数】 
            - std::istream& stream (输入参数): 输入流
            - Point<N>& point (输入参数): 点对象
        【返回值】 std::istream&: 输入流
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        friend std::istream& operator>>(std::istream& stream, Point<N>& point) {
            char ch;
            double coordinates[N];
            
            stream >> ch; // 读取并丢弃 '['
            for (int i = 0; i < N; i++) {
                stream >> coordinates[i];
                stream >> std::ws; // 忽略空白字符
            }
            stream >> ch; // 读取并丢弃 ']'
            point.SetCoordinates(coordinates);
            return stream;
        }
    private:
        double m_Coordinates[N];
};

#endif // POINT_HPP