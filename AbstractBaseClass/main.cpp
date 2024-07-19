#include <iostream>
using namespace std;

class Vehicle
{
public:
	virtual void move() = 0;
};
class GroundVehicle :public Vehicle {}; //Абстрактный пацан
class AirVehicle :public Vehicle
{
public:
	virtual void take_off() = 0;			//Взлет
	virtual void land() = 0;			    //Посадка
};

class Bike :public GroundVehicle		 //Конкретный пацан
{
public:
	void move()override
	{
		cout << "Harley Davidson едет на двух колесах" << endl;
	}
};
class Car :public GroundVehicle
{
public:
	void move()override
	{
		cout << "BMW едет на четырех колесах" << endl;
	}
};
class Airplane :public AirVehicle
{
public:
	void move()override
	{

		take_off();
		cout << "Boeing летит на крыльях" << endl;
		land();
	}
	void take_off()override
	{
		cout << "Нужна взлетная полоса" << endl;
	}
	void land()override
	{
		cout << "Нужна посадочная полоса" << endl;
	}
};
class Helicopter :public AirVehicle
{
public:
	void move()override
	{
		take_off();
		cout << "Летим потихоньку" << endl;
		land();
	}
	void take_off()override
	{
		cout << "Могу взлететь с любого огорода" << endl;
	}
	void land()override
	{
		cout << "Где захочу, там и сяду" << endl;
	}
};
void main()
{
	setlocale(LC_ALL, "");
	//Vehicle vehicle;
	//GroundVehicle gv;
	Bike harley_davidson;
	harley_davidson.move();

	Car bmw;
	bmw.move();

	Airplane boeing;
	boeing.move();

	Helicopter blackHawk;
	blackHawk.move();

}