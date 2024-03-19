#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QContextMenuEvent>
#include <QAction>
#include <QMenu>
#include <QTimer>
#include <QDateTime>
#include <QDate>
#include <QFile>
#include <QLabel>

#include "weatherinfo.h"


const int INCREACEMENT = 3;
const int X_OFFSET = 12;
const int Y_OFFSET = 12;
const int RADIUS = 3;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
   void contextMenuEvent(QContextMenuEvent *event) override;

   // 位于QWidget类
   void mousePressEvent(QMouseEvent *event) override;
   void mouseMoveEvent(QMouseEvent *event) override;
   bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void SigUpdateTime();
    void SigUpdateApi(QString);

private slots:
    void SlotUpdateUI();
    void on_act_exit_triggered();
    void on_act_reflush_triggered();

    void SlotUpdateTime();

    void on_search_btn_clicked();

private:
    void DateInit();
    void InitCityMap();
    void InitIconMap();
    void InitWeatherApi();
    void UpdateUI();
    void paintHighCurve();
    void paintLowCurve();
    QString DateFormat(const QString& dateString);


    QList<QLabel*> date_labels;  // 日期标签
    QList<QLabel*> icon_labels;  // 天气图标标签
    QList<QLabel*> text_labels;  // 天气文字标签
    QList<QLabel*> wind_dir_labels; // 风向标签
    QList<QLabel*> wind_scale_labels; // 风力等级标签

    // 获取天气信息的网络类
    WeatherInfo* _weather_info;
    QMap<QString, QString> _weather_icon_map;

    QMenu* _right_btn_menu;  //鼠标右键菜单
    QTimer* _timer;
    QPoint _offset;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
