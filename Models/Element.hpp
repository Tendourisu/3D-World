/*******************************************************************************
【文件名】 Element.hpp
【功能模块和目的】定义 Element 类模板，用于表示具有 P 个点的 N 维空间中的元素
Created by 朱昊东 on 2024/7/24
【更改记录】 无
*******************************************************************************/
#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <memory>
#include <string>
#include <vector>
#include "Point.hpp"
#include "../Errors.hpp"

/*******************************************************************************
【类名】Element
【功能】表示具有 P 个点的 N 维空间中的元素
【接口说明】
    - Element()
        受保护的默认构造函数，不允许直接构造 Element 对象
    - Element(const std::shared_ptr<Point<N>>* points)
        构造函数，根据给定的点的智能指针的数组构造元素
    - Element(const Element<N, P>& other)
        拷贝构造函数
    - Element<N, P>& operator=(const Element<N, P>& other)
        赋值运算符重载
    - virtual ~Element() = default
        虚析构函数（默认）
    - static bool IsValid(const Point<N>* points)
        判断给定的点是否构成一个合法的元素
    - static bool IsValid(const std::shared_ptr<Point<N>>* points)
        判断给定的点的智能指针是否构成一个合法的元素
    - static bool IsValid(const Element<N, P>& element)
        判断给定的元素是否合法
    - void SetPoint(std::size_t index, const std::shared_ptr<Point<N>>& point)
        设置元素的第 index 个点
    - void SetPoints(const std::shared_ptr<Point<N>>* points)
        设置元素的所有点
    - const std::shared_ptr<Point<N>>& GetPoint(std::size_t index) const
        获取元素的第 index 个点
    - const std::shared_ptr<Point<N>>& operator[](std::size_t index) const
        重载下标运算符，获取元素的第 index 个点
    - const std::vector<std::shared_ptr<Point<N>>> GetPointsVector() const
        获取元素的所有点所构成的向量
    - void ChangePoint(std::size_t index, const std::share_ptr<Point<N>>& point)
        更改元素的第 index 个点
    - static bool IsSame(const Element<N, P>& e1, const Element<N, P>& e2)
        判断两个元素是否相同
    - bool IsSame(const Element<N, P>& other) const
        判断当前元素是否与另一个元素相同
    - bool IsSame(const Point<N>* points) const
        判断当前元素是否与给定的点数组相同
    - bool IsSame(const std::shared_ptr<Point<N>>* points) const
        判断当前元素是否与给定的点的智能指针数组相同
    - virtual std::string ToString() const
        将元素转换为字符串
    - bool operator==(const Element<N, P>& other) const
        重载等于运算符
    - bool operator!=(const Element<N, P>& other) const
        重载不等于运算符
    - friend std::ostream& operator<<(std::ostream& stream,
                                      const Element<N, P>& element)
        重载输出流运算符
Created by 朱昊东 on 2024/7/24
【更改记录】 无
*******************************************************************************/
template <std::size_t N, std::size_t P>
class Element {
    public:
        /***********************************************************************
        【函数名称】 Element
        【函数功能】 构造函数，使用给定的点数组初始化元素
        【参数】 
            - std::shared_ptr<Point<N>>* points（输入参数）:
            指向 Point<N> 对象的数组
        【返回值】 无
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无
        ***********************************************************************/
        Element(const std::shared_ptr<Point<N>>* points) {
            SetPoints(points);
        }


        /***********************************************************************
        【函数名称】 Element
        【函数功能】 拷贝构造函数，使用另一个 Element 对象初始化元素
        【参数】 
            - const Element<N, P>& other（输入参数）：另一个 Element 对象
        【返回值】 无
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无
        ***********************************************************************/
        Element(const Element<N, P>& other) {
            SetPoints(other.m_Points);
        }

        /***********************************************************************
        【函数名称】 operator=
        【函数功能】 赋值操作符，赋值另一个 Element 对象
        【参数】
            - const Element<N, P>& other（输入参数）：另一个 Element 对象
        【返回值】 Element<N, P>&: 当前对象的引用
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无
        ***********************************************************************/
        Element<N, P>& operator=(const Element<N, P>& other) {
            if (this != &other) {
                SetPoints(other.m_Points);
            }
            return *this;
        }

        /***********************************************************************
        【函数名称】 ~Element
        【函数功能】 虚析构函数
        【参数】 无
        【返回值】 无
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无
        ***********************************************************************/
        virtual ~Element() = default;

        /***********************************************************************
        【函数名称】 IsValid
        【函数功能】 验证点数组是否有效（没有重复的点）
        【参数】 
            - const Point<N>* points（输入参数）：指向 Point<N> 对象的数组  
        【返回值】 bool: 返回布尔值，表示点数组是否有效
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无 
        ***********************************************************************/
        static bool IsValid(const Point<N>* points) {
            for (int i = 0; i < P; i++) {
                for (int j = i + 1; j < P; j++) {
                    if (points[i] == points[j]) return false;
                }
            }
            return true;
        }

        /***********************************************************************
        【函数名称】 IsValid
        【函数功能】 验证共享指针数组是否有效（没有重复的点）
        【参数】 
            - const std::shared_ptr<Point<N>>* points（输入参数）：指向 Point<N>
             对象的共享指针数组
        【返回值】 bool: 返回布尔值，表示共享指针数组是否有效
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无
        ***********************************************************************/
        static bool IsValid(const std::shared_ptr<Point<N>>* points) {
            for (int i = 0; i < P; i++) {
                for (int j = i + 1; j < P; j++) {
                    if (*points[i] == *points[j]) return false;
                }
            }
            return true;
        }

        /***********************************************************************
        【函数名称】 IsValid
        【函数功能】 验证 Element 对象是否有效（没有重复的点）
        【参数】 
            - const Element<N, P>& element（输入参数）：Element 对象
        【返回值】 bool: 返回布尔值，表示 Element 对象是否有效
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无 
        ***********************************************************************/
        static bool IsValid(const Element<N, P>& element) {
            return IsValid(element.m_Points);
        }

        /***********************************************************************
        【函数名称】 SetPoint
        【函数功能】 设置指定索引处的点
        【参数】 
            - std::size_t index（输入参数）：点的索引
            - const std::shared_ptr<Point<N>>& point（输入参数）：要设置的点
        【返回值】 无
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无
        ***********************************************************************/
        void SetPoint(std::size_t index,
                      const std::shared_ptr<Point<N>>& point) {
            if (index >= P) {
                throw ExceptionIndexOutOfBounds(index);
            }
            m_Points[index] = point;
        }

        /***********************************************************************
        【函数名称】 SetPoints
        【函数功能】 设置点数组
        【参数】 
            - const std::shared_ptr<Point<N>>* points（输入参数）：
            指向 Point<N> 对象的数组
        【返回值】 无
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无 
        ***********************************************************************/
        void SetPoints(const std::shared_ptr<Point<N>>* points) {
            for (int i = 0; i < P; i++) {
                SetPoint(i, points[i]);
            }
            if(!IsValid(points)){
                throw ExceptionIdenticalPoint();
            }
        }

        /***********************************************************************
        【函数名称】 GetPoint
        【函数功能】 获取指定索引处的点
        【参数】 
            - std::size_t index（输入参数）：点的索引
        【返回值】 std::shared_ptr<Point<N>>: 返回指定索引处的点的共享指针
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无 
        ***********************************************************************/
        const std::shared_ptr<Point<N>>& GetPoint(std::size_t index) const {
            if (index >= P) {
                throw ExceptionIndexOutOfBounds(index);
            }
            return m_Points[index];
        }

        /***********************************************************************
        【函数名称】 operator[]
        【函数功能】 获取指定索引处的点
        【参数】 
            - std::size_t index（输入参数）：点的索引
        【返回值】 std::shared_ptr<Point<N>>: 返回指定索引处的点的共享指针
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无 
        ***********************************************************************/
        const std::shared_ptr<Point<N>>& operator[](std::size_t index) const {
            return GetPoint(index);
        }

        /***********************************************************************
        【函数名称】 GetPointsVector
        【函数功能】 获取点的向量
        【参数】 无
        【返回值】 std::vector<std::shared_ptr<Point<N>>>: 返回点的向量
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无
        ***********************************************************************/
        const std::vector<std::shared_ptr<Point<N>>> GetPointsVector() const {
            return std::vector<std::shared_ptr<Point<N>>>(m_Points, 
                                                          m_Points + P);
        }

        /***********************************************************************
        【函数名称】 ChangePoint
        【函数功能】 更改指定索引处的点
        【参数】 
            - std::size_t index（输入参数）：点的索引
            - const std::shared_ptr<Point<N>>& point（输入参数）：要设置的点
        【返回值】 无
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无
        ***********************************************************************/
        void ChangePoint(std::size_t index, 
                         const std::shared_ptr<Point<N>>& point) {
            if (index >= P) {
            throw ExceptionIndexOutOfBounds(index);
            }
            for (int i = 0; i < P; i++) {
                if (i == index) continue;
                if (*m_Points[i] == *point) throw ExceptionIdenticalPoint();
            }//for loop 保证设置点不与其他点重合
            m_Points[index] = point;
        }

        /***********************************************************************
        【函数名称】 IsSame
        【函数功能】 判断两个 Element 对象是否相同
        【参数】    
            - const Element<N, P>& e1（输入参数）：第一个 Element 对象
            - const Element<N, P>& e2（输入参数）：第二个 Element 对象
        【返回值】 bool: 返回布尔值，表示两个 Element 对象是否相同
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无
        ***********************************************************************/
        static bool IsSame(const Element<N, P>& e1, const Element<N, P>& e2) {
            for (size_t i = 0; i < P; i++) {
                if (!Point<N>::IsSame(*e1.m_Points[i], *e2.m_Points[i])) {
                    return false;
                }
            }
            return true;
        }


        /***********************************************************************
        【函数名称】 IsSame
        【函数功能】 判断当前对象与另一个 Element 对象是否相同
        【参数】 
            - const Element<N, P>& other（输入参数）：另一个 Element 对象
        【返回值】 bool: 返回布尔值，表示当前对象与另一个 Element 对象是否相同
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无 
        ***********************************************************************/
        bool IsSame(const Element<N, P>& other) const {
            return IsSame(*this, other);
        }

        /***********************************************************************
        【函数名称】 IsSame
        【函数功能】 判断当前对象与点数组是否相同
        【参数】
            - const Point<N>* points（输入参数）：指向 Point<N> 对象的数组
        【返回值】 bool: 返回布尔值，表示当前对象与点数组是否相同
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无
        ***********************************************************************/
        bool IsSame(const Point<N>* points) const {
            for (int i = 0; i < P; i++) {
                if (*m_Points[i] != points[i]) {
                    return false;
                }
            }
            return true;
        }

        /***********************************************************************
        【函数名称】 IsSame
        【函数功能】 判断当前对象与点的智能指针数组是否相同
        【参数】 
            - const std::shared_ptr<Point<N>>* points（输入参数）：
        【返回值】 bool: 返回布尔值，表示当前对象与点的智能指针数组是否相同
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无
        ***********************************************************************/
        bool IsSame(const std::shared_ptr<Point<N>>* points) const {
            return IsSame(Element<N, P>(points));
        }

        /***********************************************************************
        【函数名称】ToString
        【函数功能】将元素转换为字符串
        【参数】 无
        【返回值】 std::string: 元素的字符串表示
        Created by 朱昊东 on 2024/7/24
        【更改记录】 无
        ***********************************************************************/
        virtual std::string ToString() const {
            std::ostringstream stream;
            stream << "[ ";
            for (int i = 0; i < P; i++) {
                stream << *m_Points[i] << " ";
            }
            stream << "]";
            return stream.str();
        }

        /***********************************************************************
        【函数名称】 operator==
        【函数功能】 相等运算符重载，判断两个元素是否相同
        【参数】 
            - const Element<N, P>& other (输入参数): 另一个元素
        【返回值】 bool: 如果两个点相同则返回 true，否则返回 false
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        bool operator==(const Element<N, P>& other) const {
            return IsSame(other);
        }
        /***********************************************************************
        【函数名称】 operator!=
        【函数功能】 不等运算符重载，判断两个元素是否不同
        【参数】 
            - const Element<N, P>& other (输入参数): 另一个元素
        【返回值】 bool: 如果两个点不同则返回 true，否则返回 false
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        bool operator!=(const Element<N, P>& other) const {
            return !IsSame(other);
        }

        /***********************************************************************
        【函数名称】 operator<<
        【函数功能】 输出点的字符串表示
        【参数】 
            - std::ostream& stream (输入参数): 输出流
            - const Element<N, P>& element (输入参数): 元素
        【返回值】 std::ostream&: 输出流
        Created by 朱昊东 on 2024/7/23
        【更改记录】 无
        ***********************************************************************/
        friend std::ostream& operator<<(std::ostream& stream,
                                        const Element<N, P>& element) {
            stream << element.ToString();
            return stream;
        }

    protected:
        Element() = default;
        std::shared_ptr<Point<N>> m_Points[P];
};


#endif // ELEMENT_HPP