package app.utils;

public final class UtilsRandom {
    private static final double LOW_SPEED = 0.5;
    private static final double HIGH_SPEED = 1.5;

    /**
     * Generates a random time span based on the given speed.
     *
     * @param speed the speed factor to determine the range of the time span
     * @return a random time span within the range determined by the speed factor
     */
    public static final long randomTimeSpan(double speed) {
        return (long) (speed * Math.random() * (HIGH_SPEED - LOW_SPEED) + LOW_SPEED);
    }

    /**
     * Simulates a coin flip with a given probability of heads.
     *
     * @param probability The probability of heads (0.0 to 1.0).
     * @return true if the coin flip results in heads, false otherwise.
     */
    public static final boolean coinFlip(double probability) {
        return Math.random() <= probability;
    }
}
