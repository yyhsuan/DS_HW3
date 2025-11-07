// 11327101陳怡瑄 11327102林姿妤

#include <fstream> // 建立/寫入檔案	讀取檔案
#include <iostream>
#include <string>
// 建立/寫入檔案	用 ofstream	ofstream file("a.txt")
// 讀取檔案	用 ifstream	ifstream file("a.txt")
class Maze {
 private:
  int row;
  int column;
  char *grid;

 public:
  void initial(int r, int c) {    // 看要不要改成建構子
    row = r;
    column = c;
    grid = new char[row * column];
  }
  
};

class Stack {
 private:
 
 public:

};

void Start() {
  std::cout << "*** (^_^) Data Structure (^o^) ***" << std::endl;
  std::cout << "*** Find the Goal(s) in a Maze ***" << std::endl;
  std::cout << "* 0. Quit                        *" << std::endl;
  std::cout << "* 1. Find one goal               *" << std::endl;
  std::cout << "* 2. Find goal(s) as requested   *" << std::endl;
  std::cout << "* 3. How many goals?             *" << std::endl;
  std::cout << "* 4. Shortest path to one goal   *" << std::endl;
  std::cout << "**********************************" << std::endl;
  std::cout << "Input a command: " << std::endl;
}

int main() {
  std::ifstream infile("123.txt"); // 測試讀檔 github不能run 成功

  if ( infile ) {
    std::cout << " uuuuu ";
  }


  return 0;

}








