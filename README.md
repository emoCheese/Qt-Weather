## Qt天气预报

#### Qt版本 6.2.4











## 和风天气api文档链接

[每日天气预报 for API](https://dev.qweather.com/docs/api/weather/weather-daily-forecast/)

[实时空气质量 for API](https://dev.qweather.com/docs/api/air/air-now/)

>以下内容来自和风天气文档

## n天天气预报返回数据 

返回数据是JSON格式并进行了[Gzip压缩](https://dev.qweather.com/docs/best-practices/gzip/)。

```json
{
  "code": "200",
  "updateTime": "2021-11-15T16:35+08:00",
  "fxLink": "http://hfx.link/2ax1",
  "daily": [
    {
      "fxDate": "2021-11-15",
      "sunrise": "06:58",
      "sunset": "16:59",
      "moonrise": "15:16",
      "moonset": "03:40",
      "moonPhase": "盈凸月",
      "moonPhaseIcon": "803",
      "tempMax": "12",
      "tempMin": "-1",
      "iconDay": "101",
      "textDay": "多云",
      "iconNight": "150",
      "textNight": "晴",
      "wind360Day": "45",
      "windDirDay": "东北风",
      "windScaleDay": "1-2",
      "windSpeedDay": "3",
      "wind360Night": "0",
      "windDirNight": "北风",
      "windScaleNight": "1-2",
      "windSpeedNight": "3",
      "humidity": "65",
      "precip": "0.0",
      "pressure": "1020",
      "vis": "25",
      "cloud": "4",
      "uvIndex": "3"
    },
    {
      "fxDate": "2021-11-16",
      "sunrise": "07:00",
      "sunset": "16:58",
      "moonrise": "15:38",
      "moonset": "04:40",
      "moonPhase": "盈凸月",
      "moonPhaseIcon": "803",
      "tempMax": "13",
      "tempMin": "0",
      "iconDay": "100",
      "textDay": "晴",
      "iconNight": "101",
      "textNight": "多云",
      "wind360Day": "225",
      "windDirDay": "西南风",
      "windScaleDay": "1-2",
      "windSpeedDay": "3",
      "wind360Night": "225",
      "windDirNight": "西南风",
      "windScaleNight": "1-2",
      "windSpeedNight": "3",
      "humidity": "74",
      "precip": "0.0",
      "pressure": "1016",
      "vis": "25",
      "cloud": "1",
      "uvIndex": "3"
    },
    ......
  ],
  "refer": {
    "sources": [
      "QWeather",
      "NMC",
      "ECMWF"
    ],
    "license": [
      "QWeather Developers License"
    ]
  }
}
```

- `code` 请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
- `updateTime` 当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
- `fxLink` 当前数据的响应式页面，便于嵌入网站或应用
- `daily.fxDate` 预报日期
- `daily.sunrise` [日出时间](https://dev.qweather.com/docs/resource/sun-moon-info/#sunrise-and-sunset)，**在高纬度地区可能为空**
- `daily.sunset` [日落时间](https://dev.qweather.com/docs/resource/sun-moon-info/#sunrise-and-sunset)，**在高纬度地区可能为空**
- `daily.moonrise` 当天[月升时间](https://dev.qweather.com/docs/resource/sun-moon-info/#moonrise-and-moonset)，**可能为空**
- `daily.moonset` 当天[月落时间](https://dev.qweather.com/docs/resource/sun-moon-info/#moonrise-and-moonset)，**可能为空**
- `daily.moonPhase` [月相名称](https://dev.qweather.com/docs/resource/sun-moon-info/#moon-phase)
- `daily.moonPhaseIcon` 月相[图标代码](https://dev.qweather.com/docs/resource/icons/)，另请参考[天气图标项目](https://icons.qweather.com/)
- `daily.tempMax` 预报当天最高温度
- `daily.tempMin` 预报当天最低温度
- `daily.iconDay` 预报白天天气状况的[图标代码](https://dev.qweather.com/docs/resource/icons/)，另请参考[天气图标项目](https://icons.qweather.com/)
- `daily.textDay` 预报白天天气状况文字描述，包括阴晴雨雪等天气状态的描述
- `daily.iconNight` 预报夜间天气状况的[图标代码](https://dev.qweather.com/docs/resource/icons/)，另请参考[天气图标项目](https://icons.qweather.com/)
- `daily.textNight` 预报晚间天气状况文字描述，包括阴晴雨雪等天气状态的描述
- `daily.wind360Day` 预报白天[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)360角度
- `daily.windDirDay` 预报白天[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)
- `daily.windScaleDay` 预报白天[风力等级](https://dev.qweather.com/docs/resource/wind-info/#wind-scale)
- `daily.windSpeedDay` 预报白天[风速](https://dev.qweather.com/docs/resource/wind-info/#wind-speed)，公里/小时
- `daily.wind360Night` 预报夜间[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)360角度
- `daily.windDirNight` 预报夜间当天[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)
- `daily.windScaleNight` 预报夜间[风力等级](https://dev.qweather.com/docs/resource/wind-info/#wind-scale)
- `daily.windSpeedNight` 预报夜间[风速](https://dev.qweather.com/docs/resource/wind-info/#wind-speed)，公里/小时
- `daily.precip` 预报当天总降水量，默认单位：毫米
- `daily.uvIndex` 紫外线强度指数
- `daily.humidity` 相对湿度，百分比数值
- `daily.pressure` 大气压强，默认单位：百帕
- `daily.vis` 能见度，默认单位：公里
- `daily.cloud` 云量，百分比数值。**可能为空**
- `refer.sources` 原始数据来源，或数据源说明，**可能为空**
- `refer.license` 数据许可或版权声明，**可能为空**

## 空气质量返回数据 

返回数据是JSON格式并进行了[Gzip压缩](https://dev.qweather.com/docs/best-practices/gzip/)。

```json
{
  "code": "200",
  "updateTime": "2021-02-16T14:42+08:00",
  "fxLink": "http://hfx.link/2ax4",
  "now": {
    "pubTime": "2021-02-16T14:00+08:00",
    "aqi": "28",
    "level": "1",
    "category": "优",
    "primary": "NA",
    "pm10": "28",
    "pm2p5": "5",
    "no2": "3",
    "so2": "2",
    "co": "0.2",
    "o3": "76"
  },
  "station": [
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "密云镇",
      "id": "CNA3697",
      "aqi": "20",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "4",
      "pm2p5": "4",
      "no2": "4",
      "so2": "3",
      "co": "0.2",
      "o3": "63"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "万寿西宫",
      "id": "CNA1001",
      "aqi": "29",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "29",
      "pm2p5": "5",
      "no2": "3",
      "so2": "1",
      "co": "0.3",
      "o3": "75"
    }
  ],
  "refer": {
    "sources": [
      "cnemc"
    ],
    "license": [
      "QWeather Developers License"
    ]
  }
}
```

> **提示：**`station`字段，即监测站数据仅限在[空气质量监测站列表](https://github.com/qwd/LocationList/blob/master/POI-Air-Monitoring-Station-List-latest.csv)中的城市返回。

- `code` 请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
- `updateTime` 当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
- `fxLink` 当前数据的响应式页面，便于嵌入网站或应用
- `now.pubTime` 空气质量数据发布时间
- `now.aqi` 空气质量指数
- `now.level` 空气质量指数等级
- `now.category` 空气质量指数级别
- `now.primary` 空气质量的主要污染物，空气质量为优时，返回值为`NA`
- `now.pm10` PM10
- `now.pm2p5` PM2.5
- `now.no2` 二氧化氮
- `now.so2` 二氧化硫
- `now.co` 一氧化碳
- `now.o3` 臭氧
- `station.name` 监测站名称
- `station.id` 监测站ID
- `station.pubTime` 空气质量数据发布时间
- `station.aqi` 空气质量指数
- `station.level` 空气质量指数等级
- `station.category` 空气质量指数级别
- `station.primary` 空气质量的主要污染物，空气质量为优时，返回值为`NA`
- `station.pm10` PM10
- `station.pm2p5` PM2.5
- `station.no2` 二氧化氮
- `station.so2` 二氧化硫
- `station.co` 一氧化碳
- `station.o3` 臭氧
- `refer.sources` 原始数据来源，或数据源说明，**可能为空**
- `refer.license` 数据许可或版权声明，**可能为空**

## 实时天气预报返回数据 

返回数据是JSON格式并进行了[Gzip压缩](https://dev.qweather.com/docs/best-practices/gzip/)。

```json
{
  "code": "200",
  "updateTime": "2020-06-30T22:00+08:00",
  "fxLink": "http://hfx.link/2ax1",
  "now": {
    "obsTime": "2020-06-30T21:40+08:00",
    "temp": "24",
    "feelsLike": "26",
    "icon": "101",
    "text": "多云",
    "wind360": "123",
    "windDir": "东南风",
    "windScale": "1",
    "windSpeed": "3",
    "humidity": "72",
    "precip": "0.0",
    "pressure": "1003",
    "vis": "16",
    "cloud": "10",
    "dew": "21"
  },
  "refer": {
    "sources": [
      "QWeather",
      "NMC",
      "ECMWF"
    ],
    "license": [
      "QWeather Developers License"
    ]
  }
}
```

- `code` 请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
- `updateTime` 当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
- `fxLink` 当前数据的响应式页面，便于嵌入网站或应用
- `now.obsTime` 数据观测时间
- `now.temp` 温度，默认单位：摄氏度
- `now.feelsLike` 体感温度，默认单位：摄氏度
- `now.icon` 天气状况的[图标代码](https://dev.qweather.com/docs/resource/icons/)，另请参考[天气图标项目](https://icons.qweather.com/)
- `now.text` 天气状况的文字描述，包括阴晴雨雪等天气状态的描述
- `now.wind360` [风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)360角度
- `now.windDir` [风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)
- `now.windScale` [风力等级](https://dev.qweather.com/docs/resource/wind-info/#wind-scale)
- `now.windSpeed` [风速](https://dev.qweather.com/docs/resource/wind-info/#wind-speed)，公里/小时
- `now.humidity` 相对湿度，百分比数值
- `now.precip` 当前小时累计降水量，默认单位：毫米
- `now.pressure` 大气压强，默认单位：百帕
- `now.vis` 能见度，默认单位：公里
- `now.cloud` 云量，百分比数值。**可能为空**
- `now.dew` 露点温度。**可能为空**
- `refer.sources` 原始数据来源，或数据源说明，**可能为空**
- `refer.license` 数据许可或版权声明，**可能为空**
