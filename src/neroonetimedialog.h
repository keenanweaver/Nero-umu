#ifndef NEROONETIMEDIALOG_H
#define NEROONETIMEDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class NeroOneTimeDialog;
}

class NeroOneTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NeroOneTimeDialog(QWidget *parent = nullptr);
    ~NeroOneTimeDialog();

    QString selected;

private slots:
    void prefixBtn_clicked() {
        QPushButton *btn = qobject_cast<QPushButton*>(sender());
        selected = btn->text();
        close();
    }

private:
    Ui::NeroOneTimeDialog *ui;

    unsigned int LOLRANDOM;
    QList<QPushButton*> prefixesBtns;
};

#endif // NEROONETIMEDIALOG_H
