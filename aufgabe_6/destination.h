#ifndef DESTINATION_H
#define DESTINATION_H

#include <string>

using namespace std;


/**
 * Represents a destination for a ticket machine.
 */
struct Destination
{
  string name;
  float price;
  string currency;
};

#endif
