#include <QDate>

#include "excalendarwidget/excalendarwidget_p.h"
#include "excalendarwidget/excalendarwidget.h"


ExCalendarWidget::ExCalendarWidget(QWidget *parent) :
    QFrame(parent),
    d_ptr(new ExCalendarWidgetPrivate(this))
{
    Q_D(ExCalendarWidget);
    d->initUi();

    setCurrentDate(QDate::currentDate());
}

ExCalendarWidget::~ExCalendarWidget()
{
    delete d_ptr;
}

QDate ExCalendarWidget::minimumDate() const
{
    Q_D(const ExCalendarWidget);
    return d->month_view->minimumDate();
}

QDate ExCalendarWidget::maximumDate() const
{
    Q_D(const ExCalendarWidget);
    return d->month_view->maximumDate();
}

QDate ExCalendarWidget::currentDate() const
{
    Q_D(const ExCalendarWidget);
    return d->month_view->currentDate();
}

QSize ExCalendarWidget::minimumSizeHint() const
{
    Q_D(const ExCalendarWidget);
    return d->month_view->minimumSizeHint() + QSize(0, d->navigator->minimumSizeHint().height());
}

QSize ExCalendarWidget::sizeHint() const
{
    return minimumSizeHint();
}

QPushButton *ExCalendarWidget::previousPeriodButton() const
{
    Q_D(const ExCalendarWidget);
    return d->navigator->previousPeriodButton();
}

QPushButton *ExCalendarWidget::nextPeriodButton() const
{
    Q_D(const ExCalendarWidget);
    return d->navigator->nextPeriodButton();
}

void ExCalendarWidget::setMinimumDate(const QDate &date)
{
    Q_D(ExCalendarWidget);

    d->month_view->blockSignals(true);
    d->year_view->blockSignals(true);
    d->decade_view->blockSignals(true);

    d->navigator->setMinimumDate(date);
    d->month_view->setMinimumDate(date);
    d->year_view->setMinimumDate(date);
    d->decade_view->setMinimumDate(date);

    d->month_view->blockSignals(false);
    d->year_view->blockSignals(false);
    d->decade_view->blockSignals(false);

    setCurrentDate(d->month_view->currentDate());
}

void ExCalendarWidget::setMaximumDate(const QDate &date)
{
    Q_D(ExCalendarWidget);

    d->month_view->blockSignals(true);
    d->year_view->blockSignals(true);
    d->decade_view->blockSignals(true);

    d->navigator->setMaximumDate(date);
    d->month_view->setMaximumDate(date);
    d->year_view->setMaximumDate(date);
    d->decade_view->setMaximumDate(date);

    d->month_view->blockSignals(false);
    d->year_view->blockSignals(false);
    d->decade_view->blockSignals(false);

    setCurrentDate(d->month_view->currentDate());
}

void ExCalendarWidget::setDateRange(const QDate &min_date, const QDate &max_date)
{
    Q_D(ExCalendarWidget);

    d->month_view->blockSignals(true);
    d->year_view->blockSignals(true);
    d->decade_view->blockSignals(true);

    d->navigator->setDateRange(min_date, max_date);
    d->month_view->setDateRange(min_date, max_date);
    d->year_view->setDateRange(min_date, max_date);
    d->decade_view->setDateRange(min_date, max_date);

    d->month_view->blockSignals(false);
    d->year_view->blockSignals(false);
    d->decade_view->blockSignals(false);

    setCurrentDate(d->month_view->currentDate());
}

void ExCalendarWidget::setCurrentDate(const QDate &date)
{
    Q_D(ExCalendarWidget);

    const QDate min_date = d->month_view->minimumDate();
    const QDate max_date = d->month_view->maximumDate();

    QDate current_date = date;

    if (min_date.isValid())
        current_date = qMax(min_date, current_date);
    if (max_date.isValid())
        current_date = qMin(current_date, max_date);

    d->month_view->blockSignals(true);
    d->year_view->blockSignals(true);
    d->decade_view->blockSignals(true);

    d->navigator->setCurrentDate(current_date);
    d->month_view->setCurrentDate(current_date);
    d->year_view->setCurrentDate(current_date);
    d->decade_view->setCurrentDate(current_date);

    d->month_view->blockSignals(false);
    d->year_view->blockSignals(false);
    d->decade_view->blockSignals(false);
}
