#pragma once
#include"TTextLink.h"
#include"Tstack.h"
#include<cstring>
#include<fstream>

#include <iostream>
using namespace std;

class TText {

protected:
	TTextLink* pFirst; // указатель на корень дерева
	TTextLink* pCurrent; // указатель текущей строки
	TStack<TTextLink*> Path; // стек траекторий движения по тексту
	TStack<TTextLink*> Up; // стек переходов по down

	TTextLink* pIter; // указатель итератора
	TStack<TTextLink*> St; // стек для итератора

public:
	TText(); // конструктор 
	TText(const TText& temp); // конструктор копирования 
	TText(TTextLink* temp); // конструктор преобразования типов
	~TText(); // деструктор 

	TText GetCopy(); // вернуть копию 
	TTextLink* GetpFirst() const; // вернуть указатель на первый 
	TTextLink* GetpCurrent() const; // вернуть указатель на текущий
	TTextLink* GetIterator(void) const; // получить указатель на3 итератор

	// навигация
	bool GoFirstLink(void); // переход к первой строке 1 adc  2 jhk 3 dfg
	bool GoDownLink(void); // переход к следующей строке по pDown (вниз)
	bool GoNextLink(void); // переход к следующей строке по pNext (вперед)
	bool GoPrevLink(void); // переход к предыдущей позиции текста (мы переходим на пред элемент в его иерархии)
	bool GoUpLink(void); // переход к родителю

	// модификация структуры текста
	TTextLink* GetLink(void); // изъять текущий элемент (или его поддерево)
	void DelLink(void); // удалить текущий элемент (или его поддерево)
	void DelSubTree(TTextLink* pTl); // рекурсия удаления поддерева
	void InsNextLnk(TTextLink* pl); // вставить элемент pl (или его поддерево) следующим за текущим 
	void InsPrevLnk(TTextLink* pl); // вставить элемент pl (или его поддерево)перед теку-щим 
	void InsDownLink(TTextLink* pd); // вставить элемент pd (или его поддерево) вниз за текущим 
	void InsUpLink(TTextLink* pd); // вставить элемент pd (или его поддерево) вверх перед текущим 

	// доступ
	std::string GetLine(void);  // чтение текущей строки 
	void SetLine(string s); // замена текущей строки 

	// итератор
	void Reset(void); // установить на первую запись 
	bool IsTextEnded(void) const; // текст завершен? 
	bool GoNext(void); // переход к следующей записи 

	// Работа с файлами
	void Read(std::string pFileName); // ввод текста из файла 
	void Write(std::string pFileName); // сохранение текста в файл 

	// Печать
	void Print(void); // печать текста 
	void PrintText(TTextLink* ptl, int level = 0); // печать текста со звена ptl (рекурсия) 

	// Операторы
	TText& operator=(const TText& c);

};


/*
  
	 
	leve= 0
 1   1 first pcurent 
 {   1- prev down-2
 a  
 b   2-=prev next-3 убираем 2
 }   убираем 3 
 2    

*/