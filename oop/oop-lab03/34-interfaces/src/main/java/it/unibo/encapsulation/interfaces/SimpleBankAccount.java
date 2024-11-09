package it.unibo.encapsulation.interfaces;

public class SimpleBankAccount implements BankAccount {

    /*
     * Aggiungere i seguenti campi:
     * - double balance: ammontare del conto
     * - int transactions: numero delle operazioni effettuate
     * - static double ATM_TRANSACTION_FEE = 1: costo delle operazioni via ATM
     */
    private static final double ATM_TRANSACTION_FEE = 1;

    private final int id;

    private double balance;
    private int transactions;

    /*
     * Creare un costruttore pubblico che prenda in ingresso un intero (ossia l'id
     * dell'utente) ed un double (ossia, l'ammontare iniziale del conto corrente).
     */
    public SimpleBankAccount(final int id, final double balance) {
        this.id = id;
        this.balance = balance;
    }

    /*
     * Si aggiungano selettori per:
     * - ottenere l'id utente del possessore del conto
     * - ottenere il numero di transazioni effettuate
     * - ottenere l'ammontare corrente del conto.
     */
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
        /*
         * Incrementa il numero di transazioni e aggiunge amount al totale del
         * conto Nota: il deposito va a buon fine solo se l'id utente
         * corrisponde
         */
        if (this.id == id) {
            transactions++;
            balance = balance + amount;
            System.out.println("Deposited " + amount + " with success");
        } else {
            System.out.println("User id doesn't correspond!");
        }
    }

    public void withdraw(final int id, final double amount) {
        /*
         * Incrementa il numero di transazioni e rimuove amount al totale del
         * conto. Note: - Il conto puo' andare in rosso (ammontare negativo) -
         * Il prelievo va a buon fine solo se l'id utente corrisponde
         */
        if (this.id == id) {
            transactions++;
            balance = balance - amount;
            System.out.println("Withdrawn " + -amount + " with success");
        } else {
            System.out.println("User id doesn't correspond!");
        }
    }

    public void depositFromATM(final int id, final double amount) {
        /*
         * Incrementa il numero di transazioni e aggiunge amount al totale del
         * conto detraendo le spese (costante ATM_TRANSACTION_FEE) relative
         * all'uso dell'ATM (bancomat) Nota: il deposito va a buon fine solo se
         * l'id utente corrisponde
         */
        if (this.id == id) {
            transactions++;
            balance = balance + amount - ATM_TRANSACTION_FEE;
            System.out.println("Deposited " + (amount - ATM_TRANSACTION_FEE) + " with success");
        } else {
            System.out.println("User id doesn't correspond!");
        }
    }

    public void withdrawFromATM(final int id, final double amount) {
        /*
         * Incrementa il numero di transazioni e rimuove amount + le spese
         * (costante ATM_TRANSACTION_FEE) relative all'uso dell'ATM (bancomat)
         * al totale del conto. Note: - Il conto puo' andare in rosso (ammontare
         * negativo) - Il prelievo va a buon fine solo se l'id utente
         * corrisponde
         */
        if (this.id == id) {
            transactions++;
            balance = balance - amount - ATM_TRANSACTION_FEE;
            System.out.println("Withdrawn " + (-amount - ATM_TRANSACTION_FEE) + " with success");
        } else {
            System.out.println("User id doesn't correspond!");
        }
    }

    public void chargeManagementFees(final int id) {
        /*
         * Riduce il bilancio del conto di un ammontare pari alle spese di gestione
         */
    }

    public String toString() {
        return "User ID = " + this.id +
            "\nTotal transactions = " + this.transactions +
            "\nTotal balance = " + this.balance;
    }
}
