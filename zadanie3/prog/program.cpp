#include <iostream>
#include <matrix.h>
#include <fstream>

using namespace std;

int main(){
  // displays readme
  ifstream readme;
  readme.open("../README");

  while(!readme.eof()){
    char buf[1000];
    readme.getline(buf, 1000);
    cout << buf << "\n";
  }

  readme.close();
  return 0;
}
