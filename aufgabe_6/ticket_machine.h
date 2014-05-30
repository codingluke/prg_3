#ifndef TICKET_MACHINE_H
#define TICKET_MACHINE_H

#include <string>
#include "destination_collection.h"
#include "price_computer.h"
#include "refound_computer.h"
#include "coin_slot.h"

using namespace std;

/**
 * TicketMachine is a simulation of a TicketMachine. It lets Users
 * chose of a list of destinations and prompts them to pay a certain
 * price. They have to enter the price out of a selection of certain
 * coin (values). The TicketMachine tells them after every insert how
 * much they already have paied and how much they have to pay more until
 * the price is reached.
 * When the price is reached, they are getting prompted to take out the
 * ticket from the ticket slot. When they paied more than the price of
 * the ticket, their refound will be calculated out of the accepted coins
 * and gets printed to the console.
 * With the coin 0.00 they can abort the paiment. When they chose the destination -1 the TicketMachine will shut down. This action is not
 * printed to the console, because its a hidde action just for engineers.
 *
 * @author  Lukas Hodel
 * @version 1.0
 */
class TicketMachine
{
  private:
    DestinationCollection destinations;
    CoinSlot coin_slot;
    RefoundComputer refound;
    string currency;
    string name;
    bool running;

  public:
    TicketMachine(string a_name, string a_currency,
                  vector<double> accepted_coins,
                  DestinationCollection a_dest_collection);

    void run();
    bool is_running() const;
};

#endif
