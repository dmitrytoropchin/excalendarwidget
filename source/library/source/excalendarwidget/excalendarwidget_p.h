#ifndef EXCALENDARWIDGET_EXCALENDARWIDGET_P_H
#define EXCALENDARWIDGET_EXCALENDARWIDGET_P_H

#include <QObject>

#include <QVBoxLayout>
#include <QStackedLayout>
#include <QFrame>

#include "excalendarwidget/excalendarnavigator.h"

#include "excalendarwidget/excalendarmonthview.h"
#include "excalendarwidget/excalendaryearview.h"
#include "excalendarwidget/excalendardecadeview.h"


class ExCalendarWidget;

class ExCalendarWidgetPrivate : public QObject {
    Q_OBJECT
    Q_DECLARE_PUBLIC(ExCalendarWidget)
public:
    ExCalendarWidget *q_ptr;

    QVBoxLayout *main_layout;
    QStackedLayout *views_layout;

    ExCalendarNavigator *navigator;

    QFrame *views_frame;

    ExCalendarMonthView *month_view;
    ExCalendarYearView *year_view;
    ExCalendarDecadeView *decade_view;

    ExCalendarWidgetPrivate(ExCalendarWidget *q);
    ~ExCalendarWidgetPrivate();

    void initUi();
public slots:
    void onNavigatorStateChanged(int state, int previous_state);

    void onNavigatorPreviousPeriodButtonClicked();
    void onNavigatorNextPeriodButtonClicked();
};

#endif // EXCALENDARWIDGET_EXCALENDARWIDGET_P_H
