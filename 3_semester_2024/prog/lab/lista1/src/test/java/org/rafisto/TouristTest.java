package org.rafisto;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

public class TouristTest extends TestCase {

    public TouristTest(String testName) {
        super(testName);
    }

    public static Test suite() {
        return new TestSuite(TouristTest.class);
    }

    public void testBadConstructorParameters() {
        try {
            new Tourist(null, "Doe", 100.0);
            fail("Name must not be null or empty");
        } catch (IllegalArgumentException e) {
            assertEquals("Name must not be null or empty", e.getMessage());
        }

        try {
            new Tourist("John", null, 100.0);
            fail("Surname must not be null or empty");
        } catch (IllegalArgumentException e) {
            assertEquals("Surname must not be null or empty", e.getMessage());
        }
    }

    public void testGetName() {
        Tourist tourist = new Tourist("John", "Doe", 100.0);
        assertEquals("John", tourist.getName());
    }

    public void testSetName() {
        Tourist tourist = new Tourist("John", "Doe", 100.0);
        tourist.setName("Jane");
        assertEquals("Jane", tourist.getName());
    }

    public void testGetSurname() {
        Tourist tourist = new Tourist("John", "Doe", 100.0);
        assertEquals("Doe", tourist.getSurname());
    }

    public void testSetSurname() {
        Tourist tourist = new Tourist("John", "Doe", 100.0);
        tourist.setSurname("Smith");
        assertEquals("Smith", tourist.getSurname());
    }

    public void testGetMoney() {
        Tourist tourist = new Tourist("John", "Doe", 100.0);
        assertEquals(100.0, tourist.getMoney());
    }

    public void testSetMoney() {
        Tourist tourist = new Tourist("John", "Doe", 100.0);
        tourist.setMoney(200.0);
        assertEquals(200.0, tourist.getMoney());
    }
}