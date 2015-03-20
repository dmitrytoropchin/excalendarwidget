#include <QDate>
#include <QPropertyAnimation>
#include <QHeaderView>

#include "excalendarwidget/excalendarview.h"


class ExCalendarViewPrivate {
    Q_DECLARE_PUBLIC(ExCalendarView)

    ExCalendarView *q_ptr;

    QDate min_date;
    QDate max_date;

    QDate current_date;

    ExCalendarViewPrivate(ExCalendarView *q) : q_ptr(q) {}
    ~ExCalendarViewPrivate() {}
};

ExCalendarView::~ExCalendarView()
{
    delete d_ptr;
}

QDate ExCalendarView::minimumDate() const
{
    Q_D(const ExCalendarView);
    return d->min_date;
}

QDate ExCalendarView::maximumDate() const
{
    Q_D(const ExCalendarView);
    return d->max_date;
}

QDate ExCalendarView::currentDate() const
{
    Q_D(const ExCalendarView);
    return d->current_date;
}

void ExCalendarView::setMinimumDate(const QDate &date)
{
    Q_D(ExCalendarView);
    d->min_date = date;

    applyDateRange(d->min_date, d->max_date);
}

void ExCalendarView::setMaximumDate(const QDate &date)
{
    Q_D(ExCalendarView);
    d->max_date = date;

    applyDateRange(d->min_date, d->max_date);
}

void ExCalendarView::setDateRange(const QDate &min_date, const QDate &max_date)
{
    Q_D(ExCalendarView);
    d->min_date = min_date;
    d->max_date = max_date;

    applyDateRange(d->min_date, d->max_date);
}

void ExCalendarView::setCurrentDate(const QDate &date)
{
    Q_D(ExCalendarView);

    if (d->current_date != date) {
        prepareDateChange(date);

        d->current_date = date;

        applyDateRange(d->min_date, d->max_date);

        emit currentDateChanged(date);
    }
}

void ExCalendarView::animatedSlideRight()
{
    QPropertyAnimation *animation = new QPropertyAnimation(viewport(), "pos", this);
    animation->setStartValue(QPoint(viewport()->width() / 2, viewport()->pos().y()));
    animation->setEndValue(QPoint(0, viewport()->pos().y()));
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->setDuration(150);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void ExCalendarView::animatedSlideLeft()
{
    QPropertyAnimation *animation = new QPropertyAnimation(viewport(), "pos", this);
    animation->setStartValue(QPoint(- viewport()->width() / 2, viewport()->pos().y()));
    animation->setEndValue(QPoint(0, viewport()->pos().y()));
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->setDuration(150);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void ExCalendarView::animatedSlideTop()
{
    QPropertyAnimation *animation = new QPropertyAnimation(viewport(), "pos", this);
    animation->setStartValue(QPoint(viewport()->pos().x(), - viewport()->height() / 2));
    animation->setEndValue(QPoint(viewport()->pos().x(), viewport()->pos().y()));
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->setDuration(150);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void ExCalendarView::animatedSlideBottom()
{
    QPropertyAnimation *animation = new QPropertyAnimation(viewport(), "pos", this);
    animation->setStartValue(QPoint(viewport()->pos().x(), viewport()->height() / 2));
    animation->setEndValue(QPoint(viewport()->pos().x(), viewport()->pos().y()));
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->setDuration(150);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

ExCalendarView::ExCalendarView(QWidget *parent) :
    QTableWidget(parent),
    d_ptr(new ExCalendarViewPrivate(this))
{
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
    verticalHeader()->setResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::SingleSelection);

    setFrameStyle(QFrame::NoFrame);

    setShowGrid(false);
}

void ExCalendarView::applyDateRange(const QDate &min, const QDate &max)
{
    Q_UNUSED(min);
    Q_UNUSED(max);
}

void ExCalendarView::prepareDateChange(const QDate &date)
{
    Q_UNUSED(date);
}
