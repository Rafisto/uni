package org.rafisto;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;
import java.util.List;

public class AgencyTest extends TestCase {

    public AgencyTest(String testName) {
        super(testName);
    }

    public static Test suite() {
        return new TestSuite(AgencyTest.class);
    }

    public void testNewTrip() {
        Agency agency = new Agency();
        Trip trip = new Trip("Paris", 7, 1000);
        agency.newTrip(trip);
        List<Trip> trips = agency.getTrips();
        assertEquals(1, trips.size());
        assertEquals(trip, trips.get(0));
    }

    public void testGetTrips() {
        Agency agency = new Agency();
        Trip trip1 = new Trip("Paris", 3, 500);
        Trip trip2 = new Trip("London", 3, 800);
        agency.newTrip(trip1);
        agency.newTrip(trip2);
        List<Trip> trips = agency.getTrips();
        assertEquals(2, trips.size());
        assertEquals(trip1, trips.get(0));
        assertEquals(trip2, trips.get(1));
    }
}