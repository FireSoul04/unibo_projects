public class Train {
    int nTotSeats;
    int nFirstClassSeats;
    int nSecondClassSeats;
    int nFirstClassReservedSeats;
    int nSecondClassReservedSeats;

    void build(int nts, int nfs, int nss) {
        nTotSeats = nts;
        nFirstClassSeats = nfs;
        nSecondClassSeats = nss;
        nFirstClassReservedSeats = 0;
        nSecondClassReservedSeats = 0;
    }

    void reserveFirstClassSeats(int n) {
        if (nFirstClassReservedSeats + n < nFirstClassSeats) {
            nFirstClassReservedSeats += n;
        } else {
            nFirstClassReservedSeats = nFirstClassSeats;
            System.out.println("Posti prima classe pieni");
        }
    }

    void reserveSecondClassSeats(int n) {
        if (nSecondClassReservedSeats + n < nSecondClassSeats) {
            nSecondClassReservedSeats += n;
        } else {
            nSecondClassReservedSeats = nSecondClassSeats;
            System.out.println("Posti seconda classe pieni");
        }
    }

    double getTotOccupancyRatio() {
        return (nFirstClassReservedSeats + nSecondClassReservedSeats) * 100.0 / nTotSeats;
    }
    
    double getFirstClassOccupancyRatio() {
        return nFirstClassReservedSeats * 100.0 / nFirstClassSeats;
    }

    double getSecondClassOccupancyRatio() {
        return nSecondClassReservedSeats * 100.0 / nSecondClassSeats;
    }

    void deleteAllReservations() {
        nFirstClassReservedSeats = 0;
        nSecondClassReservedSeats = 0;
    }
}
