package app.model;

import java.util.ArrayList;
import java.util.concurrent.TimeUnit;

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
    private Object locker;

    public ModelCell(int id, Object locker) {
        this.id = id;
        this.running = false;
        this.thread = null;
        this.color = UtilsColor.randomColor();
        this.neighbors = new ArrayList<ModelCell>();
        this.locker = locker;
    }

    private void start() {
        AppLogger.logger.info("Starting cell thread");
        this.thread = new Thread(() -> {
            while (true) {
                try {
                    TimeUnit.MILLISECONDS.sleep(UtilsRandom.randomTimeSpan(ModelParameters.getInstance().getSpeed()));
                    AppLogger.logger.info("[ModelCell" + this.id + "] Running");
                    synchronized (locker) {
                        if (!this.isRunning())
                            TimeUnit.MILLISECONDS.sleep(10);
                        if (UtilsRandom.coinFlip(ModelParameters.getInstance().getProbability())) {
                            this.setColor(UtilsColor.randomColor());
                        } else {
                            ArrayList<Color> neighborColors = new ArrayList<>();
                            for (ModelCell neighbor : this.neighbors) {
                                neighborColors.add(neighbor.getColor());
                            }
                            this.setColor(UtilsColor.calculateNewColor(neighborColors));
                        }
                        AppLogger.logger.info("[ModelCell" + this.id + "] New color: " + this.getColor());
                    }
                } catch (InterruptedException e) {
                    AppLogger.logger.warning("[ModelCell" + this.id + "] Thread interrupted: " + e.getMessage());
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

    public synchronized boolean isRunning() {
        return this.running;
    }

    public void InitializeCell() {
        this.start();
    }

    public synchronized void RunCell() {
        this.running = true;
    }

    public synchronized void SuspendCell() {
        this.running = false;

    }

    public synchronized Color getColor() {
        return this.color;
    }

    public synchronized void setColor(Color color) {
        synchronized (this.neighbors.get(0)) {
            synchronized (this.neighbors.get(1)) {
                synchronized (this.neighbors.get(2)) {
                    synchronized (this.neighbors.get(3)) {
                        this.color = color;
                    }
                }
            }
        }
    }
}