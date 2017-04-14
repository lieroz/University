#include <QApplication>

#include "gui/mainwindow.hpp"
#include "container/vector/vector.hpp"

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.show();

    vector<int> my_vec;

    for (int i = 0; i < 10; ++i) {
        my_vec.push_back(i);
    }

    for (vector<int>::iterator iter = my_vec.begin(); iter != my_vec.end(); ++iter) {
        std::cout << *iter << " ";
    }

    std::cout << std::endl << my_vec << std::endl;

    return application.exec();
}
