#pragma once

template<class T>
class node
{
public:
	T value;
	node<T>* parent;
	node<T>* child_left;
	node<T>* child_right;
	bool is_red;
	node(T val, node<T>* par) :node(val, par, true) {};
	node(T val, node<T>* par,bool red) :value(val), parent(par), child_left(NULL), child_right(NULL),is_red(red) {};
};

