#include "ticket_machine.h"
#include "destination_collection.h"

using namespace std;

/**
 * Entrypoint to the program "Fahrkartenautomat".
 * Creates and starts an Instance of TicketMachine with
 * Euro as currency and a list of accepted coins for
 * the paiment.
 */
int main()
{
  // Vector with accepted coins for the Machine
  vector<double> coins;
  coins.push_back(50);
  coins.push_back(20);
  coins.push_back(10);
  coins.push_back(5);
  coins.push_back(2);
  coins.push_back(1);
  coins.push_back(0.5);
  coins.push_back(0.1);
  coins.push_back(0.0);
  // DestinationCollection with the available
  // destinations
  DestinationCollection destinations("Euro");
  destinations.add("Kitzbuel", 11.20);
  destinations.add("Nenzlingen", 23.00);
  destinations.add("Ostermundingen", 2.30);
  destinations.add("Hinterduggingen", 9.20);
  destinations.add("Schweinsfurt", 8.90);
  destinations.add("Entenhausen", 60.00);
  destinations.add("Matterhorn", 51.50);
  destinations.add("Schwaebische alm", 1.00);
  destinations.add("Teufeldberg", 6.60);
  destinations.add("Niderbuepp", 14.10);
  destinations.add("Burgdorf", 3.70);
  // Create an Instance for the accepted coins and destinations.
  TicketMachine ticket_machine("Luki's Menschentransporte e.V.",
                               "Euro", coins, destinations);
  ticket_machine.run();
}
