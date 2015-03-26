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
    void setMinimumDate(const QDate &date);

    QDate maximumDate() const;
    void setMaximumDate(const QDate &date);

    void setDateRange(const QDate &min_date, const QDate &max_date);

    QDate currentDate() const;

    bool isAnimated() const;
    void setAnimated(bool on);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    QPushButton *previousPeriodButton() const;
    QPushButton *nextPeriodButton() const;
signals:
    void currentDateChanged(const QDate &date);
public slots:
    void setCurrentDate(const QDate &date);
};

#endif // EXCALENDARWIDGET_EXCALENDARWIDGET_H
