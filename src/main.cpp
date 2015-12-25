#include "Draupnir.h"
#include "Random.h"


#include <iostream>

using namespace std;

/**
 * Print the Draupnir logo to cerr
 *
 */
static void showLogo() {
  cerr << "\n"
          "---------------------------\n"
          "   /\\                      \n"
          "   \\/  Draupnir v0.0.1     \n"
          "   /\\                      \n"
          "---------------------------\n"
          "\n";
}


int main(int argc, char *argv[]) {
  showLogo();

  cerr << "Arguments:" << endl;
  for (int i = 0; i < argc; i++) {
    cerr << "  " << i << ": " << argv[i] << endl;
  }
  cerr << endl;

  Draupnir::CrcSponge64 d = Draupnir::CrcSponge64Builder();

  while (true) {
    cout << d.squeeze();
  }
  return 0;
}

