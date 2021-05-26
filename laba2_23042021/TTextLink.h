#pragma once
#include<iostream>
#include<cstring>

class TTextLink {

protected:
	std::string Str;// �������� ��������
	TTextLink* pNext; // ��������� �� ��������� ������� �� ��� �� ������
	TTextLink* pDown; // ��������� �� ������� ���� �������

	void Print(std::ostream& os); // ������ �����������

public:
	TTextLink(std::string s = nullptr, TTextLink* pNext_copy = nullptr, TTextLink* pDown_copy = nullptr); // �����������
	~TTextLink() {}

	bool IsAtom(); // �������� ����� �� �����������

	TTextLink* GetNext(void); // �������� ��������� �� ���������
	TTextLink* GetDown(void); // �������� ��������� �� �������� ���� �������
	std::string GetStr(void); // �������� ���������� ������
	void SetNext(TTextLink* pNext_copy); // ������ ��������� �� ���������
	void SetDown(TTextLink* pDown_copy); // ������ ��������� �� ������� ���� �������
	void SetStr(std::string str_copy); // ������ ���������� ������


	friend std::ostream& operator<<(std::ostream& os, const TTextLink& tl);
	friend class TText;

};