/*
	huffcode.hpp
	Dustin L. Dodson
	CS 411 - Assignment 6
	24 Nov, 2017
*/

// Glenn G. Chappell
// 29 Nov 2015
//
// For CS 411/611 Fall 2015
// Assignment 6, Exercise A
// Header for class HuffCode
//
// Modified 11/22/17
// Chris Hartman
// For CS 411 Fall 2017

#ifndef FILE_HUFFCODE_H_INCLUDED
#define FILE_HUFFCODE_H_INCLUDED

#include <string>
using std::string;

#include <unordered_map>
using std::unordered_map;

// Class HuffCode
// Encoding & decoding using a Huffman code
class HuffCode {
	public:
		// Compiler-generated default ctor, copy ctor, copy =, dctor used

		void setWeights(const unordered_map<char, int> & theweights);

		string encode(const string & text) const;

		string decode(const string & codestr) const;

	// ***** HuffCode: data members *****
	private:

};  // End class HuffCode

#endif //#ifndef FILE_HUFFCODE_CPP_INCLUDED