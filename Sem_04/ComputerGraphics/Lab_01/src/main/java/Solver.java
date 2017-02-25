import java.awt.*;
import java.util.Vector;

/**
 * Created by lieroz on 25.02.17.
 */

public class Solver {
    public static Point[] getMinimalAngle(Vector<Point>[] fieldSets) {
        Vector<Point> first = getAltitudesIntersectionPoints(fieldSets[0]);
        Vector<Point> second = getAltitudesIntersectionPoints(fieldSets[1]);

        double minAngle = Integer.MAX_VALUE;
        Point firstPoint = new Point();
        Point secondPoint = new Point();

        for (Point firstSetPoint : first) {

            for (Point secondSetPoint : second) {
                double angle = Math.tan(Math.toRadians(Math.abs(firstSetPoint.x - secondSetPoint.x) /
                        Math.abs(firstSetPoint.y - secondSetPoint.y)));

                if (angle < minAngle) {
                    minAngle = angle;
                    firstPoint = firstSetPoint;
                    secondPoint = secondSetPoint;
                }
            }
        }

        return new Point[]{firstPoint, secondPoint};
    }

    private static Vector<Point> getAltitudesIntersectionPoints(Vector<Point> vector) {
        Vector<Point> altitudesIntersection = new Vector<>();

        for (int i = 0; i < vector.size() - 2; ++i) {

            for (int j = i + 1; j < vector.size() - 1; ++j) {

                for (int k = j + 1; k < vector.size(); ++k) {
                    altitudesIntersection.add(findIntersectionAltitudesPoint(vector.get(i), vector.get(j), vector.get(k)));
                }
            }
        }

        return altitudesIntersection;
    }

    private static Point findIntersectionAltitudesPoint(Point A, Point B, Point C) {
        int k1 = (B.x - A.x) != 0 ? Math.round(-((B.y - A.y) / (B.x - A.x))) : 0;
        int b1 = Math.round(C.y - k1 * C.x);

        int k2 = (C.x - A.x) != 0 ? Math.round(-((C.y - A.y) / (C.x - A.x))) : 0;
        int b2 = Math.round(A.y - k2 * A.x);

        int x = (k1 - k2) != 0 ? Math.round((b2 - b1) / (k1 - k2)) : 0;
        int y = Math.round(k1 * x + b1);

        return new Point(x, y);
    }
}
