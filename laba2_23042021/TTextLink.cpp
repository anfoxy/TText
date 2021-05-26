#pragma once
#include"TTextLink.h"
#include<iostream>
#include<string>

void TTextLink::Print(std::ostream& os) {
	os << this->Str << '\n';
}

TTextLink::TTextLink(std::string s, TTextLink* pNext_copy, TTextLink* pDown_copy) {
	this->Str = "";
	for (int i = 0; i < s.size(); i++) {
		this->Str += s[i];
	}
	this->pNext = pNext_copy;
	this->pDown = pDown_copy;
}

bool TTextLink::IsAtom() {
	if (this->pDown == nullptr)
		return true;
	return false;
}


TTextLink* TTextLink::GetNext(void) {
	if (this != nullptr)
		return this->pNext;
	return nullptr;
}

TTextLink* TTextLink::GetDown(void) {
	if (this != nullptr)
		return this->pDown;
	return nullptr;
}

std::string TTextLink::GetStr(void) {
	if (this != nullptr)
		return this->Str;
	return nullptr;
}

void TTextLink::SetNext(TTextLink* pNext_copy) {
	if (this != nullptr)
		this->pNext = pNext_copy;
}

void TTextLink::SetDown(TTextLink* pDown_copy) {
	if (this != nullptr)
		this->pDown = pDown_copy;
}

void TTextLink::SetStr(std::string str_copy) {
	if (this != nullptr)
		this->Str = str_copy;
}

std::ostream& operator<<(std::ostream& os, const TTextLink& tl) {
	os << tl.Str;
	return os;
}