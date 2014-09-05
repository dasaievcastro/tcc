#include <Ethernet.h>
#include <SocketIOClient.h>
#include <SPI.h>
#include <Thread.h>
#include <ThreadController.h>

SocketIOClient client;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };
char hostname[] = "192.168.0.9"; //"54.207.65.161"; //"192.168.0.25";// //
//IPAddress ip(192, 168, 0, 11); // para definir ip manualmente
const int port = 8087;

int soma = 0;
int i;
int redpin=6;      //Pin 9
int greenpin=3;    //Pin 10
int bluepin=5;      //Pin 11
int sensorTemperatura = 0;
Thread threadTemperatura;

void software_Reset() // Restarta o programa do inicio mas nao reseta os perifericos e registradores 
{
 ("jmp 0");  
}

void ondata(SocketIOClient client, char *data) {  
  String str(data);
  soma++;
  
  Serial.println("Req numero: ");
  Serial.println(soma);
  
   if(soma==500){
    client.send("resetando");
    digitalWrite(7, LOW); //resetar ethernet (relê)
    delay(1000); //tempo para descarregamento dos capacitores
    software_Reset(); // resetar arduino (exceto perifericos)
  }

  if(str=="salaOFF"){// recebe de 
   client.send("salaDesligado"); // envia pra todos clientes 
   Serial.println("desliga");
   digitalWrite(40, LOW);
  }else if(str=="salaON"){// recebe de 
   client.send("salaLigado"); // envia pra todos clientes 
   Serial.println("liga");
   digitalWrite(40, HIGH);//////////////////////////////////////fim sala
  }else if(str=="sala2OFF"){// recebe de 
   client.send("sala2Desligado"); // envia pra todos clientes 
   Serial.println("desliga");
   digitalWrite(41, LOW);
  }else if(str=="sala2ON"){// recebe de 
   client.send("sala2Ligado"); // envia pra todos clientes 
   Serial.println("liga");
   digitalWrite(41, HIGH);////////////////////////////////////fim sala2
  }else if(str=="cozinhaOFF"){// recebe de 
   client.send("cozinhaDesligado"); // envia pra todos clientes 
   Serial.println("desliga");
   digitalWrite(42, LOW);
  }else if(str=="cozinhaON"){// recebe de 
   client.send("cozinhaLigado"); // envia pra todos clientes 
   Serial.println("liga");
   digitalWrite(42, HIGH);////////////////////////////////////fim cozinha
  }else if(str=="quartoOFF"){// recebe de 
   client.send("quartoDesligado"); // envia pra todos clientes 
   Serial.println("desliga");
   digitalWrite(3, LOW);
  }else if(str=="quartoON"){// recebe de 
   client.send("quartoLigado"); // envia pra todos clientes 
   Serial.println("liga");
   digitalWrite(3, HIGH);////////////////////////////////////fim quarto
  }else if(str=="banheiroOFF"){// recebe de 
   client.send("banheiroDesligado"); // envia pra todos clientes 
   Serial.println("desliga");
   digitalWrite(44, LOW);
  }else if(str=="banheiroON"){// recebe de 
   client.send("banheiroLigado"); // envia pra todos clientes 
   Serial.println("liga");
   digitalWrite(44, HIGH);////////////////////////////////////fim banheio
  }else if(str=="varandaOFF"){// recebe de 
   client.send("varandaDesligado"); // envia pra todos clientes 
   Serial.println("desliga");
   digitalWrite(45, LOW);
  }else if(str=="varandaON"){// recebe de 
   client.send("varandaLigado"); // envia pra todos clientes 
   Serial.println("liga");
   digitalWrite(45, LOW);////////////////////////////////////fim varanda
  }else if(str=="portaoOFF"){// recebe de 
   client.send("portaoDesligado"); // envia pra todos clientes 
   Serial.println("desliga");
   digitalWrite(46, LOW);
  }else if(str=="portaoON"){// recebe de 
   client.send("portaoLigado"); // envia pra todos clientes 
   Serial.println("liga");
   digitalWrite(46, HIGH);////////////////////////////////////fim portao
  }else if(str=="alarmeOFF"){// recebe de 
   client.send("alarmeDesligado"); // envia pra todos clientes 
   Serial.println("desliga");
   digitalWrite(47, LOW);
  }else if(str=="alarmeON"){// recebe de 
   client.send("alarmeLigado"); // envia pra todos clientes 
   Serial.println("liga");
   digitalWrite(47, HIGH);////////////////////////////////////fim alarme
  }else if(str=="novacor255,255,255"){
  //esquema do led 
  Serial.println("asfdsadf");
  analogWrite(greenpin,255);
  analogWrite(redpin,0);
  analogWrite(bluepin,0);
  }
  

}

void medeTemperatura(){
  
  float temp = analogRead(sensorTemperatura);
  temp = (temp*0.00488)*100;
  Serial.print("temperatura:");
  Serial.println(temp);
  if(temp>33){
     ligaVentilador(); 
  }else{
     desligaVentilador(); 
  }
  client.send("temperatura"+temp);
  //
}

void ligaVentilador(){
  
  
}

void desligarVentilador(){
  
}

void setup() {
	Serial.begin(9600);
        //pinMode(10, OUTPUT);
        //digitalWrite(10, HIGH);
        pinMode(7, OUTPUT);//reset ethernet
        digitalWrite(7, HIGH);
        threadTemperatura.setInterval(6000);
        threadTemperatura.onRun(medeTemperatura);
        //for(i=40;i<47;i++){ //para mega
        //pinMode(i,OUTPUT);
        //}
        
        pinMode(3,OUTPUT); // quarto com arduino UNO
        //Ethernet.begin(mac);
        delay(1000);
        //Serial.println(Ethernet.localIP());
	//client.setDataArrivedDelegate(ondata);

	
        //while (!client.connect(hostname, port)){ //enquanto desconectado tenta concetar `a rede
          // Serial.println("Not connected.");
          //client.connect(hostname, port);
        // }
   //client.send("voltei");
   Serial.println("Voltei.");
   delay(1);
}

int incomingByte = 0;
void loop() {
  if(threadTemperatura.shouldRun()){
     threadTemperatura.run(); 
  }
  //if(!client.connected()){
    //client.send("resetando");
    //digitalWrite(7, LOW); //resetar ethernet (relê)
    //delay(2000);
    //digitalWrite(7, HIGH); //resetar ethernet (relê)
    //delay(1);
    //software_Reset(); // reseta programa no inicio sem resetar perifericos e registradores
  //}
  //if(!client.connect(hostname, port)){ //enquanto desconectado tenta concetar `a rede
    //    client.connect(hostname, port);
  //}
  
  //client.monitor();
  delay(1);
	
}
