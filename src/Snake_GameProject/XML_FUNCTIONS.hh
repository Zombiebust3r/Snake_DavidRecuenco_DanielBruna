#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

#include "XML\rapidxml.hpp"
#include "XML\rapidxml_iterators.hpp"
#include "XML\rapidxml_print.hpp"
#include "XML\rapidxml_utils.hpp"


#include "Resource.hh"

using namespace rapidxml;
using namespace std;
namespace {

	//THIS FUNCTION TAKES A POINTER TO AN ARRAY OF 10 INTS TO STORE THE 10 VALUES OF THE RANKING FROM HIGHER TO LOWER
	void ReadTop10(int *myRanking) {
		string fileName = "Top10";
		int scoreForArray = 0;
		string xmlScore = "";
		int arrayIndex = 0;

		xml_document<> doc;
		std::ifstream file(RESOURCE_XML_FILE(fileName));

		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		xml_node<> *root_node = doc.first_node();
		xml_node<> *pNode = root_node->first_node();

		for (pNode; pNode; pNode = pNode->next_sibling()) {
			xmlScore = pNode->name();
			scoreForArray = atoi(xmlScore.c_str());
			myRanking[arrayIndex] = scoreForArray;
			arrayIndex++;
		}
	}

	//No se usa, la hemos usado para hacer pruebas con tipos de archivos.
	void CreateFiles() {
		string top10 = "TOP10";
		ofstream playerFile;
		playerFile.open(RESOURCE_XML_FILE(top10));
		playerFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
		playerFile.close();

		string easy = "Easy";
		playerFile.open(RESOURCE_XML_FILE(easy));
		playerFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
		playerFile.close();

		string med = "Medium";
		playerFile.open(RESOURCE_XML_FILE(med));
		playerFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
		playerFile.close();

		string hard = "Hard";
		playerFile.open(RESOURCE_XML_FILE(hard));
		playerFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
		playerFile.close();
	}

	//THIS FUNCTION READS THE XML ARCHIVE AND STORES THE VALUES ON THE VARIABLES OF EASYMODE.hh
	void ReadGrid(int mode, int *r, int *c, int *t, int *z, int *x, int *y) { //mode -> 1:Easy/2:Medium/3:Hard
																			  //DEFINE WICH MODE WE ARE IN.
		string fileName = "";
		switch (mode)
		{
		case 1:
			fileName = "Easy";
			break;
		case 2:
			fileName = "Medium";
			break;
		case 3:
			fileName = "Hard";
			break;
		default:
			fileName = "Easy";
			break;
		}
		//Parse xml doc in order to read:
		xml_document<> doc;
		std::ifstream file(RESOURCE_XML_FILE(fileName));

		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		xml_node<> *root_node = doc.first_node();
		xml_node<> *pNode = root_node->first_node();
		int i = 0;
		int valueForArray = 0;
		string xmlValue = "";
		for (pNode; pNode; pNode = pNode->next_sibling()) {
			i++; //Increments the index to know what value we are reading. Since it's going to be the same order everytime we can use an integer value instead of the names.
				 //For each case we put the value on its respective variable. This way we store the values as ints outside this function so we can use them to create the grid.
			switch (i)
			{
			case 1:
				xmlValue = pNode->value();
				valueForArray = atoi(xmlValue.c_str());
				*r = valueForArray;
				break;
			case 2:
				xmlValue = pNode->value();
				valueForArray = atoi(xmlValue.c_str());
				*c = valueForArray;
				break;
			case 3:
				xmlValue = pNode->value();
				valueForArray = atoi(xmlValue.c_str());
				*z = valueForArray;
				break;
			case 4:
				xmlValue = pNode->value();
				valueForArray = atoi(xmlValue.c_str());
				*x = valueForArray;
				break;
			case 5:
				xmlValue = pNode->value();
				valueForArray = atoi(xmlValue.c_str());
				*y = valueForArray;
				break;
			case 6:
				xmlValue = pNode->value();
				valueForArray = atoi(xmlValue.c_str());
				*t = valueForArray;
				break;
			default:
				break;
			}

		}

	}

	//COMPARISONS FOR THE TOP10 FILE. MOVES ALL THE VALUES DOWN AND THEN CHANGES THE VALUE THAT HAS BEEN BEATEN.
	void CompareTop10Snake(string score) {
		int i_score = atoi(score.c_str());
		int xmlScore = 0;
		int i = 0;
		int iterations = 0;
		string fileName = "Top10";
		string xml_score = "";

		xml_document<> doc;
		std::ifstream file(RESOURCE_XML_FILE(fileName));

		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		xml_node<> *root_node = doc.first_node();
		xml_node<> *pNode = root_node->first_node();

		for (pNode; pNode; pNode = pNode->next_sibling()) {
			i++;
			xml_score = pNode->name();
			xmlScore = atoi(xml_score.c_str());
			if (xmlScore < i_score) {
				iterations = 10 - i; //Gives the number of iterations we have to do to modify the top10 file.  
				xml_node<> *pToModify = root_node->last_node();	//Should go to the last node. The 10th score in the ranking.
				xml_node<> *pLast = pToModify->previous_sibling();	//Should point to the previous node in the ranking. The 9th.

				for (int j = iterations; j > 0; j--) {
					pToModify->name(pLast->name());
					pToModify = pToModify->previous_sibling();
					pLast = pLast->previous_sibling();
				}
				pToModify->name(score.c_str());

				//xml_node<> *aNode = doc.first_node();
				//xml_node<> *anotherNode = aNode->first_node();
				//string otroNombre = "1000";
				//anotherNode->value(otroNombre.c_str());

				xml_node<> *encode = doc.allocate_node(node_declaration);
				encode->append_attribute(doc.allocate_attribute("version", "1.0"));
				encode->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
				doc.prepend_node(encode);

				ofstream playerFile;
				playerFile.open(RESOURCE_XML_FILE(fileName));
				playerFile << doc;
				playerFile.close();
				break;

			}
		}

		/* 
		for (pNode; pNode; pNode = pNode->next_sibling()) {
			i++;
			cout << "Node #" << i << " Name: " << pNode->name() << "Score: " << pNode->value() << endl;
			xml_score = pNode->value();
			xmlScore = atoi(xml_score.c_str());
			if (xmlScore < i_score) {
				iterations = 10 - i; //Gives the number of iterations we have to do to modify the top10 file.  
				xml_node<> *pToModify = root_node->last_node();	//Should go to the last node. The 10th score in the ranking.
				xml_node<> *pLast = pToModify->previous_sibling();	//Should point to the previous node in the ranking. The 9th.

				for (int j = iterations; j > 0; j--) {
					pToModify->value(pLast->value());
					pToModify = pToModify->previous_sibling();
					pLast = pLast->previous_sibling();
				}
				pToModify->value(score.c_str());
				
				//xml_node<> *aNode = doc.first_node();
				//xml_node<> *anotherNode = aNode->first_node();
				//string otroNombre = "1000";
				//anotherNode->value(otroNombre.c_str());

				xml_node<> *encode = doc.allocate_node(node_declaration);
				encode->append_attribute(doc.allocate_attribute("version", "1.0"));
				encode->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
				doc.prepend_node(encode);

				ofstream playerFile;
				playerFile.open(RESOURCE_XML_FILE(fileName));
				playerFile << doc;
				playerFile.close();
				break;

			}
		}
		*/

		//file.close();
		doc.clear();

	}
}