#include<iostream>
#include<string>
#include<vector>
#include<conio.h>
#include<windows.h>
#include"huffman.h"

using namespace std;

class TextEditor {

private:
	string text;
	POINT currentPos;


	void set_cursor(int x = 0, int y = 0)
	{
		HANDLE handle;
		COORD coordinates;
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
		coordinates.X = x;
		coordinates.Y = y;
		SetConsoleCursorPosition(handle, coordinates);
	}
	void displaySuggestions(vector<string> suggestedWords) 
	{

		//creating above line of suggestion box
		set_cursor(0, 29);
		int j = 0;
		while (j < 61) {
			cout << "*"; j++;
		}
		cout << "(Suggestions)";
		j = 0;
		while (j < 61) {
			cout << "*"; j++;
		}
		//////////////////////////////////////
		cout <<endl<<"*	";

		//printing suggestion////
		for (int i = 0; i < suggestedWords.size(); i++)
		{
			cout << suggestedWords[i]<<"    ";
			//check for displaying next five suggestions in second line
			if (i == 4)cout << endl<<"*	";

		}
		////////////////////////
		cout <<endl<< "*";

		//printing bottom line of suggestion box////
		int k = 0;
		while (k < 134) {
			cout << "*"; k++;
		}
		//////////////////////////////////////////
		cout << endl;

		//currently cursor is at bottom of page after printing bootom line of sterics of suggestion box i.e current_cursor_position(0,34)
		//so setting cursor to first character of first suggested word by moving cursor up and right i.e(8,30)
		currentPos.x = 8;
		currentPos.y = 30;
		set_cursor(currentPos.x, currentPos.y);
		
	}


	string selectSuggestedWord(vector<string> suggestedWords) {
		
		int i = 0;
		char c = _getch();
		// while use is pressing '/' moving cursor and selected index forward
		while (c != ';') {
			if (c>=27)
				return "moreword";
			else if(c!='/')  //if first word is not slected by slash so dive in to second loop to select word
		     c = _getch();
			while (c == '/') {
				if (i == 4) {
					//when first five words are forwarded then moving cursor to next line i.e y: 30->31 and x to first character of 6th  word i.e x=8
					currentPos.x = 8;
					currentPos.y = 31;
					set_cursor(currentPos.x, currentPos.y);
				}
				else if (i == 9) {
					//when 10 words are forwarded then moving cursor to above line i.e y: 31->30 and x to first character of 1st  word i.e x=8
					currentPos.x = 8;
					currentPos.y = 30;
					set_cursor(currentPos.x, currentPos.y);
				}
				else {
					//moving  x coordinate of cursor forward from one word to other word by adding size of previous word plus 4(skipping 4 spaces between words)
					currentPos.x = currentPos.x + suggestedWords[i].size() + 4;
					set_cursor(currentPos.x, currentPos.y);
				}
		     	
				// moving selected index i.e(i) forward in array
				i = (i+1) % suggestedWords.size();
				
				c = _getch();
				if (c == ';')
					break;
			}
		}

		return suggestedWords[i];
	}
	
public:

	TextEditor( string inputFile)//constructor
	{
		ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);//maximizing console
		huffman h(inputFile);
		this->text=h.decode(); //decoding previously saved data

	}
	
	void displayText() {
		cout << this->text; //displaying text string
	}


	void addSuggestedWord(char c, vector<string>& s)
	{
		string currentword;
		currentword += c;
		vector<string> suggestedWords;

			string word = "moreword";
			while (word.compare("moreword") == 0)
			{
				suggestedWords.clear();
				int k = 0;
				for (; k < s.size(); k++)
				{
					string temp;
					for (int j = 0; j < currentword.size(); j++)
					{
						if (j < s[k].size()) {
							temp += s[k][j];
						}
					}
					if (currentword.compare(temp) == 0)
						break;
				}

				int  count = 0;
				while (count < 10 && k < s.size())
				{
					suggestedWords.push_back(s[k]);
					k++;
					count++;
				}

				this->displaySuggestions(suggestedWords);
				word = this->selectSuggestedWord(suggestedWords);
				if (word.compare("moreword") != 0)//if word is selected from suggestions then adding it to text string and returning
				{
					this->text += word;   //placing selected word in to word string
					system("cls");   //clearing screen
					set_cursor(0, 0); //set cursor to 00
					this->displayText(); //displaying previous word
					
				}
				
				// if user have not selected from current suggestions then taking next character of word to show next suggestions
				else {
					system("cls"); //clearing screen
					set_cursor(0, 0);//placing cursor to 00
					this->displayText();//printing previous text
					cout << currentword;
					c = _getch(); //get next character of currently typing word

					cout << c;
					currentword += c; 
				}
			}

	}



	void compressAndSave(string path) {
		huffman h(path);
		h.encode(text); //encoding and saving to file
	}

	void addSuggestedWord(char c)
	{

			if (c == '\r')   // check for newline (new line is read as '\r' by getch() so manually printing it and inserting orignal '\n' character to text string)
			{
				cout << endl;
				this->text += '\n';
			}
			else if (c >= ' ' && c <= '@' || c >= '[' && c <= '`' || c >= '{' && c <= '~')
				this->text += c;
		

	}

	vector<string> read_word_by_word(string filename)
	{
		vector<string> data;
		fstream file;
		string word;
		int i = 0;
		file.open(filename.c_str());
		while (!file.eof()) {
			file >> word;
			data.push_back(word);
			//cout << data[i] << endl;
			i++;
		}
		file.close();
		return data;

	}

};
