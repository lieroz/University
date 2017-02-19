import java.awt.EventQueue;
import javax.swing.JFrame;

public class MainApplication extends JFrame {

    public MainApplication() {

        initUI();
    }

    private void initUI() {

        setTitle("Simple example");
        setSize(300, 200);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    public static void main(String[] args) {

        EventQueue.invokeLater(() -> {
            MainApplication ex = new MainApplication();
            ex.setVisible(true);
        });
    }
}
