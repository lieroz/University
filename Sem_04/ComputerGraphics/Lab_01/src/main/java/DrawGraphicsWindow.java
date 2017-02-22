import java.awt.*;
import java.util.Vector;
import javax.swing.*;

/**
 * Created by lieroz on 21.02.17.
 * Organisation park.mail.ru.
 */
public class DrawGraphicsWindow extends JFrame {
    public DrawGraphicsWindow(Vector<Point>[] fieldSets) {
        add(new GridDrawer(fieldSets));
        initUI();
    }

    private void initUI() {
        setTitle("Graphics drawing window");
        setLocation(0, 0);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setMinimumSize(new Dimension(1000, 500));
        setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
    }
}
