#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "time.h"

using namespace std;

class point {
private:
	double x;
	double y;
public:
	static double xc;   // (xc, yc) centre of mas;
	static double yc;
	point() : x(0), y(0) {};
	point(double _x, double _y);
	double get_x();
	double get_y();
	void set_x(double _x);
	void set_y(double _y);
	bool compare(point a, point b);  // *this - first comparing element,,, a - second comparing element,,, b - centre of mass
	bool operator > (point a);
	bool operator>=(point a);
	bool operator < (point a);
	point operator=(point a);
	bool operator!=(point a);
};

//____________________________________________________*Class methods*____________________________________________________________

point::point(double _x, double _y)
{
	x = _x;
	y = _y;
}

double point::get_x()
{
	return x;
}

double point::get_y()
{
	return y;
}

void point::set_x(double _x)
{
	x = _x;
}

void point::set_y(double _y)
{
	y = _y;
}

bool point::compare(point a, point b)  // *this - first comparing element,,, a - second comparing element,,, b - centre of mass
{
	double tmp1;
	double tmp2;

	tmp1 = sqrt((b.get_x() - x)*(b.get_x() - x) + (b.get_y() - y)*(b.get_y() - y));
	tmp2 = sqrt((b.get_x() - a.get_x())*(b.get_x() - a.get_x()) + (b.get_y() - a.get_y())*(b.get_y() - a.get_y()));

	return tmp1 > tmp2;
}

ifstream& operator>>(ifstream& ifs, point& a)   //from file
{
	if (ifs.is_open())
	{
		double tmp1, tmp2;
		ifs >> tmp1 >> tmp2;
		a.set_x(tmp1);
		a.set_y(tmp2);
	}
	return ifs;
}

ostream& operator<<(ostream& os, point& a)
{

	cout << " " << a.get_x() << " " << a.get_y();
	return os;
}

ofstream& operator<<(ofstream& ofs, point& a)
{
	if (ofs.is_open())
		ofs << a.get_x() << " " << a.get_y();
	return ofs;
}

bool point::operator>(point a)
{
	double tmp1;	//растояние объекта слева(this) до центра масс 
	double tmp2;	//растояние объекта справа(a) до центр масс	

	tmp1 = sqrt(pow(xc - this->x, 2) + pow((yc - this->y), 2));
	tmp2 = sqrt(pow(xc - a.get_x(), 2) + pow(yc - a.get_y(), 2));

	return tmp1 > tmp2;
}

bool point::operator>=(point a)
{
	double tmp1;	//растояние объекта слева(this) до центра масс 
	double tmp2;	//растояние объекта справа(a) до центр масс	

	tmp1 = sqrt(pow(xc - this->x, 2) + pow((yc - this->y), 2));
	tmp2 = sqrt(pow(xc - a.get_x(), 2) + pow(yc - a.get_y(), 2));

	return tmp1 >= tmp2;
}

bool point::operator<(point a)
{
	double tmp1;	//растояние объекта слева(this) до центра масс 
	double tmp2;	//растояние объекта справа(a) до центр масс	

	tmp1 = sqrt(pow(xc - this->x, 2) + pow((yc - this->y), 2));
	tmp2 = sqrt(pow(xc - a.get_x(), 2) + pow(yc - a.get_y(), 2));

	return tmp1 < tmp2;
}

point point::operator=(point a)
{
	x = a.get_x();
	y = a.get_y();
	return *this;
}

bool point::operator!=(point a)
{
	return (this->x != a.get_x() || this->y != a.get_y());
}

double point::xc;
double point::yc;

//_______________________________________________________________________________________________________________________________


point find_centre_of_mass(string f)   //WORKING CODE. Function is working.
{
	ifstream a;
	a.open(f);
	double tmp=0, summ_x=0, summ_y=0;

	int k=0;
	bool flag=0;

	while (!a.eof())
	{
			
		if (flag == 0)
		{
			a >> tmp;
			summ_x += tmp;
			flag = 1;
			k++;
			continue;
		}
		
		if (flag == 1)
		{
			a >> tmp;
			flag = 0;
		}

	}

	a.close();
	flag = 0;

	//cout << summ_x << " "; //FOR CHECK
	//cout << "k=" << k << " "; //FOR CHECK

	ifstream b;
	b.open(f);
	while (!b.eof())
	{
		if (flag == 1)
		{
			b >> tmp;
			summ_y += tmp;
			flag = 0;
			continue;
		}

		if (flag == 0)
		{
			b >> tmp;
			flag = 1;
		}
	}
	b.close();

		double sr_x = 0, sr_y = 0;
		sr_x = summ_x / k;
		sr_y = summ_y / k;

		point p;
		p.set_x(sr_x);
		p.set_y(sr_y);

		return p;
}

void gen_file()
{
	ofstream f;
	f.open("f.txt");

	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		f << " ";
		f << (rand() % 100) / 1.3;
	}
	

	f.close();

}

void distribution(string a, int kf) //a-file name, kf-quantity of files!
{
	ofstream *f = new ofstream[kf];   //massiv of files

	for (int i = 0; i < kf; i++)
	{
		f[i].open("f_" +  to_string(i) + ".txt");
	}

	ifstream fi; //open the source file
	fi.open(a);

	point tmp, tmp1;	
	//int tmp=0, tmp1=0;
	int i = 0;
	while (!fi.eof())
	{
		tmp1 = tmp;
		fi >> tmp;		
		if (tmp >= tmp1)
		{
			f[i] << " ";
			f[i] << tmp;
		}
		else
		{
			f[i] << " -1 -1";
			i = (i + 1) % kf; //change file
			f[i] << " ";
			f[i] << tmp;
		}
	}
	//f[i] << " -1 -1";
	fi.close();
	for (int i = 0; i < kf; i++)
		f[i].close();
	delete[] f;
}

int check(ifstream *f, int kf)  //check for end of any file, if one of files will end, return 0
{
	int tmp = 0;
	for (int i = 0; i < kf; i++)
		if (!f[i].eof()) tmp++;
	return tmp;
}

point get_elem(ifstream &f)
{
	point tmp;
	if (!f.eof())
		f >> tmp;
	else
	{
		tmp.set_x(-1);
		tmp.set_y(-1);
	}
	return tmp;
}

int FindIndexOfMin(point *elements, int kf)
{
	int index=-1;
	point tmp(-1, -1);
	for (int i = 0; i < kf; i++)
	{
		if (elements[i] != tmp)
		{
			index = i;
			break;
		}
	}
	if (index == -1) return -1;
	point min=elements[index];
	for (int i= index; i < kf;i++)
		if (elements[i] < min && elements[i]!=tmp)
		{
			min = elements[i];
			index = i;
		}
	return index;
}

int merger(string a, int kf)
{
	ifstream *f = new ifstream[kf]; //massiv of files (for merger)
	for (int i=0; i < kf; i++)
		f[i].open("f_" + to_string(i) + ".txt");

	ofstream fi; //Source file
	fi.open(a);

	point *elements=new point[kf];  //for keeping elements from files

	int ks = 0;
	
	while (check(f,kf))
	{
		for (int i = 0; i < kf; i++)
			elements[i] = get_elem(f[i]);
		int min = FindIndexOfMin(elements, kf);
		while (min!=-1)
		{
			fi << " ";
			fi << elements[min];
			elements[min] = get_elem(f[min]);
			min = FindIndexOfMin(elements, kf);
		}
		ks++;
	}
	
	for (int i = 0; i < kf; i++)
		f[i].close();
	delete[] f;


	return ks;
}

void sort(string a, int kf)
{
	point centre;
	centre = find_centre_of_mass(a);
	point::xc = centre.get_x();
	point::yc = centre.get_y();

	int ks = 0;
	
	while (ks != 1)
	{
		distribution(a, kf);
		ks = merger(a, kf);
	}
}


int main()
{

	gen_file();
	//distribution("f.txt", 2);
	
	
	//merger("4.txt", 2);
	sort("f.txt", 2);
	
	/*
	distribution("3.txt", 2);
	merger("4.txt", 2);
	distribution("4.txt", 2);
	merger("4.txt", 2);
	*/
	cout << endl << endl;
}
