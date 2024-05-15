// ПРИМЕР АВТОНОМНОЙ РАБОТЫ СВЕТОФОРА:                                // * Строки со звёздочкой являются необязательными.
// После загрузки скетча, светофор будет работать без Arduino.        //
//                                                                    //
// Светофор:                                                          //   https://iarduino.ru/shop/Expansion-payments/svetofor.html
// Шлагбаум для светофора:                                            //   https://iarduino.ru/shop/Expansion-payments/shlagbaum-dlya-svetofora.html
// Знаки и модули дорожного движения "Роботраффик"                    //   https://iarduino.ru/shop/Expansion-payments/road-traffic/
// Информация о подключении модулей к шине I2C:                       //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о светофоре, шлагбауме и описание библиотеки:           //   https://wiki.iarduino.ru/page/traffic-light/
// Информация о дорожных знаках и описание библиотеки:                //   https://wiki.iarduino.ru/page/road-sign/
                                                                      //
#include <Wire.h>                                                     //   Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_I2C_Track.
#include <iarduino_I2C_Track.h>                                       //   Подключаем библиотеку для работы с модулями трассы I2C-flash.
iarduino_I2C_Track tlight(0x09);                                      //   Объявляем объект tlight для работы с функциями и методами библиотеки iarduino_I2C_Track, указывая адрес модуля на шине I2C.
                                                                      //   Если объявить объект без указания адреса (iarduino_I2C_Track tlight;), то адрес будет найден автоматически.
void setup(){                                                         //
     delay(500);                                                      // * Ждём завершение переходных процессов связанных с подачей питания.
     tlight.begin(&Wire , MODUL_TLIGHT_AUTO, TRACK_F               ); //   Инициируем работу с модулем. Указываем что модуль находится на шине Wire , является автоматическим светофором, дорога только прямо, без секций поворотов.
//   tlight.begin(&Wire1, MODUL_TLIGHT_AUTO, TRACK_FR,  SECTION_R  ); //   Инициируем работу с модулем. Указываем что модуль находится на шине Wire1, является автоматическим светофором, дорога прямо и направо, с секцией поворота направо.
//   tlight.begin(&Wire2, MODUL_TLIGHT_AUTO, TRACK_FLR, SECTION_LR ); //   Инициируем работу с модулем. Указываем что модуль находится на шине Wire2, является автоматическим светофором, дорога прямо налево и направо, с двумя секциями поворотов.
//   tlight.begin(        MODUL_TLIGHT_AUTO, TRACK_FRL, SECTION_LRG); //   Инициируем работу с модулем. Не указываем шину (по умолчанию Wire), модуль является автоматическим светофором, дорога прямо налево и направо, с двумя секциями поворотов и шлагбаумом.
     tlight.timing(5, 3, 10);                                         // * Указываем время свечения зелёного (5сек), жёлтого или мигающего зелёного (3сек) и красного (10сек) цветов для автоматического светофора.
     tlight.irProtocol(IR_IARDUINO);                                  // * Указываем протокол передачи данных по ИК-каналу: "IARDUINO".
     tlight.indicator(true);                                          // * Разрешаем работу светодиода информирующего об отправке данных.
     tlight.irAutoSend();                                             //   Указываем модулю постоянно отправлять информацию о состоянии светофора по ИК-каналу с паузой между пакетами определённой ИК протоколом по умолчанию ±50%.
//   tlight.irAutoSend(100);                                          //   Указываем модулю постоянно отправлять информацию о состоянии светофора по ИК-каналу с паузой между пакетами в 100 мс ±50%.
     tlight.offline(true);                                            //   Указываем модулю сохранить все полученные настройки в энергонезависимую память и работать в автономном режиме.
}                                                                     //   В автономном режиме модуль начинает работать сразу после подачи питания, без получения команд от Arduino.
                                                                      //   Отключить автономный режим можно функцией offline() с параметром false.
void loop(){}                                                         //