#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <XML\rapidxml.hpp>


using namespace std;

void ReadXML() {
	ifstream myfile("sampleconfig.xml");
	rapidxml::xml_document<> doc;

	/* "Read file into vector<char>"  See linked thread above*/
	vector<char> buffer((istreambuf_iterator<char>(myfile)), istreambuf_iterator<char>());

	buffer.push_back('\0');

	cout << &buffer[0] << endl; /*test the buffer */

	doc.parse<0>(&buffer[0]);

	cout << "Name of my first node is: " << doc.first_node()->name() << "\n";  /*test the xml_document */


}