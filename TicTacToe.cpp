#include <graphics.h>
#include <conio.h>
#include <iostream>


char board[3][3];
int currentPlayer = 1;
int cellHeight = 150; 
int cellWidth = 150;  
int topMargin = 100;  
int leftMargin = 100; 

int playerTurnXCoord = 550;
int playerTurnYCoord = 30;

int conclusionAnnouncXCoord = 600;
int conclusionAnnouncYCoord = 350;

// Initialize the graphics window
void windowOpen() {
    int width = 1000, height = 600;
    initwindow(width, height, "Tic Tac Toe");
}

// Hamro Loading Window
void loadingWindow() {
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 7);
    outtextxy(280, 250, "TIC TAC TOE");
    
    
    rectangle(280, 350, 700, 370);

    for (int i = 0; i <= 420; i += 5) {
        setfillstyle(SOLID_FILL, YELLOW);
        bar(280, 352, 280 + i, 369);
        delay(50);
    }
    delay(400);
    cleardevice();
}

// Initialize the board
void initBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}


// Game Grid
void drawGrid() {
    cleardevice();
    
    // Draw vertical and horizontal lines
    for (int i = 1; i < 3; i++) {
        line(leftMargin + i * cellWidth, topMargin, leftMargin + i * cellWidth, topMargin + 3 * cellHeight); // Vertical lines
        line(leftMargin, topMargin + i * cellHeight, leftMargin + 3 * cellWidth, topMargin + i * cellHeight); // Horizontal lines
    }
}

// Draw X or O in the grid
void drawXO(int row, int col, char symbol) {
	
    
    // Calculate the X and Y position to center the symbol in the cell
   	int x = leftMargin + col * cellWidth + cellWidth / 2; 
    int y = topMargin + row * cellHeight + cellHeight / 2; 
    
//    std :: cout << "X Position : "<<x << " & Y Positon : " << y << std::endl;

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);  

    char str[2]; 
    str[0] = symbol;  
    str[1] = '\0';  

    
    setcolor(YELLOW);
    outtextxy(x - textwidth(str) / 2, y - textheight(str) / 2, str); 
}




// Update the game board visually
void updateBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 'X' || board[i][j] == 'O') {
                drawXO(i, j, board[i][j]);
            }
        }
    }
}


// Check for a winner
bool checkWinner() {
	
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
    	// Row match
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            {
            	return true;
			}  
            
        // Column match
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            {
            	return true; 
			} 
    }

    // Check diagonals
    
    // Main diagonal
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
       { 
	   return true;  
	   }
        
    // Anti-diagonal
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
	{
        return true;
	}

    return false;
}

// Check for a draw
bool checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') 
                return false;
        }
    }
    return true;
}

// Handle user input (mouse clicks)
void handleInput() {
		//Player Turn Card
		setcolor(YELLOW);
    	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    	char playerTurn[50];
    	sprintf(playerTurn, "Turn : Player %d",currentPlayer);
    	outtextxy(playerTurnXCoord,playerTurnYCoord,playerTurn);
    while (1) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x = mousex(), y = mousey();
//            std::cout << "Mouse X : "<<x << " & Mouse Y :" << y << std::endl;
            clearmouseclick(WM_LBUTTONDOWN);


            // Calculate the row and column based on click position
            int row = (y - topMargin) / cellHeight;
            int col = (x - leftMargin) / cellWidth;

            // Click gareko Thau Inside Board chaki chain Check garne
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                
				// Update the board
                board[row][col] = (currentPlayer == 1) ? 'X' : 'O';
                drawXO(row, col, board[row][col]);
                
                //Player ko Turn Dekhaune
                if(currentPlayer==1){
                	setcolor(YELLOW);
                	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
                	char playerTurn[50];
                	sprintf(playerTurn, "Turn : Player %d",currentPlayer+1);
                	outtextxy(playerTurnXCoord,playerTurnYCoord,playerTurn);
				}
				else if(currentPlayer==2){
					setcolor(YELLOW);
                	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
                	char playerTurn[50];
                	sprintf(playerTurn, "Turn : Player %d",currentPlayer-1);
                	outtextxy(playerTurnXCoord,playerTurnYCoord,playerTurn);
				}

                // Check for winner or draw
                if (checkWinner()) {
                    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
                    char winMessage[50];
                    sprintf(winMessage, "Player %d Wins!", currentPlayer);
                    outtextxy(conclusionAnnouncXCoord, conclusionAnnouncYCoord, winMessage);
                    delay(2000);
                    return;
                } else if (checkDraw()) {
                    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(conclusionAnnouncXCoord, conclusionAnnouncYCoord, "It's a Draw!");
                    delay(2000);
                    return;
                }

                // Switch player
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
        }
    }
}



// Game Window
void gameWindow() {
    
    initBoard();
    drawGrid();
    updateBoard();
    handleInput();
}

void instructionsWindow() {
    cleardevice();
    int startX = getmaxx()/4;
    int currentY = 0;
    int lineSpacing = 20;
    int sectionSpacing = 40;

    struct InstructionSection {
        char* heading;
        int headingSize;
        char* body[10]; 
        int bodySize; //fontsize
        int bodyLineCount;
    };

    InstructionSection sections[] = {
        {
            "How To Play", 5,
            {
                "Player 1 plays as X, and Player 2 plays as O.",
                "Use the mouse to click on a cell to place your mark.",
                "The game automatically switches turns after each move."
            }, 3, 3
        },
        {
            "Control", 5,
            {
                "Mouse Click : Place your mark on the board",
                "Up/Down Arrow Keys : Navigate the menu.",
                "Press 'B' : Go back to the menu from the instructions window.",
                "Enter Key : Select a menu option."
            }, 3, 4
        },
        {
            "Winning the Game", 5,
            {
                "A player wins if they have three of their marks (X or O) in a row, column, or diagonal",
                "If all cells are filled and no one has won, the game ends in a draw."
            }, 3, 2
        }
    };

 
    for (int s = 0; s < 3; s++) {
        // Draw heading
        setcolor(YELLOW);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, sections[s].headingSize);
        outtextxy(startX, currentY, (char*)(sections[s].heading));
        currentY += textheight(sections[s].heading) + lineSpacing;

        // Draw body lines
        
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, sections[s].bodySize);
        for (int i = 0; i < sections[s].bodyLineCount; i++) {
        	setcolor(WHITE);
            outtextxy(startX, currentY, (char*)(sections[s].body[i]));
            currentY += textheight(sections[s].body[i]) + lineSpacing / 2;
        }
        currentY += sectionSpacing;
    }

    // Input handling loop
    while (true) {
        if (kbhit() && getch() == 'b') {
            cleardevice();
            return;
        }
    }
}

// About Us Window
void aboutUsWindow() {
    cleardevice();
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
    int x = 330; //yo chai sabai text ko x position

    int aboutY = 0;       
    int toolsY = 600;
    
   //yo loop ko ekchoti move hunchha
    while (aboutY < 100 || toolsY > 300) {
        cleardevice();
        setcolor(WHITE);

        // yesko final fix position samma move garne
        if (aboutY < 100) aboutY += 5;
        outtextxy(x, aboutY, "About Us");

        // yesko ni final position sammai move garne,mathi launa each step ma 5 ghataune position bata
        if (toolsY > 300) toolsY -= 5;
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
        outtextxy(x, toolsY, "Tools Used");

        delay(50);
    }

    //yo loop ko ekchoti sangai move hunchhan
    int bodyY = -200;      // Body text starts above screen
    int detailsY = 640;    // Other details start below screen
    while (bodyY < 140 || detailsY > 340) {
        cleardevice();
        setcolor(WHITE);

        //agadi ko loop ko text yesma clear garda nahatos bhaner,feri text dekhako
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
        setcolor(YELLOW);
        outtextxy(x, 100, "About Us");
        outtextxy(x, 300, "Tools Used");

		setcolor(WHITE);
        if (bodyY < 140) bodyY += 5;
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
        outtextxy(x, bodyY, "Simple Tictactoe game.");
        outtextxy(x, bodyY + 40, "Developed by Ujjwal and Suman");
        outtextxy(x, bodyY + 80, "For Computer Graphics Project.");

        if (detailsY > 340) detailsY -= 5;
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
        outtextxy(x, detailsY, "C++");
        outtextxy(x, detailsY + 40, "Graphics.h");
        outtextxy(x, detailsY + 80, "Git and Github");

        delay(50);
    }


    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
    outtextxy(320, 500, "Press B to go back");

    // Wait for user input
    while (1) {
        if (kbhit() && getch() == 'b') {
            cleardevice();
            return;
        }
    }
}

// Exit Window with Confirmation
bool exitWindow() {
    cleardevice();
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
    outtextxy(190, 100, "Are you sure you want to exit?");
    setcolor(YELLOW);
    outtextxy(190, 300, "Press Y to confirm, N to cancel");

    while (1) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 'y' || ch == 'Y') {
                return true;
            } else if (ch == 'n' || ch == 'N') {
                cleardevice();
                return false;
            }
        }
    }
}

// Draw Menu Items
void drawMenu(int selectedOption) {
    cleardevice(); 
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 7);
    outtextxy(370, 50, "Menu");

    char* menuItems[] = { "1. Start Game", "2. Instructions", "3. About Us", "4. Exit" };
    int yPos[] = { 200, 250, 300, 350 }; //yeslai hatauna sakinx , direct top margin ni use garne , add gardai jane

    for (int i = 0; i < 4; i++) {
        if (i == selectedOption) {
            setcolor(YELLOW);
        } else {
            setcolor(WHITE);
        }
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
        outtextxy(330, 2*topMargin+i*50, menuItems[i]);
    }
    setcolor(WHITE);  // Reset color after menu drawing
}

void gameMenu() {
    int selectedOption = 0;
    drawMenu(selectedOption);

    while (true) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 0 || ch == 224) {  
                ch = getch();
                switch (ch) {
                case 72:  // Up arrow
                    selectedOption = (selectedOption > 0) ? selectedOption - 1 : 3;
                    break;

                case 80:  // Down arrow
                    selectedOption = (selectedOption < 3) ? selectedOption + 1 : 0;
                    break;
                }
                drawMenu(selectedOption);
            } else if (ch == 13) {  
                switch (selectedOption) {
                case 0:
                    gameWindow();
                    break;
                case 1:
                    instructionsWindow();
                    break;
                case 2:
                    aboutUsWindow();
                    break;
                case 3:
                    if (exitWindow()) {
                        return;
                    }
                    break;
                }
                drawMenu(selectedOption);  // Redraw menu after return
            }
        }
        delay(100);  
    }
}


int main() {
    // Open graphics window
    windowOpen();

    // Display the loading window
    loadingWindow();

    // Display the game menu
    gameMenu();

    // Close graphics window
    closegraph();
    return 0;
}

