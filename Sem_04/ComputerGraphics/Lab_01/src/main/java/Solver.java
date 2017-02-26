import java.awt.*;
import java.util.Vector;

/**
 * Created by lieroz on 25.02.17.
 */

public class Solver {
    public static Vector<Point[]> firstSetTriangles = new Vector<>();
    public static Vector<Point[]> secondSetTriangles = new Vector<>();

    public static int firstIndex = 0;
    public static int secondIndex = 0;

    public static Point[] getMinimalAngle(Vector<Point>[] fieldSets) {
        Vector<Point> first = getAltitudesIntersectionPoints(fieldSets[0], firstSetTriangles);
        Vector<Point> second = getAltitudesIntersectionPoints(fieldSets[1], secondSetTriangles);

        double minAngle = Integer.MAX_VALUE;
        Point firstPoint = new Point();
        Point secondPoint = new Point();

        int firstCounter = 0;

        for (Point firstSetPoint : first) {
            int secondCounter = 0;

            for (Point secondSetPoint : second) {
                double width = Math.abs(firstSetPoint.x - secondSetPoint.x);
                double height = Math.abs(firstSetPoint.y - secondSetPoint.y);
                double angle = Math.toDegrees(Math.atan(height / width));

                if (angle < minAngle) {
                    minAngle = angle;
                    firstPoint = firstSetPoint;
                    secondPoint = secondSetPoint;
                    firstIndex = firstCounter;
                    secondIndex = secondCounter;
                }

                ++secondCounter;
            }

            ++firstCounter;
        }

        return new Point[]{firstPoint, secondPoint};
    }

    private static Vector<Point> getAltitudesIntersectionPoints(Vector<Point> vector, Vector<Point[]> triangles) {
        Vector<Point> altitudesIntersection = new Vector<>();

        for (int i = 0; i < vector.size() - 2; ++i) {

            for (int j = i + 1; j < vector.size() - 1; ++j) {

                for (int k = j + 1; k < vector.size(); ++k) {
                    altitudesIntersection.add(findIntersectionAltitudesPoint(vector.get(i), vector.get(j), vector.get(k)));
                    triangles.add(new Point[]{vector.get(i), vector.get(j), vector.get(k)});
                }
            }
        }

        return altitudesIntersection;
    }

    private static Point findIntersectionAltitudesPoint(Point A, Point B, Point C) {
        double a1 = (B.x - A.x);
        double b1 = (A.y - B.y);
        double c1 = a1 * C.x - b1 * C.y;

        double a2 = (C.x - A.x);
        double b2 = (A.y - C.y);
        double c2 = a2 * B.x - b2 * B.y;

        int x = b1 != 0 ? (int) Math.round((c1 * b2 / b1 - c2) / (a2 - a1 * b2 / b1)) : (int) Math.round((c1 * b1 / b2 - c1) / (a1 - a2 * b1 / b2));
        int y = b1 != 0 ? (int) Math.round(-(a1 * x + c1) / b1) : (int) Math.round(-(a2 * x + c2) / b2);

        return new Point(-x, y);
    }
}
