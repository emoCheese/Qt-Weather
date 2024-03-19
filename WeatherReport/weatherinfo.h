#ifndef WEATHERINFO_H
#define WEATHERINFO_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "WeatherData.h"
#include <array>

/*
 * 获取天气信息的类
 * 嫌麻烦就用了友元
*/
class WeatherInfo : public QObject
{
    Q_OBJECT
    friend class MainWindow;
public:
    WeatherInfo(QObject *parent = nullptr);
    ~WeatherInfo();
    void getWeatherInfo(const QString& request_url);
    QString getCityCode(const QString& city);
    QString getCitybyCode(const QString& code);
    void parseAirJson(QByteArray&);
    void parseWeatherJson(QByteArray&);
    void parseNowWeatherJson(QByteArray&);
    bool isParsed() const;
signals:
    void SigUpdateUI();

public slots:
    void SlotUpdateApi(QString request);

private slots:
    void SlotOnWeatherReplied(QNetworkReply* reply);

private:
    void InitCityMap();
    void InitWeatherApi();
    void ResetBoolen();

    QWidget* _parent;

    QString _cur_city;
    // 请求天气api
    QString _prefix_weather;  // 天气预报
    QString _prefix_air;      // 空气质量
    QString _prefix_now;   // 实时天气
    QString _city_code;
    QString _api_key;

    QString _weather_url;   // 天气请求url
    QString _air_url;       // 空气质量请求url
    QString _now_url;       // 实时天气url

    // 判断天气信息是否解析完成
    bool _b_parse_weather;
    bool _b_parse_air;
    bool _b_parse_now;

    // key 城市名或地区名
    QMap<QString, QStringList> _city_info_map;
    // code 对应 城市
    QMap<QString, QString> _city_code_map;

    QNetworkAccessManager* _net_access_mgr;

    // 保存获取的天气预报
    Air _air;
    std::array<Weather, FORECAST_DAYS> _weather_infos;
    NowWeather _now_weather;
};

#endif // WEATHERINFO_H
