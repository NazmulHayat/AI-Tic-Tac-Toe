#include<bits/stdc++.h>
using namespace std;

char human = 'X';
char ai = 'Y';
int score=0,total=0;

struct Move{
  int row;
  int col;
};

void display(vector<vector<char>>& board)
{
    cout<<"\n\n";
    cout<<"     |     |     \n";
    cout<<"  "<<board[0][0]<<"  |  "<<board[0][1]<<"  |   "<<board[0][2]<<" \n";
    cout<<"_____|_____|_____\n";
    cout<<"     |     |     \n";
    cout<<"  "<<board[1][0]<<"  |  "<<board[1][1]<<"  |   "<<board[1][2]<<" \n";
    cout<<"_____|_____|_____\n";
    cout<<"     |     |     \n";
    cout<<"  "<<board[2][0]<<"  |  "<<board[2][1]<<"  |   "<<board[2][2]<<" \n";
    cout<<"     |     |     \n";
    cout<<endl;
}
int istie(vector< vector<char>>& board)
{

  for(int i = 0 ; i < 3 ; i++)
  {
    for(int j = 0 ; j < 3 ; j++)
    {
      if(board[i][j] != human && board[i][j] != ai)
      {
          return false;
      }
    }
  }
  return true;
}
int gamewin(vector< vector<char>>& board, char player){
  int winCombos[8][3] = {
      {0, 1, 2},
      {3, 4, 5},
      {6, 7, 8},
      {0, 3, 6},
      {1, 4, 7},
      {2, 5, 8},
      {0, 4, 8},
      {6, 4, 2}};
  bool jitse = 0;
  for(int i = 0 ; i < 8 ; i++)
  {
    for(int j = 0 ; j < 3 ; j++)
    {
      int r = winCombos[i][j]/3;
      int c = winCombos[i][j]%3;
      if(board[r][c] == player){
        jitse = 1;
        continue;
      }
      jitse=0;
      break;
    }
    if(jitse){
      score = player == 'X' ? 1 : -1;
      return true;
    }
  }
  return false;
}
int global = 0;
int minimax(vector<vector<char>>& board, int depth, bool isMax)
{
  char player = isMax == 0 ? ai : human;
  int emne = gamewin(board, player);
  if(emne)
  {
      total++;
      int temp = score;
      score=0;
      global = depth;
      if(temp == 1)
        return -depth;
      if(temp == -1)
        return depth;
  }
  int raiyan = istie(board);

  if(raiyan==1)
    {
        total++;
        return 0;
    }

  if(isMax)
  {
    int best = INT_MIN, mx;
    for(int i = 0 ; i < 3 ; i++)
    {
      for(int j = 0  ; j < 3 ; j++)
      {
        char temp = board[i][j];
        if(board[i][j] != human && board[i][j] != ai)
        {
          board[i][j] = ai;
          mx  = minimax(board, depth+1, false);
          best = max(best, mx);
          board[i][j] = temp;
        }
      }
    }
    return best;
  }
  else
    {
      int best = INT_MAX,mn;
      for(int i = 0 ; i < 3 ; i++)
      {
        for(int j = 0  ; j < 3 ; j++)
        {
          char temp = board[i][j];
          if(board[i][j] != human && board[i][j] != ai)
          {
            board[i][j] = human;
            mn = minimax(board, depth+1, true);
            best = min(best, mn);
            board[i][j] = temp;
          }
        }
      }
      return best;
    }
}
Move findingbestmove(vector< vector<char>>&board){
  int bestval = INT_MIN;
  Move bestmove;
  bestmove.row = -1;
  bestmove.col = -1;
  bool flag=1;
  int x,y,z=INT_MAX;
  for(int i =  0 ; i < 3 ; i++)
  {
    for(int j = 0 ; j < 3 ; j++)
    {
      char temp = board[i][j];
      if(board[i][j] != human && board[i][j] != ai)
      {
        board[i][j] = ai;
        int moveval = minimax(board, 1, false);
        board[i][j] = temp;
        if(moveval < 0) flag = 0;
        if(flag && z > moveval && moveval!=0) {
            x=i, y=j, z = moveval;
        }
        if(moveval > bestval ){
          bestval = moveval;
          bestmove.row = i;
          bestmove.col = j;
        }
      }
    }
  }
  if(flag && z != INT_MAX)
  {
      bestmove.row = x;
      bestmove.col = y;
  }
  board[bestmove.row][bestmove.col] = ai;
  int a = (bestmove.row*3) + (bestmove.col);
  display(board);
  cout<<endl<<"TT moved at box no. "<<a<<endl;
}

int main()
{
  string arr[5] = {"Broo are you srs, you gotta play more better", "AI vs HUMAN, LOL",
                    "Man you suck at tic tac toe too", "So AI won as always", "A.I: you lost...sed :("};
  srand(time(NULL));
  cout<<"Built Date: 19th June, 2020"<<endl<<endl;
  cout<<"WELCOME TO\n";
  cout<<"TIC TAC TOE GAME with TT\n\n";
  vector<vector<char>> board = {{'0','1','2'},
                                {'3','4','5'},
                                {'6','7','8'}};

  vector<vector<char>> board2 = {{'O','X','O'},
                                {'O','X','5'},
                                {'6','O','X'}};
  int n, r, c;
  char see, first, play;
  cout<<"Hi there, my name is TT. I am an A.I. bot"<<endl;
  cout<<"I am best at playing the game TIC TAC TOE, do you wanna try me (Y/N)? ";
  cin>>play;
  if(play == 'N')
  {
      cout<<endl<<"So I suppose you have surrendered already..OK nice"<<endl;
      return 0;
  }
  cout<<endl<<"  \t\t\t*INSTRUCTIONS*"<<endl;
  cout<<"\t     You will play 'X', TT will play 'Y'"<<endl;
  cout<<"\t     You just have to type your the number of \n\t     your box to make a move"<<endl;

  cout<<endl<<"Do you wanna go first? (Y/N): ";
  cin>>first;
  cout<<"Do you wanna see the evaluation (Y/N): ";
  cin>>see;
  cout<<endl;
  cout<<"Don't mind I get overexcited sometimes .... hehe"<<endl;
  display(board);
  if(first == 'N')
    {
        findingbestmove(board);
        if(see=='Y') {
            cout<<"The A.I. computed "<<total<<" possibilities\n"<<endl;
            total = 0;
        }

    }


  while(true)
  {

    if(gamewin(board, human))
      {
          cout<<"You have won congo"<<endl;
          break;
      }
    if(gamewin(board, ai))
    {
        cout<<arr[rand()%5]<<endl;
        break;
    }
    if(istie(board)){
        cout<<"Nice Try man!!"<<endl;
        break;
    }
    cout<<"X's move: ";
    cin>>n;
    r = n/3;
    c = n%3;
    board[r][c] = human;
    findingbestmove(board);
    if(see=='Y')
        cout<<"The A.I. computed "<<total<<" possibilities\n"<<endl;
    total=0;
  }
}
