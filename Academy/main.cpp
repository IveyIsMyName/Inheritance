#include <iostream>
#include <string>
#include <fstream>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n---------------------------------------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	static const int TYPE_WIDTH = 12;
	static const int LAST_NAME_WIDTH = 15;
	static const int FIRST_NAME_WIDTH = 15;
	static const int AGE_WIDTH = 5;

	std::string first_name;
	std::string last_name;
	int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	//			Constructors:
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//			Methods:
	virtual std::ostream& print(std::ostream& os)const
	{
		return os << last_name << " " << first_name << " " << age;
	}
	virtual std::ofstream& print(std::ofstream& ofs)const
	{
		ofs.width(TYPE_WIDTH);		//Метод width() задает ширину вывода.
									//При первом вызове метод width() включает выравнивание по правому краю.
		ofs << std::left;

		ofs << std::string(strchr(typeid(*this).name(), ' ') + 1) + ":"; //оператор typeid(type | value) определяет тип значения на этапе выполнения программы
		ofs.width(LAST_NAME_WIDTH);																 //Метод name() возвращает C-String (Null Terminated Line)
		ofs << last_name;
		ofs.width(FIRST_NAME_WIDTH);
		ofs << first_name; 
		ofs.width(AGE_WIDTH);
		ofs << age;
		return ofs;
	}
	virtual std::ifstream& read(std::ifstream& ifs)
	{
		ifs >> last_name >> first_name >> age;
		return ifs;
	}
};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.print(os);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	return obj.print(ofs);
}
std::ifstream& operator>>(std::ifstream& ifs, Human& obj)
{
	return obj.read(ifs);
}

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance

class Student : public Human
{
	const static int SPECIALITY_WIDTH = 25;
	const static int GROUP_WIDTH = 8;
	const static int RATING_WIDTH = 8;
	const static int ATTENDANCE_WIDTH = 8;
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}
	
	//		Constructors:
	Student(HUMAN_TAKE_PARAMETERS,STUDENT_TAKE_PARAMETERS):Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	Student(const Human& human, STUDENT_TAKE_PARAMETERS) :Human(human)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "Sconstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//		Methods:

	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os)<< " " << speciality << " " << group << " " << rating << " " << attendance;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);
		ofs.width(SPECIALITY_WIDTH);
		ofs << speciality; 
		ofs.width(GROUP_WIDTH);
		ofs << group;
		ofs.width(RATING_WIDTH);
		ofs << rating;
		ofs.width(ATTENDANCE_WIDTH);
		ofs << attendance;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Human::read(ifs);
		ifs >> speciality;
		ifs >> group;
		ifs >> rating;
		ifs >> attendance;
		return ifs;
	}
};

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience

class Teacher :public Human
{
	const static int SPECIALITY_WIDTH = 25;
	const static int EXPERIENCE_WIDTH = 5;
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}

	//			Constructors:
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) : Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//			Methods:
	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os)<< " " << speciality << " " << experience;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);
		ofs.width(SPECIALITY_WIDTH);
		ofs << speciality;
		ofs.width(EXPERIENCE_WIDTH);
		ofs << experience;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Human::read(ifs);
		char sz_speciality[SPECIALITY_WIDTH + 1]{}; //sz_ - String Zero
		ifs.read(sz_speciality, SPECIALITY_WIDTH);
		for (int i = SPECIALITY_WIDTH - 2; sz_speciality[i] == ' '; i--)sz_speciality[i] = 0;
		while (sz_speciality[0] == ' ')for (int i = 0; sz_speciality[i]; i++)sz_speciality[i] = sz_speciality[i + 1];
		speciality = sz_speciality;
		ifs >> experience;
		return ifs;
	}
};

#define GRADUATE_TAKE_PARAMETERS const std::string& topic
#define GRADUATE_GIVE_PARAMETERS topic

class Graduate :public Student
{
	const static int TOPIC_WIDTH = 25;
	std::string topic;
public:
	const std::string& get_topic()const
	{
		return topic;
	}
	void set_topic(const std::string& topic)
	{
		this->topic = topic;
	}

	//			Constructors:
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS) : Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_topic(topic);
		
		cout << "GConstructor:\t" << this << endl;
	}
	Graduate(const Student& student, const std::string& topic) :Student(student)
	{
		set_topic(topic);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//			Methods:
	std::ostream& print(std::ostream& os)const override
	{
		return Student::print(os) <<" " << topic;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Student::print(ofs); 
		ofs.width(TOPIC_WIDTH);
		ofs << topic;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Student::read(ifs);
		std::getline(ifs, topic);
		return ifs;
	}
};

Human* HumanFactory(const std::string& type)
{
	Human* human = nullptr;
	if (type == "Human:")human = new Human("", "", 0);
	if (type == "Student:")human = new Student("", "", 0, "", "", 0, 0);
	if (type == "Teacher:")human = new Teacher("", "", 0, "", 0);
	if (type == "Graduate:")human = new Graduate("", "", 0, "", "", 0, 0, "");
	return human;
}
void Print(Human* group[], const int n)
{
	cout << delimiter << endl;
	for (int i = 0; i < n; i++)
	{
		//group[i]->print();
		if (group[i])
		{
			cout << *group[i] << endl;
			cout << delimiter << endl;
		}
	}
	cout << "Количество человек в группе: " << n << endl;
}
void Clear(Human* group[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		delete group[i];
	}
}
void WriteToFile(Human* group[], const int n, const std::string& filename)
{
	std::ofstream fout(filename); 
	for (int i = 0; i < n; i++)
	{
		fout << *group[i] << endl;
	}
	fout.close();
	std::string cmd = "notepad " + filename;
	system(cmd.c_str());	//Функция system(const char*) выполняет любую доступную команду операционной системы
}							//Метод c_str() возвращает С-string (NULL Terminated Line), обвернутый в объект класса std::string
bool NotAppropriateType(const std::string& buffer)
{
	return buffer.find("Human") == std::string::npos &&
		buffer.find("Student") == std::string::npos &&
		buffer.find("Teacher") == std::string::npos &&
		buffer.find("Graduate") == std::string::npos;
}
Human** Load(const std::string& filename, int& n)
{
	Human** group = nullptr;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		n = 0;
		//1) Вычисляем размер файла
		while (!fin.eof())
		{
			std::string buffer;
			std::getline(fin, buffer); //читает все до конца строки
			if (NotAppropriateType(buffer))continue;
			n++;
		}
		cout << "Количество записей в файле " << n << endl;

		//2) Выделяем память для группы:
		group = new Human * [n] {};

		//3) Возвращаемся в начало файла, для того чтобы прочитать содержимое этого файла
		cout << "Позиция курсора на чтение: " << fin.tellg() << endl;
		fin.clear();
		fin.seekg(0);
		cout << "Позиция курсора на чтение: " << fin.tellg() << endl;

		//4) Читаем файл:
		for (int i = 0; i < n; i++)
		{
			std::string type;
			fin >> type;
			if (NotAppropriateType(type))continue;
			//std::getline(fin, type, ':');
			group[i] = HumanFactory(type);
			if (group[i]) fin >> *group[i];
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file is not found" << endl;
	}
	return group;
}

//#define INHERITANCE_1
//#define INHERITANCE_2
//#define SAVE_CHECK
#define LOAD_CHECK
void main()
{
	setlocale(LC_ALL, "");
	
#ifdef INHERITANCE_1
	Human human("Richter", "Jeffrey", 40);
	human.print();
	cout << delimiter;

	Student student("Pinkman", "Jessie", 20, "Chemistry", "WW_220", 95, 90);
	student.print();
	cout << delimiter;

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.print();
	cout << delimiter;

	Graduate graduate("Ilyukhin", "Ivan", 32, "Software Engineering", "BV_319", 100, 100, "Best app in the world");
	graduate.print();
	cout << delimiter;
#endif // INHERITANCE_1

#ifdef INHERITANCE_2
	Human human("Vercetty", "Tommy", 30);
	human.print();
	cout << delimiter;

	Student student(human, "Theft", "Vice", 95, 98);
	student.print();
	cout << delimiter;

	Graduate graduate(student, "How to make money");
	graduate.print();
	cout << delimiter;
#endif // INHERITANCE_2

#ifdef SAVE_CHECK
		Human* group[] =
	{
		new Student("Pinkman", "Jessie", 20, "Chemistry", "WW_220", 95, 90),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Ilyukhin", "Ivan", 32, "Software Engineering", "BV_319", 100, 100, "Best app in the world"),
		new Student("Vercetti", "Tommy", 30, "Theft", "Vice", 95, 98),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};
	cout << delimiter;
	//Print(group, sizeof(group) / sizeof(group[0]));
	WriteToFile(group, sizeof(group) / sizeof(group[0]), "Group.txt");
	//ReadFromFile(group, sizeof(group) / sizeof(group[0]), "Group.txt");
	Clear(group, sizeof(group) / sizeof(group[0]));

#endif // SAVE_CHECK

#ifdef LOAD_CHECK
	int n = 0;
	Human** group = Load("Group.txt", n);
	Print(group, n);
	Clear(group, n);
#endif // LOAD_CHECK

}