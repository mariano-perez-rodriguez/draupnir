#include <iostream>

using namespace std;

static void showLogo() {
  cout << "\n"
          "---------------------------\n"
          "   /\\                      \n"
          "   \\/  Draupnir v0.0.1     \n"
          "   /\\                      \n"
          "---------------------------\n"
          "\n";
}

int main(int argc, char *argv[]) {
  showLogo();

  cout << "Arguments:" << endl;
  for (int i = 0; i < argc; i++) {
    cout << "  " << i << ": " << argv[i] << endl;
  }

  return 0;
}
