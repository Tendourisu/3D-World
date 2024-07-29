#ifndef MODEL_HPP
#define MODEL_HPP

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include "Face.hpp"
#include "Line.hpp"
#include "Point.hpp"
#include "../Errors.hpp"

template <std::size_t N>
class Model {
    public:
        Model(std::string name = ""): m_Name(name) {}
        Model(const Model<N>& other) = delete;
        Model<N>& operator=(const Model<N>& other) = delete;
        virtual ~Model() = default;
        
        const std::string& Name { m_Name };
        const std::vector<std::shared_ptr<Line<N>>>& Lines { m_Lines };
        const std::vector<std::shared_ptr<Face<N>>>& Faces { m_Faces };

        void SetName(const std::string& name) {
            m_Name = name;
        }

        std::vector<std::shared_ptr<Point<N>>> CollectPoints() const{
            std::vector<std::shared_ptr<Point<N>>> points;

            auto addUniquePoints = [&](const auto& elements) {
                for (const auto& element : elements) {
                    for (const auto& point : element->GetPointsVector()) {
                        if (std::none_of(
                            points.begin(),
                            points.end(), 
                            [&](const auto& p) {return p == point;})) {
                            points.push_back(point);
                        }
                    }
                }
            };

            addUniquePoints(m_Lines);
            addUniquePoints(m_Faces);

            return points;
        }

        void AddLine(
            const Point<N>& first,
            const Point<N>& second
        ) {
            const Point<N> points[2] = { first, second };
            if (!Line<N>::IsValid(points)) {
                throw ExceptionIdenticalPoint();
            }
            for (auto line: m_Lines) {
                if (line->IsSame(points)) {
                    throw ExceptionIdenticalElement();
                }
            }
            Line<N> line(std::make_shared<Point<N>>(first), std::make_shared<Point<N>>(second));
            AddLineUnchecked(line);
        }

        void AddFace(
            const Point<N>& first,
            const Point<N>& second,
            const Point<N>& third
        ){
            const Point<N> points[3] = { first, second, third };
            if (!Face<N>::IsValid(points)) {
                throw ExceptionIdenticalPoint();
            }
            for (auto face: m_Faces) {
                if (face->IsSame(points)) {
                    throw ExceptionIdenticalPoint();
                }
            }
            Face<N> face(std::make_shared<Point<N>>(first), std::make_shared<Point<N>>(second), std::make_shared<Point<N>>(third));
            AddFaceUnchecked(face);
        }

        void AddLineUnchecked(const Line<N>& line){
            m_Lines.push_back(std::make_shared<Line<N>>(line));
        }

        void AddFaceUnchecked(const Face<N>& face){
            m_Faces.push_back(std::make_shared<Face<N>>(face));
        }

        void ModifyLine(
            std::size_t index,
            int pointIndex,
            const Point<N>& point
        ) {
            if(index >= m_Lines.size()){
                throw ExceptionIndexOutOfBounds(index);
            }
            m_Lines[index]->ChangePoint(pointIndex, std::make_shared<Point<N>>(point));
            for (int i = 0; i < m_Lines.size(); i++) {
                if (i != index && m_Lines[i]->IsSame(*m_Lines[index])) {
                    throw ExceptionIdenticalElement();
                }
            }

        }

        void ModifyFace(
            std::size_t index,
            int pointIndex,
            const Point<N>& point
        ) {
            if(index >= m_Faces.size()) {
                throw ExceptionIndexOutOfBounds(index);
            }
            m_Faces[index]->ChangePoint(pointIndex, std::make_shared<Point<N>>(point));
            for (int i = 0; i < m_Lines.size(); i++) {
                if (i != index && m_Lines[i]->IsSame(*m_Lines[index])) {
                    throw ExceptionIdenticalElement();
                }
            }
        }

        bool RemoveLine(std::size_t index) {
            if(index >= m_Lines.size()) {
                return false;
            }
            m_Lines.erase(m_Lines.begin() + index);
            return true;
        }

        bool RemoveFace(std::size_t index) {
            if(index >= m_Faces.size()) {
                return false;
            }
            m_Faces.erase(m_Faces.begin() + index);
            return true;
        }

        void Clear() {
            m_Lines.clear();
            m_Faces.clear();
        }

        double GetMinBoxVolume() const {
            double coordinates[2 * N];
            for (int i = 0; i < N; i++) {
                coordinates[2 * i] = std::numeric_limits<double>::max();// 初始化为极大值
                coordinates[2 * i + 1] = std::numeric_limits<double>::min();// 初始化为极小值
            }
            for (auto point: CollectPoints()) {
                for (int i = 0; i < N; i++) {
                    coordinates[2 * i] = std::min(coordinates[2 * i], point->GetCoordinate(i));
                    coordinates[2 * i + 1] = std::max(coordinates[2 * i + 1], point->GetCoordinate(i));
                }
            }
            double volume = 1;
            for (int i = 0; i < N; i++) {
                volume *= coordinates[2 * i + 1] - coordinates[2 * i];
            }
            return volume;
        }

    private:
        std::string m_Name;
        std::vector<std::shared_ptr<Line<N>>> m_Lines;
        std::vector<std::shared_ptr<Face<N>>> m_Faces;
};

#endif // MODEL_HPP