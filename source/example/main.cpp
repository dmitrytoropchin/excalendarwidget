#include <QApplication>
#include <QPushButton>
#include <QDate>

#include <excalendarwidget/excalendarwidget.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ExCalendarWidget calendar;
    calendar.setWindowTitle("Calendar Widget Example");
    calendar.show();

    ExCalendarWidget styled_calendar;
    styled_calendar.setWindowTitle("Styled Calendar Widget Example");

    styled_calendar.nextPeriodButton()->setIcon(QIcon());
    styled_calendar.previousPeriodButton()->setIcon(QIcon());

    styled_calendar.setStyleSheet(
                "* {"
                "background-color: #ffffff;"
                "font-size: 12px;"
                "}"
                ""
                "QFrame#navigator {"
                "background-color: #484741;"
                "}"
                ""
                "QFrame#navigator QPushButton {"
                "color: #ffffff;"
                "border-color: #484741;"
                "font-size: 14px;"
                "font-weight: bold;"
                "}"
                ""
                "QFrame#navigator QPushButton:pressed {"
                "background-color: #484741;"
                "border: none;"
                "}"
                ""
                "QFrame#navigator QPushButton#previous-period-button {"
                "background-image: url(icons/arrow-back.png);"
                "background-position: center;"
                "background-repeat: no-repeat;"
                "border-color: #484741;"
                "background-color: #484741;"
                "}"
                ""
                "QFrame#navigator QPushButton#previous-period-button:disabled {"
                "background-image: url(icons/arrow-back-disabled.png);"
                "}"
                ""
                "QFrame#navigator QPushButton#next-period-button {"
                "background-image: url(icons/arrow-forward.png);"
                "background-position: center;"
                "background-repeat: no-repeat;"
                "border-color: #484741;"
                "background-color: #484741;"
                "}"
                ""
                "QFrame#navigator QPushButton#next-period-button:disabled {"
                "background-image: url(icons/arrow-forward-disabled.png);"
                "}"
                ""
                "QHeaderView::section {"
                "background-color: #484741;"
                "border: none;"
                "color: #ffffff;"
                "padding: 4px;"
                "}"
                ""
                "QTableWidget {"
                "background-color: #484741;"
                "color: #ffffff;"
                "}"
                ""
                "QTableWidget::item:selected {"
                "background-color: #ff6a36;"
                "color: #ffffff;"
                "}"
                ""
                "QTableWidget::item:disabled {"
                "color: #686761;"
                "}"
                );

    styled_calendar.setMaximumDate(QDate(2008, 4, 13));

    styled_calendar.show();

    return app.exec();
}
