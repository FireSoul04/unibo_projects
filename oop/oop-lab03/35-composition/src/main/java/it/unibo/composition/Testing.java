package it.unibo.composition;

public class Testing {

    public static void main(final String[] args) {

        // 1)Creare 3 studenti a piacere
        final Student rossi = new Student(1001, "Mario", "Rossi", "sdadsa", 2018);
        final Student bianchi = new Student(1004, "Alberto", "Bianchi", "adjsdjasj", 2021);
        final Student conti = new Student(1005, "Alessandro", "Conti", "xadsda", 2019);

        // 2)Creare 2 docenti a piacere
        final Professor ghini = new Professor(67, "Vittorio", "Ghini", "pippo", new String[]{"Operating systems"});
        final Professor viroli = new Professor(69, "Mirko", "Viroli", "baudo", new String[]{"Object oriented programming"});

        // 3) Creare due aulee di esame, una con 100 posti una con 80 posti
        final ExamRoom lab31 = new ExamRoom(100, "Computer Lab 3.1", true, true);
        final ExamRoom lab22 = new ExamRoom(80, "Computer Lab 2.2", true, false);

        // 4) Creare due esami, uno con nMaxStudents=10, l'altro con
        // nMaxStudents=2
        final Exam os = new Exam(2145, "Operating systems", 100, ghini, lab31);
        final Exam oop = new Exam(3241, "Object oriented programming", 60, viroli, lab22);

        // 5) Iscrivere tutti e 3 gli studenti agli esami
        os.registerStudent(rossi);
        os.registerStudent(bianchi);
        os.registerStudent(conti);
        
        oop.registerStudent(rossi);
        oop.registerStudent(bianchi);
        oop.registerStudent(conti);

        // 6) Stampare in stdout la rapresentazione in stringa dei due esami
        System.out.println(os);
        System.out.println(oop);
    }
}
