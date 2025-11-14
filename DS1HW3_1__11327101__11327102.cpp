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
    Node *next;
    // 用於任務四
    bool right = false;
    bool left = false;
    bool up = false;
    bool down = false;

    Node(int r, int c) { // Node的建構子
      row = r;
      column = c;
      next = NULL;
      right = false;
      left = false;
      up = false;
      down = false;
    }
  };
  Node *head;
 
 public:
  Stack() {
    Node *first = new Node(0,0); // （最左邊上面的那一格）
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
    Node *temp = head;
    head = head->next;
    delete temp;
    if ( !empty() ) {
      r = head->row;
      c = head->column;
    }
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

  void clear() {
    Node *temp = head;
    Node *temp2;
    while ( temp != NULL ) {
      temp2 = temp->next;
      delete temp;
      temp = temp2;
    }
    head = NULL;
    return;
  } 

  void copy(Stack &s) {
    clear();
    Node *temp = s.head;
    while (temp != NULL ) {
      push(temp->row, temp->column);
      temp = temp->next;
    }
    return;
  }

  void turnR(Maze &a);  // 改R
  void turnG(Maze &a);  // 改G
  int Length() {
    int count = 0;
    Node *temp = head;
    while (temp != NULL) {
      count++;
      temp = temp->next;
    }
    return count;
  }

  bool getRight() {
    Node *temp = head;
    if ( temp != NULL ) {
      return temp->right;
    }
    return false;
  }

  bool getLeft() {
    Node *temp = head;
    if ( temp != NULL ) {
      return temp->left;
    }
    return false;
  }

  bool getUp() {
    Node *temp = head;
    if ( temp != NULL ) {
      return temp->up;
    }
    return false;
  }

  bool getDown() {
    Node *temp = head;
    if ( temp != NULL ) {
      return temp->down;
    }
    return false;
  }

  void turnLeft(bool haha) {
    Node *temp = head;
    if ( temp != NULL ) {
      temp->left = haha;
    }
    return;
  }

  void turnRight(bool haha) {
    Node *temp = head;
    if ( temp != NULL ) {
      temp->right = haha;
    }
    return;
  }

  void turnUp(bool haha) {
    Node *temp = head;
    if ( temp != NULL ) {
      temp->up = haha;
    }
    return;
  }

  void turnDown(bool haha) {
    Node *temp = head;
    if ( temp != NULL ) {
      temp->down = haha;
    }
    return;
  }

};

class Maze {
 private:
  int row;
  int column;
  char *grid;

 public:
  void initial(int r, int c) {
    row = r;
    column = c;
    grid = new char[row * column];  
  }

  void clear() {
    delete[] grid;
  }

  void load(std::ifstream &infile) { // 載入迷宮資料
    char ch;
    int r = 0;
    int c = 0;
    while (infile.get(ch)) {   // 每次讀一個字元
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
      std::cout << "\n";
    }
  }

  char Getgrid(int r, int c) { // 取得這格的東西
    return grid[r * column + c];
  }

  void Setgrid(int r, int c, char letter) { // 改這格的字母
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

  bool GoRight(int &r, int &c, Stack &s, Stack &back) { // r c 放目前的位置
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

  

  bool GoLeft4(int &r, int &c, Stack &s, Stack &back, int &size, int &path) { // r c 放目前的位置
    int count = 0;
    path = s.Length();
    while (c - 1 >= 0 && grid[r * column + (c - 1)] != 'O') {
      bool yes = s.IsSame(r, c - 1);
      bool left_yes = s.getLeft();
      if (!left_yes) {
        if ( !yes ) {
          if ( s.Length() < size ) {
            if (grid[r * column + c - 1 ] == 'G') { // 到終點
              count++;
              return true;
            }
            count++;
            c--;      
            s.turnLeft(1);
            s.push(r, c);
            left_yes = s.getLeft();
            back.push(r, c);
            Setgrid(r, c, 'V');
            path = s.Length();
          }

          else {
            if (grid[r * column + c - 1 ] != 'G') {
              s.pop(r, c);
              path = s.Length();
            }
            break;
          }
        }

        else {
          //s.pop(r, c);
          path = s.Length();
          return false;
        }
      }

      else {
        break;
      }
    }
    if ( count > 0 ) {
      return true;
    }

    else {
      return false;
    }
  }

  bool GoRight4(int &r, int &c, Stack &s, Stack &back, int &size, int &path) { // r c 放目前的位置 ，向右到撞牆
    int count = 0;
    path = s.Length();
    while (c + 1 < column && grid[r * column + (c + 1)] != 'O') {
      bool yes = s.IsSame(r, c + 1);
      bool right_yes = s.getRight();
      if (!right_yes) {
        if ( !yes ) {
          if ( path < size ) {
            if (grid[r * column + c + 1] == 'G') { // 到終點
              count++;
              return true;
            }
            count++;                 
            c++;
            s.turnRight(1);
            s.push(r, c);
            right_yes = s.getRight();
            back.push(r, c);
            Setgrid(r, c, 'V');
            path = s.Length();
          }

          else {
            if (grid[r * column + c + 1] != 'G') {
              s.pop(r, c);
              path = s.Length();
            }
            break;
          }
        }

        else {
          //s.pop(r, c);
          path = s.Length();
          return false;
        }
 
      }

      else {
        break;
      }
    }
    if ( count > 0 ) {
      return true;
    }

    else {
      return false;
    }
  }  
  bool GoUp4(int &r, int &c, Stack &s, Stack &back, int &size, int &path) {
    int count = 0;
    path = s.Length();
    while (r - 1 >= 0 && grid[(r - 1) * column + c] != 'O') {
      bool yes = s.IsSame(r - 1, c);
      bool up_yes = s.getUp();
      if (!up_yes) {
        if ( !yes ) {
          if ( path < size ) {
            if (grid[(r - 1) * column + c] == 'G') {
              count++;
              return true;
            }
            count++;
            r--;
            s.turnUp(1);
            s.push(r, c);
            up_yes = s.getUp();
            back.push(r, c);
            Setgrid(r, c, 'V');
            path = s.Length();
          }

          else {
            if (grid[(r - 1) * column + c] != 'G') {
              s.pop(r, c);
              path = s.Length();
            }
            break;
          }
        }

        else {
          //s.pop(r, c);
          path = s.Length();
          return false;
        }
 
      }

      else {
        break;
      }
    }
    if ( count > 0 ) {
      return true;
    } 

    else {
      return false;
    }
  }  
  bool GoDown4(int &r, int &c, Stack &s, Stack &back, int &size, int &path) {
    path = s.Length();
    int count = 0;
    while (r + 1 < row && grid[(r + 1) * column + c] != 'O') {
      bool Down_yes = s.getDown();
      bool yes = s.IsSame(r + 1, c);
      if (!Down_yes) {
        if ( !yes ) {
          if ( path < size ) {
            if (grid[(r + 1) * column + c] == 'G') {
              count++;
              return true;
            }
            count++;
            r++;
            s.turnDown(1);
            s.push(r, c);
            Down_yes = s.getDown();
            back.push(r, c);
            Setgrid(r, c, 'V');
            path = s.Length();
          }

          else {
            if (grid[(r + 1) * column + c] != 'G') {
              s.pop(r, c);
              path = s.Length();
              break;
            }
            break;
          }
        }

        else {
          //s.pop(r, c);
          path = s.Length();
          return false;
        }
      }

      else {
        break;
      }
    }
    if ( count > 0 ) {
      return true;
    }

    else {
      return false;
    }
  }

  bool Go4(Stack &s, Stack &back, int &size, Stack &small) {
    bool yes = false; // 和走過的r c 相同
    int r = 0, c = 0;
    Stack p;
    bool have_go = false; // 找到g
    size = 9999999;
    int is_small = size;
    int path = 1; // 每條的數量
    Setgrid(r, c, 'V');
    while (!s.empty()) {
      bool move = false;
      //std::cout << "r " << r << "\n";
      //std::cout << "c " << c << "\n";
      if (GoRight4(r, c, s, back, is_small, path)) {
        move = true;
        if (c < column - 1) {
          if (grid[r * column + c + 1] == 'G') {
            have_go = true;
            if ( s.Length() < is_small ) {
              small.copy(s);
              is_small = s.Length();
            }
            s.pop(r, c);
          }
        }
      }
      if (GoDown4(r, c, s, back, is_small, path)) {
        move = true;
        if (r < row - 1) {
          if (grid[(r + 1) * column + c] == 'G') {
            have_go = true;
            if ( s.Length() < is_small ) {
              small.copy(s);
              is_small = s.Length();
            }
            s.pop(r, c);
          }
        }
      }
      if (GoLeft4(r, c, s, back, is_small, path)) {
        move = true;
        if (c > 0) {
          if (grid[r * column + c - 1] == 'G') {
            have_go = true;
            if ( s.Length() < is_small ) {
              small.copy(s);
              is_small = s.Length();
            }
            s.pop(r, c);
          }
        }
      }
      if (GoUp4(r, c, s, back, is_small, path)) {
        move = true;
        if (r > 0) {
          if (grid[(r - 1) * column + c] == 'G') {
            have_go = true;
            if ( s.Length() < is_small ) {
              small.copy(s);
              is_small = s.Length();
            }
            s.pop(r, c);
          }
        }
      }
      if (!move) { // 回上一格
        s.pop(r, c);
        path = s.Length();
      }
    }
    return have_go;
  }

  bool Go(Stack &s, Stack &back) {
    bool yes = false; // 和走過的r c 相同
    int r = 0, c = 0;
    bool have_go = false; // 找到g
    Setgrid(r, c, 'V');
    while (!s.empty()) {
      bool move = false;
      yes = back.IsSame(r, c + 1);
      if (!yes) {
        if (GoRight(r, c, s, back)) {
          move = true;
          if (c < column - 1) {
            if (grid[r * column + c + 1] == 'G') {
              have_go = true;
              break;
            }
          }
        }
      }
      yes = back.IsSame(r + 1, c);
      if (!yes) {
        if (GoDown(r, c, s, back)) {
          move = true;
          if (r < row - 1) {
            if (grid[(r + 1) * column + c] == 'G') {
              have_go = true;
              break;
            }
          }
        }
      }
      yes = back.IsSame(r, c - 1);
      if (!yes) {
        if (GoLeft(r, c, s, back)) {
          move = true;
          if (c > 0) {
            if (grid[r * column + c - 1] == 'G') {
              have_go = true;
              break;
            }
          }
        }
      }
      yes = back.IsSame(r - 1, c);
      if (!yes) {
        if (GoUp(r, c, s, back)) {
          move = true;
          if (r > 0) {
            if (grid[(r - 1) * column + c] == 'G') {
              have_go = true;
              break;
            }
          }
        }
      }
      if (!move) { // 回上一格
        s.pop(r, c);
      }
    }
    return have_go;
  }

  bool Findgoals(Stack &s, int number, Stack &back, Stack &saveG) {
    bool yes = false;
    int r = 0, c = 0;
    bool have_go = false; 
    int found = 0;
    s.push(r, c);
    Setgrid(r, c, 'V');
    while (!s.empty()) {
      bool move = false;
      yes = back.IsSame(r, c + 1);
      if (!yes) {
        if (GoRight(r, c, s, back)) {
          move = true;
          if (c < column - 1) {
            if (grid[r * column + c + 1] == 'G') {
              found++;
              Setgrid(r, c + 1, 'E');
              saveG.push(r , c + 1);
              if (found == number) {
                have_go = true;
                break;
              }
            }
          }
        }
      }
      yes = back.IsSame(r + 1, c);
      if (!yes) {
        if (GoDown(r, c, s, back)) {
          move = true;
          if (r < row - 1) {
            if (grid[(r + 1) * column + c] == 'G') {
              found++;
              Setgrid(r + 1, c, 'E');
              saveG.push(r + 1 , c);
              if (found == number) {
                have_go = true;
                break;
              }
            }
          }
        }
      }
      yes = back.IsSame(r, c - 1);
      if (!yes) {
        if (GoLeft(r, c, s, back)) {
          move = true;
          if (c > 0) {
            if (grid[r * column + c - 1] == 'G') {
              found++;
              Setgrid(r, c - 1, 'E');
              saveG.push(r , c - 1);
              if (found == number) {
                have_go = true;
                break;
              }
            }
          }
        }
      }
      yes = back.IsSame(r - 1, c);
      if (!yes) {
        if (GoUp(r, c, s, back)) {
          move = true;
          if (r > 0) {
            if (grid[(r - 1) * column + c] == 'G') {
              found++;
              Setgrid(r - 1, c, 'E');
              saveG.push(r - 1 , c);
              if (found == number) {
                have_go = true;
                break;
              }
            }
          }
        }
      }
      if (!move) { // 回上一格
        s.pop(r, c);
      }
    }
    return have_go;
  }

  bool Findgoals3(Stack &s, int &number, Stack &back, Stack &saveG) { // saveG 存G的位置
    bool yes = false;
    int r = 0, c = 0;
    bool have_go = false; 
    Setgrid(r, c, 'V');
    while (!s.empty()) {
      bool move = false;
      yes = back.IsSame(r, c + 1);
      if (!yes) {
        if (GoRight(r, c, s, back)) {
          move = true;
          if (c < column - 1) {
            if (grid[r * column + c + 1] == 'G') {
              number++;
              Setgrid(r, c + 1, 'E');
              saveG.push(r , c + 1);
              have_go = true;
            }
          }
        }
      }
      yes = back.IsSame(r + 1, c);
      if (!yes) {
        if (GoDown(r, c, s, back)) {
          move = true;
          if (r < row - 1) {
            if (grid[(r + 1) * column + c] == 'G') {
              number++;
              Setgrid(r + 1, c, 'E');
              saveG.push(r + 1, c);
              have_go = true;
            }
          }
        }
      }
      yes = back.IsSame(r, c - 1);
      if (!yes) {
        if (GoLeft(r, c, s, back)) {
          move = true;
          if (c > 0) {
            if (grid[r * column + c - 1] == 'G') {
              number++;
              Setgrid(r, c - 1, 'E');
              saveG.push(r , c - 1);
              have_go = true;
            }
          }
        }
      }
      yes = back.IsSame(r - 1, c);
      if (!yes) {
        if (GoUp(r, c, s, back)) {
          move = true;
          if (r > 0) {
            if (grid[(r - 1) * column + c] == 'G') {
              number++;
              Setgrid(r - 1, c, 'E');
              saveG.push(r - 1, c);
              have_go = true;
            }
          }
        }
      }
      if (!move) { // 回上一格
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

void Stack::turnG(Maze &a) {  // 改G 因為編譯器的問題，所以放在這
  Node *temp = head;
  while (temp->next != NULL) { // (0,0)不是G
    a.Setgrid(temp->row, temp->column, 'G');
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
  int file_number; // 檔案數字
  Maze a;
  std::cout << "\n";
  std::cout << "Input a file number: ";
  std::cin >> file_number;
  filename = "input" + std::to_string(file_number) + ".txt"; // 轉字串
  std::ifstream infile(filename); // 讀檔
  char ch = getchar();
  if ( infile ) {
    int x;
    int y;
    infile >> x >> y; // 讀int x,y
    infile.get();
    a.initial(y, x);
    a.load(infile);
    Stack s;
    Stack back;
    int r = 0;
    int c = 0;
    bool yes = a.Go(s, back);
    a.print();
    infile.close();
    Maze b; // 因為之前迷宮有v，所以直接用新迷宮轉R
    std::ifstream infile(filename);
    int u;
    int o;
    infile >> u >> o; // 讀int x,y
    infile.get();
    b.initial(o, u);
    b.load(infile);
    if ( yes ) {
      std::cout << "\n";
      s.turnR(b);
      b.print();
    }
    s.clear();
    back.clear();
    a.clear();
    b.clear();
  }

  else { // 沒這檔案
    std::cout << "\ninput" << file_number << ".txt does not exist!";
  }
  std::cout << std::endl;
  std::cout << "\n";
  infile.close(); // 關閉檔案
  return;
}

void task2(std::string filename) { 
  int number; // 我要找多少G
  Maze a;
  std::cout << "\n";
  std::ifstream infile(filename);
  if ( infile ) {
    while (true) {
      std::cout << "Number of G (goals): ";
      int num = 0;
      bool has_digit = false;
      bool invalid = false;
      char ch;
      while ((ch = getchar()) != '\n') {
        if (ch == ' ' || ch == '\t') {
          continue;  // 忽略空白
        } else if (ch >= '0' && ch <= '9') {
          has_digit = true;
          num = num * 10 + (ch - '0');
        } else {
          invalid = true;  // 有非數字
        }
      }

      if (!has_digit || invalid) {
        // 輸入不是純數字
        continue;
      }
      if (num < 1 || num > 100) {
        std::cout << "### The number must be in [1,100] ###" << std::endl;
        continue;
      }
      number = num;
      break;
    }
    std::ifstream infile(filename);
    int x;
    int y;
    infile >> x >> y; // 讀int x,y
    infile.get();
    a.initial(y, x);
    a.load(infile);
    Stack s;
    Stack back;
    Stack saveG;
    int r = 0;
    int c = 0;
    bool yes = a.Findgoals(s,number, back, saveG);
    saveG.turnG(a);
    a.print();
    infile.close();
    Maze b; // 因為之前迷宮有v，所以直接用新迷宮轉R
    std::ifstream filet(filename);
    int u;
    int o;
    filet >> u >> o; // 讀int x,y
    filet.get();
    b.initial(o, u);
    b.load(filet);
    saveG.turnG(b); // 存G點轉迷宮G
    if ( yes ) {
      std::cout << "\n";
      s.turnR(b);
      b.print();
    }
    s.clear();
    back.clear();
    saveG.clear();
    a.clear();
    b.clear();
  }
  else { // 你沒輸1迷宮
    std::cout << "### Execute command 1 to load a maze! ###";
  }
  std::cout << std::endl;
  std::cout << "\n";
  return;
}

void task3(std::string filename) { 
  int number = 0;
  Maze a;
  std::ifstream infile(filename);
  if ( infile ) {
    std::ifstream infile(filename);
    int x;
    int y;
    infile >> x >> y; // 讀int x,y
    infile.get();
    a.initial(y, x);
    a.load(infile);
    Stack s;
    Stack back;
    Stack saveG;
    int r = 0;
    int c = 0;
    bool yes = a.Findgoals3(s,number, back, saveG);
    saveG.turnG(a);
    a.print();
    std::cout << "\n";
    std::cout << "The maze has " << number << " goal(s) in total.\n";
    s.clear();
    back.clear();
    saveG.clear();
    a.clear();
  }
  
  else { // 你沒輸1迷宮
    std::cout << "### Execute command 1 to load a maze! ###";
  }
  std::cout << std::endl;
  return;
}

void task4() {
  std::string filename;
  int file_number;
  Maze a;
  std::cout << "\n";
  std::cout << "Input a file number: ";
  std::cin >> file_number;
  filename = "input" + std::to_string(file_number) + ".txt"; // 轉字串
  char ch = getchar();
  std::ifstream infile(filename); // 讀檔
  if ( infile ) {
    int x,y;
    Stack small;
    std::ifstream infile(filename);
    infile >> x >> y; // 讀int x,y
    infile.get();
    Maze b;
    b.initial(y, x);
    b.load(infile);
    Stack s_2;
    Stack back_2;
    int size;
    bool yes_2 = b.Go4(s_2, back_2, size, small);
    b.print();
    Maze c; // 因為之前迷宮有v，所以直接用新迷宮轉R
    infile.close();
    std::ifstream yy(filename);
    yy >> x >> y; // 讀int x,y
    yy.get();
    c.initial(y, x);
    c.load(yy);
    if ( yes_2 ) {
      std::cout << "\n";
      small.turnR(c);
      c.print();
      int path_small_size = small.Length();
      std::cout << "\nShortest path length = " << path_small_size + 1;
    }

    else { // 沒G
      std::cout << "\n### There is no path to find a goal! ###";
    }
    
  }
  
  else {
    std::cout << "input" << file_number << ".txt does not exist!";
  }
  std::cout << std::endl;
  std::cout << "\n";
  infile.close(); // 關閉檔案
  return;
}
int main() {
  std::string filename;
  char ch;
  int command = 0;
  bool has_command1; // 執行過任務一
  Start(); // 印選單
  while (true) {
    command = 0;
    bool has_digit = false; // 已經有數字
    bool invalid = false; // 非法輸入
    while ((ch = getchar()) != '\n') {
      if (ch == ' ' || ch == '\t') { // 跳過空白跟tab
        continue;
      } else if (ch >= '0' && ch <= '4') {
        if (has_digit) {
          invalid = true; // 多個數字
        } else {
          command = ch - '0';
          has_digit = true;
        }
      } else { // 非法字元
        invalid = true;
      }
    }

    if (invalid || (!has_digit)) {
      std::cout << "Command does not exist!" << std::endl << std::endl;
      Start();
      continue;
    }
    if (command == 0) {
      return 0;
    }
    if ((command == 2 || command == 3) && !has_command1) {
      std::cout << "### Execute command 1 to load a maze! ###" << std::endl << std::endl;
      Start();
      continue;
    }
    if (command == 1) {
      task1(filename);
      has_command1 = true;
    } else if (command == 2) {
      task2(filename);
    } else if (command == 3) {
      task3(filename);
    } else if (command == 4) {
      task4();
    }
    Start();
  }
  return 0;
}










