﻿#define _USE_MATH_DEFINES
#include <Windows.h>
#include <iostream>
using namespace std;

namespace Geometry
{
	enum Color
	{	//CMYK - Cyan Magenta 
		//RGB:
		RED			= 0x000000FF,
		GREEN		= 0x0000FF00,
		DARK_GREEN	= 0x0000AA00,
		BLUE		= 0x00FF0000,
		YELLOW		= 0x0000FFFF,
		CONSOLE_RED = 0xCC,  //Старшая "С" - цвет фона, младшая "С" - цвет текста.
		CONSOLE_GREEN = 0xAA,
		CONSOLE_BLUE = 0x99,
		CONSOLE_DEFAULT = 0x07
	};
#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color
	class Shape 
	{
	protected:
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 50;
		static const int MAX_START_X = 1000;
		static const int MAX_START_Y = 500;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 32;
		static const int MIN_SIZE = 50;
		static const int MAX_SIZE = 500;
		static int count;
	public:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
			count++;
		}
		virtual ~Shape()
		{
			count--;
		}
		int get_count()const
		{
			return count;
		}
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(unsigned int start_x)
		{
			if (start_x < MIN_START_X)start_x = MIN_START_X;
			if (start_x > MAX_START_X)start_x = MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y < MIN_START_Y)start_y = MIN_START_Y;
			if (start_y > MAX_START_Y)start_y = MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			//if (line_width > 30)line_width = 30;
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH : 
				line_width > MAX_LINE_WIDTH? MAX_LINE_WIDTH : 
				line_width;
		}
		int filter_size(int size)const
		{
			return 
				size<MIN_SIZE ? MIN_SIZE : 
				size>MAX_SIZE ? MAX_SIZE : 
				size;
		}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	int Shape::count = 0;

	//class Square :public Shape
	//{
	//	double side;
	//public:
	//	Square(double side, Color color) :Shape(color)
	//	{
	//		set_side(side);
	//	}
	//	~Square() {}
	//	void set_side(double side)
	//	{
	//		this->side = side;
	//	}
	//	double get_side()const
	//	{
	//		return side;
	//	}
	//	double get_area()const override
	//	{
	//		return side * side;
	//	}
	//	double get_perimeter()const override
	//	{
	//		return side * 4;
	//	}
	//	void draw()const override
	//	{
	//		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//		SetConsoleTextAttribute(hConsole, color);
	//		int side = 5;
	//		for (int i = 0; i < side; i++)
	//		{
	//			for (int j = 0; j < side; j++)
	//			{
	//				if (i + j >= side - 1)
	//					cout << '*';
	//				else
	//					cout << ' ';
	//			}
	//			cout << endl;
	//		}
	//		SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
	//	}
	//	void info()const override
	//	{
	//		cout << typeid(*this).name() << endl;
	//		cout << "Длина стороны: " << get_side() << endl;
	//		Shape::info();
	//	}
	//};

	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}
		void set_width(double width)
		{
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
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
			//1) Получаем окно консоли
			//HWND hwnd = GetConsoleWindow(); //Функция получает окно консоли
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			//2) Для того чтобы рисовать, нужен контекст устройства (Device Context), который есть у каждого окна
			//контекст устройства можно получить при помощи функции GetDC();
			HDC hdc = GetDC(hwnd);  //Получаем контекст окна консоли
			//Контекст устройства - это то, на чем мы будем рисовать
			//3) Теперь нам нужно то, чем мы будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);  //hPen - рисует контур фигуры
			//PS_SOLID - сплошная лини
			//5 - толщина линии 5 пикселов
			HBRUSH hBrush = CreateSolidBrush(color);	//hBrush - рисует заливку фигуры
			//SolidBrush - сплошной цвет
			//4) Выбираем чем, и на чем мы будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//5) Рисуем фигуру
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height); //:: - Global Scope
			//6) hdc, hPen и hBrush занимают ресурсы и после того, как мы ими воспользовалисись, ресурсы нужно освободить
			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина прямоугольника: " << get_width() << endl;
			cout << "Высота прямоугольника: " << get_height() << endl;
			Shape::info();
		}
	};
	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS):Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~Square(){}
	};
	class Circle :public Shape
	{
		double radius;
	public:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle(){}
		void set_radius(double radius)
		{
			//if (radius < 20)radius = 20;
			//if (radius > 200)radius = 200;
			this->radius = filter_size(radius);
		}
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return 2 * radius;
		}
		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return M_PI * get_diameter();
		}
		void draw()const override
		{
			//HWND hwnd = GetConsoleWindow();
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус окружности: " << get_radius() << endl;
			cout << "Диаметр окружности: " << get_diameter() << endl;
			Shape::info();
		}
	};

	class Triangle :public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS){}
		~Triangle() {}
		virtual double get_height()const = 0;
		void info()const override
		{
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
		}
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		~EquilateralTriangle(){}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const override
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area()const override
		{
			return side * get_height() / 2;
		}
		double get_perimeter()const override
		{
			return side * 3;
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT vertex[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};
			::Polygon(hdc, vertex, 3);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << get_side() << endl;
			Triangle::info();
		}
	};
	class IsoscelesTriangle :public Triangle
	{
		double base;
		double side;
	public:
		IsoscelesTriangle(double base, double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_base(base);
			set_side(side);
		}
		~IsoscelesTriangle(){}
		void set_base(double base)
		{
			this->base = filter_size(base);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
			if (this->side <= base / 2)this->side = base * 3 / 5;
		}
		double get_base()const
		{
			return base;
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const override
		{
			return sqrt(pow(side, 2) - pow(base / 2, 2));
		}
		double get_area()const override
		{
			return base * get_height() / 2;
		}
		double get_perimeter()const override
		{
			return base + side * 2;
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT vertex[] =
			{
				{start_x, start_y + side},
				{start_x + base, start_y + side},
				{start_x + base / 2, start_y + side - get_height()}
			};

			::Polygon(hdc, vertex, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Основание треугольника: " << get_base() << endl;
			cout << "Сторона треугольника: " << get_side() << endl;
			cout << "Высота треугольника: " << get_height() << endl;
			Triangle::info();
		}
	};
	class RightTriangle :public Triangle
	{
		double side1;
		double side2;
	public:
		RightTriangle(double side1, double side2, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side_1(side1);
			set_side_2(side2);
		}
		~RightTriangle(){}
		double get_side_1()const
		{
			return side1;
		}
		double get_side_2()const
		{
			return side2;
		}
		void set_side_1(double side1)
		{
			this->side1 = filter_size(side1);
		}
		void set_side_2(double side2)
		{
			this->side2 = filter_size(side2);
		}
		double get_hypotenuse()const
		{
			return sqrt(side1 * side1 + side2 * side2);
		}
		double get_height()const override
		{
			return side2;
		}
		double get_area()const override
		{
			return side1 * side2 / 2;
		}
		double get_perimeter()const override
		{
			return side1 + side2 + get_hypotenuse();
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT vertex[] =
			{
				{start_x, start_y},
				{start_x, start_y + get_height()},
				{start_x + side1, start_y + get_height()}
			};

			::Polygon(hdc, vertex, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона 1:	 " << side1 << endl;
			cout << "Сторона 2:	 " << side2 << endl;
			cout << "Гипотенуза: " << get_hypotenuse() << endl;
			Triangle::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	
	Geometry::Square square(50, 100, 100, 5, Geometry::Color::RED);
	square.info();
	
	Geometry::Rectangle rect(10000, 5000, 200, 100, 10, Geometry::Color::BLUE);
	rect.info();

	Geometry::Circle circle(50, 50, 300, 5, Geometry::Color::YELLOW);
	circle.info();

	Geometry::EquilateralTriangle eq_triangle(100, 400, 500, 5, Geometry::Color::RED);
	eq_triangle.info();

	Geometry::IsoscelesTriangle is_triangle(200, 10, 900, 200, 5, Geometry::Color::DARK_GREEN);
	is_triangle.info();
	
	Geometry::RightTriangle r_triangle(150, 80, 900, 100, 5, Geometry::Color::BLUE);
	r_triangle.info();

	cout << "Количество фигур: " << r_triangle.get_count() << endl;
}