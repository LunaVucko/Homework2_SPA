#include "game_of_life.h"

bool game_of_life::random_value()
{
	// generate a random boolean value for each cell on the game board ( 20 x 40 )

	return rand() % 2 == 0;
}

bool game_of_life::cell_taken(int i, int j)
{
	//checking if the cell is alive or dead

	return _generation[i][j];
}

int game_of_life::count_live_neighbors(int i, int j)
{
   

    /*
    
    
    The nested for loop is too count all possible neighbouring cells, including cells to the top-left, top, top-right, left, right, bottom-left, bottom, and bottom-right of the current cell.

By checking the status of each of these cells, it counts the number of live cells surrounding the current cell and use that count to determine the next state of the current cell according to the rules of the Game of Life.*/

    int count = 0;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            
            //This checks if the current cell is the same as the original cell.If it is, the loop skips to the next iteration(i.e., the loop does not count the original cell as its own neighbor).
            if (di == 0 && dj == 0) continue;

            // Calculate the neighbor's position
           
            //This calculates the row index of the neighboring cell by adding the value of di to the row index of the original cell (i).
            int ni = i + di;
            //This calculates the column index of the neighboring cell by adding the value of dj to the column index of the original cell(j).
            int nj = j + dj;

            // Check if the neighbor is out of bounds
            if (ni < 0 || ni >= ROWS || nj < 0 || nj >= COLS) continue;

            // Count the live neighbors
            if (_generation[ni][nj]) count++;
        }
    }
    return count;
}

game_of_life::game_of_life()
{
	// this is the default constructor

    // Initialize the _generation 2D array with random values
    srand(time(0));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            _generation[i][j] = random_value();
        }
    }
}

void game_of_life::next_generation()
{
    // two for loops to go through the 2D array on the game board
  
    

    // Calculate the next generation of the game
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
           
            int live_neighbors = count_live_neighbors(i, j);


            /*

            Rules of Game of Life:

            If the current alive cell has two or three neighbouring alive cells, it stays alive in the next generation.
            If the current alive cell has <2 and >3 neighbouring alive cells, the current cell dies in the next generation.

            */

            if (_generation[i][j]) {
               
                _next_generation[i][j] = live_neighbors == 2 || live_neighbors == 3;
            }
            else {

                /* If the current dead cell has exactly 3 neighbouring alive cells, the current dead cell will be alive in the next generation.
            Otherwise, the current dead cell stays dead in the next generation.*/

                _next_generation[i][j] = live_neighbors == 3;
            }
        }
    }

    // Copy the _next_generation array to the _generation array
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            _generation[i][j] = _next_generation[i][j];
        }
    }
	
}

void game_of_life::draw()
{
    system("cls");

    // Display the current state of the game board
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (_generation[i][j]) {
                //alive cells
                cout << "O";
            }
            else {
                //dead cells
                cout << ".";
            }
        }
        cout << endl;
    }
}

 