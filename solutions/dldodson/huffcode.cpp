/*
	huffcode.cpp
	Dustin L. Dodson
	CS 411 - Assignment 6
	24 Nov, 2017
*/

// Glenn G. Chappell
// 29 Nov 2015
//
// For CS 411/611 Fall 2015
// Assignment 6, Exercise A
// Source for class HuffCode
//
// Modified 11/22/17
// Chris Hartman
// For CS 411 Fall 2017

#ifndef FILE_HUFFCODE_CPP_INCLUDED
#define FILE_HUFFCODE_CPP_INCLUDED

#include "huffcode.hpp"  // for class HuffCode declaration

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <unordered_map>
using std::unordered_map;

#include <memory>
using std::shared_ptr;

#include <queue>
using std::priority_queue;

#include <vector>
using std::vector;

bool HuffCode::Compare::operator() (const HuffCode::Node & a, const HuffCode::Node & b) {
	return a._weight > b._weight;
}

HuffCode::Node::Node(): _left(NULL), _right(NULL), _char(NULL), _code(NULL), _weight(0) {}

void HuffCode::setWeights(const unordered_map<char, int> & theWeights) {
	priority_queue<HuffCode::Node, vector<HuffCode::Node>, Compare> minHeap;

	for(auto i : theWeights) {
		HuffCode::Node node;
		node._char = i.first;
		node._weight = i.second;
		minHeap.push(node);
		// cout << node._char << " " << node._weight << endl;
	}

	auto min = minHeap.top();
	// minHeap.pop();
	// cout << min._char << " " << min._weight << endl;
}


string HuffCode::encode(const string & text) const {
	// WRITE THIS!!!
	return "";  // DUMMY RETURN
}


string HuffCode::decode(const string & codeStr) const {
	// WRITE THIS!!!
	return "";  // DUMMY RETURN
}

#endif