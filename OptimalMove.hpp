#include <iostream>

int max(int a, int b)
{
    return (a >= b) ? a : b;
}

int min(int a, int b)
{
    return (a <= b) ? a : b;
}

struct Move
{
    int row, col;
    Move(int row, int col)
    {
        this->row = -1;
        this->col = -1;
    }
};

bool isMoveLeft(char board[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == '_')
            {
                return true;
            }
        }
    }
    return false;
}

int evaluate(char board[3][3], char player)
{
    char opponent;
    if (player == 'x')
    {   
        opponent = 'o';
    }
    else if (player = 'o')
    {
        opponent = 'x';
    }
    // checking row x or o victory
    for (int row = 0; row < 3; ++row)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            if (board[row][0] == player)
            {
                return 10;
            }
            else if (board[row][0] == opponent)
            {
                return -10;
            }
        }
    }

    // checking column for victory
    for (int col = 0; col < 3; ++col)
    {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col])
        {
            if (board[0][col] == player)
            {
                return 10;
            }
            else if (board[0][col] == opponent)
            {
                return -10;
            }
        }
    }

    // checking diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == player)
        {
            return 10;
        }
        else if (board[0][0] == opponent)
        {
            return -10;
        }
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == player)
        {
            return 10;
        }
        else if (board[0][2] == opponent)
        {
            return -10;
        }
    }

    // else if nonw of them have won then 
    return 0;
}

int minimax(char board[3][3], int depth, bool isMax, char player)
{
    char opponent;
    if (player == 'x')
    {   
        opponent = 'o';
    }
    else if (player = 'o')
    {
        opponent = 'x';
    }
    int score = evaluate(board, player);

    // if Maximer has won the game return his evaluated score
    if (score == 10)
    {
        return score - depth;
    }

    // if Minimizer has won the game return his score
    if (score == -10)
    {
        return score  + depth;
    }

    // if there is no more move and no winner so this is a tie
    if (!isMoveLeft(board))
    {
        return 0;
    }

    // if this is Maximer's move
    if (isMax)
    {
        int best = -1000;

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                // check if the cell is empty
                if (board[i][j] != 'x' && board[i][j] != 'o')
                {
                    char pos_of_this_move;

                    // make the move
                    pos_of_this_move = board[i][j];
                    board[i][j] = player;

                    // call minimax recursivly and choose the maximum value
                    best = max(best, minimax(board, depth + 1, false, opponent));

                    // undo the move
                    board[i][j] = pos_of_this_move;
                }
            }
        }
        return best;
    }

    // Now if it's Minimizer's move
    else
    {
        int best = 1000;

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board[i][j] != 'x' && board[i][j] != 'o')
                {
                    char pos_of_this_move;

                    // make the move
                    pos_of_this_move = board[i][j];
                    board[i][j] = player;

                    // call function minimax adn choose minimum value
                    best = min(best, minimax(board, depth + 1, true, player));

                    // then undo the move
                    board[i][j] = pos_of_this_move;
                }
            }
        }
        return best;
    }
}

Move bestMove(-1, -1);
// Function find best move
Move findBestMove(char board[3][3], char player)
{
    char opponent;
    if (player == 'x')
    {   
        opponent = 'o';
    }
    else if (player = 'o')
    {
        opponent = 'x';
    }
    int bestVal = -1000;

    // Traverse all cell, evaluate minimax for all empty cells, and return the cell with optimal value
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            // check if the cell is empty
            if (board[i][j] != 'x' && board[i][j] != 'o')
            {
                char pos_of_this_move;
                pos_of_this_move = board[i][j];

                // make the move
                board[i][j] = player;

                // evaluate this move
                // this move is opponent's move
                int moveVal = minimax(board, 0, false, player);

                // then undo the move
                board[i][j] = pos_of_this_move;

                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[bestMove.row][bestMove.col] = player;
    return bestMove;
}