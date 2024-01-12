#include <iostream>

int main(int argc, char **argv) {
  if (argc == 2) {
    std::cout << argv[0];
    std::cout << argv[1];
  } else {
    std::cout << "demo: ./fcsearch directory content \n";
  }
}
