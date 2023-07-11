// NimaMahanloo_Battleship.CPP
// Nima Mahanloo - CISP 400
// 03/01/2018
#include <iostream>
#include <random>
#include <ctime>
using namespace std;
// Class Ship friend with Battleship class
class ship
{
    public :
        friend class battleShip;
        ship();
    private:
        int shipSize;
        char shipModel;
};
// Class Battleship as main program class
class battleShip
{
    public:
        battleShip();
        void gameBoard();
        void mainMenu();
        char shipDirection();
        bool shipPosition(ship, char);
        void boardArrangement (char);
        void gameShot(char);
        int gameMentor(char);
        void displayBoard();
        void showGameMap(char);
        bool getGameOver();
        void setGameOver(bool);
        void resetSuccessfulShots();
        void futureShotsReset();
    private:
        char board [11][11];
        char ships [11][11];
        bool successShots[10];
        int successShotsX[10];
        int successShotsY[10];
        char successShotsShip[10];
        int successShotsSize[10];
        bool futureShots[10];
        int futureShotsX[10];
        int futureShotsY[10];
        char futureShotsShip[10];
        int futureShotsSize[10];
        char boardSign;
        char mapSign;
        char columnLetter;
        char rowNumber;
        char hitShot;
        char missedShot;
        char playerSide;
        bool firstRun;
        bool gameOver;
        bool missed;
        ship Carrier;
        ship Battleship;
        ship Cruiser;
        ship Submarine;
        ship Destroyer;
        int nShot, fCounter, destroyCounter;
        int cShow, bShow, uShow, sShow, dShow;
};
// Class Ship default constructor
ship::ship()
{
    shipSize = 1;
    shipModel = 'N';
}
// Class Battleship default constructor
battleShip::battleShip()
{
    boardSign = '+';
    mapSign = '-';
    columnLetter = 'a';
    rowNumber = '1';
    hitShot = 'x';
    missedShot = ' ';
    playerSide = '?';
    firstRun = true;
    gameOver = false;
    missed = false;
    nShot = -1;
    destroyCounter = 0;
    Carrier.shipModel = 'C';
    Carrier.shipSize = 5;
    Battleship.shipModel = 'B';
    Battleship.shipSize = 4;
    Cruiser.shipModel = 'U';
    Cruiser.shipSize = 3;
    Submarine.shipModel = 'S';
    Submarine.shipSize = 3;
    Destroyer.shipModel = 'D';
    Destroyer.shipSize = 2;
    cShow = 0; bShow = 0; uShow = 0; sShow = 0; dShow = 0, fCounter = -1;
    resetSuccessfulShots();
    futureShotsReset();
}
// A module to reset success shots points list what is useful for next computer moves and analyzes
void battleShip::resetSuccessfulShots()
{
    for (int i = 0; i < 10; i++)
    {
        successShots[i] = false;
        successShotsX[i] = 0;
        successShotsY[i] = 0;
        successShotsShip[i] = 'K';
        successShotsSize[i] = 0;
    }
}
// A module to reset AI's current ship success shots data's list
void battleShip::futureShotsReset()
{
    for (int i = 0; i < 10; i++)
    {
        futureShots[i] = false;
        futureShotsX[i] = 0;
        futureShotsY[i] = 0;
        futureShotsShip[i] = 'K';
        futureShotsSize[i] = 0;
    }
}
// A function to return private member as game over status (To access)
bool battleShip::getGameOver()
{
    return gameOver;
}
// A module to set private member value as game over status (mutator)
void battleShip::setGameOver(bool gameOver)
{
    this->gameOver = gameOver;
}
// A module to initial game board
void battleShip::gameBoard ()
{
    int boardSize = 11;
    int rCounter, cCounter;
    board[0][0] = ' ';
    ships[0][0] = ' ';
    for (rCounter = 1; rCounter < boardSize; rCounter++)
    {
        board[rCounter][0] = rowNumber;
        ships[rCounter][0] = rowNumber;
        rowNumber++;
        for (cCounter = 1; cCounter < boardSize; cCounter++)
        {
            board[rCounter][cCounter] = boardSign;
            ships[rCounter][cCounter] = mapSign;
            if (rCounter == 1)
            {
                board[0][cCounter] = columnLetter;
                ships[0][cCounter] = columnLetter;
                columnLetter++;
            }
        }
    }
}
// A module for the game start menu
void battleShip::mainMenu()
{
    if (firstRun == true)
    {
        cout << "<Battleship>" << endl << endl;
        while ((playerSide != 'l') && (playerSide != 'r') && (playerSide != 'q'))
        {
            cout << "Please select your side >" << endl << "('l' for Left, 'r' for right, 'q' for quit)" << endl;
            cin >> playerSide;
        }
        firstRun = false;
        if (playerSide == 'q')
        {
            gameOver = true;
        }
    }
}
// A character function to return randomized selected direction value for the ship position on the board for new game
char battleShip::shipDirection()
{
    int x, y;
    char shipDir = 'U';
    while (shipDir == 'U')
    {
        x = rand() % 5;
        y = rand() % 5;
        if (x < y)
        {
            shipDir = 'V';
        }
        else if (x > y)
        {
            shipDir = 'H';
        }
        else
        {
            shipDir = 'U';
        }
    }
    return shipDir;
}
// A boolean function to set the ship randomized position on the board for new game and return the process success status
bool battleShip::shipPosition(ship playerShip, char player)
{
    bool arrangeSuccess = true;
    char direction;
    int x, y, xEnd, yEnd, counter, start, endC;
    int shipLength = playerShip.shipSize;
    if (player == 'p')
    {
        if (playerSide == 'l')
        {
            start = 1;
            endC = 6;
        }
        else
        {
            start = 6;
            endC = 11;
        }
    }
    else
    {
        if (playerSide == 'l')
        {
            start = 6;
            endC = 11;
        }
        else
        {
            start = 1;
            endC = 6;
        }
    }
    direction = shipDirection();
    x = rand() % 5 + start;
    y = rand() % 10 + 1;
    if (direction == 'V')
    {
        yEnd = y + shipLength - 1;
        if ((ships [y][x] == mapSign) && (ships[yEnd][x] == mapSign) && (yEnd < 11))
        {
            for (counter = y+1; counter < yEnd; counter++)
            {
                if (ships[counter][x] != mapSign)
                {
                    arrangeSuccess = false;
                }
            }
            if (arrangeSuccess == true)
            {
                for (counter = y; counter <= yEnd; counter++)
                {
                    ships[counter][x] = playerShip.shipModel;
                }
            }
        }
        else
        {
            arrangeSuccess = false;
        }
    }
    else
    {
        xEnd = x + shipLength - 1;
        if ((ships [y][x] == mapSign) && (ships[y][xEnd] == mapSign) && (xEnd < endC))
        {
            for (counter = x+1; counter < xEnd; counter++)
            {
                if (ships[y][counter] != mapSign)
                {
                    arrangeSuccess = false;
                }
            }
            if (arrangeSuccess == true)
            {
                for (counter = x; counter <= xEnd; counter++)
                {
                    ships[y][counter] = playerShip.shipModel;
                }
            }
        }
        else
        {
            arrangeSuccess = false;
        }
    }
    return arrangeSuccess;
}
// A module to arrange and set up all ships on the player game board for new game
void battleShip::boardArrangement(char player)
{
    bool arrangeSuccess = false;
    while (!(arrangeSuccess))
    {
        arrangeSuccess = shipPosition(Carrier, player);
    }
    arrangeSuccess = false;
    while (!(arrangeSuccess))
    {
        arrangeSuccess = shipPosition(Battleship, player);
    }
    arrangeSuccess = false;
    while (!(arrangeSuccess))
    {
        arrangeSuccess = shipPosition(Cruiser, player);
    }
    arrangeSuccess = false;
    while (!(arrangeSuccess))
    {
        arrangeSuccess = shipPosition(Submarine, player);
    }
    arrangeSuccess = false;
    while (!(arrangeSuccess))
    {
        arrangeSuccess = shipPosition(Destroyer, player);
    }
}
// A module to make a shot and analyze computer shots as AI engine
void battleShip::gameShot(char player)
{
    char startCol = 0, endCol = 0, xChar = '0', yChar = '0';
    char *yStr = (char*)malloc(sizeof(char)); char *xStr = (char*)malloc(sizeof(char));
    xStr[1] = '\0';
    yStr[2] = '\0';
    int startC, endC, xInt, yInt;
    int x = -1, y = -1;
    int tempX = 0, tempY = 0, tempSize = 0;
    int aiShotRCounter, aiShotCCounter;
    char tempShip = 'k';
    bool error = false;
    bool shot = false;
    bool method = false;
    bool manualShot = true;
    while (shot == false)
    {
        // User shots
        if (player == 'p')
        {
            if (playerSide == 'l')
            {
                startCol = 'f';
                endCol = 'j';
            }
            else
            {
                startCol = 'a';
                endCol = 'e';
            }
            while (board[y][x] != boardSign)
            {
                if (error == true)
                {
                    cout << "Invalid location! Please select another location to shot!" << endl;
                    xChar = '0';
                    yChar = '0';
                }
                cout << endl << "Player 1 turn :" << endl << endl;
                while ((int(xChar) > int(endCol)) || (int(xChar) < int(startCol)) || (xStr[1] != '\0'))
                {
                    xStr[1] = '\0';
                    cout << "Enter your shot column location (" << startCol << " to " << endCol << ") > ";
                    cin >> xStr;
                    xChar = xStr[0];
                }
                while ((int(yChar) < 49) || (int (yChar) > 58) || (yInt < 1) || (yInt > 10) || (yStr[2] != '\0'))
                {
                    yStr[2] = '\0';
                    cout << "Enter your shot row location (1 to 10) > ";
                    cin >> yStr;
                    if (yStr[1] != '\0')
                    {
                        yInt = ((yStr[0]-48)*10)+(yStr[1]-48);
                    }
                    else
                    {
                        yInt = yStr[0]-48;
                    }
                    yChar = char(yInt+48);
                }
                cout << endl;
                x = int(xChar) - 96;
                y = int(yChar) - 48;
                error = true;
            }
        }
        // Computer shots
        else
        {
            memoPoint:
            if (playerSide == 'l')
            {
                startCol = 'a';
                endCol = 'e';
            }
            else
            {
                startCol = 'f';
                endCol = 'j';
            }
            startC = int(startCol);
            endC = int(endCol);
            cout << endl << "Computer turn :" << endl << endl;
            if ((futureShots[fCounter] == true) && (nShot == -1))
            {
                nShot = 0;
                successShotsX[nShot] = futureShotsX[fCounter];
                successShotsY[nShot] = futureShotsY[fCounter];
                successShots[nShot] = true;
                successShotsShip[nShot] = futureShotsShip[fCounter];
                successShotsSize[nShot] = futureShotsSize[fCounter];
                destroyCounter = successShotsSize[nShot]-1;
                futureShots[fCounter] = false;
                fCounter--;
            }
            if (nShot >= 0)
            {
                if ((nShot > 0) && (successShots[nShot] == true))
                {
                    if (successShotsShip[nShot] == successShotsShip[nShot-1])
                    {
                        if ((successShotsX[nShot] == successShotsX[nShot-1]))
                        {
                            if (destroyCounter > 0)
                            {
                                if (((successShotsY[nShot] - successShotsY[nShot-1]) == 1) && (board[successShotsY[nShot] + 1][successShotsX[nShot]] == boardSign) && ((successShotsY[nShot] + 1) < 11) && (missed == false))
                                {
                                    x = successShotsX[nShot];
                                    y = successShotsY[nShot] + 1;
                                }
                                else if (((successShotsY[nShot] - successShotsY[nShot-1]) == 1) && ((board[successShotsY[nShot] + 1][successShotsX[nShot]] != boardSign) || ((successShotsY[nShot] + 1) >= 11) || (missed == true)))
                                {
                                    tempX = successShotsX[0];
                                    tempY = successShotsY[0];
                                    tempShip = successShotsShip[0];
                                    tempSize = successShotsSize[0];
                                    resetSuccessfulShots();
                                    nShot = 0;
                                    successShotsX[nShot] = tempX;
                                    successShotsY[nShot] = tempY;
                                    successShotsShip[nShot] = tempShip;
                                    successShotsSize[nShot] = tempSize;
                                    successShots[nShot] = true;
                                    if (((successShotsY[nShot] - 1) > 0) && (board[successShotsY[nShot] - 1][successShotsX[nShot]] == boardSign))
                                    {
                                        y = successShotsY[nShot] - 1;
                                        x = successShotsX[nShot];
                                        method = true;
                                    }
                                }
                                else if (((successShotsY[nShot-1] - successShotsY[nShot]) == 1) && (board[successShotsY[nShot] - 1][successShotsX[nShot]] == boardSign) && ((successShotsY[nShot] - 1) > 0) && (missed == false))
                                {
                                    x = successShotsX[nShot];
                                    y = successShotsY[nShot] - 1;
                                }
                                else if (((successShotsY[nShot-1] - successShotsY[nShot]) == 1) && ((board[successShotsY[nShot] - 1][successShotsX[nShot]] != boardSign) || ((successShotsY[nShot] - 1) <= 0) || (missed == true)))
                                {
                                    tempX = successShotsX[0];
                                    tempY = successShotsY[0];
                                    tempShip = successShotsShip[0];
                                    tempSize = successShotsSize[0];
                                    resetSuccessfulShots();
                                    nShot = 0;
                                    successShotsX[nShot] = tempX;
                                    successShotsY[nShot] = tempY;
                                    successShotsShip[nShot] = tempShip;
                                    successShotsSize[nShot] = tempSize;
                                    successShots[nShot] = true;
                                    if (((successShotsY[nShot] + 1) > 0) && (board[successShotsY[nShot] + 1][successShotsX[nShot]] == boardSign))
                                    {
                                        y = successShotsY[nShot] + 1;
                                        x = successShotsX[nShot];
                                        method = true;
                                    }
                                }
                            }
                            else
                            {
                                resetSuccessfulShots();
                                nShot = -1;
                                goto memoPoint;
                            }
                        }
                        else if ((successShotsY[nShot] == successShotsY[nShot-1]))
                        {
                            if (destroyCounter > 0)
                            {
                                if (((successShotsX[nShot] - successShotsX[nShot-1]) == 1) && (board[successShotsY[nShot]][successShotsX[nShot]+1] == boardSign) && ((successShotsX[nShot] + 1) <= (endC-96)) && (missed == false))
                                {
                                    x = successShotsX[nShot] + 1;
                                    y = successShotsY[nShot];
                                }
                                else if (((successShotsX[nShot] - successShotsX[nShot-1]) == 1) && ((board[successShotsY[nShot]][successShotsX[nShot]+1] != boardSign) || ((successShotsX[nShot] + 1) > (endC-96)) || (missed == true)))
                                {
                                    tempX = successShotsX[0];
                                    tempY = successShotsY[0];
                                    tempShip = successShotsShip[0];
                                    tempSize = successShotsSize[0];
                                    resetSuccessfulShots();
                                    nShot = 0;
                                    successShotsX[nShot] = tempX;
                                    successShotsY[nShot] = tempY;
                                    successShotsShip[nShot] = tempShip;
                                    successShotsSize[nShot] = tempSize;
                                    successShots[nShot] = true;
                                    if (((successShotsX[nShot] - 1) >= (startC-96)) && (board[successShotsY[nShot]][successShotsX[nShot] - 1] == boardSign))
                                    {
                                        y = successShotsY[nShot];
                                        x = successShotsX[nShot] - 1;
                                        method = true;
                                    }
                                }
                                else if (((successShotsX[nShot-1] - successShotsX[nShot]) == 1) && (board[successShotsY[nShot]][successShotsX[nShot] - 1] == boardSign) && ((successShotsX[nShot] - 1) >= (startC-96)) && (missed == false))
                                {
                                    x = successShotsX[nShot] - 1;
                                    y = successShotsY[nShot];
                                }
                                else if (((successShotsX[nShot-1] - successShotsX[nShot]) == 1) && ((board[successShotsY[nShot]][successShotsX[nShot] - 1] != boardSign) || ((successShotsX[nShot] - 1) < (startC-96)) || (missed == true)))
                                {
                                    tempX = successShotsX[0];
                                    tempY = successShotsY[0];
                                    tempShip = successShotsShip[0];
                                    tempSize = successShotsSize[0];
                                    resetSuccessfulShots();
                                    nShot = 0;
                                    successShotsX[nShot] = tempX;
                                    successShotsY[nShot] = tempY;
                                    successShotsShip[nShot] = tempShip;
                                    successShotsSize[nShot] = tempSize;
                                    successShots[nShot] = true;
                                    if (((successShotsX[nShot] + 1) > 0) && (board[successShotsY[nShot]][successShotsX[nShot]+1] == boardSign))
                                    {
                                        y = successShotsY[nShot];
                                        x = successShotsX[nShot] + 1;
                                        method = true;
                                    }
                                }
                            }
                            else
                            {
                                resetSuccessfulShots();
                                nShot = -1;
                                goto memoPoint;
                            }
                        }
                    }
                    else
                    {
                        fCounter++;
                        futureShotsX[fCounter] = successShotsX[nShot];
                        futureShotsY[fCounter] = successShotsY[nShot];
                        futureShotsShip[fCounter] = successShotsShip[nShot];
                        futureShotsSize[fCounter] = successShotsSize[nShot];
                        futureShots[fCounter] = true;
                        successShots[nShot] = false;
                        nShot--;

                    }
                }
                if ((nShot == 0) && (successShots[nShot] == true) && (method == false))
                {
                    if (((successShotsY[nShot] + 1) < 11) && (board[successShotsY[nShot] + 1][successShotsX[nShot]] == boardSign))
                    {
                        y = successShotsY[nShot] + 1;
                        x = successShotsX[nShot];
                    }
                    else if (((successShotsY[nShot] - 1) > 0) && (board[successShotsY[nShot] - 1][successShotsX[nShot]] == boardSign))
                    {
                        y = successShotsY[nShot] - 1;
                        x = successShotsX[nShot];
                    }
                    if(((successShotsX[nShot] + 1 + 96) <= endC) && (board[successShotsY[nShot]][successShotsX[nShot] + 1] == boardSign))
                    {
                        x = successShotsX[nShot] + 1;
                        y = successShotsY[nShot];
                    }
                    else if (((successShotsX[nShot] - 1 + 96) >= startC) && (board[successShotsY[nShot]][successShotsX[nShot] - 1] == boardSign))
                    {
                        x = successShotsX[nShot] - 1;
                        y = successShotsY[nShot];
                    }
                }
            }
            if (nShot < 0)
            {
                while ((manualShot == true) && (x == -1) && (y == -1))
                {
                    for (aiShotRCounter = 3; aiShotRCounter < 11; aiShotRCounter+=3)
                    {
                        for (aiShotCCounter = (startC-96); aiShotCCounter <= (endC-96); aiShotCCounter++)
                        {
                            if ((board[aiShotRCounter][aiShotCCounter] == boardSign) && (manualShot == true))
                            {
                                x = aiShotCCounter;
                                y = aiShotRCounter;
                                manualShot = false;
                            }
                        }
                    }
                    manualShot = false;
                }
                manualShot = true;
                while ((manualShot == true) && (x == -1) && (y == -1))
                {
                    for (aiShotRCounter = 1; aiShotRCounter < 11; aiShotRCounter+=9)
                    {
                        for (aiShotCCounter = (startC-96); aiShotCCounter < (endC-96); aiShotCCounter++)
                        {
                            if ((board[aiShotRCounter][aiShotCCounter] == boardSign) && (manualShot == true))
                            {
                                x = aiShotCCounter;
                                y = aiShotRCounter;
                                manualShot = false;
                            }
                        }
                    }
                    manualShot = false;
                }
                manualShot = true;
                while ((manualShot == true) && (x == -1) && (y == -1))
                {
                    for (aiShotRCounter = 2; aiShotRCounter < 9; aiShotRCounter+=2)
                    {
                        for (aiShotCCounter = (startC-96); aiShotCCounter < (endC-96); aiShotCCounter++)
                        {
                            if ((board[aiShotRCounter][aiShotCCounter] == boardSign) && (manualShot == true))
                            {
                                x = aiShotCCounter;
                                y = aiShotRCounter;
                                manualShot = false;
                            }
                        }
                    }
                    manualShot = false;
                }
                if ((manualShot == false) && (x == -1) && (y == -1))
                {
                    while (board[y][x] != boardSign)
                    {
                        xInt = rand() %5 + startC;
                        yInt = rand() %10 + 49;
                        x = xInt - 96;
                        y = yInt - 48;
                    }
                }
            }
        }
        // Make a shot
        cout << char(x+96) << " " << y << endl << endl;
        if ((ships[y][x] == 'C') || (ships[y][x] == 'B') || (ships[y][x] == 'U') || (ships[y][x] == 'S') || (ships[y][x] == 'D'))
        {
            board[y][x] = hitShot;
            if (player == 'c')
            {
                if (ships[y][x] == 'C')
                {
                    successShotsSize[nShot+1] = 5;
                }
                else if (ships[y][x] == 'B')
                {
                    successShotsSize[nShot+1] = 4;
                }
                else if (ships[y][x] == 'U')
                {
                    successShotsSize[nShot+1] = 3;
                }
                else if (ships[y][x] == 'S')
                {
                    successShotsSize[nShot+1] = 3;
                }
                else if (ships[y][x] == 'D')
                {
                    successShotsSize[nShot+1] = 2;
                }
                if (nShot < 0)
                {
                    destroyCounter = successShotsSize[nShot+1]-1;
                }
                nShot++;
                successShots[nShot] = true;
                successShotsX[nShot] = x;
                successShotsY[nShot] = y;
                successShotsShip[nShot] = ships[y][x];
                if (nShot > 0)
                {
                    if (successShotsShip[nShot] == successShotsShip[nShot-1])
                    {
                        destroyCounter--;
                    }
                }
                missed = false;
                method = false;
            }
            shot = true;
            cout << "Success Shot!" << endl << endl;
        }
        else
        {
            board[y][x] = missedShot;
            if (player == 'c')
            {
                missed = true;
                method = false;
            }
            shot = true;
            cout << "Missed Shot!" << endl << endl;
        }
    }
}
// An integer function to analyze destroyed ships status, game status and return game winner player number
int battleShip::gameMentor(char player)
{
    int winner, colIndex, colEnd, rIndex, cIndex;
    int cShip = 0, bShip = 0, uShip = 0, sShip = 0, dShip = 0;
    if (player == 'p')
    {
        winner = 1;
        if (playerSide == 'l')
        {
            colIndex = 6;
            colEnd = 11;
        }
        else
        {
            colIndex = 1;
            colEnd = 6;
        }
    }
    else
    {
        winner = 2;
        if (playerSide == 'l')
        {
            colIndex = 1;
            colEnd = 6;
        }
        else
        {
            colIndex = 6;
            colEnd = 11;
        }
    }
    for (rIndex = 1; rIndex < 11; rIndex++)
    {
        for (cIndex = colIndex; cIndex < colEnd; cIndex++)
        {
            if ((ships[rIndex][cIndex] == 'C') || (ships[rIndex][cIndex] == 'B') || (ships[rIndex][cIndex] == 'U') || (ships[rIndex][cIndex] == 'S') || (ships[rIndex][cIndex] == 'D'))
            {
                if ((board[rIndex][cIndex] != hitShot) && (board[rIndex][cIndex] != 'C') && (board[rIndex][cIndex] != 'B') && (board[rIndex][cIndex] != 'U') && (board[rIndex][cIndex] != 'S') && (board[rIndex][cIndex] != 'D'))
                {
                    winner = 0;
                }
                else
                {
                    if (ships[rIndex][cIndex] == 'C')
                    {
                        cShip++;
                    }
                    else if (ships[rIndex][cIndex] == 'B')
                    {
                        bShip++;
                    }
                    else if (ships[rIndex][cIndex] == 'U')
                    {
                        uShip++;
                    }
                    else if (ships[rIndex][cIndex] == 'S')
                    {
                        sShip++;
                    }
                    else if (ships[rIndex][cIndex] == 'D')
                    {
                        dShip++;
                    }
                }
            }
        }
    }
    if (cShip == 5)
    {
        for (rIndex = 1; rIndex < 11; rIndex++)
        {
            for (cIndex = colIndex; cIndex < colEnd; cIndex++)
            {
                if (ships[rIndex][cIndex] == 'C')
                {
                    board[rIndex][cIndex] = ships[rIndex][cIndex];
                }
            }
        }
    }
    if (bShip == 4)
    {
        for (rIndex = 1; rIndex < 11; rIndex++)
        {
            for (cIndex = colIndex; cIndex < colEnd; cIndex++)
            {
                if (ships[rIndex][cIndex] == 'B')
                {
                    board[rIndex][cIndex] = ships[rIndex][cIndex];
                }
            }
        }
    }
    if (uShip == 3)
    {
        for (rIndex = 1; rIndex < 11; rIndex++)
        {
            for (cIndex = colIndex; cIndex < colEnd; cIndex++)
            {
                if (ships[rIndex][cIndex] == 'U')
                {
                    board[rIndex][cIndex] = ships[rIndex][cIndex];
                }
            }
        }
    }
    if (sShip == 3)
    {
        for (rIndex = 1; rIndex < 11; rIndex++)
        {
            for (cIndex = colIndex; cIndex < colEnd; cIndex++)
            {
                if (ships[rIndex][cIndex] == 'S')
                {
                    board[rIndex][cIndex] = ships[rIndex][cIndex];
                }
            }
        }
    }
    if (dShip == 2)
    {
        for (rIndex = 1; rIndex < 11; rIndex++)
        {
            for (cIndex = colIndex; cIndex < colEnd; cIndex++)
            {
                if (ships[rIndex][cIndex] == 'D')
                {
                    board[rIndex][cIndex] = ships[rIndex][cIndex];
                }
            }
        }
    }
    return winner;
}
// A module to display board game as live
void battleShip::displayBoard()
{
    int boardSize = 11;
    int rCounter, cCounter;
    for (rCounter = 0; rCounter < boardSize; rCounter++)
    {
        for (cCounter = 0; cCounter < boardSize; cCounter++)
        {
            if (rCounter == 10 && cCounter == 0)
            {
                cout << 10 << " ";
            }
            else if (cCounter == 0)
            {
                cout << board[rCounter][cCounter] << "  ";
            }
            else
            {
                cout << board[rCounter][cCounter] << " ";
                if (cCounter == 5)
                {
                    cout << "| ";
                }
            }
        }
        cout << endl;
    }
}
// A module to display game winner and the all ships position on the board game at game over
void battleShip::showGameMap(char winPlayer)
{
    int boardSize = 11;
    int rCounter, cCounter;
    cout << endl;
    if (winPlayer == 'p')
    {
        cout << "Congrats! You WIN!" << endl;
    }
    else
    {
        cout << "Computer WIN!" << endl;
    }
    cout << endl << "The game map was :" << endl << endl;
    for (rCounter = 0; rCounter < boardSize; rCounter++)
    {
        for (cCounter = 0; cCounter < boardSize; cCounter++)
        {
            if (rCounter == 10 && cCounter == 0)
            {
                cout << 10 << " ";
            }
            else if (cCounter == 0)
            {
                cout << ships[rCounter][cCounter] << "  ";
            }
            else
            {
                cout << ships[rCounter][cCounter] << " ";
                if (cCounter == 5)
                {
                    cout << "| ";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int winner = 0;
    battleShip newBattle;
    newBattle.gameBoard();
    srand(time(0));
    newBattle.mainMenu();
    if (newBattle.getGameOver() == false)
    {
        newBattle.boardArrangement('p');
        newBattle.boardArrangement('c');
        newBattle.displayBoard();
        while (newBattle.getGameOver() == false)
        {
            newBattle.gameShot('p');
            winner = newBattle.gameMentor('p');
            newBattle.displayBoard();
            if (winner == 0)
            {
                newBattle.gameShot('c');
                winner = newBattle.gameMentor('c');
                newBattle.displayBoard();
                if (winner == 2)
                {
                    newBattle.showGameMap('c');
                    newBattle.setGameOver(true);
                }
            }
            else
            {
                newBattle.showGameMap('p');
                newBattle.setGameOver(true);
            }
        }
    }
    return 0;
}
