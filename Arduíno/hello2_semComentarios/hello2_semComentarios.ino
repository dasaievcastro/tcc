/* Arquivo para desenvolvimento da aplicação do arduíno
Programador/Autor: Dasaiev Castro
Programador/Revisor: Felipe Diogenes

 * Bibliotecas*/
#include <Ethernet.h>
#include <SocketIOClient.h>
#include <SPI.h>
#include <Thread.h>
#include <ThreadController.h>

SocketIOClient client;

/*Configurando MAC ADDRESS*/
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE};

/*IP de configuração do servidor*/
char hostname[] = "192.168.1.2"; //"54.207.65.161"; //"192.168.0.25";// //

/*configurar porta do socket.io*/
const int port = 8087;

//configurando estrutura pra usar no vetor.

typedef struct {
    char* nome;
    char* enviar;
    char* printar;
    byte pino;
    byte sinal;
} Opcao;

int soma = 0;
int i;
/*Pinos para mapeamento das lampadas RGB da Casa*/
int redpin = 28; //Pin 9
int greenpin = 30; //Pin 10
int bluepin = 32; //Pin 11
int sensorTemperatura = A8;
int interruptor = 18;
int ledCopa = 22;
int ventilador = 24;
/*Objeto para representar thread de leitura da temperatura do comodo da cada*/
Thread threadTemperatura;



Opcao opcoes[4] = {
    {"salaOFF", "salaDesligado", "desliga", 40, 0},
    {"salaON", "salaLigado", "liga", 40, 1},
    {"copaOFF", "copaDesligado", "desliga", ledCopa, 0},
    {"copaON", "copaLigado", "liga", ledCopa, 1}
};

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

/*Função que trata os eventos do socketio enviadaos pela aplicação*/

void ondata(SocketIOClient client, char *data) {
    String str(data);
    soma++;
    if(str.indexOf("novacor")>=0){
        Serial.println("mudacor");
        str.replace("novacor","");
        Serial.println(str);
        String R = getValue(str,',',0);
        String G = getValue(str,',',1);
        String B = getValue(str,',',2);
        Serial.println(R);
        Serial.println(G);
        Serial.println(B);
        analogWrite(redpin,R.toInt());
        analogWrite(greenpin,G.toInt());
        analogWrite(bluepin,B.toInt());
    }
    if (str == "salaOFF") {// recebe de 
        client.send("salaDesligado"); // envia pra todos clientes 
        Serial.println("desliga");
        digitalWrite(40, LOW);
    } else if (str == "salaON") {// recebe de 
        client.send("salaLigado"); // envia pra todos clientes 
        Serial.println("liga");
        digitalWrite(40, HIGH); //////////////////////////////////////fim sala
    } else if (str == "copaOFF") {// recebe de 
        client.send("copaDesligado"); // envia pra todos clientes 
        Serial.println("desliga");
        digitalWrite(ledCopa, LOW);
    } else if (str == "copaON") {// recebe de 
        client.send("copaLigado"); // envia pra todos clientes 
        Serial.println("liga");
        digitalWrite(ledCopa, HIGH); ////////////////////////////////////fim sala2
    } else if (str == "cozinhaOFF") {// recebe de 
        client.send("cozinhaDesligado"); // envia pra todos clientes 
        Serial.println("desliga");
        digitalWrite(42, LOW);
    } else if (str == "cozinhaON") {// recebe de 
        client.send("cozinhaLigado"); // envia pra todos clientes 
        Serial.println("liga");
        digitalWrite(42, HIGH); ////////////////////////////////////fim cozinha
    } else if (str == "quartoOFF") {// recebe de 
        client.send("quartoDesligado"); // envia pra todos clientes 
        Serial.println("desliga");
        digitalWrite(3, LOW);
    } else if (str == "quartoON") {// recebe de 
        client.send("quartoLigado"); // envia pra todos clientes 
        Serial.println("liga");
        digitalWrite(3, HIGH); ////////////////////////////////////fim quarto
    } else if (str == "banheiroOFF") {// recebe de 
        client.send("banheiroDesligado"); // envia pra todos clientes 
        Serial.println("desliga");
        digitalWrite(44, LOW);
    } else if (str == "banheiroON") {// recebe de 
        client.send("banheiroLigado"); // envia pra todos clientes 
        Serial.println("liga");
        digitalWrite(44, HIGH); ////////////////////////////////////fim banheio
    } else if (str == "varandaOFF") {// recebe de 
        client.send("varandaDesligado"); // envia pra todos clientes 
        Serial.println("desliga");
        digitalWrite(45, LOW);
    } else if (str == "varandaON") {// recebe de 
        client.send("varandaLigado"); // envia pra todos clientes 
        Serial.println("liga");
        digitalWrite(45, LOW); ////////////////////////////////////fim varanda
    } else if (str == "portaoOFF") {// recebe de 
        client.send("portaoDesligado"); // envia pra todos clientes 
        Serial.println("desliga");
        digitalWrite(46, LOW);
    } else if (str == "portaoON") {// recebe de 
        client.send("portaoLigado"); // envia pra todos clientes 
        Serial.println("liga");
        digitalWrite(46, HIGH); ////////////////////////////////////fim portao
    } else if (str == "alarmeOFF") {// recebe de 
        client.send("alarmeDesligado"); // envia pra todos clientes 
        Serial.println("desliga");
        digitalWrite(47, LOW);
    } else if (str == "alarmeON") {// recebe de 
        client.send("alarmeLigado"); // envia pra todos clientes 
        Serial.println("liga");
        digitalWrite(47, HIGH);
    } ////////////////////////////////////fim alarme
//    } else if (str == "novacor255,255,255") {
//        //esquema do led 
//        analogWrite(greenpin, 255);
//        analogWrite(redpin, 0);
//        analogWrite(bluepin, 0);
//    }


}

//função para medir a temperatura

void medeTemperatura() {

    float temp = analogRead(sensorTemperatura);
    temp = (temp * 0.488);
    Serial.print("temperatura:");
    Serial.println(temp);
    if (temp > 33) {
        ligaVentilador(String(temp));
    } else {
        desligaVentilador(String(temp));
    }
    //client.send("temperatura" + temp);
    //
}

void ligaVentilador(String temp) {
    //void
    String enviar = "temperatura"+temp;
    char charBuf[50];
    enviar.toCharArray(charBuf, 50); 
    client.send(charBuf);
    digitalWrite(ventilador,HIGH);
}

void desligaVentilador(String temp) {
    //void
    String enviar = "temperatura"+temp;
    char charBuf[50];
    enviar.toCharArray(charBuf, 50); 
    client.send(charBuf);
    digitalWrite(ventilador,LOW);
}

void setup() {
    Serial.begin(9600);

    //interruptor
    //pinMode(interruptor,INPUT);
  
    //led copa
    pinMode(ledCopa,OUTPUT);
    //cooler ventilador
    
    pinMode(ventilador,OUTPUT);
    
    //pinos rgb
    
    pinMode(redpin,OUTPUT);
    pinMode(bluepin,OUTPUT);
    pinMode(greenpin,OUTPUT);
    
    
//    analogWrite(redpin,255);
//        analogWrite(greenpin,144);
//        analogWrite(bluepin,132);

    //módulo ethernet sd3
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);

    /*Setando thread pra verificar temperaturas*/
    threadTemperatura.setInterval(2000);
    threadTemperatura.onRun(medeTemperatura);

    // quarto com arduino UNO
    pinMode(3, OUTPUT);

    //interruptor
    
    attachInterrupt(5, mudar, HIGH);

    /*Iniciando conexão com internet*/
    Ethernet.begin(mac);
    delay(1000);
    Serial.println(Ethernet.localIP());
    client.setDataArrivedDelegate(ondata);

    //enquanto desconectado tenta concetar à rede
    while (!client.connect(hostname, port)) {
        Serial.println("Not connected.");
        client.connect(hostname, port);
    }
    delay(1);
}

int valorInterruptor = 0;

void loop() {
    //executando thread temperatura
    if (threadTemperatura.shouldRun()) {
        threadTemperatura.run();
    }
    
    
    //instanciando leitor do socket.io
    client.monitor();
    delay(1);

}

void mudar(){
  valorInterruptor = digitalRead(interruptor);
    if(valorInterruptor == HIGH){
      int valorLedCopa = digitalRead(ledCopa);
      if(valorLedCopa==HIGH){
        Serial.println("apaga");
        digitalWrite(ledCopa,LOW);
        client.send("copaDesligado");      
      }else{
        digitalWrite(ledCopa,HIGH);
        Serial.println("apagas");
        client.send("copaLigado");
      }    
    }
}
