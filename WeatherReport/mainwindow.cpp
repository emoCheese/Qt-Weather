#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCursor>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QPointer>
#include <QPen>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _weather_info(nullptr)
    , _right_btn_menu(nullptr)
    , _timer(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint); // 设置窗口无边框
    _right_btn_menu = new QMenu(parent);
    _timer = new QTimer(parent);
    _timer->start(1000);  // 1000 1s发送 timeOut信号
    // 初始化控件列表
    date_labels << ui->date_1 << ui->date_2 << ui->date_3 << ui->date_4
                << ui->date_5 << ui->date_6;
    icon_labels << ui->Weather_1 << ui->Weather_2 << ui->Weather_3 << ui->Weather_4
                << ui->Weather_5 << ui->Weather_6;
    text_labels << ui->Weather_text_1 << ui->Weather_text_2 << ui->Weather_text_3 << ui->Weather_text_4
                << ui->Weather_text_5 << ui->Weather_text_6;
    wind_dir_labels << ui->lblFx0 << ui->lblFx1 << ui->lblFx2 << ui->lblFx3
                    << ui->lblFx4 << ui->lblFx5;
    wind_scale_labels << ui->lblFl0 << ui->lblFl1 << ui->lblFl2 << ui->lblFl3
                      << ui->lblFl4 << ui->lblFl5;


    // 时间初始化
    DateInit();
    InitIconMap();
    _weather_info = new WeatherInfo(this);
    ui->lblLowCurve->installEventFilter(this);
    ui->lblHighCurve->installEventFilter(this);

    connect(_timer, &QTimer::timeout, this, &MainWindow::SlotUpdateTime);
    connect(this, &MainWindow::SigUpdateTime, this, &MainWindow::SlotUpdateTime);
    connect(this, &MainWindow::SigUpdateApi, _weather_info, &WeatherInfo::SlotUpdateApi);
    connect(_weather_info, &WeatherInfo::SigUpdateUI, this, &MainWindow::SlotUpdateUI);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 重写 contextMenuEvent 实现鼠标右键菜单
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    _right_btn_menu->addAction(ui->act_exit);
    _right_btn_menu->addAction(ui->act_reflush);
    // 使菜单出现在鼠标当前位置
    _right_btn_menu->exec(QCursor::pos());
    QMainWindow::contextMenuEvent(event);
}

void MainWindow::on_act_exit_triggered()
{
    qApp->exit(0);
}


void MainWindow::on_act_reflush_triggered()
{
    qDebug() << "已刷新\n";
    emit SigUpdateTime();
}

void MainWindow::SlotUpdateTime()
{
    // 获取当前日期和时间
    QDateTime DT = QDateTime::currentDateTime();
    QString str = DT.toString("yyyy-MM-dd hh:mm:ss  ");

    // 获取当前日期
    QDate currentDate = QDate::currentDate();
    // 获取星期几（返回值为 1-7，分别代表周一到周日）
    int dayOfWeek = currentDate.dayOfWeek();
    QString day = "星期一 ";

    switch (dayOfWeek) {
    case 1:
        day = "星期一 ";
        break;
    case 2:
        day = "星期二 ";
        break;
    case 3:
        day = "星期三 ";
        break;
    case 4:
        day = "星期四 ";
        break;
    case 5:
        day = "星期五 ";
        break;
    case 6:
        day = "星期六 ";
        break;
    case 7:
        day = "星期天 ";
    default:
        break;
    }
    ui->date_label->setText(str + day);
}

// 日期初始化
void MainWindow::DateInit()
{
    // 获取当前日期和时间
    QDateTime DT = QDateTime::currentDateTime();
    QString str = DT.toString("yyyy-MM-dd hh:mm:ss  ");

    // 获取当前日期
    QDate currentDate = QDate::currentDate();
    // 获取星期几（返回值为 1-7，分别代表周一到周日）
    int dayOfWeek = currentDate.dayOfWeek();
    QString day = "星期一 ";

    switch (dayOfWeek) {
    case 1:
        day = "星期一 ";
        break;
    case 2:
        day = "星期二 ";
        break;
    case 3:
        day = "星期三 ";
        break;
    case 4:
        day = "星期四 ";
        break;
    case 5:
        day = "星期五 ";
        break;
    case 6:
        day = "星期六 ";
        break;
    case 7:
        day = "星期天 ";
    default:
        break;
    }


    ui->date_label->setText(str + day);
}

void MainWindow::InitIconMap()
{
    _weather_icon_map["晴"] = ":/res/type/Qing.png";
    _weather_icon_map["暴雪"] = ":/res/type/BaoXue.png";
    _weather_icon_map["暴雨到大暴雨"] = ":/res/type/BaoYuDaoDaBaoYu.png";
    _weather_icon_map["大暴雨"] = ":/res/type/DaBaoYu.png";
    _weather_icon_map["暴雨到特大暴雨"] = ":/res/type/DaBaoYuDaoTeDaBaoYu.png";
    _weather_icon_map["大暴雪"] = ":/res/type/DaDaoBaoXue.png";
    _weather_icon_map["大暴雨"] = ":/res/type/DaDaoBaoYu.png";
    _weather_icon_map["大雪"] = ":/res/type/DaXue.png";
    _weather_icon_map["大雨"] = ":/res/type/DaYu.png";
    _weather_icon_map["冻雨"] = ":/res/type/DongYu.png";
    _weather_icon_map["多云"] = ":/res/type/DuoYun.png";
    _weather_icon_map["浮尘"] = ":/res/type/FuChen.png";
    _weather_icon_map["雷阵雨"] = ":/res/type/LeiZhenYu.png";
    _weather_icon_map["雷阵雨伴有冰雹"] = ":/res/type/LeiZhenYuBanYouBingBao.png";
    _weather_icon_map["霾"] = ":/res/type/Mai.png";
    _weather_icon_map["强沙尘暴"] = ":/res/type/QiangShaChenBao.png";
    _weather_icon_map["沙尘暴"] = ":/res/type/ShaChenBao.png";
    _weather_icon_map["特大暴雨"] = ":/res/type/TeDaBaoYu.png";
    _weather_icon_map["雾"] = ":/res/type/Wu.png";
    _weather_icon_map["小到中雪"] = ":/res/type/XiaoDaoZhongXue.png";
    _weather_icon_map["小到中雨"] = ":/res/type/XiaoDaoZhongYu.png";
    _weather_icon_map["小雪"] = ":/res/type/XiaoXue.png";
    _weather_icon_map["小雨"] = ":/res/type/XiaoYu.png";
    _weather_icon_map["雪"] = ":/res/type/Xue.png";
    _weather_icon_map["扬沙"] = ":/res/type/YangSha.png";
    _weather_icon_map["阴"] = ":/res/type/Yin.png";
    _weather_icon_map["雨"] = ":/res/type/Yu.png";
    _weather_icon_map["雨夹雪"] = ":/res/type/YuJiaXue.png";
    _weather_icon_map["阵雪"] = ":/res/type/ZhenXue.png";
    _weather_icon_map["阵雨"] = ":/res/type/ZhenYu.png";
    _weather_icon_map["中到大雪"] = ":/res/type/ZhongDaoDaXue.png";
    _weather_icon_map["中到大雨"] = ":/res/type/ZhongDaoDaYu.png";
    _weather_icon_map["中雪"] = ":/res/type/ZhongXue.png";
    _weather_icon_map["中雨"] = ":/res/type/ZhongYu.png";
}

void MainWindow::UpdateUI()
{
    QString str = "°";
    // 实时天气部分更新
    ui->city_label->clear();
    ui->city_label->setText(_weather_info->_cur_city);

    const QString& cur_temp = _weather_info->_now_weather.temp;
    ui->temp_label->clear();
    ui->temp_label->setText(cur_temp+str);


    const QString& cur_weather = _weather_info->_now_weather.text;
    ui->weather_info->clear();
    ui->weather_info->setText(cur_weather);

    QPixmap pixmap(_weather_icon_map[cur_weather]);
    ui->weather_label->setPixmap(pixmap);

    QString tempMax = _weather_info->_weather_infos[0].tempMax;
    QString tempMin = _weather_info->_weather_infos[0].tempMin;
    ui->temp_info->setText(tempMin+str+"~"+tempMax+str);

    ui->wind_label->setText(_weather_info->_now_weather.windDir);
    ui->wind_level_label->setText(_weather_info->_now_weather.windScale);
    ui->pm25_level_label->setText(_weather_info->_air.pm2p5);
    ui->humidity_percent->setText(_weather_info->_now_weather.humidity);
    ui->air_level_label->setText(_weather_info->_air.category);

    // 预报七天天气部分更新，但是只展示六天
    for(int i = 0; i < FORECAST_DAYS - 1; ++i)
    {
        // 更改日期
        QString date = DateFormat(_weather_info->_weather_infos[i].fxDate);
        date_labels[i]->setText(date);
        // 更改图标
        icon_labels[i]->clear();
        QPixmap pixmap(_weather_icon_map[_weather_info->_weather_infos[i].textDay]);
        icon_labels[i]->setPixmap(pixmap);
        // 更改文本
        text_labels[i]->setText(_weather_info->_weather_infos[i].textDay);

        wind_dir_labels[i]->clear();
        wind_dir_labels[i]->setText(_weather_info->_weather_infos[i].windDirDay);
        wind_scale_labels[i]->clear();
        wind_scale_labels[i]->setText(_weather_info->_weather_infos[i].windScaleDay);
    }

    // 绘图
    ui->lblLowCurve->update();
    ui->lblHighCurve->update();



    // 更新完后重置
    _weather_info->ResetBoolen();
}

void MainWindow::paintHighCurve()
{
    qDebug() << "paintHighCurve";
    QPainter painter(ui->lblHighCurve);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int pointX[6] = {0};
    // 获取x坐标
    for(int i = 0; i < 6; ++i)
    {
        pointX[i] = date_labels[i]->pos().x() + date_labels[i]->width()/2;
    }
    // 获取y坐标
    int tempMaxSum = 0, tempMinSum = 0;
    for(int i = 0; i < 6; ++i)
    {
        tempMaxSum += _weather_info->_weather_infos[i].tempMax.toInt();
        // tempMinSum += _weather_info->_weather_infos[i].tempMin.toInt();
    }
    int MaxAvg = tempMaxSum/6;
    // int MinAvg = tempMinSum/6;
    // 计算y坐标
    int pointY[6] = {0};
    int yCenter = ui->lblHighCurve->height()/2;
    for(int i = 0; i < 6; ++i)
    {
        pointY[i] = yCenter-((_weather_info->_weather_infos[i].tempMax.toInt() - MaxAvg) * INCREACEMENT);
    }
    // 开始绘制
    QPen pen = painter.pen();
    pen.setWidth(1);
    pen.setColor(QColor(255,170,0));
    painter.setBrush(QColor(255,170,0));
    painter.setPen(pen);
    for(int i = 0; i < 6; ++i)
    {
        painter.drawEllipse(QPoint(pointX[i], pointY[i]), RADIUS, RADIUS);
        painter.drawText(QPoint(pointX[i]-X_OFFSET, pointY[i]-Y_OFFSET)
                         , _weather_info->_weather_infos[i].tempMax+"°");
    }
    for(int i = 0; i < 5; ++i)
        painter.drawLine(pointX[i],pointY[i], pointX[i+1],pointY[i+1]);
    painter.end();
}

void MainWindow::paintLowCurve()
{
    qDebug() << "paintLowCurve";
    QPainter painter(ui->lblLowCurve);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int pointX[6] = {0};
    // 获取x坐标
    for(int i = 0; i < 6; ++i)
    {
        pointX[i] = date_labels[i]->pos().x() + date_labels[i]->width()/2;
    }
    // 获取y坐标
    int tempMinSum = 0;
    for(int i = 0; i < 6; ++i)
    {
        tempMinSum += _weather_info->_weather_infos[i].tempMin.toInt();
    }
    int MinAvg = tempMinSum/6;
    // 计算y坐标
    int pointY[6] = {0};
    int yCenter = ui->lblLowCurve->height()/2;
    for(int i = 0; i < 6; ++i)
    {
        pointY[i] = yCenter-((_weather_info->_weather_infos[i].tempMin.toInt() - MinAvg) * INCREACEMENT);
    }
    // 开始绘制
    QPen pen = painter.pen();
    pen.setWidth(1);
    pen.setColor(QColor(0,255,255));
    painter.setBrush(QColor(0,255,255));
    painter.setPen(pen);
    for(int i = 0; i < 6; ++i)
    {
        painter.drawEllipse(QPoint(pointX[i], pointY[i]), RADIUS, RADIUS);
        painter.drawText(QPoint(pointX[i]-X_OFFSET, pointY[i]-Y_OFFSET)
                         , _weather_info->_weather_infos[i].tempMin+"°");
    }
    for(int i = 0; i < 5; ++i)
        painter.drawLine(pointX[i],pointY[i], pointX[i+1],pointY[i+1]);
    painter.end();
}

QString MainWindow::DateFormat(const QString &dateString)
{
    QDateTime dateTime = QDateTime::fromString(dateString, "yyyy-MM-dd");
    QString formattedDate;
    if (dateTime.isValid()) {
        formattedDate = QString::number(dateTime.date().month()) + "/" + QString::number(dateTime.date().day());
    } else {
        qDebug() << "Invalid date string";
    }
    return formattedDate;
}


// 实现鼠标拖动窗口事件
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    _offset = event->globalPos() - this->pos();
    QWidget::mousePressEvent(event);
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - _offset);
    QWidget::mouseMoveEvent(event);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lblHighCurve && event->type() == QEvent::Paint)
    {
        paintHighCurve();
    }
    if(watched == ui->lblLowCurve && event->type() == QEvent::Paint)
    {
        paintLowCurve();
    }
    QMainWindow::eventFilter(watched, event);
}

void MainWindow::SlotUpdateUI()
{
    UpdateUI();
}



void MainWindow::on_search_btn_clicked()
{
    // 获取搜索栏 地区
    auto text = ui->search_edit->text();
    if(text.isEmpty())
    {
        return;
    }
    emit SigUpdateApi(text);
}

