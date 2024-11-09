package it.unibo.arrays;

class MyCircularArray {

    final int DEF_SIZE = 10;
    final int DEF_LAST_ELEM = 0;
    final int DEF_RESETTED_ELEM = 0;

    int[] array;
    int lastElem;
    int length;

    MyCircularArray() {
        array = new int[DEF_SIZE];
        lastElem = DEF_LAST_ELEM;
        length = DEF_SIZE;
    }

    MyCircularArray(int size) {
        array = new int[size];
        lastElem = DEF_LAST_ELEM;
        length = size;
    }

    void add(final int elem) {
        array[lastElem] = elem;

        lastElem++;
        if (lastElem >= array.length) {
            lastElem = DEF_LAST_ELEM;
        }
    }

    void reset() {
        for (int i = 0; i < array.length; i++) {
            array[i] = DEF_RESETTED_ELEM;
        }
        lastElem = DEF_LAST_ELEM;
    }

    void printArray() {
        System.out.print("[");
        for (int i = 0; i < this.array.length - 1; i++) {
            System.out.print(this.array[i] + ",");
        }
        System.out.println(this.array[this.array.length - 1] + "]");
    }

    public static void main(final String[] args) {

        // 1) Creare un array circolare di dieci elementi
        MyCircularArray a1 = new MyCircularArray(10);

        // 2) Aggiungere gli elementi da 1 a 10 e stampare il contenuto
        // dell'array circolare
        for (int i = 0; i <= 10; i++) {
            a1.add(i);
        }
        a1.printArray();

        // 3) Aggiungere gli elementi da 11 a 15 e stampare il contenuto
        // dell'array circolare
        for (int i = 11; i <= 15; i++) {
            a1.add(i);
        }
        a1.printArray();

        // 4) Invocare il metodo reset
        a1.reset();

        // 5) Stampare il contenuto dell'array circolare
        a1.printArray();

        // 6) Aggiungere altri elementi a piacere e stampare il contenuto
        // dell'array circolare
        for (int i = 0; i <= 18; i++) {
            a1.add(i * 2);
        }
        a1.printArray();
    }
}
