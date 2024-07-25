#define _USE_MATH_DEFINES
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
			HPEN hPen = CreatePen(PS_SOLID, 5, color);  //hPen - рисует контур фигуры
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
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
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
		double side;
	public:
		Triangle(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		~Triangle(){}
		void set_side(double side)
		{
			//if (side < 20)side = 20;
			//if (side > 200)side = 200;
			this->side = filter_size(side);
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const 
		{
			return sqrt(side * side - side / 2 * side / 2);
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
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};
			::Polygon(hdc, trianglePoints, 3);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << get_side() << endl;
			Shape::info();
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

	Geometry::Circle circle(10000, 500, 500, 5, Geometry::Color::YELLOW);
	circle.info();

	Geometry::Triangle triangle(100, 300, 100, 10, Geometry::Color::GREEN);
	triangle.info();

	cout << "Количество фигур: " << triangle.get_count() << endl;

}