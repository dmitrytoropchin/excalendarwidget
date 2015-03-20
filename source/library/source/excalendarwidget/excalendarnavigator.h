#ifndef EXCALENDARWIDGET_EXCALENDARNAVIGATOR_H
#define EXCALENDARWIDGET_EXCALENDARNAVIGATOR_H

#include <QFrame>

class QDate;
class QPushButton;

class ExCalendarNavigatorPrivate;

class ExCalendarNavigator : public QFrame {
    Q_OBJECT
    Q_DECLARE_PRIVATE(ExCalendarNavigator)

    ExCalendarNavigatorPrivate * const d_ptr;
public:
    enum State {
        StateMonth = 0,
        StateYear = 1,
        StateDecade = 2
    };
public:
    explicit ExCalendarNavigator(QWidget *parent = 0);
    ~ExCalendarNavigator();

    QDate minimumDate() const;
    QDate maximumDate() const;

    QDate currentDate() const;

    QPushButton *previousPeriodButton() const;
    QPushButton *nextPeriodButton() const;
signals:
    void currentDateChanged(const QDate &date);

    void stateChanged(int state, int previous_state);

    void previousPeriodButtonClicked();
    void nextPeriodButtonClicked();
public slots:
    void setMinimumDate(const QDate &date);
    void setMaximumDate(const QDate &date);

    void setDateRange(const QDate &min_date, const QDate &max_date);

    void setCurrentDate(const QDate &date);

    void toPreviousState();
    void toNextState();
private slots:
    void onViewButtonClicked();

    void onPreviousPeriodButtonClicked();
    void onNextPeriodButtonClicked();
};

#endif // EXCALENDARWIDGET_EXCALENDARNAVIGATOR_H
