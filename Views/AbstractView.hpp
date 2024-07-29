#ifndef ABSTRACT_VIEW_HPP
#define ABSTRACT_VIEW_HPP

#include "../Controllers/Controller.hpp"

class AbstractView {
    public:
        virtual void Run(Controller& controller) const = 0;
};

#endif // ABSTRACT_VIEW_HPP