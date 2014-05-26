#ifndef DESTINATION_COLLECTION_H
#define DESTINATION_COLLECTION_H

#include <vector>
#include <string>
#include "destination.h"

using namespace std;

class DestinationCollection
{
  private:
    vector<Destination> destinations;
    string currency;

  public:
    DestinationCollection();

    int add(string name, float price);
    void remove(int key);
    void clear();
    int count() const;

    Destination operator[](int key) const;
};

ostream& operator<<(ostream& output, const DestinationCollection& destinations);

#endif
