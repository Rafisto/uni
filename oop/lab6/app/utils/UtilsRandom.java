package app.utils;

public class UtilsRandom {
    private static double LOW_SPEED = 0.5;
    private static double HIGH_SPEED = 1.5;
    public static long randomTimeSpan(double speed) {
        return (long) (speed * Math.random() * (HIGH_SPEED - LOW_SPEED) + LOW_SPEED);
    }

    public static boolean coinFlip(double probability) {
        return Math.random() < probability;
    }
}
