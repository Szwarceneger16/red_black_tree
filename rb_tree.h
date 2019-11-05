#pragma once
#include "node.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h> 
#include <process.h> 
#include <direct.h>



template<class T>
class rb_tree
{
	node<T>* root;
	long size;
	char lp[4];
	
	int lp_draws;

	node<T>* search_position_and_add(T val, bool (*fun)(const T, const T))
	{
		node<T> *tmp = this->root;
		while (true)
		{
			if (fun(val,tmp->value))
			{
				if (tmp->child_left == NULL)
				{
					tmp->child_left = new node<T>(val,tmp,lp);
					this->increment_lp();
					return tmp->child_left;
				}
				else tmp = tmp->child_left;
			}
			else
			{
				if (tmp->child_right == NULL)
				{
					tmp->child_right = new node<T>(val,tmp,lp);
					this->increment_lp();
					return tmp->child_right;
				}
				else tmp = tmp->child_right;
			}
		}
	}

	void increment_lp()
	{
		lp[0]++;
		if (lp[0] == 'Z') { lp[1]++; lp[0] = 'A'; }
		if (lp[1] == 'Z') { lp[2]++; lp[1] = 'A'; }
		if (lp[2] == 'Z') { lp[3]++; lp[2] = 'A'; }
	}

	int fall_in_tree(node<T>* tmp)
	{
		if (!tmp)
		{
			return 0;
		}
		else
		{
			int ll = fall_in_tree(tmp->child_left);
			int rr = fall_in_tree(tmp->child_right);
			if (rr < ll) return(ll + 1);
			else return(rr + 1);
		}
	}

	void fall_in_tree_file(node<T>* tmp,std::fstream & file1,std::fstream & file2)
	{
			file1 << "		" << tmp->lp[3] << tmp->lp[2] << tmp->lp[1] << tmp->lp[0] << " [fillcolor=" << (tmp->is_red ? "red" : "black") << "]" << std::endl;
			if (tmp->child_left && tmp->child_right)
			{
				file2 << " " << tmp->lp[3] << tmp->lp[2] << tmp->lp[1] << tmp->lp[0] << " -> {" << tmp->child_left->lp[3] << tmp->child_left->lp[2] << tmp->child_left->lp[1] << tmp->child_left->lp[0] << "," << tmp->child_right->lp[3] << tmp->child_right->lp[2] << tmp->child_right->lp[1] << tmp->child_right->lp[0] << "};" << std::endl;
				
				fall_in_tree_file(tmp->child_left, file1, file2);
			
				fall_in_tree_file(tmp->child_right, file1, file2);
				
			}
			else if (tmp->child_left)
			{
				file2 << " " << tmp->lp[3] << tmp->lp[2] << tmp->lp[1] << tmp->lp[0] << " -> {" << tmp->child_left->lp[3] << tmp->child_left->lp[2] << tmp->child_left->lp[1] << tmp->child_left->lp[0] << "};" << std::endl;
				fall_in_tree_file(tmp->child_left, file1, file2);
			}
			else if (tmp->child_right)
			{
				file2 << " " << tmp->lp[3] << tmp->lp[2] << tmp->lp[1] << tmp->lp[0] << " -> {" << tmp->child_right->lp[3] << tmp->child_right->lp[2] << tmp->child_right->lp[1] << tmp->child_right->lp[0] << "};" << std::endl;
				fall_in_tree_file(tmp->child_right, file1, file2);
			}
			return;
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
			node<T>* scroll = tmp2->child_left;
			tmp2->child_left = tmp3->child_left;
			tmp3->child_left = tmp2;
			tmp2->child_left->parent = tmp2;
			tmp2->parent = tmp3;
			tmp2 = tmp2->child_left;
			tmp2->child_right = scroll;
			if (scroll) scroll->parent = tmp2;
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
			node<T>* scroll = tmp2->child_right;
			tmp2->child_right = tmp3->child_right;
			tmp3->child_right = tmp2;
			tmp2->child_right->parent = tmp2;
			tmp2->parent = tmp3;
			tmp2 = tmp2->child_right;
			tmp2->child_left = scroll;
			if (scroll) scroll->parent = tmp2;
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
	rb_tree() :root(NULL), size(0),lp_draws(0)
	{ 
		lp[0] = 'A'; lp[1] = 'A'; lp[2] = 'A'; lp[3] = 'A';
	};
	rb_tree(T val) :rb_tree()
	{
		add(val);
	}
	static int lp_rbtree;

	bool add(T val,bool (*fun)(const T,const T))
	{
		this->size++;
		if (this->root == NULL)
		{
			this->root = new node<T>(val, NULL,lp,false);
			this->increment_lp();
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
		}
		
		return true;
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

	void draw_graf()
	{
		std::fstream points, lines, file_out;
		std::string line = "", name_out;
		_mkdir("C:\\Users\\GSzwa\\source\\repos\\labo_algo_3\\labo_algo_3\\graph_out");
		name_out = "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\" -Tpng C:\\Users\\GSzwa\\source\\repos\\labo_algo_3\\labo_algo_3\\graph_out\\file.dot -o C:\\Users\\GSzwa\\source\\repos\\labo_algo_3\\labo_algo_3\\graph_out\\mojgraf_rbtree_" + std::to_string(lp_rbtree) + "_" + std::to_string(lp_draws) + ".png";
		points.open("graph_out\\points.txt", std::ios::out | std::ios::in | std::ios::trunc);
		lines.open("graph_out\\lines.txt", std::ios::out | std::ios::in | std::ios::trunc);
		file_out.open("graph_out\\file.dot", std::ios::out | std::ios::trunc);
		 
		node<int>* tmp = this->root;

		fall_in_tree_file(tmp,points,lines);

		file_out << "digraph D {" << std::endl;
		file_out << "	{" << std::endl;
		file_out << "	 node [shape = circle style = filled fontcolor=yellow]" << std::endl;
		
		points.seekg(0, std::ios::beg);
		while (getline(points, line)) {
			file_out << line << std::endl;
		}
		file_out << "	}" << std::endl;
		lines.seekg(0, std::ios::beg);
		while (getline(lines, line)) {
			file_out << line << std::endl;
		}
		points.close();
		lines.close();
		remove("graph_out\\points.txt");
		remove("graph_out\\lines.txt");
		file_out << "}" << std::endl;
		file_out.close();
		system(name_out.c_str());
		
		//remove("graph_out\\file.dot");
		lp_draws++;
	}

	bool erase_ptr(void)
	{
		if (!this->root) throw rb_tree_exceptions(2);
		fall_in_tree_delete_ptr(this->root);
		this->root = NULL;
		this->size = 0;
	}
};

