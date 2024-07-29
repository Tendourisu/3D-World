#pragma once

#include <stdexcept>

class ExceptionIndexOutOfBounds: public std::invalid_argument {
    public:
        ExceptionIndexOutOfBounds(std::size_t index): invalid_argument("Index out of bounds."), m_Index(index) {}
        const std::size_t& Index { m_Index };
    private:
        std::size_t m_Index;
};

class ExceptionDowngrade: public std::invalid_argument {
    public:
        ExceptionDowngrade(): invalid_argument("Cannot downgrade point dimension.") {}
};

class ExceptionFileExtension: public std::invalid_argument {
    public:
        ExceptionFileExtension(): invalid_argument("Invalid file extension.") {}
};

class ExceptionFileOpen: public std::invalid_argument {
    public:
        ExceptionFileOpen(): invalid_argument("Cannot open specific file.") {}
};
 
class ExceptionFileFormat: public std::invalid_argument {
    public:
        ExceptionFileFormat(): invalid_argument("File contains invalid format.") {}
};

class ExceptionIdenticalPoint: public std::invalid_argument {
    public: 
        ExceptionIdenticalPoint(): invalid_argument("Two of provided points are the same.") {}
};

class ExceptionIdenticalElement: public std::invalid_argument {
    public:
        ExceptionIdenticalElement(): invalid_argument("Element coincides with existing ones.") {}
};

class ExceptionOnlyOneInstance: public std::invalid_argument {
    public:
        ExceptionOnlyOneInstance(): invalid_argument("Only one module is allowed to be created.") {}
};