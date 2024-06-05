package app.model;

import java.util.ArrayList;

public class ModelGrid {
    private static ModelGrid instance;
    private boolean running;
    private ArrayList<ArrayList<ModelCell>> grid;

    public static ModelGrid getInstance() {
        if (instance == null) {
            instance = new ModelGrid();
        }
        return instance;
    }

    private ModelGrid() {
        this.running = false;
        this.grid = new ArrayList<>();

        int width = ModelParameters.getInstance().getWidth();
        int height = ModelParameters.getInstance().getHeight();

        for (int i = 0; i < height; i++) {
            ArrayList<ModelCell> row = new ArrayList<>();
            for (int j = 0; j < width; j++) {
                row.add(new ModelCell(i+j));
            }
            this.grid.add(row);
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                ArrayList<ModelCell> neighbors = new ArrayList<>();
                if (i > 0) {
                    neighbors.add(this.grid.get(i - 1).get(j));
                }
                if (i < height - 1) {
                    neighbors.add(this.grid.get(i + 1).get(j));
                }
                if (j > 0) {
                    neighbors.add(this.grid.get(i).get(j - 1));
                }
                if (j < width - 1) {
                    neighbors.add(this.grid.get(i).get(j + 1));
                }
                this.grid.get(i).get(j).setNeighbors(neighbors);
            }
        }
    }

    public void Start() {
        if (this.running) return;

        this.running = true;
        for (ArrayList<ModelCell> row : this.grid) {
            for (ModelCell cell : row) {
                cell.switchRunning();
            }
        }
    }

    public ModelCell getCell(int i, int j) {
        return this.grid.get(i).get(j);
    }

    public ModelCell getCell(int id) {
        int width = ModelParameters.getInstance().getWidth();
        return this.grid.get(id / width).get(id % width);
    }
}
