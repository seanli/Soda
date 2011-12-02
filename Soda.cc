#include "Soda.h"

using namespace std;

PRNG r; // Global random generator

void uMain::main() 
{
  ConfigParms cparam;
  string filePath = "Config.txt";
  processConfigFile(filePath.c_str(), cparam);
  
  cout << cparam.maxPurchases << endl;
}
