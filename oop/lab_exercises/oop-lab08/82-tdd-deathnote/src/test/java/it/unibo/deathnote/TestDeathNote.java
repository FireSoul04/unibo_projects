package it.unibo.deathnote;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import it.unibo.deathnote.api.DeathNote;
import it.unibo.deathnote.impl.DeathNoteImplementation;

class TestDeathNote {

    private static final String HEART_ATTACK = "heart attack";
    private static final String KARTING_ACCIDENT = "karting accident";
    private static final String RUN_DEATH_DETAILS = "ran for too long";
    private static final String KART_DEATH_DETAILS = "crashed in a kart competition";
    private DeathNote deathNote;

    @BeforeEach
    void setup() {
        deathNote = new DeathNoteImplementation();
    }

    @Test
    void checkValidRuleNumber() {
        try {
            deathNote.getRule(0);
            deathNote.getRule(-1);
            fail("Rule cannot be zero or negative");
        } catch (final IllegalArgumentException e) {
        
        }
    }

    @Test
    void checkValidRuleContent() {
        for (final String rule : DeathNote.RULES) {
            assertNotNull(rule);
            assertNotEquals("", rule);
        }
    }

    @Test
    void checkWriteName() {
        final String deadHuman = "AZ";
        final String aliveHuman = "Adriano";
        assertFalse(deathNote.isNameWritten(deadHuman));
        deathNote.writeName(deadHuman);
        assertTrue(deathNote.isNameWritten(deadHuman));
        assertFalse(deathNote.isNameWritten(aliveHuman));
        assertFalse(deathNote.isNameWritten(""));
    }

    @Test
    void checkDeathCause() {
        final String heartAttactHuman = "Gechis";
        final String kartAccidentHuman = "Camilla";
        try {
            deathNote.writeDeathCause(HEART_ATTACK);
            fail("Cannot set a death cause without a name of a human before");
        } catch (final IllegalStateException e) {

        }
        deathNote.writeName(heartAttactHuman);
        assertEquals(HEART_ATTACK, deathNote.getDeathCause(heartAttactHuman));
        deathNote.writeName(kartAccidentHuman);
        assertTrue(deathNote.writeDeathCause(KARTING_ACCIDENT));
        assertEquals(KARTING_ACCIDENT, deathNote.getDeathCause(kartAccidentHuman));
        try {
            Thread.sleep(100);
        } catch (final InterruptedException e) {
            fail("Thread crashed unexpectedly", e);
        }
        assertFalse(deathNote.writeDeathCause(HEART_ATTACK));
        assertNotEquals(KARTING_ACCIDENT, deathNote.getDeathCause(kartAccidentHuman));
    }

    @Test
    void checkDeathDetails() {
        final String heartAttackHuman = "N";
        final String kartAccidentHuman = "Vera";
        try {
            deathNote.writeDetails(RUN_DEATH_DETAILS);
            fail("Cannot set death details without a name of a human before");
        } catch (final IllegalStateException e) {

        }
        deathNote.writeName(heartAttackHuman);
        assertEquals("", deathNote.getDeathDetails(heartAttackHuman));
        assertTrue(deathNote.writeDetails(RUN_DEATH_DETAILS));
        assertEquals(RUN_DEATH_DETAILS, deathNote.getDeathDetails(heartAttackHuman));
        deathNote.writeName(kartAccidentHuman);
        try {
            Thread.sleep(6100);
        } catch (final InterruptedException e) {
            fail("Thread crashed unexpectedly", e);
        }
        assertFalse(deathNote.writeDetails(KART_DEATH_DETAILS));
        assertNotEquals(RUN_DEATH_DETAILS, deathNote.getDeathDetails(kartAccidentHuman));
    }
}