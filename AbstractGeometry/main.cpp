#define _USE_MATH_DEFINES
#include <Windows.h>
#include <iostream>
using namespace std;

namespace Geometry
{
	enum Color
	{
		CONSOLE_RED = 0xCC,  //������� "�" - ���� ����, ������� "�" - ���� ������.
		CONSOLE_GREEN = 0xAA,
		CONSOLE_BLUE = 0x99,
		CONSOLE_DEFAULT = 0x07
	};

	class Shape
	{
	protected:
		Color color;
	public:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		Shape(Color color) :color(color) {}
		virtual ~Shape() {}
		virtual void info()const
		{
			cout << "������� ������: " << get_area() << endl;
			cout << "�������� ������: " << get_perimeter() << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;
	public:
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Square() {}
		void set_side(double side)
		{
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			int side = 5;
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					if (i + j >= side - 1)
						cout << '*';
					else
						cout << ' ';
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "����� �������: " << get_side() << endl;
			Shape::info();
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, Color color) :Shape(color)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}
		void set_width(double width)
		{
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			//WinGDI - Windows Graphics Device Interface
			//1) �������� ���� �������
			//HWND hwnd = GetConsoleWindow(); //������� �������� ���� �������
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			//2) ��� ���� ����� ��������, ����� �������� ���������� (Device Context), ������� ���� � ������� ����
			//�������� ���������� ����� �������� ��� ������ ������� GetDC();
			HDC hdc = GetDC(hwnd);  //�������� �������� ���� �������
			//�������� ���������� - ��� ��, �� ��� �� ����� ��������
			//3) ������ ��� ����� ��, ��� �� ����� ��������
			HPEN hPen = CreatePen(PS_SOLID, 5, color);  //hPen - ������ ������ ������
			//PS_SOLID - �������� ����
			//5 - ������� ����� 5 ��������
			HBRUSH hBrush = CreateSolidBrush(color);	//hBrush - ������ ������� ������
			//SolidBrush - �������� ����
//4) �������� ���, � �� ��� �� ����� ��������
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//5) ������ ������
			::Rectangle(hdc, 500, 100, 900, 300); //:: - Global Scope
			//6) hdc, hPen � hBrush �������� ������� � ����� ����, ��� �� ��� �����������������, ������� ����� ����������
			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������ ��������������: " << get_width() << endl;
			cout << "������ ��������������: " << get_height() << endl;
			Shape::info();
		}
	};
	class Circle :public Shape
	{
		double radius;
	public:
		Circle(double radius, Color color) :Shape(color)
		{
			set_radius(radius);
		}
		~Circle(){}
		void set_radius(double radius)
		{
			this->radius = radius;
		}
		double get_radius()const
		{
			return radius;
		}
		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return 2 * M_PI * radius;
		}
		void draw()const override
		{
			//HWND hwnd = GetConsoleWindow();
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, 500, 300, 900, 600);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������ ����������: " << get_radius() << endl;
			Shape::info();
		}
	};

	class Triangle :public Shape
	{
		double side;
	public:
		Triangle(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Triangle(){}
		void set_side(double side)
		{
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_area()const override
		{
			return side * side * sqrt(3) / 4;
		}
		double get_perimeter()const override
		{
			return side * 3;
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT trianglePoints[] =
			{
			 { 200, 150 },
			 { 150, 250 },
			 { 250, 250 }
			};
			::Polygon(hdc, trianglePoints, 3);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "����� �������: " << get_side() << endl;
			Shape::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	
	Geometry::Square square(5, Geometry::Color::CONSOLE_RED);
	square.info();
	
	Geometry::Rectangle rect(100, 50, Geometry::Color::CONSOLE_BLUE);
	rect.info();

	Geometry::Circle circle(100, Geometry::Color::CONSOLE_GREEN);
	circle.info();

	Geometry::Triangle triangle(100, Geometry::Color::CONSOLE_GREEN);
	triangle.info();

}