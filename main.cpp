
#include "Sort.cpp"

using namespace std;

int main(int argc, char** argv) {
  Sort *sorts = new Sort(argv[1]);
  sorts->runSorts();

  return 0;
}
