#ifndef EXCALENDARWIDGET_EXCALENDARDECADEVIEW_H
#define EXCALENDARWIDGET_EXCALENDARDECADEVIEW_H

#include "excalendarwidget/excalendarview.h"

class ExCalendarDecadeViewPrivate;

class ExCalendarDecadeView : public ExCalendarView {
    Q_OBJECT
    Q_DECLARE_PRIVATE(ExCalendarDecadeView)

    ExCalendarDecadeViewPrivate * const d_ptr;
public:
    explicit ExCalendarDecadeView(QWidget *parent = 0);
    ~ExCalendarDecadeView();
private slots:
    void onCellClicked(int row, int column);
private:
    void applyDateRange(const QDate &min, const QDate &max);

    void prepareDateChange(const QDate &date);
};

#endif // EXCALENDARWIDGET_EXCALENDARDECADEVIEW_H
