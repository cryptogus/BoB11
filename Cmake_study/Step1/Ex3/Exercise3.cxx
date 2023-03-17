#include "Exercise3.h"

int main(int argc, char *argv[])
{   
    if (argc < 2) {
    // report version
    std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }
    printf("Cmake second succes\n");
    return 0;
}