// 11327101陳怡瑄 11327102林姿妤
#include <fstream>
#include <iostream>
#include <string>
// 建立/寫入檔案	用 ofstream	ofstream file("a.txt")
// 讀取檔案	用 ifstream	ifstream file("a.txt")
class Maze {
 private:
  int row;
  int column;
  char *grid;   // 這不知道對不對 反正要有上面那兩個?

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
  std::ifstream infile("301.txt"); // 測試讀檔 github不能run
  if ( infile ) {
    std::cout << " uuuuu " << std::endl;
    /*
    std::string line;  // ← 這裡宣告一個變數 line
    
    while (getline(infile, line)) {  // 讀取檔案的一行到 line
      std::cout << line << std::endl;        // 印出這一行
    }
    */
    char c;
    while (infile.get(c)) {   // 每次讀一個字元到 c
      std::cout << c;            // 直接印出
    }
    infile.close();               // 關閉檔案
  }


  return 0;

}



