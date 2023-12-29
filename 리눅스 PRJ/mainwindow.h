#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <QTextEdit>
#include <QToolButton>
#include <QLCDNumber>
#include <mcp3004.h>

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

#define I2C_ADDR 0x3f
#define LCD_CHR  1
#define LCD_CMD  0
#define LINE1    0x80
#define LINE2    0xC0
#define LCD_BACKLIGHT  0x08
#define ENABLE   0x04

#define BASE 100
#define SPI_CHAN 0
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int pin[8] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
    int digPin[4] = {DIG1, DIG2, DIG3, DIG4};
    int pinPiezo;    

private slots: 
    void on_LEDon_clicked();
    void on_piezo_clicked();
    void on_FND_clicked();
    void on_LCD_clicked();
    void on_CDS_clicked();

private:
    Ui::MainWindow *ui;
    QTextEdit *textEdit;
    void lcd_init(void);
    void lcd_byte(int bits, int mode);
    void lcd_toggle_enable(int bits);
    void typeInt(int i);
    void typeFloat(float myFloat);
    void lcdLoc(int line);
    void lcdClear(void);
    void typeln(const char* s);
    void typeChar(char val);
    int xio; 
};
#endif // MAINWINDOW_H
