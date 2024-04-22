import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

public class SimpleGUI extends JFrame {
    private JLabel label;
    private JButton button;
    private JTextField textField;

    public SimpleGUI() {
        setTitle("Simple GUI Example");
        setSize(500, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        label = new JLabel("Enter the number of rows (1-33):");
        textField = new JTextField(10);
        button = new JButton("Generate Pascal Triangle");

        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                generatePascalTriangle();
            }
        });

        JPanel inputPanel = new JPanel(new FlowLayout(FlowLayout.CENTER)); 
        inputPanel.add(label);
        inputPanel.add(textField);
        inputPanel.add(button);

        JPanel topPanel = new JPanel(new BorderLayout());
        topPanel.add(inputPanel, BorderLayout.NORTH);

        JPanel emptyPanel = new JPanel();
        
        JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, topPanel, emptyPanel);
        splitPane.setDividerLocation(80);
        getContentPane().add(splitPane);

        setVisible(true);
    }

    private void generatePascalTriangle() {
        String input = textField.getText();
        int numRows;
        try {
            numRows = Integer.parseInt(input);
            if (numRows < 1 || numRows > 33) {
                JOptionPane.showMessageDialog(this, "Please enter a number between 1 and 33.");
                return;
            }
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Invalid input. Please enter a valid number.");
            return;
        }

        JPanel trianglePanel = new JPanel(new GridLayout(0, 1));

        List<List<Integer>> triangle = new ArrayList<>();

        for (int i = 0; i < numRows; i++) {
            List<Integer> row = Binomials.generateRow(i);
            triangle.add(row);
        }

        for (List<Integer> row : triangle) {
            JPanel rowPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
            for (Integer value : row) {
                JLabel label = new JLabel(value.toString());
                rowPanel.add(label);
            }
            trianglePanel.add(rowPanel);
        }

        JSplitPane splitPane = (JSplitPane) getContentPane().getComponent(0);
        JScrollPane scrollPane = new JScrollPane(trianglePanel);
        int midpointX = (trianglePanel.getPreferredSize().width - scrollPane.getViewport().getWidth()) / 3;
        scrollPane.getViewport().setViewPosition(new Point(midpointX, 0));
        splitPane.setBottomComponent(scrollPane);
        revalidate();
    }
}
