#include <iostream>
#include "SynaesthetiQ-LED-Library/src/SynaesthetiQ/synaesthetiq.hpp"

int main()
{
    std::cout << "Turning off LEDs..." << std::endl;
    SynaesthetiQ* obj = new SynaesthetiQ();
    Colour offColour(0, 0, 0);
    obj->setBigLEDColour(offColour);
    obj->setMatrixColour(offColour);
    obj->render();
    delete obj;
    std::cout << "Exiting" << std::endl;
    return 0;
}
