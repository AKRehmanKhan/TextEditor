#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "linklist.h"

# include "myconsole.h"
# include "editor.h"

using namespace std;


//-------------------------------Color Codes------------------------------//
// Color Codes Hexadecimal values for both Fore Ground and Back Ground //ForeGround|BackGround
int B_BLACK = 0x00;	int B_Royal_Blue = 0x10;	int B_Dark_Green = 0x20;
int B_Tale_Blue = 0x30;	int B_Dark_Red = 0x40;	int B_Purple = 0x50;
int B_Tale_Green = 0x60;	int B_Light_Grey = 0x70; int B_Dark_Gray = 0x80;
int B_Light_Blue = 0x90; int B_Light_Green = 0xA0;	int B_Sky_Blue = 0xB0;
int B_Red = 0xC0;	int B_Pink = 0xD0;	int B_Yellow = 0xE0;
int B_White = 0xF0;

int F_BLACK = 0x00;	int F_Royal_Blue = 0x01; int F_Dark_Green = 0x02;
int F_Tale_Blue = 0x03;	int F_Dark_Red = 0x04;	int F_Purple = 0x05;
int F_Tale_Green = 0x06;	int F_Light_Grey = 0x07; int F_Dark_Gray = 0x08;
int F_Light_Blue = 0x09; int F_Light_Green = 0x0A;	int F_Sky_Blue = 0x0B;
int F_Red = 0x0C;	int F_Pink = 0x0D;	int F_Yellow = 0x0E;
int F_White = 0x0F;

//-------------------------------POINT CLASS------------------------------//
//initialize MaxPoint
point point::MaxPoint(MAX_X, MAX_Y);
bool point::incrementX()
{
	bool returnValue = true;
	if (x < MaxPoint.x)
	{
		x++;

	}
	else if (y < MaxPoint.y)
	{
		x = 0;
		y = y + 1;
	}
	else
		returnValue = false;

	return returnValue;
}

bool point::incrementY()
{
	bool returnValue = true;
	if (y < MaxPoint.y)
		y++;
	else
		returnValue = false;

	return returnValue;

}
bool point::decrementX()
{
	bool returnValue = true;
	if (x > 0)
		x--;
	else if (y > 0)
	{
		y--;
		x = MaxPoint.x;
	}
	else
		returnValue = false;

	return returnValue;
}
bool point::decrementY()
{
	bool returnValue = true;
	if (y > 0)
		y--;
	else
		returnValue = false;

	return returnValue;

}

//-------------------------------END OF POINT CLASS------------------------------------------------//


//--------------------------The function Where you will write code--------------------------------//
int mainEditor()
{
	int key = 0;
	int y_used = 1;
	int xaxix = 0; int x_axix = 0; int y_axix = 0; int i = 0; int dum = 0; int itr_pos = 0; int spc = 0;
	bool stop = false;
	point currentPosition(0, 0);
	currentPosition.setMaxPoint(MAX_X, MAX_Y);
	bool specialKey = false;
	int* x_size = new int[MAX_X];
	Linklist<char>* l = new Linklist<char>;
	l->Insert_at_Head((char)(key));
	Linklist<char> ::Iterator itr = l->begin();
	itr--;
	point temp(0, 0);
	point temp1(0, 0);
	while (!stop)
	{
		key = CheckWhichKeyPressed(specialKey);
		if (key == ESCKEY)
		{
			stop = true;
		}
		else if (!specialKey && key >= 32 && key <= 126)
		{
			temp1.setX(x_size[itr_pos]);
			if (currentPosition.getX() < MAX_X)
			{


				if ((itr_pos == i) && (currentPosition.getX() == x_size[i] || currentPosition.getX() == 0))
				{
					cout << (char)key;
					l->Insert(itr, (char)key);
					itr++;

					y_axix = currentPosition.getY() - 1;
					//You can change color of text by calling this function
					SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_Red | B_Light_Green);   //ForeGround|BackGround
					currentPosition.incrementX();
					x_axix = currentPosition.getX();

					x_size[i] = currentPosition.getX();
				}
				else
				{


					if (temp1.getX() < MAX_X - 1)
					{
						l->Insert(itr, (char)key);
						itr++;
						ClearScreen();
						PlaceCursor(0, 0);
						temp.set(0, 0);

						for (Linklist<char> ::Iterator pos = l->begin(); pos != l->end(); pos++)
						{

							cout << *pos;
							SetColorAtPoint(temp.getX(), temp.getY(), F_Red | B_Light_Green);

							temp.incrementX();

							if (*pos == '\n')
							{
								temp.setX(0);
								temp.incrementY();
							}


						}

						currentPosition.incrementX();
						x_size[itr_pos] = x_size[itr_pos] + 1;
						
					}
				}
			}
			else if (currentPosition.getY() < MAX_Y)
			{
				l->Insert(itr, '\n');
				itr++;

				cout << ('\n');
				y_used += 1;
				x_size[i] = currentPosition.getX();
				i += 1;
				currentPosition.incrementY();
				currentPosition.setX(0);
				itr_pos += 1;
				y_used += 1;
			}
		}
		else if (specialKey && key == LEFTKEY)
		{
			if (itr.current != l->head)
			{
				if (itr.current->data == '\n')
				{
					if (currentPosition.getY() != 0)
					{
						itr--;
						itr_pos -= 1;
						currentPosition.setX(x_size[itr_pos]);
						currentPosition.decrementY();
					}
				}
				else
				{
					currentPosition.decrementX();
					itr--;
				}

			}
		}
		else if (specialKey && key == RIGHTKEY)
		{
			if ((itr.current->next->next != nullptr))
			{
				if (itr.current->next->data == '\n')
				{
					itr++;
					currentPosition.setX(0);
					currentPosition.incrementY();
					itr_pos += 1;
				}
				else
				{
					currentPosition.incrementX();
					itr++;
				}
			}
		}
		else if (specialKey && key == UPKEY)
		{
			if (currentPosition.getY() != 0)
			{
				currentPosition.decrementY();
				if (x_size[itr_pos - 1] > currentPosition.getX())
				{
					int s = x_size[itr_pos - 1];
					while (s != 0)
					{
						itr--;
						s--;
					}
					itr--;
					currentPosition.setX(currentPosition.getX());
				}
				else
				{
					currentPosition.setX(x_size[itr_pos - 1]);
					while (itr.current->data != '\n')
					{
						itr--;
					}
					itr--;
				}

				itr_pos -= 1;
			}
		}
		else if (specialKey && key == DOWNKEY)
		{	//Update it so that cursur not move downword if it is at last line of text.
			if (currentPosition.getY() < y_used - 1)
			{
				currentPosition.incrementY();
				if (currentPosition.getX() < x_size[itr_pos + 1])
				{
					currentPosition.setX(currentPosition.getX());
					int s = x_size[itr_pos];
					while (s != 0)
					{
						itr++;
						s--;
					}
					itr++;

				}
				else
				{

					int s = (x_size[itr_pos] - currentPosition.getX()) + x_size[itr_pos + 1];
					currentPosition.setX(x_size[itr_pos + 1]);
					while (s != 0)
					{
						itr++;
						s--;
					}
					itr++;

				}
				itr_pos += 1;
			}
		}
		else if (key == ENTERKEY)
		{
			if (itr.current->next->next != nullptr)
			{
				l->Insert(itr, '\n');
				itr++;
				Linklist<char>::Iterator t = itr;
				y_used += 1;
				int s = x_size[itr_pos] - currentPosition.getX();
				x_size[itr_pos] = currentPosition.getX();

				for (int i = y_used; i > itr_pos; i--)
				{
					x_size[i] = x_size[i - 1];
				}
				itr_pos += 1;
				i += 1;
				x_size[itr_pos] = s;

				currentPosition.setX(0);
				currentPosition.incrementY();
				ClearScreen();
				PlaceCursor(0, 0);
				point temp1(0, 0);
				for (Linklist<char>::Iterator pos = l->begin(); pos != l->end(); pos++)
				{
					cout << *pos;
					if (*pos == '\n')
					{
						SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);
						temp1.incrementY();
						temp1.setX(0);
					}
					else
					{
						SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);
						temp1.incrementX();
					}

				}
			}
			else
			{
				l->Insert(itr, '\n');
				itr++;

				cout << ('\n');
				y_used += 1;
				x_size[i] = currentPosition.getX();
				i += 1;
				// dum = i - 1;
				itr_pos = i;
				currentPosition.setX(0);
				currentPosition.incrementY();
			}
		}
		else if (key == DELKEY)
		{
			//call a function to handle 
			if (itr.current != l->head)
			{
				if ((itr.current->next->next != nullptr) && (l->begin() != nullptr))
				{
					

					if (itr.current->next->data == '\n')
					{
			
						x_size[itr_pos] = x_size[itr_pos] + x_size[itr_pos + 1];
						for (int i = itr_pos + 1; i <= y_used; i++)
						{
							x_size[i] = x_size[i + 1];
						}
						y_used -= 1;

					}

					Linklist<char> ::Iterator temp = itr;
					temp++;
					l->Delete(temp);

					ClearScreen();
					PlaceCursor(0, 0);
					point temp1(0, 0);
					
					for (Linklist<char> ::Iterator pos = l->begin(); pos != l->end(); pos++)
					{
						char k = *pos;
						if (k == '\n')
						{
							cout << ('\n');
							temp1.setX(0);
							temp1.incrementY();
							SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);


						}
						else
						{

							if (temp1.getX() < MAX_X)
							{
								cout << k;

								//You can change color of text by calling this function

								SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);   //ForeGround|BackGround
								temp1.incrementX();

							}
							else if (temp1.getY() < MAX_Y)
							{
								cout << ('\n');
								temp1.incrementY();
								temp1.setX(0);
								SetColorAtPoint(temp1.getX(), temp1.getY(), F_White | B_Light_Green);

							}
						}

					}
				}


			}
		}
		else if (key == BACKSPACE)
		{
			if (itr.current != l->head)
			{
				if ((itr.current->next->next == nullptr) && (l->begin() != nullptr))
				{
					Linklist<char> ::Iterator temp = itr;
					itr--;

					
					
					l->Delete(temp);


					ClearScreen();
					PlaceCursor(0, 0);
					temp1.set(0, 0);


					for (Linklist<char> ::Iterator pos = l->begin(); pos != l->end(); pos++)
					{
						char k = *pos;
						if (k == '\n')
						{

							cout << ('\n');

							temp1.setX(0);
							temp1.incrementY();
							SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);


						}
						else
						{

							if (temp1.getX() < MAX_X)
							{
								cout << k;

								//You can change color of text by calling this function

								SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);   //ForeGround|BackGround
								temp1.incrementX();

							}
							else if (temp1.getY() < MAX_Y)
							{
								cout << ('\n');
								temp1.incrementY();
								temp1.setX(0);
								SetColorAtPoint(temp1.getX(), temp1.getY(), F_White | B_Light_Green);

							}
						}

					}
					currentPosition.decrementX();
				}
				else
				{
					Linklist<char> ::Iterator temp = itr;
					itr--;
					if (l->head->next != nullptr)
					{
						if (temp.current->data == '\n')
						{
							itr_pos -= 1;
							currentPosition.setX(x_size[itr_pos] + 1);

							x_size[itr_pos] = x_size[itr_pos] + x_size[itr_pos+1];

							for (int i = itr_pos+1; i <= y_used; i++)
							{
								x_size[i] = x_size[i + 1];
							}
							
							y_used -= 1;

							currentPosition.decrementY();

						}
						else
						{
							x_size[itr_pos] = x_size[itr_pos] - 1;
						}


						l->Delete(temp);


						ClearScreen();
						PlaceCursor(0, 0);
						currentPosition.decrementX();
						point temp1(0, 0);

						if (l->head->next != nullptr)
						{


							for (Linklist<char> ::Iterator pos = l->begin(); pos != l->end(); pos++)
							{
								char k = *pos;
								if (k == '\n')
								{

									cout << ('\n');

									SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);
									temp1.incrementY();
									temp1.setX(0);
								}
								else
								{

									if (currentPosition.getX() < MAX_X)
									{
										cout << k;


										//You can change color of text by calling this function
										SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);   //ForeGround|BackGround
										temp1.incrementX();

									}
									else if (currentPosition.getY() < MAX_Y)
									{
										cout << ('\n');

										SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_Red | B_Light_Green);
										temp1.incrementY();
										temp1.setX(0);
									}
								}

							}
						}
					}
				}
			}
		}
		else if (key == F1KEY || key == F2KEY || key == F3KEY)
		{

			point f(currentPosition.getX(), currentPosition.getY());
			PlaceCursor(0, MAX_Y - 2);
			for (int i = 0; i < MAX_X; i++)
			{
				cout << '\0';
				currentPosition.incrementX();
			}


			cout << "Enter Search Text: " << endl;
			currentPosition.setX(strlen("Enter Search Text : "));
			currentPosition.setY(MAX_Y - 2);
			PlaceCursor(strlen("Enter Search Text : "), MAX_Y - 2);

			if (key == F1KEY) {
				//Search for one instance of string and move cursor there
				Linklist<char> ::Iterator it;
				bool stopp = false;
				while (!stopp)
				{
					key = CheckWhichKeyPressed(specialKey);


					if (key >= 32 && key <= 126)
					{
						it = l->Search_First((char)key);
						cout << (char)key;

						point temp1(0, 0);
						for (Linklist<char> ::Iterator pos = l->begin(); pos != l->end(); pos++)
						{
							char k = *pos;

							if (k == '\n')
							{
								temp1.incrementY();
								temp1.setX(0);
							}
							else
							{

								if (currentPosition.getX() < MAX_X)
								{

									
									if (it.current == pos.current)
									{
										SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Yellow);								

									}
									temp1.incrementX();

								}
								else if (currentPosition.getY() < MAX_Y)
								{

									temp1.incrementY();
									temp1.setX(0);
								}
							}

						}



					}

					else if (key == ESCKEY)
					{
						stopp = true;
						ClearScreen();
						PlaceCursor(0,0);
						temp1.set(0,0);
						for (Linklist<char> ::Iterator pos = l->begin(); pos != l->end(); pos++)
						{
							char k = *pos;
							if (k == '\n')
							{

								cout << ('\n');

								SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);
								temp1.incrementY();
								temp1.setX(0);
							}
							else
							{

								if (temp1.getX() < MAX_X)
								{
									cout << *pos;


									//You can change color of text by calling this function
									SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);   //ForeGround|BackGround
									temp1.incrementX();

								}
								else if (temp1.getY() < MAX_Y)
								{
									cout << ('\n');

									SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);
									temp1.incrementY();
									temp1.setX(0);
								}
							}

						}
						
						
						PlaceCursor(f.getX() , f.getY());
						currentPosition.set(f.getX(), f.getY());
						break;
					}
				}
			}
			else if (key == F2KEY)
			{
				//Search for all instances of string and Highlight them


				Linklist<char> ::Iterator* it;
				bool stopp = false;
				while (!stopp)
				{
					key = CheckWhichKeyPressed(specialKey);


					if (key >= 32 && key <= 126)
					{
						it = l->Search_All((char)key);
						cout << (char)key;

						point temp1(0, 0);
						for (Linklist<char> ::Iterator pos = l->begin(); pos != l->end(); pos++)
						{
							char k = *pos;

							if (k == '\n')
							{
								temp1.incrementY();
								temp1.setX(0);
							}
							else
							{

								if (currentPosition.getX() < MAX_X)
								{

									//You can change color of text by calling this function
									if (it->current == pos.current)
									{
										SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Yellow);
										it++;
									}
									temp1.incrementX();

								}
								else if (currentPosition.getY() < MAX_Y)
								{

									temp1.incrementY();
									temp1.setX(0);
								}
							}

						}



					}

					else if (key == ESCKEY)
					{
						stopp = true;
						ClearScreen();
						PlaceCursor(0, 0);
						temp1.set(0, 0);
						for (Linklist<char> ::Iterator pos = l->begin(); pos != l->end(); pos++)
						{
							char k = *pos;
							if (k == '\n')
							{

								cout << ('\n');

								SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);
								temp1.incrementY();
								temp1.setX(0);
							}
							else
							{

								if (currentPosition.getX() < MAX_X)
								{
									cout << *pos;


									//You can change color of text by calling this function
									SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);   //ForeGround|BackGround
									temp1.incrementX();

								}
								else if (currentPosition.getY() < MAX_Y)
								{
									cout << ('\n');

									SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_Red | B_Light_Green);
									temp1.incrementY();
									temp1.setX(0);
								}
							}

						}
						PlaceCursor(f.getX(), f.getY());
						currentPosition.set(f.getX(), f.getY());
						break;
					}

				}



			}
			else
			{
				//Search for all instances of string 
				//Take a second input string 
				//and replace all instances of first string with second string
				Linklist<char> ::Iterator* it;
				point h(currentPosition.getX(), currentPosition.getY());
				PlaceCursor(50, MAX_Y - 2);
				cout << "Enter Replace Text: " << endl;
				currentPosition.setX(50 + strlen("Enter Replace Text : "));
				point t(50 + strlen("Enter Replace Text : "), MAX_Y - 2);
				currentPosition.setY(MAX_Y - 2);
				PlaceCursor(h.getX(), MAX_Y - 2);
				char* arr1 = new char[20];
				char* arr2 = new char[20];
				int i = 0, j = 0;
				bool stopp = false;
				while (!stopp)
				{
					key = CheckWhichKeyPressed(specialKey);


					if (!specialKey && key >= 32 && key <= 126)
					{
						arr1[i] = key;
						cout << (char)key;
						i += 1;
						currentPosition.incrementX();

					}
					else if (specialKey && key == RIGHTKEY)
					{
						arr1[i+1] = '\0';
						PlaceCursor(t.getX(), t.getY());
						currentPosition.set(t.getX(), t.getY());
						while (key != ENTERKEY)
						{
							key = CheckWhichKeyPressed(specialKey);
							if (key >= 32 && key <= 126)
							{
								cout << (char)key;
								arr2[j] = key;
								j += 1;
								currentPosition.incrementX();

							}
						}
						arr2[j + 1] = '\0';

					}
					else if (key == ENTERKEY)
					{
						int s = 0;
						int *t=nullptr;
						l->Replace_All(arr1, arr2, s,t);

						int s1 = 0, s2 = 0;
						for (; arr1[s1] != '\0'; s1++)
						{
						}
						for (; arr2[s2] != '\0'; s2++)
						{
						}
						s1 -= 1;
						s2 -= 1;
						
						if (s1 < s2)
						{
							int l = 0;
							while (l<s)
							{
								x_size[t[l]] = x_size[t[l]] + (s2 - s1);
								l++;
							}
							
						}
						else if (s2 < s1)
						{
							int l = 0;
							while (l < s)
							{
							 x_size[t[l]] = x_size[t[l]] - (s1 - s2);
							 l++;
							}
						}
						while (s != 0)
						{
							stopp = true;
							if (s1 < s2)
							{
								int y = 0;
								while ((s2 - s1) != y)
								{
									f.incrementX();
									y++;
								}
							}
							if (s1 > s2)
							{
								int z = 0;
								while ((s1 - s2) != z)
								{
									f.decrementX();
									z++;
								}
							}
							s--;
						}
						ClearScreen();
						PlaceCursor(0, 0);
						point temp1(0, 0);
						itr = l->begin();
						if (l->head->next != nullptr)
						{


							for (Linklist<char> ::Iterator pos = l->begin(); pos != l->end(); pos++)
							{
								char k = *pos;
								if (k == '\n')
								{

									cout << ('\n');
									if (itr.current->next->next != nullptr)
										itr++;
									SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);
									temp1.incrementY();
									temp1.setX(0);
								}
								else
								{

									if (temp1.getX() < MAX_X)
									{
										cout << k;
										if (itr.current->next->next != nullptr)
											itr++;

										//You can change color of text by calling this function
										SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);   //ForeGround|BackGround
										temp1.incrementX();

									}
									else if (temp1.getY() < MAX_Y)
									{
										cout << ('\n');
										if (itr.current->next->next != nullptr)
											itr++;
										SetColorAtPoint(temp1.getX(), temp1.getY(), F_Red | B_Light_Green);
										temp1.incrementY();
										temp1.setX(0);
									}
								}

							}
						}

						PlaceCursor(temp1.getX(), temp1.getY());
						temp.set(temp1.getX(), temp1.getY());
						currentPosition.set(temp1.getX(), temp1.getY());
						break;
					}

				}

			}

		}
		else if (key == F4KEY)
		{
			ofstream fout("save.txt");
			for (Linklist<char> ::Iterator pos = l->begin(); pos != l->end(); pos++)
			{
				fout << *pos;
			}
			fout.close();

		}
	PlaceCursor(currentPosition.getX(), currentPosition.getY());

	}

	delete l;
	return 0;
}

//-------------------------------------------End Main Editor--------------------------//
void main()
{
	mainEditor();
}
