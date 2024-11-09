package it.unibo.encapsulation.interfaces;

public class StrictBankAccount implements BankAccount {
    private static final double ATM_TRANSACTION_FEE = 1;

    private final int id;

    private double balance;
    private int transactions;

    public StrictBankAccount(final int id, final double balance) {
        this.id = id;
        this.balance = balance;
    }

    public int getid() {
        return this.id;
    }

    public double getBalance() {
        return this.balance;
    }

    public int getTransactionsCount() {
        return this.transactions;
    }

    public void deposit(final int id, final double amount) {
        if (this.id == id) {
            transactions++;
            balance = balance + amount;
            System.out.println("Deposited " + amount + " with success");
        } else {
            System.out.println("User id doesn't correspond!");
        }
    }

    public void withdraw(final int id, final double amount) {
        if (this.id == id) {
            transactions++;
            if (balance - amount >= 0.0) {
                balance = balance - amount;
                System.out.println("Withdrawn " + -amount + " with success");
            } else {
                System.out.println("Cannot withdraw, not enough in balance!");
            }
        } else {
            System.out.println("User id doesn't correspond!");
        }
    }

    public void depositFromATM(final int id, final double amount) {
        if (this.id == id) {
            transactions++;
            balance = balance + amount - ATM_TRANSACTION_FEE;
            System.out.println("Deposited " + (amount - ATM_TRANSACTION_FEE) + " with success");
        } else {
            System.out.println("User id doesn't correspond!");
        }
    }

    public void withdrawFromATM(final int id, final double amount) {
        if (this.id == id) {
            transactions++;
            if (balance - amount - ATM_TRANSACTION_FEE >= 0.0) {
                balance = balance - amount - ATM_TRANSACTION_FEE;
                System.out.println("Withdrawn " + (-amount - ATM_TRANSACTION_FEE) + " with success");
            } else {
                System.out.println("Cannot withdraw, not enough in balance!");
            }
        } else {
            System.out.println("User id doesn't correspond!");
        }
    }

    public void chargeManagementFees(final int id) {
        /*
         * Riduce il bilancio del conto di un ammontare pari alle spese di gestione
         */
        if (this.id == id) {
            balance = balance - (5 + 0.1 * transactions);
            System.out.println("Fees managed successfully");
        } else {
            System.out.println("User id doesn't correspond!");
        }
    }

    public String toString() {
        return "User ID = " + this.id +
            "\nTotal transactions = " + this.transactions +
            "\nTotal balance = " + this.balance;
    }
}
