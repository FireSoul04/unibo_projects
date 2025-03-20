package a04.e1;

import java.util.function.*;

public class BankAccountFactoryImpl implements BankAccountFactory {

    private static abstract class BankAccountImpl implements BankAccount {
        private int balance;

        @Override
        public int getBalance() {
            return this.balance;
        }

        protected void setBalance(final int balance) {
            this.balance = balance;
        }

        public abstract void deposit(final int amount);

        public abstract boolean withdraw(final int amount);
    }

    private BankAccount generic(final BiFunction<Integer, Integer, Integer> deposit, final BiFunction<Integer, Integer, Integer> withdraw, final BiPredicate<Integer, Integer> withdrawCondition) {
        return new BankAccountImpl() {
            @Override
            public void deposit(final int amount) {
                this.setBalance(deposit.apply(this.getBalance(), amount));
            }

            @Override
            public boolean withdraw(final int amount) {
                final boolean canWithdraw = withdrawCondition.test(this.getBalance(), amount);
                this.setBalance(canWithdraw ? withdraw.apply(this.getBalance(), amount) : this.getBalance());
                return canWithdraw;
            }
        };
    }

    @Override
    public BankAccount createBasic() {
        return generic((b, a) -> b + a, (b, a) -> b - a, (b, a) -> b > a);
    }

    @Override
    public BankAccount createWithFee(final UnaryOperator<Integer> feeFunction) {
        return generic((b, a) -> b + a, (b, a) -> b - a - feeFunction.apply(a), (b, a) -> b > a);
    }

    @Override
    public BankAccount createWithCredit(final Predicate<Integer> allowedCredit, final UnaryOperator<Integer> rateFunction) {
        return generic((b, a) -> b + a, (b, a) -> b - a - (allowedCredit.test(b) ? rateFunction.apply(0) : 0), (b, a) -> allowedCredit.test(Math.abs(b - a)));
    }

    @Override
    public BankAccount createWithBlock(final BiPredicate<Integer, Integer> blockingPolicy) {
        return new BankAccountImpl() {
            private boolean blocked = false;

            @Override
            public void deposit(final int amount) {
                this.setBalance(this.getBalance() + amount);
            }

            @Override
            public boolean withdraw(final int amount) {
                final boolean canWithdraw = blockingPolicy.test(this.getBalance(), amount);
                if (!canWithdraw) {
                    this.blocked = true;
                }
                this.setBalance(canWithdraw && !this.blocked ? this.getBalance() - amount : this.getBalance());
                return canWithdraw && !this.blocked;
            }
        };
    }

    @Override
    public BankAccount createWithFeeAndCredit(final UnaryOperator<Integer> feeFunction, final Predicate<Integer> allowedCredit,
            final UnaryOperator<Integer> rateFunction) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'createWithFeeAndCredit'");
    }
}
