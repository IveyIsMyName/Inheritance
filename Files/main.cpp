#include<iostream>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;

#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	cout << "Hello files" << endl;

	std::ofstream fout;			  //1)Cоздаем поток
	fout.open("File.txt", std::ios_base::app); //2)Открываем поток
	fout << "Hello files" << endl;
	fout << "Привет" << endl;     //3)Пишем в поток
	fout.close();				  //4)Закрываем поток

	system("notepad File.txt");
#endif // WRITE_TO_FILE

	std::ifstream fin("File.txt");  //1) Создание и открытие потока можно совместить
	if (fin.is_open())				//2) При чтении обязательно нужно проверять, открылся поток или нет
	{
		while (!fin.eof()) 			//3) Чтение из файла
		{
			const int SIZE = 1024000;
			char buffer[SIZE]{};
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		fin.close();				//4)Поток есть смысл закрывать только в том случае, если он был открыт
	}
	else
	{
		std::cerr << "Error: file is not found" << endl;
	}
}