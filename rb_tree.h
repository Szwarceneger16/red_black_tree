#pragma once
#include "node.h"
#include <string>

class rb_tree_exceptions
{
	short i;
public:
	explicit rb_tree_exceptions(short ii):i(ii) {};
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

template<class T>
class rb_tree
{
	node<T>* root;
	long size;

	node<T>* search_position_and_add(T val, bool (*fun)(const T, const T))
	{
		node<T> *tmp = this->root;
		while (true)
		{
			if (fun(val,tmp->value))
			{
				if (tmp->child_left == NULL)
				{
					tmp->child_left = new node<T>(val,tmp);
					return tmp->child_left;
				}
				else tmp = tmp->child_left;
			}
			else
			{
				if (tmp->child_right == NULL)
				{
					tmp->child_right = new node<T>(val,tmp);
					return tmp->child_right;
				}
				else tmp = tmp->child_right;
			}
		}
	}

	long fall_in_tree(node<T>* tmp)
	{
		if (!tmp)
		{
			return 0;
		}
		else
		{
			long ll = fall_in_tree(tmp->child_left);
			long rr = fall_in_tree(tmp->child_right);
			if (rr < ll) return(ll + 1);
			else return(rr + 1);
		}
	}

	void fall_in_tree_delete(node<T>* tmp)
	{
		if(tmp->child_left) fall_in_tree_delete(tmp->child_left);
		if(tmp->child_right) fall_in_tree_delete(tmp->child_right);
		delete tmp;
	}

	void fall_in_tree_delete_ptr(node<T>* tmp)
	{
		if (tmp->child_left) fall_in_tree_delete_ptr(tmp->child_left);
		if (tmp->child_right) fall_in_tree_delete_ptr(tmp->child_right);
		delete tmp->value;
		delete tmp;
	}

	bool recolor(node<T>* tmp)
	{
		tmp->child_left->is_red = tmp->child_right->is_red = false;

		if (tmp->parent == NULL) tmp->is_red = false;
		else tmp->is_red = true;
		return true;
	}

	void rotate(node<T>* tmp2, node<T>* tmp3)
	{
		if (tmp2 == tmp2->parent->child_left && tmp2->parent == tmp3->child_left)  // lewa strona prosta
		{
			if (tmp3->parent)
			{
				if (tmp3->parent->child_left == tmp3) tmp3->parent->child_left = tmp3->child_left;
				else tmp3->parent->child_right = tmp3->child_left;
			}
			else {
				this->root = tmp3->child_left;
			}
			tmp3->child_left->parent = tmp3->parent;
			tmp3->parent = tmp3->child_left;
			if (tmp2->parent->child_right == NULL)  tmp3->child_left = NULL;
			else {
				tmp3->child_left = tmp2->parent->child_right; tmp3->child_left->parent = tmp3;
			}
			tmp2->parent->child_right = tmp3;
			tmp2->parent->is_red = false;
			tmp3->is_red = true;
		}
		else if (tmp2 == tmp2->parent->child_right && tmp2->parent == tmp3->child_left) // lewa storna lamana
		{
			tmp2->child_left = tmp3->child_left;
			tmp3->child_left = tmp2;
			tmp2->child_left->parent = tmp2;
			tmp2->parent = tmp3;
			tmp2 = tmp2->child_left;
			tmp2->child_right = NULL;
			// ........
			if (tmp3->parent)
			{
				if (tmp3->parent->child_left == tmp3) tmp3->parent->child_left = tmp3->child_left;
				else tmp3->parent->child_right = tmp3->child_left;
			}
			else {
				this->root = tmp3->child_left;
			}
			tmp3->child_left->parent = tmp3->parent;
			tmp3->parent = tmp3->child_left;
			if (tmp2->parent->child_right == NULL)  tmp3->child_left = NULL;
			else {
				tmp3->child_left = tmp2->parent->child_right; tmp3->child_left->parent = tmp3;
			}
			tmp2->parent->child_right = tmp3;
			tmp2->parent->is_red = false;
			tmp3->is_red = true;
		}
		else if (tmp2 == tmp2->parent->child_right && tmp2->parent == tmp3->child_right) // prawa strona prosta
		{
			if (tmp3->parent)
			{
				if (tmp3->parent->child_left == tmp3) tmp3->parent->child_left = tmp3->child_right;
				else tmp3->parent->child_right = tmp3->child_right;
			}
			else {
				this->root = tmp3->child_right;
			}
			tmp3->child_right->parent = tmp3->parent;
			tmp3->parent = tmp3->child_right;
			if (tmp2->parent->child_left == NULL) tmp3->child_right = NULL;
			else {
				tmp3->child_right = tmp2->parent->child_left; tmp3->child_right->parent = tmp3;
			}
			tmp2->parent->child_left = tmp3;
			tmp2->parent->is_red = false;
			tmp3->is_red = true;
		}
		else // prawa strona lamana
		{
			tmp2->child_right = tmp3->child_right;
			tmp3->child_right = tmp2;
			tmp2->child_right->parent = tmp2;
			tmp2->parent = tmp3;
			tmp2 = tmp2->child_right;
			tmp2->child_left = NULL;
			// ...........
			if (tmp3->parent)
			{
				if(tmp3->parent->child_left == tmp3) tmp3->parent->child_left = tmp3->child_right;
				else tmp3->parent->child_right = tmp3->child_right;
			}
			else {
				this->root = tmp3->child_right;
			}
			tmp3->child_right->parent = tmp3->parent;
			tmp3->parent = tmp3->child_right;
			if (tmp2->parent->child_left == NULL) tmp3->child_right = NULL;
			else {
				tmp3->child_right = tmp2->parent->child_left; tmp3->child_right->parent = tmp3;
			}
			tmp2->parent->child_left = tmp3;
			tmp2->parent->is_red = false;
			tmp3->is_red = true;
		}
	}

	void in_order(node<T>* tmp,void (*fun)(const T, const bool),long quan)
	{
		if (tmp->child_left) in_order(tmp->child_left,fun);
		fun(tmp->value,tmp->is_red);
		if (tmp->child_right) in_order(tmp->child_right,fun);
		return;
	}

	void pre_order(node<T>* tmp, void (*fun)(const T, const bool),long & quan)
	{
		fun(tmp->value,tmp->is_red);
		quan--;
		if (tmp->child_left && quan) pre_order(tmp->child_left, fun,quan);
		if (tmp->child_right && quan) pre_order(tmp->child_right, fun,quan);
		quan++;
		return;
	}

public:
	rb_tree() :root(NULL), size(0) {};
	rb_tree(T val) :rb_tree()
	{
		add(val);
	}

	bool add(T val,bool (*fun)(const T,const T))
	{
		this->size++;
		if (this->root == NULL)
		{
			this->root = new node<T>(val, NULL,false);
			
			return true;
		}
		else
		{
			node<T>* const tmp = search_position_and_add(val,fun);
			node<T>* tmp2=tmp, *tmp3=tmp;
			bool flag = false;

			if (!tmp->parent->parent) return true;

			while (tmp2->parent->is_red && tmp2->is_red && tmp2 != this->root)
			{
				
				tmp3 = tmp2->parent->parent;
				if (tmp3->child_left && tmp3->child_right) // sprawdzanie istnienia wujka do przeklorowania
				{
					if (tmp3->child_left->is_red && tmp3->child_right->is_red && !tmp3->is_red)
					{
						recolor(tmp3);
					}
					else
					{
						rotate(tmp2, tmp3);
					}
				}
				else
				{
					rotate(tmp2, tmp3);
				}

				if (!tmp3->parent) break;
				if (!tmp3->parent->parent) break;
				tmp2 = tmp3;
			}
			
			return true;
		}
	}

	T& find_value(T val,bool (*fun)(const T a,const T b))
	{
		node<T>* tmp = this->root;
		while (true)
		{
			if (tmp->value == val) return tmp->value;
			if (val < tmp->value)
			{
				if (tmp->child_left == NULL) throw rb_tree_exceptions(1);
				else tmp = tmp->child_left;
			}
			else
			{
				if (tmp->child_right == NULL) throw rb_tree_exceptions(1);
				else tmp = tmp->child_right;
			}
		}
	}

	long get_height(void)
	{
		return fall_in_tree(this->root);
	}

	void in_order_traverse(void (*fun)(const T, const bool),long quantity)
	{
		if (!this->root) throw rb_tree_exceptions(2);
		if (quantity < 0) throw rb_tree_exceptions(3);
		in_order(this->root,fun,quantity);
	}
	void in_order_traverse(void (*fun)(const T, const bool))
	{
		long a = this->get_height();
		if (!this->root) throw rb_tree_exceptions(2);
		in_order(this->root, fun, a);
	}

	void pre_order_traverse(void (*fun)(const T,const bool), long quantity)
	{
		if (!this->root) throw rb_tree_exceptions(2);
		if (quantity < 0) throw rb_tree_exceptions(3);
		pre_order(this->root, fun,quantity);
	}
	void pre_order_traverse(void (*fun)(const T, const bool))
	{
		long a = this->get_height();
		if (!this->root) throw rb_tree_exceptions(2);
		pre_order(this->root, fun, a);
	}

	void erase(void)
	{
		if (!this->root) throw rb_tree_exceptions(2);
		fall_in_tree_delete(this->root);
		this->root = NULL;
		this->size = 0;
	}

	bool erase_ptr(void)
	{
		if (!this->root) throw rb_tree_exceptions(2);
		fall_in_tree_delete_ptr(this->root);
		this->root = NULL;
		this->size = 0;
	}
};

