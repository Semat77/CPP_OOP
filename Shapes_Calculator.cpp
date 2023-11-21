#include <map>
#include <cmath>
#include <vector>
#include <memory>
#include <string>
#include <iostream>
using namespace std;

static double pi = acos(-1);

class Shape
{
public:
	virtual ostream &out(ostream &s)const = 0;
	virtual istream &inp(istream &s) = 0;
	virtual double perimeter()const = 0;
	virtual double surface()const = 0;
	static shared_ptr<Shape> input(istream &s);
	template<typename T> static shared_ptr<Shape> make(istream &s);
};
ostream &operator<<(ostream &s, const Shape &sh) { return sh.out(s); }
istream &operator>>(istream &s, Shape &sh) { return sh.inp(s); }

class Circle :public Shape
{
private:
	double radius;
public:
	virtual ostream &out(ostream &s)const
	{
		//*///
		return s
            << "Circle"
            << "("
            << "radius:" << radius << ", "
            << "perimeter:" << perimeter() << ", "
            << "surface:" << surface()
            << ")"
			;
	}
	virtual istream &inp(istream &s) { return s >> radius; }
	virtual double perimeter()const { return 2 * pi*radius; };
	virtual double surface()const { return pi * radius*radius; }
};

class Rectangle :public Shape
{
private:
	double length;
	double width;
public:
	virtual ostream &out(ostream &s)const
	{
		return s
        << "Rectangle"
        << "("
        << "Length:" << length << ", "
        << "Width: " << width << ", "
        << "perimeter:" << perimeter() << ", "
        << "surface:" << surface()
        << ")";
	}
	virtual istream &inp(istream &s) { return s >> length >> width; };
	virtual double perimeter()const { return length + width; };
	virtual double surface()const { return length * width; };

};

class Triangle :public Shape
{
private:
	double a;
	double b;
	double c;
public:
	virtual ostream &out(ostream &s)const
	{
		return s
        << "Triangle"
        << "("
        << "a_side:" << a << ", "
        << "b_side: " << b << ", "
        << "c_side: " << c << ", "
        << "perimeter:" << perimeter() << ", "
        << "surface:" << surface()
        << ")";
	}
	virtual istream &inp(istream &s) { return s >> a >> b >> c; };
	virtual double perimeter()const { return a + b + c; };
	virtual double surface()const { double heron = (a + b + c) / 2; return sqrt(heron * (heron - a) * (heron - b) * (heron - c)); };
};


shared_ptr<Shape> Shape::input(istream &s)
{
	typedef shared_ptr<Shape> ShapeCreator(istream &s);
	typedef map<string, ShapeCreator*> MapOfCreators;
	static MapOfCreators map
	{
		{"circle",Shape::make<Circle>},
		{"triangle",Shape::make<Triangle>},
		{"rectangle",Shape::make<Rectangle>},
	};
	string key;
	s >> key;
	MapOfCreators::iterator found = map.find(key);
	if (found == map.end()) return nullptr;
	return found->second(s);
}

template<typename T> shared_ptr<Shape> Shape::make(istream &s)
{
	shared_ptr<Shape> sh = make_shared<T>();
	s >> *sh;
	cout << sh->perimeter() << endl;
	return sh;
}



int main()
{
	vector<shared_ptr<Shape>> tb;
	while (true)
	{
		cout << "Input shape: ";
		shared_ptr<Shape> sh = Shape::input(cin);
		if (sh == nullptr) break;
		tb.push_back(sh);

	}
	cout << endl << "Inputed:" << endl;
	for (shared_ptr<Shape> sh : tb) cout << *sh << endl;
	return 0;

}
