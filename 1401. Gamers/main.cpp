#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void play(vector<vector<int>> &gameBoard, int xEmptyDot, int yEmptyDot, int xLeftUpperDot, int yLeftUpperDot, int n) {

    // figure id
    static int c; c++;

    // calculate the position of the empty point in the coordinates of a smaller square
    int xEmptyRel = xEmptyDot - yLeftUpperDot;
    int yEmptyRel = yEmptyDot - xLeftUpperDot;

    // dimensionality reduction
    n = n / 2;

    // calculation of coordinates of the separated sectors closest to the center
    int xRightLowerCenter = xLeftUpperDot + n,      yRightLowerCenter = yLeftUpperDot + n;
    int xLeftLowerCenter = xLeftUpperDot + n - 1,   yLeftLowerCenter = yLeftUpperDot + n;
    int xRightUpperCenter = xLeftUpperDot + n,      yRightUpperCenter = yLeftUpperDot + n - 1;
    int xLeftUpperCenter = xLeftUpperDot + n - 1,   yLeftUpperCenter  = yLeftUpperDot + n - 1;

    // if an empty dot at right lower sector
    if (xEmptyRel >= n and yEmptyRel >= n) {

        // build a corner figure in the central part, except for the right lower sector
        gameBoard[xLeftLowerCenter][yLeftLowerCenter] = c;
        gameBoard[xRightUpperCenter][yRightUpperCenter] = c;
        gameBoard[xLeftUpperCenter][yLeftUpperCenter] = c;

        // dimensionality limit 2x2
        if (n > 1) {
            // using recursion
            play(gameBoard, xEmptyDot, yEmptyDot, xRightLowerCenter, yRightLowerCenter, n);
            play(gameBoard, yLeftLowerCenter, xLeftLowerCenter, xLeftUpperDot,  yLeftLowerCenter, n);
            play(gameBoard, yRightUpperCenter, xRightUpperCenter, xRightUpperCenter, yLeftUpperDot,  n);
            play(gameBoard, yLeftUpperCenter, xLeftUpperCenter, xLeftUpperDot,  yLeftUpperDot,  n);
        }
    }
        // if an empty dot at left lower sector
    else if (xEmptyRel >= n and yEmptyRel < n) {

        // build a corner figure in the central part, except for the left lower sector
        gameBoard[xRightLowerCenter][yRightLowerCenter] = c;
        gameBoard[xRightUpperCenter][yRightUpperCenter] = c;
        gameBoard[xLeftUpperCenter][yLeftUpperCenter] = c;

        // dimensionality limit 2x2
        if (n > 1) {
            // using recursion
            play(gameBoard, yRightLowerCenter, xRightLowerCenter, xRightLowerCenter, yRightLowerCenter, n);
            play(gameBoard, xEmptyDot,  yEmptyDot,  xLeftUpperDot,  yLeftLowerCenter, n);
            play(gameBoard, yRightUpperCenter, xRightUpperCenter, xRightUpperCenter, yLeftUpperDot,  n);
            play(gameBoard, yLeftUpperCenter, xLeftUpperCenter, xLeftUpperDot,  yLeftUpperDot,  n);
        }
    }
        // if an empty dot at right upper sector
    else if (xEmptyRel < n and yEmptyRel >= n) {

        // build a corner figure in the central part, except for the right upper sector
        gameBoard[xRightLowerCenter][yRightLowerCenter] = c;
        gameBoard[xLeftLowerCenter][yLeftLowerCenter] = c;
        gameBoard[xLeftUpperCenter][yLeftUpperCenter] = c;

        // dimensionality limit 2x2
        if (n > 1) {
            // using recursion
            play(gameBoard, yRightLowerCenter, xRightLowerCenter, xRightLowerCenter, yRightLowerCenter, n);
            play(gameBoard, yLeftLowerCenter, xLeftLowerCenter, xLeftUpperDot,  yLeftLowerCenter, n);
            play(gameBoard, xEmptyDot,  yEmptyDot,  xRightUpperCenter, yLeftUpperDot,  n);
            play(gameBoard, yLeftUpperCenter, xLeftUpperCenter, xLeftUpperDot,  yLeftUpperDot,  n);
        }
    }
        // if an empty dot at left upper sector
    else  if (xEmptyRel < n and yEmptyRel < n) {

        // build a corner figure in the central part, except for the left upper sector
        gameBoard[xRightLowerCenter][yRightLowerCenter] = c;
        gameBoard[xLeftLowerCenter][yLeftLowerCenter] = c;
        gameBoard[xRightUpperCenter][yRightUpperCenter] = c;

        // dimensionality limit 2x2
        if (n > 1) {
            // using recursion
            play(gameBoard, yRightLowerCenter, xRightLowerCenter, xRightLowerCenter, yRightLowerCenter, n);
            play(gameBoard, yLeftLowerCenter, xLeftLowerCenter, xLeftUpperDot,  yLeftLowerCenter, n);
            play(gameBoard, yRightUpperCenter, xRightUpperCenter, xRightUpperCenter, yLeftUpperDot,  n);
            play(gameBoard,  xEmptyDot,  yEmptyDot, xLeftUpperDot,  yLeftUpperDot,  n);
        }
    }
    return;
}

int main() {

    // data input
    int n, xEmptyDot, yEmptyDot;
    cin >> n >> yEmptyDot >> xEmptyDot;

    // calculate n
    n = pow(2, n);

    // left upper coords (1; 1) -> (0; 0)
    int xLeftUpperDot, yLeftUpperDot;
    xLeftUpperDot = 0; yLeftUpperDot = 0;
    xEmptyDot--; yEmptyDot--;

    // creating game board
    vector<vector<int>> gameBoard(n, (vector<int>(n)));

    // recursive function that arranges the pieces by dividing the board into 4 equal squares until we get the size 4x4
    play(gameBoard, xEmptyDot, yEmptyDot, xLeftUpperDot, yLeftUpperDot, n);

    // result table output
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << gameBoard[i][j] << " ";
        cout << endl;
    }

    return 0;
}