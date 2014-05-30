#ifndef TICKET_MACHINE_H
#define TICKET_MACHINE_H

#include <string>
#include "destination_collection.h"
#include "price_computer.h"
#include "refound_computer.h"
#include "coin_slot.h"

using namespace std;

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
    bool is_running();

  private:
    void init_destinations();
    void init_coin_slot();
};

#endif
