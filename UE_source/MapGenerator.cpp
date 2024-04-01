// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"

MapGenerator::MapGenerator(int width, int height, int lines, int objects)
{
    MAP_X = width;
    MAP_Y = height;
    N_OF_LINES_TO_WIN = lines;
    N_OF_OBJECTS = objects;

    MAP_MATRIX.Init(TArray<char>(), MAP_Y);
    for (int i = 0; i < MAP_Y; i++) {
        MAP_MATRIX[i].Init('.', MAP_X);
    }
}

MapGenerator::~MapGenerator()
{
    UE_LOG(LogTemp, Warning, TEXT("Bye-bye!"));
}

int MapGenerator::getRandom(int lower, int upper)
{
    return ((rand() % (upper - lower + 1)) + lower);
}

int MapGenerator::generatePaths()
{
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
    TArray<int> available_directions;
    int current_direction = 0;
    int n_of_possible_directions = 0;
    int n_of_found_directions = 0;
    int length = 0;
    int previous_direction = 0;
    int min_length = 0;
    int loop_counter = 0;

    //cout << "end (" << end_x << ", " << end_y << ")" << endl;

    //finding the lines to form the solution path
    for (int line = 0; line < N_OF_LINES_TO_WIN; line++) {

        //cout << "curr (" << current_x << ", " << current_y << ")" << endl;

        available_directions.Init(1, 4);    //{left, up, right, down}

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

        if (n_of_possible_directions == 0) return 1;

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

        //determining the length of a move
        if (current_direction == ((previous_direction + 2) % 4)) min_length = length / 2;
        else min_length = 1;

        length = 0;
        loop_counter = 0;

        if (current_direction == 0) {

            if (line == (N_OF_LINES_TO_WIN - 2) || line == (N_OF_LINES_TO_WIN - 1)) {
                length = current_x - end_x;
            } else {
                length = getRandom(min_length, (current_x - 1));
                while (((current_x - length == end_x) || (current_x - length == end_x + 1)) && (current_y == end_y)) {
                    length = getRandom(min_length, (current_x - 1));
                    if (loop_counter == 5) return 1;
                    loop_counter++;
                }
            }
            
            //Marking the correct path and placing a box at the end of it
            for (int x = 0; x < length; x++) {
                current_x -= 1;
                if (MAP_MATRIX[current_y][current_x] != 'B') MAP_MATRIX[current_y][current_x] = 'P';
            }
            MAP_MATRIX[current_y][current_x - 1] = 'B';

        } else if (current_direction == 1) {
            
            if (line == (N_OF_LINES_TO_WIN - 2) || line == (N_OF_LINES_TO_WIN - 1)) {
                length = current_y - end_y;
            } else {
                length = getRandom(min_length, (current_y - 1));
                while (((current_y - length == end_y) || (current_y - length == end_y + 1)) && (current_x == end_x)) {
                    length = getRandom(min_length, (current_y - 1));
                    if (loop_counter == 5) return 1;
                    loop_counter++;
                }
            }

            for (int y = 0; y < length; y++) {
                current_y -= 1;
                if (MAP_MATRIX[current_y][current_x] != 'B') MAP_MATRIX[current_y][current_x] = 'P';
            }
            MAP_MATRIX[current_y - 1][current_x] = 'B';

        } else if (current_direction == 2) {

            if (line == (N_OF_LINES_TO_WIN - 2) || line == (N_OF_LINES_TO_WIN - 1)) {
                length = end_x - current_x;
            } else {
                length = getRandom(min_length, (((MAP_X - 1) - 1) - current_x));
                while (((current_x + length == end_x) || (current_x + length == end_x - 1)) && (current_y == end_y)) {
                    length = getRandom(min_length, (((MAP_X - 1) - 1) - current_x));
                    if (loop_counter == 5) return 1;
                    loop_counter++;
                }
            }

            for (int x = 0; x < length; x++) {
                current_x += 1;
                if (MAP_MATRIX[current_y][current_x] != 'B') MAP_MATRIX[current_y][current_x] = 'P';
            }
            MAP_MATRIX[current_y][current_x + 1] = 'B';

        } else {

            if (line == (N_OF_LINES_TO_WIN - 2) || line == (N_OF_LINES_TO_WIN - 1)) {
                length = end_y - current_y;
            } else {
                length = getRandom(min_length, (((MAP_Y - 1) - 1) - current_y));
                while (((current_y + length == end_y) || (current_y + length == end_y - 1)) && (current_x == end_x)) {
                    length = getRandom(min_length, (((MAP_Y - 1) - 1) - current_y));
                    if (loop_counter == 5) return 1;
                    loop_counter++;
                }
            }

            for (int y = 0; y < length; y++) {
                current_y += 1;
                if (MAP_MATRIX[current_y][current_x] != 'B') MAP_MATRIX[current_y][current_x] = 'P';
            }
            MAP_MATRIX[current_y + 1][current_x] = 'B';

        }
    }

    MAP_MATRIX[start / MAP_Y][start % MAP_Y] = 'S';
    MAP_MATRIX[end_y][end_x] = 'X';

    return 0;
}

int MapGenerator::placeBoxes()
{
    bool boxesPlaced = false;
    int potential_direction = 0;
    int potential_distance = 0;
    int tries = 0;
    
    //iterating through all the fields of the map looking for the ones with boxes
    for (int current_y = 0; current_y < MAP_Y; current_y++) {
        for (int current_x = 0; current_x < MAP_X; current_x++) {

            if (MAP_MATRIX[current_y][current_x] == 'B') {

                boxesPlaced = false;
                tries = 0;

                while (!boxesPlaced) {

                    if (tries == 5) break;
                    tries++;

                    potential_direction = getRandom(0, 3);
                    
                    if (potential_direction == 0) {

                        if (current_x == 0 || current_x == 1 || current_x == (MAP_X - 1)) continue;

                        potential_distance = getRandom(2, current_x);
                        if (MAP_MATRIX[current_y][current_x - potential_distance] != '.') {
                            if (MAP_MATRIX[current_y][current_x - potential_distance] != 'b'
                                && MAP_MATRIX[current_y][current_x - potential_distance] != 'B') continue;
                        }

                        if (MAP_MATRIX[current_y][current_x + 1] != '.') {
                            if (MAP_MATRIX[current_y][current_x + 1] != 'b'
                                && MAP_MATRIX[current_y][current_x + 1] != 'B') continue;
                        }

                        MAP_MATRIX[current_y][current_x - potential_distance] = 'b';
                        MAP_MATRIX[current_y][current_x + 1] = 'b';
                        boxesPlaced = true;

                        //Moving the initial boxes
                        MAP_MATRIX[current_y][current_x - potential_distance + 1] = 'b';
                        if (MAP_MATRIX[current_y][current_x] != 'X') MAP_MATRIX[current_y][current_x] = '.';

                    } else if (potential_direction == 1) {

                        if (current_y == 0 || current_y == 1 || current_y == (MAP_Y - 1)) continue;

                        potential_distance = getRandom(2, current_y);
                        if (MAP_MATRIX[current_y - potential_distance][current_x] != '.') {
                            if (MAP_MATRIX[current_y - potential_distance][current_x] != 'b'
                                && MAP_MATRIX[current_y - potential_distance][current_x] != 'B') continue;
                        }

                        if (MAP_MATRIX[current_y + 1][current_x] != '.') {
                            if (MAP_MATRIX[current_y + 1][current_x] != 'b'
                                && MAP_MATRIX[current_y + 1][current_x] != 'B') continue;
                        }

                        MAP_MATRIX[current_y - potential_distance][current_x] = 'b';
                        MAP_MATRIX[current_y + 1][current_x] = 'b';
                        boxesPlaced = true;

                        MAP_MATRIX[current_y - potential_distance + 1][current_x] = 'b';
                        if (MAP_MATRIX[current_y][current_x] != 'X') MAP_MATRIX[current_y][current_x] = '.';

                    } else if (potential_direction == 2) {

                        if (current_x == (MAP_X - 1) || current_x == (MAP_X - 2) || current_x == 0) continue;

                        potential_distance = getRandom(2, (MAP_X - 1 - current_x));
                        if (MAP_MATRIX[current_y][current_x + potential_distance] != '.') {
                            if (MAP_MATRIX[current_y][current_x + potential_distance] != 'b'
                                && MAP_MATRIX[current_y][current_x + potential_distance] != 'B') continue;
                        }

                        if (MAP_MATRIX[current_y][current_x - 1] != '.') {
                            if (MAP_MATRIX[current_y][current_x - 1] != 'b'
                                && MAP_MATRIX[current_y][current_x - 1] != 'B') continue;
                        }

                        MAP_MATRIX[current_y][current_x + potential_distance] = 'b';
                        MAP_MATRIX[current_y][current_x - 1] = 'b';
                        boxesPlaced = true;

                        MAP_MATRIX[current_y][current_x + potential_distance - 1] = 'b';
                        if (MAP_MATRIX[current_y][current_x] != 'X') MAP_MATRIX[current_y][current_x] = '.';

                    } else {

                        if (current_y == (MAP_Y - 1) || current_y == (MAP_Y - 2) || current_y == 0) continue;

                        potential_distance = getRandom(2, (MAP_Y - 1 - current_y));
                        if (MAP_MATRIX[current_y + potential_distance][current_x] != '.') {
                            if (MAP_MATRIX[current_y + potential_distance][current_x] != 'b'
                                && MAP_MATRIX[current_y + potential_distance][current_x] != 'B') continue;
                        }

                        if (MAP_MATRIX[current_y - 1][current_x] != '.') {
                            if (MAP_MATRIX[current_y - 1][current_x] != 'b'
                                && MAP_MATRIX[current_y - 1][current_x] != 'B') continue;
                        }

                        MAP_MATRIX[current_y + potential_distance][current_x] = 'b';
                        MAP_MATRIX[current_y - 1][current_x] = 'b';
                        boxesPlaced = true;

                        MAP_MATRIX[current_y + potential_distance - 1][current_x] = 'b';
                        if (MAP_MATRIX[current_y][current_x] != 'X') MAP_MATRIX[current_y][current_x] = '.';

                    }

                }

            }

        }
    }

    return 0;
}

int MapGenerator::formatLayout()
{
    for (int i = 0; i < MAP_Y; i++) {
        for (int j = 0; j < MAP_X; j++) {
            if (MAP_MATRIX[i][j] == 'P') MAP_MATRIX[i][j] = '.';
            if (MAP_MATRIX[i][j] == 'b') MAP_MATRIX[i][j] = 'B';
        }
    }

    return 0;
}

int MapGenerator::printLog()
{
    for (int i = 0; i < MAP_Y; i++) {
        for (int j = 0; j < MAP_X; j++) {
            UE_LOG(LogTemp, Log, TEXT("%c"), MAP_MATRIX[i][j]);
        }
        UE_LOG(LogTemp, Log, TEXT("\n"));
    }

    return 0;
}

