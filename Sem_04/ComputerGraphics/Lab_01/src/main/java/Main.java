import java.awt.*;

/**
 * Created by lieroz on 21.02.17.
 * Organisation park.mail.ru.
 */
public class Main {
    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            MainWindow ex = new MainWindow();
            ex.setVisible(true);
        });
    }
}
