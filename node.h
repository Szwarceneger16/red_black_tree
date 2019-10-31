#pragma once

template<class T>
class node
{
public:
	char lp[4];
	T value;
	node<T>* parent;
	node<T>* child_left;
	node<T>* child_right;
	bool is_red;
	node(T val, node<T>* par,char const lpp[4]) :node(val, par,lpp, true) {};
	node(T val, node<T>* par,char const lpp[4],bool red) :value(val), parent(par), child_left(NULL), child_right(NULL),is_red(red) 
	{
		lp[0] = lpp[0]; lp[1] = lpp[1]; lp[2] = lpp[2]; lp[3] = lpp[3];
	};
};

class rb_tree_exceptions
{
	short i;
public:
	explicit rb_tree_exceptions(short ii) :i(ii) {};
	std::string get_info(void)
	{
		switch (this->i)
		{
		case 1:
			return "Error! Finding value doesn't exist!";
			break;
		case 2:
			return "Error! You fucked up! This red_black_tree is empty!!!";
			break;
		case 3:
			return "Error! You pass value smaller than 0! Please Kill yoursefl";
			break;
		default:
			return "I don't recognize this error";
			break;
		}
	}
};
