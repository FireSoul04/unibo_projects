package it.unibo.tostring;

public class AccountHolder {

    private final String name;
    private final String surname;
    private final int userID;

    public AccountHolder(final String name, final String surname, final int accountID) {
        this.name = name;
        this.surname = surname;
        this.userID = accountID;
    }

    public String getName() {
        return this.name;
    }

    public String getSurname() {
        return this.surname;
    }

    public int getUserID() {
        return this.userID;
    }

    public String toString() {
        return "Name = " + this.name + 
            ", surname = " + this.surname + 
            ", ID = " + this.userID;
    }

    public static void main(final String[] args) {
        System.out.println(new AccountHolder("Alex", "Ghini", 42).toString());
    }
}
