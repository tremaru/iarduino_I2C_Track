// ПРИМЕР СМЕНЫ АДРЕСА МОДУЛЯ:                               // * Строки со звёздочкой являются необязательными.
// Требуется установить библиотеку <iarduino_I2C_Software.h> //   https://iarduino.ru/file/627.html
                                                             //
// Светофор:                                                 //   https://iarduino.ru/shop/Expansion-payments/svetofor.html
// Шлагбаум для светофора:                                   //   https://iarduino.ru/shop/Expansion-payments/shlagbaum-dlya-svetofora.html
// Знаки и модули дорожного движения "Роботраффик"           //   https://iarduino.ru/shop/Expansion-payments/road-traffic/
// Информация о подключении модулей к шине I2C:              //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о светофоре, шлагбауме и описание библиотеки:  //   https://wiki.iarduino.ru/page/traffic-light/
// Информация о дорожных знаках и описание библиотеки:       //   https://wiki.iarduino.ru/page/road-sign/
                                                             //
// Данный скетч демонстрирует не только                      //
// возможность смены адреса на указанный в                   //
// переменной newAddress, но и обнаружение,                  //
// и вывод текущего адреса модуля на шине I2C.               //
                                                             //
// Библиотека <iarduino_I2C_Track.h>                         //
// предназначена для работы с модулями трассы                //
// серии I2C-flash и меняет только их адреса.                //
// Но, в разделе Файл/Примеры/.../findSortDevices            //
// находятся примеры смены и сортировки адресов              //
// любых модулей iarduino серии Flash I2C.                   //
                                                             //
uint8_t newAddress = 0x09;                                   //   Назначаемый модулю адрес (0x07 < адрес < 0x7F).
                                                             //
#include <iarduino_I2C_Software.h>                           //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_I2C_Track.
SoftTwoWire sWire(3,4);                                      //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                             //
#include <iarduino_I2C_Track.h>                              //   Подключаем библиотеку для работы с модулями трассы I2C-flash.
iarduino_I2C_Track sign;                                     //   Объявляем объект sign для работы с функциями и методами библиотеки iarduino_I2C_Track.
                                                             //   Если при объявлении объекта указать адрес, например, iarduino_I2C_Track sign(0xBB), то пример будет работать с тем модулем, адрес которого был указан.
void setup(){                                                //
    delay(500);                                              // * Ждём завершение переходных процессов связанных с подачей питания.
    Serial.begin(9600);                                      //
    while(!Serial){;}                                        // * Ждём завершения инициализации шины UART.
    if( sign.begin(&sWire) ){                                //   Инициируем работу с модулем, указав ссылку на объект для работы с шиной I2C на которой находится модуль (Wire, Wire1, Wire2 ...).
        Serial.print("Найден модуль 0x");                    //
        Serial.println( sign.getAddress(), HEX );            //   Выводим текущий адрес модуля.
        if( sign.changeAddress(newAddress) ){                //   Меняем адрес модуля на newAddress.
            Serial.print("Адрес изменён на 0x");             //
            Serial.println(sign.getAddress(), HEX);          //   Выводим текущий адрес модуля.
        }else{                                               //
            Serial.println("Адрес не изменён!");             //
        }                                                    //
    }else{                                                   //
        Serial.println("Модуль не найден!");                 //
    }                                                        //
}                                                            //
                                                             //
void loop(){                                                 //
}                                                            //
