#include <iostream>
#include <iomanip>
#include "destination_collection.h"

using namespace std;

DestinationCollection::DestinationCollection()
{
  currency = "Euro";
}

int DestinationCollection::add(string name, float price)
{
  Destination dest = { name, price, currency };
  destinations.push_back(dest);
  return destinations.size() -1;
}

void DestinationCollection::clear()
{
  destinations.clear();
}

int DestinationCollection::count() const
{
  return destinations.size();
}

Destination DestinationCollection::operator[](int key) const
{
  return destinations[key];
}

ostream& operator<<(ostream& output, const DestinationCollection& destinations)
{
  output << "Bitte waehle ein Fahrziel:" << endl;
  output << setw(7) << left << "Nummer" << setw(20) << "Fahrziel"
         << "Preis" << endl;
  for(int i = 0; i < destinations.count(); i++)
  {
    Destination dest = destinations[i];
    output << setw(7) << left << (i + 1) << setw(20) << dest.name
           << dest.price << " " << dest.currency << endl;
  }
  return output;
}
