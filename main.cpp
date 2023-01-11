#include <iostream>
#include "huffman.h"
#include "texteditor.cpp"
#include "tree.h"
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<vector>
using namespace std;

int main()
{
    //*screen maximize function is in constructor of text editor*
    string path = "D:/courses/Projects/Editor/output.txt"; //path of output file where text will be saved
    TextEditor t(path);//creating textEdiitor//contructor
    t.displayText(); // displaying previously saved text after decoding it in TextEditor's cunstructor
    vector<string> for_insert; 
    //reading dictionary, file handling and storing dictionary in "for_insert" vector
    for_insert = t.read_word_by_word("D:/courses/Projects/Editor/dictionary.txt");

    TrieNode* root = new TrieNode;//creating tree //cunstructor call
    //Moving dictionary word form "for_insert" vector to tree
    for (int i = 0; i < for_insert.size(); i++)
        insert(root, for_insert[i]);



    while (1)
    {
        char c = _getch(); //taking character input without pressing enter
        if (c == '\b') {//do nothing on pressing backspace to remove bactward editing functionality
        }
        else if (c == '=')
        {
            t.compressAndSave(path); //encoding and saving text
            break;//exiting
        }
        else if (c == 27)//esc button to retun without saving
            return 0;

        if (c >= ' ' && c <= '@' || c >= '[' && c <= '`' || c >= '{' && c <= '~' || c >= 'a' && c <= 'z' || c=='\r')
        {
            //if input character is in range 'a' to 'z' then show suggestions else simply add to text
            if (c >= 'a' && c <= 'z')
            {
                vector<string> suggestion;
                char wordArray[1000];
                getAllWords(root, wordArray, 0, c, suggestion); //getting all Suggestions of input charcter from tree in to "suggestion" vector
          
                cout << c;
                t.addSuggestedWord(c, suggestion); //1. displaying suggestions,2. selecting one of the suggested word and 3. adding to text
            }
            else {
                cout << c;
                t.addSuggestedWord(c); //simply adding special characters to text string
            }
        }
    
    }
    return 0;
}