#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <memory>
#include <string>
#include <vector>
#include "Point.hpp"
#include "../Errors.hpp"

template <std::size_t N, std::size_t P>
class Element {
public:
    Element(const std::shared_ptr<Point<N>>* points) {
        SetPoints(points);
    }

    Element(const Element<N, P>& other) {
        SetPoints(other.m_Points);
    }

    Element<N, P>& operator=(const Element<N, P>& other) {
        if (this != &other) {
            SetPoints(other.m_Points);
        }
        return *this;
    }

    virtual ~Element() = default;

    static bool IsValid(const Point<N>* points) {
        for (int i = 0; i < P; i++) {
            for (int j = i + 1; j < P; j++) {
                if (points[i] == points[j]) return false;
            }
        }
        return true;
    }

    static bool IsValid(const std::shared_ptr<Point<N>>* points) {
        for (int i = 0; i < P; i++) {
            for (int j = i + 1; j < P; j++) {
                if (*points[i] == *points[j]) return false;
            }
        }
        return true;
    }

    static bool IsValid(const Element<N, P>& element) {
        return IsValid(element.m_Points);
    }

    void SetPoint(std::size_t index, const std::shared_ptr<Point<N>>& point) {
        if (index >= P) {
            throw ExceptionIndexOutOfBounds(index);
        }
        m_Points[index] = point;
    }

    void SetPoints(const std::shared_ptr<Point<N>>* points) {
        for (int i = 0; i < P; i++) {
            SetPoint(i, points[i]);
        }
        if(!IsValid(points)){
            throw ExceptionIdenticalPoint();
        }
    }

    const std::shared_ptr<Point<N>>& GetPoint(std::size_t index) const {
        if (index >= P) {
            throw ExceptionIndexOutOfBounds(index);
        }
        return m_Points[index];
    }

    const std::shared_ptr<Point<N>>& operator[](std::size_t index) const {
        return GetPoint(index);
    }

    const std::vector<std::shared_ptr<Point<N>>> GetPointsVector() const {
        return std::vector<std::shared_ptr<Point<N>>>(m_Points, m_Points + P);
    }

    void ChangePoint(std::size_t index, const std::shared_ptr<Point<N>>& point) {
        if (index >= P) {
        throw ExceptionIndexOutOfBounds(index);
        }
        for (int i = 0; i < P; i++) {
            if (i == index) continue;
            if (*m_Points[i] == *point) throw ExceptionIdenticalPoint();
        }//for loop 保证设置点不与其他点重合
        m_Points[index] = point;
    }

    static bool IsSame(const Element<N, P>& e1, const Element<N, P>& e2) {
        for (size_t i = 0; i < P; i++) {
            if (!Point<N>::IsSame(*e1.m_Points[i], *e2.m_Points[i])) {
                return false;
            }
        }
        return true;
    }

    bool IsSame(const Element<N, P>& other) const {
        return IsSame(*this, other);
    }

    bool IsSame(const Point<N>* points) const {
        for (int i = 0; i < P; i++) {
            if (*m_Points[i] != points[i]) {
                return false;
            }
        }
        return true;
    }

    bool IsSame(const std::shared_ptr<Point<N>>* points) const {
        return IsSame(Element<N, P>(points));
    }

    virtual std::string ToString() const {
        std::ostringstream stream;
        stream << "[ ";
        for (int i = 0; i < P; i++) {
            stream << *m_Points[i] << " ";
        }
        stream << "]";
        return stream.str();
    }

    bool operator==(const Element<N, P>& other) const {
        return IsSame(other);
    }

    bool operator!=(const Element<N, P>& other) const {
        return !IsSame(other);
    }

    friend std::ostream& operator<<(std::ostream& stream, const Element<N, P>& element) {
        stream << element.ToString();
        return stream;
    }

protected:
    Element() = default;
    std::shared_ptr<Point<N>> m_Points[P];
};


#endif // ELEMENT_HPP