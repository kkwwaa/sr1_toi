#include <iostream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;
int studentsNumber = 4;

struct Student {
	int id;
	string name;
	int grade;

	void input() {
		cout << "Введите ID студента: ";
		cin >> id;

		cout << "Введите ФИО: ";
		cin >> name;

		cout << "Введите оценку: ";
		cin >> grade;
	}

	void print() {
		cout << "ID: " << id
			<< " Name: " << name
			<< " Grade: " << grade << endl;
	}
};
Student students[MAX_STUDENTS] = {
	{1,"Ave", 2},
	{2,"Bib", 3},
	{3,"Cid", 1},
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
	}

	void print() {
		for (int i = 0; i < size; i++)
			cout << arr[i] << ' ';
	}

	void addIndex() {
		int* newArr = new int[size+1];
		int i = 0;
		while (i < size && students[arr[i]].id < students[size].id) {
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
		size--;
		int* newArr = new int[size];
		int i = 0;
		while (i < key) {
			if (arr[i] > arr[key]) newArr[i] = arr[i] - 1;
			else newArr[i] = arr[i];
			i++;
		}
		while (i < size) {
			if (arr[i+1] > arr[key]) newArr[i] = arr[i+1] - 1;
			else newArr[i] = arr[i];
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

	~IndexArray() { delete[] arr; }
};
IndexArray inds(studentsNumber);

void printStudents() {
	for (int i = 0; i < studentsNumber; i++) {
		students[i].print();
	}
}

void addStudents() {
	int number = 0;
	cout << "Введите количество студентов для добавления: ";
	cin >> number;
	for (int i = 0; i < number; i++) {
		students[studentsNumber].input();
		studentsNumber++;
		inds.addIndex();
	}
}

void binarySearchByIDRecursive(int& key, int left, int right) {
	int mid = left + (right - left) / 2;
	if (mid>=studentsNumber || left>right) {
		key = -1;
		cout << "\nСтудент не найден\n";
		return;
	}
	int studentIndex = inds.arr[mid];

	if (students[studentIndex].id == key) {
		students[studentIndex].print();
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

	while (!exit) {
		cout<<"Главное меню:\n";
		cout << "1. Добавить студентов\n";
		cout << "2. Вывести список студентов\n";
		cout << "3. Список студентов по возрастанию ID\n";
		cout << "4. Поиск студента по ID\n";
		cin >> choice;

		switch (choice) {
		case 1:
			addStudents();
			break;
		case 2:
			printStudents();
			break;
		case 3:
			inds.printStudents();
			break;
		case 4:
			int key;
			cout << "Введите ID студента: ";
			cin >> key;
			binarySearchByIDRecursive(key, 0, studentsNumber);
			if (key > -1) {
				int subchoice = 0;
				cout << "1. Редактировать запись\n2. Удалить запись\nВведите команду: ";
				cin >> subchoice;
				if (subchoice == 1) {

				}
				else {
					deleteStudent(inds.arr[key]);
					inds.deleteIndex(key);
				}
			}
			break;
		case 5:
			exit = true;
			break;
		default:
			cout << "Неправильный ввод. Попробуйте еще)\n";
			break;
		}
	}
	
	//inds.sortByIndex();
	//inds.printStudents();

	//printStudents(students);
	//inputStudent(students);
	//printStudents(students);

	
}