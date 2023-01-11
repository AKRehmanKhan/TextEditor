#include<iostream>
#include<cstring>
using namespace std;

template <typename T>
class Linklist
{
public:

	Linklist()
	{
		head = new Node<T>;
		tail = new Node<T>;
	}
	~Linklist() {
		while (head->next != nullptr) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
		}
		delete head;
	}

	template <typename T>
	class Node
	{

	public:
		T data;
		Node<T>* next;
		Node<T>* prev;
		Node()
		{
			data = '\0';
			next = prev = nullptr;
		}

		Node(T v)
		{
			data = v;
			next = prev = nullptr;
		}

	};
 
	class Iterator
	{
	public:
		friend class Linklist;

		Node<T>* current;


		Iterator(Node<T>* newptr) : current(newptr) {}
		Iterator() : current(nullptr) {}

		bool operator!=(const Iterator& itr) const
		{
			return (current != itr.current);
		}
		bool operator==(const Iterator& itr) const
		{
			return !(current != itr.current);
		}

		T& operator *() const
		{
			return current->data;
		}

		//overloading post increment
		Iterator operator ++(int)
		{
			Iterator temp = *this;
			current = current->next;
			return temp;
		}

		//overloading pre increment
		Iterator operator ++ ()
		{
			current = current->next;
			return *this;

		}

		//overloading post decrement
		Iterator operator --(int)
		{
			Iterator temp = *this;
			current = current->prev;
			return temp;
		}

		//overloading pre decrement
		Iterator operator -- ()
		{
			current = current->prev;
			return *this;

		}


	};
	Iterator begin() const
	{
		return Iterator(head->next);
	}
	Iterator end()const
	{
		return Iterator(nullptr);
	}
	Iterator End()const
	{
		return Iterator(tail->prev);
	}

	Iterator Search_First(T v)
	{
		if (head->next != nullptr)
		{
			Iterator pos = this->begin();
			if (this->begin() != nullptr)
			{
				while (pos.current->next != nullptr && pos.current->data != v)
				{
					pos++;
				}
				if (pos.current->data == v)
				{
					return pos;
				}
				else return nullptr;
			}
		}
		return nullptr;

	}
	Iterator* Search_All(char* v, int size, int & s,  int* &t)
	{
		
		if (head->next != nullptr)
		{

			Iterator pos = this->begin();
			Iterator* temp;
			Iterator temp1= this->begin();
			while (temp1.current->next !=  nullptr)
			{
				temp1++;
			}


			Iterator e = temp1;
			int sa = size;
			while (sa > 0)
			{
				e--;
				sa--;
			}
			e++;
			bool found = false; int si = size, k = 0; int i = 0;
			for (Iterator p = this->begin(); p != e && p.current->next!=nullptr; )
			{
				found = false;
				si = size;
				if (*p == v[i])
				{
					Iterator pi = p;
					int j = i;
					pi++; j += 1;
					si -= 1;
					found = true;
					while (si > 0)
					{

						if (*pi == v[j])
						{
							found = true;
						}
						else
						{
							found = false;
							break;
						}

						pi++;
						j += 1;
						si -= 1;
					}

					if (found == true)
					{
						k++;
						int k = 0;
						while (k < size)
						{
							p++;
							k++;
						}
					}
					else
					p++;
					

				}
				else
					p++;
			}

		    t = new int [k];
			int n = 0,m=0;

			s = k;
			temp = new Iterator[k];
			int l = 0;
			i = 0;
			found = false;  si = size;
			for (Iterator p = this->begin(); p != e; p++)
			{
				
				found = false;
				si = size;
				if (*p == v[i])
				{
					Iterator pi = p;
					int j = i;
					pi++; j += 1; si -= 1;
					found = true;
					while (si > 0)
					{
						if (*pi == v[j])
						{
							found = true;
						}
						else
						{
							found = false;
							break;
						}
						pi++;
						j += 1;
						si -= 1;
					}

					if (found == true)
					{
						temp[l] = p.current;
						l++;

							t[n] = m ;
							n += 1;
						

					}
				}
				if (*p == '\n')
				{
					m += 1;
				}
			}


			return temp;
		}
	}
	Iterator* Search_All(T v)
	{
		if (head->next != nullptr)
		{
			Iterator pos = this->begin();
			Iterator* temp;

			int i = 0;

			while (pos.current != nullptr)
			{
				if (pos.current->data == v)
				{
					i++;
				}
				pos++;
			}

			pos = this->begin();
			temp = new Iterator[i];
			int j = 0;
			while (pos.current != nullptr)
			{
				if (pos.current->data == v)
				{
					temp[j] = pos.current;
					j++;
				}
				pos++;
			}


			return temp;
		}
	}

	void Insert_at_Head(T ele)
	{
		Node<T>* n = new Node<T>(ele);
		if (head->next == nullptr)
		{
			head->next = n;
			n->prev = head;
			n->next = nullptr;
		}
		else
		{
			n->next = head->next;
			n->next->prev = n;
			head->next = n;
			n->prev = head;

		}
	}
	void Insert(Iterator pos, T v)
	{
		if (pos.current->next == nullptr)
		{
			Node<T>* n = new Node<T>(v);
			pos.current->next = n;
			n->prev = pos.current;
			n->next = nullptr;

		}
		else
		{
			Node<T>* n = new Node<T>(v);
			n->next = pos.current->next;
			n->prev = pos.current;
			pos.current->next = n;
			n->next->prev = n;
		}

	}

	void Replace_All(char* v1, char* v2, int &s, int* &t)
	{
		Iterator* p1 = new Iterator[5000];
		
		int s1 = 0,s2=0;
		for (; v1[s1] != '\0'; s1++)
		{ }
			for (; v2[s2] != '\0'; s2++)
			{ }
				s1 -= 1;
		s2 -= 1;

		p1 = this->Search_All(v1,s1, s,t);
		if (s1 == s2)
		{
			for (int i = 0; i <s ; i++)
			{
				Iterator pos = p1[i];
				for (int j = 0; j < s2; j++,pos++)
				{
					pos.current->data = v2[j];
				}
			}
		}
		else if (s1 > s2)
		{
			for (int i = 0; i < s; i++)
			{
				Iterator pos = p1[i];
				for (int j = 0; j < s2; j++, pos++)
				{
					pos.current->data = v2[j];
				}
				for (int i=0;i< s1 - s2;i++)
				{
					Iterator temp = pos;
					 pos++;
					this->Delete(temp.current);
					
				}
			}
		}

		else if (s1 < s2)
		{
			for (int i = 0; i < s; i++)
			{
				Iterator pos = p1[i];
				int j = 0;
				for ( j = 0; j < s1; j++, pos++)
				{
					pos.current->data = v2[j];
				}
				pos--;
				for (int i = 0; i < s2 - s1; i++)
				{
				
					this->Insert(pos.current,v2[j]);
					pos++;
					j++;
				
					
				}
			}
		}
	}
	void Swap(T v1, T v2)
	{

		if (head->next != nullptr)
		{
			Node<T>* cv1 = new Node<T>;
			cv1 = head->next;
			Node<T>* cv2 = new Node<T>;
			cv2 = head->next;


			while (cv1->next != nullptr && cv1->data != v1)
			{
				cv1 = cv1->next;
			}
			while (cv2->next != nullptr && cv2->data != v2)
			{
				cv2 = cv2->next;
			}

			Node<T>* temp = new Node<T>;
			temp = cv2;
			cv1->next->prev = cv2;
			cv1->prev->next = cv2;
			cv2->next = cv1->next;
			cv2->prev = cv1->prev;

			temp->next->prev = cv1;
			temp->prev->next = cv1;
			cv1->next = temp->next;
			cv1->prev = temp->prev;


		}

	}

	void Delete_in_Range(Iterator pos1, Iterator pos2)
	{

		while (pos1.current->next != pos2.current)
		{

			Node<T>* ToDelete = new Node<T>;
			ToDelete = pos1.current->next;
			ToDelete->prev->next = ToDelete->next;
			ToDelete->next->prev = ToDelete->prev;
			delete ToDelete;

		}
	}
	void Delete(Iterator itr)
	{
		if (itr.current == head)
			return;
		else if (head->next != nullptr)
		{
			if (itr.current->next == nullptr)
			{
				Iterator temp = itr;
				temp--;
				temp.current->next = nullptr;
				delete itr.current;
			}
			else if (itr.current->prev == head)
			{
				Node<T>* temp = itr.current;
				head->next = temp -> next;
				temp->next->prev = head;
				delete temp;
			}
			else
			{
				Node<T>* temp = itr.current;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;

			}
		}


	}
	void Delete_from_Head()
	{
		if (head->next != nullptr)
		{
			if (head->next->next == nullptr)
			{
				delete head->next;
				head->next = nullptr;
			}
			else
			{
				Node<T>* ToHold = new Node<T>;
				ToHold = head->next->next;
				delete head->next;
				head->next = ToHold;
				ToHold->prev = head;
			}
		}
	}
	void Delete_All(T v)
	{
		if (head->next != nullptr)
		{
			Node<T>* curr = new Node<T>;
			curr = head->next;

			while (curr->next != nullptr)
			{
				if (curr->data == v)
				{

					curr = curr->next;
					Node<T>* ToDelete = new Node<T>;
					ToDelete = curr->prev;
					ToDelete->prev->next = ToDelete->next;
					ToDelete->next->prev = ToDelete->prev;
					delete ToDelete;

				}

				else

					curr = curr->next;

			}
			if ((curr->next == nullptr) && (curr->data == v))
			{

				curr->prev->next = nullptr;
				delete curr;

			}
		}

	}

	void Print()
	{
		if (head->next != nullptr)
		{

			for (Iterator pos = this->begin(); pos != this->end(); pos++)
			{
				cout << *pos;
			}
		}

	}


	Node<T>* head;
	Node<T>* tail;
};