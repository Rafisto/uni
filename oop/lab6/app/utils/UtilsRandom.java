package app.utils;

public class UtilsRandom {
    private static double LOW_SPEED = 0.5;
    private static double HIGH_SPEED = 1.5;
    public static double randomTimeSpan(double speed) {
        return Math.random() * (HIGH_SPEED - LOW_SPEED) + LOW_SPEED;
    }
}
