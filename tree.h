#pragma once
#include <iostream>
#include <string>
using namespace std;
#define NO_OF_ALPHABETS 26
#define MAX_WORD_SIZE 100


struct TrieNode
{
    TrieNode* child[NO_OF_ALPHABETS];
    bool isEndOfWord;

    //constructor
    TrieNode() :isEndOfWord(false) {
        for (int i = 0; i < NO_OF_ALPHABETS; i++)
            child[i] = NULL;
    }
};

void insert(TrieNode* root, string word)
{
    //inserting words to tree
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (root->child[word[i] - 'a'] == NULL)
        {
            root->child[word[i] - 'a'] = new TrieNode;
        }
        root = root->child[word[i] - 'a'];
    }
    root->isEndOfWord = true;
}


void getWord(string str, int n,char c,vector<string>& s)
{
    string temp;
    if (str[0] == c)
    {
        for (int i = 0; i < n; i++)
        {
            temp += str[i];
        }
        s.push_back(temp);
    }
}


void getAllWords(TrieNode* root, char* wordArray, int pos,char c, vector<string>& s)
{
    //traversing tree to get words
    if (root == NULL)
        return;
    if (root->isEndOfWord)
    {
        getWord(wordArray, pos,c,s);
    }
    for (int i = 0; i < NO_OF_ALPHABETS; i++)
    {
        if (root->child[i] != NULL)
        {
            wordArray[pos] = i + 'a';
            getAllWords(root->child[i], wordArray, pos + 1,c,s);
        }
    }
}

