#include <iostream>
#define MAX_N 1000
#define MAX_M 1000

using namespace std;

const char LIFE = '*';
const char DEAD = '.';

int row, col;
char game[MAX_N][MAX_M];

int generation = 0;

void printGame() {
    system("clear");
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << game[i][j];
        }
        cout << endl;
    }
    cout << "Current generation: " << generation << endl;
    cout << "Press Enter to Continue... (or any other key + enter to exit)" << endl;
}

// counts the amount of living neighbours around position (x,y)
int countNeighbors(int x, int y) {
    int count = 0;
    for (int nx = x - 1; nx <= x + 1; ++nx)
        for (int ny = y - 1; ny <= y + 1; ++ny)
            if (0 <= nx && nx < row && 0 <= ny && ny < col)
                if (game[nx][ny] == LIFE && !(nx == x && ny == y)) count++;
    return count;
}

/*
 * Rules:
 * 1. Any live cell with fewer than two live neighbours dies.
 * 2. Any live cell with more than three live neighbours dies.
 * 3. Any live cell with two or three live neighbours lives, unchanged, to the next generation.
 * 4. Any dead cell with exactly three live neighbours will come to life.
 */
void nextGeneration() {
    char next[row][col];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            int liveCount = countNeighbors(i,j);
            if ((game[i][j] == LIFE && (liveCount == 2 || liveCount == 3))
              ||(game[i][j] == DEAD && liveCount == 3))
                 next[i][j] = LIFE;
            else next[i][j] = DEAD;
        }
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            game[i][j] = next[i][j];
        }
    }
    generation++;
    printGame();
}


int main() {
    // read initial row and column size
    cin >> row >> col;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cin >> game[i][j];
        }
    }
    printGame();
    char end;
    cin.get(end);
    do {
        cin.get(end);
        nextGeneration();
    } while(end == '\n');

    return 0;
}
