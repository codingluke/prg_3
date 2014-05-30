/**
 * TicketMachine is a simulation of a TicketMachine. It lets Users
 * chose of a list of destinations and prompts them to pai a certain
 * price. They have to enter the price out of a selection of certain
 * coin (values). The TicketMachine tells them after every insert how
 * much they already have paied and how much they have to pai more until
 * the price is reached.
 * When the price is reached, they are getting prompted to take out the
 * ticket from the ticket slot. When they paied more than the price of
 * the ticket, their refound will be calculated out of the accepted coins
 * and gets printed to the console.
 * With the coin 0.00 they can abort the paiment. When they chose the destination -1 the TicketMachine will shut down. This action is not
 * printed to the console, because its a hidde action just for engineers.
 *
 * @author  Lukas Hodel
 */

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
bool TicketMachine::is_running()
{
  return running;
}

/**
 * Initialsation of the default destinations.
 */
//void TicketMachine::init_destinations()
//{
  //destinations.add("Kitzbuel", 11.20);
  //destinations.add("Nenzlingen", 23.00);
  //destinations.add("Ostermundingen", 2.30);
  //destinations.add("Hinterduggingen", 9.20);
  //destinations.add("Schweinsfurt", 8.90);
  //destinations.add("Entenhausen", 60.00);
  //destinations.add("Matterhorn", 51.50);
  //destinations.add("Schwaebische alm", 1.00);
  //destinations.add("Teufeldberg", 6.60);
  //destinations.add("Niderbuepp", 14.10);
  //destinations.add("Burgdorf", 3.70);
//}
