#include <QDate>
#include <QHeaderView>
#include <QPropertyAnimation>

#include "excalendarwidget/excalendarmonthview.h"


class ExCalendarMonthViewPrivate {
    Q_DECLARE_PUBLIC(ExCalendarMonthView)

    ExCalendarMonthView *q_ptr;

    ExCalendarMonthViewPrivate(ExCalendarMonthView *q) : q_ptr(q) {}
    ~ExCalendarMonthViewPrivate() {}
};


ExCalendarMonthView::ExCalendarMonthView(QWidget *parent) :
    ExCalendarView(parent),
    d_ptr(new ExCalendarMonthViewPrivate(this))
{
    setObjectName("month-view");

    setRowCount(6);
    setColumnCount(7);

    QTableWidgetItem *item = 0;

    for (int i = 0; i < 7; ++ i) {
        item = new QTableWidgetItem(QDate::shortDayName(i + 1, QDate::StandaloneFormat));
        item->setTextAlignment(Qt::AlignCenter);
        setHorizontalHeaderItem(i, item);
    }

    for (int i = 0; i < 42; ++ i) {
        item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::NoItemFlags);
        setItem(i / 7, i % 7, item);
    }

    verticalHeader()->hide();
    horizontalHeader()->show();

    connect(this, SIGNAL(cellClicked(int,int)), SLOT(onCellClicked(int,int)));
}

ExCalendarMonthView::~ExCalendarMonthView()
{
    delete d_ptr;
}

QSize ExCalendarMonthView::minimumSizeHint() const
{
    return QSize(horizontalHeader()->minimumSectionSize() * 7,
                 verticalHeader()->minimumSectionSize() * 6 + horizontalHeader()->sizeHint().height());
}

QSize ExCalendarMonthView::sizeHint() const
{
    return minimumSizeHint();
}

void ExCalendarMonthView::onCellClicked(int row, int column)
{
    if (item(row, column)->flags() & Qt::ItemIsEnabled) {
        QDate clicked_date = item(row, column)->data(Qt::UserRole).toDate();

        setCurrentDate(clicked_date);

        emit dateClicked(clicked_date);
    }
}

void ExCalendarMonthView::applyDateRange(const QDate &min, const QDate &max)
{
    for (int cell_idx = 0; cell_idx < 42; ++ cell_idx) {
        QTableWidgetItem *cell_item = item(cell_idx / 7, cell_idx % 7);

        QDate cell_date = cell_item->data(Qt::UserRole).toDate();

        if (cell_date.isValid()) {
            if (min.isValid() && (cell_date < min))
                cell_item->setFlags(Qt::NoItemFlags);
            else if (max.isValid() && (cell_date > max))
                cell_item->setFlags(Qt::NoItemFlags);
            else
                cell_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
    }
}

void ExCalendarMonthView::prepareDateChange(const QDate &date)
{
    QDate cell_date = QDate(date.year(), date.month(), 1);

    const int start_cell = cell_date.dayOfWeek() - 1;
    const int end_cell = start_cell + cell_date.daysInMonth();

    const QDate current_date = currentDate();

    if ((current_date.year() != date.year()) || (current_date.month() != date.month())) {
        for (int cell_idx = 0; cell_idx < 42; ++ cell_idx) {
            QTableWidgetItem *cell_item = item(cell_idx / 7, cell_idx % 7);

            cell_item->setText(QString::null);
            cell_item->setData(Qt::UserRole, QDate());
            cell_item->setFlags(Qt::NoItemFlags);
        }

        for (int cell_idx = start_cell; cell_idx < end_cell; ++ cell_idx) {
            QTableWidgetItem *cell_item = item(cell_idx / 7, cell_idx % 7);

            cell_item->setText(QString::number(cell_date.day()));
            cell_item->setData(Qt::UserRole, cell_date);
            cell_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

            cell_date = cell_date.addDays(1);
        }
    }

    const int current_cell = start_cell + date.day() - 1;

    setCurrentCell(current_cell / 7, current_cell % 7, QItemSelectionModel::SelectCurrent);
}
