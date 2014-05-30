#include <string>
#include <iomanip>
#include "ticket_machine.h"
#include "destination_collection.h"
#include "price_computer.h"
#include "refound_computer.h"
#include "coin_slot.h"
#include "console_input.h"

using namespace std;

/**
 * Inizializes an TicketMachine instance with a given name, a given
 * currency and a list of accepted coins.
 *
 * @param a_name          Name of the TicketMachine for the welcome text.
 * @param a_currency      Currency of the price.
 * @param accepted_coins  List of accepted coins to pai the price.
 */
TicketMachine::TicketMachine(string a_name, string a_currency,
                             vector<double> accepted_coins,
                             DestinationCollection a_dest_collection)
{
  currency = a_currency;
  name = a_name;
  coin_slot = CoinSlot(a_currency, accepted_coins);
  refound = RefoundComputer(a_currency, accepted_coins);
  destinations = a_dest_collection;
}

/**
 * Starts the ticket machine. Handels the user interaction logic.
 */
void TicketMachine::run()
{
  running = true;
  int destination = -1;
  do
  {
    cout << "Willkommen beim " << name << endl << endl;
    cout << destinations << endl;
    destination = read_int("Bitte ein Fahrziel per Ziffer waehlen: ");
    if (destination > 0 && destination <= destinations.size())
    {
      destination--;
      Destination choice = destinations[destination];
      PriceComputer pc(choice.price, choice.currency);
      cout << "Ausgewaehltes Fahrziel: " << choice.name << endl;
      while(pc.state() < 0)
      {
        cout << pc << endl;
        cin >> coin_slot;
        pc.add(coin_slot.get_value());
      }
      if (pc.state() == 0)
      {
        cout << pc << endl;
        read_yes_no("Bitte entnehmen sie ihr Rückgeld!");
      }
      else if (pc.state() == 1)
        read_yes_no("Bitte entnehmen sie ihr Ticket!");
      else if (pc.state() == 2)
      {
        refound.set_refound(pc.remainder() * -1);
        cout << refound << endl;
        read_yes_no("Bitte entnehmen sie ihr Ticket!");
      }
    }
    cout << endl << endl;
  } while (destination != -1);
  cout << "Das System wird heruntergefahren!" << endl;
  running = false;
}

/**
 * Returns the state of the TicketMachine, if it is running
 * or not. Just importent when programming with multiple threads.
 *
 * @return true when the ticket machine is running.
 *         false when the ticket machine is not running.
 */
bool TicketMachine::is_running() const
{
  return running;
}
