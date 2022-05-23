20.05.2022 Добавлены 2 класса: Server и http_request

Server:

- атрибуты:
  int port - для хранения порта подключения к серверу int server_socket - для хранения fd сокета клиента

std::string html_data - строка для хранения данных запроса std::string start_date_time - время работы сервера size_t
get_request_count - счетчик количества запросов std::vector<char> fav_icon_buffer - переменная для хранения иконки (
может уберем, это просто "бантик")

- методы:
  bool socketInit() - для инициации сокета void clientProcessing(int, std::string) - для обработки клиентского
  подключения bool serverStart() - стартуем работу сервера

http_request:

- атрибуты:
  s_enumType m_type - имена запросов std::string m_url - хранение информации о том, что в поступившем запросе стоит
  после имени запроса (корень)

- методы:
  void parserHttp(const char*) - парсинг HTTP запроса (метод для проверки работы с запросами, заменим на метод тиммейта)
  const s_enumType &type() const - получение типа запроса const std::string &url() const - получение корня после имени
  запроса void parserForRequest(std::string &) - парсинг ответа от сервера

23.05.2022 Подкорректирован метод clientProcessing(int, std::string): при запуске сервера в браузере на указанном порту
отображается содержимое страницы index.html

Иконку для страницы пока не получилось сделать, но по адресу "/favicon.ico" в браузере открывается картинка (если будет
время - поковыряю как сделать чтобы у станицы отображалась иконка)

23.05.2022 Добавлены изменения в clientProcessing(int, std::string):

- при преходе в браузере на localhost:<port>/request - отображается дата и время запуска сервера и количество запросов
  сделанных к серверу с даты запуска
- при преходе в браузере на localhost:<port> - отображается стартовая страница "index.html"

![Image text](main_part/screenshot.png)

![Image text](main_part/screenshot2.png)
