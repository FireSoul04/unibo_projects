#include <iostream>

using namespace std;

class Student {
    private:
        string name;
        string surname;
        int age;
    public:
        Student(string name, string surname, int age) {
            this->name = name;
            this->surname = surname;
            this->age = age;
        }
        string getFullName() {
            return name;
        }
};

int main() {
    Student s = Student("Davide", "Mancini", 19);
    cout << s.getFullName();

    return 0;
}