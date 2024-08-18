/*******************************************************************************
【文件名】 Point.hpp
【功能模块和目的】定义 Point 类模板，用于表示 N 维点及其相关操作
Created by 朱昊东 on 2024/7/23
【更改记录】 
    2024/7/26:
    - 修改static bool IsSame(const Point<N>& p1, const Point<N>& p2)
    2024/8/17
    - 修改了一些缩进问题
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
    - Point(const double* Coordinates)
        通过数组初始化坐标的构造函数
    - Point(const Point<N>& Other)
        拷贝构造函数
    - Point<N>& operator=(const Point<N>& Other)
        赋值运算符重载
    - virtual ~Point()
        虚析构函数
    - double GetCoordinate(std::size_t Index) const
        基于下标以获取指定坐标
    - double operator[](std::size_t Index) const
        下标运算符重载，等同于 GetCoordinate
    - void SetCoordinate(std::size_t Index, double Value)
        基于下标设置指定坐标
    - void SetCoordinates(const double* Coordinates)
        通过数组设置全体坐标
    - static bool IsSame(const Point<N>& P1, const Point<N>& P2) 
        判断两个点是否相同
    - bool IsSame(const Point<N> &Other) const
        判断当前点与另一点是否相同
    - template <std::size_t M> 
        static double Distance(const Point<N> P1, const Point<M> P2) 
        计算两点间的距离
    - template <std::size_t M> 
        double Distance(const Point<M> &Other) const
        计算当前点与另一点间的距离
    - virtual std::string ToString() const
        将点转换为字符串
    - bool operator==(const Point<N> &Other) const
        相等运算符重载
    - bool operator!=(const Point<N> &Other) const
        不等运算符重载
    - friend std::ostream& operator<<(std::ostream& Stream, 
                                      const Point<N>& Point)
        输出流运算符重载
    - friend std::istream& operator>>(std::istream& Stream, Point<N>& Point)
        输入流运算符重载
Created by 朱昊东 on 2024/7/23
【更改记录】 
    2024/7/26:
    - 修改static bool IsSame(const Point<N>& P1, const Point<N>& P2)
    2024/8/17
    - 修改了一些缩进问题
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
            double Zeros[N] = {0};
            SetCoordinates(Zeros);
        }

        /***********************************************************************
        【函数名称】 Point
        【函数功能】 构造函数，使用坐标数组初始化点
        【参数】 
            - const double* Coordinates (输入参数): 坐标数组
        【返回值】 无
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        Point(const double* Coordinates) {
            SetCoordinates(Coordinates);
        }

        /***********************************************************************
        【函数名称】 Point
        【函数功能】 拷贝构造函数，使用另一个点初始化
        【参数】 
            - const Point<N>& Other (输入参数): 另一个点
        【返回值】 无
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        Point(const Point<N>& Other): Point(Other.m_Coordinates) {}

        /***********************************************************************
        【函数名称】 operator=
        【函数功能】 赋值操作符，赋值另一个点的坐标
        【参数】 
            - const Point<N>& Other (输入参数): 另一个点
        【返回值】 Point<N>&: 当前对象的引用
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/               
        Point<N>& operator=(const Point<N>& Other) {
            if (this != &Other) {
                SetCoordinates(Other.m_Coordinates);
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
            - std::size_t Index (输入参数): 坐标的下标
        【返回值】 double: 指定下标的坐标值
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        double GetCoordinate(std::size_t Index) const {
            if (Index >= N) {
                throw ExceptionIndexOutOfBounds(Index);//thorw下标越界异常
            }
            return m_Coordinates[Index];
        }

        /***********************************************************************
        【函数名称】 operator[]
        【函数功能】 下标运算符重载，等同于 GetCoordinate
        【参数】 
            - std::size_t Index (输入参数): 坐标的下标
        【返回值】 double: 指定下标的坐标值
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        double operator[](std::size_t Index) const {
            return GetCoordinate(Index);
        }

        /***********************************************************************
        【函数名称】 SetCoordinate
        【函数功能】 基于下标设置指定坐标
        【参数】 
            - std::size_t Index (输入参数): 坐标的下标
            - double value (输入参数): 要设置的坐标值
        【返回值】 无
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        void SetCoordinate(std::size_t Index, double Value) {
            if (Index >= N) {
                throw ExceptionIndexOutOfBounds(Index);
            }
            m_Coordinates[Index] = Value;
        }

        /***********************************************************************
        【函数名称】 SetCoordinates
        【函数功能】 通过数组设置全体坐标
        【参数】 
            - const double* Coordinates (输入参数): 坐标数组
        【返回值】 无
        Created by 朱昊东 on 2024/7/23
        【更改记录】 
            2024/8/17
            - 修改了一些缩进问题
        ***********************************************************************/
        void SetCoordinates(const double* Coordinates) {
            for (int i = 0; i < N; i++) {
                SetCoordinate(i, Coordinates[i]);
            }
        }

        /***********************************************************************
        【函数名称】 IsSame
        【函数功能】 判断两个点是否相同
        【参数】 
            - const Point<N>& P1 (输入参数): 第一个点
            - const Point<N>& P2 (输入参数): 第二个点
        【返回值】 bool: 如果两个点相同则返回 true，否则返回 false
        Created by 朱昊东 on 2024/7/23
        【更改记录】 
            2024/7/26:
            -修改double类型的比较方式，由直接比较改为比较绝对值差大于1e-6以满足
            浮点数比较的精度要求
            2024/8/17
            - 修改了一些缩进问题
        ***********************************************************************/
        static bool IsSame(const Point<N>& P1, const Point<N>& P2) {
            for (int i = 0; i < N; i++) {
                if (std::fabs(P1.GetCoordinate(i) 
                        - P2.GetCoordinate(i)) > 1e-6) {
                    return false;
                }
            }
            return true;
        }

        /***********************************************************************
        【函数名称】 IsSame
        【函数功能】 判断当前点与另一点是否相同
        【参数】
            - const Point<N>& Other (输入参数): 另一个点
        【返回值】 bool: 如果两个点相同则返回 true，否则返回 false
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        bool IsSame(const Point<N> &Other) const {
            return IsSame(*this, Other);
        }

        /***********************************************************************
        【函数名称】 Distance
        【函数功能】 计算两点间的距离
        【参数】 
            - const Point<N> P1 (输入参数): 第一个点
            - const Point<M> P2 (输入参数): 第二个点
        【返回值】 double: 两点间的距离，允许这两个点的维数不同
        Created by 朱昊东 on 2024/7/23
        【更改记录】 
            2024/8/17
            - 修改了一些缩进问题
        ***********************************************************************/
        template <std::size_t M>
        static double Distance(const Point<N> P1, const Point<M> P2) {
            if (N == M) {
                double SumOfSquares = 0;
                for (int i = 0; i < N; i++) {
                    SumOfSquares += std::pow(P1.GetCoordinate(i)
                        - P2.GetCoordinate(i), 2);
                }
                return std::sqrt(SumOfSquares);
            }
            else if (N > M) {
                double SumOfSquares = 0;
                for (int i = 0; i < M; i++) {
                    SumOfSquares += std::pow(P1.GetCoordinate(i)
                        - P2.GetCoordinate(i), 2);
                }
                for (int i = M; i < N; i++) {
                    SumOfSquares += std::pow(P1.GetCoordinate(i) , 2);
                }
                return std::sqrt(SumOfSquares);
            }//P1的维数大于P2的维数
            else {
                double SumOfSquares = 0;
                for (int i = 0; i < N; i++) {
                    SumOfSquares += std::pow(P1.GetCoordinate(i)
                        - P2.GetCoordinate(i), 2);
                }
                for (int i = M; i < M; i++) {
                    SumOfSquares += std::pow(P2.GetCoordinate(i) , 2);
                }
                return std::sqrt(SumOfSquares);
            }//P1的维数小于P2的维数
        }
        
        /***********************************************************************
        【函数名称】 Distance
        【函数功能】 计算当前点与另一点间的距离
        【参数】 
            - const Point<M>& Other (输入参数): 另一个点
        【返回值】 double: 两点间的距离
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        template <std::size_t M>
        double Distance(const Point<M> &Other) const {
            return Distance(*this, Other);
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
            std::ostringstream Stream;
            Stream << "[ ";
            for (int i = 0; i < N; i++) {
                Stream << GetCoordinate(i) << " ";
            }
            Stream << "]";
            return Stream.str();//格式为[ 1 2 3 ]
        }

        /***********************************************************************
        【函数名称】 operator==
        【函数功能】 相等运算符重载，判断两个点是否相同
        【参数】 
            - const Point<N>& Other (输入参数): 另一个点
        【返回值】 bool: 如果两个点相同则返回 true，否则返回 false
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        bool operator==(const Point<N> &Other) const {
            return IsSame(Other);
        }

        /***********************************************************************
        【函数名称】 operator!=
        【函数功能】 不等运算符重载，判断两个点是否不同
        【参数】 
            - const Point<N>& Other (输入参数): 另一个点
        【返回值】 bool: 如果两个点不同则返回 true，否则返回 false
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        bool operator!=(const Point<N> &Other) const {
            return !IsSame(Other);
        }

        /***********************************************************************
        【函数名称】 operator<<
        【函数功能】 输出点的字符串表示
        【参数】 
            - std::ostream& stream (输入参数): 输出流
            - const Point<N>& point (输入参数): 点对象
        【返回值】 std::ostream&: 输出流
        Created by 朱昊东 on 2024/7/23
        【更改记录】 
            2024/8/17
            - 修改了一些缩进问题
        ***********************************************************************/
        friend std::ostream& operator<<(
            std::ostream& Stream, const Point<N>& Point) {
            Stream << Point.ToString();
            return Stream;
        }

        /***********************************************************************
        【函数名称】 operator>>
        【函数功能】 从输入流中读取点的坐标
        【参数】 
            - std::istream& Stream (输入参数): 输入流
            - Point<N>& Point (输入参数): 点对象
        【返回值】 std::istream&: 输入流
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        friend std::istream& operator>>(std::istream& Stream, Point<N>& Point) {
            char Ch;
            double Coordinates[N];
            Stream >> Ch; // 读取并丢弃 '['
            for (int i = 0; i < N; i++) {
                Stream >> Coordinates[i];
                Stream >> std::ws; // 忽略空白字符
            }
            Stream >> Ch; // 读取并丢弃 ']'
            Point.SetCoordinates(Coordinates);
            return Stream;
        }
    private:
        double m_Coordinates[N];
};

#endif // POINT_HPP