#include "Zveno.h"
#include "Stack.h"

TextMem Zveno::MemHeader;
void main()
{
	Text tmp;

	char NameofFile[50], s[80];

	Zveno::InitMemSystem(100);

	setlocale(LC_CTYPE, "Russian");

	int Num = 1;

	while (Num != 0)
	{
		Num = -1;
		system("cls");
		cout << "Меню:\n\n";

		cout << "1. Считать из файла" << endl;
		cout << "2. Вывод" << endl;
		cout << "3. Сохранить файл" << endl;

		cout << "\nПеремещение указателя:" << endl;
		cout << "4. Переместить ToNext" << endl;
		cout << "5. Переместить ToDown" << endl;
		cout << "6. Переместить ToPrev" << endl;
		cout << "7. Переместить ToFirst" << endl;

		cout << "\nОперации:" << endl;
		cout << "8. Вставка InsNextLine" << endl;
		cout << "9. Вставка InsNextSection" << endl;
		cout << "10. Вставка InsDownLine" << endl;
		cout << "11. Вставка InsDownSection" << endl;
		cout << "12. Удаление DelNext" << endl;
		cout << "13. Удаление DelDown" << endl;

		cout << "\nРабота с памятью:" << endl;
		cout << "14. Сборка мусора" << endl;
		cout << "15. Вывод пустых звеньев" << endl;

		cout << "\n0. Выход\n" << endl;

		cin >> Num;

		switch (Num)
		{
		case 1:
		{
			system("cls");

			cout << "Введите название файла для чтения" << endl;
			cin >> NameofFile;

			tmp.Read(NameofFile);

			break;
		}
		case 2:
		{
			system("cls");

			tmp.Print();
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");

			cout << "Введите название файла для записи" << endl;
			cin >> NameofFile;

			tmp.PointerDelete();
			tmp.Write(NameofFile);
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");

			tmp.PointerDelete();
			tmp.ToNext();

			tmp.PointerCreate();
			tmp.Print();
			system("pause");

			break;
		}
		case 5:
		{
			system("cls");

			tmp.PointerDelete();
			tmp.ToDown();

			tmp.PointerCreate();
			tmp.Print();
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");

			tmp.PointerDelete();
			tmp.ToPrev();

			tmp.PointerCreate();
			tmp.Print();
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			tmp.PointerDelete();
			tmp.ToFirst();

			tmp.PointerCreate();
			tmp.Print();
			system("pause");
			break;
		}
		case 8:
		{
			system("cls");

			cout << "Введите новую строку" << endl;
			cin >> s;
			tmp.InsNextLine(s);

			tmp.Print();
			system("pause");
			break;
		}
		case 9:
		{
			system("cls");

			cout << "Введите новую строку" << endl;
			cin >> s;
			tmp.InsNextSection(s);

			tmp.Print();
			system("pause");
			break;
		}
		case 10:
		{
			system("cls");

			cout << "Введите новую строку" << endl;
			cin >> s;
			tmp.InsDownLine(s);

			tmp.Print();
			system("pause");
			break;
		}
		case 11:
		{
			system("cls");

			cout << "Введите новую строку" << endl;
			cin >> s;
			tmp.InsDownSection(s);

			tmp.Print();
			system("pause");
			break;
		}
		case 12:
		{
			system("cls");

			tmp.DelNext();

			tmp.Print();
			system("pause");
			break;
		}
		case 13:
		{
			system("cls");

			tmp.DelDown();

			tmp.Print();
			system("pause");
			break;
		}
		case 14:
		{
			system("cls");

			Zveno::MemCleaner(tmp);
			system("pause");
			break;
		}
		case 15:
		{
			system("cls");

			Zveno::PrintFreeLink();
			system("pause");
			break;
		}
		default: continue;
		}
	}

}