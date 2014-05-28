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
  output << "Vorhandene Fahrziele:" << endl;
  output << setw(8) << left << "Ziffer" << setw(20) << "Fahrziel"
         << "Preis" << endl << setw(35) << setfill('-') << "-" << endl;
  for(int i = 0; i < destinations.count(); i++)
  {
    Destination dest = destinations[i];
    output << setfill(' ') << setw(8) << left << (i + 1)
           << setw(20) << dest.name << setprecision(6) << dest.price << " "
           << dest.currency << endl;
  }
  return output;
}
