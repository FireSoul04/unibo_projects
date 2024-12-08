package it.unibo.oop.workers02;

import java.util.ArrayList;
import java.util.List;

public class MultiThreadedSumMatrix implements SumMatrix {
    
    private final int nthread;

    /**
     * 
     * @param nthread
     *            no. of thread performing the sum.
     */
    public MultiThreadedSumMatrix(final int nthread) {
        this.nthread = nthread;
    }

    private static class Worker extends Thread {
        private final double[][] matrix;
        private final int startcol;
        private final int startrow;
        private final int nelem;
        private long res;

        /**
         * Build a new worker.
         * 
         * @param matrix
         *            the matrix to sum
         * @param startpos
         *            the initial position for this worker
         * @param nelem
         *            the no. of elems to sum up for this worker
         */
        Worker(final double[][] matrix, final int startcol, final int startrow, final int nelem) {
            super();
            this.matrix = matrix;
            this.startcol = startcol;
            this.startrow = startrow;
            this.nelem = nelem;
        }

        @Override
        @SuppressWarnings("PMD.SystemPrintln")
        public void run() {
            System.out.println("Working from position " + startrow + " to position " + (startrow + nelem - 1));
            for (int i = startcol; i < matrix.length; i++) {
                for (int j = startrow; j < matrix[0].length && i < startrow + nelem; j++) {
                    this.res += this.matrix[i][j];
                }
            }
        }

        /**
         * Returns the result of summing up the integers within the list.
         * 
         * @return the sum of every element in the array
         */
        public long getResult() {
            return this.res;
        }
    }

    @Override
    public double sum(final double[][] matrix) {
        final int size = (matrix.length * matrix[0].length) / nthread;
        final List<Worker> workers = new ArrayList<>(nthread);
        for (int start = 0; start < matrix.length * matrix[0].length; start += size) {
            workers.add(new Worker(matrix, start % matrix.length * matrix[0].length, start / matrix.length * matrix[0].length, size));
        }
        for (final Worker w: workers) {
            w.start();
        }
        long sum = 0;
        for (final Worker w: workers) {
            try {
                w.join();
                sum += w.getResult();
            } catch (InterruptedException e) {
                throw new IllegalStateException(e);
            }
        }
        return sum;
    }
}
