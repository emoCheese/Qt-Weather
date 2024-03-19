#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QString>

// 预报天气数
const int FORECAST_DAYS = 7;

// 七天预报
class Weather
{
public:
    Weather()
        : fxDate("2024-03-18")
        , sunrise("06:17")
        , sunset("18:22")
        , moonrise("11:49")
        , moonset("02:05")
        , moonPhase("盈凸月")
    {

        moonPhaseIcon = "803";
        tempMax = "10";
        tempMin = "3";
        iconDay = "104";
        textDay = "阴";
        iconNight = "150";
        textNight = "晴";
        wind360Day = "45";
        windDirDay = "东北风";
        windScaleDay = "1-3";
        windSpeedDay = "3";
        wind360Night = "270";
        windDirNight = "西风";
        windScaleNight = "1-3";
        windSpeedNight = "16";
        humidity = "75";
        precip = "0.0";
        pressure = "1022";
        vis = "24";
        cloud = "25";
        uvIndex = "7";
    }

    // QString textDay;       // 天气
    // QString tempMax;       // 最高气温
    // QString tempMin;       // 最低气温
    // QString windDirDay;    // 风向
    // QString windScaleDay;  // 风力
    // QString humidity;      // 湿度

    QString fxDate;
    QString sunrise;
    QString sunset;
    QString moonrise;
    QString moonset;
    QString moonPhase;
    QString moonPhaseIcon;
    QString tempMax;
    QString tempMin;
    QString iconDay;
    QString textDay;
    QString iconNight;
    QString textNight;
    QString wind360Day;
    QString windDirDay;
    QString windScaleDay;
    QString windSpeedDay;
    QString wind360Night;
    QString windDirNight;
    QString windScaleNight;
    QString windSpeedNight;
    QString humidity;
    QString precip;
    QString pressure;
    QString vis;
    QString cloud;
    QString uvIndex;
};

class NowWeather
{
public:
    NowWeather()
    {
        obsTime = "2024-03-18T16:48+08:00";
        temp = "10";
        feelsLike = "7";
        icon = "104";
        text = "阴";
        wind360 = "45";
        windDir = "东北风";
        windScale = "2";
        windSpeed = "8";
        humidity = "42";
        precip = "0.0";
        pressure = "1016";
        vis = "25";
        cloud = "100";
        dew = "1";
    }
    QString obsTime;
    QString temp;
    QString feelsLike;
    QString icon;
    QString text;
    QString wind360;
    QString windDir;
    QString windScale;
    QString windSpeed;
    QString humidity;
    QString precip;
    QString pressure;
    QString vis;
    QString cloud;
    QString dew;
};



// 实时空气质量
class Air
{
public:
    Air()
    {
        pubTime = "2024-03-18T13:00+08:00";
        aqi = "62";
        level = "2";
        category = "良";
        primary = "PM10";
        pm10 = "74";
        pm2p5 = "26";
        no2 ="27";
        so2 = "8";
        co = "0.8";
        o3 = "58";
    }
    QString pubTime;
    QString aqi;
    QString level;
    QString category;
    QString primary;
    QString pm10;
    QString pm2p5;
    QString no2;
    QString so2;
    QString co;
    QString o3;
};


#endif // WEATHERDATA_H
