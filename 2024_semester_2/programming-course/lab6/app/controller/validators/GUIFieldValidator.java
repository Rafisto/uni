package app.controller.validators;

public class GUIFieldValidator {
    /**
     * Validates the speed value provided as a string and returns it as a double.
     * 
     * @param speed the speed value to be validated
     * @return the validated speed value as a double
     * @throws NumberFormatException if the speed value is not a valid number or is less than or equal to 0
     */
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

    /**
     * Validates the height value provided as a string.
     *
     * @param height the height value to be validated
     * @return the validated height value as an integer
     * @throws NumberFormatException if the height value is not a valid integer or is less than or equal to 0
     */
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

    /**
     * Validates the width value provided as a string and returns the parsed integer value.
     * 
     * @param width the width value to be validated
     * @return the parsed integer value of the width
     * @throws NumberFormatException if the width value is not a valid integer or is less than or equal to 0
     */
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

    /**
     * Validates a probability value and converts it to a decimal representation.
     * The probability value must be between 0 and 100 (inclusive).
     *
     * @param probabilityValue the probability value to validate
     * @return the decimal representation of the probability value
     * @throws NumberFormatException if the probability value is not within the valid range
     */
    public static double validateProbability(double probabilityValue) throws NumberFormatException {
        if (probabilityValue >= 0 && probabilityValue <= 100) {
            return probabilityValue / 100.0;
        }
        throw new NumberFormatException("Probability % must be between 0 and 100");
    }
}
