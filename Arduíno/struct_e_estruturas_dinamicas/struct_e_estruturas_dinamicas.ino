struct Opcao {
    String nome;
    String enviar;
    String printar;
    byte pino;
    byte sinal;
};

Opcao opcoes[] = {
    {"salaOFF", "salaDesligado", "desliga", 40, 0},
    {"salaON", "salaLigado", "liga", 40, 1},
    {"sala2OFF", "sala2Desligado", "desliga", 41, 0},
    {"sala2ON", "sala2Ligado", "liga", 41, 1}
   
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  int tamanho = (sizeof(opcoes)/sizeof(Opcao));
  for(int i=0;i<tamanho;i++){
    if(opcoes[i].nome=="sala2ON"){
      //aqui vem os comandos dps interrompe
      
      break;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
