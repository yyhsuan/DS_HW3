// 11327101陳怡瑄 11327102林姿妤
#include <fstream>
#include <iostream>
#include <string>
// 建立/寫入檔案	用 ofstream	ofstream file("a.txt")
// 讀取檔https://ieet2022survey3.cycu.edu.tw/MySurvey案	用 ifstream	ifstream file("a.txt")       
class Maze;
class Stack {
 private:
  struct Node{
    int row;
    int column;
    Node *next;  // 感覺原本少打*(?

    Node(int r, int c) { // Node的建構子
      row = r;
      column = c;
      next = NULL;
    }
  };
  Node *head;
 
 public:
  Stack() {
    Node *first = new Node(0,0); // （最左邊上面的那一格）
    // 上面那行是不是要改成Node *first = new Node(0,0); (?
    // 對
    head = first;
  }
  bool empty() {
    return head == nullptr;
  }
  void push(int r, int c) { 
    Node *newNode = new Node(r, c); 
    newNode->next = head; 
    head = newNode; 
  }
  void pop(int &r, int &c) {
    r = head->row;
    c = head->column;
    Node *temp = head;
    head = head->next;
    delete temp;
  }

  bool IsSame(int r, int c) {
    Node *temp = head;
    while ( temp != NULL ) {
      if ( temp->row == r && temp->column == c ) {
        return true;
      }
      temp = temp->next;
    }
    return false;
  }

  void turnR(Maze &a);  // 只宣告 // 改R

};

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

  // print我有修一下 不對再改回去
  void print() { // 印出迷宮資料
    for (int r = 0; r < row; r++) {
      for (int c = 0; c < column; c++) {
        std::cout << grid[r * column + c];
      }
      std::cout << "\n";
    }
  }

  char Getgrid(int r, int c) { // 取得這格的東西
    return grid[r * column + c];
  }

  void Setgrid(int r, int c, char letter) { // 改這格的字母(走過改V,路徑改R)
    grid[r * column + c] = letter; 
  }

  bool GoLeft(int &r, int &c, Stack &s, Stack &back) { // r c 放目前的位置
    int count = 0;
    while (c - 1 >= 0 && grid[r * column + (c - 1)] != 'O') {
      if (grid[r * column + c - 1 ] == 'G') { // 到終點
        count++;
        return true;
      }
      count++;
      c--;      
      s.push(r, c);
      back.push(r, c);
      Setgrid(r, c, 'V');
    }
    if ( count > 0 ) {
      return true;
    }

    else {
      return false;
    }
  }

  bool GoRight(int &r, int &c, Stack &s, Stack &back) { // r c 放目前的位置 ，向左到撞牆 direction走的方向
    int count = 0;
    while (c + 1 < column && grid[r * column + (c + 1)] != 'O') {
      if (grid[r * column + c + 1] == 'G') { // 到終點
        count++;
        return true;
      }
      count++;                 
      c++;
      s.push(r, c);
      back.push(r, c);
      Setgrid(r, c, 'V');
    }
    if ( count > 0 ) {
      return true;
    }

    else {
      return false;
    }
  }  
  bool GoUp(int &r, int &c, Stack &s, Stack &back) {
    int count = 0;
    while (r - 1 >= 0 && grid[(r - 1) * column + c] != 'O') {
      if (grid[(r - 1) * column + c] == 'G') {
        count++;
        return true;
      }
      count++;
      r--;
      s.push(r, c);
      back.push(r, c);
      Setgrid(r, c, 'V');
    }
    if ( count > 0 ) {
      return true;
    }

    else {
      return false;
    }
  }  
  bool GoDown(int &r, int &c, Stack &s, Stack &back) {
    int count = 0;
    while (r + 1 < row && grid[(r + 1) * column + c] != 'O') {
      if (grid[(r + 1) * column + c] == 'G') {
        count++;
        return true;
      }
      count++;
      r++;
      s.push(r, c);
      back.push(r, c);
      Setgrid(r, c, 'V');
    }
    if ( count > 0 ) {
      return true;
    }

    else {
      return false;
    }
  }

  bool Go(Stack &s) {
    Stack back; // 存走過的
    bool yes = false; // 和走過的r c 相同
    int r = 0, c = 0;
    bool have_go = false; // 找到g
    s.push(r, c);
    Setgrid(r, c, 'V');
    while (!s.empty()) {
      bool move = false;
      yes = back.IsSame(r, c + 1);
      if ( !yes ) {
        if (GoRight(r, c, s, back)) { 
          move = true; 
          if ( c < column - 1 ) {
            if ( grid[r * column + c + 1] == 'G' ) {
              have_go = true;
              break;
            }
          }
        }
      }
      yes = back.IsSame(r + 1, c);
      if ( !yes ) {
        if (GoDown(r, c, s, back)) { 
          move = true;
          if ( r < row - 1) {
            if ( grid[(r + 1) * column + c] == 'G' ) {
              have_go = true;
              break;
            }
          }
        }
      }
      yes = back.IsSame(r, c - 1);
      if ( !yes ) {
        if (GoLeft(r, c, s, back)) { 
          move = true;
          if ( c > 0 ) {
            if ( grid[r * column + c - 1] == 'G' ) {
              have_go = true;
              break;
            }
          }
        }
      }
      yes = back.IsSame(r - 1, c);
      if ( !yes ) {
        if (GoUp(r, c, s, back)) { 
          move = true;
          if ( r > 0 ) {
            if ( grid[(r - 1) * column + c] == 'G' ) {
              have_go = true;
              break;
            }
          }
        }
      }
      if (!move) {// 回上一格
        s.pop(r, c);
      }
    }
    return have_go;
  }
};

void Stack::turnR(Maze &a) {  // 改R 因為編譯器的問題，所以放在這
  Node *temp = head;
  while (temp != NULL) {
    a.Setgrid(temp->row, temp->column, 'R');
    temp = temp->next;
  }
  return;
}

void Start() {
  std::cout << "*** (^_^) Data Structure (^o^) ***" << std::endl;
  std::cout << "*** Find the Goal(s) in a Maze ***" << std::endl;
  std::cout << "* 0. Quit                        *" << std::endl;
  std::cout << "* 1. Find one goal               *" << std::endl;
  std::cout << "* 2. Find goal(s) as requested   *" << std::endl;
  std::cout << "* 3. How many goals?             *" << std::endl;
  std::cout << "* 4. Shortest path to one goal   *" << std::endl;
  std::cout << "**********************************" << std::endl;
  std::cout << "Input a command(0, 1, 2, 3, 4): ";
}

void task1(std::string &filename) {
  int file_number;
  Maze a;
  std::cout << "Input a file number: ";
  std::cin >> file_number;
  filename = std::to_string(file_number) + ".txt"; // 轉字串
  std::ifstream infile(filename); // 測試讀檔 github不能run
  if ( infile ) {
    int x;
    int y;
    infile >> x >> y; // 讀int x,y
    infile.get();
    a.initial(y, x);
    a.load(infile);
    Stack s;
    int r = 0;
    int c = 0;
    bool yes = a.Go(s);
    a.print();
    if ( yes ) {
      std::cout << "\n";
      s.turnR(a);
      a.print();
    }
  }

  else {
    std::cout << "input" << file_number << ".txt does not exist!";
  }
  std::cout << std::endl;
  infile.close(); // 關閉檔案
  return;
}

void task2(std::string filename) { // 還沒完成
  int number;
  Maze a;
  if ( !filename.empty() ) {
    std::cout << "Number of G (goals): ";
    std::cin >> number;
    std::ifstream infile(filename);
    int x;
    int y;
    infile >> x >> y; // 讀int x,y
    infile.get();
    a.initial(y, x);
    a.load(infile);
    Stack s;
    int r = 0;
    int c = 0;
    bool yes = a.Go(s);
    a.print();
    if ( yes ) {
      std::cout << "\n";
      s.turnR(a);
      a.print();
    }
  }

  else {
    std::cout << "### Execute command 1 to load a maze! ###";
  }
  std::cout << std::endl;
  return;
}

int main() {
  std::string filename;
  int common;
  Start();
  while ( std::cin >> common ) {
    std::cout << std::endl;
    if ( common == 1 ) {
      task1(filename);
    }
    if ( common == 2 ) {
      task2(filename);
    }
    if ( common == 0 ) {
      return 0;
    }
    Start();
  }


  return 0;

}

