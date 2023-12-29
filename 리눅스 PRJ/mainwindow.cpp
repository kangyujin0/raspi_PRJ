#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <softTone.h>

#define LED0 4
#define LED1 21	// A 11
#define LED2 16	// B 7
#define LED3 23	// C 4
#define LED4 25	// D 2
#define LED5 12	// E 1
#define LED6 20	// F 10
#define LED7 18	// G 5
#define LED8 24	// DP 3
#define DIG1 19
#define DIG2 13
#define DIG3 6
#define DIG4 5

const int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); 
    wiringPiSetupGpio();
    pinPiezo = 27;
    softToneCreate(pinPiezo);
    mcp3004Setup(BASE, SPI_CHAN);

    //connect(ui->LEDon, &QToolButton::clicked, this, &MainWindow::onLedButtonClicked);
    //connect(ui->piezo, &QToolButton::clicked, this, &MainWindow::on_piezo_2_clicked);

    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);
    pinMode(LED6, OUTPUT);
    pinMode(LED7, OUTPUT);
    pinMode(LED8, OUTPUT);
    pinMode(DIG1, OUTPUT);
    pinMode(DIG2, OUTPUT);
    pinMode(DIG3, OUTPUT);
    pinMode(DIG4, OUTPUT);
    for(int i = 0; i < 4; i++){
        digitalWrite(digPin[i], LOW);
    }
    for(int i = 0; i < 8; i++){
        digitalWrite(pin[i], LOW);
    }  
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LEDon_clicked()
{    
    for(int i = 0; i < 5; i++){
        digitalWrite(LED0, HIGH);
        ui->textEdit->append("LED on");
        QCoreApplication::processEvents();
        delay(100);
        digitalWrite(LED0, LOW);
        ui->textEdit->append("LED off");
        QCoreApplication::processEvents();
        delay(100);
    }
}

void MainWindow::on_piezo_clicked()
{
    QString noteNames[] = {"도", "레", "미", "파", "솔", "라", "시", "도"};
    for (int i = 0; i < 8; ++i) {
        softToneWrite(pinPiezo, melody[i]);
        delay(100);
        QString note = noteNames[i];    // 음계를 textEdit에 출력
        ui->textEdit->append("Note: " + note);
        QCoreApplication::processEvents();
    }
    softToneWrite(pinPiezo, 0);
}

void MainWindow::on_FND_clicked()
{    
    for(int j = 0; j < 500; j++){
        digitalWrite(DIG1, HIGH);
        digitalWrite(DIG2, LOW);
        digitalWrite(DIG3, LOW);
        digitalWrite(DIG4, LOW);
        digitalWrite(LED1, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED6, LOW);
        digitalWrite(LED7, LOW);
        printf("S\n");
        delay(1);
        for(int i = 0; i < 8; i++){
            digitalWrite(pin[i], HIGH);
        }

        digitalWrite(DIG1, LOW);
        digitalWrite(DIG2, HIGH);
        digitalWrite(DIG3, LOW);
        digitalWrite(DIG4, LOW);
        digitalWrite(LED1, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);
        digitalWrite(LED6, LOW);
        digitalWrite(LED7, LOW);
        printf("E\n");
        delay(1);
        for(int i = 0; i < 8; i++){
            digitalWrite(pin[i], HIGH);
        }

        digitalWrite(DIG1, LOW);
        digitalWrite(DIG2, LOW);
        digitalWrite(DIG3, HIGH);
        digitalWrite(DIG4, LOW);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED5, LOW);
        digitalWrite(LED6, LOW);
        digitalWrite(LED7, LOW);
        printf("P\n");
        delay(1);
        for(int i = 0; i < 8; i++){
            digitalWrite(pin[i], HIGH);
        }

        digitalWrite(DIG1, LOW);
        digitalWrite(DIG2, LOW);
        digitalWrite(DIG3, LOW);
        digitalWrite(DIG4, HIGH);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        printf("7\n");
        delay(1);
        for(int i = 0; i < 8; i++){
            digitalWrite(pin[i], HIGH);
        }
    }
    ui->textEdit->append("FND 실행이 완료되었습니다.");
}

void MainWindow::on_LCD_clicked()
{
    xio = wiringPiI2CSetup(I2C_ADDR);
    lcd_init();

    char str1[] = "Hello World";
    char str2[] = "QT Programming";
    for(int i = 0; i < 2; i++){
        lcdClear();
        lcdLoc(LINE1);
        typeln("I2C Program");
        lcdLoc(LINE2);
        typeln("LCD TEST");
        delay(2000);

        lcdClear();
        lcdLoc(LINE1);
        typeln(str1);
        lcdLoc(LINE2);
        typeln(str2);
        delay(2000);
    }
    ui->textEdit->append("LCD 실행이 완료되었습니다.");
}
void MainWindow::typeFloat(float myFloat)
{
    char buffer[20];
    sprintf(buffer, "%4.2f", myFloat);
    typeln(buffer);
}
/*정수를 문자열로 변환하여 LCD에 출력 sprintf 함수를 사용하여 정수 값을 문자열로 변환*/
void MainWindow::typeInt(int i)
{
    char array[20];
    sprintf(array, "%d", i);
    typeln(array);
}
/*LCD 화면을 지우는 함수*/
void MainWindow::lcdClear(void)
{
    lcd_byte(0x01, LCD_CMD);
    lcd_byte(0x02, LCD_CMD);
}
/*LCD 화면의 특정 라인으로 커서를 이동시키는 함수*/
void MainWindow::lcdLoc(int line)
{
    lcd_byte(line, LCD_CMD);
}
/*주어진 문자(char)를 LCD에 출력하는 함수*/
void MainWindow::typeChar(char val)
{
    lcd_byte(val, LCD_CHR);
}
/*주어진 문자열을 LCD에 출력하는 함수*/
void MainWindow::typeln(const char *s)
{
    while(*s) lcd_byte(*(s++), LCD_CHR);
}
/*LCD에 명령을 보내는 함수 bits와 mode를 조합하여 LCD에 데이터를 전송*/
void MainWindow::lcd_byte(int bits, int mode)
{
    int bits_high;
    int bits_low;
    bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT;
    bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT;

    wiringPiI2CReadReg8(xio, bits_high);
    lcd_toggle_enable(bits_high);

    wiringPiI2CReadReg8(xio, bits_low);
    lcd_toggle_enable(bits_low);
}
/*LCD Enable 핀을 토글하는 함수*/
void MainWindow::lcd_toggle_enable(int bits)
{
    delayMicroseconds(500);
    wiringPiI2CReadReg8(xio, (bits | ENABLE));
    delayMicroseconds(500);
    wiringPiI2CReadReg8(xio, (bits& ~ENABLE));
    delayMicroseconds(500);
}
/*LCD 초기화를 위한 함수*/
void MainWindow::lcd_init()
{
    lcd_byte(0x33, LCD_CMD);
    lcd_byte(0x32, LCD_CMD);
    lcd_byte(0x06, LCD_CMD);
    lcd_byte(0x0C, LCD_CMD);
    lcd_byte(0x28, LCD_CMD);
    lcd_byte(0x01, LCD_CMD);
    delayMicroseconds(500);
}

void MainWindow::on_CDS_clicked()
{
    for(int i = 0; i < 10; i++){
        int cdsValue = analogRead(BASE + SPI_CHAN);
        ui->lcdNumber->display(cdsValue); // QLCDNumber에 값 표시
        QCoreApplication::processEvents();
        digitalWrite(LED0, HIGH);
        delay(500);
        digitalWrite(LED0, LOW);
        delay(500);
    }
    ui->textEdit->append("CDS 실행이 완료되었습니다.");
}
