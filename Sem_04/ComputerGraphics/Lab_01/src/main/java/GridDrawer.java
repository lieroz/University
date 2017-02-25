import com.sun.javafx.geom.Vec2d;

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

    private Dimension window = new Dimension(1400, 800);
    private double dimensionRatio = 1;

    public GridDrawer(Vector<Point>[] fieldSets) {
        firstSet = fieldSets[0];
        secondSet = fieldSets[1];
        setBackground(Color.WHITE);
        setDimension();
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

        vector.forEach(point -> {
            graphics.fillOval(point.x, point.y, 5, 5);
        });
    }

    private void setDimension() {
        Vector<Point> set = new Vector<>();
        set.addAll(firstSet);
        set.addAll(secondSet);

        Point[] extremeCoordinates = seekExtremeCoordinates(set);

        int windowWidth = extremeCoordinates[1].x - extremeCoordinates[0].x;
        int windowHeight = extremeCoordinates[1].y - extremeCoordinates[0].y;
        dimensionRatio = Math.min(window.getHeight() / windowHeight, window.getWidth() / windowWidth);

        normalizePoints(firstSet, extremeCoordinates[0]);
        normalizePoints(secondSet, extremeCoordinates[0]);
    }

    private void normalizePoints(Vector<Point> vector, Point extremePoint) {
        vector.forEach(point -> {
            point.x += Math.abs(extremePoint.x);
            point.x *= dimensionRatio;

            point.y += Math.abs(extremePoint.y);
            point.y *= dimensionRatio;
            point.y = (int) window.getHeight() - point.y;
        });
    }

    private Point[] seekExtremeCoordinates(Vector<Point> vector) {
        Point minCoordinates = new Point(vector.get(0));
        Point maxCoordinates = new Point(vector.get(0));

        vector.forEach(point -> {

            if (minCoordinates.x > point.x) {
                minCoordinates.x = point.x;
            }

            if (minCoordinates.y > point.y) {
                minCoordinates.y = point.y;
            }

            if (maxCoordinates.x < point.x) {
                maxCoordinates.x = point.x;
            }

            if (maxCoordinates.y < point.y) {
                maxCoordinates.y = point.y;
            }
        });

        return new Point[]{minCoordinates, maxCoordinates};
    }

    private void drawLine(Graphics graphics) {
        Point[] points = Solver.getMinimalAngle(new Vector[]{firstSet, secondSet});

        graphics.setColor(Color.MAGENTA);
        graphics.drawLine(points[0].x, (int) window.getHeight() - points[0].y,
                points[1].x, (int) window.getHeight() - points[1].y);
    }

    @Override
    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);
        drawGrid(graphics);
        drawPoints(graphics);
        drawLine(graphics);
    }
}
