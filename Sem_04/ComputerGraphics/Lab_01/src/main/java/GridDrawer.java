import javax.swing.*;
import java.awt.*;
import java.util.Vector;

/**
 * Created by lieroz on 21.02.17.
 * Organisation park.mail.ru.
 */
public class GridDrawer extends JPanel {
    private Vector<Point> firstSet;
    private Vector<Point> secondSet;

    public GridDrawer(Vector<Point>[] fieldSets) {
        firstSet = fieldSets[0];
        secondSet = fieldSets[1];
        setBackground(Color.WHITE);
    }

    private void drawGrid(Graphics graphics) {
        graphics.setColor(Color.LIGHT_GRAY);

        for (int i = 7; i < getHeight(); i += 7) {
            graphics.drawLine(0, i, getWidth(), i);
        }

        for (int i = 7; i < getWidth(); i += 7) {
            graphics.drawLine(i, 0, i, getHeight());
        }
    }

    private void drawPoints(Graphics graphics) {
        getPoints(firstSet, graphics, Color.RED);
        getPoints(secondSet, graphics, Color.BLUE);
    }

    private void getPoints(Vector<Point> vector, Graphics graphics, Color color) {
        graphics.setColor(color);

        vector.forEach((point) -> {
            graphics.fillOval(point.x, point.y, 5, 5);
        });
    }

    @Override
    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);
        drawGrid(graphics);
        drawPoints(graphics);
    }
}
