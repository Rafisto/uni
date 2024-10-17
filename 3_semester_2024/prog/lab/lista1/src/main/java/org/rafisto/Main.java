package org.rafisto;

public final class Main {
    private Main() {
        throw new UnsupportedOperationException("Unable to create an instance of Main class");
    }

    public static void main(String[] args) {
        Trip reise = new Trip("Berlin", 5, 1000.0);
        reise.addTourist(new Tourist("John", "Doe", 3000.0));
        reise.addTourist(new Tourist("Heidi", "Klum", 10000.0));

        try {
            reise.setDestination("Porsche Museum, Porscheplatz 1, Zuffenhausen, 70435 Stuttgart");

            Agency buro = new Agency();
            buro.newTrip(reise);

            System.out.println(buro.getTrips().get(0).describeTrip());
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }
}