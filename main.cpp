#include <iostream>
#include <cstdlib>
#include <ctime>
#include "OptimalMove.hpp"

char board[3][3] = {{'_', '_', '_'},
                    {'_', '_', '_'},
                    {'_', '_', '_'}};

char current_marker;
int current_player;

void drawBoard()
{
    std::cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    std::cout << "-----------\n";
    std::cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    std::cout << "-----------\n";
    std::cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
    std::cout << "\n";
}

bool placeMarker(int slot)
{
    int row = slot / 3, col;
    if (slot % 3 == 0)
    {
        row -= 1;
        col = 2;
    }
    else
    {
        col = (slot % 3) - 1;
    }

    if (board[row][col] != 'x' && board[row][col] != 'o')
    {
        board[row][col] = current_marker;
        return true;
    }
    else
    {
        return false;
    }
}

int winner()
{
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return current_player;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return current_player;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return current_player;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return current_player;
    }
    return 0;
}

void swapPlayer()
{
    if (current_marker == 'x')
    {
        current_marker = 'o';
    }
    else
    {
        current_marker = 'x';
    }

    if (current_player == 1)
    {
        current_player = 2;
    }
    else
    {
        current_player = 1;
    }
}

void game2Players()
{
    std::cout << "Player 1, choose your marker: ";
    char marker_p1;
    std::cin >> marker_p1;
    current_player = 1;
    current_marker = marker_p1;

    int playerWon = 0;
    drawBoard();
    for (int i = 0; i < 9; ++i)
    {
        std::cout << "It's player" << current_player << "'s turn. Enter slot: ";
        int slot;
        std::cin >> slot;

        if (slot < 1 || slot > 9)
        {
            std::cout << "Slot is invalid!\n";
            --i;
            continue;
        }

        if (!placeMarker(slot))
        {
            std::cout << "That slot is occupied!\n";
            --i;
            continue;
        }
        playerWon = winner();
        drawBoard();

        if (playerWon != 0)
        {
            std::cout << "Player" << playerWon << " won!\n";
            break;
        }

        swapPlayer();
    }

    if (playerWon == 0)
    {
        std::cout << "It's a draw!\n";
    }
}

void ComputerMove()
{
    current_player = 2;
    if (current_marker == 'x')
    {
        current_marker = 'o';
    }
    else
    {
        current_marker = 'x';
    }

    srand(time(NULL));
    int slot = rand() % (9 - 1 + 1) + 1;
    while (!placeMarker(slot))
    {
        ++slot;
    }
}

void gameRandom()
{
    current_player = 1;
    char marker;
    std::cout << "Enter your marker: ";
    std::cin >> marker;
    current_marker = marker;

    drawBoard();
    for (int i = 0; i < 9 / 2 + 1; ++i)
    {
        current_player = 1;
        current_marker = marker;
        std::cout << "It's your turn. Enter slot: ";
        int slot;
        std::cin >> slot;

        if (slot < 1 || slot > 9)
        {
            std::cout << "Slot is invalid!\n";
            --i;
            continue;
        }

        if (!placeMarker(slot))
        {
            std::cout << "That slot is occupied!\n";
            --i;
            continue;
        }

        if (winner() != 0)
        {
            std::cout << "Winner: " << winner();
            return;
        }
        ComputerMove();
        drawBoard();
        if (winner() != 0)
        {
            std::cout << "Winner: " << winner();
            return;
        }
    }
    std::cout << "Winner: " << winner();
}

char getWinner()
{
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] != '_' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return board[i][0];
        }
        if (board[0][i] != '_' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    if (board[0][0] != '_' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] != '_' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return board[0][2];
    }
    return 'z';
}

void gameWithAI()
{
    char human = 'x', AI = 'o';
    current_marker = 'x';
    drawBoard();

    for (int i = 0; i < 9 / 2; ++i)
    {
        std::cout << "It's your turn. Enter slot: ";
        int slot;
        std::cin >> slot;

        if (slot < 1 || slot > 9)
        {
            std::cout << "Slot is invalid!\n";
            --i;
            continue;
        }

        if (!placeMarker(slot))
        {
            std::cout << "That slot is occupied!\n";
            --i;
            continue;
        }

        if (getWinner() != 'z')
        {
            std::cout << "Winner: " << getWinner() << "\n";
            drawBoard();
            return;
        }
        
        if (board[1][1] == '_')
        {
            board[1][1] = AI;
        }
        else
        {
            Move nextMove = findBestMove(board, AI);
        }
        

        if (getWinner() != 'z')
        {
            std::cout << "Winner: " << getWinner() << "\n";
            drawBoard();
            return;
        }

        drawBoard();
    }

    if (getWinner() == 'z')
    {
        drawBoard();
        std::cout << "It's a tie!\n";
    }
}

int main()
{
    // game();
    // srand(time(NULL));
    // std::cout << rand() % (10 - 1 + 1) + 1 << "\n";
    // gameRandom();
    gameWithAI();
}

// random number
//  [L, U) = ( rand() % (U - L + 1) ) + L