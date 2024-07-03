#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n---------------------------------------------------------------------------\n"
#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
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
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//			Methods:
	void print()const
	{
		cout << "Last name: " << last_name << " First name: "  << first_name << " (" << age << " years old)" << endl;
	}
};

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance

class Student : public Human
{
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
	void set_specialty(const std::string& speciality)
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
		set_specialty(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//		Methods:

	void print()const
	{
		Human::print();
		cout << "Speciality: " << speciality << " Group: " << group << " Rating: " << rating << " Attendance: " << attendance << endl;
	}
};

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience

class Teacher :public Human
{
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
	void print()const
	{
		Human::print();
		cout << "Speciality: " << speciality << " Experience: " << experience << " years" << endl;
	}
};

#define GRADUATE_TAKE_PARAMETERS const std::string& topic, int day, int month
#define GRADUATE_GIVE_PARAMETERS topic, day, month

class Graduate :public Student
{
	std::string topic;
	int day;
	int month;
public:
	const std::string& get_topic()const
	{
		return topic;
	}
	int get_day()const
	{
		return day;
	}
	int get_month()const
	{
		return month;
	}
	void set_topic(const std::string topic)
	{
		this->topic = topic;
	}
	void set_day(int day)
	{
		this->day = day;
	}
	void set_month(int month)
	{
		this->month = month;
	}

	//			Constructors:
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS) : Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_topic(topic);
		set_day(day);
		set_month(month);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//			Methods:
	void print()const
	{
		Student::print();
		cout <<"Topic: " << topic << " Date: " << day << '/' << month << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	
	Human human("Richter", "Jeffrey", 40);
	human.print();
	cout << delimiter;

	Student student("Pinkman", "Jessie", 20, "Chemistry", "WW_220", 95, 90);
	student.print();
	cout << delimiter;

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.print();
	cout << delimiter;

	Graduate graduate("Ilyukhin", "Ivan", 32, "Software Engineering", "BV_319", 100, 100, "Best app in the world", 31, 12);
	graduate.print();
	cout << delimiter;
}