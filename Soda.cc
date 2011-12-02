#include "Soda.h"

using namespace std;

void uMain::main() 
{
  ConfigParms cparam;
  string filePath = "Config.txt";
  processConfigFile(filePath.c_str(), cparam);
  
  cout << cparam.maxPurchases << endl;
}
