#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>

using namespace std;

// defines all glasses state
enum GlassState
{
    UNBREAKABLE, BREAKABLE, BROKEN
};
void gotoxy(int xpos, int ypos);

void initialOutputScreen(char outputElements[][85]);
// a is the array ready to pint out
// the pass in array must be 15 * 85
// pass in empty array, returns array that is ready to show on the screen

void initialGlassState(GlassState glasses[][30]);
// pass in array must be 2 or it won't work
// pass in blank array, and it will auto assign GlassStates to every elements of glasses

void showGlassState(const GlassState glasses[][30], ostream& outputDevice = cout);
// show glasses' GlassState on an output device, default is the screen(cout)

void showScreen(const char outputElements[][85]);
// show output elements on the screen

void updateOutputElements(const GlassState glasses[][30], char playerStateOnGlass[][30][2], int markersOnGlass[][30], char outputElements[][85]);
// update outputElements array by glasses'states
// BROKEN -> X

void initialPlayers(char*, int, bool);

void clearPlayersOnGlass(char playerStateOnGlass[][30][2]);

void showPlayersAtTheBeginning(vector<char> playersAtTheBeginning);

void findPlayer(int nowMovingPlayerLocation[], char targetPlayer, const char playerStateOnGlass[2][30][2]);

int main()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//Don't have to change!
    CONSOLE_CURSOR_INFO CursorInfo;					//Don't have to change!
    GetConsoleCursorInfo(handle, &CursorInfo);		//Don't have to change!
    CursorInfo.bVisible = false;					//Don't have to change!
    SetConsoleCursorInfo(handle, &CursorInfo);		//Don't have to change!

    gotoxy(0, 0);

    /*======================= Making Storage =======================*/
    // Stores glasses data
    GlassState glasses[2][30];
    // outputScreen : Stores characters ready to be displayed on the screen
    char outputElements[15][85];

    // TODO: make it user input
    int playerQuantity = 20;
    cout << "How many players are gonna to play this bad game? ";
    cin >> playerQuantity;
    // use player[0] to get player zero's character id;
    char* player = new char[playerQuantity];

    // Stores player's states
    char playerStateOnGlass[2][30][2];

    vector<char> playersAtTheBeginning;

    // current moving player
    char nowMovingPlayer;
    int nowMovingPlayerLocation[2];

    char keyBoard = '\0';
    int nowMovingPlayerID;

    long long int totalAward = 0;

    // if value is 1, its
    int markersOnGlass[2][30] = {0};

    int successfulPlayers = 0;

    char whereToMark = '\0';

    bool markingStuff = false;

    bool debugMode = false;

    /* ================== Initializing Data =======================*/
    // placing glasses on the bridge
    initialGlassState(glasses);
    // printing out glasses data
    //showGlassState(glasses);
    initialPlayers(player, playerQuantity, true);
    // clear everything on the glass
    clearPlayersOnGlass(playerStateOnGlass);
    // constructing the screen
    initialOutputScreen(outputElements);
    nowMovingPlayerID = 0;
    // everyone put your money in it
    cout << "Total Reward: ";
    cin >> totalAward;

    cout << "DEBUGGING?" << endl;
    cin >> debugMode;


    // initialize players at the beginning
    for (int playerNo = playerQuantity-1; playerNo >= 0; playerNo--)
    {
        playersAtTheBeginning.push_back(player[playerNo]);
    }


    while (true)
    {
        // if everyone is deadt
        if (nowMovingPlayerID == playerQuantity)
        {
            if (successfulPlayers == 0)
            {
                system("cls");
                cout << "OOF everyone is dead" << endl;
                exit(0);
            }
            else
            {
                system("cls");
                cout << "YEA everyone who doesn't die gets " << totalAward / (playerQuantity - nowMovingPlayerID + successfulPlayers);
                exit(0);
            }
        }


        /* Game Starts*/
        updateOutputElements(glasses, playerStateOnGlass, markersOnGlass, outputElements);
        findPlayer(nowMovingPlayerLocation, nowMovingPlayer, playerStateOnGlass);

        nowMovingPlayer = player[nowMovingPlayerID];
        gotoxy(0, 0);
        keyBoard = '\0';

        /*Outputs*/
        showPlayersAtTheBeginning(playersAtTheBeginning);
        cout << "Now Moving Player: " << nowMovingPlayer;
        cout << "                                          " << endl;
        cout << "Player Location at: " << nowMovingPlayerLocation[0] << "," << nowMovingPlayerLocation[1];
        cout << "                                                                                         " << endl;
        cout << "Money per player: " << totalAward / (playerQuantity - nowMovingPlayerID + successfulPlayers);
        cout << "                                                           " << endl;
        cout << "Players Left: " << (playerQuantity - nowMovingPlayerID);
        cout << "                                          " << endl;
        cout << "Successful Player: " << successfulPlayers;
        cout << "                                          " << endl;
        showScreen(outputElements);

        if (debugMode == true)
        {
            cout << "Glass States: ";
            cout << "                                                                                                          " << endl;
            showGlassState(glasses);
            // cout << "Player States:";
            // cout << "                                                                                                          " << endl;
            // for (int yIndex = 0; yIndex < 2; yIndex++)
            // {
            // for (int xIndex = 0; xIndex < 30; xIndex++)
            //     {
            //         cout << playerStateOnGlass[yIndex][xIndex][0] << " ";
            //     }
            //     cout << "                                                                                                          " << endl;
            // }
            // cout << "                                                                                                          " << endl;
            // cout << "Markers on glass: " << endl;
            // for (int yIndex = 0; yIndex < 2; yIndex++)
            // {
            //    for (int xIndex = 0; xIndex < 30; xIndex++)
            //   {
            //     cout << markersOnGlass[yIndex][xIndex] << " ";
            //    }
            //    cout << endl;
            // }
            // cout << endl;
        }


        if (markingStuff)
        {
            while (true)
            {
                if (kbhit())
                {
                    whereToMark = '\0';
                    whereToMark = getch();
                    markingStuff = false;
                    switch (whereToMark)
                    {
                    case 't':
                        markersOnGlass[0][nowMovingPlayerLocation[0]] = 1;
                        break;
                    case 'd':
                        markersOnGlass[1][nowMovingPlayerLocation[0]] = 1;
                        break;
                    }
                    break;
                }
            }
        }

        /*Keys*/
        if (kbhit())
        {
            keyBoard = '\0';
            keyBoard = getch();
        }

        switch (keyBoard)
        {
        case 'z': // leave
            exit(1);
            break;
        case 't': // right top
            // at the start
            if (nowMovingPlayerLocation[0] == -1 && nowMovingPlayerLocation[1] == -1)
            {
                playersAtTheBeginning.pop_back();
                if (glasses[0][0] == UNBREAKABLE)
                {
                    playerStateOnGlass[0][0][0] = nowMovingPlayer;
                    cout << "T:Mark Top, D: Mark Bottom, others: No marks" << endl;
                    markingStuff = true;
                }
                else if (glasses[0][0] == BREAKABLE)
                {
                    glasses[0][0] = BROKEN;
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
                else if (glasses[0][0] == BROKEN)
                {
                    glasses[0][0] = BROKEN;
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
            }
            else // at the mid
            {
                // player is at the end
                if (nowMovingPlayerLocation[0] == 29)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    nowMovingPlayerID++;
                    successfulPlayers++;
                    cout << "                                                " << endl;
                }
                else if (nowMovingPlayerLocation[1] == 1 && glasses[0][nowMovingPlayerLocation[0]+1] == UNBREAKABLE)
                {
                    playerStateOnGlass[0][nowMovingPlayerLocation[0]+1][0] = nowMovingPlayer;
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    cout << "T:Mark Top, D: Mark Bottom, others: No marks" << endl;
                    markingStuff = true;

                }
                else if (nowMovingPlayerLocation[1] == 1 && glasses[0][nowMovingPlayerLocation[0]+1] == BREAKABLE)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    glasses[0][nowMovingPlayerLocation[0]+1] = BROKEN;
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
                else if (nowMovingPlayerLocation[1] == 1 && glasses[0][nowMovingPlayerLocation[0]+1] == BROKEN)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    glasses[0][nowMovingPlayerLocation[0]+1] = BROKEN;
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
                else if (nowMovingPlayerLocation[1] == 0)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
            }
            break;
        case 'd': // right down
            if (nowMovingPlayerLocation[0] == -1 && nowMovingPlayerLocation[1] == -1)
            {
                playersAtTheBeginning.pop_back();
                if (glasses[1][0] == UNBREAKABLE)
                {
                    playerStateOnGlass[1][0][0] = nowMovingPlayer;
                    cout << "T:Mark Top, D: Mark Bottom, others: No marks" << endl;
                    markingStuff = true;
                }
                else if (glasses[1][0] == BREAKABLE)
                {
                    glasses[1][0] = BROKEN;
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
                else if (glasses[1][0] == BROKEN)
                {
                    glasses[1][0] = BROKEN;
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
            }
            else
            {
                if (nowMovingPlayerLocation[0] == 29)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    nowMovingPlayerID++;
                    successfulPlayers++;
                    cout << "                                                " << endl;
                }
                else if (nowMovingPlayerLocation[1] == 0 && glasses[1][nowMovingPlayerLocation[0]+1] == UNBREAKABLE)
                {
                    playerStateOnGlass[1][nowMovingPlayerLocation[0]+1][0] = nowMovingPlayer;
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    cout << "T:Mark Top, D: Mark Bottom, others: No marks" << endl;
                    markingStuff = true;
                }
                else if (nowMovingPlayerLocation[1] == 0 && glasses[1][nowMovingPlayerLocation[0]+1] == BREAKABLE)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    glasses[1][nowMovingPlayerLocation[0]+1] = BROKEN;
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
                else if (nowMovingPlayerLocation[1] == 0 && glasses[1][nowMovingPlayerLocation[0]+1] == BROKEN)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    glasses[1][nowMovingPlayerLocation[0]+1] = BROKEN;
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
                else if (nowMovingPlayerLocation[1] == 1)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
            }
            break;
        case 'r': // right forward
            if (nowMovingPlayerLocation[0] != -1 && nowMovingPlayerLocation[1] != -1)
            {
                if (nowMovingPlayerLocation[0] == 29)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    nowMovingPlayerID++;
                    successfulPlayers++;
                    cout << "                                                " << endl;
                }
                else if (nowMovingPlayerLocation[1] == 1 && glasses[1][nowMovingPlayerLocation[0]+1] == UNBREAKABLE)
                {
                    playerStateOnGlass[1][nowMovingPlayerLocation[0]+1][0] = nowMovingPlayer;
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    cout << "T:Mark Top, D: Mark Bottom, others: No marks" << endl;
                    markingStuff = true;
                }
                else if (nowMovingPlayerLocation[1] == 1 && glasses[1][nowMovingPlayerLocation[0]+1] == BREAKABLE)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    glasses[1][nowMovingPlayerLocation[0]+1] = BROKEN;
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
                else if (nowMovingPlayerLocation[1] == 1 && glasses[1][nowMovingPlayerLocation[0]+1] == BROKEN)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    glasses[1][nowMovingPlayerLocation[0]+1] = BROKEN;
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
                else if (nowMovingPlayerLocation[1] == 0 && glasses[0][nowMovingPlayerLocation[0]+1] == UNBREAKABLE)
                {
                    playerStateOnGlass[0][nowMovingPlayerLocation[0]+1][0] = nowMovingPlayer;
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    cout << "T:Mark Top, D: Mark Bottom, others: No marks" << endl;
                    markingStuff = true;
                }
                else if (nowMovingPlayerLocation[1] == 0 && glasses[0][nowMovingPlayerLocation[0]+1] == BREAKABLE)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    glasses[0][nowMovingPlayerLocation[0]+1] = BROKEN;
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }
                else if (nowMovingPlayerLocation[1] == 0 && glasses[0][nowMovingPlayerLocation[0]+1] == BROKEN)
                {
                    playerStateOnGlass[nowMovingPlayerLocation[1]][nowMovingPlayerLocation[0]][0] = '*';
                    glasses[0][nowMovingPlayerLocation[0]+1] = BROKEN;
                    nowMovingPlayerID++;
                    cout << "                                                " << endl;
                }


            }


        }

        cout << "                                               " << endl;



    }


    // deleting stuff
    delete [] player;

}

void gotoxy(int xpos, int ypos)//Don't have to change!
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}

void findPlayer(int nowMovingPlayerLocation[], char targetPlayer, const char playerStateOnGlass[2][30][2])
{
    bool foundPlayer = false;
    for (int yIndex = 0; yIndex < 2; yIndex++)
    {
        for (int xIndex = 30-1; xIndex >= 0; xIndex--)
        {
            if (playerStateOnGlass[yIndex][xIndex][0] == targetPlayer)
            {
                nowMovingPlayerLocation[0] = xIndex;
                nowMovingPlayerLocation[1] = yIndex;
                foundPlayer = true;
                break;
            }
        }
    }
    if (foundPlayer == false)
    {
        nowMovingPlayerLocation[0] = -1;
        nowMovingPlayerLocation[1] = -1;
    }

}

void showPlayersAtTheBeginning(vector<char> playersAtTheBeginning)
{
    cout << "Players at the beginning (Next <- Last): ";
    for (int index = playersAtTheBeginning.size()-1; index >= 0; index--)
    {
        cout << playersAtTheBeginning[index] << ",";
    }
    cout << "                      " << endl;
}

void clearPlayersOnGlass(char playerStateOnGlass[][30][2])
{
    for (int yIndex = 0; yIndex < 2; yIndex++)
    {
        for (int xIndex = 0; xIndex < 30; xIndex++)
        {
            for (int glassIndex = 0; glassIndex < 2; glassIndex++)
            {
                playerStateOnGlass[yIndex][xIndex][glassIndex] = '*';
            }
        }
    }
}

void initialPlayers(char* player, int playerQuantity, bool debugMod)
{
    for (int playerNo = 0; playerNo < playerQuantity; playerNo++)
    {
        player[playerNo] = playerNo+'A';
    }

    if (debugMod)
    {
        cout << "Players: ";
        for (int playerNo = 0; playerNo < playerQuantity; playerNo++)
        {
            cout << player[playerNo] << ",";
        }
        cout << "                      " << endl;
    }
}

void initialGlassState(GlassState glasses[][30])
{
    srand(time(0));

    for (int i = 0; i < 30; i++)
    {
        int randomNumberZeroOrOne = rand()%2;
        // if even -> BREAKABLE, odd -> UNBREAKABLE
        if (randomNumberZeroOrOne == 1)
        {
            glasses[0][i] = BREAKABLE;
            glasses[1][i] = UNBREAKABLE;
        }
        else if (randomNumberZeroOrOne == 0)
        {
            glasses[0][i] = UNBREAKABLE;
            glasses[1][i] = BREAKABLE;
        }
        else
        {
            cout << "Warning: RandomNumberZeroOrOne Got Problems!!" << endl;
        }
    }
}

void initialOutputScreen(char outputElements[][85])
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 85; j++)
            outputElements[i][j] = ' ';
    }//設初始值

    for (int i = 0; i < 85; i++)
    {
        outputElements[0][i] = '*';
        outputElements[14][i] = '*';
    }//設上下框

    for (int i = 1; i < 10; i++)
    {
        outputElements[6][i] = '*';
        outputElements[8][i] = '*';
    }//start上下

    outputElements[7][1] = '*';
    outputElements[7][9] = '*';//start左右

    outputElements[7][3] = 'S';
    outputElements[7][4] = 'T';
    outputElements[7][5] = 'A';
    outputElements[7][6] = 'R';
    outputElements[7][7] = 'T';//start文字

    for (int i = 77; i < 84; i++)
    {
        outputElements[6][i] = '$';
        outputElements[8][i] = '$';
    }//end上下

    outputElements[7][77] = '$';
    outputElements[7][83] = '$';//end左右
    outputElements[7][79] = 'E';
    outputElements[7][80] = 'N';
    outputElements[7][81] = 'D';//end文字

    for (int i = 13; i < 74; i++)
        outputElements[5][i] = '-';
    for (int i = 13; i < 74; i+=2)
        outputElements[6][i] = '|';
    for (int i = 13; i < 74; i++)
        outputElements[7][i] = '-';
    for (int i = 13; i < 74; i+=2)
        outputElements[8][i] = '|';
    for (int i = 13; i < 74; i++)
        outputElements[9][i] = '-';//玻璃橋設置
}

void showGlassState(const GlassState glasses[][30], ostream& outputDevice)
{
    for (int yIndex = 0; yIndex < 2; yIndex++)
    {
        for (int xIndex = 0; xIndex < 30; xIndex++)
        {
            outputDevice << glasses[yIndex][xIndex] << " ";
        }
        outputDevice << endl;
    }
}

void showScreen(const char outputElements[][85])
{
    for (int yOutputScreenIndex = 0; yOutputScreenIndex < 15; yOutputScreenIndex++)
    {
        for (int xOutputScreenIndex = 0; xOutputScreenIndex < 85; xOutputScreenIndex++)
            cout << outputElements[yOutputScreenIndex][xOutputScreenIndex];
        cout << endl;
    }//輸出畫面
}

void updateOutputElements(const GlassState glasses[][30], char playerStateOnGlass[][30][2], int markersOnGlass[][30], char outputElements[][85])
{
    for (int glassesYIndex = 0; glassesYIndex < 2; glassesYIndex++)
    {
        for (int glassesXIndex = 0; glassesXIndex < 30; glassesXIndex++)
        {
            outputElements[6+2*glassesYIndex][14+2*glassesXIndex] = ' ';
            if (markersOnGlass[glassesYIndex][glassesXIndex] == 1)
            {
                outputElements[6+2*glassesYIndex][14+2*glassesXIndex] = '#';
            }

            if (glasses[glassesYIndex][glassesXIndex] == BROKEN)
            {
                outputElements[6+2*glassesYIndex][14+2*glassesXIndex] = 'X';
            }

            if (playerStateOnGlass[glassesYIndex][glassesXIndex][0] != '*')
            {
                outputElements[6+2*glassesYIndex][14+2*glassesXIndex] = playerStateOnGlass[glassesYIndex][glassesXIndex][0];
            }
        }
    }
}
