package org.rafisto;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

public class TripTest extends TestCase {

    public TripTest(String testName) {
        super(testName);
    }

    public static Test suite() {
        return new TestSuite(TripTest.class);
    }

    public void testBadConstructorParameters() {
        try {
            new Trip(null, 5, 500.0);
            fail("Destination must not be null or empty");
        } catch (IllegalArgumentException e) {
            assertEquals("Destination must not be null or empty", e.getMessage());
        }

        try {
            new Trip("Berlin", 0, 500.0);
            fail("Length must be greater than 0");
        } catch (IllegalArgumentException e) {
            assertEquals("Length must be at least 1 day", e.getMessage());
        }

        try {
            new Trip("Berlin", 5, -10.0);
            fail("Cost must be a positive number");
        } catch (IllegalArgumentException e) {
            assertEquals("Cost must be a positive number", e.getMessage());
        }
    }

    public void testDescribeTripNoTourists() {
        Trip trip = new Trip("Berlin", 5, 500.0);
        assertEquals("Reise nach Berlin für 5 Tage kostet 500.0 Euro. Touristen: Keine Touristen.",
                trip.describeTrip());
    }

    public void testDescribeTripWithTourists() {
        Trip trip = new Trip("Berlin", 5, 500.0);
        Tourist tourist1 = new Tourist("John", "Doe", 100.0);
        Tourist tourist2 = new Tourist("Jane", "Smith", 200.0);
        trip.addTourist(tourist1);
        trip.addTourist(tourist2);
        assertEquals("Reise nach Berlin für 5 Tage kostet 500.0 Euro. Touristen: John, Jane", trip.describeTrip());
    }

    public void testGetDestination() {
        Trip trip = new Trip("Berlin", 5, 500.0);
        assertEquals("Berlin", trip.getDestination());
    }

    public void testSetDestination() {
        Trip trip = new Trip("Berlin", 5, 500.0);
        trip.setDestination("Munich");
        assertEquals("Munich", trip.getDestination());
    }

    public void testGetLength() {
        Trip trip = new Trip("Berlin", 5, 500.0);
        assertEquals(5, trip.getLength());
    }

    public void testSetLength() {
        Trip trip = new Trip("Berlin", 5, 500.0);
        trip.setLength(7);
        assertEquals(7, trip.getLength());
    }

    public void testGetCost() {
        Trip trip = new Trip("Berlin", 5, 500.0);
        assertEquals(500.0, trip.getCost());
    }

    public void testSetCost() {
        Trip trip = new Trip("Berlin", 5, 500.0);
        trip.setCost(700.0);
        assertEquals(700.0, trip.getCost());
    }

    public void testAddTourist() {
        Trip trip = new Trip("Berlin", 5, 500.0);
        Tourist tourist = new Tourist("John", "Doe", 100.0);
        trip.addTourist(tourist);
        assertTrue(trip.getTourists().contains(tourist));
    }

    public void testRemoveTourist() {
        Trip trip = new Trip("Berlin", 5, 500.0);
        Tourist tourist = new Tourist("John", "Doe", 100.0);
        trip.addTourist(tourist);
        trip.removeTourist(tourist);
        assertFalse(trip.getTourists().contains(tourist));
    }
}