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

  void load(std::ifstream &infile) { // 載入迷宮資料
    char ch;
    int r = 0;
    int c = 0;
    while (infile.get(ch)) {   // 每次讀一個字元到 c
      if ( ch != '\n' ) {
        grid[r * column + c] = ch;
        c++;
      }

      else {
        r++;
        c = 0;
      }       
    }
    return;
  }

  void print() { // 印出迷宮資料
    for (int r = 0; r < row; r++) {
      for (int c = 0; c < column; c++) {
        std::cout << grid[r * column + c];
    }
      if ( r > 0 ) {
        std::cout << "\n";
      }
    }
    return;
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
  Maze a;
  if ( infile ) {
    int x;
    int y;
    infile >> x >> y; // 讀int x,y
    a.initial(x, y);
    a.load(infile);
    a.print();
    infile.close();               // 關閉檔案
  }


  return 0;

}


