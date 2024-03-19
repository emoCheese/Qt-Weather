#include "weatherinfo.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


WeatherInfo::WeatherInfo(QObject *parent)
    : QObject(parent)
    , _parent(static_cast<QWidget*>(parent))
    , _b_parse_weather(false)
    , _b_parse_air(false)
    , _b_parse_now(false)
    , _net_access_mgr(nullptr)
{

    _net_access_mgr = new QNetworkAccessManager(parent);
    // 初始化 city_map 和 request
    InitCityMap();
    InitWeatherApi();


    connect(_net_access_mgr, &QNetworkAccessManager::finished, this, &WeatherInfo::SlotOnWeatherReplied);
    // 获取 7 天， 空气质量，实时天气预报
    getWeatherInfo(_weather_url);
    getWeatherInfo(_air_url);
    getWeatherInfo(_now_url);
}

WeatherInfo::~WeatherInfo()
{
}

// 发送 https 请求获取天气数据
void WeatherInfo::getWeatherInfo(const QString& request_url)
{
    QUrl url(request_url);
    _net_access_mgr->get(QNetworkRequest(url));
}

QString WeatherInfo::getCityCode(const QString &city)
{
    if(_city_info_map.find(city) == _city_info_map.end())
        return "";
    return _city_info_map[city][0];
}

QString WeatherInfo::getCitybyCode(const QString &code)
{
    return _city_code_map[code];
}

// 解析空气质量
void WeatherInfo::parseAirJson(QByteArray& byte_arr)
{
    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(byte_arr, &err);
    if(err.error != QJsonParseError::NoError)
    {
        return;
    }
    QJsonObject root_obj = json_doc.object();
    // 获取空气质量预报
    QJsonObject now_air = root_obj.value("now").toObject();
    qDebug() << "当前空气质量: " << now_air;
    // 获取部分
    _air.category = now_air.value("category").toString();
    _air.pm2p5 = now_air.value("pm2p5").toString();
    _b_parse_air = true;
}

// 解析7天天气预报
void WeatherInfo::parseWeatherJson(QByteArray& byte_arr)
{
    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(byte_arr, &err);
    if(err.error != QJsonParseError::NoError)
    {
        return;
    }
    QJsonObject root_obj = json_doc.object();

    // 获取 7 天天气预报
    QJsonArray daliy_arr = root_obj.value("daily").toArray();
    qDebug() << "七天天气预报: " << daliy_arr;
    for(int i = 0; i < FORECAST_DAYS; ++i)
    {
        QJsonObject daliy_obj = daliy_arr[i].toObject();
        // 获取部分
        _weather_infos[i].fxDate = daliy_obj.value("fxDate").toString();            // 预报日期
        _weather_infos[i].textDay = daliy_obj.value("textDay").toString();
        _weather_infos[i].tempMax = daliy_obj.value("tempMax").toString();
        _weather_infos[i].tempMin = daliy_obj.value("tempMin").toString();
        _weather_infos[i].windDirDay = daliy_obj.value("windDirDay").toString();     // 白天风向
        _weather_infos[i].windScaleDay = daliy_obj.value("windScaleDay").toString(); // 白天风力等级
        _weather_infos[i].humidity = daliy_obj.value("humidity").toString();         // 空气湿度
    }
    _b_parse_weather = true;
}

// 解析实时天气预报
void WeatherInfo::parseNowWeatherJson(QByteArray &byte_arr)
{
    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(byte_arr, &err);
    if(err.error != QJsonParseError::NoError)
    {
        return;
    }
    QJsonObject root_obj = json_doc.object();
    QJsonObject now_weather = root_obj.value("now").toObject();
    qDebug() << "实时天气: " << now_weather;

    // 获取部分
    _now_weather.temp = now_weather.value("temp").toString();           // 气温
    _now_weather.text = now_weather.value("text").toString();           // 天气
    _now_weather.humidity = now_weather.value("humidity").toString();   // 湿度
    _now_weather.windDir = now_weather.value("windDir").toString();     // 风向
    _now_weather.windScale = now_weather.value("windScale").toString(); // 风力等级
    _b_parse_now = true;
}

bool WeatherInfo::isParsed() const
{
    return _b_parse_air && _b_parse_now && _b_parse_weather;
}

// 更新天气 api 并重新获取信息 和 city 名
void WeatherInfo::SlotUpdateApi(QString text)
{
    if(_city_info_map.find(text) == _city_info_map.end())
    {
        qDebug() << "该地区不存在或未录入\n";
        QMessageBox::information(_parent, "提示", "该地区未找到", QMessageBox::Ok);
        return;
    }
    qDebug() << _city_info_map[text] << Qt::endl;
    _cur_city = text;
    _city_code = _city_info_map[text][0];
    _weather_url = _prefix_weather + _city_code + _api_key;
    _air_url = _prefix_air + _city_code + _api_key;
    _now_url = _prefix_now + _city_code + _api_key;
    qDebug() << _weather_url << Qt::endl << _air_url << Qt::endl << _now_url;

    // api 更新后重新获取
    getWeatherInfo(_weather_url);
    getWeatherInfo(_air_url);
    getWeatherInfo(_now_url);
}

void WeatherInfo::SlotOnWeatherReplied(QNetworkReply *reply)
{
    // 获取状态码
    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if(reply->error() != QNetworkReply::NoError || status_code != 200)
    {
        qDebug() << reply->errorString().toUtf8().data();
        QMessageBox::warning(_parent , "天气", "请求数据失败", QMessageBox::Ok);
        return;
    }
    // 通过判断不同的 url 处理不同的reply
    // 或者调用不同的处理函数
    if(reply->url() == QUrl(_weather_url))
    {
        QByteArray byte_arr = reply->readAll();
        // to do
        parseWeatherJson(byte_arr);
    }
    else if(reply->url() == QUrl(_air_url))
    {
        QByteArray byte_arr = reply->readAll();
        // to do

        parseAirJson(byte_arr);

    }
    else if(reply->url() == QUrl(_now_url))
    {
        QByteArray byte_arr = reply->readAll();
        // to do

        parseNowWeatherJson(byte_arr);
    }
    reply->deleteLater();
    // 当最后一个信息被解析完成时发生更新 UI signal
    if(!isParsed())
        emit SigUpdateUI();
}

// 从外部csv文件中读取城市列表
void WeatherInfo::InitCityMap()
{
    QString fileName = ":/res/city_list/China-City-List-latest.csv";
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << "城市CSV文件打开失败\n";
        return;
    }
    QTextStream stream(&file);
    // 逐行读取文件内容
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList parts = line.split(","); // 假设CSV文件中字段是用逗号分隔的
        // 选择第1、第3和第8列的数据
        QString col1 = parts[0];
        QString col3 = parts[2];
        QString col8 = parts[7];
        QString col9 = parts[8];

        QStringList selectedColumns;
        // 城市编号，省，地区，城市
        selectedColumns << col1 << col8 << col3 << col9;
        _city_info_map[col3] = selectedColumns;
        _city_code_map[col1] = col3;
    }

    file.close();
}

// 从外部文件中读取 api key
void WeatherInfo::InitWeatherApi()
{
    auto fileName = ":/res/city_weather_api.txt";
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << "天气api文件打开错误\n";
        return;
    }
    QTextStream stream(&file);

    for(int i = 0; i < 5; ++i)
    {
        QString line = stream.readLine();
        if(i == 0)
            _prefix_weather = line;
        else if(i == 1)
            _prefix_air = line;
        else if(i == 2)
            _prefix_now = line;
        else if(i == 3)
        {
            _city_code = line;
            _cur_city = _city_code_map[_city_code];
        }
        else
            _api_key = line;
    }
    _air_url = _prefix_air + _city_code + _api_key;
    _weather_url = _prefix_weather + _city_code + _api_key;
    _now_url = _prefix_now + _city_code + _api_key;
    qDebug() << "api 初始化\n" << _weather_url << Qt::endl << _air_url << Qt::endl << _now_url;
}

void WeatherInfo::ResetBoolen()
{
    _b_parse_weather = _b_parse_air = _b_parse_now = false;
}

