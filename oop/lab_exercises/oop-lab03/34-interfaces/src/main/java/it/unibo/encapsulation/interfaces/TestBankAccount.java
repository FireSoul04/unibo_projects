package it.unibo.encapsulation.interfaces;

public class TestBankAccount {

    private TestBankAccount() {
    }

    public static void main(final String[] args) {
        /*
         * 1) Creare l' AccountHolder relativo a Andrea Rossi con id 1
         */
        AccountHolder rossiAndrea = new AccountHolder("Andrea", "Rossi", 1);
        /*
         * 2) Creare l' AccountHolder relativo a Alex Bianchi con id 2
         */
        AccountHolder bianchiAlex = new AccountHolder("Alex", "Bianchi", 2);
        /*
         * 3) Dichiarare due variabili di tipo BankAccount ed inizializzarle,
         * rispettivamente, con oggetti di tipo SimpleBankAccount per il conto di
         * Rossi (ammontare iniziale = 0), e di tipo StrictBankAccount per il conto di
         * Bianchi (ammontare iniziale = 0)
         */
        BankAccount baRossiAndrea = new SimpleBankAccount(rossiAndrea.getUserID(), 0);
        BankAccount baBianchiAlex = new StrictBankAccount(bianchiAlex.getUserID(), 0);
        /*
         * 4) Prima riflessione: perché è stato possibile fare la new di due classi
         * diverse in variabili dello stesso tipo?
         */
        /*
         * 5) Depositare €10000 in entrambi i conti
         */
        baRossiAndrea.deposit(1, 10000);
        baBianchiAlex.deposit(2, 10000);
        /*
         * 6) Prelevare €15000$ da entrambi i conti
         */
        baRossiAndrea.withdraw(1, 15000);
        baBianchiAlex.withdraw(2, 15000);
        /*
         * 7) Stampare in stdout l'ammontare corrente
         */
        System.out.println(baRossiAndrea);
        System.out.println(baBianchiAlex);
        /*
         * 8) Qual è il risultato e perché?
         */
        /*
         * 9) Depositare nuovamente €10000 in entrambi i conti
         */
        baRossiAndrea.deposit(1, 10000);
        baBianchiAlex.deposit(2, 10000);
        /*
         * 10) Invocare il metodo computeManagementFees su entrambi i conti
         */
        baRossiAndrea.chargeManagementFees(1);
        baBianchiAlex.chargeManagementFees(2);
        /*
         * 11) Stampare a video l'ammontare corrente
         */
        System.out.println(baRossiAndrea);
        System.out.println(baBianchiAlex);
        /*
         * 12) Qual è il risultato e perché?
         */
    }
}
