class TestComplexNumCalculator {
  public static void main(String[] args) {
      /*
       * 1) Testare la classe ComplexNumCalculator con le seguenti operazioni
       *    tra numeri complessi:
       *
       * - add(1+2i, 2+3i) = 3+5i
       *
       * - sub(4+5i, 6+7i) = -2-2i
       *
       * - mul(8+2i, 3-i) = 26 - 2i
       *
       * - ... altre a piacere
       *
       * 2) Verificare il corretto valore dei campi nOpDone, lastRes
       *
       * 3) Fare altre prove con operazioni a piacere
       */
      ComplexNumCalculator calc = new ComplexNumCalculator();
      ComplexNum a = new ComplexNum();
      ComplexNum b = new ComplexNum();

      calc.build();

      System.out.println("Number of operations done: " + calc.nOpDone);
      System.out.println("Last result: " + calc.lastRes.toStringRep());

      a.build(1.0, 2.0);
      b.build(2.0, 3.0);

      calc.add(a, b);

      System.out.println("Number of operations done: " + calc.nOpDone);
      System.out.println("Last result: " + calc.lastRes.toStringRep());

      a.build(4.0, 5.0);
      b.build(6.0, 7.0);

      calc.sub(a, b);

      System.out.println("Number of operations done: " + calc.nOpDone);
      System.out.println("Last result: " + calc.lastRes.toStringRep());

      a.build(8.0, 2.0);
      b.build(3.0, -1.0);

      calc.mul(a, b);
      
      System.out.println("Number of operations done: " + calc.nOpDone);
      System.out.println("Last result: " + calc.lastRes.toStringRep());

      a.build(5.0, -2.0);
      b.build(3.0, 2.0);

      calc.div(a, b);

      System.out.println("Number of operations done: " + calc.nOpDone);
      System.out.println("Last result: " + calc.lastRes.toStringRep());
  }
}
