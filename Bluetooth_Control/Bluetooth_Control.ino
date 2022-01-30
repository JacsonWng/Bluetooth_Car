//author：wangxiao
//date tume:2022.01.14
//蓝牙遥控小车

//引脚定义
#define PWMA 3
#define AIN1 2
#define AIN2 4
#define BIN1 6
#define BIN2 7
#define PWMB 9

char cmd;                           //定义接收指令字符
int pwma = 150;
int pwmb = 150;

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
void forward(){//前进
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  delay(10);
}

void backward(){//后退
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  delay(10);
}

void turnLeft(){//左转
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  delay(10);
}

void turnRight(){//右转
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
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


void loop()
{
    if(Serial.available())//检测串口是否有字符发来
    {
        cmd = Serial.read();
        Serial.println();
        switch(cmd)
      {
        case 'f': analogWrite(PWMA, pwma); analogWrite(PWMB, pwmb); forward(); break;
        case 'b': analogWrite(PWMA, pwma); analogWrite(PWMB, pwmb); backward(); break;
        case 'l': analogWrite(PWMA, 200); analogWrite(PWMB, 120); turnLeft(); break;
        case 'r': analogWrite(PWMA, 120); analogWrite(PWMB, 200); turnRight(); break;
        case 'F': analogWrite(PWMA, 250); analogWrite(PWMB, 250); forward(); break;
        case 'B': analogWrite(PWMA, 250); analogWrite(PWMB, 250); backward(); break;
        case 'L': analogWrite(PWMA, 220); analogWrite(PWMB, 220); turnLeft(); break;
        case 'R': analogWrite(PWMA, 220); analogWrite(PWMB, 220); turnRight(); break;
        case 'k': analogWrite(PWMA, pwma); analogWrite(PWMB, pwmb); Brake(); break;
        case 's': analogWrite(PWMA, 0); analogWrite(PWMB, 0); STOP(); break;
        default:
            Brake();break;
      }
    }
}
