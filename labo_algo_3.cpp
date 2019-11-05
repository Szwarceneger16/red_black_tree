#include <iostream>
#include "rb_tree.h"
#include <time.h>
#include <random>


template<class T>
bool cmp1(const T a, const T b)
{
	return a == b ? true : false;
}

template<class T>
bool cmp2(const T a, const T b)
{
	return a < b ? true : false;
}

void printer(const int a,const bool b)
{
	std::cout.width(6);
	std::cout.setf(std::ios::left);
	std::cout << a << std::boolalpha << b << " || ";
}

template<class T>
int rb_tree<T>::lp_rbtree = 0;

int main()
{
	//int tab[] = {25,15,50,10,22,35,70,4,12,18,24,31,44,66,90};
	srand(NULL);

	rb_tree<int> moje;

	for (int i = 0; i < 10000000; i++)
	{
		moje.add(rand()%10000,cmp2<int>);
		//if(i % 10 == 0) moje.draw_graf();
	}

	moje.pre_order_traverse(printer,2);
	std::cout << moje.get_height();
	//moje.draw_graf();
	/*try {
		std::cout << moje.find_value(52,cmp1<int>) << std::endl;
	}
	catch (rb_tree_exceptions & ee) {
		std::cout<<ee.get_info();
	}*/

	//const int MAX_ORDER = 7;
	//rb_tree<int> rbt;
	//clock_t t1, t2;

	//for (int o = 0; o <= MAX_ORDER; o++)
	//{
	//	const int n = pow(10, o);
	//	srand(NULL);

	//	t1 = clock();
	//	for (int i = 0; i < n; i++)
	//	{
	//		int a = rand() % 100000;
	//		rbt.add(a,cmp2);
	//	}
	//	t2 = clock();

	//	rbt.pre_order_traverse(printer, 2);
	//	std::cout << std::endl << "Wysokosc: " << rbt.get_height() << "  Czas dodawania: " << (double(t2) - double(t1)) / CLOCKS_PER_SEC << std::endl;

	//	const int m = pow(10, 4); // liczba prob wyszukiwania
	//	int hits = 0; // liczba trafien
	//	t1 = clock();
	//	for (int i = 0; i < m; i++)
	//	{
	//		int a = rand() % 100000;
	//		try {
	//			rbt.find_value(a, cmp1<int>);
	//			hits++;
	//		}
	//		catch (rb_tree_exceptions & ee) {
	//		}
	//	}
	//	t2 = clock();
	//	std::cout  << "Liczba trafien: " <<hits << "  Czas wyszukiwania: " << (double(t2) - double(t1)) / CLOCKS_PER_SEC << std::endl;
	//	rbt.erase();
	//	std::cout << "----------------------------------------------------------" << std::endl;
	//}
	
}
