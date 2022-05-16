#pragma warning (disable : 4996) 
#include<iostream>
#include<string>
#include<stdio.h>
#include<fstream>
#include <vector>
#include<ctime>

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
	string disease;
public:
	Patient() :Person() {
		year = 0;
		disease = "";
	}
	Patient(string name, string address, long long phone, int year) :Person(name, address, phone) {
		this->year = year;
	}
	void set() {
		cin.ignore(1);
		cout << "\t\tEnter Name:";
		getline(cin, name);

		cout << "\n\t\tEnter address:";
		cin.ignore(1);
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
	void setDisease(string b) {
		disease = b;
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
	string getDisease() {
		return disease;
	}
	string getInfo() {
		string info = name + "," + address + "," + to_string(phone) + "," + to_string(year);
		return info;
	}

	void print() {
		cout << "\n" << "\t\t" << name << "\t\t\t\t";
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
void khamBenh(vector<Patient>& P, vector<Patient>& Pdone) {
	if (P.size()==0) {						//xac dinh co danh sach nao k
		cout << "Loi: khong co benh nhan.";
		return;
	}
	string b;
	cout << "Benh nhan: " << P.at(0).getInfo() << endl;	//lay thong tin benh nhan dau hang cho
	cout << "Benh: ";
	cin.ignore();
	getline(cin, b);
	P.at(0).setDisease(b);
	Pdone.push_back(P.at(0));						//luu thong tin benh nhan da kham xong nay 
	P.erase(next(P.begin(), 0));					//xoa benh nhan da kham xong khoi queue
}
//update data sau khi kham xong 1 patient
void updateDataFile(vector<Patient>& P, string filename) {
	ofstream update;
	update.open(filename);
	for (int i = 0; i < P.size(); i++) {
		update << P.at(i).getInfo() ;
		if (i != P.size() - 1) {
			update << "\n";
		}
	}
	update.close();
}

void showList(vector<Patient>& P) {
	if (!P.size()) {
		cout << "\t\t\t\tChua co benh nhan nao\n\n\n\n\n\n" << endl;
	}
	else {
		for (size_t i = 0; i < P.size(); i++)
			//show priority patient
			if (P.at(i).age() < 2 || P.at(i).age() > 79) {
				P.at(i).print();
				cout << "(uu tien)";
			}
			else P.at(i).print();		//show patient
	}
}
//luu danh sach da kham
void saveList(vector<Patient>& P, string filename) {
	ofstream ofs;
	ofs.open(filename, ios::out | ios::app);
	char b = '"';
	if (!ofs) {
		cout << "Loi: file khong mo duoc.";
		return;
	}
	// current date/time based on current system
	time_t now = time(0);
	// convert sang string
	char* dt = ctime(&now);
	//nhập ngày tháng vào file lưu trữ
	ofs << "\n" << dt << endl;	
	for (size_t i = 0; i < P.size(); i++) {
		ofs << P.at(i).getInfo() << "," << P.at(i).getDisease() << endl;
	}
}
int main() {
	vector<Patient> Pdone;
	int ans = 0;
	while (ans != 5) {
		vector<Patient> P;
		//vector<Patient> Pdone;
		system("CLS");
		cout << "\t\t\t-------------------";
		cout << "\n\t\tPhong kham uy tin chat luong cuc dinh" << endl;
		cout << "\t\t\t-------------------" << endl;
		int ans;
		bool check = false;
		cout << "\t\tPRESS 1 : Benh nhan tiep theo" << endl;
		cout << "\n\t\tPRESS 2 : Hien danh sach kham benh" << endl;		
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
			readDataFile(P);			
			khamBenh(P, Pdone);
			updateDataFile(P, "queue.txt");			
			break;
		case 2:
			system("CLS");
			readDataFile(P);
			showList(P);
			//cout << "\n";
			break;
		case 5:
			cout << "\n\t\tChuc moi nguoi 1 ngay tot lanh!\n\n\n\n";
			//updateDataFile(Pdone, "Text.txt");
			break;
		}
		if (ans == 5) break;
		system("pause");		
	}
	
	saveList(Pdone, "Text.txt");
		//ket thuc buoi kham, luu danh sach da kham
	
	return 0;
}