package app.model;

import java.util.ArrayList;

import app.logger.AppLogger;
import app.utils.UtilsColor;
import app.utils.UtilsRandom;
import javafx.scene.paint.Color;

public class ModelCell {
    private final int id;
    private final ArrayList<ModelCell> neighbors;

    private boolean running;
    private Thread thread;
    private Color color;

    public ModelCell(int id) {
        this.id = id;
        this.running = true;
        this.thread = null;
        this.color = UtilsColor.randomColor();
        this.neighbors = new ArrayList<ModelCell>();
    }

    private void start() {
        AppLogger.logger.info("Starting cell thread");
        this.thread = new Thread(() -> {
            while (this.running) {
                try {
                    Thread.sleep((long) (UtilsRandom.randomTimeSpan(ModelParameters.getInstance().getSpeed())));
                    this.color = UtilsColor.randomColor();
                } catch (InterruptedException e) {
                    AppLogger.logger.warning("[ModelCell" + this.id + "] Thread interrupted: " + e.getMessage());
                    System.exit(-1);
                }

            }
        });
        this.thread.start();
    }

    public void addNeighbor(ModelCell neighbor) {
        this.neighbors.add(neighbor);
    }

    public void setNeighbors(ArrayList<ModelCell> neighbors) {
        this.neighbors.addAll(neighbors);
    }

    public boolean isRunning() {
        return this.running;
    }

    public void switchRunning() {
        this.running = !this.running;
        if (this.running) {
            this.start();
        }
    }

    public Color getColor() {
        return this.color;
    }

    public synchronized void setColor(Color color) {
        this.color = color;
    }
}