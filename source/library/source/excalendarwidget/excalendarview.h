#ifndef EXCALENDARWIDGET_EXCALENDARVIEW_H
#define EXCALENDARWIDGET_EXCALENDARVIEW_H

#include <QTableWidget>

class QDate;

class ExCalendarViewPrivate;

class ExCalendarView : public QTableWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(ExCalendarView)

    ExCalendarViewPrivate * const d_ptr;
public:
    virtual ~ExCalendarView();

    QDate minimumDate() const;
    QDate maximumDate() const;

    QDate currentDate() const;
signals:
    void currentDateChanged(const QDate &date);

    void dateClicked(const QDate &date);
public slots:
    void setMinimumDate(const QDate &date);
    void setMaximumDate(const QDate &date);

    void setDateRange(const QDate &min_date, const QDate &max_date);

    void setCurrentDate(const QDate &date);

    void animatedSlideRight();
    void animatedSlideLeft();
    void animatedSlideTop();
    void animatedSlideBottom();
protected:
    explicit ExCalendarView(QWidget *parent = 0);

    virtual void applyDateRange(const QDate &min, const QDate &max);

    virtual void prepareDateChange(const QDate &date);
};

#endif // EXCALENDARWIDGET_EXCALENDARVIEW_H
