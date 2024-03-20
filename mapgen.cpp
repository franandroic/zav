#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

//a class representing the map on which the game is played
class PlayMap {

    //member variables that describe the map
    private:

        //number of fields along the x axis of the map
        int MAP_X;
        //number of fields along the y axis of the map
        int MAP_Y;
        //how many character moves will be necessary to beat the level
        int N_OF_LINES_TO_WIN;
        //number of objects to be placed aside from the ones necessary to beat the level
        int N_OF_OBJECTS;
    
    public:

        //a matrix of characters where each field represents a field of the map
        vector<vector<char>> MAP_MATRIX;

        //constructor
        PlayMap(int width, int height, int lines, int objects) {
            MAP_X = width;
            MAP_Y = height;
            N_OF_LINES_TO_WIN = lines;
            N_OF_OBJECTS = objects;

            vector<vector<char>> matrix(MAP_Y, vector<char>(MAP_X, '.'));
            MAP_MATRIX = matrix;
        }

        //function that returns a random number inside a given interval
        int getRandom(int lower, int upper) {
            return ((rand() % (upper - lower + 1)) + lower);
        }

        //function that generates the paths and objects on the map
        void generate() {
            
            //creating a starting and a finishing point on the map
            int start = getRandom(0, MAP_X * MAP_Y);
            int finish = getRandom(0, MAP_X * MAP_Y);
            while (start == finish) finish = getRandom(0, MAP_X * MAP_Y);

            int current_x = start % MAP_Y;
            int current_y = start / MAP_Y;
            int end_x = finish % MAP_Y;
            if (end_x == 0) end_x++;
            else if (end_x == MAP_X - 1) end_x--;
            int end_y = finish / MAP_Y;
            if (end_y == 0) end_y++;
            else if (end_y == MAP_Y - 1) end_y--;

            MAP_MATRIX[current_y][current_x] = 'S';
            MAP_MATRIX[end_y][end_x] = 'X';

            //creating a solution path from start to finish

            //finding a start and finish position inside the map matrix
            vector<bool> available_directions;
            int current_direction = 0;
            int n_of_possible_directions = 0;
            int n_of_found_directions = 0;
            int length = 0;
            int previous_direction = 0;
            int min_length = 0;

            //cout << "end (" << end_x << ", " << end_y << ")" << endl;

            //finding the lines to form the solution path
            for (int line = 0; line < N_OF_LINES_TO_WIN; line++) {

                //cout << "curr (" << current_x << ", " << current_y << ")" << endl;

                available_directions = {1, 1, 1, 1};    //{left, up, right, down}

                //determining available directions of the move

                //preventing moving in the same direction twice in a row
                if (line != 0) available_directions[current_direction] = 0;

                //preventing backtracking if necessary
                if (line != 0) {
                    if (length < 5) available_directions[(current_direction + 2) % 4] = 0;
                }

                //preventing movement off of the edge of the map
                if (current_x <= 1) available_directions[0] = 0;
                else if (current_x >= (MAP_X - 2)) available_directions[2] = 0;
                
                if (current_y <= 1) available_directions[1] = 0;
                else if (current_y >= (MAP_Y - 2)) available_directions[3] = 0;

                //ensuring arrival at the end
                if (line == (N_OF_LINES_TO_WIN - 2)) {
                    if (current_x == end_x) {
                        available_directions[1] = 0;
                        available_directions[3] = 0;
                        N_OF_LINES_TO_WIN++;
                    } else if (current_y == end_y) {
                        available_directions[0] = 0;
                        available_directions[2] = 0;
                        N_OF_LINES_TO_WIN++;
                    }
                    if (current_x < end_x) available_directions[0] = 0;
                    else if (current_x > end_x) available_directions[2] = 0;
                    if (current_y < end_y) available_directions[1] = 0;
                    else if (current_y > end_y) available_directions[3] = 0;
                }

                if (line == (N_OF_LINES_TO_WIN - 1)) {
                    if (current_y == end_y) {
                        if (current_x < end_x) available_directions = {0, 0, 1, 0};
                        else available_directions = {1, 0, 0, 0};
                    } else {
                        if (current_y < end_y) available_directions = {0, 0, 0, 1};
                        else available_directions = {0, 1, 0, 0};
                    }
                }

                //determining the direction of the move based on the ones available
                n_of_possible_directions = 0;
                for (int i = 0; i < 4; i++) {
                    if (available_directions[i] == 1) n_of_possible_directions++;
                }

                previous_direction = current_direction;
                current_direction = getRandom(0, n_of_possible_directions - 1);

                n_of_found_directions = 0;
                for (int i = 0; i < 4; i++) {
                    if (available_directions[i] == 1) {
                        if (current_direction == n_of_found_directions) {
                            current_direction = i;
                            break;
                        } else {
                            n_of_found_directions++;
                        }
                    }
                }

                //determining the length of a move and moving
                if (current_direction == ((previous_direction + 2) % 4)) min_length = length / 2;
                else min_length = 1;

                length = 0;

                if (current_direction == 0) {

                    if (line == (N_OF_LINES_TO_WIN - 2) || line == (N_OF_LINES_TO_WIN - 1)) {
                        length = current_x - end_x;
                    } else {
                        length = getRandom(min_length, (current_x - 1));
                        while (((current_x - length == end_x) || (current_x - length == end_x + 1)) && (current_y == end_y))
                            length = getRandom(min_length, (current_x - 1));
                    }
                    
                    for (int x = 0; x < length; x++) {
                        current_x -= 1;
                        MAP_MATRIX[current_y][current_x] = 'P';
                    }

                } else if (current_direction == 1) {
                    
                    if (line == (N_OF_LINES_TO_WIN - 2) || line == (N_OF_LINES_TO_WIN - 1)) {
                        length = current_y - end_y;
                    } else {
                        length = getRandom(min_length, (current_y - 1));
                        while (((current_y - length == end_y) || (current_y - length == end_y + 1)) && (current_x == end_x))
                            length = getRandom(min_length, (current_y - 1));
                    }

                    for (int y = 0; y < length; y++) {
                        current_y -= 1;
                        MAP_MATRIX[current_y][current_x] = 'P';
                    }

                } else if (current_direction == 2) {

                    if (line == (N_OF_LINES_TO_WIN - 2) || line == (N_OF_LINES_TO_WIN - 1)) {
                        length = end_x - current_x;
                    } else {
                        length = getRandom(min_length, (((MAP_X - 1) - 1) - current_x));
                        while (((current_x + length == end_x) || (current_x + length == end_x - 1)) && (current_y == end_y)) {
                            //cout << "[ " << length << " " << (current_x + length - end_x) << " ]" << endl;
                            length = getRandom(min_length, (((MAP_X - 1) - 1) - current_x));
                        }
                    }

                    for (int x = 0; x < length; x++) {
                        current_x += 1;
                        MAP_MATRIX[current_y][current_x] = 'P';
                    }

                } else {

                    if (line == (N_OF_LINES_TO_WIN - 2) || line == (N_OF_LINES_TO_WIN - 1)) {
                        length = end_y - current_y;
                    } else {
                        length = getRandom(min_length, (((MAP_Y - 1) - 1) - current_y));
                        while (((current_x + length == end_x) || (current_x + length == end_x - 1)) && (current_x == end_x))
                            length = getRandom(min_length, (((MAP_Y - 1) - 1) - current_y));
                    }

                    for (int y = 0; y < length; y++) {
                        current_y += 1;
                        MAP_MATRIX[current_y][current_x] = 'P';
                    }

                }

                //cout << "available directions: " << available_directions[0] << " " << available_directions[1] << " " << available_directions[2] << " " << available_directions[3] << endl;
                //cout << "current direction: " << current_direction << endl;
                //cout << "length: " << length << endl;

                cout << current_direction << length << " ";

            }

            cout << endl;

            MAP_MATRIX[current_y][current_x] = 'S';
            MAP_MATRIX[end_y][end_x] = 'X';

        }

};

int main() {

    int WIDTH = 10;
    int HEIGHT = 10;
    int LINES = 10;
    int OBJECTS = 20;

    //random number generator setup
    srand(time(0));

    PlayMap map(WIDTH, HEIGHT, LINES, OBJECTS);
    map.generate();

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << map.MAP_MATRIX[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}