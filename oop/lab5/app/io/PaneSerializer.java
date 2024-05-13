package app.io;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.Node;
import java.io.*;

import app.logger.AppLogger;

public class PaneSerializer {

    public static void serializePane(ObservableList<Node> nodes, String filename) {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filename))) {
            oos.writeInt(nodes.size());
            for (Node n : nodes) {
                if (n instanceof Serializable) {
                    oos.writeObject(n);
                }
            }
            AppLogger.logger.info("Saved number of figures: " + nodes.size());
            AppLogger.logger.info("Pane data saved successfully");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static ObservableList<Node> deserializePane(String filename) {
        ObservableList<Node> nodes = FXCollections.observableArrayList();
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(filename))) {
            int numNodes = ois.readInt();
            for (int i = 0; i < numNodes; i++) {
                Node n = (Node) ois.readObject();
                AppLogger.logger.info("Loaded: " + n.toString());
                nodes.add(n);
            }
            AppLogger.logger.info("Loaded number of figures: " + nodes.size());
            AppLogger.logger.info("Pane data deserialized successfully");
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        return nodes;
    }
}
