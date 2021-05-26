#include "TText.h"
#include <string>

TText::TText() {
	this->pFirst = nullptr;
	this->pCurrent = nullptr;
	this->pIter = nullptr;
}

TText::TText(const TText& temp) {
	TTextLink* curr = temp.GetpFirst();
	TStack<TTextLink*> stack(100);
	TStack<TTextLink*> path(100);
	bool flag_first = true;
	while (curr != nullptr) {
		if (flag_first) {
			this->pFirst = new TTextLink(curr->GetStr());
			this->pCurrent = this->pFirst;
			flag_first = false;
		}
		else {
			if (path.See()->GetDown() == curr) {
				this->InsDownLink(new TTextLink(curr->GetStr()));
				this->GoDownLink();
			}
			else if (path.See()->GetNext() == curr) {
				this->InsNextLnk(new TTextLink(curr->GetStr()));
				this->GoNextLink();
			}
		}
		if (curr->GetDown() != nullptr) {
			path.Put(curr);
			stack.Put(curr);
			curr = curr->GetDown();
		}
		else if (curr->GetNext() != nullptr) {
			path.Put(curr);
			curr = curr->GetNext();
		}
		else {
			while (!stack.IsEmpty() && stack.See()->GetNext() == nullptr) {
				curr = stack.Get();
				this->GoUpLink();
			}
			if (stack.IsEmpty()) {
				curr = curr->GetNext();
				this->GoFirstLink();
			}
			else {
				curr = stack.Get();
				this->GoUpLink();
				path.Put(curr);
				curr = curr->GetNext();
			}
		}
	}
}

TText::TText(TTextLink* temp) {
	this->pFirst = temp;
	this->pCurrent = temp;
	this->pIter = temp;
}

TText::~TText() {
	this->GoFirstLink();
	while (this->pCurrent != nullptr)
		this->DelLink();
	this->Path.Clear();
	this->Up.Clear();
	this->pIter = nullptr;
	this->St.Clear();
}

TText TText::GetCopy() {
	TText copy(*this);
	return copy;
}

TTextLink* TText::GetpFirst() const {
	return this->pFirst;
}

TTextLink* TText::GetpCurrent() const {
	return this->pCurrent;
}

TTextLink* TText::GetIterator(void) const {
	return this->pIter;
}

bool TText::GoFirstLink(void) {
	this->Path.Clear();
	this->pCurrent = this->pFirst;
	return true;
}


bool TText::GoDownLink(void) {
	if (this != nullptr) {
		if (this->pCurrent->GetDown() != nullptr) {
			this->Path.Put(this->pCurrent);
			this->Up.Put(this->pCurrent);
			this->pCurrent = this->pCurrent->GetDown();
			return true;
		}
		return false;
	}
	return false;
}


bool TText::GoNextLink(void) {

	if (this != nullptr) {
		if (this->pCurrent->GetNext() != nullptr) {
			this->Path.Put(this->pCurrent);
			this->pCurrent = this->pCurrent->GetNext();
			return true;
		}
		return false;
	}
	return false;
}

bool TText::GoPrevLink(void) {
	if (!(this->Path.IsEmpty())) {
		if (this->Path.See() != this->Up.See())
			this->pCurrent = this->Path.Get();
		else {
			this->pCurrent = this->Path.Get();
			this->Up.Get();
		}
		return true;
	}
	return false;
}

bool TText::GoUpLink(void) {
	if (this != nullptr) {
		if (!this->Up.IsEmpty()) {
			this->pCurrent = this->Up.Get();
			while (this->Path.See() != this->pCurrent)
				this->Path.Get();
			this->Path.Get();
			return true;
		}
		return false;
	}
	return false;
}


TTextLink* TText::GetLink(void) {
	this->Reset();
	TTextLink* temp = this->pCurrent; 
	
	if (temp == this->pFirst) { 
		this->pFirst = temp->GetNext();
		this->pCurrent = this->pFirst;
		temp->SetNext(nullptr);
	}
	else { 
		while (this->pIter->GetNext() != temp && this->pIter->GetDown() != temp) {
			this->GoNext();
		}
		if (this->pIter->GetNext() == temp) {
			this->pIter->SetNext(temp->GetNext());
			temp->SetNext(nullptr);
			this->pCurrent = this->pIter->GetNext();
			if (this->pCurrent == nullptr)
				this->pCurrent = this->pFirst;
		}
		else if (this->pIter->GetDown() == temp) {
			this->pIter->SetDown(temp->GetNext());
			temp->SetNext(nullptr);
			this->pCurrent = this->pIter->GetDown();
			if (this->pCurrent == nullptr)
				this->pCurrent = this->pFirst;
		}
	}
	return temp;
}


void TText::DelLink(void) {
	this->Reset();
	TTextLink* temp = this->pCurrent; 
	if (temp == this->pFirst) { 
		this->pFirst = temp->GetNext();
		this->pCurrent = this->pFirst;
		temp->SetNext(nullptr);
	}
	else { 
		while (this->pIter->GetNext() != temp && this->pIter->GetDown() != temp) {
			this->GoNext();
		}
		if (this->pIter->GetNext() == temp) {
			this->pIter->SetNext(temp->GetNext());
			temp->SetNext(nullptr);
			this->pCurrent = this->pIter->GetNext();
			if (this->pCurrent == nullptr)
				this->pCurrent = this->pFirst;
		}
		else if (this->pIter->GetDown() == temp) {
			this->pIter->SetDown(temp->GetNext());
			temp->SetNext(nullptr);
			this->pCurrent = this->pIter->GetDown();
			if (this->pCurrent == nullptr)
				this->pCurrent = this->pFirst;
		}
	}
	this->DelSubTree(temp);
}

void TText::DelSubTree(TTextLink* pTl) {
	if (pTl->GetDown() != nullptr) this->DelSubTree(pTl->GetDown());
	TTextLink* temp = pTl->GetNext();
	delete pTl;
	if (temp != nullptr) this->DelSubTree(temp);
}

void TText::InsNextLnk(TTextLink* pl) {
	pl->SetNext(this->pCurrent->GetNext());
	this->pCurrent->SetNext(pl);
}

void TText::InsPrevLnk(TTextLink* pl) {
	TTextLink* prev = this->Path.See();
	if (!this->Path.IsEmpty()) {
		if (prev->GetNext() == this->pCurrent) {
			pl->SetNext(this->pCurrent);
			prev->SetNext(pl);
		}
		else if (prev->GetDown() == this->pCurrent) {
			pl->SetNext(this->pCurrent);
			prev->SetDown(pl);
		}
	}
	else {
		pl->SetNext(this->pCurrent);
		this->pFirst = pl;
	}
}


void TText::InsDownLink(TTextLink* pd) {
	pd->SetNext(this->pCurrent->GetDown());
	this->pCurrent->SetDown(pd);
}

void TText::InsUpLink(TTextLink* pd) {
	TTextLink* prev = this->Path.See();
	if (!this->Path.IsEmpty()) {
		pd->SetDown(this->pCurrent);
		pd->SetNext(this->pCurrent->GetNext());
		this->pCurrent->SetNext(nullptr);
		if (prev->GetNext() == this->pCurrent)
			prev->SetNext(pd);
		else if (prev->GetDown() == this->pCurrent)
			prev->SetDown(pd);
		this->pCurrent = pd;
	}
	else if (this->pCurrent == this->pFirst) {
		pd->SetDown(this->pCurrent);
		pd->SetNext(this->pCurrent->GetNext());
		this->pCurrent->SetNext(nullptr);
		this->pFirst = pd;
		this->pCurrent = pd;
	}
}


std::string TText::GetLine(void) {
	if (this->pCurrent == nullptr)
		return "Can't read Str, because of nullptr";
	return this->pCurrent->Str;
}


void TText::SetLine(string s) {
	this->pCurrent->SetStr(s);
}


void TText::Reset(void) {
	this->St.Clear();
	this->pIter = this->pFirst;
}

bool TText::IsTextEnded(void) const {
	if (this->pIter == nullptr)
		return true;
	return false;
}

bool TText::GoNext(void) {
	if (this->pIter != nullptr) {
		if (this->pIter->GetDown() != nullptr) {
			this->St.Put(this->pIter);
			this->pIter = this->pIter->GetDown();
		}
		else if (this->pIter->GetNext() != nullptr) {
			this->pIter = this->pIter->GetNext();
		}
		else {
			while (!(this->St.IsEmpty()) && this->St.See()->GetNext() == nullptr) {
				this->pIter = this->St.Get();
			}
			if (this->St.IsEmpty()) {
				this->pIter = this->pIter->GetNext();
			}
			else {
				this->pIter = this->St.Get();
				this->pIter = this->pIter->GetNext();
			}
		}
		return true;
	}
	else {
		return false;
	}
}


void TText::Read(std::string pFileName) {
	fstream fin;
	fin.open(pFileName);
	std::string temp;
	TStack<TTextLink*> stack(100);
	bool flag_first = true;
	while (getline(fin, temp)) {
		TTextLink* add = new TTextLink(temp);
		if (flag_first) {
			this->pFirst = add;
			this->pCurrent = add;
			flag_first = false;
			stack.Put(add);
		}
		else {
			if (temp == "{") {
				TTextLink* prev = stack.See();
				getline(fin, temp);
				TTextLink* add = new TTextLink(temp);
				prev->SetDown(add);
				stack.Put(add);
			}
			else if (temp == "}") {
				stack.Get();
			}
			else {
				TTextLink* prev = stack.Get();
				prev->SetNext(add);
				stack.Put(add);
			}
		}

	}

	this->Reset();
	fin.close();
}


void TText::Write(std::string pFileName) {
	ofstream fout;
	fout.open(pFileName);
	TTextLink* curr = this->pFirst;
	TStack<TTextLink*> stack(100);

	while (curr != nullptr) {
		fout << curr->GetStr() << '\n';
		if (curr->GetDown() != nullptr) {
			fout << "{\n";
			stack.Put(curr);
			curr = curr->GetDown();
		}
		else if (curr->GetNext() != nullptr) {
			curr = curr->GetNext();
		}
		else {
			while (!stack.IsEmpty() && stack.See()->GetNext() == nullptr) {
				curr = stack.Get();
				fout << "}\n";
			}
			if (stack.IsEmpty()) {
				curr = curr->GetNext();
			}
			else {
				curr = stack.Get();
				fout << "}\n";
				curr = curr->GetNext();
			}
		}
	}
	fout.close();

	
}



void TText::Print(void) {
	TTextLink* curr = this->pFirst;
	TStack<TTextLink*> stack(100);
	int level = 0;
	while (curr != nullptr) {
		std::string tab = "";
		for (int i = 0; i < level; i++)
			tab = tab + "    ";
		cout << tab << curr->GetStr();
		if (curr == this->pCurrent)
			cout << "(+)";
		cout << endl;
		if (curr->GetDown() != nullptr) {
			stack.Put(curr);
			curr = curr->GetDown();
			level++;
		}
		else if (curr->GetNext() != nullptr) {
			curr = curr->GetNext();
		}
		else {
			while (!(stack.IsEmpty()) && stack.See()->GetNext() == nullptr) {
				curr = stack.Get();
				level--;
			}
			if (stack.IsEmpty()) {
				curr = curr->GetNext();
			}
			else {
				curr = stack.Get();
				level--;
				curr = curr->GetNext();
			}
		}
	}
}


void TText::PrintText(TTextLink* ptl, int level) {
	string temp = "";
	for (int i = 0; i < level; i++) {
		temp = temp + "    ";
	}
	cout << temp << ptl->GetStr();
	if (ptl == this->pCurrent) {
		cout << "(+)";
	}
	cout << '\n';
	if (ptl->GetDown() != nullptr)	this->PrintText(ptl->GetDown(), level + 1);
	if (ptl->GetNext() != nullptr)	this->PrintText(ptl->GetNext(), level);
}

TText& TText::operator=(const TText& temp)
{

	this->GoFirstLink();
	while (this->pCurrent != nullptr)
		this->DelLink();
	this->Path.Clear();
	this->Up.Clear();
	this->pIter = nullptr;
	this->St.Clear();

	TTextLink* curr = temp.GetpFirst(); 
	TStack<TTextLink*> stack(100); 
	TStack<TTextLink*> path(100); 
	bool flag_first = true;
	while (curr != nullptr) {

		if (flag_first) {
			this->pFirst = new TTextLink(curr->GetStr());
			this->pCurrent = this->pFirst;
			flag_first = false;
		}
		else {
			if (path.See()->GetDown() == curr) {
				this->InsDownLink(new TTextLink(curr->GetStr()));
				this->GoDownLink();
			}
			else if (path.See()->GetNext() == curr) {
				this->InsNextLnk(new TTextLink(curr->GetStr()));
				this->GoNextLink();
			}
		}
		if (curr->GetDown() != nullptr) {
			path.Put(curr);
			stack.Put(curr);
			curr = curr->GetDown();
		}
		else if (curr->GetNext() != nullptr) {
			path.Put(curr);
			curr = curr->GetNext();
		}
		else {
			while (!stack.IsEmpty() && stack.See()->GetNext() == nullptr) {
				curr = stack.Get();
				this->GoUpLink();
			}
			if (stack.IsEmpty()) {
				curr = curr->GetNext();
				this->GoFirstLink();
			}
			else {
				curr = stack.Get();
				this->GoUpLink();
				path.Put(curr);
				curr = curr->GetNext();
			}
		}
	}

	return *this;
}