package app.controller.validators;

public class GUIFieldValidator {
    public static double validateSpeed(String speed) throws NumberFormatException {
        try {
            double speedValue = Double.parseDouble(speed);
            if (speedValue > 0) {
                return speedValue;
            }
            throw new NumberFormatException("Speed must be greater than 0");
        } catch (NumberFormatException e) {
            throw new NumberFormatException("Unable to parse speed value");
        }
    }

    public static int validateHeight(String height) throws NumberFormatException {
        try {
            int heightValue = Integer.parseInt(height);
            if (heightValue > 0) {
                return heightValue;
            }
            throw new NumberFormatException("Height must be greater than 0");
        } catch (NumberFormatException e) {
            throw new NumberFormatException("Unable to parse height value");
        }
    }

    public static int validateWidth(String width) throws NumberFormatException {
        try {
            int widthValue = Integer.parseInt(width);
            if (widthValue > 0) {
                return widthValue;
            }
            throw new NumberFormatException("Width must be greater than 0");
        } catch (NumberFormatException e) {
            throw new NumberFormatException("Unable to parse width value");
        }
    }

    public static double validateProbability(double probabilityValue) throws NumberFormatException {
        if (probabilityValue >= 0 && probabilityValue <= 100) {
            return probabilityValue / 100.0;
        }
        throw new NumberFormatException("Probability % must be between 0 and 100");
    }
}
