#include <iostream>

#include "DraupnirCrc64.h"

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

  cerr << sizeof(unsigned char) << endl;
  cerr << sizeof(unsigned short) << endl;
  cerr << sizeof(unsigned) << endl;
  cerr << sizeof(unsigned long) << endl;
  cerr << sizeof(unsigned long long) << endl;
return 0;
  Draupnir::Crc64 d = Draupnir::crc64();

  while (true) {
    cout << d.getByte();
  }

  return 0;
}

