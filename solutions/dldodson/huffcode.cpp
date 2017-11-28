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
	return a.getWeight() > b.getWeight();
}

HuffCode::Node::Node(const char & ch, const int & weight): 
	_left(NULL), _right(NULL), _char(ch), _code(0), _weight(weight) {}

HuffCode::Node::Node(shared_ptr<Node> left, shared_ptr<Node> right): 
	_left(left), _right(right), _char(0), _code(0), _weight(0) {}

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

void HuffCode::Node::traverse(unordered_map<char, string> & ledger, const string code) {
	if(!this->_left && !this->_right) {
		ledger[this->_char] = code;
		return;
	}

	if(this->_left)
		this->_left->traverse(ledger, (code + "0"));

	if(this->_right)
		this->_right->traverse(ledger, (code + "1"));
}

void HuffCode::setWeights(const unordered_map<char, int> & theWeights) {
	this->_ledger = unordered_map<char, string>();
	this->_reverseLedger = unordered_map<string, char>();
	this->_tree = NULL;

	priority_queue<HuffCode::Node, vector<HuffCode::Node>, Compare> minHeap;

	for(auto i : theWeights) {
		// cout << i.first << " " << i.second << endl;
		minHeap.emplace(i.first, i.second);
	}

	while(minHeap.size() > 1) {
		auto min1 = minHeap.top();
		min1._code = '0';
		minHeap.pop();

		auto min2 = minHeap.top();
		min2._code = '1';
		minHeap.pop();

		minHeap.emplace(make_shared<Node>(min1), make_shared<Node>(min2));
	}

	if(minHeap.size() > 0) {
		string tempStr = "";
		this->_tree = make_shared<Node>(minHeap.top());
		this->_tree->traverse(this->_ledger, tempStr);

		for(const auto & i : this->_ledger)
			this->_reverseLedger[i.second] = i.first;
	}
}

string HuffCode::encode(const string & text) const {
	string ret = "";
	
	for(const auto & c : text) {
		auto temp = this->_ledger.find(c);

		if(temp != std::end(this->_ledger))
			ret += temp->second;
	}

	// for(const auto i : this->_ledger)
	// 	cout << i.first << " - " << i.second << endl;

	return ret;
}

string HuffCode::decode(const string & codeStr) const {
	string ret = "";
	shared_ptr<Node> currNode = this->_tree;

	auto it = std::begin(codeStr);

	while(it != std::end(codeStr)) {
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