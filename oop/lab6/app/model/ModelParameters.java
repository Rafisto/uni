package app.model;

public class ModelParameters {
    private static ModelParameters instance;
    private double speed;
    private double probability;
    private int width;
    private int height;

    private ModelParameters() {
        this.speed = 1000.0;
        this.probability = 0.55;
        this.width = 30;
        this.height = 20;
    }

    public static ModelParameters getInstance() {
        if (instance == null) {
            instance = new ModelParameters();
        }
        return instance;
    }

    public void setParameters(double speed, double probability, int width, int height) throws IllegalArgumentException {
        if (speed <= 0) {
            throw new IllegalArgumentException("Speed must be greater than 0");
        }
        if (probability < 0 || probability > 1) {
            throw new IllegalArgumentException("Probability must be between 0 and 1");
        }
        if (width <= 0) {
            throw new IllegalArgumentException("Width must be greater than 0");
        }
        if (height <= 0) {
            throw new IllegalArgumentException("Height must be greater than 0");
        }

        this.speed = speed;
        this.probability = probability;
        this.width = width;
        this.height = height;
    }

    public double getSpeed() {
        return speed;
    }

    public double getProbability() {
        return probability;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public void setSpeed(double speed) {
        this.speed = speed;
    }

    public void setProbability(double probability) {
        this.probability = probability;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public void setHeight(int height) {
        this.height = height;
    }
}