#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <string>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

struct node
{
	char id;																				
	int freq;																				
	string code;																			
	node* left;
	node* right;
	node()
	{
		left = right = NULL;
	}
};
typedef node* node_ptr;

class huffman
{
protected:
	//protected data members
	char id;
	node_ptr node_array[128];																
	node_ptr child, parent, root;
	fstream in_file, out_file;
	string in_file_name, out_file_name;
	class compare
	{
	public:
		bool operator()(const node_ptr& c1, const node_ptr& c2) const
		{
			return c1->freq > c2->freq;
		}
	};
	priority_queue<node_ptr, vector<node_ptr>, compare> pq;

	//protected functions
	string decimal_to_binary(int);
	int binary_to_decimal(string&);															 
	void create_node_array();
	inline void build_tree(string&, char);	
	void traverse(node_ptr, string);
	void recreate_huffman_tree();
	string decoding();
	void create_pq(string text);
	void create_huffman_tree();
	void calculate_huffman_codes();
	void coding_save(string in_text);

public:
	//public functions
	huffman(string);
	void encode(string text);
	string decode();


};

#endif
