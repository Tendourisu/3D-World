#include <iostream>
#include "Controllers/Controller.hpp"
#include "Views/ConsoleView.hpp"
using namespace std;

int main() {
    ConsoleView view;
    Controller& controller = Controller::GetInstance();
    view.Run(controller);
    return 0;
}