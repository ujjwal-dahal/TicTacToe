#include <graphics.h>
#include <conio.h>
#include <iostream>


char board[3][3];
int currentPlayer = 1;

// Initialize the graphics window
void windowOpen() {
    int width = 1000, height = 600;
    initwindow(width, height, "Tic Tac Toe Game");
}

// Hamro Loading Window
void loadingWindow() {
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 7);
    outtextxy(330, 250, "Loading...");
    rectangle(330, 350, 610, 370);

    for (int i = 0; i <= 280; i += 5) {
        setfillstyle(SOLID_FILL, RED);
        bar(330, 351, 330 + i, 369);
        delay(50);
    }

    delay(500);
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
    
    // Vertical Lines
    line(200, 100, 200, 450);  // First vertical line
    line(400, 100, 500, 450);  // Second vertical line
  
    // Horizontal Lines
    line(100, 250, 600, 250);  // First horizontal line
    line(100, 350, 600, 350);  // Second horizontal line
}

// Draw X or O in the grid
void drawXO(int row, int col, char symbol) {
    // Calculate the X and Y position to center the symbol in the cell
    int x = 150 + col * 100;  // X position (column)
    int y = 200 + row * 100;  // Y position (row)
    std :: cout << "X Position : "<<x << " & Y Positon : " << y << std::endl;

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);  // Set the font size

    char str[2];  // Array to hold the character and null terminator
    str[0] = symbol;  // Assign the character
    str[1] = '\0';  // Null-terminate the string

    // Position the text slightly adjusted to center it within the grid cell
    setcolor(YELLOW);
    outtextxy(x - 20, y - 30, str);  // Adjusted the x and y to center the text better
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
       { return true;  
	   }
        
    // Anti-diagonal
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        return true;
	}

    return false;
}

// Check for a draw
bool checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')  // Empty cell found
                return false;
        }
    }
    return true;
}

// Handle user input (mouse clicks)
void handleInput() {
    while (1) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x = mousex(), y = mousey();
            std::cout << "Mouse X : "<<x << " & Mouse Y :" << y << std::endl;
            clearmouseclick(WM_LBUTTONDOWN);

            // Calculate the row and column based on click position
            int row = (y - 100) / 100;
            int col = (x - 100) / 100;

            // Check if the click is inside the board and the cell is empty
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
                outtextxy(550,30,playerTurn);
				}
				else if(currentPlayer==2){
					setcolor(YELLOW);
                settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
                char playerTurn[50];
                sprintf(playerTurn, "Turn : Player %d",currentPlayer-1);
                outtextxy(550,30,playerTurn);
				}

                // Check for winner or draw
                if (checkWinner()) {
                    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
                    char winMessage[50];
                    sprintf(winMessage, "Player %d Wins!", currentPlayer);
                    outtextxy(550, 330, winMessage);
                    delay(2000);
                    return;
                } else if (checkDraw()) {
                    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(550, 330, "It's a Draw!");
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

// Instruction Window
void instructionsWindow() {
    cleardevice();
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
    outtextxy(330, 100, "Instructions Window");
    outtextxy(330, 300, "Press B to go back");
    while (1) {
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
    outtextxy(330, 100, "About Us Window");
    
    outtextxy(320, 300, "Press B to go back");
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
    outtextxy(330, 100, "Are you sure you want to exit?");
    setcolor(RED);
    outtextxy(270, 300, "Press Y to confirm, N to cancel");

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
    cleardevice();  // Clear screen before drawing
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 7);
    outtextxy(330, 50, "Tic Tac Toe");

    char* menuItems[] = { "1. Start Game", "2. Instructions", "3. About Us", "4. Exit" };
    int yPos[] = { 200, 250, 300, 350 };

    for (int i = 0; i < 4; i++) {
        if (i == selectedOption) {
            setcolor(YELLOW);
        } else {
            setcolor(WHITE);
        }
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
        outtextxy(330, yPos[i], menuItems[i]);
    }
    setcolor(WHITE);  // Reset color after menu drawing
}

void gameMenu() {
    int selectedOption = 0;
    drawMenu(selectedOption);

    while (true) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 0 || ch == 224) {  // Special key
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
            } else if (ch == 13) {  // Enter key
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
        delay(100);  // Prevent CPU overuse
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

