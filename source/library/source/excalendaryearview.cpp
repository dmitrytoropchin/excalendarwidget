#include <QDate>
#include <QHeaderView>

#include "excalendarwidget/excalendaryearview.h"


class ExCalendarYearViewPrivate {
    Q_DECLARE_PUBLIC(ExCalendarYearView)

    ExCalendarYearView *q_ptr;

    ExCalendarYearViewPrivate(ExCalendarYearView *q) : q_ptr(q) {}
    ~ExCalendarYearViewPrivate() {}
};


ExCalendarYearView::ExCalendarYearView(QWidget *parent) :
    ExCalendarView(parent),
    d_ptr(new ExCalendarYearViewPrivate(this))
{
    setObjectName("year-view");

    setRowCount(3);
    setColumnCount(4);

    QTableWidgetItem *item = 0;
    for (int i = 0; i < 12; ++ i) {
        item = new QTableWidgetItem(QDate::shortMonthName(i + 1, QDate::StandaloneFormat));
        item->setTextAlignment(Qt::AlignCenter);
        setItem(i / 4, i % 4, item);
    }

    verticalHeader()->hide();
    horizontalHeader()->hide();

    connect(this, SIGNAL(cellClicked(int,int)), SLOT(onCellClicked(int,int)));
}

ExCalendarYearView::~ExCalendarYearView()
{
    delete d_ptr;
}

void ExCalendarYearView::onCellClicked(int row, int column)
{
    if (item(row, column)->flags() & Qt::ItemIsEnabled) {
        QDate current_date = currentDate();

        QDate current_month = QDate(current_date.year(), row * 4 + column + 1, 1);

        QDate clicked_date = QDate(current_month.year(),
                                   current_month.month(),
                                   qMin(current_date.day(), current_month.daysInMonth()));

        setCurrentDate(clicked_date);

        emit dateClicked(clicked_date);
    }
}

void ExCalendarYearView::applyDateRange(const QDate &min, const QDate &max)
{
    for (int cell_idx = 0; cell_idx < 12; ++ cell_idx) {
        const int row = cell_idx / 4;
        const int column = cell_idx % 4;


        QDate current_date = currentDate();
        QDate current_month = QDate(current_date.year(), row * 4 + column + 1, 1);

        QDate cell_date = QDate(current_month.year(),
                                current_month.month(),
                                qMin(current_date.day(), current_month.daysInMonth()));

        QTableWidgetItem *cell_item = item(row, column);

        if (cell_date.isValid()) {
            if (min.isValid() && (cell_date.year() <= min.year()) && (cell_date.month() < min.month()))
                cell_item->setFlags(Qt::NoItemFlags);
            else if (max.isValid() && (cell_date.year() >= max.year()) && (cell_date.month() > max.month()))
                cell_item->setFlags(Qt::NoItemFlags);
            else
                cell_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
    }
}

void ExCalendarYearView::prepareDateChange(const QDate &date)
{
    setCurrentCell((date.month() - 1) / 4, (date.month() - 1) % 4, QItemSelectionModel::SelectCurrent);
}
