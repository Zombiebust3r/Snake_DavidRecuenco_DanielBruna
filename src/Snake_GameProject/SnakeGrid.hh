#pragma once
#include "ID.hh"
#include <XML\rapidxml.hpp>
#include <XML\rapidxml_iterators.hpp>
#include <XML\rapidxml_print.hpp>
#include <XML\rapidxml_utils.hpp>
#include <vector>
#include "Sprite.hh"
#include "Resource.hh"
#include "Logger.hh"

//Width and height of every cell
#define CELL 14

using namespace std;
using namespace Logger;

enum Mode {
	EASY, MEDIUM, HARD
};

namespace {

	class SnakeGrid
	{
	public:
		SnakeGrid();
		~SnakeGrid();
		SnakeGrid(string filename);
		SnakeGrid(Mode mode);
		void SetGrid(Mode mode);
		void DrawGrid();

	private:
		int baseCols, baseRows;
		int rows, cols;
		vector<vector<Sprite>> myGridSprites;

	};

	SnakeGrid::SnakeGrid()
	{
		baseCols = 15; //X
		baseRows = 8; //Y
		myGridSprites.resize(baseCols);
		//Loop to iterate inside myGridSprites in order to fill it. It will not have any obstacles inside.
		for (int i = 0; i <= baseCols - 1; i++) {
			myGridSprites[i].resize(baseRows);
			for (int j = 0; j <= baseRows - 1; j++) {
				if (i == 0 || j == 0 || j == baseRows - 1 || i == baseCols - 1) { myGridSprites[i][j] = { { i + 1, j + 1, 14, 14 }, ObjectID::WALL }; }
				else if (i != 0 || j != 0 || j != baseRows - 1 || i != baseCols - 1) { myGridSprites[i][j] = { { i, j, 14, 14 }, ObjectID::EMPTY }; }
			}
		}

	}

	SnakeGrid::~SnakeGrid()
	{
	}

	SnakeGrid::SnakeGrid(string filename) {	//NOT IN USE
											//SHOULD READ AND LOAD INFORMATION OF THE XML AND STORE IT.
		rapidxml::file<> xmlFile(RESOURCE_FILE(filename));
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *root_node = doc.first_node("document");
		for (rapidxml::xml_node<> * node = root_node->first_node("node"); node; node = node->next_sibling()) {

			Println("Node: ",
				node->first_attribute("att1")->value(),
				" - ",
				node->first_attribute("att2")->value());

		}
	}

	SnakeGrid::SnakeGrid(Mode mode) {
		baseCols = 15; //X
		baseRows = 8; //Y
		switch (mode) {
		case EASY: cols = baseCols * 5; rows = baseRows * 5; printf("EASY"); break;
		case MEDIUM: cols = baseCols * 2; rows = baseRows * 2; printf("MEDIUM"); break;
		case HARD: cols = baseCols * 1; rows = baseRows * 1; printf("HARD"); break;
		}
		myGridSprites.resize(cols);
		//Loop to iterate inside myGridSprites in order to fill it. It will not have any obstacles inside.
		for (int i = 0; i <= cols - 1; i++) {
			myGridSprites[i].resize(rows);
			for (int j = 0; j <= rows - 1; j++) {
				if (i == 0 || j == 0 || j == rows - 1 || i == cols - 1) { myGridSprites[i][j] = { { (CELL / 2) + ((i + 1)*CELL), (120 + (CELL / 2) + ((j + 1)*CELL)), CELL, CELL }, ObjectID::WALL }; }
				else if (i != 0 || j != 0 || j != rows - 1 || i != cols - 1) { myGridSprites[i][j] = { { (CELL / 2) + ((i + 1)*CELL), (120 + (CELL / 2) + ((j + 1)*CELL)), CELL, CELL }, ObjectID::EMPTY }; }
			}
		}


	}

	void SnakeGrid::SetGrid(Mode mode) {
		switch (mode) {
		case EASY: cols = baseCols * 5; rows = baseRows * 5; printf("EASY"); break;
		case MEDIUM: cols = baseCols * 2; rows = baseRows * 2; printf("MEDIUM"); break;
		case HARD: cols = baseCols * 1; rows = baseRows * 1; printf("HARD"); break;
		}
		myGridSprites.resize(cols);
		//Loop to iterate inside myGridSprites in order to fill it. It will not have any obstacles inside.
		for (int i = 0; i <= cols - 1; i++) {
			myGridSprites[i].resize(rows);
			for (int j = 0; j <= rows - 1; j++) {
				if (i == 0 || j == 0 || j == rows - 1 || i == cols - 1) { myGridSprites[i][j] = { { (CELL / 2) + ((i + 1)*CELL), (120 + (CELL / 2) + ((j + 1)*CELL)), CELL, CELL }, ObjectID::WALL }; }
				else if (i != 0 || j != 0 || j != rows - 1 || i != cols - 1) { myGridSprites[i][j] = { { (CELL / 2) + ((i + 1)*CELL), (120 + (CELL / 2) + ((j + 1)*CELL)), CELL, CELL }, ObjectID::EMPTY }; }
			}
		}
	}

	void SnakeGrid::DrawGrid() {
		for (int i = 0; i <= cols - 1; i++) {
			for (int j = 0; j <= rows - 1; j++) {
				if (myGridSprites[i][j].objectID == ObjectID::WALL) { myGridSprites[i][j].Draw(); }
				else if (myGridSprites[i][j].objectID == ObjectID::EMPTY) { myGridSprites[i][j].Draw(); }
			}
		}
	}



}