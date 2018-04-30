#include "Connect4Game.h"
#include <iostream>
using namespace std;

//Constructor
Connect4Game::Connect4Game()
{
 cout<<"\t      CONNECT 4 GAME \n\n";
 turn=1;
 for(int i=0;i<7;i++)              // first initialized all cell by 0
 {
  for(int j=0;j<7;j++)
  {
   board[i][j]=0;
  }
 }
}

// To display the board
void Connect4Game::showBoard()
{
 for(int i=0;i<7;i++)
 {
  cout<<"\t\t";
  for(int j=0;j<7;j++)
  {
   cout<<board[i][j];
  }
  cout<<endl;
 }
 cout<<endl;
}
// to toggle turns
void Connect4Game::switchTurn()
{
// I use 2 for the player 2 and 1 for the player 1
 int mod;
 turn++; // here if turn is 1 it become 2 and if turn is 2 it becomes 3
 mod=turn%2; // and the mod becomes 0 if turn is 2 and becomes 1 if if turn is 3
 if(mod==0)
  turn=2;     // which mean its player 2 turn
 else
  turn=1;     // which mean its player 1 turn
}

// To check which player won
bool Connect4Game::Won()
{
 // horizontally check whether the sum of alternate 4 column are 4 or 8 and also check all the columns are filled
 for(int i=6;i>=0;i--)
 {
  for(int j=0;j<4;j++)
  {
   if(   (board[i][j]+board[i][j+1]+board[i][j+2]+board[i][j+3]==8||
                                 board[i][j]+board[i][j+1]+board[i][j+2]+board[i][j+3]==4)&&
     (board[i][j]!=0&&board[i][j+1]!=0&&board[i][j+2]!=0&&board[i][j+3]!=0) )
   {
    if(board[i][j]+board[i][j+1]+board[i][j+2]+board[i][j+3]==8) // To check which player won                                                                                                                                        // player won
    {
     cout<<"player 2 won !\n";
     return true;
    }
    else
    {
     cout<<"player 1 won !\n";
     return true;
    }
   }
  }
 }
 // vertically check whether the sum of alternate 4 rows are 4 or 8 and also check all the rows are filled             
 for(int j=0;j<7;j++)
 {
  for(int i=6;i>2;i--)
  {
   if( (board[i][j]+board[i-1][j]+board[i-2][j]+board[i-3][j]==8
                            ||board[i][j]+board[i-1][j]+board[i-2][j]+board[i-3][j]==4)&&
       (board[i][j]!=0&&board[i-1][j]!=0&&board[i-2][j]!=0&&board[i-3][j]!=0) )
   {
    if(board[i][j]+board[i-1][j]+board[i-2][j]+board[i-3][j]==8)// To check which                                                                                                                                         // player won
    {
     cout<<"player 2 won !\n";
     return true;
    }
    else
    {
     cout<<"player 1 won !\n";
     return true;
    }
   }
  }
  
 }
 // diagnally check whether the sum of diagonal 4 rows are 4 or 8 and also check all the 4 cell are filled
 for(int i=6;i>2;i--)
 {
  for(int j=0;j<4;j++)
  {
   if(j==0&&i==6)
   {
    for(int c=0;c<4;c++)
    {
     if((board[i-c][j+c]+board[i-(c+1)][j+(c+1)]+board[i-(c+2)][j+(c+2)]+board[i-(c+3)][j+(c+3)]==8||
      board[i-c][j+c]+board[i-(c+1)][j+(c+1)]+board[i-(c+2)][j+(c+2)]+board[i-(c+3)][j+(c+3)]==4)&&
      (board[i-c][j+c]!=0&&board[i-(c+1)][j+(c+1)]!=0&&board[i-(c+2)][j+(c+2)]!=0&&board[i-(c+3)][j+(c+3)]!=0))
     {
      if(board[i-c][j+c]+board[i-(c+1)][j+(c+1)]+board[i-(c+2)][j+(c+2)]+board[i-(c+3)][j+(c+3)]==8)
      {
       cout<<"player 2 won !\n";
       return true;
      }
      else
      {
       cout<<"player 1 won !\n";
       return true;
      }
     }
    
    }
   }

   if((j==1&&i==6)||(j==0&&i==5))
   {
    for(int c=0;c<3;c++)
    {
     if((board[i-c][j+c]+board[i-(c+1)][j+(c+1)]+board[i-(c+2)][j+(c+2)]+board[i-(c+3)][j+(c+3)]==8||
      board[i-c][j+c]+board[i-(c+1)][j+(c+1)]+board[i-(c+2)][j+(c+2)]+board[i-(c+3)][j+(c+3)]==4)&&
      (board[i-c][j+c]!=0&&board[i-(c+1)][j+(c+1)]!=0&&board[i-(c+2)][j+(c+2)]!=0&&board[i-(c+3)][j+(c+3)]!=0))
     {
      if(board[i-c][j+c]+board[i-(c+1)][j+(c+1)]+board[i-(c+2)][j+(c+2)]+board[i-(c+3)][j+(c+3)]==8)
      {
       cout<<"player 2 won !\n";
       return true;
      }
      else
      {
       cout<<"player 1 won !\n";
       return true;
      }
     }
    
    }
   }

   if(j==2&&i==6||(j==0&&i==4))
   {
    for(int c=0;c<2;c++)
    {
     if((board[i-c][j+c]+board[i-(c+1)][j+(c+1)]+board[i-(c+2)][j+(c+2)]+board[i-(c+3)][j+(c+3)]==8||
      board[i-c][j+c]+board[i-(c+1)][j+(c+1)]+board[i-(c+2)][j+(c+2)]+board[i-(c+3)][j+(c+3)]==4)&&
      (board[i-c][j+c]!=0&&board[i-(c+1)][j+(c+1)]!=0&&board[i-(c+2)][j+(c+2)]!=0&&board[i-(c+3)][j+(c+3)]!=0))
     {
      if(board[i-c][j+c]+board[i-(c+1)][j+(c+1)]+board[i-(c+2)][j+(c+2)]+board[i-(c+3)][j+(c+3)]==8)
      {
       cout<<"player 2 won !\n";
       return true;
      }
      else
      {
       cout<<"player 1 won !\n";
       return true;
      }
     }
    }
   }

   if(i==6&&j==3||(j==0&&i==3))
   {
    if((board[i][j]+board[i-1][j+1]+board[i-2][j+2]+board[i-3][j+3]==8||
     board[i][j]+board[i-1][j+1]+board[i-2][j+2]+board[i-3][j+3]==4)&&
     (board[i][j]!=0&&board[i-1][j+1]!=0&&board[i-2][j+2]!=0&&board[i-3][j+3]!=0))
    {
     if(board[i][j]+board[i-1][j+1]+board[i-2][j+2]+board[i-3][j+3]==8)
     {
      cout<<"player 2 won !\n";
      return true;
     }
     else
     {
      cout<<"player 1 won !\n";
      return true;
     }
    }
   }

  }
 }
 for(int i=6;i>2;i--)
 {
  for(int j=6;j>2;j--)
  {
   if(j==6&&i==6)
   {
    for(int c=0;c<4;c++)
    {
     if((board[i-c][j-c]+board[i-(c+1)][j-(c+1)]+board[i-(c+2)][j-(c+2)]+board[i-(c+3)][j-(c+3)]==8||
      board[i-c][j-c]+board[i-(c+1)][j-(c+1)]+board[i-(c+2)][j-(c+2)]+board[i-(c+3)][j-(c+3)]==4)&&
      (board[i-c][j-c]!=0&&board[i-(c+1)][j-(c+1)]!=0&&board[i-(c+2)][j-(c+2)]!=0&&board[i-(c+3)][j-(c+3)]!=0))
     {
      if(board[i-c][j-c]+board[i-(c+1)][j-(c+1)]+board[i-(c+2)][j-(c+2)]+board[i-(c+3)][j-(c+3)]==8)
      {
       cout<<"player 2 won !\n";
       return true;
      }
      else
      {
       cout<<"player 1 won !\n";
       return true;
      }
     }
    
    }
   }

   if((j==5&&i==6)||(j==6&&i==5))
   {
    for(int c=0;c<3;c++)
    {
     if((board[i-c][j-c]+board[i-(c+1)][j-(c+1)]+board[i-(c+2)][j-(c+2)]+board[i-(c+3)][j-(c+3)]==8||
      board[i-c][j-c]+board[i-(c+1)][j-(c+1)]+board[i-(c+2)][j-(c+2)]+board[i-(c+3)][j-(c+3)]==4)&&
      (board[i-c][j-c]!=0&&board[i-(c+1)][j-(c+1)]!=0&&board[i-(c+2)][j-(c+2)]!=0&&board[i-(c+3)][j-(c+3)]!=0))
     {
      if(board[i-c][j-c]+board[i-(c+1)][j-(c+1)]+board[i-(c+2)][j-(c+2)]+board[i-(c+3)][j-(c+3)]==8)
      {
       cout<<"player 2 won !\n";
       return true;
      }
      else
      {
       cout<<"player 1 won !\n";
       return true;
      }
     }
    
    }
   }

   if(j==4&&i==6||(j==6&&i==4))
   {
    for(int c=0;c<2;c++)
    {
     if((board[i-c][j-c]+board[i-(c+1)][j-(c+1)]+board[i-(c+2)][j-(c+2)]+board[i-(c+3)][j-(c+3)]==8||
      board[i-c][j-c]+board[i-(c+1)][j-(c+1)]+board[i-(c+2)][j-(c+2)]+board[i-(c+3)][j-(c+3)]==4)&&
      (board[i-c][j-c]!=0&&board[i-(c+1)][j-(c+1)]!=0&&board[i-(c+2)][j-(c+2)]!=0&&board[i-(c+3)][j-(c+3)]!=0))
     {
      if(board[i-c][j-c]+board[i-(c+1)][j-(c+1)]+board[i-(c+2)][j-(c+2)]+board[i-(c+3)][j-(c+3)]==8)
      {
       cout<<"player 2 won !\n";
       return true;
      }
      else
      {
       cout<<"player 1 won !\n";
       return true;
      }
     }
    
    }
   }

   if(i==6&&j==3||(j==6&&i==3))
   {
    if((board[i][j]+board[i-1][j-1]+board[i-2][j-2]+board[i-3][j-3]==8||
     board[i][j]+board[i-1][j-1]+board[i-2][j-2]+board[i-3][j-3]==4)&&
     (board[i][j]!=0&&board[i-1][j-1]!=0&&board[i-2][j-2]!=0&&board[i-3][j-3]!=0))
    {
     if(board[i][j]+board[i-1][j-1]+board[i-2][j-2]+board[i-3][j-3]==8)
     {
      cout<<"player 2 won !\n";
      return true;
     }
     else
     {
      cout<<"player 1 won !\n";
      return true;
     }
    }
   }
  }
 }
 return false;
}

// check wether the board is full or not
bool Connect4Game::BoardFull()
{
 static int turnCount=0;
 turnCount++;
 if(turnCount==49)
 {
  cout<<"The match is draw /n";
  return true;
 }
 return false;
}
void Connect4Game::start()
{
 bool flag=true;
 showBoard();
 while(flag==true)
 {
  int columno=0;
  bool flag2=true;
  do                             // take input from user
  {
   cout<<"Player "<<turn<<" enter : ";
   cin>>columno;
  }while(columno<1||columno>7);
  columno--;

  for(int i=6;i>=0&&flag2==true;i--) // put the respective label in the desired cell
  {
   if(board[i][columno]==0)
   {
    board[i][columno]=turn;
    flag2=false;
   }
  }
  if(flag2==true)
   cout<<"The board has not column no"<<columno<<" available\n";
  showBoard();  // show the board
  flag=Won();    // check wether any player win or not
  
  if(flag==false)  // if no one win
  {
   flag=BoardFull(); //check board status
   if(flag==false)    // if board is not full
   {
    switchTurn();  // toggle turn
    flag=true;
   }
   else
    flag=false;
  }
  else
   flag=false;
 }
}


Connect4Game::~Connect4Game()
{
 cout<<"\n\n\t    Thanks for playing \n\n\n";
}
