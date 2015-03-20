#ifndef EXCALENDARWIDGET_EXCALENDARMONTHVIEW_H
#define EXCALENDARWIDGET_EXCALENDARMONTHVIEW_H

#include "excalendarwidget/excalendarview.h"

class ExCalendarMonthViewPrivate;

class ExCalendarMonthView : public ExCalendarView {
    Q_OBJECT
    Q_DECLARE_PRIVATE(ExCalendarMonthView)

    ExCalendarMonthViewPrivate * const d_ptr;
public:
    explicit ExCalendarMonthView(QWidget *parent = 0);
    ~ExCalendarMonthView();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
private slots:
    void onCellClicked(int row, int column);
private:
    void applyDateRange(const QDate &min, const QDate &max);

    void prepareDateChange(const QDate &date);
};

#endif // EXCALENDARWIDGET_EXCALENDARMONTHVIEW_H
