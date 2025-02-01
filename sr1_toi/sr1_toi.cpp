#include <iostream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;
int studentsNumber = 5;
bool sortById = true;

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

	void edit() {
		string newName;
		int newGrade;
		int newId;

		cout << "Введите ID студента (или -1, чтобы оставить): ";
		cin >> newId;
		if (newId != -1) {
			id = newId;
		}

		cout << "Введите ФИО (или enter, чтобы оставить): ";
		cin.ignore();
		getline(cin, newName);
		if (!newName.empty()) {
			name = newName;
		}

		cout << "Введите оценку (или -1, чтобы оставить): ";
		cin >> newGrade;
		if (newGrade != -1) {
			grade = newGrade;
		}
	}
};
Student students[MAX_STUDENTS] = {
	{3,"Ave", 2},
	{2,"Bib", 3},
	{1,"Cid", 1},
	{4,"Azi", 0},
	{7, "Lal", 1}
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
		sortById = !sortById;//для создания индФИО
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
					// Меняем местами индексы в nameIndex
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
	cout << "Введите количество студентов для добавления: ";
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
		if (students[studentsNumber-1].id == key) {//проверка последнего
			key = studentsNumber-1;
			return;
		}
		key = -1;
		cout << "\nСтудент не найден\n";
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

int binarySearchByNameIterative(string& key) {
	int left = 0;
	int right = studentsNumber;
	int mid;

	while (left <= right) {
		mid = (left + right) / 2;
		int studentIndex = indexName.arr[mid];

		if (students[studentIndex].name == key) {
			return mid;
		}
		if (students[studentIndex].name > key) {
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


	indexID.deleteIndex(keyId);//добав в струткру студент номер в инд-масс-ах
	indexName.deleteIndex(keyName);
}

int main()
{
	setlocale(LC_ALL, "Russian");

	bool exit = false;
	int choice = 0;
	int subchoice = 0;

	string Name;
	int keyName;
	int key;

	while (!exit) {
		cout<<"Главное меню:\n";
		cout << "1. Добавить студентов\n";
		cout << "2. Вывести список студентов\n";
		cout << "3. Отсортировать список студентов\n";
		cout << "4. Поиск студента по ID\n5. Поиск студента по ФИО\n";
		cin >> choice;

		switch (choice) {
		case 1:
			addStudents();
			break;
		case 2:
			printStudents();
			break;
		case 3:
			cout << "1. Сортировать по возрастанию ID\n2. Сортировать по убыванию ФИО\nВведите команду: ";
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
				cout << "В списке нет студентов: ";
				break;
			}
			cout << "Введите ID студента: ";
			cin >> key;
			binarySearchByIDRecursive(key, 0, studentsNumber);//key для ид
			students[indexID.arr[key]].print();
			if (key > -1) {
				cout << "1. Редактировать запись\n2. Удалить запись\n3. Назад\nВведите команду: ";
				cin >> subchoice;
				if (subchoice == 1) {
					students[indexID.arr[key]].edit();
					indexID.sortByIndex();
				}
				else if (subchoice == 2) {
					keyName = binarySearchByNameIterative(students[indexID.arr[key]].name);//keyName для ИмяИнекс
					deleteStudent(key, keyName);
				}
			}
			break;
		case 5:
			if (studentsNumber == 0) {
				cout << "В списке нет студентов: ";
				break;
			}
			cout << "Введите ФИО студента: ";
			cin >> Name;
			keyName = binarySearchByNameIterative(Name);
			students[indexName.arr[keyName]].print();
			key = students[indexName.arr[keyName]].id;
			if (keyName>-1) {
				cout << "1. Редактировать запись\n2. Удалить запись\n3. Назад\nВведите команду: ";
				cin >> subchoice;
				if (subchoice == 1) {
					students[indexID.arr[key]].edit();
					indexName.sortByIndex();
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
			cout << "Неправильный ввод. Попробуйте еще)\n";
			break;
		}
	}	
}