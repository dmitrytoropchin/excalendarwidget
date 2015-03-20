#include <QDate>
#include <QHeaderView>

#include "excalendarwidget/excalendardecadeview.h"


class ExCalendarDecadeViewPrivate {
    Q_DECLARE_PUBLIC(ExCalendarDecadeView)

    ExCalendarDecadeView *q_ptr;

    ExCalendarDecadeViewPrivate(ExCalendarDecadeView *q) : q_ptr(q) {}
    ~ExCalendarDecadeViewPrivate() {}
};


ExCalendarDecadeView::ExCalendarDecadeView(QWidget *parent) :
    ExCalendarView(parent),
    d_ptr(new ExCalendarDecadeViewPrivate(this))
{
    setObjectName("decade-view");

    setRowCount(3);
    setColumnCount(4);

    QTableWidgetItem *item = 0;
    for (int i = 0; i < 12; ++ i) {
        item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignCenter);
        setItem(i / 4, i % 4, item);
    }

    verticalHeader()->hide();
    horizontalHeader()->hide();

    connect(this, SIGNAL(cellClicked(int,int)), SLOT(onCellClicked(int,int)));
}

ExCalendarDecadeView::~ExCalendarDecadeView()
{
    delete d_ptr;
}

void ExCalendarDecadeView::onCellClicked(int row, int column)
{
    if (item(row, column)->flags() & Qt::ItemIsEnabled) {
        QDate clicked_date = item(row, column)->data(Qt::UserRole).toDate();

        setCurrentDate(clicked_date);

        emit dateClicked(clicked_date);
    }
}

void ExCalendarDecadeView::applyDateRange(const QDate &min, const QDate &max)
{
    for (int cell_idx = 0; cell_idx < 12; ++ cell_idx) {
        QTableWidgetItem *cell_item = item(cell_idx / 4, cell_idx % 4);

        QDate cell_date = cell_item->data(Qt::UserRole).toDate();

        if (cell_date.isValid()) {
            if (min.isValid() && (cell_date.year() < min.year()))
                cell_item->setFlags(Qt::NoItemFlags);
            else if (max.isValid() && (cell_date.year() > max.year()))
                cell_item->setFlags(Qt::NoItemFlags);
            else
                cell_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
    }
}

void ExCalendarDecadeView::prepareDateChange(const QDate &date)
{
    for (int cell_idx = 0; cell_idx < 12; ++ cell_idx) {
        int year = date.year() + cell_idx - 5;
        QTableWidgetItem *year_item = item(cell_idx / 4, cell_idx % 4);

        QDate current_month = QDate(year, date.month(), 1);

        QDate cell_date = QDate(current_month.year(),
                                current_month.month(),
                                qMin(date.day(), current_month.daysInMonth()));

        year_item->setText(QString::number(year));
        year_item->setData(Qt::UserRole, cell_date);
    }

    setCurrentCell(1, 1, QItemSelectionModel::SelectCurrent);
}
