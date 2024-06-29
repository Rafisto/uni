package app.model;

import java.util.ArrayList;

import app.logger.AppLogger;

public class ModelGrid {
    private final Object locker = new Object();
    private ArrayList<ArrayList<ModelCell>> grid;

    /**
     * Constructs a ModelGrid with the specified parameters.
     * 
     * @param speed       the speed value for each ModelCell in the grid
     * @param probability the probability value for each ModelCell in the grid
     * @param width       the width of the grid
     * @param height      the height of the grid
     * 
     * @see ModelCell
     */
    public ModelGrid(double speed, double probability, int width, int height) {
        this.grid = new ArrayList<>();

        for (int i = 0; i < height; i++) {
            ArrayList<ModelCell> row = new ArrayList<>();
            for (int j = 0; j < width; j++) {
                AppLogger.logger.fine("Adding ModelCell to ModelGrid at row: " + i + ", column: " + j);
                row.add(new ModelCell(i * width + j, speed, probability, this.locker));
            }
            this.grid.add(row);
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                ArrayList<ModelCell> neighbors = new ArrayList<>();
                neighbors.add(this.grid.get(((i - 1) + height) % height).get(j));
                neighbors.add(this.grid.get(((i + 1) + height) % height).get(j));
                neighbors.add(this.grid.get(i).get(((j - 1) + width) % width));
                neighbors.add(this.grid.get(i).get(((j + 1) + width) % width));
                this.getCell(i, j).setNeighbors(neighbors);
            }
        }
    }

    /**
     * Starts the simulation by calling the start method on each cell in the grid.
     */
    public void Start() {
        for (ArrayList<ModelCell> row : this.grid) {
            for (ModelCell cell : row) {
                cell.start();
            }
        }
    }

    /**
     * Returns the ModelCell at the specified position in the grid.
     *
     * @param i the row index of the cell
     * @param j the column index of the cell
     * @return the ModelCell at the specified position
     */
    public ModelCell getCell(int i, int j) {
        return this.grid.get(i).get(j);
    }
}
