// ПРИМЕР ОТПРАВКИ ИНФОРМАЦИИ О ЗНАКАХ:                    // * Строки со звёздочкой являются необязательными.
// - Пример "SignSend" использует функцию: irSend();       //   Однократно отправить информацию о знаке по ИК-каналу.
// - Остальные примеры используют функцию: irAutoSend();   //   Постоянно отправлять информацию о знаке по ИК-каналу.
                                                           //
// Светофор:                                               //   https://iarduino.ru/shop/Expansion-payments/svetofor.html
// Шлагбаум для светофора:                                 //   https://iarduino.ru/shop/Expansion-payments/shlagbaum-dlya-svetofora.html
// Знаки и модули дорожного движения "Роботраффик"         //   https://iarduino.ru/shop/Expansion-payments/road-traffic/
// Информация о подключении модулей к шине I2C:            //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о светофоре, шлагбауме и описание библиотеки://   https://wiki.iarduino.ru/page/traffic-light/
// Информация о дорожных знаках и описание библиотеки:     //   https://wiki.iarduino.ru/page/road-sign/
                                                           //
#include <Wire.h>                                          //   Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_I2C_Track.
#include <iarduino_I2C_Track.h>                            //   Подключаем библиотеку для работы с модулями трассы I2C-flash.
iarduino_I2C_Track sign_1(0x10);                           //   Объявляем объект sign_1 для работы с функциями и методами библиотеки iarduino_I2C_Track, указывая адрес модуля на шине I2C.
iarduino_I2C_Track sign_2(0x11);                           //   Объявляем объект sign_2 для работы с функциями и методами библиотеки iarduino_I2C_Track, указывая адрес модуля на шине I2C.
iarduino_I2C_Track sign_3(0x12);                           //   Объявляем объект sign_3 для работы с функциями и методами библиотеки iarduino_I2C_Track, указывая адрес модуля на шине I2C.
                                                           //   Количество объектов ограничено количеством имеющихся модулей и свободной динамической памятью.
void setup(){                                              //
     delay(500);                                           // * Ждём завершение переходных процессов связанных с подачей питания.
     sign_1.begin(&Wire,  MODUL_SIGN, 2,1   );             //   Инициируем работу с модулем. Указываем что модуль находится на шине Wire , является знаком 2.1 ПДД «Главная дорога».
     sign_2.begin(&Wire,  MODUL_SIGN, 2,4   );             //   Инициируем работу с модулем. Указываем что модуль находится на шине Wire , является знаком 2.4 ПДД «Уступите дорогу».
     sign_3.begin(&Wire,  MODUL_SIGN, 2,3,1 );             //   Инициируем работу с модулем. Указываем что модуль находится на шине Wire , является знаком 2.3.1 ПДД «Пересечение со второстепенной дорогой».
//   sign_1.begin(&Wire1, MODUL_SIGN, 2,1   );             //   Инициируем работу с модулем. Указываем что модуль находится на шине Wire1, является знаком 2.1 ПДД «Главная дорога».
//   sign_2.begin(&Wire2, MODUL_SIGN, 2,4   );             //   Инициируем работу с модулем. Указываем что модуль находится на шине Wire2, является знаком 2.4 ПДД «Уступите дорогу».
//   sign_3.begin(        MODUL_SIGN, 1,23  );             //   Инициируем работу с модулем. Не указываем шину (по умолчанию Wire), модуль является знаком 1.23 ПДД "Дети".
     sign_1.irProtocol(IR_IARDUINO);                       // * Указываем протокол передачи данных по ИК-каналу: "IARDUINO".
     sign_2.irProtocol(IR_IARDUINO);                       // * Указываем протокол передачи данных по ИК-каналу: "IARDUINO".
     sign_3.irProtocol(IR_IARDUINO);                       // * Указываем протокол передачи данных по ИК-каналу: "IARDUINO".
     sign_1.indicator(false);                              // * Запрещаем работу светодиода 1 модуля, информирующего об отправке данных.
     sign_2.indicator(false);                              // * Запрещаем работу светодиода 2 модуля, информирующего об отправке данных.
     sign_3.indicator(false);                              // * Запрещаем работу светодиода 3 модуля, информирующего об отправке данных.
     sign_1.irAutoSend();                                  //   Указываем 1 модулю постоянно отправлять информацию о знаке по ИК-каналу с паузой между пакетами определённой ИК протоколом по умолчанию ±50%.
     sign_2.irAutoSend();                                  //   Указываем 2 модулю постоянно отправлять информацию о знаке по ИК-каналу с паузой между пакетами определённой ИК протоколом по умолчанию ±50%.
     sign_3.irAutoSend();                                  //   Указываем 3 модулю постоянно отправлять информацию о знаке по ИК-каналу с паузой между пакетами определённой ИК протоколом по умолчанию ±50%.
     sign_1.backlight(2);                                  // * Указываем автоматически мигать всеми светодиодами подсветки 1 знака.
     sign_2.backlight(1);                                  // * Включаем  все светодиоды подсветки 2 знака.
     sign_3.backlight(0);                                  // * Отключаем все светодиоды подсветки 3 знака.
}                                                          //
                                                           //
void loop(){                                               //
     sign_3.backlight(1);                                  //   Включаем  все светодиоды подсветки 3 знака.
     delay(100);                                           //
     sign_3.backlight(0);                                  //   Отключаем все светодиоды подсветки 3 знака.
     delay(100);                                           //
}                                                          //