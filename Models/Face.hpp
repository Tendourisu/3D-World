#ifndef FACE_HPP
#define FACE_HPP

#include <cmath>
#include <memory>
#include <ostream>
#include <string>
#include "Element.hpp"
#include "Point.hpp"

template <std::size_t N>
class Face: public Element<N, 3> {
    public:
        Face(
            const std::shared_ptr<Point<N>>& first,
            const std::shared_ptr<Point<N>>& second,
            const std::shared_ptr<Point<N>>& third
        ) {
            std::shared_ptr<Point<N>> points[] = { first, second, third };
            this->SetPoints(points);
        }

        Face(const std::shared_ptr<Point<N>>* points) {
            this->SetPoints(points);
        }

        Face(const Face<N>& other): Element<N, 3>(other) {}

        Face<N>& operator=(const Face<N>& other){
            if (this != &other) {
                Element<N, 3>::operator=(other);
            }
            return *this;
        }

        ~Face() override = default;
                

        const std::shared_ptr<Point<N>>& First  { Element<N, 3>::m_Points[0] };
        const std::shared_ptr<Point<N>>& Second  { Element<N, 3>::m_Points[1] };
        const std::shared_ptr<Point<N>>& Third  { Element<N, 3>::m_Points[2] };

        void SetFirst(const std::shared_ptr<Point<N>>& first){
            this->SetPoint(0, first);
        }
        void SetSecond(const std::shared_ptr<Point<N>>& second){
            this->SetPoint(1, second);
        }
        void SetThird(const std::shared_ptr<Point<N>>& third){
            this->SetPoint(2, third);
        }
        double GetArea() const{
            double a = Point<N>::Distance(*First, *Second);
            double b = Point<N>::Distance(*Second, *Third);
            double c = Point<N>::Distance(*Third, *First);
            double p = (a + b + c) / 2;
            return std::sqrt(p * (p - a) * (p - b) * (p - c));

        }

        std::string ToString() const override{
            std::ostringstream stream;
            stream << "Face ";
            stream << Element<N, 3>::ToString();
            return stream.str();
        } 
    protected:
        Face() = default;   
};

#endif // FACE_HPP