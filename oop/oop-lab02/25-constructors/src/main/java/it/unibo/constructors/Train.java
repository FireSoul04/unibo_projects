package it.unibo.constructors;

class Train {

    static final int DEFAULT_N_FC_SEATS = 50;
    static final int DEFAULT_N_SC_SEATS = 100;
    static final int DEFAULT_TOT_SEATS = 150;

    int seats;
    int firstClassSeats;
    int secondClassSeats;
    int firstClassReserved;
    int secondClassReserved;

    Train(final int s, final int fc, final int sc) {
        this.seats = s;
        this.firstClassSeats = fc;
        this.secondClassSeats = sc;
        this.firstClassReserved = 0;
        this.secondClassReserved = 0;
    }
    
    Train(final int fc, final int sc) {
        this(fc + sc, fc, sc);
    }
    
    Train() {
        this(DEFAULT_TOT_SEATS, DEFAULT_N_FC_SEATS, DEFAULT_N_SC_SEATS);
    }

    void deleteAllReservations() {
        this.firstClassReserved = 0;
        this.secondClassReserved = 0;
    }

    double getFirstClassOccupancyRatio() {
        return this.firstClassReserved * 100d / this.firstClassSeats;
    }

    int getFirstClassSeats() {
        return this.firstClassSeats;
    }

    int getSecondClassSeats() {
        return this.secondClassSeats;
    }

    double getOccupancyRatio() {
        return (this.firstClassReserved + this.secondClassReserved) * 100d / this.seats;
    }

    double getSecondClassOccupancyRatio() {
        return this.secondClassReserved * 100 / this.secondClassSeats;
    }

    int getTotalSeats() {
        return this.seats;
    }

    void printTrainInfo() {
        System.out.println("Train info:");
        System.out.println("-nTotSeats: " + this.seats);
        System.out.println("-nFCSeats: " + this.firstClassSeats);
        System.out.println("-nSCSeats: " + this.secondClassSeats);
        System.out.println("-nFCReservedSeats: " + this.firstClassReserved);
        System.out.println("-nSCReservedSeats: " + this.secondClassReserved + "\n");
    }

    void reserveFirstClassSeats(final int nSeats) {
        this.firstClassReserved += nSeats;
    }

    void reserveSecondClassSeats(final int nSeats) {
        this.secondClassReserved += nSeats;
    }
}
