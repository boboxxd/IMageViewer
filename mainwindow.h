#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSettings>
namespace Ui {
class MainWindow;
}
class QListWidgetItem;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    ~MainWindow();

signals:
    void sendimagename(const QString &);
protected:
    int index;
private:
    Ui::MainWindow *ui;
    QMenu *filemenu;
    QAction *openaction;
    QAction *opendiraction;

    QAction *nextaction;
    QAction *priviousaction;

    QLineEdit *statusedit;
    QStringList filelist;

    QSettings sets;

    void initWidget();
    void setlistWidget();
    void open();
    void opendir();
    void openfromlist(QListWidgetItem *item);
    void openfile(QString path);
    void next();
    void privious();

};

#endif // MAINWINDOW_H
