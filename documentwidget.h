#ifndef DOCUMENTWIDGET_H
#define DOCUMENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include "baseuser.h"
class DocumentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DocumentWidget(QWidget *parent = 0,BaseUser *m_baseuser=0);

signals:

public slots:
    void s_counter();
private:
    QTextEdit *m_txt;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_buttonLayout;
    QHBoxLayout *m_creditLayout;
    void createLayouts();

    void closeFile();
    void readFile();

    QLabel*			m_time;
    QLabel*			m_credits;

    QPushButton* m_closeButton;
    QPushButton* m_ReportButton;

    int				m_timevalue;
    QTimer*			m_timer;
    int				m_currentCredits;
    BaseUser*		m_baseUser;
};

#endif // DOCUMENTWIDGET_H
