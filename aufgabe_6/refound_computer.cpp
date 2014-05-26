#include <iostream>
#include "refound_computer.h"

RefoundComputer::RefoundComputer(double a_refound)
{
  refound = a_refound;
  init_default_coins();
}

void RefoundComputer::init_default_coins()
{
  accepted_coins.push_back(50);
  accepted_coins.push_back(20);
  accepted_coins.push_back(10);
  accepted_coins.push_back(5);
  accepted_coins.push_back(1);
  accepted_coins.push_back(0.5);
  accepted_coins.push_back(0.1);
}

void RefoundComputer::calculate()
{
  while (refound > 0)
  {
    for(unsigned int i = 0; i < accepted_coins.size(); i++)
    {
      if (accepted_coins[i] <= refound)
      {
        refound -= accepted_coins[i];
        refound_in_coins.push_back(accepted_coins[i]);
      }
    }
  }
}



