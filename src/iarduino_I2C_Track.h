//	Библиотека для работы с дорожными знаками и светофором из линейки «дорожное движение», I2C-flash для Arduino: https://iarduino.ru/shop/Expansion-payments/road-traffic/
//  Версия: 1.0.1
//  Последнюю версию библиотеки Вы можете скачать по ссылке: https://iarduino.ru/file/546.html
//  Подробное описание функций бибилиотеки доступно по ссылкам: https://wiki.iarduino.ru/page/road-sign/ или https://wiki.iarduino.ru/page/traffic-light/
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел.
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_I2C_Track_h																					//
#define iarduino_I2C_Track_h																					//
																												//
#if defined(ARDUINO) && (ARDUINO >= 100)																		//
#include		<Arduino.h>																						//
#else																											//
#include		<WProgram.h>																					//
#endif																											//
																												//
#include		<iarduino_I2C_Track_I2C.h>																		//	Подключаем файл iarduino_I2C_Track_I2C.h - для работы с шиной I2C		(используя функции структуры iI2C)
																												//
#define			DEF_CHIP_ID_FLASH		0x3C																	//	ID линейки чипов - константа для всех чипов серии Flash (позволяет идентифицировать принадлежность чипа к серии).
#define			DEF_CHIP_ID_METRO		0xC3																	//	ID линейки чипов - константа для всех чипов серии Metro (позволяет идентифицировать принадлежность чипа к серии).
#define			DEF_MODEL_IR0			0x17																	//	Идентификатор модели - константа.
#define			DEF_MODEL_IR1			0x18																	//	Идентификатор модели - константа.
//				Адреса регистров модуля:																		//
#define			REG_FLAGS_0				0x00																	//	Адрес регистра флагов управления для чтения.
#define			REG_BITS_0				0x01																	//	Адрес регистра битов  управления для чтения и записи.
#define			REG_FLAGS_1				0x02																	//	Адрес регистра флагов управления для чтения.
#define			REG_BITS_1				0x03																	//	Адрес регистра битов  управления для чтения и записи.
#define			REG_MODEL				0x04																	//	Адрес регистра содержащего номер типа модуля.
#define			REG_VERSION				0x05																	//	Адрес регистра содержащего версию прошивки.
#define			REG_ADDRESS				0x06																	//	Адрес регистра содержащего текущий адрес модуля на шине I2C. Если адрес указан с флагом IF-PIN-ADDRES то адрес установится (и запишется в регистр) только при наличии 1 на входе PIN_ADDRES.
#define			REG_CHIP_ID				0x07																	//	Адрес регистра содержащего ID линейки чипов «Flash». По данному ID можно определить принадлежность чипа к линейки «Flash».
#define			REG_IR1_SEND_RPT		0x10																	//	Адрес регистра содержащего минимальное время между отправляемыми пакетами повторов в мс * 2 (значение 1=2мс, 2=4мс, ... , 127=254мс, значение 0 указывает использовать интервал протокола по умолчанию). Последний бит регистра указывает передавать пакеты повтора, пока этот бит не будет сброшен.
#define			REG_IR1_SEND_ADR		0x11																	//	Адрес регистра содержащего байт адреса  устройства для передачи по ИК-каналу.
#define			REG_IR1_SEND_COM		0x12																	//	Адрес регистра содержащего байт команды устройству для передачи по ИК-каналу.
#define			REG_IR1_SEND_COD		0x13																	//	Адрес регистра содержащего номер протокола используемого для передачи данных по ИК-каналу.
#define			REG_IR1_BIT				0x18																	//	Адрес регистра содержащего биты управления ИК-каналом.
#define			REG_IR1_BLINK			0x19																	//	Адрес регистра позволяющего мигать выводом двухрядной колодки, если на нём установлен активный логический уровень.
#define			REG_IR1_DIGITAL			0x1A																	//	Адрес регистра позволяющего установить логические уровни выводов на двухрядной колодке.
#define			REG_IR1_BLINK_ON		0x1B																	//	Адрес регистра позволяющего установить мигание вывода двухрядной колодки, если на нём установлен активный логический уровень: 0-игнорировать; 1-установить.
#define			REG_IR1_BLINK_OFF		0x1C																	//	Адрес регистра позволяющего сбросить   мигание вывода двухрядной колодки, если на нём установлен активный логический уровень: 0-игнорировать; 1-сбросить.
#define			REG_IR1_DIGITAL_ON		0x1D																	//	Адрес регистра позволяющего установить активный логический уровень: 0-игнорировать; 1-установить.
#define			REG_IR1_DIGITAL_OFF		0x1E																	//	Адрес регистра позволяющего сбросить активный логический уровень: 0-игнорировать; 1-сбросить.
#define			REG_IR1_TL_BIT			0x1F																	//	Адрес регистра содержащего биты управления модулем в автоматическом/полуавтоматическом режиме светофора.
#define			REG_IR1_TL_YEL_SEC		0x20																	//	Адрес регистра содержащего длительность свечения жёлтого  сигнала и мигающего зелёного в сек., при работе модуля в автоматическом (IR1_BIT_TL_AUTOJOB=1) или полуавтоматическом режиме светофора (IR1_BIT_TL_UP/LT/RT).
#define			REG_IR1_TL_GRN_SEC		0x21																	//	Адрес регистра содержащего длительность свечения зелёного сигнала в сек., при работе модуля в автоматическом режиме светофора (IR1_BIT_TL_AUTOJOB=1).
#define			REG_IR1_TL_RED_SEC		0x22																	//	Адрес регистра содержащего длительность свечения красного сигнала в сек., при работе модуля в автоматическом режиме светофора (IR1_BIT_TL_AUTOJOB=1).
#define			REG_IR1_SERVO_MCS_L		0x23																	//	Адрес регистра содержащего длительность импульсов ШИМ сервопривода в мкс  (мл. байт).
#define			REG_IR1_SERVO_MCS_H		0x24																	//	Адрес регистра содержащего длительность импульсов ШИМ сервопривода в мкс  (ст. байт).
#define			REG_IR1_GATE_SPEED		0x25																	//	Адрес регистра содержащего скорость открывания/закрывания шлагбаума       (от 0 до 255). Байт хранится в flash памяти модуля.
#define			REG_IR1_GATE_OPEN_L		0x26																	//	Адрес регистра содержащего ширину импульса в мкс, для открытого шлагбаума (ст. байт).    Байт хранится в flash памяти модуля.
#define			REG_IR1_GATE_OPEN_H		0x27																	//	Адрес регистра содержащего ширину импульса в мкс, для открытого шлагбаума (ст. байт).    Байт хранится в flash памяти модуля.
#define			REG_IR1_GATE_CLOSE_L	0x28																	//	Адрес регистра содержащего ширину импульса в мкс, для закрытого шлагбаума (мл. байт).    Байт хранится в flash памяти модуля.
#define			REG_IR1_GATE_CLOSE_H	0x29																	//	Адрес регистра содержащего ширину импульса в мкс, для закрытого шлагбаума (ст. байт).    Байт хранится в flash памяти модуля.
//				Позиция битов и флагов:																			//
#define			IR1_BIT_REPEAT			0x01																	//	Бит  регистра REG_IR1_SEND_RPT   указывает модулю отправлять пакеты повтора после отправки любого пакета, до тех пор, пока бит не будет сброшен.
#define			IR1_NUM_CODING			0x1F																	//	Биты регистра REG_IR1_SEND_COD   хранят номер используемого протокола для передачи данных.
#define			IR1_RC6_MODE			0xE0																	//	Биты регистра REG_IR1_SEND_COD   хранят номер режима используемого протоколом RC-6 для передачи данных.
#define			IR1_BIT_AVTO_LOAD		0x80																	//	Бит  регистра REG_IR1_BIT        указывает модулю загружать значения регистров 0x10-0x22 из flash памяти. Значение бита сохраняется в flash память.
#define			IR1_BIT_SAVE_ALL		0x40																	//	Бит  регистра REG_IR1_BIT        указывает модулю сохранить значений регистров 0x10-0x22 в  flash память. Бит сбрасывается автоматически. Зти значения будут загружаться в регистры при подаче питания, если установлен бит IR1_BIT_AVTO_LOAD.
#define			IR1_BIT_TX_BUSY			0x20																	//	Бит  регистра REG_IR1_BIT        информирует о занятости ИК-передатчика.
#define			IR1_BIT_TX_LED			0x10																	//	Бит  регистра REG_IR1_BIT        разрешает работу светодиода информирующего о передаче данных по ИК-каналу.
#define			IR1_BIT_TX_SHIFT		0x08																	//	Бит  регистра REG_IR1_BIT        указывает модулю самостоятельно и хаотично менять интервал между отправляемыми пакетами повторов в диапазоне ±50% от заданного.
#define			IR1_BIT_TX_EN			0x01																	//	Бит  регистра REG_IR1_BIT        разрешает работу ИК-передатчика.
#define			IR1_BIT_TL_RT			0x80																	//	Бит  регистра REG_IR1_DIGITAL    позволяет управлять сигналом правого поворота светофора.
#define			IR1_BIT_GATE			0x40																	//	Бит  регистра REG_IR1_DIGITAL    позволяет использовать цифровое управление шлагбаумом (1-закрыть 0-открыть).
#define			IR1_BIT_TL_RED			0x20																	//	Бит  регистра REG_IR1_DIGITAL    позволяет управлять сигналом красного цвета светофора.
#define			IR1_BIT_TL_YEL			0x08																	//	Бит  регистра REG_IR1_DIGITAL    позволяет управлять сигналом жёлтого цвета светофора.
#define			IR1_BIT_TL_BEP			0x04																	//	Бит  регистра REG_IR1_DIGITAL    позволяет управлять звуковым сигналом светофора.
#define			IR1_BIT_TL_LT			0x02																	//	Бит  регистра REG_IR1_DIGITAL    позволяет управлять сигналом левого поворота светофора.
#define			IR1_BIT_TL_GRN			0x01																	//	Бит  регистра REG_IR1_DIGITAL    позволяет управлять сигналом зелёного цвета светофора.
#define			IR1_BIT_TL_AUTOJOB		0x80																	//	Бит  регистра REG_IR1_BIT_TL     указывает модулю работать в режиме автоматически переключающегося светофора.
#define			IR1_BIT_TL_AUTOCOM		0x40																	//	Бит  регистра REG_IR1_BIT_TL     указывает модулю автоматически менять значение регистра REG_IR1_SEND_COM в соответствии с текущими цветами светофора. Состояние бита автоматически сохраняется и в бит IR1_BIT_REPEAT для запуска/остановки отправки пакетов повторов по ИК-каналу.
#define			IR1_BIT_TL_UP_ON		0x20																	//	Бит  регистра REG_IR1_BIT_TL     полуавтоматического переключения. Установка бита приведёт к последовательному переключению светофора на зелёный сигнал.  Бит сбрасывается автоматически по завершении переключения.
#define			IR1_BIT_TL_UP_OFF		0x10																	//	Бит  регистра REG_IR1_BIT_TL     полуавтоматического переключения. Установка бита приведёт к последовательному переключению светофора на красный сигнал.  Бит сбрасывается автоматически по завершении переключения.
#define			IR1_BIT_TL_LT_ON		0x08																	//	Бит  регистра REG_IR1_BIT_TL     полуавтоматического переключения. Установка бита приведёт к последовательному переключению левой  стрелки на включение.  Бит сбрасывается автоматически по завершении переключения.
#define			IR1_BIT_TL_LT_OFF		0x04																	//	Бит  регистра REG_IR1_BIT_TL     полуавтоматического переключения. Установка бита приведёт к последовательному переключению левой  стрелки на отключение. Бит сбрасывается автоматически по завершении переключения.
#define			IR1_BIT_TL_RT_ON		0x02																	//	Бит  регистра REG_IR1_BIT_TL     полуавтоматического переключения. Установка бита приведёт к последовательному переключению правой стрелки на включение.  Бит сбрасывается автоматически по завершении переключения.
#define			IR1_BIT_TL_RT_OFF		0x01																	//	Бит  регистра REG_IR1_BIT_TL     полуавтоматического переключения. Установка бита приведёт к последовательному переключению правой стрелки на отключение. Бит сбрасывается автоматически по завершении переключения.
#define			IR1_BIT_TL_LT_EN		0x80																	//	Бит  регистра REG_IR1_TL_YEL_SEC указывает о наличии левой секции поворота. 
#define			IR1_BIT_TL_RT_EN		0x80																	//	Бит  регистра REG_IR1_TL_GRN_SEC указывает о наличии правой секции поворота. 
#define			IR1_BIT_TL_GT_EN		0x80																	//	Бит  регистра REG_IR1_TL_RED_SEC указывает о наличии шлагбаума. 
//				Константы библиотеки:																			//
#define			MODUL_TLIGHT_AUTO		0x01																	//	begin     (MODUL_TLIGHT_AUTO ,  [, ]             ); определяем модуль на работу в качестве светофора с автопереключением его цветов.
#define			MODUL_TLIGHT			0x02																	//	begin     (MODUL_TLIGHT      ,  [, ]             ); определяем модуль на работу в качестве светофора.
#define			MODUL_SIGN				0x03																	//	begin     (MODUL_SIGN   , , [, ][, ]             ); определяем модуль на работу в качестве дорожного знака.
#define			TRACK_L					0x10	//	---100-- --------											//	begin     (MODUL_TLIGHT ,     TRACK_L   [, ]     ); определяем модуль на работу в качестве светофора регулирующего перекрёсток с движением только  налево.
#define			TRACK_F					0x08	//	---010-- --------											//	begin     (MODUL_TLIGHT ,     TRACK_F   [, ]     ); определяем модуль на работу в качестве светофора регулирующего перекрёсток с движением только  прямо.
#define			TRACK_R					0x04	//	---001-- --------											//	begin     (MODUL_TLIGHT ,     TRACK_R   [, ]     ); определяем модуль на работу в качестве светофора регулирующего перекрёсток с движением только  направо.
#define			TRACK_LF				0x18	//	---110-- --------											//	begin     (MODUL_TLIGHT ,     TRACK_LF  [, ]     ); определяем модуль на работу в качестве светофора регулирующего перекрёсток с движением налево  или прямо.
#define			TRACK_FL				0x18	//	---110-- --------											//	begin                   ,     TRACK_FL  [, ]
#define			TRACK_RF				0x0C	//	---011-- --------											//	begin     (MODUL_TLIGHT ,     TRACK_RF  [, ]     ); определяем модуль на работу в качестве светофора регулирующего перекрёсток с движением направо или прямо.
#define			TRACK_FR				0x0C	//	---011-- --------											//	begin                   ,     TRACK_FR  [, ]
#define			TRACK_LR				0x14	//	---101-- --------											//	begin     (MODUL_TLIGHT ,     TRACK_LR  [, ]     ); определяем модуль на работу в качестве светофора регулирующего перекрёсток с движением налево  или направо.
#define			TRACK_RL				0x14	//	---101-- --------											//	begin                   ,     TRACK_RL  [, ]
#define			TRACK_LFR				0x1C	//	---111-- --------											//	begin     (MODUL_TLIGHT ,     TRACK_LFR [, ]     ); определяем модуль на работу в качестве светофора регулирующего перекрёсток с движением налево, прямо или направо.
#define			TRACK_LRF				0x1C	//	---111-- --------											//	begin                   ,     TRACK_LRF [, ]
#define			TRACK_FLR				0x1C	//	---111-- --------											//	begin                   ,     TRACK_FLR [, ]
#define			TRACK_FRL				0x1C	//	---111-- --------											//	begin                   ,     TRACK_FRL [, ]
#define			TRACK_RFL				0x1C	//	---111-- --------											//	begin                   ,     TRACK_RFL [, ]
#define			TRACK_RLF				0x1C	//	---111-- --------											//	begin                   ,     TRACK_RLF [, ]
#define			SECTION_G				0x04	//	-----*00 --------											//	begin     (MODUL_TLIGHT , ,   SECTION_G          ); определяем модуль на работу в качестве светофора с шлагбаумом.
#define			SECTION_L				0x02	//	------10 --------											//	begin     (MODUL_TLIGHT , ,   SECTION_L          ); определяем модуль на работу в качестве светофора с секцией поворота влево.
#define			SECTION_R				0x01	//	------01 --------											//	begin     (MODUL_TLIGHT , ,   SECTION_R          ); определяем модуль на работу в качестве светофора с секцией поворота вправо.
#define			SECTION_LR				0x03	//	------11 --------											//	begin     (MODUL_TLIGHT , ,   SECTION_LR         ); определяем модуль на работу в качестве светофора с секциями поворота влево и вправо.
#define			SECTION_RL				0x03	//	------11 --------											//	begin                   , ,   SECTION_RL
#define			SECTION_LG				0x06	//	-----*10 --------											//	begin     (MODUL_TLIGHT , ,   SECTION_LG         ); определяем модуль на работу в качестве светофора с секцией поворота влево  и шлагбаумом.
#define			SECTION_GL				0x06	//	-----*10 --------											//	begin                   , ,   SECTION_GL
#define			SECTION_RG				0x05	//	-----*01 --------											//	begin     (MODUL_TLIGHT , ,   SECTION_RG         ); определяем модуль на работу в качестве светофора с секцией поворота вправо и шлагбаумом.
#define			SECTION_GR				0x05	//	-----*01 --------											//	begin                   , ,   SECTION_GR
#define			SECTION_LRG				0x07	//	-----*11 --------											//	begin     (MODUL_TLIGHT , ,   SECTION_LRG        ); определяем модуль на работу в качестве светофора с секциями поворота влево, вправо и шлагбаумом.
#define			SECTION_LGR				0x07	//	-----*11 --------											//	begin                   , ,   SECTION_LGR
#define			SECTION_RGL				0x07	//	-----*11 --------											//	begin                   , ,   SECTION_RGL
#define			SECTION_RLG				0x07	//	-----*11 --------											//	begin                   , ,   SECTION_RLG
#define			SECTION_GRL				0x07	//	-----*11 --------											//	begin                   , ,   SECTION_GRL
#define			SECTION_GLR				0x07	//	-----*11 --------											//	begin                   , ,   SECTION_GLR
#define			SIGN_CAR_TRUCK			15+1	//	-------- -----001											//	begin     (MODUL_SIGN , , , , SIGN_CAR_TRUCK     ); определяем модуль на работу в качестве дорожного знака действие которого распространяется только на грузовые автомобили.
#define			SIGN_CAR_LIGHT			15+2	//	-------- -----010											//	begin     (MODUL_SIGN , , , , SIGN_CAR_LIGHT     ); определяем модуль на работу в качестве дорожного знака действие которого распространяется только на легковые автомобили.
#define			SIGN_DISTANCE_050		15+3	//	-------- -----011											//	begin     (MODUL_SIGN , , , , SIGN_DISTANCE_050  ); определяем модуль на работу в качестве дорожного знака зона действия которого определена расстоянием в  50 метров.
#define			SIGN_DISTANCE_100		15+4	//	-------- -----100											//	begin     (MODUL_SIGN , , , , SIGN_DISTANCE_100  ); определяем модуль на работу в качестве дорожного знака зона действия которого определена расстоянием в 100 метров.
#define			SIGN_DISTANCE_150		15+5	//	-------- -----101											//	begin     (MODUL_SIGN , , , , SIGN_DISTANCE_150  ); определяем модуль на работу в качестве дорожного знака зона действия которого определена расстоянием в 150 метров.
#define			SIGN_DISTANCE_200		15+6	//	-------- -----110											//	begin     (MODUL_SIGN , , , , SIGN_DISTANCE_200  ); определяем модуль на работу в качестве дорожного знака зона действия которого определена расстоянием в 200 метров.
#define			SIGN_DISTANCE_250		15+7	//	-------- -----111											//	begin     (MODUL_SIGN , , , , SIGN_DISTANCE_250  ); определяем модуль на работу в качестве дорожного знака зона действия которого определена расстоянием в 250 метров.
#define			IR_UNDEFINED			0		//																//	irProtocol(IR_UNDEFINED                          ); сбросить ранее установленный протокол передачи данных.
#define			IR_NEC					1		//	NEC															//	irProtocol(IR_NEC                                ); установить ИК-протокол передачи данных NEC         (кодирование длинной паузы).
#define			IR_SAMSUNG				2		//	SAMSUNG														//	irProtocol(IR_SAMSUNG                            ); установить ИК-протокол передачи данных SAMSUNG     (кодирование длинной паузы).
#define			IR_SHARP				3		//	SHARP														//	irProtocol(IR_SHARP                              ); установить ИК-протокол передачи данных SHARP       (кодирование длинной паузы).
#define			IR_SIRC12				4		//	SONY														//	irProtocol(IR_SIRC12                             ); установить ИК-протокол передачи данных SIRC12      (кодирование длинной импульса).
#define			IR_SIRC15				5		//	SONY														//	irProtocol(IR_SIRC15                             ); установить ИК-протокол передачи данных SIRC15      (кодирование длинной импульса).
#define			IR_RC5					6		//	PHILIPS														//	irProtocol(IR_RC5                                ); установить ИК-протокол передачи данных RC5         (бифазное кодирование).
#define			IR_RC5X					7		//	PHILIPS														//	irProtocol(IR_RC5X                               ); установить ИК-протокол передачи данных RC5X        (бифазное кодирование).
#define			IR_RC6					8		//	PHILIPS														//	irProtocol(IR_RC6                                ); установить ИК-протокол передачи данных RC6         (бифазное кодирование)
#define			IR_IARDUINO				9		//	IARDUINO													//	irProtocol(IR_IARDUINO                           ); установить ИК-протокол передачи данных IR_IARDUINO (кодирование длинной паузы).
#define			TL_FORWARD_OFF			2																		//	set       (TL_FORWARD_OFF  [, ] [, ]             ); полуавтоматический переход на запрещающий сигнал светофора в прямом направлении.
#define			TL_FORWARD_ON			3																		//	set       (TL_FORWARD_ON   [, ] [, ]             ); полуавтоматический переход на разрешающий сигнал светофора в прямом направлении.
#define			TL_LEFT_OFF				4																		//	set       (TL_LEFT_OFF     [, ] [, ]             ); полуавтоматический переход на запрещающий сигнал левого  поворота светофора.
#define			TL_LEFT_ON				5																		//	set       (TL_LEFT_ON      [, ] [, ]             ); полуавтоматический переход на разрешающий сигнал левого  поворота светофора.
#define			TL_RIGHT_OFF			6																		//	set       (TL_RIGHT_OFF    [, ] [, ]             ); полуавтоматический переход на запрещающий сигнал правого поворота светофора.
#define			TL_RIGHT_ON				7																		//	set       (TL_RIGHT_ON     [, ] [, ]             ); полуавтоматический переход на разрешающий сигнал правого поворота светофора.
#define			TL_RED					8																		//	set       (TL_RED   ,0/1/2 [,до 7 пар параметров]); ручное управление красным цветом светофора.
#define			TL_YELLOW				9																		//	set       (TL_YELLOW,0/1/2 [,до 7 пар параметров]); ручное управление жёлтым  цветом светофора.
#define			TL_GREEN				10																		//	set       (TL_GREEN ,0/1/2 [,до 7 пар параметров]); ручное управление зелёным цветом светофора.
#define			TL_RIGHT				11																		//	set       (TL_RIGHT ,0/1/2 [,до 7 пар параметров]); ручное управление стрелкой светофора вправо.
#define			TL_LEFT					12																		//	set       (TL_LEFT  ,0/1/2 [,до 7 пар параметров]); ручное управление стрелкой светофора влево.
#define			TL_BEEP					13																		//	set       (TL_BEEP  ,0/1/2 [,до 7 пар параметров]); ручное управление звуковым сигналом.
#define			TL_GATE					14																		//	set       (TL_GATE  ,0/1   [,до 7 пар параметров]); ручное управление шлагбаумом.
#define			TL_ALL					15																		//	set       (TL_GATE  ,0/1   [,до 7 пар параметров]); ручное управление всеми цветами, звуком и шлагбаумом.
																												//
class iarduino_I2C_Track{																						//
	public:																										//
	/**	Конструктор класса **/																					//
		iarduino_I2C_Track							(uint8_t address=0){										//	Конструктор класса													(Параметр: адрес модуля на шине I2C, если не указан (=0), то адрес будет определён).
													if(address>0x7F){ address>>=1; }							//	Корректируем адрес, если он указан с учётом бита RW.
							valAddrTemp			=	address;													//	Сохраняем переданный адрес модуля.
							objI2C				=	new iarduino_I2C;											//	Переопределяем указатель objI2C на объект производного класса iarduino_I2C.
		}																										//
	/**	Пользовательские функции **/																			//
		bool				begin					(void					){ return begin(MODUL_SIGN,1,1); }	//	Объявляем  функцию инициализации модуля								(Параметр:  отсутствует).
		bool				begin					(uint8_t, uint8_t, uint8_t=0, uint8_t=0, uint8_t=0);		//	Объявляем  функцию инициализации модуля								(Параметры: тип модуля, группа знака или перекрёсток светофора [, номер знака или секции светофора] [, пункт знака] [, табличка знака].
		bool				reset					(void					);									//	Объявляем  функцию перезагрузки модуля								(Параметр:  отсутствует).
		bool				changeAddress			(uint8_t				);									//	Объявляем  функцию смены адреса модуля на шине I2C					(Параметр:  новый адрес модуля).
		uint8_t				getAddress				(void					){ return valAddr; }				//	Определяем функцию возвращающую текущий адрес модуля на шине I2C	(Параметр:  отсутствует).
		uint8_t				getVersion				(void					){ return valVers; }				//	Определяем функцию возвращающую текущую версию прошивки модуля		(Параметр:  отсутствует).
		bool				getPullI2C				(void					);									//	Объявляем  функцию возвращающую флаг наличия подтяжки шины I2C		(Параметр:  отсутствует).
		bool				setPullI2C				(bool=true				);									//	Объявляем  функцию установки    подтяжки шины I2C					(Параметр:  флаг подтяжки).
		bool				backlight				(uint8_t, uint8_t=255	);									//	Объявляем  функцию управления   подсветкой знака					(Параметры: 0-откл/1-вкл/2-мигать [, 0-откл/1-вкл/2-мигать]).
		bool				indicator				(bool					);									//	Объявляем  функцию управления   светодиодом информ о передаче данных(Параметр:  0-откл/1-вкл). Применяется и для знака, и для светофора.
		bool				irProtocol				(uint8_t				);									//	Объявляем  функцию установки    протокола передачи данных по ИК     (Параметр:  протокол).
		bool				irSend					(void					);									//	Объявляем  функцию отправки     информации по ИК-каналу однократно	(Параметр:  отсутствует).  Применяется и для знака, и для светофора.
		void				irWait					(void					);									//	Объявляем  функцию ожидания     завершения однократной отправки		(Параметр:  отсутствует).  Применяется и для знака, и для светофора.
		bool				irAutoSend				(uint8_t=0				);									//	Объявляем  функцию отправки     информации по ИК-каналу постоянно	(Параметр:  25-255 мс).    Применяется и для знака, и для светофора.
		bool				irStop					(void					);									//	Объявляем  функцию остановки    постоянной отправки информации		(Параметр:  отсутствует).  Применяется и для знака, и для светофора.
		bool				offline					(bool					);									//	Объявляем  функцию установки    автономного режима работы			(Параметр:  0-откл/1-вкл). Применяется и для знака, и для светофора.
		bool				timing					(uint8_t, uint8_t, uint8_t);								//	Объявляем  функцию установки    времени свечения всех цветов светоф.(Параметры: время свечения зелёного, жёлтого (или мигающего зелёного), красного сигналов от 1 до 127 секунд).
		bool				timing					(uint8_t g, uint8_t r	){ return timing(g, 0, r); }		//	Определяем функцию установки    времени свечения зелёного и красного(Параметры: время свечения зелёного, красного сигналов от 1 до 127 секунд).
		bool				timing					(uint8_t				);									//	Объявляем  функцию установки    времени свечения жёлтого цвета		(Параметр:  время свечения жёлтого (или мигающего зелёного) от 1 до 127 секунд).
		bool				set						(uint8_t, uint8_t=0, uint8_t=0, uint8_t=0, uint8_t=0, uint8_t=0, uint8_t=0, uint8_t=0, uint8_t=0, uint8_t=0, uint8_t=0, uint8_t=0, uint8_t=0, uint8_t=0);	//	Объявляем  функцию управления светофором в ручном и полуавтомате (Параметры: [разрешение[,разрешение[,разрешение]]] или [цвет, флаг [,цвет, флаг [,цвет, флаг [,цвет, флаг [,цвет, флаг [,цвет, флаг [,цвет, флаг]]]]]]]).
		bool				gateSpeed				(uint8_t				);									//	Объявляем  функцию установки    скорости шлагбаума в авто режиме	(Параметр:  скорость от 0-мин до 255-мах). Скорость сохраняется в энергонезависимую память.
		bool				gateWidth				(uint16_t				);									//	Объявляем  функцию установки    ширины импульсов ШИМ шлагбаума		(Параметр:  ширина импульсов ШИМ от 0 мкс до 20'000 мкс.
		bool				gateWidthOpen			(uint16_t				);									//	Объявляем  функцию установки    ширины имп. ШИМ открытого шлагбаума	(Параметр:  ширина импульсов ШИМ от 1 мкс до 19'999 мкс. Ширина импульсов хранится в энергонезависимой памяти.
		bool				gateWidthClose			(uint16_t				);									//	Объявляем  функцию установки    ширины имп. ШИМ закрытого шлагбаума	(Параметр:  ширина импульсов ШИМ от 1 мкс до 19'999 мкс. Ширина импульсов хранится в энергонезависимой памяти.
	private:																									//
	/**	Внутренние переменные **/																				//
		uint8_t				valAddrTemp			=	0;															//	Определяем переменную для хранения адреса модуля на шине I2C который был указан, но не был проверен.
		uint8_t				valAddr				=	0;															//	Определяем переменную для хранения адреса модуля на шине I2C.
		uint8_t				valVers				=	0;															//	Определяем переменную для хранения версии прошивки модуля.
		uint8_t				data[6];																			//	Объявляем  массив     для хранения получаемых/передаваемых данных.
		iarduino_I2C_BASE*	objI2C;																				//	Объявляем  указатель  на  объект полиморфного класса iarduino_I2C_BASE, но в конструкторе данного класса этому указателю будет присвоена ссылка на производный класс iarduino_I2C.
		uint16_t			valIrAdrCom			=	0;															//	Определяем переменную для хранения адреса и команды передаваемой по ИК-каналу.
		bool				flgGate				=	0;															//	Определяем флаг наличия шлагбаума (наличие секций поворота определено битами SECTION_L/R переменной valIrAdrCom, а флага наличия шлагбаума там нет).
	/**	Внутренние функции **/																					//
		bool				_readBytes				(uint8_t, uint8_t								);			//	Объявляем  функцию чтения данных в  массив  data					(Параметры: номер первого регистра, количество байт).
		bool				_writeBytes				(uint8_t, uint8_t, uint8_t=0					);			//	Объявляем  функцию записи данных из массива data					(Параметры: номер первого регистра, количество байт, номер первого элемента массива data).
};																												//
																												//
#endif																											//