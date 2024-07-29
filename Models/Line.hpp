#ifndef LINE_HPP
#define LINE_HPP

#include <memory>
#include <ostream>
#include <string>
#include "Element.hpp"
#include "Point.hpp"

template <std::size_t N>
class Line: public Element<N, 2> {
    public:
        Line(
            const std::shared_ptr<Point<N>>& first,
            const std::shared_ptr<Point<N>>& second
        ){
            std::shared_ptr<Point<N>> points[] = { first, second };
            this->SetPoints(points);
        }

        Line(const std::shared_ptr<Point<N>>* points) {
            this->SetPoints(points);
        }

        Line(const Line<N>& other): Element<N, 2>(other) {}

        Line<N>& operator=(const Line<N>& other){
            if (this != &other) {
                Element<N, 2>::operator=(other);
            }
            return *this;
        }

        ~Line() override = default;
                
        const std::shared_ptr<Point<N>>& First  { Element<N, 2>::m_Points[0] };
        const std::shared_ptr<Point<N>>& Second  { Element<N, 2>::m_Points[1] };

        void SetFirst(const std::shared_ptr<Point<N>>& first){
            this->SetPoint(0, first);
        }
        void SetSecond(const std::shared_ptr<Point<N>>& second){
            this->SetPoint(1, second);
        }

        double GetLength() const{
        return Point<N>::Distance(*First, *Second);
        }

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