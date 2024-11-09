package it.unibo.bank.impl;

import it.unibo.bank.api.AccountHolder;
import it.unibo.bank.api.BankAccount;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

/**
 * Test class for the {@link StrictBankAccount} class.
 */
class TestStrictBankAccount {

    // Create a new AccountHolder and a StrictBankAccount for it each time tests are executed.
    private AccountHolder mRossi;
    private BankAccount bankAccount;

    private static final int AMOUNT = 100;
    private static final int ACCEPTABLE_MESSAGE_LENGTH = 10;

    /**
     * Prepare the tests.
     */
    @BeforeEach
    public void setUp() {
        this.mRossi = new AccountHolder("Mario", "Rossi", 1);
        this.bankAccount = new StrictBankAccount(mRossi, 0.0);
    }

    /**
     * Test the initial state of the StrictBankAccount.
     */
    @Test
    public void testInitialization() {
        assertEquals(0.0, this.bankAccount.getBalance());
        assertEquals(0, this.bankAccount.getTransactionsCount());
        assertEquals(this.mRossi, this.bankAccount.getAccountHolder());
    }

    /**
     * Perform a deposit of 100€, compute the management fees, and check that the balance is correctly reduced.
     */
    @Test
    public void testManagementFees() {
        this.bankAccount.deposit(this.mRossi.getUserID(), AMOUNT);
        assertEquals(AMOUNT, this.bankAccount.getBalance());

        final int transactionsBeforeTest = this.bankAccount.getTransactionsCount();
        final double balanceBeforeTest = this.bankAccount.getBalance();
        final double feeAmount = 
            StrictBankAccount.MANAGEMENT_FEE 
            + this.bankAccount.getTransactionsCount()
            * StrictBankAccount.TRANSACTION_FEE;

        this.bankAccount.chargeManagementFees(this.mRossi.getUserID());
        if (this.bankAccount.getBalance() > feeAmount) {
            assertEquals(balanceBeforeTest - feeAmount, this.bankAccount.getBalance());
            assertEquals(0, this.bankAccount.getTransactionsCount());
        } else {
            assertEquals(balanceBeforeTest, this.bankAccount.getBalance());
            assertEquals(transactionsBeforeTest, this.bankAccount.getTransactionsCount());
        }
    }

    /**
     * Test that withdrawing a negative amount causes a failure.
     */
    @Test
    public void testNegativeWithdraw() {
        final double balanceBeforeTest = this.bankAccount.getBalance();
        try {
            this.bankAccount.withdraw(this.mRossi.getUserID(), -AMOUNT);
            fail("Withdrawing a negative amount was possible, but should have thrown an exception");
        } catch (IllegalArgumentException e) {
            assertEquals(balanceBeforeTest, this.bankAccount.getBalance());
            assertNotNull(e.getMessage());
            assertFalse(e.getMessage().isBlank());
            assertTrue(e.getMessage().length() >= ACCEPTABLE_MESSAGE_LENGTH);
        }
    }

    /**
     * Test that withdrawing more money than it is in the account is not allowed.
     */
    @Test
    public void testWithdrawingTooMuch() {
        final double balanceBeforeTest = this.bankAccount.getBalance();
        try {
            this.bankAccount.withdraw(this.mRossi.getUserID(), balanceBeforeTest + AMOUNT);
            fail("Withdrawing an amount greater than account's balance was possible, but should have thrown an exception");
        } catch (IllegalArgumentException e) {
            assertEquals(balanceBeforeTest, this.bankAccount.getBalance());
            assertNotNull(e.getMessage());
            assertFalse(e.getMessage().isBlank());
            assertTrue(e.getMessage().length() >= ACCEPTABLE_MESSAGE_LENGTH);
        }
    }
}
