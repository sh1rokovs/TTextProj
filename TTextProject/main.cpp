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
		cout << "����:\n\n";

		cout << "1. ������� �� �����" << endl;
		cout << "2. �����" << endl;
		cout << "3. ��������� ����" << endl;

		cout << "\n����������� ���������:" << endl;
		cout << "4. ����������� ToNext" << endl;
		cout << "5. ����������� ToDown" << endl;
		cout << "6. ����������� ToPrev" << endl;
		cout << "7. ����������� ToFirst" << endl;

		cout << "\n��������:" << endl;
		cout << "8. ������� InsNextLine" << endl;
		cout << "9. ������� InsNextSection" << endl;
		cout << "10. ������� InsDownLine" << endl;
		cout << "11. ������� InsDownSection" << endl;
		cout << "12. �������� DelNext" << endl;
		cout << "13. �������� DelDown" << endl;

		cout << "\n������ � �������:" << endl;
		cout << "14. ������ ������" << endl;
		cout << "15. ����� ������ �������" << endl;

		cout << "\n0. �����\n" << endl;

		cin >> Num;

		switch (Num)
		{
		case 1:
		{
			system("cls");

			cout << "������� �������� ����� ��� ������" << endl;
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

			cout << "������� �������� ����� ��� ������" << endl;
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

			cout << "������� ����� ������" << endl;
			cin >> s;
			tmp.InsNextLine(s);

			tmp.Print();
			system("pause");
			break;
		}
		case 9:
		{
			system("cls");

			cout << "������� ����� ������" << endl;
			cin >> s;
			tmp.InsNextSection(s);

			tmp.Print();
			system("pause");
			break;
		}
		case 10:
		{
			system("cls");

			cout << "������� ����� ������" << endl;
			cin >> s;
			tmp.InsDownLine(s);

			tmp.Print();
			system("pause");
			break;
		}
		case 11:
		{
			system("cls");

			cout << "������� ����� ������" << endl;
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