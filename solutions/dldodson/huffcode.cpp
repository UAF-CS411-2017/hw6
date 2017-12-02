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

#include <iterator>
using std::begin;
using std::end;

bool HuffCode::Compare::operator() (const HuffCode::Node & a, const HuffCode::Node & b) {
	return a.getWeight() > b.getWeight();
}

HuffCode::Node::Node(const char & ch, const int & weight): 
	_left(NULL), _right(NULL), _char(ch), _weight(weight) {}

HuffCode::Node::Node(shared_ptr<Node> left, shared_ptr<Node> right, const int & weight): 
	_left(left), _right(right), _char(0), _weight(weight) {}

const int HuffCode::Node::getWeight() const {
	return this->_weight;
}

const shared_ptr<HuffCode::Node> & HuffCode::Node::getLeft() const {
	return this->_left;
}

const shared_ptr<HuffCode::Node> & HuffCode::Node::getRight() const {
	return this->_right;
}

void HuffCode::Node::traverse(unordered_map<char, string> & ledger, string & code) {
	if(!this->_left && !this->_right) {
		ledger[this->_char] = code;
		return;
	}

	if(this->_left) {
		code.push_back('0');
		this->_left->traverse(ledger, code);
		code.pop_back();
	}

	if(this->_right) {
		code.push_back('1');
		this->_right->traverse(ledger, code);
		code.pop_back();
	}
}

void HuffCode::setWeights(const unordered_map<char, int> & theWeights) {
	this->_ledger = unordered_map<char, string>();
	this->_tree = NULL;

	if(theWeights.size() > 1) {
		priority_queue<HuffCode::Node, vector<HuffCode::Node>, HuffCode::Compare> minHeap;

		for(const auto & i : theWeights)
			minHeap.emplace(i.first, i.second);

		while(minHeap.size() > 1) {
			auto min1 = minHeap.top();
			minHeap.pop();

			auto min2 = minHeap.top();
			minHeap.pop();

			minHeap.emplace(make_shared<Node>(min1), make_shared<Node>(min2), min1._weight + min2._weight);
		}

		if(minHeap.size() > 0) {
			string tempStr = "";
			this->_tree = make_shared<Node>(minHeap.top());
			this->_tree->traverse(this->_ledger, tempStr);
		}
	}
	else if(theWeights.size() == 1) {
		char theChar;
		int theInt;

		for(const auto & i : theWeights) {
			theChar = i.first;
			theInt = i.second;
		}

		this->_ledger[theChar] = "0";
		this->_tree = make_shared<HuffCode::Node>(theChar, theInt);
	}
}

string HuffCode::encode(const string & text) const {
	string ret = "";
	
	for(const auto & c : text) {
		auto temp = this->_ledger.find(c);

		if(temp != end(this->_ledger))
			ret += temp->second;
	}

	return ret;
}

string HuffCode::decode(const string & codeStr) const {
	string ret = "";
	shared_ptr<Node> currNode = this->_tree;

	auto it = begin(codeStr);

	while(it != end(codeStr)) {
		if(!currNode->_left && !currNode->_right) {
			ret += currNode->_char;
			currNode = this->_tree;
		}

		switch(*it) {
			case '0':
				currNode = currNode->_left;
				break;
			case '1':
				currNode = currNode->_right;
				break;
		}

		it++;
	}

	if(currNode && currNode->_char)
		ret += currNode->_char;

	return ret;
}

#endif