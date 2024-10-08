package it.unibo.encapsulation;

public class Student {

    private final String name;
    private final String surname;
    private final int id;
    private final int matriculationYear;

    public Student(final int id, final String name, final String surname, final int matriculationYear) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.matriculationYear = matriculationYear;
    }

    public String getName() {
        return name;
    }

    public String getSurname() {
        return surname;
    }

    public int getId() {
        return id;
    }

    public int getMatriculationYear() {
        return matriculationYear;
    }

    public void printStudentInfo() {
        System.out.println("Student id: " + this.getId());
        System.out.println("Student name: " + this.getName());
        System.out.println("Student surname: " + this.getSurname());
        System.out.println("Student matriculationYear: " + this.getMatriculationYear() + "\n");
    }

    public static void main(String[] args) {
        Student st1 = new Student(20, "Mario", "Rossi", 2015);
        st1.printStudentInfo();
    }
}
