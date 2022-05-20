20.05.2022
Добавлены 2 класса: Server и http_request

Server:
- атрибуты:
int port - для хранения порта подключения к серверу
int server_socket - для хранения fd сокета клиента

std::string html_data - строка для хранения данных запроса
std::string start_date_time - время работы сервера
size_t get_request_count - счетчик количества запросов
std::vector<char> fav_icon_buffer - переменная для хранения иконки (может уберем, это просто "бантик")

- методы:
bool socketInit() - для инициации сокета
void clientProcessing(int, std::string) - для обработки клиентского подключения
bool serverStart() - стартуем работу сервера


http_request:
- атрибуты:
enumType m_type {enumType::Unknown} - имена запросов (переделаю под #define)
std::string m_url - хранение информации о том, что в поступившем запросе стоит после имени запроса (корень)

- методы:
void parserHttp(const char*) - парсинг HTTP запроса (метод для проверки работы с запросами, заменим на мтод тиммета)
const enumType &type() const - получение типа запроса (будет изменен)
const std::string &url() const - получение корня после имени запроса (будет изменен)
void parserForRequest(std::string &) - парсинг ответа от сервера