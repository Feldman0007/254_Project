#ifndef PRIORITIZER_H
#define PRIORITIZER_H

#include <QMainWindow>

namespace Ui {
class Prioritizer;
}

class Prioritizer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Prioritizer(QWidget *parent = nullptr);
    ~Prioritizer();

private slots:
    void on_AddTask_clicked();

    void on_RemoveTask_clicked();

private:
    Ui::Prioritizer *ui;
};

#endif // PRIORITIZER_H
