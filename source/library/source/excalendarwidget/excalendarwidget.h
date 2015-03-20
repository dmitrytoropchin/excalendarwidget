#ifndef EXCALENDARWIDGET_EXCALENDARWIDGET_H
#define EXCALENDARWIDGET_EXCALENDARWIDGET_H

#include <excalendarwidget/excalendarwidget_common.h>
#include <QFrame>

class QDate;
class QPushButton;

class ExCalendarWidgetPrivate;

class EXCALENDARWIDGET_EXPORT ExCalendarWidget : public QFrame {
    Q_OBJECT
    Q_DECLARE_PRIVATE(ExCalendarWidget)

    ExCalendarWidgetPrivate * const d_ptr;
public:
    explicit ExCalendarWidget(QWidget *parent = 0);
    ~ExCalendarWidget();

    QDate minimumDate() const;
    QDate maximumDate() const;

    QDate currentDate() const;

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    QPushButton *previousPeriodButton() const;
    QPushButton *nextPeriodButton() const;
public slots:
    void setMinimumDate(const QDate &date);
    void setMaximumDate(const QDate &date);

    void setDateRange(const QDate &min_date, const QDate &max_date);

    void setCurrentDate(const QDate &date);
};

#endif // EXCALENDARWIDGET_EXCALENDARWIDGET_H
