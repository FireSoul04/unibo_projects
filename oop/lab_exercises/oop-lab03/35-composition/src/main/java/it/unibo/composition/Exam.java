package it.unibo.composition;

import java.io.*;
import java.util.*;

public class Exam {
    
    private final int id;
    private final String courseName;
    private final int maxStudents;

    private int registeredStudents;
    private Professor professor;
    private ExamRoom room;
    private Student[] students;

    public Exam(
        final int id,
        final String courseName,
        final int maxStudents,
        final Professor professor,
        final ExamRoom room
    ) {
        this.id = id;
        this.courseName = courseName;
        this.maxStudents = maxStudents;
        this.professor = professor;
        this.room = room;
        this.students = new Student[maxStudents];
    }

    public final int getId() {
        return this.id;
    }

    public final String getCourseName() {
        return this.courseName;
    }

    public final int getMaxStudents() {
        return this.maxStudents;
    }

    public final int getRegisteredStudents() {
        return this.registeredStudents;
    }
    
    public final Professor getProfessor() {
        return this.professor;
    }

    public final ExamRoom getRoom() {
        return this.room;
    }

    public final Student[] getStudents() {
        return this.students;
    }

    public void registerStudent(final Student student) {
        if (this.registeredStudents < this.maxStudents) {
            this.students[this.registeredStudents++] = student; 
            System.out.println("Student " + student.getId() + " added successfully");
        } else {
            System.out.println("Max registered students reached");
        }
    }

    public final String toString() {
        return "Exam ["
            + "name=" + this.courseName 
            + ", professor=" + this.professor.getFullname()
            + ", id=" + this.id
            + ", exam room=" + this.room.getDescription()
            + ", number of registered students=" + this.registeredStudents
            + ", max students=" + this.maxStudents
            + ", registered students=" + Arrays.toString(this.students)
            + "]";
    }
}