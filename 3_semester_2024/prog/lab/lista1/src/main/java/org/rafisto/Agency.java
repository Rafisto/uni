package org.rafisto;

import java.util.ArrayList;
import java.util.List;

public final class Agency {
    private List<Trip> trips = new ArrayList<Trip>();

    public void newTrip(Trip trip) {
        trips.add(trip);
    }

    public List<Trip> getTrips() {
        return trips;
    }
}
