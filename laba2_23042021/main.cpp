#include<iostream>
#include"TText.h"
#include"TTextLink.h"
#include<cstring>
#include<string>
#include<cstdlib>
#include<fstream>
using namespace std;


void StringInput(string& temp) {
	cout << "Input string: ";
	getline(cin, temp);
}

void ShowCommands(void) {

	cout << "    " << "help" << " - выводит список команд в консоль" << endl;
	cout << "    " << "n" << " - установить директорию" << endl;
	cout << "    " << "c" << " - скопировать текущую строку" << endl;
	cout << "    " << "o" << " - открыть файл" << endl;
	cout << "    " << "s" << " - сохранить текст в файл" << endl;
	cout << "    " << "p" << " - вывести текст"  << endl;
	cout << "    " << "f" << " - перейти к первой" << endl;
	cout << "    " << "v" << " - перейти вниз" << endl;
	cout << "    " << ">" << " - перейти к следующей" << endl;
	cout << "    " << "<" << " - перейти к предыдущей" << endl;
	cout << "    " << "u" << " - перейти вверх" << endl;
	cout << "    " << "d" << " - удалить текущую строку" << endl;
	cout << "    " << "i" << " - вставить строчку" << endl;
	cout << "    " << "r" << " - изменить строчку" << endl;
	cout << "    " << "l" << " - clear the console" << endl;
	cout << "    " << "e" << " - close the app" << endl;
}

int main() {
	string t = "";
	TText text_list[5];
	TText* text = &text_list[0];
	int dir_number = 0;
	string Input = "";
	TTextLink* text_link = nullptr;
	setlocale(LC_CTYPE, "Russian");
	string name = "";
	cout << "Directory number " << dir_number << endl;
	cout << "Введите название файла, который хотите открыть: ";
	cin >> name;
	if (name != "") {
		text->Read(name);
	}
	while (true)
	{
		system("cls");
		cout << "Directory number " << dir_number << endl;
		cout << "________________________________________________________________________________" << endl;
		text->Print();
		cout << "________________________________________________________________________________" << endl;
		cout << "Ваша команда: ";
		cin >> name;
		if (name == "help") {
			ShowCommands();
			system("pause");
		}
		else
			switch (name[0])
			{
			case 'n':
				cout << "Введите номер директории (0,1,2,3,4)" << endl;
				cin >> name;
				if (name == "0") {
					text = &text_list[0];
					dir_number = 0;
				}
				else if (name == "1") {
					text = &text_list[1];
					dir_number = 1;
				}
				else if (name == "2") {
					text = &text_list[2];
					dir_number = 2;
				}
				else if (name == "3") {
					text = &text_list[3];
					dir_number = 3;
				}
				else if (name == "4") {
					text = &text_list[4];
					dir_number = 4;
				}
				else {
					cout << "неверная команда" << endl;
					system("pause");
				}
				break;

			case 'c':
				text_link = text->GetLink();
				break;

			case 'f':
				if (!text->GoFirstLink()) {
					cout << "Can't go first. " << endl;
					system("pause");
				}
				break;

			case 'o':
				cout << "Введите название файла, который хотите открыть: " << endl;
				cin >> name;
				if (name != "") {
					text->Read(name);
				}
				break;

			case 's':
				cout << "Введите название файла, в который вы хотите сохранить: " << endl;
				cin >> name;
				if (name != "") {
					text->Write(name);
				}
				break;

			case 'v':
				if (!text->GoDownLink()) {
					cout << "Can't go down. " << endl;
					system("pause");
				}
				break;
			case '>':
				if (!text->GoNextLink()) {
					cout << "Can't go next. " << endl;
					system("pause");
				}
				break;
			case '<':
				if (!text->GoPrevLink()) {
					cout << "Can't go previous. " << endl;
					system("pause");
				}
				break;
			case 'u':
				if (!text->GoUpLink()) {
					cout << "Can't go up. " << endl;
					system("pause");
				}
				break;

			case 'd':
				text->DelLink();
				break;
			case 'i':
				cout << "Выберите команду:" << endl;
				cout << "1 - вставить элемент следующим за текущим (вручную)"<<endl;
				cout << "2 - вставить элемент перед теку-щим  (вручную)" << endl;
				cout << "3 - вставить элемент вниз за текущим  (вручную)" << endl;
				cout << "4 - вставить элемент вверх перед текущим (вручную)" << endl;
				cout << "+1 - вставить элемент следующим за текущим (скопированное)" << endl;
				cout << "+2 - вставить элемент перед теку-щим (скопированное)" << endl;
				cout << "+3 - вставить элемент вниз за текущим (скопированное)" << endl;

				cin >> name;
				if (name == "1") {
					StringInput(Input);
					text->InsNextLnk(new TTextLink(Input));
				}
				else if (name == "+1" && text_link != nullptr) {
					text->InsNextLnk(text_link);
	
				}
				else if (name == "2") {
					cin >> Input;
					text->InsPrevLnk(new TTextLink(Input));
				}
				else if (name == "+2" && text_link != nullptr) {
					text->InsPrevLnk(text_link);
				}
				else if (name == "3") {
					cin >> Input;
					text->InsDownLink(new TTextLink(Input));
				}
				else if (name == "+3" && text_link != nullptr) {
					text->InsDownLink(text_link);
				}
				else if (name == "4") {
					cin >> Input;
					text->InsUpLink(new TTextLink(Input));
				}
				else {
					cout << "неверная команда"<< endl;
					system("pause");
				}
				break;

			case 'p':
				cout << "Выберите команду:" << endl;
				cout << "1 - вывести все" << endl;
				cout << "2 - вывести текущую строку" << endl;
				cout << "3 - вывести все после текущей" << endl;
				cin >> name;
				if (name == "1") {
					text->Print();
					system("pause");
				}
				else if (name == "2") {
					cout << text->GetLine();
					system("pause");
				}
				else if (name == "3") {
					text->PrintText(text->GetpCurrent(), 0);
					system("pause");
				}
				else {
					cout << "неверная команда"<< endl;
					system("pause");
				}
				break;
			case 'r':
				cout << "Введите строку: ";
				cin >> name;
				text->SetLine(name);
				break;
			case 'l':
				system("cls");
				break;
			case 'e':
				return 0;
				break;
			default:
				cout << "неверная команда" << endl;
				system("pause");
				break;



			}
	}
}