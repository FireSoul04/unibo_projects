package it.unibo.inheritance.impl;
import it.unibo.inheritance.api.AccountHolder;
import it.unibo.inheritance.api.BankAccount;

public abstract class AbstractBankAccount implements BankAccount {

    protected static final double ATM_TRANSACTION_FEE = 1;
    protected static final double MANAGEMENT_FEE = 5;

    private final AccountHolder holder; 
    private double balance;
    private int transactions;

    public AbstractBankAccount(final AccountHolder accountHolder, final double balance) {
        this.holder = accountHolder;
        this.balance = balance;
        this.transactions = 0;
    }

    public void chargeManagementFees(final int id) {
        if (checkUser(id)) {
            this.balance -= SimpleBankAccount.MANAGEMENT_FEE;
        }
    }

    public void deposit(final int id, final double amount) {
        this.transactionOp(id, amount);
    }

    public void depositFromATM(final int id, final double amount) {
        this.deposit(id, amount - SimpleBankAccount.ATM_TRANSACTION_FEE);
    }

    public double getBalance() {
        return this.balance;
    }

    protected void setBalance(final double balance) {
        this.balance = balance;
    }

    public int getTransactionsCount() {
        return this.transactions;
    }

    public AccountHolder getAccountHolder() {
        return holder;
    }

    public void withdraw(final int id, final double amount) {
        if (isWithDrawAllowed(amount)) {
            this.transactionOp(id, -amount);
        }
    }

    public void withdrawFromATM(final int id, final double amount) {
        this.withdraw(id, amount + SimpleBankAccount.ATM_TRANSACTION_FEE);
    }

    protected boolean checkUser(final int id) {
        return this.holder.getUserID() == id;
    }

    protected void incrementTransactions() {
        this.transactions++;
    }

    protected void resetTransactions() {
        this.transactions = 0;
    }

    private void transactionOp(final int id, final double amount) {
        if (checkUser(id)) {
            this.balance += amount;
            this.incrementTransactions();
        }
    }

    protected abstract boolean isWithDrawAllowed(final double amount);
    protected abstract double computeFee();
}
