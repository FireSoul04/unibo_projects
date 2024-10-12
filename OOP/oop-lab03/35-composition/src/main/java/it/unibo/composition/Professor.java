package it.unibo.composition;

public class Professor implements User {
    
    private final int id;
    private final String name;
    private final String surname;
    private String password;
    private String[] courses;

    public Professor(
        final int id,
        final String name,
        final String surname,
        final String password,
        final String[] courses
    ) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.password = password;
        this.courses = courses;
    }

    public void replaceCourse(final String courseName, final int index) {
        for (int i = 0; i < courses.length; i++) {
            if (index == i) {
                courses[i] = courseName;
            }
        }
    }

    public void replaceAllCourses(final String[] newCourses) {
        courses = newCourses;
    }

    public String toString() {
        return "Professor ["
            + "name=" + this.name
            + ", surname=" + this.surname
            + ", id=" + this.id
            + ", courses=" + Array.toString(this.courses)
            + "]";
    }

    public final String getUsername() {
        return name;
    }

    public final String getPassword() {
        return password;
    }

    public final String getDescription() {
        return this.toString();
    }
}
