class Student {

    String name;
    String surname;
    int id;
    int matriculationYear;

    void build(String name, String surname, int id, int matriculationYear) {
        this.name = name;
        this.surname = surname;
        this.id = id;
        this.matriculationYear = matriculationYear;
    }

    void printStudentInfo() {
        System.out.println("-- DETTAGLI STUDENTE --");
        System.out.println("Nome: " + this.name);
        System.out.println("Cognome: "+ this.surname);
        System.out.println("Matricola: " + this.id);
        System.out.println("Anno immatricolazione " + this.matriculationYear);
        System.out.println("-----------------------");
    }
}
