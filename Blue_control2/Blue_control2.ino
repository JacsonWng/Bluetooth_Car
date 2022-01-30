//author：wangxiao
//date tume:2022.01.30
//蓝牙遥控小车
#include <Arduino.h>

//引脚定义
#define PWMA 3
#define AIN1 2
#define AIN2 4
#define BIN1 6
#define BIN2 7
#define PWMB 9

char cmd;
int xPWM = 0;
int yPWM = 0;
int PWMa = 0;
int PWMb = 0;

/************引脚初始化**********/
void setup()
{
    Serial.begin(9600);
    pinMode(PWMA, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
}

/**********小车运动函数*********/
void forward(int PWM){//前进
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, PWM);
  analogWrite(PWMB, PWM);
  delay(10);
}

void backward(int PWM){//后退
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, PWM);
  analogWrite(PWMB, PWM);
  delay(10);
}

void turnLeft(int PWMa, int PWMb){//左转
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, PWMa);
  analogWrite(PWMB, PWMb);
  delay(10);
}

void turnRight(int PWMa, int PWMb){//右转
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, PWMa);
  analogWrite(PWMB, PWMb);
  delay(10);
}

void Brake(){//刹车
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  delay(10);
}

void STOP()//急停
{
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, HIGH);
  delay(10);
}


/**************以下解析字符串中数值的方法没有直接使用库函数Serial.parseInt()快捷*************/
/*void findPWM(void)
{
  //求字长
    for(int i = 0;i < cmd.length();i++)
    {
      if(cmd[i] == ',')
      {
        xL = i - 1;
      }

      if(cmd[i] == 's')
      {
          yL = i - (xL+1) - 1; 
      }
    }

    //解算xPWM
    if(xL == 1)
    {
      xPWM = int(cmd[2]) - 48;
    }
    if(xL == 2)      
    {
      xPWM = (int(cmd[3]) - 48) + (int(cmd[2]) - 48) * 10;
    }
    if(xL == 3)
    {
      xPWM = (int(cmd[4]) - 48) + (int(cmd[3]) - 48) * 10 + (int(cmd[2]) - 48) * 100;
    }

    //解算yPWM
    if(yL == 1)
    {
      yPWM = int(cmd[xL + 4]) - 48;
    }
    if(yL == 2)      
    {
      yPWM = (int(cmd[xL + 5]) - 48) + (int(cmd[xL + 4]) - 48) * 10;
    }
    if(yL == 3)
    {
      yPWM = (int(cmd[xL + 6]) - 48) + (int(cmd[xL + 5]) - 48) * 10 + (int(cmd[xL + 4]) - 48) * 100;
    }
}*/

/****************摇杆控制***************/
void pad_Control(void)
{
  if(cmd == 'X')//X轴摇杆
  {
    xPWM = Serial.parseInt();
    if(xPWM > 0)
    {
      //turnRight(xPWM);
    }else if(xPWM < 0)
    {
      //turnLeft(xPWM);
    }else if(xPWM == 0)
    {
      Brake();
    }
  }

  if(cmd == 'Y')//Y轴摇杆
  {
    yPWM = Serial.parseInt();
    if(yPWM < 0)
    {
      forward(yPWM);
    }else if(yPWM > 0)
    {
      backward(yPWM);
    }else if(yPWM == 0)
    {
      Brake();
    }
  }
}

/**************按键控制***************/
void key_Control(void)
{
  if(cmd == 'f')
  {
    forward(PWMa);
  }else if(cmd == 'b')
  {
    backward(PWMa);
  }else if(cmd == 'l')
  {
    turnLeft(PWMa, PWMb);
  }else if(cmd == 'r')
  {
    turnRight(PWMa, PWMb);
  }else
  {
    Brake();
  }

}


void loop()
{
    if(Serial.available())//检测串口是否有字符发来
    {
      cmd = Serial.read();
      //Serial.println(cmd);
      if(cmd == 's')//急刹车
      {
        STOP();
      }

      if(cmd == 'A')
      {
        PWMa = Serial.parseInt();
      }
      if(cmd == 'B')
      {
        PWMb = Serial.parseInt();
      }
      //摇杆控制
      //pad_Control();
      //按键控制
      key_Control();
    }
}
