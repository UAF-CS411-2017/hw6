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
using std::make_shared;

#include <queue>
using std::priority_queue;

#include <vector>
using std::vector;

bool HuffCode::Compare::operator() (const HuffCode::Node & a, const HuffCode::Node & b) {
	return a._weight > b._weight;
}

HuffCode::Node::Node(const char & ch, const int & weight): 
	_left(NULL), _right(NULL), _char(ch), _weight(weight) {}

HuffCode::Node::Node(shared_ptr<Node> left, shared_ptr<Node> right): 
	_left(left), _right(right), _char(0), _weight(0) {}

const int HuffCode::Node::getWeight() const {
	auto weight = this->_weight;

	if(this->_left)
		weight += this->_left->getWeight();

	if(this->_right)
		weight += this->_right->getWeight();

	return weight;
}

const shared_ptr<HuffCode::Node> & HuffCode::Node::getLeft() const {
	return this->_left;
}

const shared_ptr<HuffCode::Node> & HuffCode::Node::getRight() const {
	return this->_right;
}

void HuffCode::setWeights(const unordered_map<char, int> & theWeights) {
	priority_queue<HuffCode::Node, vector<HuffCode::Node>, Compare> minHeap;

	for(auto i : theWeights) {
		HuffCode::Node node(i.first, i.second);
		minHeap.push(node);
	}

	while(minHeap.size() > 1) {
		auto min1 = minHeap.top();
		minHeap.pop();

		auto min2 = minHeap.top();
		minHeap.pop();

		HuffCode::Node node(make_shared<Node>(min1), make_shared<Node>(min2));
		minHeap.push(node);
	}

	if(minHeap.size() > 0)
		this->_tree = make_shared<Node>(minHeap.top());
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