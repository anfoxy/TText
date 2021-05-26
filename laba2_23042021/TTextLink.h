#pragma once
#include<iostream>
#include<cstring>

class TTextLink {

protected:
	std::string Str;// хранимое значение
	TTextLink* pNext; // указатель на следующий элемент на том же уровне
	TTextLink* pDown; // указатель на элемент ниже уровнем

	void Print(std::ostream& os); // печать содержимого

public:
	TTextLink(std::string s = nullptr, TTextLink* pNext_copy = nullptr, TTextLink* pDown_copy = nullptr); // конструктор
	~TTextLink() {}

	bool IsAtom(); // проверка звена на атомарность

	TTextLink* GetNext(void); // получить указатель на следующий
	TTextLink* GetDown(void); // получить указатель на элеемент ниже уровнем
	std::string GetStr(void); // получить содержимое строки
	void SetNext(TTextLink* pNext_copy); // задать указатель на следующий
	void SetDown(TTextLink* pDown_copy); // задать указатель на элемент ниже уровнем
	void SetStr(std::string str_copy); // задать содержимое строки


	friend std::ostream& operator<<(std::ostream& os, const TTextLink& tl);
	friend class TText;

};