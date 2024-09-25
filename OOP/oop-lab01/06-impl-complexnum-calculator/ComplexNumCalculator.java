public class ComplexNumCalculator {
    int nOpDone;
    ComplexNum lastRes;

    void build() {
        nOpDone = 0;
        lastRes = new ComplexNum();
        lastRes.build(0.0, 0.0);
    }

    ComplexNum add(ComplexNum a, ComplexNum b) {
        nOpDone++;
        lastRes = a;
        lastRes.add(b);
        return lastRes;
    }

    ComplexNum sub(ComplexNum a, ComplexNum b) {
        nOpDone++;
        lastRes = a;
        lastRes.sub(b);
        return lastRes;
    }

    ComplexNum mul(ComplexNum a, ComplexNum b) {
        nOpDone++;
        lastRes = a;
        lastRes.mul(b);
        return lastRes;
    }

    ComplexNum div(ComplexNum a, ComplexNum b) {
        nOpDone++;
        lastRes = a;
        lastRes.div(b);
        return lastRes;
    }
}
