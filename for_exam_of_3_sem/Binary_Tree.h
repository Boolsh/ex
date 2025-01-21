#pragma once

#include <iostream>
#include <fstream>

class A
{
private:
	int a, b;
public:
	A() { a = 0, b = 0; }
	A(int a, int b) { this->a = a, this->b = b; }
	~A() {};
	void print() { std::cout << a << ',' << b << "\n"; };
	int geta() { return a; }
	int getb() { return b; }
};


namespace btree
{

	using TInfo = int;

	struct NODE
	{
		TInfo info;
		NODE* left = nullptr, * right = nullptr;
		NODE(TInfo info) :info(info) {}
		~NODE()
		{
			left = right = nullptr;
		}
	};

	using ptrNODE = NODE*;

	struct BTREE
	{
	private:
		ptrNODE root;
	public:
		BTREE() { root = nullptr; }
		BTREE(const char* file_name);
		bool empty();
		TInfo get_info(ptrNODE ptr)
		{
			return ptr->info;
		}
		ptrNODE get_root() const
		{
			return root;
		}
		void set_root(ptrNODE ptr)
		{
			root = ptr;
		}
		~BTREE();
		void print(std::ostream& stream = std::cout);
		void clear(ptrNODE& ptr);
	};

}