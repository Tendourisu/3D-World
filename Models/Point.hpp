#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>
#include <ostream>
#include <sstream>
#include <string>
#include "../Errors.hpp"

template <std::size_t N>
class Point {
    public:
        Point() {
            double zeros[N] = {0};
            SetCoordinates(zeros);
        }

        Point(const double* coordinates) {
            SetCoordinates(coordinates);
        }

        Point(const Point<N>& other): Point(other.m_Coordinates) {}

                
        Point<N>& operator=(const Point<N>& other) {
            if (this != &other) {
                SetCoordinates(other.m_Coordinates);
            }
            return *this;
        }

        virtual ~Point() = default;
        double GetCoordinate(std::size_t index) const {
            if (index >= N) {
                throw ExceptionIndexOutOfBounds(index);
            }
            return m_Coordinates[index];
        }

        double operator[](std::size_t index) const {
            return GetCoordinate(index);
        }

        void SetCoordinate(std::size_t index, double value) {
            if (index >= N) {
                throw ExceptionIndexOutOfBounds(index);
            }
            m_Coordinates[index] = value;
        }

        void SetCoordinates(const double* coordinates) {
            for (int i = 0; i < N; i++) {
                SetCoordinate(i, coordinates[i]);
            }
        }

        static bool IsSame(const Point<N>& p1, const Point<N>& p2) {
            for (int i = 0; i < N; i++) {
                if (std::fabs(p1.GetCoordinate(i) - p2.GetCoordinate(i)) > 1e-6) {
                    return false;
                }
            }
            return true;
        }
        bool IsSame(const Point<N> &other) const {
            return IsSame(*this, other);
        }

        template <std::size_t M>
        static double Distance(const Point<N> p1, const Point<M> p2) {
            if (N == M) {
                double sumOfSquares = 0;
                for (int i = 0; i < N; i++) {
                    sumOfSquares += std::pow(p1.GetCoordinate(i) - p2.GetCoordinate(i), 2);
                }
                return std::sqrt(sumOfSquares);
            }
            else if (N > M) {
                double sumOfSquares = 0;
                for (int i = 0; i < M; i++) {
                    sumOfSquares += std::pow(p1.GetCoordinate(i) - p2.GetCoordinate(i), 2);
                }
                for (int i = M; i < N; i++) {
                    sumOfSquares += std::pow(p1.GetCoordinate(i) , 2);
                }
                return std::sqrt(sumOfSquares);
            }
            else {
                double sumOfSquares = 0;
                for (int i = 0; i < N; i++) {
                    sumOfSquares += std::pow(p1.GetCoordinate(i) - p2.GetCoordinate(i), 2);
                }
                for (int i = M; i < M; i++) {
                    sumOfSquares += std::pow(p2.GetCoordinate(i) , 2);
                }
                return std::sqrt(sumOfSquares);
            }
        }
        
        template <std::size_t M>
        double Distance(const Point<M> &other) const {
            return Distance(*this, other);
        }

        
        virtual std::string ToString() const{
            std::ostringstream stream;
            stream << "[ ";
            for (int i = 0; i < N; i++) {
                stream << GetCoordinate(i) << " ";
            }
            stream << "]";
            return stream.str();//格式为[ 1 2 3 ]
        }

        bool operator==(const Point<N> &other) const {
            return IsSame(other);
        }

        bool operator!=(const Point<N> &other) const {
            return !IsSame(other);
        }

        friend std::ostream& operator<<(std::ostream& stream, const Point<N>& point) {
            stream << point.ToString();
            return stream;
        }

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