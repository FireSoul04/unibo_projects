package it.unibo.inheritance.impl;

import it.unibo.inheritance.api.AccountHolder;

public class ClassicBankAccount extends AbstractBankAccount {

    public ClassicBankAccount(final AccountHolder accountHolder, final double balance) {
        super(accountHolder, balance);
    }

    @Override
    protected boolean isWithDrawAllowed(final double amount) {
        return true;
    }

    @Override
    protected double computeFee() {
        return MANAGEMENT_FEE;
    }
}
