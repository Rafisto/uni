package app.model;

import java.util.ArrayList;

import app.controller.GUICell;
import app.logger.AppLogger;
import app.utils.UtilsColor;
import app.utils.UtilsRandom;
import javafx.scene.paint.Color;

public class ModelCell extends Thread {
    private final int id;
    private final double speed;
    private final double probability;

    private GUICell guiRepresentation;
    private Object locker;

    private ArrayList<ModelCell> neighbors;

    private boolean isRunning = true;
    private Color color;

    /**
     * Represents a cell in the model. A cell has a unique id, a speed, a
     * probability, and a color.
     * Throws IllegalArgumentException if the speed is less than 0, the probability
     * is less than 0 or greater than 1, or if the gridLocker is null.
     * 
     * @param id          the id of the cell
     * @param speed       the speed of the cell
     * @param probability the probability of the cell
     * @param gridLocker  the locker object for the grid
     * 
     * @see GUICell
     */
    public ModelCell(int id, double speed, double probability, Object gridLocker) throws IllegalArgumentException {
        if (speed < 0 || probability < 0 || probability > 1) {
            throw new IllegalArgumentException("Invalid speed or probability input parameters");
        }
        if (gridLocker == null) {
            throw new IllegalArgumentException("Invalid gridLocker, cannot be null");
        }
        this.id = id;
        this.speed = speed;
        this.probability = probability;
        this.locker = gridLocker;

        this.color = UtilsColor.randomColor();
    }

    /**
     * Sets the neighbors of the current cell.
     *
     * @param neighbors the list of neighboring cells
     * 
     * @see ModelGrid
     */
    public final void setNeighbors(ArrayList<ModelCell> neighbors) throws IllegalArgumentException {
        if (neighbors.size() != 4) {
            throw new IllegalArgumentException("Invalid number of neighbors");
        }
        this.neighbors = neighbors;
    }

    /**
     * Sets the GUI representation of the model cell.
     *
     * @param guiRepresentation the GUI representation to be set
     */
    public final void setGUIRepresentation(GUICell guiRepresentation) throws IllegalArgumentException {
        if (guiRepresentation == null) {
            throw new IllegalArgumentException("Invalid GUI representation, cannot be null");
        }
        this.guiRepresentation = guiRepresentation;
    }

    /**
     * Updates the GUI representation of the cell with the specified color.
     * If the GUI representation is not null, it calls the update method on it
     * passing the specified color as a parameter.
     *
     * @param color the color to update the GUI representation with
     */
    private final void updateGUI(Color color) {
        if (this.guiRepresentation != null) {
            this.guiRepresentation.update(color);
        }
    }

    /**
     * Returns the color of the cell.
     *
     * @return the color of the cell
     */
    public synchronized final Color getColor() {
        return this.color;
    }

    /**
     * Returns the current running state of the cell.
     *
     * @return true if the cell is running, false otherwise.
     */
    public synchronized final boolean isRunning() {
        return this.isRunning;
    }

    /**
     * Sets the running state of the cell.
     *
     * @param isRunning the running state to be set
     */
    public synchronized final void changeRunningState() {
        synchronized (this) {
            this.isRunning = !isRunning;

            if (this.isRunning) {
                updateGUI(null);
                AppLogger.logger.info("[STATE CHANGE] Cell " + this.id + " is now running");
            }

            else {
                updateGUI(Color.WHITE);
                AppLogger.logger.info("[STATE CHANGE] Cell " + this.id + " is now stopped");
            }
        }
    }

    /**
     * Changes the color of the cell according to the simulation rules.
     * If the number of neighbors is not equal to 4, an IllegalArgumentException is
     * thrown.
     * If the probability check passes, the color of the cell is set to a random
     * color.
     * Otherwise, the color of the cell is calculated based on the colors of the
     * operating neighbors.
     *
     * @throws IllegalArgumentException if the number of neighbors is not equal to 4
     */
    public final void changeColor() throws IllegalArgumentException {
        synchronized (locker) {
            synchronized (this) {
                if (neighbors.size() != 4) {
                    throw new IllegalArgumentException("Invalid number of neighbors");
                }
                synchronized (neighbors.get(0)) {
                    synchronized (neighbors.get(1)) {
                        synchronized (neighbors.get(2)) {
                            synchronized (neighbors.get(3)) {
                                AppLogger.logger.info("[START] Cell " + this.id + " is changing color");
                                if (UtilsRandom.coinFlip(probability)) {
                                    this.color = UtilsColor.randomColor();
                                } else {
                                    ArrayList<Color> neighbor_colors = new ArrayList<>();
                                    for (ModelCell neighbor : neighbors) {
                                        if (neighbor.isRunning()) {
                                            neighbor_colors.add(neighbor.getColor());
                                        }
                                    }
                                    AppLogger.logger.fine("[NEIGHBORS] Cell " + this.id + " has fetched "
                                            + neighbor_colors.size() + " colors of operating neighbors");
                                    this.color = UtilsColor.calculateNewColor(neighbor_colors);
                                }
                                this.updateGUI(this.color);
                                AppLogger.logger.info("[END] Cell " + this.id + " changed color to " + color);
                            }
                        }
                    }
                }
            }
        }
    }

    /**
     * Runs the cell in a separate thread.
     * The cell continuously changes its color while it is alive and running.
     * The color change is controlled by the `isRunning` flag.
     * The cell sleeps for a random time span determined by the `speed` parameter
     * between color changes.
     * If the thread is interrupted, a warning message is logged.
     */
    public void run() {
        while (isAlive()) {
            if (isRunning) {
                changeColor();
            }
            try {
                sleep(UtilsRandom.randomTimeSpan(speed));
            } catch (InterruptedException e) {
                AppLogger.logger.warning("Cell " + this.id + " interrupted");
            }
        }
    }
}