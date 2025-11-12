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

  void clear() {
    Node *temp = head;
    while ( temp != NULL ) {
      delete temp;
      temp = temp->next;
    }
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

  void turnR(Maze &a);  // 只宣告 // 改R
  void turnG(Maze &a); // 只宣告 // 改G
  int Length() {
    int count = 0;
    Node *temp = head;
    while (temp != NULL) {
      count++;
      temp = temp->next;
    }
    return count;
  }

  void size_place() {
    Node *temp = head;
    while (temp != NULL) {
      std::cout << "r " << temp->row << " ,c " << temp->column << "\n";
      temp = temp->next;
    }
    return;
  }

  int getR() {
    Node *temp = head;
    if ( temp != NULL ) {
      return temp->row;
    }
    return 0;
  }

  int getC() {
    Node *temp = head;
    if ( temp != NULL ) {
      return temp->row;
    }
    return 0;
  }

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

  bool Go(Stack &s, Stack &back) {
    bool yes = false; // 和走過的r c 相同
    int r = 0, c = 0;
    bool have_go = false; // 找到g
    int dr[4] = {0, 1, 0, -1};  //  右下左上
    int dc[4] = {1, 0, -1, 0};
    Setgrid(r, c, 'V');
    while (!s.empty()) {
      bool move = false;
      int nr = r;
      int nc = c;
      for (int i = 0; i < 4; i++) {
        nr = r + dr[i];
        nc = c + dc[i];
        while ( grid[nr * column + nc] != 'O' && !yes ) {
          if ( nr < 0 || nr >= row || nc < 0 || nc >= column ) {
            nr = nr - dr[i];
            nc = nc - dc[i];
            break;
          }
          yes = back.IsSame(nr, nc);
          if (grid[nr * column + nc] == 'G') {
            have_go = true;
            return have_go;
          }
          r = nr;
          c = nc;
          s.push(r, c);
          back.push(r, c);
          Setgrid(r, c, 'V');
          move = true;
          nr = nr + dr[i];
          nc = nc + dc[i];
        }
      }

      if ( !move ) {
        s.pop(r, c);
        r = s.getR();
        c = s.getC();
      }
    }
    return have_go;
  }

  bool Findgoals(Stack &s, int number, Stack &back, Stack &saveG) { // saveG 存G點位置
    bool yes = false; // 和走過的r c 相同
    int r = 0, c = 0;
    bool have_go = false; // 找到g && found == nuber
    int found = 0;
    int dr[4] = {0, 1, 0, -1};  //  右下左上
    int dc[4] = {1, 0, -1, 0};
    Setgrid(r, c, 'V');
    while (!s.empty()) {
      bool move = false;
      int nr = r;
      int nc = c;
      for (int i = 0; i < 4; i++) {
        nr = r + dr[i];
        nc = c + dc[i];
        while ( grid[nr * column + nc] != 'O' && !yes ) {
          if ( nr < 0 || nr >= row || nc < 0 || nc >= column ) {
            nr = nr - dr[i];
            nc = nc - dc[i];
            break;
          }
          yes = back.IsSame(nr, nc);
          if (grid[nr * column + nc] == 'G') {
            std::cout << "r " << r << "\n";
            std::cout << "c " << r << "\n";
            found++;
            Setgrid(nr, nc, 'E');
            saveG.push(nr, nc);
            if ( found == number ) {
              have_go = true;
              return have_go;
            }
          }
          r = nr;
          c = nc;
          s.push(r, c);
          back.push(r, c);
          Setgrid(r, c, 'V');
          move = true;
          nr = nr + dr[i];
          nc = nc + dc[i];
        }
      }

      if ( !move ) {
        s.pop(r, c);
        r = s.getR();
        c = s.getC();
      }
    }
    return have_go;
  }

  bool Findgoals3(Stack &s, int number, Stack &back, Stack &saveG) { // saveG 存G點位置
    bool yes = false; // 和走過的r c 相同
    int r = 0, c = 0;
    bool have_go = false; // 找到g
    int found = 0;
    int dr[4] = {0, 1, 0, -1};  //  右下左上
    int dc[4] = {1, 0, -1, 0};
    while (!s.empty()) {
      break;
      bool move = false;
      std::cout << "r " << r << std::endl;
      std::cout << "c " << c << std::endl;
      for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if ( nr < 0 || nr >= row || nc < 0 || nc >= column ) {
          continue;
        }
        yes = back.IsSame(nr, nc);
        if (grid[nr * column + nc] == 'G') {
          found++;
          Setgrid(nr, nc, 'E');
          saveG.push(nr, nc);
          have_go = true;
        }
        if ( grid[nr * column + nc] == 'O' || !yes ) {
          continue;
        }
        s.push(nr, nc);
        back.push(nr, nc);
        Setgrid(r, c, 'V');
        move = true;
      }

      if ( r == row - 1 && c == column - 1 ) {
        break;
      }

      if ( !move ) {
        s.pop(r, c);
        std::cout << "r " << r << std::endl;
        std::cout << "c " << c << std::endl;
        r = s.getR();
        c = s.getC();
      }
    }
    return have_go;
  }

  bool Go4(Stack &s, Stack &back, int &size, Stack &small) {
    bool yes = false; // 和走過的r c 相同
    int r = 0, c = 0;
    size = 9999999;
    bool have_go = false; // 找到G
    int small_size = size;
    int path_size = 1;
    int dr[4] = {0, 1, 0, -1};  //  右下左上
    int dc[4] = {1, 0, -1, 0};
    while (!s.empty()) {
      bool move = false;
      for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if ( nr < 0 || nr >= row || nc < 0 || nc >= column ) {
          continue;
        }
        yes = s.IsSame(nr, nc);
        if (grid[nr * column + nc] == 'G') {
          if ( path_size < small_size ) {
            small_size = path_size;
            small.copy(s);
          }
          have_go = true;
        }
        if ( grid[nr * column + nc] == 'O' || !yes ) {
          continue;
        }
        if ( path_size < small_size ) {
          path_size++;
          s.push(nr, nc);
          back.push(nr, nc);
          Setgrid(r, c, 'V');
          move = true;
        }

        else {
          path_size--;
          s.pop(r, c);
          r = s.getR();
          c = s.getC();
        }
      }

      if ( r == row - 1 && c == column - 1 ) {
        break;
      }

      if ( !move ) {
        s.pop(r, c);
        r = s.getR();
        c = s.getC();
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
  int file_number;
  Maze a;
  std::cout << "Input a file number: ";
  std::cin >> file_number;
  filename = "input" + std::to_string(file_number) + ".txt"; // 轉字串
  std::ifstream infile(filename); // 測試讀檔 github不能run
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

void task2(std::string filename) { 
  int number;
  Maze a;
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
    std::cout << "The maze has " << number <<  " goal(s) in total.";
  }
  else {
    std::cout << "### Execute command 1 to load a maze! ###";
  }
  std::cout << std::endl;
  return;
}

void task4() {
  std::string filename;
  int file_number;
  Maze a;
  std::cout << "Input a file number: ";
  std::cin >> file_number;
  filename = "input" + std::to_string(file_number) + ".txt"; // 轉字串
  char ch = getchar();
  std::ifstream infile(filename); // 測試讀檔 github不能run
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
    if ( yes_2 ) {
      std::cout << "\n";
      small.turnR(b);
      b.print();
    }
  }

  else {
    std::cout << "input" << file_number << ".txt does not exist!";
  }
  std::cout << std::endl;
  infile.close(); // 關閉檔案
  return;
}
int main() {
  std::string filename;
  char ch;
  int command = 0;
  bool has_command1;
  Start();
  while (true) {
    command = 0;
    bool has_digit = false;
    bool invalid = false;
    while ((ch = getchar()) != '\n') {
      if (ch == ' ' || ch == '\t') {
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
    // 處理非法輸入
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
