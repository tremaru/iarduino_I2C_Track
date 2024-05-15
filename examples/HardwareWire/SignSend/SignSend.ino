// ПРИМЕР ОТПРАВКИ ИНФОРМАЦИИ О ЗНАКЕ:                     // * Строки со звёздочкой являются необязательными.
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
iarduino_I2C_Track sign(0x09);                             //   Объявляем объект sign для работы с функциями и методами библиотеки iarduino_I2C_Track, указывая адрес модуля на шине I2C.
                                                           //   Если объявить объект без указания адреса (iarduino_I2C_Track sign;), то адрес будет найден автоматически.
void setup(){                                              //
     delay(500);                                           // * Ждём завершение переходных процессов связанных с подачей питания.
     sign.begin(&Wire , MODUL_SIGN, 2,4    );              //   Инициируем работу с модулем. Указываем что модуль находится на шине Wire , является знаком 2.4 ПДД "Уступите дорогу".
//   sign.begin(&Wire1, MODUL_SIGN, 6,8,2  );              //   Инициируем работу с модулем. Указываем что модуль находится на шине Wire1, является знаком 6.8.2 ПДД "Тупик" (справа).
//   sign.begin(&Wire2, MODUL_SIGN, 3,24, 5);              //   Инициируем работу с модулем. Указываем что модуль находится на шине Wire2, является знаком 3.24 ПДД "Ограничение максимальной скорости", последняя цифра (0-15) указывает скорость (5 = 50км/ч).
//   sign.begin(        MODUL_SIGN, 1,23  );               //   Инициируем работу с модулем. Не указываем шину (по умолчанию Wire), модуль является знаком 1.23 ПДД "Дети".
     sign.irProtocol(IR_IARDUINO);                         // * Указываем протокол передачи данных по ИК-каналу: "IARDUINO".
     sign.backlight(true);                                 // * Включаем подсветку знака.
     sign.indicator(true);                                 // * Разрешаем работу светодиода информирующего об отправке данных.
}                                                          //
                                                           //
void loop(){                                               //
     sign.irSend();                                        //   Выполняем отправку одного пакета данных по ИК-каналу. В одном пакете есть вся информация о знаке.
//   sign.irWait();                                        // * Ждём  завершения отправки пакета данных по ИК-каналу. Отправка одного пакета данных в кодировке IARDUINO занимает 26,5 мс.
     delay(200);                                           //   Ждём 200 мс.
}                                                          //