import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.util.LinkedHashMap;
import java.util.Vector;

/**
 * Created by lieroz on 20.02.17.
 * Organisation park.mail.ru.
 */
public class MainWindow extends JFrame {
    private JPanel rootPanel;

    private JPanel leftPanel;
    private JPanel rightPanel;

    private JPanel firstAxisPaneX;
    private JPanel firstAxisPaneY;
    private JPanel secondAxisPaneX;
    private JPanel secondAxisPaneY;

    private JButton addFirstSetPointButton;
    private JButton removeFirstSetPointButton;
    private JButton calculateButton;
    private JButton removeSecondSetPointButton;
    private JButton addSecondSetPointButton;

    private GridBagConstraints gridBagConstraints = new GridBagConstraints();

    private LinkedHashMap<JTextField, JTextField> firstSetFieldsContainer = new LinkedHashMap<>();
    private LinkedHashMap<JTextField, JTextField> secondSetFieldsContainer = new LinkedHashMap<>();

    private Vector<Point> firstSetPoints;
    private Vector<Point> secondSetPoints;

    private int firstPanePointsCount = 3;
    private int secondPanePointsCount = 3;

    private boolean canRemoveFirstSetPoint = false;
    private boolean canRemoveSecondSetPoint = false;

    public MainWindow() {
        super("Coordinates input");
        setContentPane(rootPanel);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        setLayouts();
        setPanels();

        JScrollPane jScrollPane = new JScrollPane(rootPanel,
                ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,
                ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
        jScrollPane.getVerticalScrollBar().setUnitIncrement(16);
        setContentPane(jScrollPane);

        addFirstSetPointButton.addActionListener((ActionEvent e) -> {
            addFields(new JPanel[]{firstAxisPaneX, firstAxisPaneY}, firstPanePointsCount++);
            validate();
            jScrollPane.getViewport().setViewPosition(new Point(0, rootPanel.getSize().height));
        });

        removeFirstSetPointButton.addActionListener((ActionEvent e) -> {
            canRemoveFirstSetPoint = firstPanePointsCount > 3;

            if (canRemoveFirstSetPoint) {
                removeFields(new JPanel[]{firstAxisPaneX, firstAxisPaneY}, --firstPanePointsCount);
                validate();
                jScrollPane.getViewport().setViewPosition(new Point(0, rootPanel.getSize().height));
            }
        });

        calculateButton.addActionListener((ActionEvent e) -> {
            firstSetPoints = getPointsFromFields(firstSetFieldsContainer);
            secondSetPoints = getPointsFromFields(secondSetFieldsContainer);

            DrawGraphicsWindow win = new DrawGraphicsWindow(new Vector[]{firstSetPoints, secondSetPoints});
            win.setVisible(true);
        });

        removeSecondSetPointButton.addActionListener((ActionEvent e) -> {
            canRemoveSecondSetPoint = secondPanePointsCount > 3;

            if (canRemoveSecondSetPoint) {
                removeFields(new JPanel[]{secondAxisPaneX, secondAxisPaneY}, --secondPanePointsCount);
                validate();
                jScrollPane.getViewport().setViewPosition(new Point(0, rootPanel.getSize().height));
            }
        });

        addSecondSetPointButton.addActionListener((ActionEvent e) -> {
            addFields(new JPanel[]{secondAxisPaneX, secondAxisPaneY}, secondPanePointsCount++);
            validate();
            jScrollPane.getViewport().setViewPosition(new Point(0, rootPanel.getSize().height));
        });

        pack();
        setMinimumSize(new Dimension(480, 250));
        setLocationRelativeTo(null);
        setResizable(false);
    }

    private void setLayouts() {
        firstAxisPaneX.setLayout(new GridBagLayout());
        firstAxisPaneY.setLayout(new GridBagLayout());
        secondAxisPaneX.setLayout(new GridBagLayout());
        secondAxisPaneY.setLayout(new GridBagLayout());
    }

    private void setPanels() {
        setFields(new JPanel[]{firstAxisPaneX, firstAxisPaneY});
        setFields(new JPanel[]{secondAxisPaneX, secondAxisPaneY});
    }

    private void setFields(JPanel[] panels) {
        for (int i = 0; i < 3; ++i) {
            addFields(panels, i);
        }
    }

    private void addFields(JPanel[] panels, int count) {
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = count;
        gridBagConstraints.anchor = GridBagConstraints.NORTH;
        panels[0].add(new JLabel("X" + Integer.toString(count + 1) + ": "), gridBagConstraints);

        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = count;
        gridBagConstraints.anchor = GridBagConstraints.NORTH;
        JTextField textFieldX = new JTextField(4);
        panels[0].add(textFieldX, gridBagConstraints);

        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = count;
        gridBagConstraints.anchor = GridBagConstraints.NORTH;
        panels[1].add(new JLabel("Y" + Integer.toString(count + 1) + ": "), gridBagConstraints);

        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = count;
        gridBagConstraints.anchor = GridBagConstraints.NORTH;
        JTextField textFieldY = new JTextField(4);
        panels[1].add(textFieldY, gridBagConstraints);

        if (panels[0] == firstAxisPaneX && panels[1] == firstAxisPaneY) {
            firstSetFieldsContainer.put(textFieldX, textFieldY);

        } else if (panels[0] == secondAxisPaneX && panels[1] == secondAxisPaneY) {
            secondSetFieldsContainer.put(textFieldX, textFieldY);
        }
    }

    private void removeFields(JPanel[] panels, int count) {
        panels[0].remove(count * 2);
        panels[0].remove(count * 2);
        panels[1].remove(count * 2);
        panels[1].remove(count * 2);

        if (panels[0] == firstAxisPaneX && panels[1] == firstAxisPaneY) {
            removeLastElement(firstSetFieldsContainer);

        } else if (panels[0] == secondAxisPaneX && panels[1] == secondAxisPaneY) {
            removeLastElement(secondSetFieldsContainer);
        }
    }

    private <K, V> void removeLastElement(LinkedHashMap<K, V> map) {
        K lastElementKey = null;

        for (K key : map.keySet()) {
            lastElementKey = key;
        }

        map.remove(lastElementKey);
    }

    private Vector<Point> getPointsFromFields(LinkedHashMap<JTextField, JTextField> map) {
        Vector<Point> vector = new Vector<>();

        map.forEach((key, value) -> {
            String dataX = key.getText();
            String dataY = value.getText();

            if (!dataX.isEmpty() && !dataY.isEmpty()) {
                vector.add(new Point(Integer.parseInt(dataX), Integer.parseInt(dataY)));
            }
        });

        return vector;
    }
}
