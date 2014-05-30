/**
 * DestinationCollection represents a collection of Destinations.
 * Destinations is a struct with the data fields name and price.
 *
 * @author  Lukas Hodel
 */

#include <iostream>
#include <iomanip>
#include "destination_collection.h"

using namespace std;

/**
 * Constructor without parameters initializes a empty
 * collection with the currency as "Euro".
 */
DestinationCollection::DestinationCollection()
{
  currency = "Euro";
}

/**
 * Constructor without parameters initializes a empty
 * collection with a given currency.
 */
DestinationCollection::DestinationCollection(string a_currency)
{
  currency = a_currency;
}

/**
 * Adds a new destination to the collection.
 *
 * @param name    Name of the destination.
 * @param price   Fare price to the destination.
 *
 * @return the new size of the collection counted from zero.
 */
int DestinationCollection::add(string name, float price)
{
  Destination dest = { name, price, currency };
  destinations.push_back(dest);
  return destinations.size() -1;
}

/**
 * Removes all the destinations from the collection.
 */
void DestinationCollection::clear()
{
  destinations.clear();
}

/**
 * Returns the size of the collection with the count start
 * of 1.
 *
 * @return size of the collection.
 */
int DestinationCollection::size() const
{
  return destinations.size();
}

/**
 * Overrides operator[]. Gives back the destination of the collection
 * at the index of the given key.
 *
 * @param key   Index of the destination to return.
 *
 * @return Destination at the index of the given key.
 */
Destination DestinationCollection::operator[](int key) const
{
  return destinations[key];
}

/**
 * Overrides operator<< "put to". Defines how to represent a
 * DestinationCollection when print out to the console.
 *
 * Vorhandene Fahrziele:
 * Ziffer   Fahrziel      Preis
 * 1        Fahrziel 1    10.00
 * 2        Fahrziel 2     5.00
 * ...
 *
 * @param output        IO output stream
 * @param destinations  The DestinationCollection to print to the console.
 *
 * @return the io output stream.
 */
ostream& operator<<(ostream& output, const DestinationCollection& destinations)
{
  output << "Vorhandene Fahrziele:" << endl;
  output << setw(8) << left << "Ziffer"
         << setw(20) << left << "Fahrziel"
         << setw(10) << right << "Preis" << endl
         << setw(43) << setfill('-') << "-" << setfill(' ') << endl;
  for(int i = 0; i < destinations.size(); i++)
  {
    Destination dest = destinations[i];
    output << setw(8) << left << (i + 1)
           << setw(20) << left << fixed << dest.name
           << setw(10) << right << setprecision(2) << fixed << dest.price
           << setw(5) << " " + dest.currency << endl;
  }
  return output;
}
