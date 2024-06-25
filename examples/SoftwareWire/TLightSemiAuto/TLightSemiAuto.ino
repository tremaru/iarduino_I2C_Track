// ПРИМЕР РАБОТЫ СВЕТОФОРА В ПОЛУАВТОМАТИЧЕСКОМ РЕЖИМЕ:             // * Строки со звёздочкой являются необязательными.
// Требуется установить библиотеку <iarduino_I2C_Software.h>        //   https://iarduino.ru/file/627.html
                                                                    //
// Если функция set() вызвана с параметром(ами) управления секциями //
// TL_RED, TL_YELLOW, TL_GREEN, TL_RIGHT, TL_LEFT, TL_BEEP, TL_GATE //   красный, жёлтый, зелёный, правый поворот, левый поворот, звук, шлагбаум.
// после которых указано число 0,1,2, такой режим является ручным.  //   0-выключить (поднять), 1-включить (опустить), 2-мигать.
// Если функция set() вызвана с параметром(ми) указания направления //
// TL_FORWARD_ON/OFF, TL_LEFT_ON/OFF, TL_RIGHT_ON/OFF, то такой     //   прямое направление, левый поворот, правый поворот.
// режим управления светофором называется полуавтоматическим.       //
                                                                    //
// Светофор:                                                        //   https://iarduino.ru/shop/Expansion-payments/svetofor.html
// Шлагбаум для светофора:                                          //   https://iarduino.ru/shop/Expansion-payments/shlagbaum-dlya-svetofora.html
// Знаки и модули дорожного движения "Роботраффик"                  //   https://iarduino.ru/shop/Expansion-payments/road-traffic/
// Информация о подключении модулей к шине I2C:                     //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о светофоре, шлагбауме и описание библиотеки:         //   https://wiki.iarduino.ru/page/traffic-light/
// Информация о дорожных знаках и описание библиотеки:              //   https://wiki.iarduino.ru/page/road-sign/
                                                                    //
#include <iarduino_I2C_Software.h>                                  //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_I2C_Track.
SoftTwoWire sWire(3,4);                                             //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                                    //
#include <iarduino_I2C_Track.h>                                     //   Подключаем библиотеку для работы с модулями трассы I2C-flash.
iarduino_I2C_Track tlight(0x09);                                    //   Объявляем объект tlight для работы с функциями и методами библиотеки iarduino_I2C_Track, указывая адрес модуля на шине I2C.
                                                                    //   Если объявить объект без указания адреса (iarduino_I2C_Track tlight;), то адрес будет найден автоматически.
void setup(){                                                       //
     delay(500);                                                    // * Ждём завершение переходных процессов связанных с подачей питания.
     tlight.begin(&sWire, MODUL_TLIGHT, TRACK_FLR, SECTION_LR);     //   Инициируем работу с модулем. Указываем ссылку на объект для работы с шиной I2C, модуль является светофором, дорога прямо налево и направо, с двумя секциями поворотов.
//   tlight.begin(&sWire, MODUL_TLIGHT, TRACK_FRL, SECTION_RL);     //   Инициируем работу с модулем. Указываем ссылку на объект для работы с шиной I2C, модуль является светофором, дорога прямо налево и направо, с двумя секциями поворотов.
//   tlight.begin(&sWire, MODUL_TLIGHT, TRACK_RLF, SECTION_LRG);    //   Инициируем работу с модулем. Указываем ссылку на объект для работы с шиной I2C, модуль является светофором, дорога прямо налево и направо, с двумя секциями поворотов и шлагбаумом.
     tlight.timing(3);                                              //   Указываем время свечения жёлтого и мигающего зелёного (3сек).
     tlight.irProtocol(IR_IARDUINO);                                // * Указываем протокол передачи данных по ИК-каналу: "IARDUINO".
     tlight.indicator(true);                                        // * Разрешаем работу светодиода информирующего об отправке данных.
     tlight.irAutoSend();                                           //   Указываем модулю постоянно отправлять информацию о состоянии светофора по ИК-каналу с паузой между пакетами определённой ИК протоколом по умолчанию ±50%.
     tlight.set(TL_ALL, false);                                     //   Отключаем все секции светофора.
}                                                                   //
                                                                    //
void loop(){                                                        //
     tlight.set(TL_FORWARD_ON);                delay( 5000);        // Разрешаем движение в прямом направлении.
     tlight.set(TL_RIGHT_ON);                  delay( 5000);        // Разрешаем движение направо.
     tlight.set(TL_FORWARD_OFF, TL_RIGHT_OFF); delay(10000);        // Запрещаем движение в прямом направлении и направо.
     tlight.set(TL_LEFT_ON);                   delay( 5000);        // Разрешаем движение налево.
     tlight.set(TL_LEFT_OFF);                  delay( 5000);        // Запрещаем движение налево.
     tlight.set(TL_FORWARD_ON);                delay( 5000);        // Разрешаем движение в прямом направлении.
}                                                                   //