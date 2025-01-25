#include <iostream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;
int studentsNumber = 4;



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

	void print() const {
		for (int i = 0; i < size; i++)
			cout << arr[i] << ' ';
	}

	void sortByIndex(Student students[]) {
		for (int i = 0; i < studentsNumber; ++i) {
			for (int j = i + 1; j < studentsNumber; ++j) {
				if (students[arr[i]].id < students[arr[j]].id) {
					// Меняем местами индексы в nameIndex
					int temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
	}

	void printStudents(Student students[]) {
		for (int i = 0; i < studentsNumber; i++) {
			students[arr[i]].print();
		}
	}

	~IndexArray() { delete[] arr; }
};

struct Student {
	int id;
	string name;
	int grade;

	void print() {
		cout << "ID: " << id
			<< " Name: " << name
			<< " Grade: " << grade << endl;
	}
};

void inputStudent(Student students[]) {
	Student newStudent;

	cout << "Введите ID студента: ";
	cin >> newStudent.id;

	cout << "Введите ФИО: ";
	cin >> newStudent.name;

	cout << "Введите оценку: ";
	cin >> newStudent.grade;

	students[studentsNumber]=newStudent;
	studentsNumber++;
}

void printStudent(const Student& student) {
	cout << "ID: " << student.id << "	Name: " << student.name << "	Grade: " << "" << student.grade << "\n";
}

void printStudents(Student students[]) {
	for (int i = 0; i < studentsNumber; i++) {
		printStudent(students[i]);
	}
}



int main()
{

	setlocale(LC_ALL, "Russian");

	Student students[MAX_STUDENTS] = {
		{1,"Ave", 2},
		{2,"Bib", 3},
		{3,"Cid", 1},
		{4,"Azi", 0}
	};
	
	IndexArray inds(studentsNumber);
	inds.print();
	/*inds.sortByIndex(students);
	inds.printStudents(students);*/

	//inds.sortByIndex();
	//inds.printStudents();

	//printStudents(students);
	//inputStudent(students);
	//printStudents(students);

	
}