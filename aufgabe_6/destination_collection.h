#ifndef DESTINATION_COLLECTION_H
#define DESTINATION_COLLECTION_H

#include <vector>
#include <string>
#include "destination.h"

using namespace std;

/**
 * DestinationCollection represents a collection of Destinations.
 * Destinations is a struct with the data fields name and price.
 *
 * @author  Lukas Hodel
 * @version 1.0
 */
class DestinationCollection
{
  private:
    vector<Destination> destinations;
    string currency;

  public:
    DestinationCollection();
    DestinationCollection(const string& a_currency);

    int add(string name, float price);
    void remove(int key);
    void clear();
    int size() const;

    Destination operator[](int key) const;
};

ostream& operator<<(ostream& output, const DestinationCollection& destinations);

#endif
