class TestStudent {

    public static void main(String[] args) {
        Student studentOne = new Student();
        Student studentTwo = new Student();
        Student studentThree = new Student();

        studentOne.build("Alex", "Balducci", 1015, 2019);
        studentTwo.build("Angel", "Bianchi", 1016, 2018);
        studentThree.build("Andrea", "Bracci", 1017, 2017);
        
        studentTwo.printStudentInfo();
        studentOne.printStudentInfo();
        studentThree.printStudentInfo();
    }
}
