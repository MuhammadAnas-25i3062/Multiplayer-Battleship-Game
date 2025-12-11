/*
 * BATTLESHIP GAME
 * A two-player naval strategy game
 * 
 * Features:
 * - Manual and random ship placement
 * - Turn-based combat
 * - Scoring system
 * - Game history/leaderboard
 * - Color-coded UI
 * 
 * Author: [Muhammad Anas Zahid]
 * Date: December 2025
 */

#include <iostream>
#include<iomanip>
#include <windows.h> 
#include <cstdlib>
#include<ctime>
#include <conio.h> 
#include<fstream> 
using namespace std;
char board1[10][10];
char board2[10][10];
char enemyboard[10][10];
char playerboard[10][10];
int size,color1,color2,activecolor;
int player1shipHits[5]={0,0,0,0,0};
int player2shipHits[5]={0,0,0,0,0};
int currentAttacker=1;
int p1shipsdestroyed=0;
int p2shipsdestroyed=0;
char currentShip='1';
void vsPlayer(char board1[10][10], char board2[10][10]);
void setRandomShips(char board[10][10]);
void placement(char board1[10][10], char board2[10][10]);
void clearScreen();
void setColor(int textColor, int bgColor);
void showGameMenu();
void initializeBoard(char board[10][10]);
void printBoard(char board[10][10],bool hideShips);
void manualShips(char board[10][10]);
void playerAttack(char opponentBoard[10][10], int &playerScore);
void printThreeBoards(char leftBoard[10][10], char middleBoard[10][10], char rightBoard[10][10], bool hideShips);
void colorShipPink(char board[10][10],int shipIndex);
void saveScore(string playerName, int score);     
void viewLeaderboard(); 
bool hit=false;

//resets the game so that leaderboard works properly 

void resetGame() 
{
    p1shipsdestroyed=0;
    p2shipsdestroyed=0;
    currentAttacker=1;
    
    for(int i=0;i<5;i++) 
	{
        player1shipHits[i]=0;
        player2shipHits[i]=0;
    }
    
    hit=false;
}

//score update function

void updateScore(int &score)
{
	if(hit)
        score+=10;   
    else
        score-=1;    
}

//color changes to pink if a ship is sunk completely

void colorShipPink(char board[10][10],int shipIndex)
{
    char id='1'+shipIndex; 

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(board[i][j]==id || board[i][j]=='X')
            {
                board[i][j]='P';   //I have to do it pink
            }
        }
    }
}


//For clearing Screen

void clearScreen() {
		system("CLS"); 

}

// Color codes

const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;
const int GREY = 8;

// Function to set console text and background color

void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

//funtion to print main menu

void showGameMenu()
{
cout<<"==============================================="<<endl;
    cout<<"          WELCOME TO BATTLESHIP GAME"<<endl;
    cout<<"==============================================="<<endl<<endl;
    cout<< setw(28) << "MAIN MENU" << endl;
    cout<<"-----------------------------------------------"<<endl;
    setColor(4,0);
    cout << "1.";
    setColor(7,0); 
    cout << "Start New Game"<<endl;
    setColor(4,0);
    cout << "2.";
    setColor(7,0);
    cout << "Instructions" << endl;
    setColor(4,0);
    cout << "3.";
    setColor(7,0);
    cout << "View History" << endl;
    setColor(4,0);
    cout << "4.";
    setColor(7,0);
    cout << "Exit" << endl;
    cout<<"-----------------------------------------------"<<endl<<endl;
}

//board initializing

void initializeBoard(char board[10][10])
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            board[i][j] = '~'; // water
        }
    }
}

//board printing

void printBoard(char board[10][10],bool hideShips) {
    
    cout<<"     ";
    for(int j=0;j<10;j++)
	cout<<j<<"     ";
    cout<<endl;

    cout<<"    +";
    for (int j=0;j<10;j++)
	cout<<"-----+";
    cout<<endl;

    for (int i=0;i<10;i++)
	{
        cout<<"  "<<i<<" ¦";

        for(int j=0;j<10;j++)
		 {
           char cell=board[i][j];
           if (hideShips && (cell>='1'&&cell<='5')) 
		   {
        setColor(7,1);
        cout<<"  ~  ";
          }
          else if(cell=='P')
            {
                setColor(0,5);   // PINK background
                cout<<"  X  ";
            }
            
            else if(cell=='~') 
			{
                setColor(7,1); 
				cout << "  ~  ";
            } 
			else if((cell>='1' && cell<='5')) 
			{
                setColor(7,activecolor);
				cout<<"  S  ";
            }
			else if(cell=='X') 
			{
                setColor(0,4); 
				cout<<"  X  ";
            }
			else if(cell=='O') 
			{
                setColor(0,8);cout<<"  O  ";
            } 
            

            setColor(7,0); 
            cout<<"¦";
        }
        cout<<endl;

        cout<<"    +";
        for (int j=0;j<10;j++)
		cout<<"-----+";
        cout<<endl;
    }
}

//manual ships placement

void manualShips(char board[10][10])
{

bool placed = false;
while(!placed)
{
	int row,col;
	char orientation;
	cout<<"Enter Starting row[0-9] : ";
	cin>>row;
	cout<<"Enter Starting column[0-9] : ";
	cin>>col;
	cout<<"If you want to place Horizontally, enter 'H', and 'V' to place vertically : ";
	cin>>orientation;
	bool canBeplace=true;
	
	//for horizontal
	
	if (orientation=='H' || orientation=='h')
	{
		if((col+size>10))
		{
		cout<<"Invalid Input, enter again"<<endl;
		continue;
	}
		for(int i=0;i<size;i++)
		{
			if(board[row][col+i]!='~')
			{
				cout<<"Invalid Input, enter again"<<endl;
				canBeplace=false;
			}
		}
		if(canBeplace)
		{
			for(int i=0;i<size;i++)
			{
				board[row][col+i]=currentShip;
				
			}
			placed = true;
		}
	}
	
	//for vertical
	
	if (orientation=='V' || orientation=='v')
	{
		if((row+size>10))
		{
		cout<<"Invalid Input, enter again"<<endl;
		continue;
	}
		for(int i=0;i<size;i++)
		{
			if(board[row+i][col]!='~')
			{
				cout<<"Invalid Input, enter again"<<endl;
				canBeplace=false;
			}
		}
		if(canBeplace)
		{
			for(int i=0;i<size;i++)
			{
				board[row+i][col]=currentShip;
			}
			placed = true;
		}
	}
}
}

//random placement of ships

void setRandomShips(char board[10][10])
{

bool placed = false;
while(!placed)
{
	int orientation=rand()%2;//horizontal ya vertical
	int row=rand()%10;
	int col=rand()%10;
	bool canBeplace=true;
	
	//for horizontal
	
	if (orientation==0)
	{
		if((col+size>10))
		continue;
		for(int i=0;i<size;i++)
		{
			if(board[row][col+i]!='~')
			{
				canBeplace=false;
			}
		}
		if(canBeplace)
		{
			for(int i=0;i<size;i++)
			{
				board[row][col+i]=currentShip;
				
			}
			placed = true;
		}
	}
	
	//for vertical
	
	if (orientation==1)
	{
		if((row+size>10))
		continue;
		for(int i=0;i<size;i++)
		{
			if(board[row+i][col]!='~')
			{
				canBeplace=false;
			}
		}
		if(canBeplace)
		{
			for(int i=0;i<size;i++)
			{
				board[row+i][col]=currentShip;
			}
			placed = true;
		}
	}
}
}

//printing three boards

void printThreeBoards(char leftBoard[10][10], char middleBoard[10][10], char rightBoard[10][10], bool hideShips)//middle board  doosry player ka board ka board with ships hidd
{
cout<<"     Player 2 Board                                    Opponent Board                                 Player 1 board"<<endl<<endl;

cout<<"   ";
for(int i=0;i<10;i++)//enemy board top
cout<<i<<" ";
cout<<"           ";//spaces for the next board(opponent board)

for(int i=0;i<10;i++)//opponent board top
cout<<i<<"     ";
cout<<"       ";//space for the player board(right board)

for(int i=0;i<10;i++)//player board top
cout<<i<<" ";
cout<<endl;
    
// Middle board top border
cout<< "                                 +";
for(int j = 0; j < 10; j++) cout << "-----+";
cout<<endl;
    
    //Left (enemy) Board
    for(int r=0;r<10;r++)
    {
        cout<<r<<"  ";
        for(int c=0;c<10;c++)
        {
            char cell=leftBoard[r][c];
            if(cell=='X'||cell=='P')
            {
                cell='X';
                cout<<cell<<" ";
            }
            else if(cell=='O')
            cout<<cell<<" ";
            else
                cout<<". ";
        }
        
        cout<<"     ";
        
        //Middle board 
        cout<<"  "<<r<<" ¦";
        for(int c=0;c<10;c++)
        {
            char cell=middleBoard[r][c];
            
            if(hideShips && (cell>='1'&&cell<='5'))
            {
                setColor(7,1);
                cout<<"  ~  ";
            }
             else if (cell=='P') 
			{
                setColor(0, 5);
                cout<<"  X  ";
            }
            else if(cell=='~')
            {
                setColor(7, 1);
                cout<<"  ~  ";
            }
            else if((cell>='1'&&cell<='5'))
            {
                setColor(7,activecolor);
                cout<<"  S  ";
            }
            else if(cell=='X')
            {
                setColor(0,4);
                cout<<"  X  ";
            }
            else if(cell=='O')
            {
                setColor(0,8);
                cout<<"  O  ";
            }
            
            setColor(7,0);
            cout<<"¦";
        }
        
        cout<<"     ";
        
        //right player board
        cout<<r<<"  ";
        for(int c=0;c<10;c++)
        {
            char cell=rightBoard[r][c];
            if(cell=='X'||cell=='P')
            {
                cell='X';
                cout<<cell<<" ";
            }
            else if(cell=='O')
            cout<<cell<<" ";
            else
                cout<<". ";
        }
        
        cout<<endl;
        
        
        cout<<"                                 +";
        for(int j=0;j<10;j++) 
		cout<<"-----+";
        cout<<endl;
    }
    cout<<endl;
}

//players attack function

void playerAttack(char opponentBoard[10][10], int &playerScore)
{
    int attRow,attCol;
    bool valid=false;

    while(!valid)
    {
        cout<<"Enter row to attack [0-9]: ";
        cin>>attRow;
        cout<<"Enter col to attack [0-9]: ";
        cin>>attCol;
        
        // Validations:
        if(attRow<0||attRow>9||attCol<0||attCol>9)
        {
            cout<<"Invalid Input, Enter Again!"<<endl;
            continue;
        }
        if(opponentBoard[attRow][attCol]=='X'||opponentBoard[attRow][attCol]=='O'||opponentBoard[attRow][attCol]=='P')
        {
            cout<<"Already Attacked! Try another cell."<<endl;
            continue;
        }
        
        valid=true;
    }
    
    char cell=opponentBoard[attRow][attCol];
    if(cell>='1'&&cell<='5')
    {
        opponentBoard[attRow][attCol]='X';
        
        setColor(4,0);
        cout<<endl<<"*** HIT! ***"<<endl;
        setColor(7,0);
         hit=true;                          
        updateScore(playerScore);  
        
        int shipSizes[5]={5,4,3,3,2};
        int shipIndex=cell- '1'; 
        
        if(currentAttacker==1)
        {
             player2shipHits[shipIndex]++;
            if(player2shipHits[shipIndex]==shipSizes[shipIndex])
            {
			    setColor(4,0);
                cout<<endl<<"=== SHIP DESTROYED! ==="<<endl<<endl;
                setColor(6,0);
                cout<<"Ship size "<<shipSizes[shipIndex]<<" sunk!"<<endl<<endl;
                setColor(7,0);
                
				colorShipPink(opponentBoard,shipIndex);
                p2shipsdestroyed+=1;
                cout<<"Ships destroyed: "<<p2shipsdestroyed<<"/5"<<endl<<endl;
            }
        }
        else //currentAttacker==2
        {
            player1shipHits[shipIndex]++;
            
            if(player1shipHits[shipIndex]==shipSizes[shipIndex])
            {
                setColor(4,0);
                cout<<endl<<"=== SHIP DESTROYED! ==="<<endl<<endl;
                setColor(6,0);
    
                cout<<"Ship size "<<shipSizes[shipIndex]<<" sunk!"<<endl<<endl;
                setColor(7,0);
                colorShipPink(opponentBoard, shipIndex);
                p1shipsdestroyed+=1;
                cout<<"Ships destroyed: "<<p1shipsdestroyed<<"/5"<<endl<<endl;
            }   
        }
         cout<<"Score: "<<playerScore<<endl; 
    }
    else if(cell=='~')
    {
        // MISS!
        opponentBoard[attRow][attCol]='O';
        
        setColor(8,0);
        cout<<endl<<"--- MISS ---"<<endl;
        setColor(7,0);
        hit = false;     
        updateScore(playerScore);   
	    cout<<"Score: "<<playerScore<<endl; 
    }
}

//vs player function

void vsPlayer(char board1[10][10], char board2[10][10])
{
resetGame();
cout<<"================================================"<<endl;
cout<<"                   Player 1"<<endl;
cout<<"================================================"<<endl<<endl<<endl;
cout<<"=================Ship Placement================="<<endl<<endl;
start:
	cout<<"Choose your ship colour : ";
	cout<<endl<<endl;
	setColor(3,0);
	cout<<"1. cyan"<<endl;
	setColor(6,0);
	cout<<"2. Yellow"<<endl;
	setColor(5,0);
	cout<<"3. Magenta"<<endl;
	setColor(2,0);
	cout<<"4. Green "<<endl;
	setColor(7,0);
	cin>>color1;
	activecolor=color1;
	 switch(color1)
    {
        case 1:activecolor=CYAN; 
		break;     
        case 2:activecolor=YELLOW; 
		break;   
        case 3:activecolor=MAGENTA; 
		break;  
        case 4:activecolor=GREEN; 
		break;    
        
    }
    int ship;
    cout<<endl<<"Choose Your ship to place  : "<<endl<<endl;
    setColor(4,0);
cout<<"1.";
setColor(7,0);
    cout<<" AirCraft carrier - 5 blocks "<<endl;
    setColor(4,0);
    cout<<"2.";
    setColor(7,0);
    cout<<" Battleship - 4 blocks"<<endl;
    setColor(4,0);
    cout<<"3.";
    setColor(7,0);
    cout<<" Destroyer - 3 blocks"<<endl;
    setColor(4,0);
    cout<<"4.";
    setColor(7,0);
    cout<<" Submarine - 3 blocks"<<endl;
    setColor(4,0);
    cout<<"5.";
    setColor(7,0);
    cout<<" Patrol Boat - 2 blocks"<<endl;
    string shipNames[5] = {"Aircraft Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat"};
    int shipSizes[5]    = {5, 4, 3, 3, 2};
    cin>>ship;
    size=shipSizes[ship-1];
    int index=ship-1;
    currentShip='1'+index;
    initializeBoard(board1);
    printBoard(board1,false);
    int placement;
    cout<<"Choose placement option : "<<endl;
    cout<<"1. Manual "<<endl;
    cout<<"2. Random "<<endl;
    cin>>placement;
    switch(placement)
    {
    	case 1: {
    		manualShips(board1);
    		printBoard(board1,false);
			break;
		}
		case 2:{
			setRandomShips(board1);
			printBoard(board1,false);
			break;
		}
}
for(int i=0;i<5;i++)
{
    if(i==index)    // pehly wali ship!
    continue;
    currentShip='1'+i;
    size=shipSizes[i];

    cout << "You have one ship of size " << size << " to place."<<endl;
    cout << "Choose placement option:\n";
    cout << "1. Manual\n";
    cout << "2. Random\n";

    int choice;
    cin>>choice;

    if(choice==1)
    {
       manualShips(board1);
       printBoard(board1,false);
    }
    else if(choice==2)
    {
        setRandomShips(board1);
        printBoard(board1,false);
    }
    else
    {
        cout << "Invalid option! Using random.\n";
        setRandomShips(board1);
        printBoard(board1,false);
    }
}

char confirmation;
cout<<"Confirm placement ? (Y,N) "<<endl;
cin>>confirmation;
if(confirmation=='Y'||confirmation=='y')
{
	printBoard(board1,true);

	cout << "\nPress any key to continue...";
    getch();
    clearScreen();
}
else if(confirmation=='N'||confirmation=='n')
{
	goto start; 
}
else 
{
cout<<"Invalid Input, Place again "<<endl<<endl;
goto start;

}

cout<<"================================================"<<endl;
cout<<"                   Player 2"<<endl;
cout<<"================================================"<<endl<<endl<<endl;
cout<<"=================Ship Placement================="<<endl<<endl;
start2:
	cout<<"Choose your ship colour : ";
	cout<<endl<<endl;
	setColor(3,0);
	cout<<"1. cyan"<<endl;
	setColor(6,0);
	cout<<"2. Yellow"<<endl;
	setColor(5,0);
	cout<<"3. Magenta"<<endl;
	setColor(2,0);
	cout<<"4. Green "<<endl;
	setColor(7,0);
	cin>>color2;
	activecolor=color2;
	switch(color2)
    {
    case 1:activecolor=CYAN; 
	break;     
    case 2:activecolor=YELLOW; 
	break;   
    case 3:activecolor=MAGENTA; 
	break;  
    case 4:activecolor=GREEN; 
	break;    
       
    }
initializeBoard(board2);
printBoard(board2,false);
int ship2;
    cout<<endl<<"Choose Your ship to place  : "<<endl<<endl;
setColor(4,0);
cout<<"1.";
setColor(7,0);
    cout<<" AirCraft carrier - 5 blocks "<<endl;
    setColor(4,0);
    cout<<"2.";
    setColor(7,0);
    cout<<" Battleship - 4 blocks"<<endl;
    setColor(4,0);
    cout<<"3.";
    setColor(7,0);
    cout<<" Destroyer - 3 blocks"<<endl;
    setColor(4,0);
    cout<<"4.";
    setColor(7,0);
    cout<<" Submarine - 3 blocks"<<endl;
    setColor(4,0);
    cout<<"5.";
    setColor(7,0);
    cout<<" Patrol Boat - 2 blocks"<<endl;
    string shipNames2[5] = {"Aircraft Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat"};
    int shipSizes2[5]    = {5, 4, 3, 3, 2};
    cin>>ship2;
    int index2=ship2-1;
    size=shipSizes2[ship2-1];
    currentShip='1'+index2;
    int placement2;
    cout<<"Choose placement option : "<<endl;
    cout<<"1. Manual "<<endl;
    cout<<"2. Random "<<endl;
    cin>>placement2;
    switch(placement2)
    {
    	case 1: {
    		manualShips(board2);
    		printBoard(board2,false);
			break;
		}
		case 2:{
			setRandomShips(board2);
			printBoard(board2,false);
			break;
		}
}
for(int i=0;i<5;i++)
{
    if(i==index2)    // pehly wali ship!
    continue;
    currentShip='1'+i;
    size=shipSizes2[i];

    cout<<"You have one ship of size " << size << " to place."<<endl;
    cout<<"Choose placement option: "<<endl;
    cout<<"1. Manual "<<endl;
    cout<<"2. Random "<<endl;

    int choice;
    cin>>choice;

    if(choice==1)
    {
       manualShips(board2);
    		printBoard(board2,false);
    }
    else if(choice==2)
    {
        setRandomShips(board2);
        printBoard(board2,false);
    }
    else
    {
        cout<<"Invalid option! Using random."<<endl;
        setRandomShips(board2);
        printBoard(board2,false);
    }
}
char confirmation2;
cout<<"Confirm placement ? (Y,N) "<<endl;
cin>>confirmation2;
if(confirmation2=='Y'||confirmation2=='y')
{
	printBoard(board2,true);
	cout << "\nPress any key to continue...";
    getch();
    clearScreen();
}
else if(confirmation2=='N'||confirmation2=='n')
{
	goto start2; 
}
else 
{
cout<<"Invalid Input, Place again "<<endl<<endl;
goto start2;

}

int p1fires=6;
int p2fires=6;
int player1Score=0;
int player2Score=0;

bool gameover=false;

while(!gameover)
{
    // PLAYER 1 TURN
    if(currentAttacker==1)
    {
        clearScreen();
        cout<<"==============================================="<<endl;
        cout<<"              PLAYER 1's TURN" << endl;
        cout<<"==============================================="<<endl;
        cout<<"Fires remaining: "<<p1fires<<endl;
        cout<<"Ships destroyed: "<<p2shipsdestroyed<<" "<<endl<<endl;
        //copy to enemy board
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                 if(board2[i][j]=='X'||board2[i][j]=='P')
                    enemyboard[i][j]='X';
                else if(board2[i][j]=='O')
                    enemyboard[i][j]=board2[i][j];
            }
        }
        
       // Printing boards BEFORE attacks
        printThreeBoards(enemyboard,board2,playerboard,true);
        //in start fires are 6 and then they would decrease
        p1fires=6-p1shipsdestroyed;
        for(int fire=0;fire<p1fires;fire++)
        {
            cout<<endl<<" Fire "<<(fire + 1)<<"/"<<p1fires<<endl;
            playerAttack(board2,player1Score);
            if(p2shipsdestroyed==5)
            {
                clearScreen();
                setColor(2,0);
                cout<<endl<<"==============================================="<<endl;
                cout<<"          PLAYER 1 WINS!" << endl;
                cout<<"     ALL ENEMY SHIPS DESTROYED!" << endl;
                cout<<"==============================================="<<endl<<endl;
                setColor(7,0);
                gameover=true;
                 saveScore("Player1",player1Score);
                saveScore("Player2",player2Score); 
                cout<<endl<<"Press any key to return to main menu...";
                getch();              
                return;   
            }
            if (player1Score>=150) 
			{
            clearScreen();
            setColor(2,0);
            cout<<endl<<"PLAYER 1 WINS BY REACHING 150 POINTS!" << endl;
            setColor(7,0);
            gameover=true;
            saveScore("Player1",player1Score);
            saveScore("Player2",player2Score); 
            cout<<endl<<"Press any key to return to main menu...";
            getch();              
            return;  
            }
        }
        
        if(gameover)
		break;
        
        
        //board after all attacks
        clearScreen();
        cout<<"Player 1's attacks completed!"<<endl<<endl;
        
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(board2[i][j]=='X'||board2[i][j]=='P')
                    enemyboard[i][j]='X';
                else if(board2[i][j]=='O')
                    enemyboard[i][j]=board2[i][j];
            }
        }
        
        printThreeBoards(enemyboard, board2, playerboard, true);
        
        cout<<"Press any key for Player 2's turn...";
        getch();
        currentAttacker = 2;
    }
    
    // PLAYER 2 TURN
    else
    {
        clearScreen();
        cout<<"==============================================="<<endl;
        cout<<"              PLAYER 2's TURN"<<endl;
        cout<<"==============================================="<<endl;
        cout<<"Fires remaining: "<<p2fires<<endl;
        cout<<"Ships destroyed: "<<p1shipsdestroyed<<" "<<endl<<endl;
    
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(board1[i][j]=='X'||board1[i][j]=='P')
                    playerboard[i][j]='X';
                else if(board1[i][j]=='O')
                    playerboard[i][j]=board1[i][j];
            }
        }
    
        printThreeBoards(enemyboard,board1,playerboard,true);
        	p2fires=6-p2shipsdestroyed;
        for(int fire=0;fire<p2fires;fire++)
        {
            cout<<endl<<" Fire "<<(fire + 1)<<"/"<<p2fires<<endl;
            playerAttack(board1,player2Score);
            
            // Check if all ships destroyed
            if(p1shipsdestroyed==5)
            {
                clearScreen();
                setColor(2,0);
                cout<<endl<<"==============================================="<<endl;
                cout<<"          PLAYER 2 WINS!"<<endl;
                cout<<"     ALL ENEMY SHIPS DESTROYED!"<<endl;
                cout<<"==============================================="<<endl;
                setColor(7,0);
                gameover=true;
                saveScore("Player1",player1Score);
                saveScore("Player2",player2Score); 
                 cout<<endl<<"Press any key to return to main menu...";
                getch();              
                return;  
            }
             if (player2Score>=150) 
			 {
                clearScreen();
                setColor(2,0);
                cout<<endl<<"PLAYER 2 WINS BY REACHING 150 POINTS!"<<endl;
                setColor(7,0);
                saveScore("Player1",player1Score);
                saveScore("Player2",player2Score);
                gameover=true;
                 cout<<endl<<"Press any key to return to main menu...";
                getch();              
                return;  
             }
        }
        
        if(gameover) 
		break;

        
        // Show final board after all attacks
        clearScreen();
        cout<<"Player 2's attacks completed!"<<endl<<endl;
        
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
               if(board1[i][j]=='X'||board1[i][j]=='P')
                    playerboard[i][j]='X';
                else if(board1[i][j]=='O')
                    playerboard[i][j]=board1[i][j];
            }
        }
        
        printThreeBoards(enemyboard,board1,playerboard,true);
        
        cout<<"Press any key for Player 1's turn...";
        getch();
        currentAttacker = 1;
    }
}

cout<<"Final Scores:"<<endl;
cout<<"Player 1 score : "<<player1Score<<endl;
cout<<"Player 2 score : "<<player2Score<<endl;
cout<<"Press any key to return to main menu...";
getch();
clearScreen();
showGameMenu();
}
void saveScore(string playerName, int score) {
    ofstream file;
    file.open("leaderboard.txt", ios::app); // append mode
    
    if(file.is_open()) {
        file << playerName << " " << score << endl;
        file.close();
    }
    else {
        cout << "\nError: Could not save score!" << endl;
    }
}

//History
void viewLeaderboard() 
{
    ifstream file("leaderboard.txt");
    
    if(!file.is_open()) 
    {
        clearScreen();
        cout<<"==============================================="<<endl;
        cout<<"              LEADERBOARD" << endl;
        cout<<"==============================================="<<endl;
        cout<<endl<<"No scores recorded yet!"<<endl;
        cout<<endl<<"Press any key to return to Main Menu...";
        getch();
        clearScreen();
        return;
    }
    string names[100];
    int scores[100];
    int count = 0;
    
    while(file >> names[count] >> scores[count] && count < 100) 
    {
        count++;
    }
    file.close();
    
    clearScreen();
    cout<<"==============================================="<<endl;
    cout<<"              LEADERBOARD" << endl;
    cout<<"==============================================="<<endl<<endl;
    
    if(count == 0) 
    {
        cout<<endl<<"No scores found!"<<endl;
        cout<<"===============================================" << endl;
        cout<<endl<<"Press any key to return to Main Menu...";
        getch();
        clearScreen();
        return;
    }
    
    cout<<left<<setw(10)<<"Game #"<<setw(20)<<"Player 1"<<setw(20)<<"Player 2"<<setw(15)<<"Winner"<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
    
    int gameNumber = 1;
    
    
    for(int i=0;i<count;i+=2) 
    {
        if(i + 1<count) 
        {
            int p1Score=scores[i];
            int p2Score=scores[i + 1];
            string winner;
            
            if(p1Score>p2Score)
                winner="Player 1";
            else if(p2Score>p1Score)
                winner="Player 2";
            else
                winner="Tie";
            
            cout<<left<<setw(10)<<gameNumber;
            
            if(p1Score>p2Score)
                setColor(2, 0); 
            else
                setColor(7, 0);
            cout<<setw(20)<<p1Score;
    
            if(p2Score>p1Score)
                setColor(2, 0);  
            else
                setColor(7, 0); 
            cout<<setw(20)<<p2Score;
            setColor(6, 0); 
            cout<<setw(15)<<winner<<endl;
            setColor(7, 0);             
            gameNumber++;
        }
    }
    
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<endl<<"Total Games Played: "<<(gameNumber - 1)<<endl;
    cout<<"===============================================" << endl;
    cout<<endl<<"Press any key to return to Main Menu...";
    getch();
    clearScreen();

// main function

}

int main()
{
	srand(time(0));
	while(true)
	{
	clearScreen();
	showGameMenu();
	
	int choice;
    cout<<"Enter your choice (1-4): ";
    cin>>choice;
    switch(choice)
    {
        case 1:
        	{
    			clearScreen();
    			      cout<<"==============================================="<<endl;
    			cout<<endl<<"---------------Starting New Game---------------"<<endl<<endl;
    			      cout<<"==============================================="<<endl<<endl;
                		
                		vsPlayer(board1,board2);
                		break;		
			}
		case 2:
			{
				clearScreen();
				cout<<"------------------------------------------------"<<endl;
				cout<<setw(30)<<"Instructions"<<endl;
				cout<<"------------------------------------------------"<<endl<<endl;
				setColor(4,0);
                cout<<"1.";
                setColor(7,0); 
                cout<<" Place your ships on the board."<<endl;
                setColor(4,0);
                cout<<"2.";
                setColor(7,0); 
                cout<<" Player 1 and Player 2 take turns firing shots."<<endl;
                setColor(4,0);
                cout<<"3.";
                setColor(7,0); 
                cout<<" 'O' means MISS, 'X' means HIT."<<endl;
                setColor(4,0);
                cout<<"4.";
                setColor(7,0); 
                cout<<" Sink all enemy ships to win!"<<endl;
                setColor(4,0);
                cout<<"5.";
                setColor(7,0); 
                cout<<" Your score is based on accuracy and speed."<<endl;
                cout<<"------------------------------------------------"<<endl<<endl;
                cout<<"Press any key to return to Main Menu..."<<endl;
                getch();
                clearScreen();
                showGameMenu();
                break;
			}
		case 3:
			{
				viewLeaderboard();
				break;
			}
		case 4:
		    {
		    	clearScreen();
		    	setColor(4,0);
                cout<<"Exiting..."<<endl;
                return 0;
            }
            default:
                cout<<"Invalid option! Try again."<<endl;
	}
}
return 0;
}
