class ComplexNum {
    double re;
    double im;

    void build(double re, double im) {
        this.re = re;
        this.im = im;
    }

    boolean equal(ComplexNum num) {
        return this.re == num.re && this.im == num.im;
    }

    void add(ComplexNum num) {
        this.re += num.re;
        this.im += num.im;
    }

    void sub(ComplexNum num) {
        this.re -= num.re;
        this.im -= num.im;
    }

    void mul(ComplexNum num) {
        ComplexNum result = new ComplexNum();
        result.build(this.re, this.im);
        result.re = this.re * num.re - this.im * num.im;
        result.im = this.im * num.re + this.re * num.im;

        this.re = result.re;
        this.im = result.im;
    }

    void div(ComplexNum num) {
        ComplexNum result = new ComplexNum();
        result.build(this.re, this.im);
        result.re = (this.re * num.re + this.im * num.im) / (num.re * num.re + num.im * num.im);
        result.im = (this.im * num.re - this.re * num.im) / (num.re * num.re + num.im * num.im);

        this.re = result.re;
        this.im = result.im;
    }

    String toStringRep() {
        String stringRe = "";
        String stringIm = "";
        String result = "";
        if (this.re != 0.0) {
            stringRe = Double.toString(this.re);
        }

        if (this.im == 1.0) {
            stringIm = "i";
        } else if (this.im == -1.0) {
            stringIm = "-i";
        } else {
            stringIm = Double.toString(this.im) + "i";
        }

        if (this.re == 0.0 && this.im == 0.0) {
            result = "0.0";
        } else if (this.im > 0.0) {
            result = stringRe + "+" + stringIm;
        } else if (this.im < 0.0) {
            result = stringRe + stringIm;
        }
        return result;
    }
}