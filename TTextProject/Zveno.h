#pragma once

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#include "Stack.h"

class Text;
class Zveno;
class TextMem
{
	Zveno* pFirst;
	Zveno* pLast;
	Zveno* pFree;

	friend class Zveno;
};

class Zveno
{
protected:
	Zveno* pNext;
	Zveno* pDown;
	char str[80];

	static TextMem MemHeader; // Система управлению памяти

public:
	Zveno(char* s = NULL, Zveno* pN = NULL, Zveno* pD = NULL);

	~Zveno();

	static void InitMemSystem(int size = 1000);

	void* operator new(size_t size);

	void operator delete(void* pM);

	static void MemCleaner(Text& txt);

	static void PrintFreeLink();

	friend class Text;
};

class Text
{
	Zveno* pFirst, * pCurr;
	stack <Zveno*> st;
	int TextLevel;

public:
	Text(Zveno* pf = NULL);
	~Text();

	void ToNext()
	{
		if (pCurr->pNext)
		{
			st.push(pCurr);
			pCurr = pCurr->pNext;
		}
	}

	void ToDown()
	{
		if (pCurr->pDown)
		{
			st.push(pCurr);
			pCurr = pCurr->pDown;
		}
	}

	void ToPrev()
	{
		if (!st.Empty())
			pCurr = st.pop();
	}

	void ToFirst()
	{
		pCurr = pFirst;
		st.clear();
	}

	void InsNextLine(char* s)
	{
		if (pCurr != NULL)
		{
			Zveno* tmp;
			tmp = new Zveno(s, pCurr->pNext, NULL);
			pCurr->pNext = tmp;
		}
	}
	void InsNextSection(char* s)
	{
		if (pCurr != NULL)
		{
			Zveno* tmp;
			tmp = new Zveno(s, NULL, pCurr->pNext);
			pCurr->pNext = tmp;
		}
	}

	void InsDownLine(char* s)
	{
		if (pCurr != NULL)
		{
			Zveno* tmp;
			tmp = new Zveno(s, pCurr->pDown, NULL);
			pCurr->pDown = tmp;
		}
	}

	void InsDownSection(char* s)
	{
		if (pCurr != NULL)
		{
			Zveno* tmp;
			tmp = new Zveno(s, NULL, pCurr->pDown);
			pCurr->pDown = tmp;
		}
	}

	void DelNext()
	{
		if (pCurr->pNext != NULL)
		{
			Zveno* tmp;
			tmp = pCurr->pNext;
			pCurr->pNext = pCurr->pNext->pNext;
			delete tmp;
		}
	}

	void DelDown()
	{
		if (pCurr->pDown != NULL)
		{
			Zveno* tmp;
			tmp = pCurr->pDown;
			pCurr->pDown = pCurr->pDown->pNext;
			delete tmp;
		}
	}

	void ToStart()
	{
		pCurr = pFirst;
	}

	Zveno* ReadText(ifstream& TxtFile)
	{
		Zveno* pHead, * ptl;
		char StrBuf[80];
		int BufLength = 80;
		pHead = ptl = new Zveno();

		while (TxtFile.eof() == 0)
		{
			TxtFile.getline(StrBuf, BufLength, '\n');

			if (StrBuf[0] == '}')
			{
				break;
			}
			else
				if (StrBuf[0] == '{')
				{
					Zveno* tmp = ReadText(TxtFile);
					ptl->pDown = tmp->pNext;
					delete tmp;
				}
				else
				{
					ptl->pNext = new Zveno(StrBuf);
					ptl = ptl->pNext;
				}
		}

		ptl = pHead;
		if (pHead->pDown != NULL)
		{
			pHead = pHead->pNext;
			delete ptl;
		}

		return pHead;
	}

	void Read(char* pFileName)
	{
		ifstream TxtFile(pFileName);

		if (pFileName != NULL)
		{
			pFirst = ReadText(TxtFile);
		}

		Zveno* tmp = pFirst;
		pFirst = pFirst->pNext;
		pCurr = pFirst;
		delete tmp;
	}

	void PrintText(Zveno* ptl)
	{
		if (ptl != NULL)
		{
			for (int i = 0; i < TextLevel; i++)
				cout << " ";

			cout << " " << ptl->str << endl;

			if (ptl->pDown != NULL)
			{
				//TextLevel++;
				PrintText(ptl->pDown);
			}
			if (ptl->pNext != NULL)
			{
				//TextLevel--;
				PrintText(ptl->pNext);
			}
		}
	}

	void Print()
	{
		TextLevel = 0;
		PrintText(pFirst);
	}

	void WriteText(ofstream& ofs, Zveno* tl)
	{
		ofs << tl->str << endl;
		if (tl->pDown != NULL)
		{
			ofs << '{' << endl;
			WriteText(ofs, tl->pDown);
			ofs << '}' << endl;
		}
		if (tl->pNext != NULL)
		{
			WriteText(ofs, tl->pNext);
		}
	}

	void Write(char* pFileName)
	{
		ofstream ofs(pFileName);
		WriteText(ofs, pFirst);
	}

	Zveno* GetCurrent() { return pCurr; };
	int IsEnd();

	void GoNext();

	void Reset();

	void PointerCreate();
	void PointerDelete();
};

Zveno::Zveno(char* s, Zveno* pN, Zveno* pD)
{
	pNext = pN; pDown = pD;

	if (s) strcpy_s(str, s);
	else str[0] = '\0';
}

Zveno::~Zveno() {};

void* Zveno::operator new(size_t size)
{
	Zveno* pLink = MemHeader.pFree;

	if (MemHeader.pFree != NULL)
		MemHeader.pFree = pLink->pNext;

	return pLink;
}

void Zveno::operator delete(void* pM)
{
	Zveno* pLink = (Zveno*)pM;
	pLink->pNext = MemHeader.pFree;
	MemHeader.pFree = pLink;
}

void Zveno::MemCleaner(Text& txt)
{
	for (txt.Reset(); !txt.IsEnd(); txt.GoNext())
	{
		char Marker[80] = "&&&";
		strcat_s(Marker, txt.GetCurrent()->str);
		strcpy_s(txt.GetCurrent()->str, Marker);
	}

	Zveno* pLink;

	for (pLink = MemHeader.pFree; pLink != NULL; pLink = pLink->pNext)
		strcpy_s(pLink->str, "&&&");

	for (pLink = MemHeader.pFirst; pLink <= MemHeader.pLast; pLink++)
		if (strstr(pLink->str, "&&&") != NULL)
			strcpy_s(pLink->str, pLink->str + 3);
		else
			delete pLink;
}

void Zveno::InitMemSystem(int size)
{
	MemHeader.pFirst = (Zveno*) new char[sizeof(Zveno) * size];
	MemHeader.pFree = MemHeader.pFirst;
	MemHeader.pLast = MemHeader.pFirst + (size - 1);
	Zveno* pLink = MemHeader.pFirst;

	for (int i = 0; i < size - 1; i++, pLink++)
	{
		pLink->pNext = pLink + 1;
	}

	pLink->pNext = NULL;
}

void Zveno::PrintFreeLink()
{
	cout << "List:\n" << endl;

	for (Zveno* pLink = MemHeader.pFree; pLink != NULL; pLink = pLink->pNext)
	{
		if (strcmp(pLink->str, "") != 0)
			cout << pLink->str << endl;
	}
}

Text::Text(Zveno* pf)
{
	if (!pf) pf = new Zveno;

	pFirst = pf;
	pCurr = pFirst;
}

Text::~Text() {};

int Text::IsEnd()
{
	return st.Empty();
}

void Text::GoNext()
{
	if (!IsEnd())
	{
		pCurr = st.pop();

		if (pCurr != pFirst)
		{
			if (pCurr->pNext != NULL) st.push(pCurr->pNext);
			if (pCurr->pDown != NULL) st.push(pCurr->pDown);
		}
	}
}

void Text::Reset()
{
	st.clear();

	pCurr = pFirst;

	if (pCurr != NULL)
	{
		st.push(pCurr);

		if (pCurr->pNext != NULL) st.push(pCurr->pNext);
		if (pCurr->pDown != NULL) st.push(pCurr->pDown);
	}
}

void Text::PointerCreate()
{
	if (pCurr != NULL)
	{
		char Point[80] = "->";
		strcat_s(Point, pCurr->str);
		strcpy_s(pCurr->str, Point);
	}
}

void Text::PointerDelete()
{
	if (pCurr != NULL && strstr(pCurr->str, "->") != NULL)
		strcpy_s(pCurr->str, pCurr->str + 2);
}
