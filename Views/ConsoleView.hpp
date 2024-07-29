#ifndef CONSOLE_VIEW_HPP
#define CONSOLE_VIEW_HPP


#include "../Controllers/Controller.hpp"
#include "AbstractView.hpp"

class ConsoleView: public AbstractView {
    public:
        ConsoleView() = default;
        void Run(Controller& controller) const override;
    private:
        bool LoadModel(Controller& controller, std::string* path) const;
        void SaveModel(const Controller& controller, std::string defaultPath) const;
        void ShowHelp() const;
        void ShowStatistics(const Controller& controller) const;
        void ListFaces(const Controller& controller) const;
        void ListFace_sPoints(const Controller& controller) const;
        void AddFace(Controller& controller) const;
        void RemoveFace(Controller& controller) const;
        void ModifyFace(Controller& controller) const;
        void ListLines(const Controller& controller) const;
        void ListLine_sPoints(const Controller& controller) const;
        void AddLine(Controller& controller) const;
        void RemoveLine(Controller& controller) const;
        void ModifyLine(Controller& controller) const;
};


#endif // CONSOLE_VIEW_HPP