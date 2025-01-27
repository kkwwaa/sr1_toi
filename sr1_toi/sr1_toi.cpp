#include <iostream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;
int studentsNumber = 4;
bool sortById = true;

struct Student {
	int id;
	string name;
	int grade;

	void input() {
		cout << "������� ID ��������: ";
		cin >> id;

		cout << "������� ���: ";
		cin >> name;

		cout << "������� ������: ";
		cin >> grade;
	}

	void print() {
		cout << "ID: " << id
			<< " Name: " << name
			<< " Grade: " << grade << endl;
	}

	void edit() {
		string newName;
		int newGrade;
		int newId;

		cout << "������� ID �������� (��� -1, ����� ��������): ";
		cin >> newId;
		if (newId != -1) {
			id = newId;
		}

		cout << "������� ��� (��� enter, ����� ��������): ";
		cin.ignore();
		getline(cin, newName);
		if (!newName.empty()) {
			name = newName;
		}

		cout << "������� ������ (��� -1, ����� ��������): ";
		cin >> newGrade;
		if (newGrade != -1) {
			grade = newGrade;
		}
	}

	// �������� ���������
	bool operator<(const Student& other) const {
		if (sortById) {
			return id < other.id; // ��������� �� id
		}
		else {
			return name > other.name; // ��������� �� name (�� ��������)
		}
	}
};
Student students[MAX_STUDENTS] = {
	{3,"Ave", 2},
	{2,"Bib", 3},
	{1,"Cid", 1},
	{4,"Azi", 0}
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

	void print() {
		for (int i = 0; i < size; i++)
			cout << arr[i] << ' ';
	}

	void addIndex() {

		/*cout << endl;
		for (int i = 0; i < size; i++) cout << arr[i] << ' ';*/

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
			if (arr[i] < arr[key]) newArr[i] = arr[i + 1];
			else {
				if (arr[i + 1] < arr[key]) newArr[i] = arr[i + 1];
				else newArr[i] = arr[i + 1] - 1;
			}
			i++;
		}

		delete[] arr;
		arr = newArr;
	}

	void edit(int key) {
		int* newArr = new int[size];
		int i = 0;

		while (i < size && students[arr[i]] < students[arr[key]] ) {
			newArr[i] = arr[i];
			i++;
		}
		i++;
		while (i < size && students[arr[i]] < students[arr[key]]) {
			newArr[i - 1] = arr[i];
			i++;
		}
		newArr[i - 1] = arr[key];
		while (i < size) {
			newArr[i] = arr[i];
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
	int mid = left + right / 2;
	if (left>right) {
		if (students[studentsNumber-1].id == key) {//�������� ����������
			key = studentsNumber-1;
			cout << endl << key << endl;
			return;
		}
		key = -1;
		cout << "\n������� �� ������\n";
		return;
	}
	int studentIndex = indexID.arr[mid];

	if (students[studentIndex].id == key) {
		students[studentIndex].print();
		key = mid;
		cout << endl << key << endl;
		return;
	}
	if (students[studentIndex].id < key) {
		binarySearchByIDRecursive(key, mid + 1, right);
	}
	else {
		binarySearchByIDRecursive(key, left, mid - 1);
	}
}

void deleteStudent(int key) {
	int i = key;
	studentsNumber--;
	while (i < studentsNumber) {
		students[i] = students[i+1];
		i++;
	}
}



int main()
{
	setlocale(LC_ALL, "Russian");

	bool exit = false;
	int choice = 0;
	int subchoice = 0;

	while (!exit) {
		cout<<"������� ����:\n";
		cout << "1. �������� ���������\n";
		cout << "2. ������� ������ ���������\n";
		cout << "3. ������������� ������ ���������\n";
		cout << "4. ����� �������� �� ID\n";
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
			int key;
			cout << "������� ID ��������: ";
			cin >> key;
			binarySearchByIDRecursive(key, 0, studentsNumber);
			if (key > -1) {
				cout << "1. ������������� ������\n2. ������� ������\n������� �������: ";
				cin >> subchoice;
				if (subchoice == 1) {
					students[indexID.arr[key]].edit();
					indexID.edit(key);
				}
				else {
					deleteStudent(indexID.arr[key]);
					indexID.deleteIndex(key);
				}
			}
			break;
		case 5:
			exit = true;
			break;
		default:
			cout << "������������ ����. ���������� ���)\n";
			break;
		}
	}
	
	//��� ����� ��� ����, ���-�� � ����-��

	
}