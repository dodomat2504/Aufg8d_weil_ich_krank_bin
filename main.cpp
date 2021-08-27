#include <iostream>
#include "dlist.h"


int main() {
    DList<int> zahlen;

    zahlen.push_back(10);
    zahlen.push_front(11);
    zahlen.push_back(12);

    for (int i = 0; i < 3; i++) {
        std::cout << "Wert: '" << zahlen.getAt(i) << "'" << std::endl;
    }
    std::cout << std::endl;

    zahlen.pop_back();
    zahlen.pop_front();

    std::cout << "Wert: '" << zahlen.getAt(0) << "'" << std::endl << std::endl;

    zahlen.pop_front();



    DList<std::string> l;
    l.push_back("ist");
    l.push_front("Dominik");
    l.push_back("mies");
    l.push_back("coden.");
    l.insert("am", 3);

    for (int i = 0; i < l.getLength(); i++) {
        std::cout << "Wert: '" << l.getAt(i) << "'" << std::endl;
    }

    std::cout << "Inverted:" << std::endl;

    l.invert();

    for (int i = 0; i < l.getLength(); i++) {
        std::cout << "Wert: '" << l.getAt(i) << "'" << std::endl;
    }

    l.remove("coden.");
    l.removeAt(2);
    l.pop_back();
    l.insert("Smartpointer", 0);
    l.push_back("sein.");
    l.remove("am");
    l.insert("können", 1);

    for (int i = 0; i < l.getLength(); i++) {
        std::cout << "Wert: '" << l.getAt(i) << "'" << std::endl;
    }

    l.invert();

    for (int i = 0; i < l.getLength(); i++) {
        std::cout << "Wert: '" << l.getAt(i) << "'" << std::endl;
    }

    return 0;
}
