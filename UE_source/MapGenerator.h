// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include <time.h>


class SPARKYPUZZLE_API MapGenerator
{
public:

	MapGenerator(int width, int height, int lines, int objects);

	~MapGenerator();

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
    TArray<TArray<char>> MAP_MATRIX;

	//function that returns a random number inside a given interval
	int getRandom(int lower, int upper);

	//function that generates the solution paths and neccessary objects on the map
	int generatePaths();

	//function that places additional objects and moves them around
	int placeBoxes();

	//function that prepares the matrix to be used to generate the 3D level
	int formatLayout();

	//logs the map layout to terminal
	int printLog();

};
