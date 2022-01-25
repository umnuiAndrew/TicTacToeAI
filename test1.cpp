#include <bits/stdc++.h>
#include "OptimalMove.hpp"
using namespace std;

void drawBoard(char board[3][3])
{
    std::cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    std::cout << "-----------\n";
    std::cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    std::cout << "-----------\n";
    std::cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
    std::cout << "\n";
}

// Driver code
int main()
{
    char board[3][3] =
        {
            {'o', '_', '_'},
            {'_', '_', '_'},
            {'_', '_', '_'}};

    Move bestMove = findBestMove(board, 'x');

    printf("The Optimal Move is :\n");
    printf("ROW: %d COL: %d\n\n", bestMove.row,
           bestMove.col);
    drawBoard(board);

    return 0;
}
