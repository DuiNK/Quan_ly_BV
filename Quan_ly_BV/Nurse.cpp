#include<iostream>
#include<string>
#include<stdio.h>
#include<fstream>
#include <vector>

using namespace std;

class Person {
protected:
	int id;
	string name;
	string address;
	long long  phone;

public:
	//constructor function
	Person() {
		id = 0;
		name = "";
		address = "";
		phone = 0;
	}
	Person(string name, string address, long long phone) {
		this->name = name;
		this->address = address;
		this->phone = phone;
	}
	virtual void set() {}
	virtual void print() {}
	//virtual int age(){}

	~Person() { }
};

class Patient : public Person {
protected:
	int year;
	string benh;
public:
	Patient() :Person() {
		year = 0;
	}
	Patient(string name, string address, long long phone, int year) :Person(name, address, phone) {
		this->year = year;
	}
	void set() {
		cin.ignore();
		cout << "\t\tEnter Name:";
		getline(cin, name);

		cout << "\n\t\tEnter address:";
		getline(cin, address);

		cout << "\n\t\tEnter year: ";
		cin >> year;

		cout << "\n\t\tEnter phone number:";
		cin >> phone;
		while (cin.fail()) {
			cout << "Phone number is in integer form!";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> phone;
		}
	}
	void setBenh(string b) {
		benh = b;
	}
	string getBenh() {
		return benh;
	}
	int age() {
		return (2022 - year);
	}
	string getname() {
		return name;
	}
	long long getphone() {
		return phone;
	}
	string getadd() {
		return address;
	}
	string getInfo() {				//tao thong tin benh nhan de luu vao file
		string info = name + "," + address + "," + to_string(phone) + "," + to_string(year);
		return info;
	}
	void print() {
		cout << "\t" << name << "\t\t";
		cout << age() << "\t";

	}
};
void readDataFile(vector<Patient>& p) {
	string myText;
	ifstream MyReadFile("queue.txt");
	while (getline(MyReadFile, myText)) {
		string s = myText;
		string delim = ",";
		int cnt = 0;
		//tim duoc data1
		auto start = 0U;
		auto end = s.find(delim);

		string name;
		string address;
		long long  phone;
		int year;
		//read data
		while (end != string::npos)		//dieu kien khi gap gia tri ao
		{
			string value = s.substr(start, end - start);	//xac dinh khoang data nam giua 2 dau ,
			if (cnt == 0) name = value;			//luu data1 vao name
			if (cnt == 1) address = value;		//luu data2 vao address
			if (cnt == 2) phone = stoi(value);	//luu data3 vao phone
			cnt++;
			start = end + delim.length();
			end = s.find(delim, start);
		}
		string value = s.substr(start, end);
		year = stoi(value);
		p.push_back(Patient(name, address, phone, year));
	}
}

//PatientList(add patient in list)
void getPatientList(vector<Patient>& P) {
	P.push_back(Patient());
	P.back().set();
	//cout<< "\n get list  ";
}
//sort(uu tien)
void sortPatientList(vector<Patient>& P) {
	Patient tg;
	for (int i = P.size() - 1; i > 0; i--) {
		if (P.at(i).age() < 2 || P.at(i).age() > 79) {
			tg = P.at(i);
			P.at(i) = P.at(i - 1);
			P.at(i - 1) = tg;
		}
	}
	//cout << "\n sort list  ";
}
//save data to text
void saveList(vector<Patient>& P) {
	ofstream ofs("queue.txt");
	char b = '"';
	if (!ofs) {
		cout << "Loi: file khong mo duoc.";
		return;
	}
	for (size_t i = 0; i < P.size(); i++) {
		ofs << P.at(i).getInfo() << endl;
	}
}
void updateDataFile(vector<Patient>& P, string filename) {
	ofstream update;
	update.open(filename);
	for (int i = 0; i < P.size(); i++) {
		update << P.at(i).getInfo();
		if (i != P.size() - 1) {
			update << "\n";
		}
	}
	update.close();
}

//showList 
void showList(vector<Patient>& P) {
	int i;
	if (!P.size()) {
		cout << "\t\t\t\tChua co benh nhan nao\n\n\n\n\n\n" << endl;
	}
	else {
		for ( i = 0; i < P.size(); i++)
			//show priority patient
			if (P.at(i).age() < 2 || P.at(i).age() > 79) {
				cout << "\t" << i + 1 << ".\t";
				P.at(i).print();
				cout << "(uu tien)";
				cout << endl;
			}
			else {
				cout << "\t" << i + 1 << ".\t";
				P.at(i).print();		//show patient
				cout << endl;
			}
	}
}
//Delete the wrong Patient
void DelPatient(vector<Patient>& P, int i) {		//xoa benh nhan o vi tri i trong danh sach
	next(P.begin(), i - 1)->print();					//hien benh nhan xoa
	P.erase(next(P.begin(), i - 1));
}

void readDataFile(vector<Patient> p, string fileName) {
	string myText;
	ifstream MyReadFile(fileName);
	while (getline(MyReadFile, myText)) {
		string s = myText;
		//if (s.compare("") == 0) return;
		string delim = ",";
		int cnt = 0;

		auto start = 0U;
		auto end = s.find(delim);

		string name;
		string address;
		long long  phone;
		int year;

		while (end != string::npos)
		{
			string value = s.substr(start, end - start);

			if (cnt == 0) name = value;
			if (cnt == 1) address = value;
			if (cnt == 2) phone = stoi(value);
			cnt++;
			start = end + delim.length();
			end = s.find(delim, start);
		}
		string value = s.substr(start, end);
		year = stoi(value);
		p.push_back(Patient(name, address, phone, year));
	}
	MyReadFile.close();
}
int main() {
	int ans = 0;
	//vector<Patient> P;	
	while (ans != 5) {
		system("CLS");
		vector<Patient> P;
		cout << "\t\t\t-------------------";
		cout << "\n\t\tPhong kham uy tin chat luong cuc dinh" << endl;
		cout << "\t\t\t-------------------" << endl;
		int ans;
		bool check = false;
		cout << "\t\tPRESS 1 : Them benh nhan moi" << endl;
		cout << "\n\t\tPRESS 2 : Hien danh sach kham benh" << endl;
		cout << "\n\t\tPRESS 3 : Xoa thong tin benh nhan bi sai" << endl;
		cout << "\n\t\tPRESS 5 : Ket thuc lam viec" << endl;
		cout << "\t\t-----------------------------";

		cout << "\n\n\t\t\tInput:";
		cin >> ans;
		while (cin.fail()) {
			cout << "enter an integer from above choices" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> ans;
		}
		while (!check) {
			if (ans >= 1 && ans <= 5) {
				check = true;
			}
			else {
				try
				{
					throw& ans;
				}
				catch (int* ans)
				{
					cout << "enter valid input:" << endl;
					cin >> *ans;
					while (cin.fail()) {
						cout << "enter an integer from above choices" << endl;
						cin.clear();
						cin.ignore(256, '\n');
						cin >> *ans;
					}
				}
			}
		}
		switch (ans) {
		case 1:
			system("CLS");
			//vector<Patient> P;
			readDataFile(P);
			getPatientList(P);
			sortPatientList(P);
			updateDataFile(P, "queue.txt");
			break;
		case 2:
			system("CLS");
			readDataFile(P);
			showList(P);
			break;
		case 3:
			system("CLS");
			//vector<Patient> P;
			readDataFile(P);
			cout << "Nhap stt benh nhan muon xoa: ";
			int i;
			cin >> i;
			DelPatient(P, i);
			updateDataFile(P, "queue.txt");
			system("pause");
			break;
		case 5:
			cout << "\n\t\tChuc moi nguoi 1 ngay tot lanh!\n\n\n\n";
			break;
		}
		if (ans == 5) break;
		system("pause");
	}
	//saveList(P);
	exit(0);
}


