package it.unibo.deathnote.impl;

import java.util.List;
import java.util.ArrayList;
import java.util.Objects;

import it.unibo.deathnote.api.DeathNote;

public class DeathNoteImplementation implements DeathNote {

    private static class DeadHuman {

        private static final String DEFAULT_DEATH_CAUSE = "heart attack";
        private final String name;
        private String deathCause;
        private String deathDetails;
        private long deathTime;

        public DeadHuman(final String name) {
            this.name = name;
            this.deathCause = DEFAULT_DEATH_CAUSE;
            this.deathDetails = "";
            this.deathTime = System.currentTimeMillis();
        }

        public String getName() {
            return this.name;
        }

        public String getDeathCause() {
            return this.deathCause;
        }

        public long getDeathTime() {
            return System.currentTimeMillis() - this.deathTime;
        }

        public String getDeathDetails() {
            return this.deathDetails;
        }

        public void setDeathCause(final String deathCause) {
            this.deathCause = deathCause;
        }

        public void setDeathDetails(final String deathDetails) {
            this.deathDetails = deathDetails;
        }
    }

    private final List<DeadHuman> deadHumans = new ArrayList<>();

    private boolean isStringValid(final String str) {
        return Objects.isNull(str) || str.equals("");
    }

    @Override
    public String getRule(final int ruleNumber) throws IllegalArgumentException {
        final String rule = DeathNote.RULES.get(ruleNumber);
        if (ruleNumber <= 0) {
            throw new IllegalArgumentException("Invalid index of rule");
        }
        if (!isStringValid(rule)) {
            throw new IllegalArgumentException("Rule cannot be null or empty");
        }
        return rule;
    }

    @Override
    public void writeName(final String name) throws NullPointerException {
        if (Objects.isNull(name)) {
            throw new NullPointerException("Name cannot be null");
        }
        if (!name.equals("")) {
            this.deadHumans.add(new DeadHuman(name));
        }
    }

    @Override
    public boolean writeDeathCause(final String cause) throws IllegalStateException {
        if (Objects.isNull(cause)) {
            throw new IllegalStateException("Cause cannot be null");
        }
        if (this.deadHumans.isEmpty()) {
            throw new IllegalStateException("No name is written in deathnote");
        }
        final DeadHuman deadHuman = this.deadHumans.getLast();
        if (!cause.equals("")) {
            deadHuman.setDeathCause(cause);
        }
        return deadHuman.getDeathTime() <= 40;
    }

    @Override
    public boolean writeDetails(final String details) throws IllegalStateException {
        if (Objects.isNull(details)) {
            throw new IllegalStateException("Details cannot be null");
        }
        if (this.deadHumans.isEmpty()) {
            throw new IllegalStateException("No name is written in deathnote");
        }
        final DeadHuman deadHuman = this.deadHumans.getLast();
        if (!details.equals("")) {
            deadHuman.setDeathDetails(details);
        }
        return deadHuman.getDeathTime() <= 6040;
    }

    @Override
    public String getDeathCause(final String name) throws IllegalArgumentException {
        for (final DeadHuman deadHuman : this.deadHumans) {
            if (deadHuman.getName().equals(name)) {
                return deadHuman.getDeathCause();
            }
        }
        throw new IllegalArgumentException("Name not found in death note");
    }

    @Override
    public String getDeathDetails(final String name) throws IllegalArgumentException {
        for (final DeadHuman deadHuman : this.deadHumans) {
            if (deadHuman.getName().equals(name)) {
                return deadHuman.getDeathDetails();
            }
        }
        throw new IllegalArgumentException("Name not found in death note");
    }

    @Override
    public boolean isNameWritten(final String name) {
        for (final DeadHuman deadHuman : this.deadHumans) {
            if (deadHuman.getName().equals(name)) {
                return true;
            }
        }
        return false;
    }
    
}
