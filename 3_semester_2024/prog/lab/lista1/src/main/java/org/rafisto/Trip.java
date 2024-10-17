package org.rafisto;

import java.util.ArrayList;
import java.util.List;

public final class Trip {
    private String destination;
    private int length; // in days
    private double cost;
    private List<Tourist> tourists = new ArrayList<>();

    public Trip(String destination, int length, double cost) throws IllegalArgumentException {
        if (destination == null || destination.isEmpty()) {
            throw new IllegalArgumentException("Destination must not be null or empty");
        }

        if (length < 1) {
            throw new IllegalArgumentException("Length must be at least 1 day");
        }

        if (cost < 0) {
            throw new IllegalArgumentException("Cost must be a positive number");
        }

        this.destination = destination;
        this.length = length;
        this.cost = cost;
    }

    public String describeTrip() {
        StringBuilder description = new StringBuilder();
        description.append("Reise nach ").append(destination)
                .append(" für ").append(length)
                .append(" Tage kostet ").append(cost)
                .append(" Euro. Touristen: ");

        if (tourists.isEmpty()) {
            description.append("Keine Touristen.");
        } else {
            for (Tourist tourist : tourists) {
                description.append(tourist.getName()).append(", ");
            }
            description.setLength(description.length() - 2);
        }

        return description.toString();
    }

    public String getDestination() {
        return destination;
    }

    public void setDestination(String destination) throws IllegalArgumentException {
        if (destination == null || destination.isEmpty()) {
            throw new IllegalArgumentException("Destination must not be null or empty");
        }
        this.destination = destination;
    }

    public int getLength() {
        return length;
    }

    public void setLength(int length) throws IllegalArgumentException {
        if (length < 1) {
            throw new IllegalArgumentException("Length must be at least 1 day");
        }
        this.length = length;
    }

    public double getCost() {
        return cost;
    }

    public void setCost(double cost) throws IllegalArgumentException {
        if (cost < 0) {
            throw new IllegalArgumentException("Cost must be a positive number");
        }
        this.cost = cost;
    }

    public List<Tourist> getTourists() {
        return tourists;
    }

    public void addTourist(Tourist tourist) {
        this.tourists.add(tourist);
    }

    public void removeTourist(Tourist tourist) {
        this.tourists.remove(tourist);
    }
}