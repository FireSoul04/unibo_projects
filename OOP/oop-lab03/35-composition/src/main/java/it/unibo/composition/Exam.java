package it.unibo.composition;

public class Exam {
    
    private final int id;
    private final String courseName;
    private final int maxStudents;

    private int registeredStudents;
    private Professor professor;
    private ExamRoom room;
    private Student[] students;

    public Exam(final int id, final String courseName, final int maxStudents, final int registeredStudents, final Professor professor, final ExamRoom room) {
        this.id = id;
        this.courseName = courseName;
        this.maxStudents = maxStudents;
        this.registeredStudents = registeredStudents;
        this.professor = professor;
        this.room = room;
    }

    public final int getId() {
        return id;
    }

    public final String getCourseName() {
        return courseName;
    }

    public final int getMaxStudents() {
        return maxStudents;
    }

    public final int getRegisteredStudents() {
        return registeredStudents;
    }
    
    public final Professor getProfessor() {
        return professor;
    }

    public final ExamRoom getRoom() {
        return room;
    }

    public final Student[] getStudents() {
        return students;
    }

    public void setStudents(final Student[] students) {
        this.students = students;
        registeredStudents = students.length;
    }
}