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

		// Приводим к нижнему регистру вручную
		if (ch >= 'А' && ch <= 'Я') {
			ch = ch + ('a' - 'A');
		}

		// Пропускаем пробелы
		if (ch != ' ') {
			result += ch;
		}
	}
	return result;
}

struct Student {
	int id;
	string name;  // ФИО в одной строке
	string submissionDate;
	string reviewDate;
	int gradeReport;
	int gradeDefense;
	string reviewer;
	string seminarist;

	void input() {
		cout << "Введите ID студента: ";
		cin >> id;
		cin.ignore();  // Игнорируем \n перед getline
		cout << "Введите ФИО: ";
		getline(cin, name);
		cout << "Введите дату сдачи (ДД.ММ.ГГГГ): ";
		cin >> submissionDate;
		cout << "Введите дату проверки (ДД.ММ.ГГГГ): ";
		cin >> reviewDate;
		cout << "Введите оценку за отчет: ";
		cin >> gradeReport;
		cout << "Введите оценку за защиту: ";
		cin >> gradeDefense;
		cin.ignore();
		cout << "Введите фамилию проверяющего: ";
		getline(cin, reviewer);
		cout << "Введите фамилию семинариста: ";
		getline(cin, seminarist);
	}


	void print() {
		cout << "ID: " << id << ", ФИО: " << name
			<< ", Дата сдачи: " << submissionDate
			<< ", Дата проверки: " << reviewDate
			<< ", Оценка за отчет: " << gradeReport
			<< ", Оценка за защиту: " << gradeDefense
			<< ", Проверяющий: " << reviewer
			<< ", Семинарист: " << seminarist << endl;
	}


	void edit() {
		string newName, newSubmissionDate, newReviewDate, newReviewer, newSeminarist;
		int newId, newGradeReport, newGradeDefense;

		cout << "Введите новый ID (или -1, чтобы оставить): ";
		cin >> newId;
		if (newId != -1) id = newId;

		cin.ignore();
		cout << "Введите новое ФИО (или enter, чтобы оставить): ";
		getline(cin, newName);
		if (!newName.empty()) name = newName;

		cout << "Введите новую дату сдачи (или enter, чтобы оставить): ";
		getline(cin, newSubmissionDate);
		if (!newSubmissionDate.empty()) submissionDate = newSubmissionDate;

		cout << "Введите новую дату проверки (или enter, чтобы оставить): ";
		getline(cin, newReviewDate);
		if (!newReviewDate.empty()) reviewDate = newReviewDate;

		cout << "Введите новую оценку за отчет (или -1, чтобы оставить): ";
		cin >> newGradeReport;
		if (newGradeReport != -1) gradeReport = newGradeReport;

		cout << "Введите новую оценку за защиту (или -1, чтобы оставить): ";
		cin >> newGradeDefense;
		if (newGradeDefense != -1) gradeDefense = newGradeDefense;

		cin.ignore();
		cout << "Введите новую фамилию проверяющего (или enter, чтобы оставить): ";
		getline(cin, newReviewer);
		if (!newReviewer.empty()) reviewer = newReviewer;

		cout << "Введите новую фамилию семинариста (или enter, чтобы оставить): ";
		getline(cin, newSeminarist);
		if (!newSeminarist.empty()) seminarist = newSeminarist;
	}

	bool operator<(const Student& other) const {
		if (sortById) {
			return id < other.id; // Сравнение по id
		}
		else {
			return normalize(name) > normalize(other.name); // Сравнение по name (по убыванию)
		}
	}
};
Student students[MAX_STUDENTS] = {
	{3, "Борисова Екатерина Андреевна", "27.11.2024", "03.12.2024", 6, 9, "Долныкова", "Будин"},
	{5, "Дуров Павел Валерьевич", "01.12.2024", "10.12.2024", 4, 6, "Долныкова", "Цидвинцев"},
	{9, "Косвинцев Богдан Павлович", "01.12.2024", "10.12.2024", 6, 8, "Осока", "Цидвинцев"},
	{10, "Никитин Никита Никитич", "01.12.2024", "10.12.2024", 0, 0, "Долныкова", "Будин"},
	{1, "Петров Арсений Николаевич", "25.11.2024", "30.11.2024", 7, 9, "Долныкова", "Цидвинцев"},
	{8, "Понькина Татьяна Евгеньевна", "25.11.2024", "05.12.2024", 8, 8, "Осока", "Цидвинцев"},
	{2, "Семенов Евгений Александрович", "25.11.2024", "30.11.2024", 5, 8, "Долныкова", "Будин"},
	{6, "Симонов Антон Владимирович", "25.11.2024", "01.12.2024", 8, 8, "Осока", "Цидвинцев"},
	{4, "Юрьева София Юрьевна", "28.11.2024", "03.12.2024", 2, 9, "Долныкова", "Цидвинцев"},
	{7, "Янина Анна Владимировна", "25.11.2024", "01.12.2024", 7, 7, "Осока", "Цидвинцев"}
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

int binarySearchByNameIterative(string key) {
	key = normalize(key); // Приводим ключ к нормальному виду

	int left = 0;
	int right = studentsNumber - 1;
	int mid;

	while (left <= right) {
		mid = (left + right) / 2;
		int studentIndex = indexName.arr[mid];

		string studentName = normalize(students[studentIndex].name); // Приводим имя к нормальному виду

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


	indexID.deleteIndex(keyId);//добав в струткру студент номер в инд-масс-ах
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
		cout<<"Главное меню:\n";
		cout << "1. Добавить студентов\n";
		cout << "2. Вывести список студентов\n";
		cout << "3. Отсортировать список студентов\n";
		cout << "4. Поиск студента по ID\n5. Поиск студента по ФИО\n6. Выход\nВведите команду: ";
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
			
			if (key > -1) {
				students[indexID.arr[key]].print();
				cout << "1. Редактировать запись\n2. Удалить запись\n3. Назад\nВведите команду: ";
				cin >> subchoice;
				if (subchoice == 1) {
					students[indexID.arr[key]].edit();
					sortById = true;
					indexID.sortByIndex();
					sortById = false;
					indexName.sortByIndex();
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
			cin.ignore();
			getline(cin, Name);
			keyName = binarySearchByNameIterative(Name);
			if (keyName>-1) {
				students[indexName.arr[keyName]].print();
				cout << "1. Редактировать запись\n2. Удалить запись\n3. Назад\nВведите команду: ";
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
			cout << "Неправильный ввод. Попробуйте еще)\n";
			break;
		}
	}	
}