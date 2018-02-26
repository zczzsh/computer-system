// JSON_Complete.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

enum ValueType
{
INT,        // JSON's int
DOUBLE,      // JSON's double 3.14 12e-10
BOOL,       // JSON's boolean (true, false)
STRING,     // JSON's string " ... " 
OBJECT,     // JSON's object { ... }
ARRAY,      // JSON's array [ ... ]
};

class Value;
class Array {
	vector <Value> v_vec;
public:
	Array() {};
	Value & operator[](int index)
	{
		return v_vec[index];
	}

	string to_json()
	{
		string str = "[";
		for (int i=0;i<v_vec.size();i++)
		{
			str = str + v_vec[i].to_json();
			int n = i;
			if (++n != v_vec.size())
				str = str + ",";
		}
		str = str + "]";
		return str;
	}

	vector <Value>::iterator begin()
	{
		return v_vec.begin();
	}
	vector <Value>::iterator end()
	{
		return v_vec.end();
	}
	void clear()
	{
		v_vec.clear();
	}
	bool empty()
	{
		return v_vec.empty();
	}
	int size()
	{
		return v_vec.size();
	}
	void push_back(const Value & val)
	{
		v_vec.push_back(val);
	}
};

class Value {
	string v_string;
	double v_double;
	int v_int;
	bool v_bool;
	Object v_object;
	Array v_array;
	ValueType type;
public:
	Value();
	Value(string v) : v_string(v), type(STRING) { };
	Value(double v) : v_double(v), type(DOUBLE) { };
	Value(int v): v_int(v), type(INT) { };
	Value(bool v) : v_bool(v), type(BOOL) { };
	Value(Object v) : v_object(v), type(OBJECT) { };
	Value(Array v) : v_array(v), type(ARRAY) { };
	//constructions
	string & to_string() 
	{
		return this->v_string;
	}
	double & to_double()
	{
		return this->v_double;
	}
	int & to_int()
	{
		return this->v_int;
	}
	bool & to_bool()
	{
		return this->v_bool;
	}

	//conversions 
	Value & operator[](const string & val) 
	{
		return v_object[val];
	}
	Value & operator[](const int val)
	{
		return v_array[val];
	}
	Value & operator=(const string & val) 
	{
		v_string = val;
		return *this;
	}
	Value & operator=(const double & val) //两者可以同时存在，函数重载
	{
		v_double = val;
		return *this;
	}
	Value & operator=(const int & val)
	{
		v_int = val;
		return *this;
	}
	Value & operator=(const bool & val)
	{
		v_bool = val;
		return *this;
	}
	Value & operator=(const Object & val)
	{
		v_object = val;
		return *this;
	}
	Value & operator=(const Array & val)
	{
		v_array = val;
		return *this;
	}
	// and = operator for other structures…
	string to_json() 
	{
		string str = "";
		switch (type) {
		case STRING:
			str = str + this->v_string + str;
			break;
		case INT:
			str = std::to_string(v_int);
			break;
		case DOUBLE:
			str = std::to_string(v_double);
			break;
		case BOOL:
			str = v_bool ? "true" : "false"; // 这里需要返回true和false 的字符串
			break;
		case ARRAY:
			str = v_array.to_json();
			break;
		case OBJECT:
			str = v_object.to_json();
			break;
		}
		return str;
	}
	ValueType get_type()
	{
		return type;
	}

	void push_back(Value val)
	{
		v_array.push_back(val);
	}
};

class Object {
	map <string, Value> obj_map;
public:
	Object() {};
	Value & operator[] (const string & key) {
		return obj_map[key];
	}

	string to_json() {
		string str = "{";
		for (auto i = obj_map.rbegin(); i != obj_map.rend(); ++i) {
			str = str + "\"" + i->first + "\"" + ":" + i->second.to_json();
			auto n = i;
			if (++n != obj_map.rend()) {
				str = str + ",";
			}
		}
		str = str + "}";
		return str;
	}
	map<string, Value>::iterator find(const string &val)
	{
		return obj_map.find(val);
	}
	void insert(pair<string, Value> data)
	{
		obj_map.insert(data);
	}
	void erase(map<string, Value>::iterator it)
	{
		obj_map.erase(it);
	}
	map<string, Value>::iterator begin()
	{
		return obj_map.begin();
	}
	map<string, Value>::iterator end()
	{
		return obj_map.end();
	}
	int size() const {
		return obj_map.size();
	}
	void clear()
	{
		obj_map.clear();
	}
	bool empty()
	{
		return obj_map.empty();
	}
};

int main()
{
	Object obj;
	obj["title"] = "Thinking in C++";
	obj["price"] = 116.0;
	obj["pages"] = 927;
	obj["authors"] = Array();
	obj["authors"].push_back("Bruce Eckel");
	obj["authors"].push_back("Chuck Allison");
	obj["pub_info"] = Object();
	obj["pub_info"]["name"] = "China Machine Press";
	cout << obj.to_json();
	system("pause");
    return 0;
}

