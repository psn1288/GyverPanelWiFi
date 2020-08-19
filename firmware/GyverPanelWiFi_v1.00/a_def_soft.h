// Определения программных констант и переменных (параметры эффектов и т.п.)

// При запуске микроконтроллера выполняется инициализация всех параметров значениями, сохраненными в EEPROM (функция loadSettings() в eeprom.ino)
// При этом если флаг EEPROM_OK в первой строке файла eeprom.ino был изменен и не совпадает со считанными яз ячейки #1 значением -
// выполняется инициализация параметров значениями по умолчанию (функция loadSettings() в eeprom.ino, ветвь if (isInitialized) -> false )
// Заполните в этом блоки значения переменных желаемыми.

#define DEBUG 0                  // Отладочный вывод 0 - отключен, 1 - включен
#define EEPROM_OK 0xA7           // Флаг, показывающий, что EEPROM инициализирована корректными данными 
#define EEPROM_MAX 4096          // Максимальный размер EEPROM доступный для использования
#define EFFECT_EEPROM 300        // начальная ячейка eeprom с параметрами эффектов, 5 байт на эффект
#define TEXT_EEPROM 800          // начальная ячейка eeprom с текстом бегущих строк

// ******************* ОПРЕДЕЛЕНИЯ ПАРАМЕТРОВ ЭФФЕКТОВ *********************

// Список и порядок эффектов, передаваймый в приложение на смартфоне. Данный список попадает в комбобокс выбора, 
// чей индекс передается из приложения в контроллер матрицы для выбора, поэтому порядок должен соответствовать 
// списку эффектов, определенному выше
#define EFFECT_LIST F("Ночные часы,Лампа,Снегопад,Кубик,Радуга,Пейнтбол,Огонь,The Matrix,Шарики,Звездопад,Конфетти," \
                      "Цветной шум,Облака,Лава,Плазма,Радужные переливы,Полосатые переливы,Зебра,Шумящий лес,Морской прибой,Смена цвета," \
                      "Светлячки,Водоворот,Циклон,Мерцание,Северное сияние,Тени,Лабиринт,Змейка,Тетрис," \
                      "Палитра,Спектрум,Синусы,Вышиванка,Дождь,Камин,Водопад,Стрелки,Анимация,Рассвет")

// ID эффектов
#define MC_CLOCK                 0         // Режим отображения часов (когда "Ночные часы" или просто "Часы" на черном фоне, а не как оверлей поверх других эффектов
#define MC_FILL_COLOR            1
#define MC_SNOW                  2
#define MC_BALL                  3
#define MC_RAINBOW               4
#define MC_PAINTBALL             5
#define MC_FIRE                  6
#define MC_MATRIX                7
#define MC_BALLS                 8
#define MC_STARFALL              9
#define MC_SPARKLES             10
#define MC_NOISE_MADNESS        11
#define MC_NOISE_CLOUD          12
#define MC_NOISE_LAVA           13
#define MC_NOISE_PLASMA         14
#define MC_NOISE_RAINBOW        15
#define MC_NOISE_RAINBOW_STRIP  16
#define MC_NOISE_ZEBRA          17
#define MC_NOISE_FOREST         18
#define MC_NOISE_OCEAN          19
#define MC_COLORS               20
#define MC_LIGHTERS             21
#define MC_SWIRL                22
#define MC_CYCLON               23
#define MC_FLICKER              24
#define MC_PACIFICA             25
#define MC_SHADOWS              26
#define MC_MAZE                 27
#define MC_SNAKE                28
#define MC_TETRIS               29
#define MC_PALETTE              30
#define MC_ANALYZER             31
#define MC_PRIZMATA             32
#define MC_MUNCH                33
#define MC_RAIN                 34
#define MC_FIRE2                35
#define MC_WATERFALL            36
#define MC_ARROWS               37
#define MC_IMAGE                38
#define MC_DAWN_ALARM           39

#define MAX_EFFECT              40         // количество эффектов, определенных в прошивке
#define MAX_SPEC_EFFECT         11         // количество эффектов быстрого доступа определенных в прошивке -> 0..10

// ---------------------------------
#define SPECIAL_EFFECTS_START  120         // Некоторые специальные "служебные" эффекты имеют код >= SPECIAL_EFFECTS_START
                                           // Внимание !!! - для идентификатора режима используется тип int8_t (-128..127, нужно значение -1), поэтому код режима не может быть больше 127 !!!
#define MC_TEXT                125         // Режим бегущей строки (для отображения IP адреса) - бегущая строка на черном фоне
#define MC_DAWN_ALARM_SPIRAL   126         // Специальный режим, вызывается из DEMO_DAWN_ALARM для ламп на круговой матрице - огонек по спирали
#define MC_DAWN_ALARM_SQUARE   127         // Специальный режим, вызывается из DEMO_DAWN_ALARM для плоских матриц - огонек по спирали на плоскости матрицы
// ---------------------------------

// ****************** ОПРЕДЕЛЕНИЯ ПАРАМЕТРОВ БУДИЛЬНИКА ********************

#if (USE_MP3 == 1)
// SD карточка в MP3 плеере (DFPlayer) содержить в корне две папки - "1" и "2"
// Папка "1" содержит MP3 файлы звуков, проигрываемых при наступлении события будильника
// Папка "2" содержит MP3 файлы звуков, проигрываемых при наступлении события рассвета
// DFPlayer не имеет возможности считывать имена файлов, только возможность получить количество файлов в папке.
// Команда на воспроизведение звука означает - играть файл с индексом (номером) N из папки M
// Номера файлов определяются таблицей размещения файлов SD-карты (FAT)  и формируются в порядке очереди записи файлов на чистую флэшку
// Так, файл записанный в папку первым получает номер 1, вторыи - 2 и так далее и ника не зависит от имен файлов
// Данные массивы содержат отображаемые в приложении имена звуков в порядке, соответствующем нумерации записанных в папки файлов.
#define ALARM_SOUND_LIST F("One Step Over,In the Death Car")            // Список звука для комбобокса "Звук будильника" в приложении на смартфоне
#define DAWN_SOUND_LIST  F("Птицы,Гроза,Прибой,Дождь,Ручей,Мантра")     // Список звука для комбобокса "Звук рассвета" в приложении на смартфоне
#endif

// ********************* ОПРЕДЕЛЕНИЯ ПАРАМЕТРОВ ЧАСОВ **********************

#define D_CLOCK_SPEED 100                 // скорость перемещения эффекта часов по умолчанию (мс)
#define D_CLOCK_SPEED_MIN 2
#define D_CLOCK_SPEED_MAX 255

byte CLOCK_SIZE = 0;                      // Размер горизонтальных часов: 0 - авто; 1 - цифры 3x5; 2 - цифры 5х7
byte CLOCK_ORIENT = 0;                    // Ориентация отображения часов: 0 горизонтальные, 1 вертикальные (только для режима часов с цифрами 3х5; Часы шрифтом 5x7 всегда горизонтальные
byte CLOCK_MOVE_DIVIDER = 3;              // Делитель такта таймера эффектов для движения часов оверлея (режим прокручивания часов по горизонтали)
byte CLOCK_MOVE_CNT = CLOCK_MOVE_DIVIDER; // Текущее значения счетчика сдвига 

// Макрос центрирования отображения часов на матрице
#define CLOCK_X_H1 (byte((WIDTH - (4*3 + 3*1)) / 2.0 + 0.51))      // 4 цифры * (шрифт 3 пикс шириной) 3 + пробела между цифрами), /2 - в центр 
#define CLOCK_Y_H1 (byte((HEIGHT - (1*5)) / 2.0 + 0.51))           // Одна строка цифр 5 пикс высотой  / 2 - в центр
#define CLOCK_X_H2 (byte((WIDTH - (4*5 + 2*1 + 4)) / 2.0 + 0.51))  // 4 цифры * (шрифт 5 пикс шириной) 3 + пробела между цифрами) + 4 - ширина точек, /2 - в центр 
#define CLOCK_Y_H2 (byte((HEIGHT - (1*7)) / 2.0 + 0.51))           // Одна строка цифр 7 пикс высотой  / 2 - в центр
#define CLOCK_X_V  (byte((WIDTH - (2*3 + 1)) / 2.0 + 0.51))        // 2 цифры * (шрифт 3 пикс шириной) 1 + пробел между цифрами) /2 - в центр
#define CLOCK_Y_V  (byte((HEIGHT - (2*5 + 1)) / 2.0 + 0.51))       // Две строки цифр 5 пикс высотой + 1 пробел между строкми / 2 - в центр

// Макрос центрирования отображения календаря на матрице
#define CAL_X      (byte((WIDTH - (4*3 + 1)) / 2.0))               // 4 цифры * (шрифт 3 пикс шириной) 1 + пробел между цифрами) /2 - в центр
#define CAL_Y      (byte((HEIGHT - (2*5 + 1)) / 2.0))              // Две строки цифр 5 пикс высотой + 1 пробел между строкми / 2 - в центр

byte clockSpeed = D_CLOCK_SPEED;            // Скорость прокрутки часов
byte c_size = 0;                            // тип часов: 0 - авто; 1 - шрифт 3x5; 2 - шрифт 5х7; вычисляется в зависимости от настроек и параметров матрицы 

// Позиции отображения статических часов; Вычисляется в зависимости от выбранного шрифта часов 3x5 или 5x7, вертикальные/горизонтальные
byte   CALENDAR_X  = CAL_X;                 // По умолчанию - 3x5, горизонтальные - позиция вывода календаря по X
byte   CALENDAR_Y  = CAL_Y;                 // По умолчанию - 3x5, горизонтальные - позиция вывода календаря по Y
byte   CLOCK_X     = CLOCK_X_H1;            // По умолчанию - 3x5, горизонтальные - позиция вывода часов по X
byte   CLOCK_Y     = CLOCK_Y_H1;            // По умолчанию - 3x5, горизонтальные - позиция вывода часов по Y

int8_t CLOCK_XC    = CLOCK_X;               // Текущая позиция часов оверлея по оси Х 
int8_t CALENDAR_XC = CALENDAR_X;            // Текущая позиция календаря оверлея по оси Х 

// Часы могут отображаться: 
// - вертикальные при высоте матрицы >= 11 и ширине >= 7; 
// - горизонтальные при ширене матрицы >= 15 и высоте >= 5
//   минимальная ширина горизонтальных часов - 15 символов, т.к если большие часы не влазят по ширине - автоматически используются маленькие часы
bool allowVertical   = WIDTH >= 7  && HEIGHT >= 11;
bool allowHorizontal = WIDTH >= 15 && HEIGHT >= 7;

byte COLOR_MODE = 0;                     // Режим цвета часов
                                         //  0 - монохром
                                         //  1 - радужная смена (каждая цифра)
                                         //  2 - радужная смена (часы, точки, минуты)
                                         //  3 - заданные цвета (часы, точки, минуты) - HOUR_COLOR, DOT_COLOR, MIN_COLOR в clock.ino

byte    nightClockColor = 0;             // Цвет ночных часов: 0 - R; 1 - G; 2 - B; 3 - C; 4 - M; 5 - Y;
bool    needTurnOffClock = false;        // Выключать индикатор часов TM1637 при выключении устройства (true); если False - при отключении панели индикатор TM1637 продолжает показывать текущее время

boolean showDateInClock = true;          // Показывать дату при отображении часов
byte    showDateDuration = 3;            // на 3 секунд
byte    showDateInterval = 240;          // через каждые 240 секунд
byte    showDateState = false;           // false - отображаются часы; true - отображается дата
long    showDateStateLastChange = 0;     // Время, когда отображение часов сменилось на отображение календаря и наоборот

int8_t  hrs = 0, mins = 0;               // Для получения текущего времени. Инициализировано как 01.01.1970 00:00
int8_t  secs = 0, aday = 1, amnth = 1;
int16_t ayear = 1970;
bool    dotFlag;                         // флаг: в часах рисуется точки 

// ************************ НАСТРОЙКИ БЕГУЩЕЙ СТРОКИ ***********************

#define D_TEXT_SPEED 100                 // скорость перемещения эффекта часов по умолчанию (мс)
#define D_TEXT_SPEED_MIN 2
#define D_TEXT_SPEED_MAX 255

#define MIRR_V 0                         // отразить текст по вертикали (0 / 1)
#define MIRR_H 0                         // отразить текст по горизонтали (0 / 1)

#define LET_WIDTH 5                      // ширина буквы шрифта
#define LET_HEIGHT 8                     // высота буквы шрифта
#define SPACE 1                          // пробел между буквами

byte textSpeed = D_TEXT_SPEED;           // Скорость прокрутки оверлея бегущей строки

uint16_t TEXT_INTERVAL = 90;             // Интервал (время в секундах) между отображением строк
                                         // следующая бегущая строка будет отображена через указанное кол-во секунд
                                         // 0 - отключено, следующая строка отображается после завершения текущей
                                         
byte COLOR_TEXT_MODE = 0;                // Режим цвета текста бегущей строки и самой бегущей строки
                                         //  0 - монохром
                                         //  1 - радужная смена (каждая цифра)
                                         //  2 - каждая цифра свой цвет
                                         
// --- Параметры отображения текущей бегущей строки
int16_t  textShowTime = -1;              // Если больше нуля - сколько времени отображать бегущую строку в секундах; Если 0 - используется textShowCount; В самой строке спец-макросом может быть указано кол-во секунд
byte     textShowCount = 1;              // Сколько раз прокручивать текст бегущей строки поверх эффектов; По умолчанию - 1; В самой строке спец-макросом может быть указано число 
byte     textCurrentCount = 0;           // Сколько раз текст очередной бегущей строки поверх эффектов уже показан
boolean  useSpecialTextColor = false;    // В текущей бегущей строке был задан цвет, которым она должна отображаться
uint32_t specialTextColor = 0xffffff;    // Цвет отображения бегущей строки, может быть указан макросом в строке. Если не указан - используются глобальные настройки цвета бегущей строки
boolean  useSpecialBackColor = false;    // В текущей бегущей строке был задан цвет фона, на котором она должна отображаться
uint32_t specialBackColor = 0x000000;    // Цвет фона отображения бегущей строки, может быть указан макросом в строке. Если не указан - наложение на текущий эффект
int8_t   specialTextEffect = -1;         // Эффект, который нужно включить при начале отображения строки текста, может быть указан макросом в строке.
int8_t   saveEffectBeforeText = -1;      // Если указан эффект на котором отображать строку, сохранить текущий эфф тут, чтобы по зпвершению строки восстановить его
int8_t   currentTextLineIdx = -1;        // Какая строка из массива строк показыватся в текущий момент
int8_t   nextTextLineIdx = -1;           // Какую следующую строку показыват, может быть указан макросом в строке. Если указан - интервал отображения игнорируется, строка показывается сразу
boolean  textHasDateTime = false;        // Строка имеет макрос отображения текущего времени - ее нужно пересчитывать каждый раз при отрисовкеж Если макроса времени нет - рассчитать текст строки один раз на этапе инициализации
String   currentText  = "";              // Текст текущей отображаемаой строки
boolean  ignoreTextOverlaySettingforEffect = false; // Показывать бегущую строку для эффекта, даже если настройки эффекта это запрещают; В строке может быть указано, какую строку показывать следующей - ее надо показывать даже если настройки текущего эффекта это запрещают
int8_t   sequenceIdx = -1;               // Если нулевая строка массива содержит последовательность отображеняи строк (начинается с # или имеет значение ##  - указывает на позицию какой будет следующая отображаемая строка
char     editIdx = '#';                  // Индекс строки, которая в настоящий момент редактируется в приложении - 0..9,A..Z; другой символ - нет активной строки
int8_t   sendTextIdx = -1;               // Индекс строки, передаваемой в телефон для заполнения списка строк
uint16_t crc = 0;                        // Контрольная сумма загруженного массива строк. Рассчитывается при загрузке, проверяется перед сохранением 
int16_t  memoryAvail = 0;                // Сколько памяти осталось под хранение строк; Устанавливается при загрузке / сохранении массива строк
// --- 

unsigned long textStartTime = 0;         // Время начала отображения текущей бегущей строки
unsigned long textLastTime = 0;          // Время завершения отображения последней показанной бегущей строки
unsigned long textLastSend = 0;          // Время последней отправки очередной строки списка строк в телефон

boolean loadingTextFlag = false;         // Флаг инициализации показа строки в режиме MC_TEXT (показ IP адреса); для новой строки оверлейного текста используется специальный вызов prepareNextText() в custom.ino
boolean showTextNow = false;             // флаг: что в настоящий момент нужно отображать оверлеем: true - оверлей бегущей строкиж false - оверлей часов;
boolean fullTextFlag = false;            // флаг: текст бегущей строки показан полностью (строка убежала)
boolean gameOverFlag = false;            // флаг: демо-игра завершена

String  textLines[36];                   // Массив строк для отображения 0..9A..Z; 

// *************************** ПОДКЛЮЧЕНИЕ К СЕТИ **************************

// Внимание!!! Если вы меняете эти значения ПОСЛЕ того, как прошивка уже хотя бы раз была загружена в плату и выполнялась,
// чтобы изменения вступили в силу нужно также изменить значение константы EEPROM_OK в первой строке в файле eeprom.ino 

#define DEFAULT_NTP_SERVER "ru.pool.ntp.org" // NTP сервер по умолчанию "time.nist.gov"
#define DEFAULT_AP_NAME "PanelAP"        // Имя точки доступа по умолчанию 
#define DEFAULT_AP_PASS "12341234"       // Пароль точки доступа по умолчанию
#define NETWORK_SSID ""                  // Имя WiFi сети
#define NETWORK_PASS ""                  // Пароль для подключения к WiFi сети

// ---------------------------------------------------------------

WiFiUDP udp;
                                         // к длине +1 байт на \0 - терминальный символ. Это буферы для загрузки имен/пароля из EEPROM. Значения задаются в defiine выше
char   apName[11] = "";                  // Имя сети в режиме точки доступа
char   apPass[17] = "";                  // Пароль подключения к точке доступа
char   ssid[25]   = "";                  // SSID (имя) вашего роутера (конфигурируется подключением через точку доступа и сохранением в EEPROM)
char   pass[17]   = "";                  // пароль роутера
byte   IP_STA[]   = {192, 168, 0, 116};  // Статический адрес в локальной сети WiFi по умолчанию при первом запуске. Потом - загружается из настроек, сохраненных в EEPROM
unsigned int localPort = 2390;           // локальный порт на котором слушаются входящие команды управления от приложения на смартфоне, передаваемые через локальную сеть

// ---------------------------------------------------------------

bool   useSoftAP = false;                // использовать режим точки доступа
bool   wifi_connected = false;           // true - подключение к wifi сети выполнена  
bool   ap_connected = false;             // true - работаем в режиме точки доступа;
bool   wifi_print_ip = false;            // Включен режим отображения текущего IP на индикаторе TM1637
bool   wifi_print_ip_text = false;       // Включен режим отображения текущего IP на матрице
byte   wifi_print_idx = 0;               // Индекс отображаемой на индикаторе TM1637 тетрады IP адреса
String wifi_current_ip = "";             // Отображаемый в бегущей строке IP адрес лампы

// **************** СИНХРОНИЗАЦИЯ ЧАСОВ ЧЕРЕЗ ИНТЕРНЕТ ********************

IPAddress timeServerIP;
#define NTP_PACKET_SIZE 48               // NTP время - в первых 48 байтах сообщения
uint16_t SYNC_TIME_PERIOD = 60;          // Период синхронизации в минутах по умолчанию
byte packetBuffer[NTP_PACKET_SIZE];      // буфер для хранения входящих и исходящих пакетов NTP

int8_t timeZoneOffset = 7;               // смещение часового пояса от UTC
long   ntp_t = 0;                        // Время, прошедшее с запроса данных с NTP-сервера (таймаут)
byte   ntp_cnt = 0;                      // Счетчик попыток получить данные от сервера
bool   init_time = false;                // Флаг false - время не инициализировано; true - время инициализировано
bool   refresh_time = true;              // Флаг true - пришло время выполнить синхронизацию часов с сервером NTP
bool   useNtp = true;                    // Использовать синхронизацию времени с NTP-сервером
char   ntpServerName[31] = "";           // Используемый сервер NTP

// *********************** ДЛЯ БУДИЛЬНИКА-РАССВЕТ ************************

bool   isAlarming = false;               // Сработал будильник "рассвет"
bool   isPlayAlarmSound = false;         // Сработал настоящий будильник - играется звук будильника
bool   isAlarmStopped = false;           // Сработавший будильник "рассвет" остановлен пользователем

byte   alarmWeekDay = 0;                 // Битовая маска дней недели будильника
byte   alarmDuration = 1;                // Проигрывать звук будильнике N минут после срабатывания (по окончанию рассвета)

byte   alarmHour[7]   = {0,0,0,0,0,0,0}; // Часы времени срабатывания будильника по дням недели
byte   alarmMinute[7] = {0,0,0,0,0,0,0}; // Минуты времени срабатывания будильника по дням недели

int8_t dawnHour = 0;                     // Часы времени начала рассвета
int8_t dawnMinute = 0;                   // Минуты времени начала рассвета
byte   dawnWeekDay = 0;                  // День недели времени начала рассвета (0 - выключено, 1..7 - пн..вс)
byte   dawnDuration = 0;                 // Продолжительность "рассвета" по настройкам
byte   realDawnDuration = 0;             // Продолжительность "рассвета" по вычисленому времени срабатывания будильника
byte   alarmEffect = MC_DAWN_ALARM;      // Какой эффект используется для будильника "рассвет". Могут быть обычные эффекты - их яркость просто будет постепенно увеличиваться

// **************************** MP3 ПЛЕЕР *****************************

bool isDfPlayerOk = false;               // MP3-Player корректно инициализирован и готов к использованию

#if (USE_MP3 == 1)
#if defined(ESP8266)
//SoftwareSerial mp3Serial(SRX, STX);    // Используйте этот вариант, если у вас библиотека ядра ESP8266 версии 2.5.2
  SoftwareSerial mp3Serial;              // Используйте этот вариант, если у вас библиотека ядра ESP8266 версии 2.6.x
#endif
#if defined(ESP32)
  SoftwareSerial mp3Serial;
#endif

DFRobotDFPlayerMini dfPlayer; 
int16_t  alarmSoundsCount = 0;           // Кол-во файлов звуков в папке '01' на SD-карте
int16_t  dawnSoundsCount = 0;            // Кол-во файлов звуков в папке '02' на SD-карте
byte     soundFolder = 0;                // Текущая используемая папка со звуками 
byte     soundFile = 0;                  // Текущий используемый файл звука в папке
int8_t   fadeSoundDirection = 1;         // направление изменения громкости звука: 1 - увеличение; -1 - уменьшение
byte     fadeSoundStepCounter = 0;       // счетчик шагов изменения громкости, которое осталось сделать
bool     useAlarmSound = false;          // Использовать звуки в будильнике
int8_t   alarmSound = 0;                 // Звук будильника - номер файла в папке SD:/01 [-1 не использовать; 0 - случайный; 1..N] номер файла
int8_t   dawnSound = 0;                  // Звук рассвета   - номер файла в папке SD:/02 [-1 не использовать; 0 - случайный; 1..N] номер файла
byte     maxAlarmVolume = 30;            // Максимальная громкость будильника (1..30)
#endif

// ************************* КНОПКА УПРАВЛЕНИЯ *************************

// GButton butt(PIN_BTN, LOW_PULL, NORM_OPEN); // Для сенсорной кнопки
GButton butt(PIN_BTN, HIGH_PULL, NORM_OPEN);   // Для обычной кнопки

bool     isButtonHold = false;           // Кнопка нажата и удерживается
byte     bCounter = 0;                   // Счетчик нажатия на кнопку

// ************************** Дисплей TM1637 **************************

#if (USE_TM1637 == 1)
TM1637Display display(CLK, DIO);
bool     aDirection = true;              // Направление счетчика изменения яркости, отображаемом на индикаторе при регулировке
byte     aCounter = 0;                   // Текущая яркость индикатора при плавном изменении яркости
uint32_t fade_time;                      // Для плавного изменения яркости индикатора при сработавшем будильнике
#endif

// ******************** ВКЛЮЧЕНИЕ РЕЖИМОВ ПО ВРЕМЕНИ *********************

bool     AM1_running = false;            // Режим 1 по времени - работает
byte     AM1_hour = 0;                   // Режим 1 по времени - часы
byte     AM1_minute = 0;                 // Режим 1 по времени - минуты
int8_t   AM1_effect_id = -3;             // Режим 1 по времени - ID эффекта или -3 - выключено (не используется); -2 - выключить матрицу (черный экран); -1 - ночные часы, 0 - случайный, 1 и далее - эффект EFFECT_LIST
bool     AM2_running = false;            // Режим 2 по времени - работает
byte     AM2_hour = 0;                   // Режим 2 по времени - часы
byte     AM2_minute = 0;                 // Режим 2 по времени - минуты
int8_t   AM2_effect_id = -3;             // Режим 2 по времени - ID эффекта или -3 - выключено (не используется); -2 - выключить матрицу (черный экран); -1 - ночные часы, 0 - случайный, 1 и далее - эффект EFFECT_LIST
bool     AM3_running = false;            // Режим 3 по времени - работает
byte     AM3_hour = 0;                   // Режим 3 по времени - часы
byte     AM3_minute = 0;                 // Режим 3 по времени - минуты
int8_t   AM3_effect_id = -3;             // Режим 3 по времени - ID эффекта или -3 - выключено (не используется); -2 - выключить матрицу (черный экран); -1 - ночные часы, 0 - случайный, 1 и далее - эффект EFFECT_LIST
bool     AM4_running = false;            // Режим 4 по времени - работает
byte     AM4_hour = 0;                   // Режим 4 по времени - часы
byte     AM4_minute = 0;                 // Режим 4 по времени - минуты
int8_t   AM4_effect_id = -3;             // Режим 4 по времени - ID эффекта или -3 - выключено (не используется); -2 - выключить матрицу (черный экран); -1 - ночные часы, 0 - случайный, 1 и далее - эффект EFFECT_LIST

// ************************* ПРОЧИЕ ПЕРЕМЕННЫЕ *************************

#if (SMOOTH_CHANGE == 1)
  byte fadeMode = 4;                     // Фаза режима плавной смены эффекта
  boolean modeDir;                       // Направление перехода к следующему / предыдущему режиму
#endif

// ---------------------------------------------------------------

#define  D_EFFECT_SPEED       80         // скорость эффектов по умолчанию (мс)
#define  D_EFFECT_SPEED_MIN    0         // пределы регулировки скорости
#define  D_EFFECT_SPEED_MAX  255

// ---------------------------------------------------------------

#define  AUTOPLAY_PERIOD 60              // время между авто сменой режимов (секунды)
#define  IDLE_TIME 30                    // время бездействия (в минутах, по умолчанию) после которого запускается автосмена режимов, если разрешена в настройках
#define  SMOOTH_CHANGE 0                 // плавная смена режимов через чёрный

// ---------------------------------------------------------------

bool     eepromModified = false;         // флаг: EEPROM изменен, требует сохранения

// ---------------------------------------------------------------

uint32_t globalColor      = 0xffffff;    // цвет панели в режиме "Лампа" по умолчанию
uint32_t globalClockColor = 0xffffff;    // цвет часов в режиме MC_COLOR - режим цвета "Монохром" по умолчанию
uint32_t globalTextColor  = 0xffffff;    // цвет бегущей строки MC_TEXT в режиме цвета "Монохром" по умолчанию

// ---------------------------------------------------------------

bool     AUTOPLAY = false;               // false выкл / true вкл автоматическую смену режимов (откл. можно со смартфона)
bool     specialMode = false;            // Спец.режим, включенный вручную со смартфона или с кнопок быстрого включения режима
bool     specialClock = false;           // Отображение часов в спец.режиме - как отдельный эффект "Часы" на черном фоне, а не как оверлей поверх других эффектов
byte     specialBrightness = 1;          // Яркость в спец.режиме

bool     isTurnedOff = false;            // Включен черный экран (т.е всё выключено) 
bool     isNightClock = false;           // Включен режим ночных часов

int8_t   specialModeId = -1;             // Номер текущего спецрежима
int8_t   manualModeId = -1;              // Номер текущего режима

bool     useRandomSequence = true;       // Флаг: случайный выбор режима
bool     clockOverlayEnabled = true;     // Доступность оверлея часов поверх эффектов
bool     textOverlayEnabled = true;      // Доступность оверлея бегущей строки поверх эффектов
bool     overlayDelayed = false;         // используется для указания был ли оверлей на пердыдцщем цикле отрисовки
int8_t   y_overlay_low  = 0;             // Вычисленная позицуия оверлея матрицы - во всю ширину, область отображения текста бегущей строки / часов / календаря
int8_t   y_overlay_high = 0;

// ---------------------------------------------------------------

// Сервер не может инициировать отправку сообщения клиенту - только в ответ на запрос клиента
// Следующие две переменные хранят сообщения, формируемые по инициативе сервира и отправляются в ответ на ближайший запрос от клиента,
// например в ответ на периодический ping - в команде sendAcknowledge();

String   cmd95 = "";                     // Строка, формируемая sendPageParams(95) для отправки по инициативе сервера
String   cmd96 = "";                     // Строка, формируемая sendPageParams(96) для отправки по инициативе сервера

// ---------------------------------------------------------------

byte     globalBrightness = BRIGHTNESS;  // текущая яркость бегущей строки и часов (общая)
byte     contrast = 255;                 // контрастность эффектов по отношению к яркости часов / бегущей строки (общей яркости) => 0.255 -> 10..100%
bool     brightDirection = false;        // true - увеличение яркости; false - уменьшение яркости при регулировке кнопкой

// ---------------------------------------------------------------

int      effectSpeed = D_EFFECT_SPEED;   // скрость изменения эффекта (по умолчанию)
byte     effectScaleParam[MAX_EFFECT];   // Динамический параметр эффекта, параметр #1
byte     effectScaleParam2[MAX_EFFECT];  // Динамический параметр эффекта, параметр #2
byte     effectContrast[MAX_EFFECT];     // Динамический параметр эффекта - контрастность (яркость эффекта относительно яркости часов или текста бегущей строки)
bool     manualMode = false;             // флаг: true - ручное управление эффектами; false - в режиме Autoplay
bool     loadingFlag = true;             // флаг: инициализация параметров эффекта

// ---------------------------------------------------------------

uint32_t idleTime = ((long)IDLE_TIME * 60 * 1000L);     // минуты -> миллисек
uint32_t autoplayTime = ((long)AUTOPLAY_PERIOD * 1000L);// секунды -> миллисек
bool     idleState = true;                              // флаг холостого режима работы
uint32_t autoplayTimer;                                 // время до автоматического перехода в демо-режим

// ---------------------------------------------------------------

int8_t   thisMode = 0;                    // текущий режим

// ---------------------------------------------------------------

#define  GLOBAL_COLOR_1 CRGB::Green       // основной цвет №1 для игр
#define  GLOBAL_COLOR_2 CRGB::Orange      // основной цвет №2 для игр
#define  SCORE_SIZE 1                     // размер символов счёта в игре. 0 - маленький для 8х8 (шрифт 3х5), 1 - большой (шрифт 5х7)

boolean  gameDemo = true;                 // Игры Тетрис, Лабиринт, Змейка работают в демо-режиме
boolean  gamePaused = false;              // Игра на паузе (при ручном управлении игрой) 
byte     buttons;                         // Эмуляция кнопок управления играми в демо-режиме

// ---------------------------------------------------------------
timerMinim ntpSyncTimer(1000 * 60 * SYNC_TIME_PERIOD); // Сверяем время с NTP-сервером через SYNC_TIME_PERIOD минут
timerMinim effectTimer(D_EFFECT_SPEED);  // Таймер скорости эффекта (шага выполнения эффекта)
timerMinim clockTimer(D_CLOCK_SPEED);    // Таймер смещения оверлея часов
timerMinim textTimer(D_TEXT_SPEED);      // Таймер смещения оверлея часов
timerMinim changeTimer(70);              // Таймер шага плавной смены режима - Fade
timerMinim halfsecTimer(500);            // Полусекундный таймер точек часов
timerMinim idleTimer(idleTime);          // Таймер бездействия ручного управлениядля автоперехода а демо-режим 
timerMinim dawnTimer(1000);              // Таймер шага рассвета для будильника "рассвет" 
timerMinim alarmSoundTimer(4294967295);  // Таймер выключения звука будильника
timerMinim fadeSoundTimer(4294967295);   // Таймер плавного включения / выключения звука
timerMinim saveSettingsTimer(15000);     // Таймер отложенного сохранения настроек

// ********************* ДЛЯ ПАРСЕРА КОМАНДНЫХ ПАКЕТОВ *************************

#define    BUF_MAX_SIZE  1024            // максимальный размер выделяемого буфера для коммуникации по UDP каналу
#define    PARSE_AMOUNT 14               // максимальное количество значений в массиве, который хотим получить
#define    header '$'                    // стартовый символ управляющей посылки
#define    divider ' '                   // разделительный символ
#define    ending ';'                    // завершающий символ
 
int16_t    intData[PARSE_AMOUNT];        // массив численных значений после парсинга - для WiFi часы время синхр м.б отрицательным + 
                                         // период синхронизации м.б больше 255 мин - нужен тип int16_t
char       incomeBuffer[BUF_MAX_SIZE];   // Буфер для приема строки команды из wifi udp сокетаж также используется для загрузки строк из EEPROM
char       replyBuffer[8];               // ответ клиенту - подтверждения получения команды: "ack;/r/n/0"

byte       ackCounter = 0;               // счетчик отправляемых ответов для создания уникальности номера ответа

// --------------- ВРЕМЕННЫЕ ПЕРЕМЕННЫЕ ПАРСЕРА ------------------

uint32_t   prevColor;
boolean    recievedFlag;
boolean    parseStarted;
byte       parse_index;
String     string_convert = "";
String     receiveText = "";
bool       haveIncomeData = false;
char       incomingByte;

int16_t    bufIdx = 0;                   // Могут приниматься пакеты > 255 байт - тип int16_t
int16_t    packetSize = 0;

enum       eModes {NORMAL, COLOR, TEXT} parseMode;


// ************************* УПРАВЛЕНИЕ МАТРИЦЕЙ *******************************

#define    NUM_LEDS            WIDTH * HEIGHT * SEGMENTS
#define    maxDim              max(WIDTH, HEIGHT)
#define    OVERLAY_SIZE        WIDTH * 11 * SEGMENTS

CRGBArray<NUM_LEDS> leds;                 // обращение к светодиодам матрицы через этот массив
CRGBArray<OVERLAY_SIZE> overlayLEDs;      // буфер оверлея; по максимуму - для бегущей строки во всю ширину матрицы или отображение календаря / вертикальных часов - 11 высота

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

// ------------------- ВРЕМЕННЫЕ ПЕРЕМЕННЫЕ ----------------------

bool       saveSpecialMode = specialMode;
int8_t     saveSpecialModeId = specialModeId;
byte       saveMode;
byte       tmpSaveMode = 0;

// ---------------------------------------------------------------
