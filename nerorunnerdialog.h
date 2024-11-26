#ifndef NERORUNNERDIALOG_H
#define NERORUNNERDIALOG_H

#include <QDialog>
#include <QIcon>

namespace Ui {
class NeroRunnerDialog;
}

class NeroRunnerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NeroRunnerDialog(QWidget *parent = nullptr);
    ~NeroRunnerDialog();

    void SetupWindow(const bool & = false,
                     const QString & = "",
                     QIcon *icon = nullptr);
    void SetText(const QString &);

private:
    Ui::NeroRunnerDialog *ui;
};

#endif // NERORUNNERDIALOG_H
