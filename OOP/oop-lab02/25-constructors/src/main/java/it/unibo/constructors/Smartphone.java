package it.unibo.constructors;

class Smartphone {

    static final boolean DEF_HAS_GPS = true;
    static final boolean DEF_HAS_3G = true;
    static final boolean DEF_HAS_NFC = true;
    static final int DEF_SD_SIZE = 8192;
    static final int DEF_RAM_SIZE = 1024;
    static final int DEF_N_CPU = 2;

    int nCPU;
    int ram;
    int sdSize;
    String brand;
    String model;
    boolean hasGPS;
    boolean has3G;
    boolean hasNFC;

    Smartphone(String brand, String model, int nCpu, int ram, int sdSize, boolean hasGPS, boolean has3G, boolean hasNFC) {
        this.brand = brand;
        this.model = model;
        this.hasGPS = hasGPS;
        this.has3G = has3G;
        this.hasNFC = hasNFC;
        this.nCPU = nCpu;
        this.ram = ram;
        this.sdSize = sdSize;
    }

    Smartphone(String brand, String model, boolean hasGPS, boolean has3G) {
        this(brand, model, DEF_N_CPU, DEF_RAM_SIZE, DEF_SD_SIZE, hasGPS, has3G, DEF_HAS_NFC);
    }

    Smartphone(String brand, String model, boolean hasNFC) {
        this(brand, model, DEF_N_CPU, DEF_RAM_SIZE, DEF_SD_SIZE, DEF_HAS_GPS, DEF_HAS_3G, hasNFC);
    }

    Smartphone(String brand, String model, int sdSize) {
        this(brand, model, DEF_N_CPU, DEF_RAM_SIZE, sdSize, DEF_HAS_GPS, DEF_HAS_3G, DEF_HAS_NFC);
    }

    Smartphone(String brand, String model) {
        this(brand, model, DEF_SD_SIZE);
    }

    void printStringRep() {
        System.out.println("Smartphone info:");
        System.out.println("n CPU(s): " + this.nCPU);
        System.out.println("RAM amount: " + this.ram);
        System.out.println("SD size: " + this.sdSize);
        System.out.println("brand: " + this.brand);
        System.out.println("model: " + this.model);
        System.out.println("hasGPS: " + this.hasGPS);
        System.out.println("has3G: " + this.has3G);
        System.out.println("hasNFC: " + this.hasNFC + "\n");
    }

    public static void main(final String[] args) {
        // 1) Creare lo smarthpone HTC One sdSize:1024

        // 2) Creare lo smarthpone Samsung Galaxy Note 3 ram:2048 cpu:4
        // sdSize:8192 gps:true nfc:true 3g:true

        // 3) Creare lo smarthpone Apple iPhone 5S nfc:false

        // 4) Creare lo smarthpone Google Nexus 4 gps:true 3g:true

        // 5) Utilizzare il metodo printStringRep per stampare in standard
        // output le informazioni di ciascun telefono

        Smartphone galaxyNote3 = new Smartphone("Samsung", "Galaxy Note 3", 4, 2048, 8192, true, true, true);
        galaxyNote3.printStringRep();

        Smartphone iphone5S = new Smartphone("iPhone", "5S", false);
        iphone5S.printStringRep();

        Smartphone nexus4 = new Smartphone("Google", "Nexus 4", true, true);
        nexus4.printStringRep();
    }
}
