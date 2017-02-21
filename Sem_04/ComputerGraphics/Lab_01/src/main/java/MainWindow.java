import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.util.HashMap;

/**
 * Created by lieroz on 20.02.17.
 * Organisation park.mail.ru.
 */
public class MainWindow extends JFrame {
    private JPanel rootPanel;

    private JButton addFirstSetPointButton;
    private JButton calculateButton;
    private JButton addSecondSetPointButton;

    private JPanel firstAxisPaneX;
    private JPanel firstAxisPaneY;
    private JPanel secondAxisPaneX;
    private JPanel secondAxisPaneY;

    private GridBagConstraints gridBagConstraints = new GridBagConstraints();
    private HashMap<JTextField, JTextField> fieldsContainer = new HashMap<>();

    private int firstPanePointsCount = 3;
    private int secondPanePointsCount = 3;

    public MainWindow() {
        super("Coordinates input");
        setContentPane(rootPanel);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        setLayouts();
        setPanels();

        addFirstSetPointButton.addActionListener((ActionEvent e) -> {
            addFields(new JPanel[]{firstAxisPaneX, firstAxisPaneY} ,firstPanePointsCount++);
            validate();
        });

        calculateButton.addActionListener((ActionEvent e) -> {
            // TODO add here a call to another class constructor
            fieldsContainer.forEach((key, value) -> {
                String dataX = key.getText();
                String dataY = value.getText();
                System.out.println(dataX + " " + dataY);
            });
        });

        addSecondSetPointButton.addActionListener((ActionEvent e) -> {
            addFields(new JPanel[]{secondAxisPaneX, secondAxisPaneY} ,secondPanePointsCount++);
            validate();
        });

        pack();
        setMinimumSize(new Dimension(451, 198));
        setLocationRelativeTo(null);
//        setResizable(false);
    }

    private void setLayouts() {
        firstAxisPaneX.setLayout(new GridBagLayout());
        firstAxisPaneY.setLayout(new GridBagLayout());
        secondAxisPaneX.setLayout(new GridBagLayout());
        secondAxisPaneY.setLayout(new GridBagLayout());
    }

    private void setPanels() {
        setFields(firstAxisPaneX, "X");
        setFields(firstAxisPaneY, "Y");
        setFields(secondAxisPaneX, "X");
        setFields(secondAxisPaneY, "Y");
    }

    private void setFields(JPanel panel, String axis) {
        for (int i = 0; i < 3; ++i) {
            gridBagConstraints.gridx = 0;
            gridBagConstraints.gridy = i;
            gridBagConstraints.anchor = GridBagConstraints.NORTH;
            panel.add(new JLabel(axis + Integer.toString(i + 1) + ": "), gridBagConstraints);

            gridBagConstraints.gridx = 1;
            gridBagConstraints.gridy = i;
            gridBagConstraints.anchor = GridBagConstraints.NORTH;
            panel.add(new JTextField(4), gridBagConstraints);
        }
    }

    private void addFields(JPanel[] panels, Integer count) {
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = count;
        gridBagConstraints.anchor = GridBagConstraints.NORTH;
        panels[0].add(new JLabel("X" + Integer.toString(count + 1) + ": "), gridBagConstraints);

        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = count;
        gridBagConstraints.anchor = GridBagConstraints.NORTH;
        panels[0].add(new JTextField(4), gridBagConstraints);

        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = count;
        gridBagConstraints.anchor = GridBagConstraints.NORTH;
        panels[1].add(new JLabel("Y" + Integer.toString( count+ 1) + ": "), gridBagConstraints);

        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = count;
        gridBagConstraints.anchor = GridBagConstraints.NORTH;
        panels[1].add(new JTextField(4), gridBagConstraints);
    }
}
