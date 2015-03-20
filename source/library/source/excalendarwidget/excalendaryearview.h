#ifndef EXCALENDARWIDGET_EXCALENDARYEARVIEW_H
#define EXCALENDARWIDGET_EXCALENDARYEARVIEW_H

#include "excalendarwidget/excalendarview.h"

class ExCalendarYearViewPrivate;

class ExCalendarYearView : public ExCalendarView {
    Q_OBJECT
    Q_DECLARE_PRIVATE(ExCalendarYearView)

    ExCalendarYearViewPrivate * const d_ptr;
public:
    explicit ExCalendarYearView(QWidget *parent = 0);
    ~ExCalendarYearView();
private slots:
    void onCellClicked(int row, int column);
private:
    void applyDateRange(const QDate &min, const QDate &max);

    void prepareDateChange(const QDate &date);
};

#endif // EXCALENDARWIDGET_EXCALENDARYEARVIEW_H
