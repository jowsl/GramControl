#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

// Structure representing the technical data collected during field visits
struct Customer {
    std::string name;
    std::string phone;
    std::string address;
};

#endif