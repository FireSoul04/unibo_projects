package a05.e1;

public class BankAccountFactoryImpl implements BankAccountFactory {

    @Override
    public BankAccount simple() {
        return new AbstractBankAccount() {
            @Override
            protected boolean canDeposit(int amount) {
                return true;
            }

            @Override
            protected void onDisallowedDeposit() {
            }

            @Override
            protected void onDisallowedWithdraw() {
            }

            @Override
            protected int newBalanceOnWithdraw(int amount) {
                return this.balance() - amount;
            }

            @Override
            protected boolean canWithdraw(int amount) {
                return amount <= this.balance();
            }
        };
    }

    @Override
    public BankAccount withFee(int fee) {
        return new AbstractBankAccount() {
            @Override
            protected boolean canDeposit(int amount) {
                return true;
            }

            @Override
            protected void onDisallowedDeposit() {
            }

            @Override
            protected void onDisallowedWithdraw() {
            }

            @Override
            protected int newBalanceOnWithdraw(int amount) {
                return this.balance() - amount - fee;
            }

            @Override
            protected boolean canWithdraw(int amount) {
                return amount + fee <= this.balance();
            }
        };
    }

    @Override
    public BankAccount checked() {
        return new AbstractBankAccount() {
            @Override
            protected boolean canDeposit(int amount) {
                if (amount < 0) {
                    return false;
                }
                return true;
            }

            @Override
            protected void onDisallowedDeposit() {
                throw new IllegalStateException();
            }

            @Override
            protected void onDisallowedWithdraw() {
                throw new IllegalStateException();
            }

            @Override
            protected int newBalanceOnWithdraw(int amount) {
                return this.balance() - amount;
            }

            @Override
            protected boolean canWithdraw(int amount) {
                if (amount < 0) {
                    return false;
                }
                if (amount > this.balance()) {
                    return false;
                }
                return true;
            }
        };
    }

    @Override
    public BankAccount gettingBlocked() {
        return new AbstractBankAccount() {
            private boolean blocked = false;

            @Override
            protected boolean canDeposit(int amount) {
                if (blocked || amount < 0) {
                    return false;
                }
                return true;
            }

            @Override
            protected void onDisallowedDeposit() {
                blocked = true;
            }

            @Override
            protected void onDisallowedWithdraw() {
                blocked = true;
            }

            @Override
            protected int newBalanceOnWithdraw(int amount) {
                return this.balance() - amount;
            }

            @Override
            protected boolean canWithdraw(int amount) {
                if (blocked || amount < 0 || amount > this.balance()) {
                    return false;
                }
                return true;
            }
        };
    }

    @Override
    public BankAccount pool(BankAccount primary, BankAccount secondary) {
        return new AbstractBankAccount() {
            @Override
            public void deposit(int amount) {
                if (this.canDeposit(amount)){
                    this.depositOnLeastBalance(amount);
                    super.deposit(amount);
                } else {
                    this.onDisallowedDeposit();
                }
            }

            private void depositOnLeastBalance(int amount) {
                if (primary.balance() <= secondary.balance()) {
                    primary.deposit(amount);
                } else {
                    secondary.deposit(amount);
                }
            }
            
            @Override
            protected boolean canDeposit(int amount) {
                return true;
            }

            @Override
            protected void onDisallowedDeposit() {
            }

            @Override
            protected void onDisallowedWithdraw() {
            }

            @Override
            protected int newBalanceOnWithdraw(int amount) {
                if (!primary.withdraw(amount)) {
                    secondary.withdraw(amount);
                }
                return this.balance() - (this.balance() - primary.balance() - secondary.balance());
            }

            @Override
            protected boolean canWithdraw(int amount) {
                return true;
            }
        };
    }
}
