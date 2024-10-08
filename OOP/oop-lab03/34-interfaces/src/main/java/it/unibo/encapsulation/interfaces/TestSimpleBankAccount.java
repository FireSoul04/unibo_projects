package it.unibo.encapsulation.interfaces;

public class TestSimpleBankAccount {

    private TestSimpleBankAccount() {
        /*
         * Prevents object creation from the outside.
         */
    }

    public static void main(final String[] args) {
        // 1) Creare l' AccountHolder relativo a Andrea Rossi con id 1
        AccountHolder rossiAndrea = new AccountHolder("Andrea", "Rossi", 1);

        // 2) Creare l' AccountHolder relativo a Alex Bianchi con id 2
        AccountHolder bianchiAlex = new AccountHolder("Alex", "Bianchi", 2);

        // 3) Creare i due SimpleBankAccount corrispondenti
        SimpleBankAccount sbRossiAndrea = new SimpleBankAccount(rossiAndrea.getUserID(), 0);
        SimpleBankAccount sbBianchiAlex = new SimpleBankAccount(bianchiAlex.getUserID(), 0);

        // 4) Effettuare una serie di depositi e prelievi
        sbRossiAndrea.deposit(1, 200);

        sbBianchiAlex.deposit(2, 400);
        sbBianchiAlex.withdrawFromATM(2, 500);

        /*
         * 5) Stampare a video l'ammontare dei due conti e verificare la
         * correttezza del risultato
         */
        System.out.println(sbRossiAndrea);
        System.out.println(sbBianchiAlex);
         
        // 6) Provare a prelevare fornendo un id utente sbagliato
        sbRossiAndrea.depositFromATM(2, 20);

        // 7) Controllare nuovamente l'ammontare
        System.out.println(sbRossiAndrea);
        System.out.println(sbBianchiAlex);
    }
}
