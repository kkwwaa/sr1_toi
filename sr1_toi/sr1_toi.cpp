#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

const int MAX_STUDENTS = 100;
int studentsNumber = 10;
bool sortById = true;

string normalize(const string& str) {
	string result = "";
	for (size_t i = 0; i < str.length(); i++) {
		char ch = str[i];

		// �������� � ������� �������� �������
		if (ch >= '�' && ch <= '�') {
			ch = ch + ('a' - 'A');
		}

		// ���������� �������
		if (ch != ' ') {
			result += ch;
		}
	}
	return result;
}

struct Student {
	int id;
	string name;  // ��� � ����� ������
	string submissionDate;
	string reviewDate;
	int gradeReport;
	int gradeDefense;
	string reviewer;
	string seminarist;

	void input() {
		cout << "������� ID ��������: ";
		cin >> id;
		cin.ignore();  // ���������� \n ����� getline
		cout << "������� ���: ";
		getline(cin, name);
		cout << "������� ���� ����� (��.��.����): ";
		cin >> submissionDate;
		cout << "������� ���� �������� (��.��.����): ";
		cin >> reviewDate;
		cout << "������� ������ �� �����: ";
		cin >> gradeReport;
		cout << "������� ������ �� ������: ";
		cin >> gradeDefense;
		cin.ignore();
		cout << "������� ������� ������������: ";
		getline(cin, reviewer);
		cout << "������� ������� �����������: ";
		getline(cin, seminarist);
	}


	void print() {
		cout << "ID: " << id << ", ���: " << name
			<< ", ���� �����: " << submissionDate
			<< ", ���� ��������: " << reviewDate
			<< ", ������ �� �����: " << gradeReport
			<< ", ������ �� ������: " << gradeDefense
			<< ", �����������: " << reviewer
			<< ", ����������: " << seminarist << endl;
	}


	void edit() {
		string newName, newSubmissionDate, newReviewDate, newReviewer, newSeminarist;
		int newId, newGradeReport, newGradeDefense;

		cout << "������� ����� ID (��� -1, ����� ��������): ";
		cin >> newId;
		if (newId != -1) id = newId;

		cin.ignore();
		cout << "������� ����� ��� (��� enter, ����� ��������): ";
		getline(cin, newName);
		if (!newName.empty()) name = newName;

		cout << "������� ����� ���� ����� (��� enter, ����� ��������): ";
		getline(cin, newSubmissionDate);
		if (!newSubmissionDate.empty()) submissionDate = newSubmissionDate;

		cout << "������� ����� ���� �������� (��� enter, ����� ��������): ";
		getline(cin, newReviewDate);
		if (!newReviewDate.empty()) reviewDate = newReviewDate;

		cout << "������� ����� ������ �� ����� (��� -1, ����� ��������): ";
		cin >> newGradeReport;
		if (newGradeReport != -1) gradeReport = newGradeReport;

		cout << "������� ����� ������ �� ������ (��� -1, ����� ��������): ";
		cin >> newGradeDefense;
		if (newGradeDefense != -1) gradeDefense = newGradeDefense;

		cin.ignore();
		cout << "������� ����� ������� ������������ (��� enter, ����� ��������): ";
		getline(cin, newReviewer);
		if (!newReviewer.empty()) reviewer = newReviewer;

		cout << "������� ����� ������� ����������� (��� enter, ����� ��������): ";
		getline(cin, newSeminarist);
		if (!newSeminarist.empty()) seminarist = newSeminarist;
	}

	bool operator<(const Student& other) const {
		if (sortById) {
			return id < other.id; // ��������� �� id
		}
		else {
			return normalize(name) > normalize(other.name); // ��������� �� name (�� ��������)
		}
	}
};
Student students[MAX_STUDENTS] = {
	{3, "�������� ��������� ���������", "27.11.2024", "03.12.2024", 6, 9, "���������", "�����"},
	{5, "����� ����� ����������", "01.12.2024", "10.12.2024", 4, 6, "���������", "���������"},
	{9, "��������� ������ ��������", "01.12.2024", "10.12.2024", 6, 8, "�����", "���������"},
	{10, "������� ������ �������", "01.12.2024", "10.12.2024", 0, 0, "���������", "�����"},
	{1, "������ ������� ����������", "25.11.2024", "30.11.2024", 7, 9, "���������", "���������"},
	{8, "�������� ������� ����������", "25.11.2024", "05.12.2024", 8, 8, "�����", "���������"},
	{2, "������� ������� �������������", "25.11.2024", "30.11.2024", 5, 8, "���������", "�����"},
	{6, "������� ����� ������������", "25.11.2024", "01.12.2024", 8, 8, "�����", "���������"},
	{4, "������ ����� �������", "28.11.2024", "03.12.2024", 2, 9, "���������", "���������"},
	{7, "����� ���� ������������", "25.11.2024", "01.12.2024", 7, 7, "�����", "���������"}
};

struct IndexArray {
	int* arr;
	int size;

	IndexArray(int size) {
		this->size = size;
		arr = new int[size];
		for (int i = 0; i < size; i++) {
			arr[i] = i;
		}
		sortByIndex();
		sortById = !sortById;//��� �������� ������
	}

	void addIndex() {
		int* newArr = new int[size+1];
		int i = 0;
		while (i < size && students[arr[i]] < students[size]) {
			newArr[i] = arr[i];
			i++;
		}
		newArr[i] = size;
		while (i < studentsNumber) {
			newArr[i + 1] = arr[i];
			i++;
		}

		delete[] arr;
		arr = newArr;
		size = studentsNumber;
	}

	void deleteIndex(int key) {
		size=studentsNumber;
		int* newArr = new int[size];
		int i = 0;

		while (i < key) {
			if (arr[i] < arr[key]) newArr[i] = arr[i];
			else newArr[i] = arr[i] - 1;
			i++;
		}
		while (i < size) {
			if (arr[i+1] < arr[key]) newArr[i] = arr[i + 1];
			else  newArr[i] = arr[i + 1] - 1;
			i++;
		}

		delete[] arr;
		arr = newArr;
	}

	void printStudents() {
		for (int i = 0; i < studentsNumber; i++) {
			students[arr[i]].print();
		}
	}

	void sortByIndex() {
		for (int i = 0; i < studentsNumber; ++i) {
			for (int j = i + 1; j < studentsNumber; ++j) {
				if (students[arr[j]] < students[arr[i]]) {
					// ������ ������� ������� � nameIndex
					int temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
	}

	~IndexArray() { delete[] arr; }
};
IndexArray indexID(studentsNumber);
IndexArray indexName(studentsNumber);

void printStudents() {
	for (int i = 0; i < studentsNumber; i++) {
		students[i].print();
	}
}

void addStudents() {
	int number = 0;
	cout << "������� ���������� ��������� ��� ����������: ";
	cin >> number;
	for (int i = 0; i < number; i++) {
		students[studentsNumber].input();
		studentsNumber++;
		sortById = true;
		indexID.addIndex();
		sortById = false;
		indexName.addIndex();
	}
}

void binarySearchByIDRecursive(int& key, int left, int right) {
	int mid = (left + right) / 2;
	if (left>right) {
		if (students[studentsNumber-1].id == key) {//�������� ����������
			key = studentsNumber-1;
			return;
		}
		key = -1;
		cout << "\n������� �� ������\n";
		return;
	}
	int studentIndex = indexID.arr[mid];

	if (students[studentIndex].id == key) {
		key = mid;
		return;
	}
	if (students[studentIndex].id < key) {
		binarySearchByIDRecursive(key, mid + 1, right);
	}
	else {
		binarySearchByIDRecursive(key, left, mid - 1);
	}
}

int binarySearchByNameIterative(string key) {
	key = normalize(key); // �������� ���� � ����������� ����

	int left = 0;
	int right = studentsNumber - 1;
	int mid;

	while (left <= right) {
		mid = (left + right) / 2;
		int studentIndex = indexName.arr[mid];

		string studentName = normalize(students[studentIndex].name); // �������� ��� � ����������� ����

		if (studentName == key) {
			return mid;
		}
		if (studentName > key) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return -1;
}

void deleteStudent(int keyId, int keyName) {
	int i = indexName.arr[keyName];
	studentsNumber--;
	while (i < studentsNumber) {
		students[i] = students[i+1];
		i++;
	}


	indexID.deleteIndex(keyId);//����� � �������� ������� ����� � ���-����-��
	indexName.deleteIndex(keyName);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	bool exit = false;
	int choice = 0;
	int subchoice = 0;

	string Name;
	int keyName;
	int key;

	while (!exit) {
		cout<<"������� ����:\n";
		cout << "1. �������� ���������\n";
		cout << "2. ������� ������ ���������\n";
		cout << "3. ������������� ������ ���������\n";
		cout << "4. ����� �������� �� ID\n5. ����� �������� �� ���\n6. �����\n������� �������: ";
		cin >> choice;

		switch (choice) {
		case 1:
			addStudents();
			break;
		case 2:
			printStudents();
			break;
		case 3:
			cout << "1. ����������� �� ����������� ID\n2. ����������� �� �������� ���\n������� �������: ";
			cin >> subchoice;
			if (subchoice == 1) {
				indexID.printStudents();
			}
			else {
				indexName.printStudents();
			}
			break;
		case 4:
			if (studentsNumber == 0) {
				cout << "� ������ ��� ���������: ";
				break;
			}
			cout << "������� ID ��������: ";
			cin >> key;
			binarySearchByIDRecursive(key, 0, studentsNumber);//key ��� ��
			
			if (key > -1) {
				students[indexID.arr[key]].print();
				cout << "1. ������������� ������\n2. ������� ������\n3. �����\n������� �������: ";
				cin >> subchoice;
				if (subchoice == 1) {
					students[indexID.arr[key]].edit();
					sortById = true;
					indexID.sortByIndex();
					sortById = false;
					indexName.sortByIndex();
				}
				else if (subchoice == 2) {
					keyName = binarySearchByNameIterative(students[indexID.arr[key]].name);//keyName ��� ��������
					deleteStudent(key, keyName);
				}
			}
			break;
		case 5:
			if (studentsNumber == 0) {
				cout << "� ������ ��� ���������: ";
				break;
			}
			cout << "������� ��� ��������: ";
			cin.ignore();
			getline(cin, Name);
			keyName = binarySearchByNameIterative(Name);
			if (keyName>-1) {
				students[indexName.arr[keyName]].print();
				cout << "1. ������������� ������\n2. ������� ������\n3. �����\n������� �������: ";
				cin >> subchoice;
				if (subchoice == 1) {
					students[indexName.arr[keyName]].edit();
					sortById = false;
					indexName.sortByIndex();
					sortById = true;
					indexID.sortByIndex();
				}
				else if (subchoice==2){
					binarySearchByIDRecursive(key, 0, studentsNumber);
					deleteStudent(key,keyName);
				}
			}
			break;

		case 6:
			exit = true;
			break;
		default:
			cout << "������������ ����. ���������� ���)\n";
			break;
		}
	}	
}