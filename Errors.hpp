/*******************************************************************************
【文件名】 Errors.hpp
【功能模块和目的】 定义异常类
 Created by 朱昊东 on 2024/7/24
【更改记录】 
    2024/7/27 
    - 增添了文件扩展名异常类、文件打开异常类、文件格式异常类、重复点异常类、重复元素异常类
    2024/7/28 
    - 增添了单例模式异常类
*******************************************************************************/
#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>

/*******************************************************************************
【类名】 ExceptionIndexOutOfBounds
【功能】 索引越界异常类
【接口说明】
    - ExceptionIndexOutOfBounds(std::size_t index)
        构造函数，传入索引
Created by 朱昊东 on 2024/7/24
【更改记录】 无
*******************************************************************************/
class ExceptionIndexOutOfBounds: public std::invalid_argument {
    public:
        ExceptionIndexOutOfBounds(std::size_t index):
            invalid_argument("Index out of bounds."), m_Index(index) {}
        const std::size_t& Index { m_Index };
    private:
        std::size_t m_Index;
};

/*******************************************************************************
【类名】 ExceptionDowngrade
【功能】 降维异常类
【接口说明】
    - ExceptionDowngrade()
        构造函数
Created by 朱昊东 on 2024/7/24
【更改记录】 无
*******************************************************************************/
class ExceptionDowngrade: public std::invalid_argument {
    public:
        ExceptionDowngrade():
            invalid_argument("Cannot downgrade point dimension.") {}
};

/*******************************************************************************
【类名】 ExceptionFileExtension
【功能】 文件扩展名异常类
【接口说明】
    - ExceptionFileExtension()
        构造函数
Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
class ExceptionFileExtension: public std::invalid_argument {
    public:
        ExceptionFileExtension():
            invalid_argument("Invalid file extension.") {}
};

/*******************************************************************************
【类名】 ExceptionFileOpen
【功能】 文件打开异常类
【接口说明】
    - ExceptionFileOpen()
        构造函数
Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
class ExceptionFileOpen: public std::invalid_argument {
    public:
        ExceptionFileOpen():
            invalid_argument("Cannot open specific file.") {}
};
 
 /*******************************************************************************
【类名】 ExceptionFileFormat
【功能】 文件格式异常类
【接口说明】
    - ExceptionFileFormat()
        构造函数
Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
class ExceptionFileFormat: public std::invalid_argument {
    public:
        ExceptionFileFormat():
            invalid_argument("File contains invalid format.") {}
};

/*******************************************************************************
【类名】 ExceptionIdenticalPoint
【功能】 重复点异常类
【接口说明】
    - ExceptionIdenticalPoint()
        构造函数
Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
class ExceptionIdenticalPoint: public std::invalid_argument {
    public: 
        ExceptionIdenticalPoint():
            invalid_argument("Two of provided points are the same.") {}
};

/*******************************************************************************
【类名】 ExceptionIdenticalElement
【功能】 重复元素异常类
【接口说明】
    - ExceptionIdenticalElement()
        构造函数
Created by 朱昊东 on 2024/7/27
【更改记录】 无
*******************************************************************************/
class ExceptionIdenticalElement: public std::invalid_argument {
    public:
        ExceptionIdenticalElement():
            invalid_argument("Element coincides with existing ones.") {}
};

/*******************************************************************************
【类名】 ExceptionOnlyOneInstance
【功能】 单例模式异常类
【接口说明】
    - ExceptionOnlyOneInstance()
        构造函数
Created by 朱昊东 on 2024/7/28
【更改记录】 无
*******************************************************************************/
class ExceptionOnlyOneInstance: public std::invalid_argument {
    public:
        ExceptionOnlyOneInstance():
            invalid_argument("Only one module is allowed to be created.") {}
};

#endif // ERRORS_HPP