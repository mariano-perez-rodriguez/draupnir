#include <iostream>

#include "Draupnir.h"

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

  DraupnirCrc64 d = Draupnir::crc64();

  while (true) {
    cout << d.getByte();
  }

  return 0;
}

