/***************************************************************************
 * shakewebcpp.cppsslookupservercpp  -  Program to serve Shakespeare search results
 *
 * copyright : (C) 2021 by Jim Skon
 *
*
*
***************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include "textindex.h"

// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#define XML_USE_STL

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

int main() {
  // Object used for receiving AJAX call (and getting parameters)
  Cgicc cgi;    // Ajax object

  list<int> result;
  list<int>::iterator it;
  int position;
  string fileName = "/home/class/shake/Shakespeare.txt";
  string line;
  // create text index
  textindex index(fileName);

  // Prepare for output to web page
  cout << "Content-Type: text/plain\n\n";

  ifstream textFile;
  // Open the text file
  textFile.open(fileName, ios::in);
  if (textFile.bad()) {
      /* send back the results */
      cout << "File open failure!" << endl;
      return 0;
  }
  
  // Create AJAX objects to receive information from web page.
  form_iterator itword = cgi.getElement("word");

  // Retrieve the actual paramaters
  string word = **itword;

  /* Convert name to lower case*/
  transform(word.begin(), word.end(), word.begin(), ::tolower);

    result = index.indexSearch(word);
    int results = result.size();

    if (result.size() < 1) {
      cout << "No Matches for:" << word << endl;
    } else {

	  // Give the match count
	  cout << "Matches: " << results << "<br />" << endl;
	  /* Traverse the list of references */
  	for (it = result.begin() ; it != result.end(); it++)
	  {
	    // Grab the postion of the reference out of the iterator
	    position = (*it);
	    // Seek that line in the file, and display it
	    textFile.seekg (position, ios::beg);
	    getline(textFile,line);
	    cout << line << "<br />" << endl;
	  }

   } // results
}

