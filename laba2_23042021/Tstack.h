#pragma once
#include<iostream>
using namespace std;

template <class T>
class TStack {

protected:
	T* pMem;
	int MaxSize;
	int MemLen;
	//int Hi;

public:
	TStack(int Size = 100);
	~TStack();

	bool IsEmpty(void) const;
	bool IsFull(void) const;

	void Put(const T type);
	T Get(void);
	T See(void);
	void Clear(void); 

	void Output(void);
};


template <typename T>
TStack<T>::TStack(int Size) {
	this->pMem = new T[Size];
	this->MaxSize = Size;
	this->MemLen = 0;
//	this->Hi = -1;
}

template <typename T>
TStack<T>::~TStack() {
	delete[]this->pMem;
	this->MaxSize = 0;
	this->MemLen = 0;
//	this->Hi = -1;
}

template <typename T>
bool TStack<T>::IsEmpty(void) const {
	if (this->MemLen == 0)
		return true;
	return false;
}

template <typename T>
bool TStack<T>::IsFull(void) const {
	if (this->MemLen == this->MaxSize)
		return true;
	return false;
}

template <typename T>
void TStack<T>::Put(const T type) {
	if (this->IsFull() == false) {
		this->pMem[this->MemLen] = type;
		this->MemLen += 1;
	//	this->Hi += 1;
	}
}

template <typename T>
T TStack<T>::Get(void) {
	if (this->IsEmpty())
		return nullptr;
	T result = this->pMem[this->MemLen-1];
//	this->Hi -= 1;
	this->MemLen -= 1;// 1 a b c  
	return result;
}

template<typename T>
T TStack<T>::See(void) {
	return this->pMem[this->MemLen - 1];
}

template<typename T>
void TStack<T>::Clear(void) {
	while (!(this->IsEmpty())) { 
		this->Get();
	}
}
