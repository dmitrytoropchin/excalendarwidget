#include <QApplication>
#include <QPushButton>
#include <QDate>

#include <excalendarwidget/excalendarwidget.h>


QString stylesheet()
{
    return "* {"
           "background-color: #ffffff;"
           "font-size: 12px;"
           "}"
           ""
            // navigation bar
            "QFrame#navigator {"
            "background-color: #484741;"
            "}"
            ""
            // navigation bar buttons
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
            // header with week day names for month view
            "QHeaderView::section {"
            "background-color: #484741;"
            "border: none;"
            "color: #ffffff;"
            "padding: 4px;"
            "}"
            ""
            // tables with month, year and decade views
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
            "}";
}

QString stylesheetPalette()
{
    return "* {"
           "background-color: palette(base);"
           "font-size: 12px;"
           "}"
           ""
            // navigation bar
            "QFrame#navigator {"
            "background-color: palette(window);"
            "}"
            ""
            // navigation bar buttons
            "QFrame#navigator QPushButton {"
            "color: palette(window-text);"
            "border-color: palette(window);"
            "font-size: 14px;"
            "font-weight: bold;"
            "}"
            ""
            "QFrame#navigator QPushButton:pressed {"
            "background-color: palette(window);"
            "border: none;"
            "}"
            ""
            "QFrame#navigator QPushButton#previous-period-button {"
            "background-image: url(icons/arrow-back.png);"
            "background-position: center;"
            "background-repeat: no-repeat;"
            "border-color: palette(window);"
            "background-color: palette(window);"
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
            "border-color: palette(window);"
            "background-color: palette(window);"
            "}"
            ""
            "QFrame#navigator QPushButton#next-period-button:disabled {"
            "background-image: url(icons/arrow-forward-disabled.png);"
            "}"
            ""
            // header with week day names for month view
            "QHeaderView::section {"
            "background-color: palette(window);"
            "border: none;"
            "color: palette(window-text);"
            "padding: 4px;"
            "}"
            ""
            // tables with month, year and decade views
            "QTableWidget {"
            "background-color: palette(window);"
            "color: palette(window-text);"
            "}"
            ""
            "QTableWidget::item:selected {"
            "background-color: palette(highlight);"
            "color: palette(highlight-text);"
            "}"
            ""
            "QTableWidget::item:disabled {"
            "color: palette(shadow);"
            "}";
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // simple usage
    ExCalendarWidget calendar;
    calendar.setWindowTitle("Calendar Widget Example");
    // disable transition animations
    calendar.setAnimated(false);

    calendar.show();

    // example on stylesheets
    ExCalendarWidget styled_calendar;
    styled_calendar.setWindowTitle("Styled Calendar Widget Example");

    // unsetting button icons to replace them from stylesheet
    styled_calendar.nextPeriodButton()->setIcon(QIcon());
    styled_calendar.previousPeriodButton()->setIcon(QIcon());

    styled_calendar.setStyleSheet(stylesheetPalette());

    // also support date range setting
    styled_calendar.setMaximumDate(QDate(2008, 4, 13));

    styled_calendar.show();

    return app.exec();
}
